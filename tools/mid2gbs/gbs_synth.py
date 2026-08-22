#!/usr/bin/env python3
"""
gbs_synth.py - render a Game Boy APU approximation of a GBS channel assignment.

This previews the *converted* result, not the source MIDI: the point is to hear what
the four GB channels will actually produce, including the artefacts the conversion
introduces (monophonic note dropping, duration quantisation, octave clamping).

Accuracy notes
--------------
The GB APU is four fully-specified generators, so this can get close to exact.

Modelled: square duty cycles, the GB volume envelope (note_type's fade), vibrato,
all 15 wave tables, and LFSR noise - so the midi_to_gbs tone options can be judged by
ear. Not modelled: frequency sweep, the hardware high-pass, and exact vibrato depth
(extent counts raw GB frequency units, whose size in cents varies per note).
"""

import numpy as np

SAMPLE_RATE = 44100

# Duty cycles for the two square channels, as the fraction of each period spent high.
DUTY_CYCLES = {0: 0.125, 1: 0.25, 2: 0.50, 3: 0.75}

# All 15 entries of sWaveTrackPatterns (src/data/gbs.h). Each is 32 4-bit samples
# packed two per byte. The third argument of the GBS `note_type` command selects one
# of these for the wave channel - which is why --fade retimbres Ch3 rather than
# fading it, the way it does on the square channels. Embedded rather than read from a
# decomp checkout so this stays standalone.
WAVE_PATTERN_BYTES = (
    (0x02, 0x46, 0x8A, 0xCE, 0xFF, 0xFE, 0xED, 0xDC, 0xCB, 0xA9, 0x87, 0x65, 0x44, 0x33, 0x22, 0x11),   # 0
    (0x02, 0x46, 0x8A, 0xCE, 0xEF, 0xFF, 0xFE, 0xEE, 0xDD, 0xCB, 0xA9, 0x87, 0x65, 0x43, 0x22, 0x11),   # 1
    (0x13, 0x69, 0xBD, 0xEE, 0xEE, 0xFF, 0xFF, 0xED, 0xDE, 0xFF, 0xFF, 0xEE, 0xEE, 0xDB, 0x96, 0x31),   # 2
    (0x02, 0x46, 0x8A, 0xCD, 0xEF, 0xFE, 0xDE, 0xFF, 0xEE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10),   # 3
    (0x01, 0x23, 0x45, 0x67, 0x8A, 0xCD, 0xEE, 0xF7, 0x7F, 0xEE, 0xDC, 0xA8, 0x76, 0x54, 0x32, 0x10),   # 4
    (0x00, 0x11, 0x22, 0x33, 0x44, 0x33, 0x22, 0x11, 0xFF, 0xEE, 0xCC, 0xAA, 0x88, 0xAA, 0xCC, 0xEE),   # 5
    (0x02, 0x46, 0x8A, 0xCE, 0xCB, 0xA9, 0x87, 0x65, 0xFF, 0xFE, 0xED, 0xDC, 0x44, 0x33, 0x22, 0x11),   # 6
    (0xC0, 0xA9, 0x87, 0xF5, 0xFF, 0xFE, 0xED, 0xDC, 0x44, 0x33, 0x22, 0xF1, 0x02, 0x46, 0x8A, 0xCE),   # 7
    (0x44, 0x33, 0x22, 0x1F, 0x00, 0x46, 0x8A, 0xCE, 0xF8, 0xFE, 0xED, 0xDC, 0xCB, 0xA9, 0x87, 0x65),   # 8
    (0x11, 0x00, 0x00, 0x08, 0x00, 0x13, 0x57, 0x9A, 0xB4, 0xBA, 0xA9, 0x98, 0x87, 0x65, 0x43, 0x21),   # 9
    (0x21, 0xE2, 0x33, 0x28, 0xE1, 0x22, 0xFF, 0xEA, 0x10, 0x14, 0xDC, 0x10, 0xE3, 0x41, 0x51, 0x73),   # 10
    (0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),   # 11
    (0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),   # 12
    (0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00),   # 13
    (0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00),   # 14
)


def _wave_table(index):
    """Unpack a wave pattern into 32 samples in -1..+1."""
    data = WAVE_PATTERN_BYTES[index % len(WAVE_PATTERN_BYTES)]
    vals = np.array([v for b in data for v in ((b >> 4) & 0xF, b & 0xF)],
                    dtype=np.float32)
    return (vals / 7.5) - 1.0


WAVE_TABLES = [_wave_table(i) for i in range(len(WAVE_PATTERN_BYTES))]

# The GB's own master volume is 3 bits per side, and HnS shifts it down two steps in
# GBSMain, so in-game GBS is quieter and coarser than hardware. Previews here are
# rendered at full scale; apply this if you want in-game loudness instead.
HNS_MASTER_SCALE = 5.0 / 7.0


def midi_to_freq(pitch):
    return 440.0 * (2.0 ** ((pitch - 69) / 12.0))


def _envelope(n, sr, attack=0.002, release=0.012):
    """Short attack/release so notes do not click. Not the GB's envelope unit."""
    env = np.ones(n, dtype=np.float32)
    a = min(int(attack * sr), n // 2)
    r = min(int(release * sr), n // 2)
    if a > 0:
        env[:a] = np.linspace(0.0, 1.0, a, dtype=np.float32)
    if r > 0:
        env[-r:] = np.linspace(1.0, 0.0, r, dtype=np.float32)
    return env


def _fade_envelope(n, sr, vol, fade):
    """
    The GB volume envelope, as selected by note_type's third argument.

    1-7 step the volume down, 9-15 step it up, 0 holds. Each step is `fade` * 1/64 s,
    counting in the hardware's 16 volume levels. Modelled as a level-stepped ramp
    rather than a smooth curve, which is what makes it audibly "chippy".
    """
    if not fade:
        return np.full(n, vol / 15.0, dtype=np.float32)

    rising = fade >= 8
    speed = (fade - 8) if rising else fade
    if speed == 0:
        return np.full(n, vol / 15.0, dtype=np.float32)

    step_samples = max(1, int((speed / 64.0) * sr))
    steps = np.arange(n, dtype=np.int32) // step_samples
    level = (vol + steps) if rising else (vol - steps)
    return np.clip(level, 0, 15).astype(np.float32) / 15.0


def _vibrato_factor(n, sr, extent, delay_frames=16, rate=4):
    """
    Pitch wobble matching the emitted `vibrato 16, extent, 4`.

    Depth is approximate: `extent` counts raw GB frequency units, whose size in cents
    depends on the note, so it is mapped to a small fixed interval here instead.
    """
    if not extent:
        return np.ones(n, dtype=np.float32)
    t = np.arange(n, dtype=np.float32) / sr
    delay_s = delay_frames / 60.0
    hz = 60.0 / (2.0 * max(1, rate))
    depth = 2.0 ** ((extent * 0.18) / 12.0) - 1.0
    wobble = np.sin(2 * np.pi * hz * np.maximum(0.0, t - delay_s))
    return (1.0 + depth * wobble * (t > delay_s)).astype(np.float32)


def render_square(freq, dur_s, duty, vol, fade=0, vibrato=0, sr=SAMPLE_RATE):
    n = max(1, int(dur_s * sr))
    t = np.arange(n, dtype=np.float32) / sr
    inst = freq * _vibrato_factor(n, sr, vibrato)
    phase = np.cumsum(inst) / sr          # integrate for a smoothly bending pitch
    wave = np.where((phase % 1.0) < DUTY_CYCLES.get(duty, 0.5), 1.0, -1.0)
    return (wave.astype(np.float32)
            * _fade_envelope(n, sr, vol, fade)
            * _envelope(n, sr))


def render_wave(freq, dur_s, vol, pattern=0, sr=SAMPLE_RATE):
    n = max(1, int(dur_s * sr))
    t = np.arange(n, dtype=np.float32) / sr
    table = WAVE_TABLES[pattern % len(WAVE_TABLES)]
    idx = ((t * freq * len(table)) % len(table)).astype(np.int32)
    # No envelope here: on the wave channel note_type's third argument picks the
    # table above rather than setting a fade.
    return table[idx] * (vol / 15.0) * _envelope(n, sr)


def render_noise(dur_s, vol, pitch=None, sr=SAMPLE_RATE):
    """
    15-bit LFSR, the same shape the GB uses. Pitch selects the shift rate so that
    higher 'notes' read as tighter percussion, which is how the converter uses Ch4.
    """
    n = max(1, int(dur_s * sr))
    rate = 2000.0 if pitch is None else float(np.clip(midi_to_freq(pitch) * 8, 500, 20000))
    step = max(1, int(sr / rate))

    reg = 0x7FFF
    count = (n // step) + 1
    bits = np.empty(count, dtype=np.float32)
    for i in range(count):
        b = ((reg ^ (reg >> 1)) & 1)
        reg = (reg >> 1) | (b << 14)
        bits[i] = 1.0 if (reg & 1) else -1.0

    out = np.repeat(bits, step)[:n]
    # Percussion decays fast; a flat gate would sound like static.
    decay = np.exp(-np.arange(n, dtype=np.float32) / (sr * 0.05))
    return out * (vol / 15.0) * decay


def render(channel_events, sr=SAMPLE_RATE, tone=None, master_scale=1.0):
    """
    channel_events: {"Ch1": [(start_s, dur_s, pitch, vol), ...], ...}
                    Ch4 events use pitch only to colour the noise.
    tone:           the midi_to_gbs knobs that change how it sounds -
                    duty1, duty2, vibrato, fade. Pitch shifts and the Ch2 volume
                    offset are applied when the events are built, since they change
                    the notes themselves rather than the timbre.
    Returns float32 mono in -1..1.
    """
    tone = tone or {}
    duty = {"Ch1": tone.get("duty1", 2), "Ch2": tone.get("duty2", 2)}
    fade = tone.get("fade", 3)
    vib = tone.get("vibrato", 1)

    total = 0.0
    for events in channel_events.values():
        for start, dur, _p, _v in events:
            total = max(total, start + dur)
    if total <= 0:
        return np.zeros(1, dtype=np.float32)

    buf = np.zeros(int(total * sr) + sr // 4, dtype=np.float32)

    for name, events in channel_events.items():
        for start, dur, pitch, vol in events:
            if name == "Ch4":
                seg = render_noise(dur, vol, pitch, sr)
            elif name == "Ch3":
                seg = render_wave(midi_to_freq(pitch), dur, vol, fade, sr)
            else:
                seg = render_square(midi_to_freq(pitch), dur, duty.get(name, 2),
                                    vol, fade, vib, sr)
            i = int(start * sr)
            end = min(i + len(seg), len(buf))
            if end > i:
                buf[i:end] += seg[:end - i]

    buf *= master_scale
    peak = float(np.max(np.abs(buf)))
    if peak > 1.0:
        buf /= peak            # four channels clip easily; normalise rather than clip
    return buf.astype(np.float32)
