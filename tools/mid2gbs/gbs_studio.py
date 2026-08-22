#!/usr/bin/env python3
"""
gbs_studio.py - GUI front-end for midi_to_gbs.py

Load a MIDI file, see its tracks, assign them to the four Game Boy channels, and
watch how many notes each merge would drop before you commit to a conversion.

This is a *front-end*, not a second converter. Every piece of MIDI interpretation
comes from midi_to_gbs.py sitting next to it (parse_midi_track, auto_assign_channels,
get_bpm), so what you see here and what a conversion produces cannot drift apart.
Its real output is the midi_to_gbs.py command line, which keeps _regen_gbs.py the
authoritative way to rebuild every song.

Deliberately standalone: no decomp checkout, no configured directories, no project
awareness. Open a .mid and go.

    pip install -r requirements.txt
    python gbs_studio.py [file.mid]
"""

import sys
import os
import shlex
import subprocess
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

try:
    import mido
except ImportError:
    sys.exit("mido is required:  pip install -r requirements.txt")

try:
    from PySide6.QtCore import Qt, QRectF, Signal, QTimer, QSettings
    from PySide6.QtGui import (QColor, QPainter, QBrush, QPen, QFont, QTransform,
                           QFontDatabase)
    from PySide6.QtWidgets import (
        QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout,
        QTableWidget, QTableWidgetItem, QGraphicsView, QGraphicsScene,
        QLabel, QPushButton, QFileDialog, QComboBox, QSplitter,
        QHeaderView, QPlainTextEdit, QAbstractItemView,
        QDialog, QFormLayout, QSpinBox, QLineEdit, QDialogButtonBox, QCheckBox,
    )
except ImportError:
    sys.exit("PySide6 is required:  pip install -r requirements.txt")

import midi_to_gbs as conv

try:
    import numpy as np
    import sounddevice as sd
    import gbs_synth
    AUDIO_OK = True
    AUDIO_ERR = ""
except Exception as _exc:            # keep the tool usable with no audio stack
    AUDIO_OK = False
    AUDIO_ERR = str(_exc)


# ── channel model ────────────────────────────────────────────────────────────
# Ch1/Ch2 are the square channels, Ch3 the wave channel, Ch4 noise. Ch4 is the only
# one midi_to_gbs merges by design (percussion); the others merge too, but every
# overlap there costs a note, which is what OVERLAP below exists to surface.
CHANNELS = [
    ("Ch1", "Square 1", "#e5534b"),
    ("Ch2", "Square 2", "#d29922"),
    ("Ch3", "Wave",     "#3fb950"),
    ("Ch4", "Noise",    "#8957e5"),
]
UNASSIGNED = "-"


def merge_channel(note_lists, unit, priority=False):
    """
    Fit these tracks onto one monophonic GB channel.

    Both policies are imported from midi_to_gbs rather than reimplemented, so the
    counts shown here and the audio you hear are produced by the same code that
    writes the .s file.

      priority=False  first-come: earliest note wins, order breaks only exact ties
      priority=True   --priority-merge: list order is a ranking

    Returns (kept, dropped, trimmed).
    """
    if priority:
        return conv.resolve_priority(note_lists, unit)
    return conv.merge_first_come(note_lists, unit)


class TrackTable(QTableWidget):
    """
    Track list whose row selection can be turned off again.

    Qt's SingleSelection has no way to deselect: clicking the selected row keeps it
    selected, and clicking past the last row does nothing. Since selection here only
    drives a highlight on the roll, you need to be able to clear it - so clicking the
    selected row toggles it off, clicking empty space clears, and so does Escape.
    """

    def mousePressEvent(self, event):
        index = self.indexAt(event.position().toPoint())
        if not index.isValid():
            self.clearSelection()
            return
        if index.row() in {i.row() for i in self.selectedIndexes()}:
            self.clearSelection()
            return
        super().mousePressEvent(event)

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Escape:
            self.clearSelection()
            return
        super().keyPressEvent(event)


class PianoRoll(QGraphicsView):
    """
    Notes over time. Colour follows channel assignment; unassigned tracks are grey.

    Only the time axis zooms; every octave in the song stays visible. That is done by
    choosing the note height in scene units at draw time and leaving the vertical
    transform at 1.0, so nothing about the view can alter the pitch axis.
    """

    # Emitted with a scene x when the roll is clicked (not dragged).
    seekRequested = Signal(float)

    PX_PER_TICK = 0.06
    MIN_SCALE, MAX_SCALE = 0.05, 200.0
    V_MARGIN = 10               # scene units left above and below the notes

    def __init__(self):
        super().__init__()
        self.setScene(QGraphicsScene(self))
        self.setRenderHint(QPainter.Antialiasing, False)
        self.setDragMode(QGraphicsView.ScrollHandDrag)
        self.setBackgroundBrush(QColor("#0d1117"))
        self.setTransformationAnchor(QGraphicsView.AnchorUnderMouse)
        # Both scrollbars off. A horizontal bar that comes and goes changes the
        # viewport height, and note height is derived from it - so the notes would
        # visibly resize the moment you zoomed in far enough to need scrolling.
        # With no bars the height is constant and the notes are as tall as they can
        # be; scroll with the wheel or by dragging, and press F to reorient.
        self.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self._sx = 1.0
        self._playhead = None       # recreated after every scene.clear()
        self._last = None           # last render_tracks args, for redraw on resize
        self._press_pos = None      # to tell a seek click from a pan drag

    # -- zoom (time axis only) ----------------------------------------------
    # The vertical transform is always 1.0. Note height is chosen in SCENE units when
    # drawing, so the pitch axis cannot be touched by the view transform. Deriving it
    # from viewport height instead creates a feedback loop: a scrollbar appearing, or
    # any widget added inside the view, changes that height and visibly squashes the
    # notes. Zoom affects x only.
    def _apply(self):
        self.setTransform(QTransform().scale(self._sx, 1.0))

    def zoom(self, factor):
        self._sx = max(self.MIN_SCALE, min(self.MAX_SCALE, self._sx * factor))
        self._apply()

    def reset_zoom(self):
        self._sx = 1.0
        self._apply()

    def fit(self):
        """Show the whole song end to end."""
        rect = self.scene().itemsBoundingRect()
        if rect.isEmpty() or rect.width() <= 0:
            return
        self._sx = max(self.MIN_SCALE,
                       min(self.MAX_SCALE,
                           (self.viewport().width() - 12) / rect.width()))
        self._apply()
        self.centerOn(rect.center())

    def resizeEvent(self, event):
        super().resizeEvent(event)
        # Note height is baked into the scene, so a taller window needs a redraw
        # rather than just a new transform.
        if self._last:
            self.render_tracks(*self._last)
        self._apply()

    # -- input --------------------------------------------------------------
    def wheelEvent(self, event):
        mods = event.modifiers()
        dy = event.angleDelta().y()
        if dy == 0:
            super().wheelEvent(event)
            return

        if mods & Qt.ControlModifier:
            self.zoom(1.15 if dy > 0 else 1 / 1.15)
        else:
            bar = self.horizontalScrollBar()
            bar.setValue(bar.value() - dy)

    def mousePressEvent(self, event):
        self._press_pos = event.position().toPoint()
        super().mousePressEvent(event)

    def mouseReleaseEvent(self, event):
        super().mouseReleaseEvent(event)
        # ScrollHandDrag owns the left button for panning, so a seek is only a click
        # that did not move: anything past a few pixels was a drag and is left alone.
        if self._press_pos is not None and event.button() == Qt.LeftButton:
            moved = (event.position().toPoint() - self._press_pos).manhattanLength()
            if moved <= 4:
                x = self.mapToScene(event.position().toPoint()).x()
                self.seekRequested.emit(max(0.0, x))
        self._press_pos = None

    def keyPressEvent(self, event):
        key, mods = event.key(), event.modifiers()
        if mods & Qt.ControlModifier and key in (Qt.Key_Plus, Qt.Key_Equal):
            self.zoom(1.25)
        elif mods & Qt.ControlModifier and key == Qt.Key_Minus:
            self.zoom(1 / 1.25)
        elif mods & Qt.ControlModifier and key == Qt.Key_0:
            self.reset_zoom()
        elif key == Qt.Key_F:
            self.fit()
        else:
            super().keyPressEvent(event)

    # -- playhead -----------------------------------------------------------
    def set_playhead(self, scene_x, follow=True):
        """
        Draw the playback position at scene_x (song coordinates, not pixels), so it
        tracks the notes through any zoom level rather than sitting over the window.
        """
        rect = self.scene().itemsBoundingRect()
        if rect.isEmpty():
            return
        if self._playhead is None:
            pen = QPen(QColor("#f0f6fc"))
            pen.setCosmetic(True)        # stays 2px wide however far you zoom in
            pen.setWidth(2)
            self._playhead = self.scene().addLine(0, 0, 0, 1, pen)
            self._playhead.setZValue(1000)
        self._playhead.setLine(scene_x, rect.top(), scene_x, rect.bottom())
        self._playhead.setVisible(True)
        if follow:
            self.ensureVisible(
                QRectF(scene_x - 1, rect.top(), 2, rect.height()), 80, 0)

    def hide_playhead(self):
        if self._playhead is not None:
            self._playhead.setVisible(False)

    def time_to_scene_x(self, seconds, sec_per_tick):
        return (seconds / sec_per_tick) * self.PX_PER_TICK if sec_per_tick else 0.0

    def scene_x_to_time(self, scene_x, sec_per_tick):
        return (scene_x / self.PX_PER_TICK) * sec_per_tick if sec_per_tick else 0.0

    # -- drawing ------------------------------------------------------------
    def render_tracks(self, tracks, assignment, dropped_by_channel,
                      selected=None, muted=None):
        self._last = (tracks, assignment, dropped_by_channel, selected, muted)

        scene = self.scene()
        # Re-rendering rebuilds the scene, so hold the scroll position or selecting
        # a row would jump you back to the start of the song.
        keep_scroll = self.horizontalScrollBar().value()
        scene.clear()
        self._playhead = None       # destroyed along with everything else
        if not tracks:
            return

        colours = {name: col for name, _, col in CHANNELS}
        muted = muted or set()
        dropped_keys = set()
        for notes in dropped_by_channel.values():
            for n in notes:
                dropped_keys.add((n[0], n[2]))

        pitches = [n[2] for t in tracks for n in t["notes"]]
        if not pitches:
            return
        lo, hi = min(pitches), max(pitches)

        # Row height in scene units, sized so the song's full pitch range fills the
        # viewport exactly once. Because it lives in the scene rather than in the
        # transform, zooming can never change it.
        span = (hi - lo) + 1
        pitch_h = max(1.0, (self.viewport().height() - self.V_MARGIN) / span)

        # Octave guides, so vertical position reads as pitch rather than as offset.
        max_tick = max((n[0] + n[1]) for t in tracks for n in t["notes"])
        guide = QPen(QColor("#21262d"))
        guide.setCosmetic(True)
        for pitch in range(lo - (lo % 12), hi + 12, 12):
            if lo <= pitch <= hi:
                y = (hi - pitch) * pitch_h
                scene.addLine(0, y, max_tick * self.PX_PER_TICK, y, guide)

        for t in tracks:
            ch = assignment.get(t["index"], UNASSIGNED)
            base = colours.get(ch, "#484f58")
            for start, dur, pitch, vel in t["notes"]:
                x = start * self.PX_PER_TICK
                w = max(1.0, dur * self.PX_PER_TICK)
                y = (hi - pitch) * pitch_h
                # A dropped note is the thing you most need to see, so it overrides
                # the channel colour rather than blending with it.
                is_dropped = ch != UNASSIGNED and (start, pitch) in dropped_keys
                is_muted = t["index"] in muted
                dimmed = selected is not None and t["index"] != selected

                colour = QColor("#ff0000") if is_dropped else QColor(base)
                if is_muted:
                    # Muted tracks stay on screen so the shape of the song is intact,
                    # but faint enough to read as "not in what you are hearing".
                    colour.setAlpha(22)
                elif dimmed:
                    # Fade the rest rather than hiding it, so the selected track is
                    # still readable in the context of what surrounds it.
                    colour.setAlpha(55)

                pen = QPen(Qt.NoPen)
                if not is_muted and (
                        (is_dropped and not dimmed)
                        or (selected is not None and t["index"] == selected)):
                    pen = QPen(QColor("#ffffff"))
                    pen.setCosmetic(True)

                scene.addRect(QRectF(x, y, w, max(1.0, pitch_h - 0.5)),
                              pen, QBrush(colour))

        scene.setSceneRect(scene.itemsBoundingRect())
        self.horizontalScrollBar().setValue(keep_scroll)


class ExportOptions(QDialog):
    """
    The midi_to_gbs.py flags that are not derivable from the channel assignment.

    Only tone-shaping options live here; --ch1..--ch4, --note-unit and --name are
    already determined by what you set up in the main window, so asking again would
    just be a chance to contradict yourself.
    """

    def __init__(self, parent, default_name, note_unit, tone, name_visible=True):
        super().__init__(parent)
        self.setWindowTitle("Export options")
        form = QFormLayout(self)

        self.name = QLineEdit(default_name)
        if name_visible:
            form.addRow("Symbol name (--name)", self.name)

        info = QLabel(f"Note unit is {note_unit} ticks, taken from the file's TPB.")
        info.setStyleSheet("color:#8b949e")
        form.addRow("", info)

        def spin(lo, hi, val, tip=""):
            sb = QSpinBox()
            sb.setRange(lo, hi)
            sb.setValue(val)
            if tip:
                sb.setToolTip(tip)
            return sb

        self.duty1 = spin(0, 3, tone["duty1"], "0=12.5%  1=25%  2=50%  3=75%")
        self.duty2 = spin(0, 3, tone["duty2"],
                          "0=12.5%  1=25%  2=50%  3=75%  (3 is hollow/nasal)")
        self.vibrato = spin(0, 15, tone["vibrato"],
                            "Vibrato depth for both square channels")
        self.fade = spin(0, 15, tone["fade"],
                         "Squares: volume envelope (1-7 decay, 9-15 grow, 0 hold).\n"
                         "Ch3: selects one of the 15 wave tables instead.")
        self.ch1_shift = spin(-48, 48, tone["ch1_shift"],
                              "Semitones; use multiples of 12 for octaves")
        self.ch2_shift = spin(-48, 48, tone["ch2_shift"],
                              "Semitones; use multiples of 12 for octaves")
        self.ch3_shift = spin(-48, 48, tone["ch3_shift"],
                              "Semitones; use multiples of 12 for octaves")
        self.ch2_vol = spin(-15, 15, tone["ch2_vol"],
                            "Volume offset added to every Ch2 envelope")

        form.addRow("Ch1 duty (--duty1)", self.duty1)
        form.addRow("Ch2 duty (--duty2)", self.duty2)
        form.addRow("Vibrato (--vibrato-extent)", self.vibrato)
        form.addRow("Fade (--fade)", self.fade)
        form.addRow("Ch1 shift (--ch1-shift)", self.ch1_shift)
        form.addRow("Ch2 shift (--ch2-shift)", self.ch2_shift)
        form.addRow("Ch3 shift (--ch3-shift)", self.ch3_shift)
        form.addRow("Ch2 volume (--ch2-vol)", self.ch2_vol)

        buttons = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
        buttons.accepted.connect(self.accept)
        buttons.rejected.connect(self.reject)
        form.addRow(buttons)

    def values(self):
        return {"duty1": self.duty1.value(), "duty2": self.duty2.value(),
                "vibrato": self.vibrato.value(), "fade": self.fade.value(),
                "ch1_shift": self.ch1_shift.value(),
                "ch2_shift": self.ch2_shift.value(),
                "ch3_shift": self.ch3_shift.value(),
                "ch2_vol": self.ch2_vol.value()}

    def flags(self):
        """Only non-default values, so the command line stays readable."""
        defaults = {"duty1": 2, "duty2": 2, "vibrato": 1, "fade": 3,
                    "ch1_shift": 0, "ch2_shift": 0, "ch3_shift": 0, "ch2_vol": 0}
        names = {"duty1": "--duty1", "duty2": "--duty2",
                 "vibrato": "--vibrato-extent", "fade": "--fade",
                 "ch1_shift": "--ch1-shift", "ch2_shift": "--ch2-shift",
                 "ch3_shift": "--ch3-shift", "ch2_vol": "--ch2-vol"}
        out = []
        for key, value in self.values().items():
            if value != defaults[key]:
                out += [names[key], str(value)]
        return out


class Studio(QMainWindow):
    def __init__(self, path=None):
        super().__init__()
        self.setWindowTitle("GBS Studio")
        self.resize(1200, 760)

        self.midi = None
        self.midi_path = None
        self.tracks = []            # [{index, notes, program, avg_pitch, lo, hi}]
        self.assignment = {}        # track index -> "Ch1".."Ch4" | "-"
        self._needs_fit = False     # fit the view once per newly loaded file
        self._selected_track = None # table row -> highlighted notes on the roll
        self._dropped = {}          # cached so selection can re-render cheaply
        self._play_started = None   # monotonic clock captured at sd.play()
        self._play_length = 0.0
        self._sec_per_tick = 0.0
        self._audio = None          # cached render; cleared whenever settings change
        # Preview-only mute. Deliberately does NOT affect the drop counts or the
        # exported .s - those describe the conversion, which does not care what
        # you happen to be auditioning.
        self.enabled = {}           # track index -> bool

        # midi_to_gbs tone options, shared by the preview and the export so what you
        # hear is what gets written. Defaults match the converter's own argparse.
        self.tone = {"duty1": 2, "duty2": 2, "vibrato": 1, "fade": 3,
                     "ch1_shift": 0, "ch2_shift": 0, "ch3_shift": 0, "ch2_vol": 0}

        # Two independent remembered folders. MIDIs are usually read from a decomp
        # or a scratch folder while .s files are written somewhere else entirely, so
        # sharing one "last directory" would send you to the wrong place every time.
        self.settings = QSettings("mid2gbs", "GBS Studio")
        self.priority_merge = False # --priority-merge; A/B it against first-come

        root = QWidget()
        self.setCentralWidget(root)
        outer = QVBoxLayout(root)

        bar = QHBoxLayout()
        self.open_btn = QPushButton("Open MIDI...")
        self.open_btn.clicked.connect(self.pick_file)
        self.auto_btn = QPushButton("Auto-assign")
        self.auto_btn.clicked.connect(self.auto_assign)
        self.auto_btn.setEnabled(False)
        self.play_btn = QPushButton("Play GBS preview")
        self.play_btn.clicked.connect(self.play)
        self.play_btn.setEnabled(False)
        self.stop_btn = QPushButton("Stop")
        self.stop_btn.clicked.connect(self.stop)
        self.stop_btn.setEnabled(False)
        self.priority_chk = QCheckBox("Priority merge")
        self.priority_chk.setToolTip(
            "Off: earliest note wins (order only breaks exact ties).\n"
            "On:  channel track order is a ranking - the first-listed track\n"
            "     keeps its notes even where a later one started sooner.\n"
            "Toggle while playing to compare the two by ear.")
        self.priority_chk.toggled.connect(self.set_priority_merge)
        self.priority_chk.setEnabled(False)
        self.tone_btn = QPushButton("Tone...")
        self.tone_btn.setToolTip("Duty, vibrato, fade and pitch shifts.\nApplies to both the preview and the export.")
        self.tone_btn.clicked.connect(self.edit_tone)
        self.tone_btn.setEnabled(False)
        self.solo_btn = QPushButton("Solo")
        self.solo_btn.setToolTip("Preview only the selected track")
        self.solo_btn.clicked.connect(self.solo_selected)
        self.solo_btn.setEnabled(False)
        self.unmute_btn = QPushButton("Preview all")
        self.unmute_btn.setToolTip("Re-enable every track for preview")
        self.unmute_btn.clicked.connect(self.unmute_all)
        self.unmute_btn.setEnabled(False)
        self.export_btn = QPushButton("Export .s...")
        self.export_btn.clicked.connect(self.export)
        self.export_btn.setEnabled(False)
        self.file_lbl = QLabel("No file loaded")
        self.file_lbl.setStyleSheet("color:#8b949e")
        bar.addWidget(self.open_btn)
        bar.addWidget(self.auto_btn)
        bar.addWidget(self.play_btn)
        bar.addWidget(self.stop_btn)
        bar.addWidget(self.priority_chk)
        bar.addWidget(self.tone_btn)
        bar.addWidget(self.solo_btn)
        bar.addWidget(self.unmute_btn)
        bar.addWidget(self.export_btn)
        bar.addWidget(self.file_lbl, 1)
        outer.addLayout(bar)

        split = QSplitter(Qt.Vertical)
        outer.addWidget(split, 1)

        self.table = TrackTable(0, 8)
        self.table.setHorizontalHeaderLabels(
            ["Track", "Name", "Notes", "Prog", "Range", "Avg pitch",
             "Channel", "Preview"])
        self.table.verticalHeader().setVisible(False)
        self.table.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.table.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.table.setSelectionMode(QAbstractItemView.SingleSelection)
        self.table.itemSelectionChanged.connect(self.on_row_selected)
        self.table.horizontalHeader().setSectionResizeMode(1, QHeaderView.Stretch)
        split.addWidget(self.table)

        roll_box = QWidget()
        roll_lay = QVBoxLayout(roll_box)
        roll_lay.setContentsMargins(0, 0, 0, 0)
        roll_lay.setSpacing(2)
        self.roll = PianoRoll()
        self.roll.seekRequested.connect(self.seek_to)
        roll_lay.addWidget(self.roll, 1)

        zoom_bar = QHBoxLayout()
        for label, tip, fn in (
            ("Zoom out", "Show more of the song (Ctrl+wheel, Ctrl+-)",
             lambda: self.roll.zoom(1 / 1.25)),
            ("Zoom in",  "Show a smaller section (Ctrl+wheel, Ctrl++)",
             lambda: self.roll.zoom(1.25)),
            ("Fit",     "Fit the whole song in view (F)", lambda: self.roll.fit()),
            ("Reset",   "Back to 1:1 (Ctrl+0)", lambda: self.roll.reset_zoom()),
        ):
            b = QPushButton(label)
            b.setToolTip(tip)
            b.clicked.connect(fn)
            zoom_bar.addWidget(b)

        hint = QLabel("wheel: move along the song   ctrl+wheel: zoom   drag: pan   "
                      "F: fit whole song   click the roll to seek")
        hint.setStyleSheet("color:#8b949e")
        zoom_bar.addWidget(hint, 1)
        roll_lay.addLayout(zoom_bar)

        split.addWidget(roll_box)

        self.status = QPlainTextEdit()
        self.status.setReadOnly(True)
        self.status.setMaximumHeight(150)
        # Ask Qt for the platform's fixed-width font rather than naming a family.
        # "monospace" is not a real family on macOS, so Qt falls back to scanning
        # every installed font for it and warns about the cost.
        self.status.setFont(QFontDatabase.systemFont(QFontDatabase.FixedFont))
        self.status.setStyleSheet("background:#0d1117;color:#c9d1d9")
        split.addWidget(self.status)
        split.setSizes([220, 380, 150])

        # ~30 fps is smooth for a playhead and costs nothing: the timer only runs
        # while something is actually playing.
        self._play_timer = QTimer(self)
        self._play_timer.setInterval(33)
        self._play_timer.timeout.connect(self._tick_playhead)

        if path:
            self.load(path)

    # ── remembered folders ───────────────────────────────────────────────────
    def _recall_dir(self, key):
        """Last folder used for `key`, or the cwd if it has gone away."""
        path = self.settings.value(f"dirs/{key}", "", type=str)
        return path if path and os.path.isdir(path) else ""

    def _remember_dir(self, key, path):
        folder = os.path.dirname(os.path.abspath(path))
        if os.path.isdir(folder):
            self.settings.setValue(f"dirs/{key}", folder)

    # ── loading ──────────────────────────────────────────────────────────────
    def pick_file(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "Open MIDI", self._recall_dir("open"),
            "MIDI files (*.mid *.midi);;All files (*)")
        if path:
            self.load(path)

    def load(self, path):
        try:
            self.midi = mido.MidiFile(path)
        except Exception as exc:
            self.log(f"Could not read {os.path.basename(path)}: {exc}")
            return

        self.midi_path = path
        self._remember_dir("open", path)
        self.tracks = []

        # parse_midi_track is imported rather than reimplemented so the note data here
        # is byte-for-byte what a conversion will act on.
        for i, track in enumerate(self.midi.tracks):
            notes, _ = conv.parse_midi_track(track, self.midi.ticks_per_beat)
            if not notes:
                continue
            pitches = [n[2] for n in notes]
            self.tracks.append({
                "index": i,
                "name": (track.name or "").strip(),
                "notes": notes,
                "program": conv.get_track_program(track),
                "avg_pitch": sum(pitches) / len(pitches),
                "lo": min(pitches),
                "hi": max(pitches),
            })

        self.assignment = {t["index"]: UNASSIGNED for t in self.tracks}
        self.enabled = {t["index"]: True for t in self.tracks}
        self._needs_fit = True
        self._selected_track = None
        self.auto_btn.setEnabled(True)
        self.play_btn.setEnabled(AUDIO_OK)
        self.export_btn.setEnabled(True)
        self.priority_chk.setEnabled(True)
        self.tone_btn.setEnabled(True)
        self.solo_btn.setEnabled(True)
        self.unmute_btn.setEnabled(True)
        if not AUDIO_OK:
            self.log(f"Audio preview unavailable ({AUDIO_ERR}).")

        bpm = conv.get_bpm(self.midi)
        self.file_lbl.setText(
            f"{os.path.basename(path)}   -   {len(self.tracks)} tracks with notes, "
            f"TPB {self.midi.ticks_per_beat}, {bpm:.1f} BPM")
        self.log(f"Loaded {os.path.basename(path)}")
        if self.midi.ticks_per_beat != 48:
            # midi_to_gbs defaults --note-unit 12 on the assumption TPB is 48.
            self.log(f"  NOTE: TPB is {self.midi.ticks_per_beat}, not the 48 that "
                     f"--note-unit 12 assumes. Pass --note-unit "
                     f"{self.midi.ticks_per_beat // 4} instead.")

        self.auto_assign()

    def auto_assign(self):
        if not self.midi:
            return
        ch1, ch2, ch3, noise = conv.auto_assign_channels(self.midi)
        for t in self.tracks:
            self.assignment[t["index"]] = UNASSIGNED
        for idx, ch in ((ch1, "Ch1"), (ch2, "Ch2"), (ch3, "Ch3")):
            if idx is not None:
                self.assignment[idx] = ch
        for idx in noise:
            self.assignment[idx] = "Ch4"
        self.log("Auto-assigned by average pitch. midi2agb writes every track as "
                 "program 0, so noise detection usually needs fixing by hand.")
        self.refresh()

    def note_unit(self):
        """MIDI ticks per GBS unit - what midi_to_gbs --note-unit defaults to."""
        tpb = self.midi.ticks_per_beat
        return 12 if tpb == 48 else max(1, tpb // 4)

    def set_priority_merge(self, on):
        self.priority_merge = bool(on)
        self.recompute()
        self.log("Merge policy: "
                 + ("priority - channel track order ranks them"
                    if on else "first-come - earliest note wins"))

    def edit_tone(self):
        """Adjust the tone options and hear them: the preview honours them too."""
        dlg = ExportOptions(self, self.default_symbol(), self.note_unit(),
                            self.tone, name_visible=False)
        dlg.setWindowTitle("Tone settings")
        if dlg.exec() == QDialog.Accepted:
            self.tone = dlg.values()
            self.recompute()
            self.log("Tone updated - press Play to hear it. "
                     + " ".join(dlg.flags() or ["(all defaults)"]))

    def muted_tracks(self):
        return {i for i, on in self.enabled.items() if not on}

    def set_enabled(self, track_index, state):
        self.enabled[track_index] = bool(state)
        self.recompute()

    def solo_selected(self):
        """Preview only the highlighted track."""
        if self._selected_track is None:
            self.log("Select a track row first, then Solo.")
            return
        for idx in self.enabled:
            self.enabled[idx] = (idx == self._selected_track)
        self.refresh()

    def unmute_all(self):
        for idx in self.enabled:
            self.enabled[idx] = True
        self.refresh()

    def on_row_selected(self):
        """Highlight the selected track's notes on the roll and fade the rest."""
        rows = {i.row() for i in self.table.selectedIndexes()}
        if len(rows) == 1:
            item = self.table.item(rows.pop(), 0)
            self._selected_track = int(item.text()) if item else None
        else:
            self._selected_track = None
        # Only the drawing changes, so reuse the cached overlap results instead of
        # recomputing every channel merge on a click.
        self.roll.render_tracks(self.tracks, self.assignment, self._dropped,
                                self._selected_track, self.muted_tracks())

    def paint_row(self, row, channel):
        """
        Tint a track's row with its channel colour.

        The channel colours are saturated enough to read as small note rectangles on
        a dark roll, which makes them far too strong as a full row background - so
        they go on at low alpha here. The track-index cell keeps the colour at full
        strength as a solid cue that survives any theme.
        """
        colours = {name: col for name, _, col in CHANNELS}
        hexcol = colours.get(channel)

        for col in range(6):
            item = self.table.item(row, col)
            if item is None:
                continue
            if hexcol:
                tint = QColor(hexcol)
                tint.setAlpha(55)
                item.setBackground(QBrush(tint))
            else:
                item.setBackground(QBrush(Qt.NoBrush))

        idx_item = self.table.item(row, 0)
        if idx_item is not None:
            idx_item.setForeground(
                QBrush(QColor(hexcol)) if hexcol else QBrush(Qt.NoBrush))
            font = idx_item.font()
            font.setBold(bool(hexcol))
            idx_item.setFont(font)

        box = self.table.cellWidget(row, 6)
        if box is not None:
            box.setStyleSheet(
                f"QComboBox {{ border: 1px solid {hexcol}; color: {hexcol}; }}"
                if hexcol else "")

    # ── view ─────────────────────────────────────────────────────────────────
    def refresh(self):
        self.table.setRowCount(len(self.tracks))
        for row, t in enumerate(self.tracks):
            vals = [
                str(t["index"]),
                t["name"] or "(unnamed)",
                str(len(t["notes"])),
                str(t["program"]) if t["program"] >= 0 else "-",
                f'{t["lo"]}-{t["hi"]}',
                f'{t["avg_pitch"]:.1f}',
            ]
            for col, v in enumerate(vals):
                self.table.setItem(row, col, QTableWidgetItem(v))

            box = QComboBox()
            box.addItem(UNASSIGNED)
            for name, desc, _ in CHANNELS:
                box.addItem(f"{name} ({desc})", name)
            current = self.assignment.get(t["index"], UNASSIGNED)
            box.setCurrentIndex(
                0 if current == UNASSIGNED
                else [c[0] for c in CHANNELS].index(current) + 1)
            box.currentIndexChanged.connect(
                lambda _, ti=t["index"], b=box, r=row: self.set_channel(ti, b, r))
            self.table.setCellWidget(row, 6, box)

            chk = QCheckBox()
            chk.setChecked(self.enabled.get(t["index"], True))
            chk.setToolTip("Include this track in the audio preview.\n"
                           "Does not affect the exported .s.")
            chk.stateChanged.connect(
                lambda _st, ti=t["index"]: self.set_enabled(ti, _st))
            holder = QWidget()
            hl = QHBoxLayout(holder)
            hl.setContentsMargins(0, 0, 0, 0)
            hl.setAlignment(Qt.AlignCenter)
            hl.addWidget(chk)
            self.table.setCellWidget(row, 7, holder)

            self.paint_row(row, None if current == UNASSIGNED else current)

        self.table.resizeColumnsToContents()
        self.table.horizontalHeader().setSectionResizeMode(1, QHeaderView.Stretch)
        self.recompute()

    def set_channel(self, track_index, box, row=None):
        data = box.currentData()
        self.assignment[track_index] = data if data else UNASSIGNED
        # Repaint just this row: a full refresh() would rebuild every combo box and
        # re-fire currentIndexChanged, recursing back into here.
        if row is not None:
            self.paint_row(row, data if data else None)
        self.recompute()

    def recompute(self):
        """Recount dropped notes per channel and redraw. Runs on every assignment."""
        by_channel = {}
        dropped_by_channel = {}
        trimmed_by_channel = {}
        for name, _, _ in CHANNELS:
            members = [t for t in self.tracks
                       if self.assignment.get(t["index"]) == name]
            by_channel[name] = members
            if members:
                _kept, dropped, trimmed = merge_channel(
                    [m["notes"] for m in members], self.note_unit(),
                    self.priority_merge)
                dropped_by_channel[name] = dropped
                trimmed_by_channel[name] = trimmed
            else:
                dropped_by_channel[name] = []
                trimmed_by_channel[name] = []

        lines = []
        for name, desc, _ in CHANNELS:
            members = by_channel[name]
            if not members:
                lines.append(f"{name} ({desc}): -")
                continue
            idxs = ",".join(str(m["index"]) for m in members)
            total = sum(len(m["notes"]) for m in members)
            lost = len(dropped_by_channel[name])
            cut = len(trimmed_by_channel[name])
            note = f"{name} ({desc}): tracks {idxs}, {total} notes"
            if lost or cut:
                pct = 100.0 * lost / total if total else 0
                bits = []
                if lost:
                    bits.append(f"{lost} dropped ({pct:.1f}%)")
                if cut:
                    bits.append(f"{cut} shortened")
                note += f"   >>> {', '.join(bits)} - GB channels are monophonic"
            lines.append(note)

        muted = self.muted_tracks()
        if muted:
            lines.append("")
            lines.append(f"Preview muted: tracks {','.join(str(m) for m in sorted(muted))}"
                         "  (audio only - the export below is unaffected)")

        lines.append("")
        lines.append(self.command_line())
        self.status.setPlainText("\n".join(lines))
        self._dropped = dropped_by_channel
        self._audio = None          # assignment/mute/tone changed - re-render on next play
        self.roll.render_tracks(self.tracks, self.assignment, dropped_by_channel,
                                self._selected_track, self.muted_tracks())
        if self._needs_fit:
            self._needs_fit = False
            self.roll.fit()

    # ── audio preview ────────────────────────────────────────────────────────
    def channel_events(self):
        """
        Build per-channel note events in seconds, applying the same three transforms
        the converter does, so the preview contains the conversion's artefacts rather
        than an idealised version of the MIDI:

          * monophonic collapse - overlapping notes on a channel are dropped
          * duration quantisation to --note-unit
          * octave clamping to the GB's range (midi_note_to_gbs clamps to 1-8)
        """
        tpb = self.midi.ticks_per_beat
        bpm = conv.get_bpm(self.midi)
        sec_per_tick = 60.0 / (bpm * tpb)
        self._sec_per_tick = sec_per_tick
        unit = self.note_unit()

        events = {}
        for name, _desc, _col in CHANNELS:
            members = [t for t in self.tracks
                       if self.assignment.get(t["index"]) == name
                       and self.enabled.get(t["index"], True)]
            if not members:
                continue

            kept, _dropped, _trimmed = merge_channel(
                [m["notes"] for m in members], unit, self.priority_merge)

            # Shifts and the Ch2 volume offset change the notes themselves, so they
            # belong here rather than in the synth; duty/vibrato/fade are timbre and
            # are passed to the renderer instead.
            shift = self.tone.get(f"{name.lower()}_shift", 0)
            vol_adjust = self.tone.get("ch2_vol", 0) if name == "Ch2" else 0

            out = []
            for start, q_ticks, pitch, vel in kept:
                shifted = max(0, min(127, pitch + shift))
                gbs_octave, _pname = conv.midi_note_to_gbs(shifted)
                played = (gbs_octave + 2) * 12 + (shifted % 12)
                vol = max(1, min(15, conv.midi_vel_to_gbs_vol(vel) + vol_adjust))
                out.append((start * sec_per_tick,
                            q_ticks * sec_per_tick,
                            played,
                            vol))
            events[name] = out
        return events

    def play(self):
        self._start_playback(0.0)

    def seek_to(self, scene_x):
        """Jump to the clicked point on the roll and play from there."""
        if not self.midi:
            return
        if self._sec_per_tick <= 0:
            self.channel_events()          # populates _sec_per_tick
        secs = self.roll.scene_x_to_time(scene_x, self._sec_per_tick)
        self._start_playback(secs)

    def _start_playback(self, offset=0.0):
        if not (self.midi and AUDIO_OK):
            return
        if self._audio is None:
            events = self.channel_events()
            if not events:
                self.log("Nothing assigned to a channel yet.")
                return
            try:
                self._audio = gbs_synth.render(events, tone=self.tone)
            except Exception as exc:
                self.log(f"Render failed: {exc}")
                return

        audio = self._audio
        total = len(audio) / gbs_synth.SAMPLE_RATE
        offset = min(max(0.0, offset), max(0.0, total - 0.05))
        start = int(offset * gbs_synth.SAMPLE_RATE)

        try:
            sd.stop()
            sd.play(audio[start:], gbs_synth.SAMPLE_RATE)
        except Exception as exc:
            self.log(f"Playback failed: {exc}")
            return

        self.stop_btn.setEnabled(True)
        self._play_length = total
        # Offset the clock rather than the playhead, so _tick_playhead stays a plain
        # "elapsed since the start of the song" calculation.
        self._play_started = time.monotonic() - offset
        self._play_timer.start()
        self.roll.set_playhead(
            self.roll.time_to_scene_x(offset, self._sec_per_tick), follow=False)
        where = f" from {offset:.1f}s" if offset else ""
        self.log(f"Playing GBS preview{where} - {total:.1f}s total.")

    def stop(self):
        if AUDIO_OK:
            sd.stop()
        self._play_timer.stop()
        self._play_started = None
        self.roll.hide_playhead()
        self.stop_btn.setEnabled(False)

    def _tick_playhead(self):
        """Advance the playhead from a wall clock started at sd.play()."""
        if self._play_started is None:
            self._play_timer.stop()
            return
        elapsed = time.monotonic() - self._play_started
        if elapsed >= self._play_length:
            self.stop()
            return
        self.roll.set_playhead(
            self.roll.time_to_scene_x(elapsed, self._sec_per_tick))

    def default_symbol(self):
        stem = os.path.splitext(os.path.basename(self.midi_path or ""))[0]
        for prefix in ("mus_hg_gbs_", "mus_hg_"):
            if stem.startswith(prefix):
                stem = stem[len(prefix):]
                break
        return f"gbs_{stem}"

    def tone_flags(self):
        """Non-default tone options as midi_to_gbs flags."""
        defaults = {"duty1": 2, "duty2": 2, "vibrato": 1, "fade": 3,
                    "ch1_shift": 0, "ch2_shift": 0, "ch3_shift": 0, "ch2_vol": 0}
        names = {"duty1": "--duty1", "duty2": "--duty2",
                 "vibrato": "--vibrato-extent", "fade": "--fade",
                 "ch1_shift": "--ch1-shift", "ch2_shift": "--ch2-shift",
                 "ch3_shift": "--ch3-shift", "ch2_vol": "--ch2-vol"}
        out = []
        for key, value in self.tone.items():
            if value != defaults[key]:
                out += [names[key], str(value)]
        return out

    def build_argv(self, name=None, out_path=None, extra=None):
        """
        The midi_to_gbs.py argument list for the current assignment.

        Export runs exactly this, so the command shown in the status pane is the
        command that produced the file - paste it into _regen_gbs.py and you get the
        same .s back.
        """
        argv = [self.midi_path, "--name", name or self.default_symbol()]
        for ch, _desc, _col in CHANNELS:
            members = [t for t in self.tracks
                       if self.assignment.get(t["index"]) == ch]
            if members:
                argv += [f"--{ch.lower()}",
                         ",".join(str(m["index"]) for m in members)]
        unit = self.note_unit()
        if unit != 12:
            argv += ["--note-unit", str(unit)]
        if self.priority_merge:
            argv += ["--priority-merge"]
        argv += extra or []
        if out_path:
            argv += ["--out", out_path]
        return argv

    def command_line(self):
        if not self.midi_path:
            return ""
        argv = self.build_argv(extra=self.tone_flags())
        argv[0] = os.path.basename(argv[0])
        return "python3 midi_to_gbs.py " + " ".join(shlex.quote(a) for a in argv)

    # ── export ───────────────────────────────────────────────────────────────
    def export(self):
        if not self.midi:
            return
        assigned = [t for t in self.tracks
                    if self.assignment.get(t["index"], UNASSIGNED) != UNASSIGNED]
        if not assigned:
            self.log("Nothing assigned to a channel - nothing to export.")
            return

        dlg = ExportOptions(self, self.default_symbol(), self.note_unit(), self.tone)
        if dlg.exec() != QDialog.Accepted:
            return
        self.tone = dlg.values()      # keep preview and export in step

        symbol = dlg.name.text().strip() or self.default_symbol()
        out_path, _ = QFileDialog.getSaveFileName(
            self, "Save GBS assembly",
            os.path.join(self._recall_dir("save"), f"{symbol}.s"),
            "GBS assembly (*.s);;All files (*)")
        if not out_path:
            return
        self._remember_dir("save", out_path)

        argv = self.build_argv(symbol, out_path, dlg.flags())
        script = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                              "midi_to_gbs.py")

        # Run the converter as a subprocess rather than calling into it: it is an
        # argparse program that writes files and can sys.exit, and this keeps the
        # GUI and the CLI on one code path with no shared global state.
        try:
            result = subprocess.run([sys.executable, script] + argv,
                                    capture_output=True, text=True, timeout=120)
        except Exception as exc:
            self.log(f"Export failed to run: {exc}")
            return

        shown = "python3 midi_to_gbs.py " + " ".join(shlex.quote(a) for a in argv)
        if result.returncode != 0:
            self.log(f"Export FAILED (exit {result.returncode})")
            self.log(shown)
            if result.stderr.strip():
                self.log(result.stderr.strip())
            return

        size = os.path.getsize(out_path) if os.path.exists(out_path) else 0
        self.log(f"Wrote {out_path} ({size} bytes)")
        self.log(shown)
        if result.stderr.strip():
            self.log(result.stderr.strip())

    def log(self, text):
        self.status.appendPlainText(text)


def main():
    app = QApplication(sys.argv)
    app.setOrganizationName("mid2gbs")
    app.setApplicationName("GBS Studio")
    app.setStyle("Fusion")
    win = Studio(sys.argv[1] if len(sys.argv) > 1 else None)
    win.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
