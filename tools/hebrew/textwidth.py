#!/usr/bin/env python3
"""Pixel widths of Heart & Soul strings, modelled on the H&S window renderer.

Usage:
  textwidth.py [options] TEXT...           measure each TEXT (source form, as inside .string "...")
  textwidth.py [options] --stdin           one string per input line
  textwidth.py [--tree T] --fonts          per font: width table, widest/average Hebrew glyph, source
  textwidth.py --subst-table               the worst-case placeholder substitutions in use

Options:
  --tree DIR        tree whose src/fonts.c and charmap.txt are read
                    (default HNS_FONTS_TREE, which defaults to HNS_TREE)
  --charmap FILE    charmap to use instead of <tree>/charmap.txt
  --symtree DIR     tree searched for C strings named by "sym:" substitutions (battle prefixes)
                    (default HNS_TREE)
  --font NAME       FONT_NORMAL (default), FONT_NARROW, FONT_SMALL, ... or a number
  --x N             printer x (default 0); {SKIP}/{CLEAR_TO}/{SHIFT_RIGHT} are relative to it
  --fill max|avg    placeholders become N copies of the widest (default) or average Hebrew glyph
  --subst NAME=SPEC override a placeholder, e.g. --subst STR_VAR_1=W19 or --subst PLAYER='"GOLD"'
  --hebrew-widths auto|table|draft
                    auto (default): read Hebrew widths from fonts.c once they are there, else use
                    the drafts in data/font_drafts
  --json            machine-readable output

Model (src/text.c, the RTL window renderer):
  - advance = width table value of the active font; letterSpacing is ignored (src/text.c RenderText);
    {MIN_LETTER_SPACING n} makes every advance exactly n
  - {FONT_x}/{FONT n} switch the width table; {RESET_FONT} does nothing
  - {CLEAR n} adds n, {SKIP n} and {SHIFT_RIGHT n} set the pen to x+n, {CLEAR_TO n} to max(pen, x+n)
  - F9 xx uses widths[0x100|xx], {ESCAPE xx} draws glyph 0x100|xx, F8 xx is a keypad icon (8/16/24)
  - \\n starts the next row, \\l scrolls (same row, new line), \\p starts a new page; lines that end
    in \\l or \\p carry the 8 px down arrow (prompt=True)
  - a line's width is the furthest pen position reached on it, minus x
Placeholders ({PLAYER}, {STR_VAR_1}, {B_ATK_NAME_WITH_PREFIX}, ...) are expanded to worst cases
(WORST_CASE below) before measuring. SPEC grammar, parts joined with '+':
  Wn          n copies of the widest Hebrew glyph of the font active at that point
  "text"      literal source text
  sym:A|B     the widest of the C strings named A, B in --symtree (e.g. sText_FoePkmnPrefix)
  empty       nothing

Library:
  from textwidth import TextModel
  m = TextModel()                                  # defaults as above
  m.lines('Hello {PLAYER}!\\nBye$', 'FONT_NORMAL')  # -> [Line(page=1,row=1,width=..,end='n',...), ...]
  m.width('...'), m.byte_length('...'), m.encode('...'), m.decode(b'...')
"""
import argparse
import json
import math
import os
import re
import sys
from collections import namedtuple

import paths

FONTS_TREE = paths.FONTS_TREE
SYM_TREE = paths.TREE
EN_TREE = paths.UPSTREAM
DRAFT_DIR = paths.FONT_DRAFTS

FONT_IDS = {
    'FONT_SMALL': 0, 'FONT_NORMAL': 1, 'FONT_SHORT': 2, 'FONT_SHORT_COPY_1': 3, 'FONT_SHORT_COPY_2': 4,
    'FONT_SHORT_COPY_3': 5, 'FONT_BRAILLE': 6, 'FONT_NARROW': 7, 'FONT_SMALL_NARROW': 8, 'FONT_BOLD': 9,
    'FONT_NARROWER': 10, 'FONT_SMALL_NARROWER': 11, 'FONT_SHORT_NARROW': 12, 'FONT_SHORT_NARROWER': 13,
    'FONT_MALE': 1, 'FONT_FEMALE': 1,
}
FONT_NAMES = {v: k for k, v in FONT_IDS.items() if k not in ('FONT_MALE', 'FONT_FEMALE')}
# include/text.h:17-32 font ids -> src/fonts.c width tables (src/text.c:75-90 sGlyphWidthFuncs)
WIDTH_TABLES = {
    0: 'gFontSmallLatinGlyphWidths', 1: 'gFontNormalLatinGlyphWidths', 2: 'gFontShortLatinGlyphWidths',
    3: 'gFontShortLatinGlyphWidths', 4: 'gFontShortLatinGlyphWidths', 5: 'gFontShortLatinGlyphWidths',
    7: 'gFontNarrowLatinGlyphWidths', 8: 'gFontSmallNarrowLatinGlyphWidths',
    10: 'gFontNarrowerLatinGlyphWidths', 11: 'gFontSmallNarrowerLatinGlyphWidths',
    12: 'gFontShortNarrowLatinGlyphWidths', 13: 'gFontShortNarrowerLatinGlyphWidths',
}
DRAFT_FILES = {
    'gFontSmallLatinGlyphWidths': 'small', 'gFontNormalLatinGlyphWidths': 'normal',
    'gFontShortLatinGlyphWidths': 'short', 'gFontNarrowLatinGlyphWidths': 'narrow',
    'gFontSmallNarrowLatinGlyphWidths': 'small_narrow', 'gFontNarrowerLatinGlyphWidths': 'narrower',
    'gFontSmallNarrowerLatinGlyphWidths': 'small_narrower', 'gFontShortNarrowLatinGlyphWidths': 'short_narrow',
    'gFontShortNarrowerLatinGlyphWidths': 'short_narrower',
}
# Proposed draft widths, in the order below; used only if the draft files are missing.
_DRAFT_ORDER = 'אבגדהוזחטיכלמנסעפצקרשתןםץףך'
_DRAFT_BUILTIN = {
    'normal': '7 7 5 7 7 4 5 7 7 4 6 6 7 4 7 7 7 6 6 6 7 7 4 7 6 7 6',
    'short': '7 7 5 7 7 4 5 7 7 4 6 6 7 4 7 7 7 6 6 6 7 7 4 7 6 7 6',
    'small': '6 6 5 6 6 4 5 6 6 4 5 6 6 4 6 6 6 6 6 5 7 6 4 6 6 6 5',
    'small_narrow': '6 6 5 6 6 4 5 6 6 4 5 6 6 4 6 6 6 6 6 5 7 6 4 6 6 6 5',
    'narrow': '6 6 5 6 6 4 5 6 6 4 5 6 6 4 6 6 6 6 6 5 7 6 4 6 6 6 5',
    'short_narrow': '6 6 5 6 6 4 5 6 6 4 5 6 6 4 6 6 6 6 6 5 7 6 4 6 6 6 5',
    'narrower': '5 5 5 5 5 4 5 5 5 4 5 5 5 4 5 5 5 5 5 5 6 5 4 5 5 5 5',
    'short_narrower': '5 5 5 5 5 4 5 5 5 4 5 5 5 4 5 5 5 5 5 5 6 5 4 5 5 5 5',
    'small_narrower': '5 5 5 5 5 4 5 5 5 4 5 5 5 4 5 5 5 5 5 5 6 5 4 5 5 5 5',
}
# src/text.c:94-112 sKeypadIcons widths, indexed by the byte after F8
KEYPAD_WIDTHS = {0x00: 8, 0x01: 8, 0x02: 16, 0x03: 16, 0x04: 24, 0x05: 24, 0x06: 8, 0x07: 8, 0x08: 8,
                 0x09: 8, 0x0A: 8, 0x0B: 8, 0x0C: 8}
PROMPT_ARROW_PX = 8          # TextPrinterDrawDownArrow (src/text.c; 2.0.6 :1175-1215): 8x16 arrow after the last glyph; RtlDownArrowX under TEXT_RTL

EOS, NEWLINE, PLACEHOLDER, CTRL, PROMPT_CLEAR, PROMPT_SCROLL = 0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA
EXTRA_SYMBOL, KEYPAD_ICON, DYNAMIC = 0xF9, 0xF8, 0xF7
SPACE, NBSP = 0x00, 0x39
# Argument bytes after FC <code> as the renderer consumes them (src/text.c RenderText; matches
# src/string_util.c:709-745 GetExtCtrlCodeLength - 1, except SPEAKER which reads one argument byte).
CTRL_ARGS = {0x01: 1, 0x02: 1, 0x03: 1, 0x04: 3, 0x05: 1, 0x06: 1, 0x07: 0, 0x08: 1, 0x09: 0, 0x0A: 0,
             0x0B: 2, 0x0C: 1, 0x0D: 1, 0x0E: 1, 0x0F: 0, 0x10: 2, 0x11: 1, 0x12: 1, 0x13: 1, 0x14: 1,
             0x15: 0, 0x16: 0, 0x17: 0, 0x18: 0, 0x19: 1, 0x1A: 1, 0x1B: 1, 0x1C: 3}

# Worst-case placeholder expansions. Byte limits are the engine's name buffers (data/budgets.json
# name_limits); battle prefixes are read from the translated tree so the Hebrew
# prefix is measured once it exists (src/battle_message.c:133-143, 2924-2956, 3654-3690).
NICK = 'W12'
WORST_CASE = {
    # field placeholders (src/string_util.c ExpandPlaceholder_*)
    'PLAYER': 'W7', 'RIVAL': 'W7', 'STR_VAR_1': NICK, 'STR_VAR_2': NICK, 'STR_VAR_3': NICK,
    'KUN': 'empty',
    'VERSION': 'sym:gText_ExpandedPlaceholder_Emerald', 'AQUA': 'sym:gText_ExpandedPlaceholder_Aqua',
    'MAGMA': 'sym:gText_ExpandedPlaceholder_Magma', 'ARCHIE': 'sym:gText_ExpandedPlaceholder_Archie',
    'MAXIE': 'sym:gText_ExpandedPlaceholder_Maxie', 'KYOGRE': 'sym:gText_ExpandedPlaceholder_Kyogre',
    'GROUDON': 'sym:gText_ExpandedPlaceholder_Groudon', 'REGION': 'W10',
    # battle placeholders (src/battle_message.c BattleStringExpandPlaceholders)
    'B_BUFF1': NICK, 'B_BUFF2': NICK, 'B_BUFF3': NICK,
    'B_COPY_VAR_1': NICK, 'B_COPY_VAR_2': NICK, 'B_COPY_VAR_3': NICK,
    'B_PLAYER_MON1_NAME': NICK, 'B_OPPONENT_MON1_NAME': NICK, 'B_PLAYER_MON2_NAME': NICK,
    'B_OPPONENT_MON2_NAME': NICK, 'B_LINK_PLAYER_MON1_NAME': NICK, 'B_LINK_OPPONENT_MON1_NAME': NICK,
    'B_LINK_PLAYER_MON2_NAME': NICK, 'B_LINK_OPPONENT_MON2_NAME': NICK,
    'B_ATK_NAME_WITH_PREFIX_MON1': 'sym:sText_FoePkmnPrefix|sText_WildPkmnPrefix+' + NICK,
    'B_ATK_NAME_WITH_PREFIX': 'sym:sText_FoePkmnPrefix|sText_WildPkmnPrefix+' + NICK,
    'B_DEF_NAME_WITH_PREFIX': 'sym:sText_FoePkmnPrefix|sText_WildPkmnPrefix+' + NICK,
    'B_EFF_NAME_WITH_PREFIX': 'sym:sText_FoePkmnPrefix|sText_WildPkmnPrefix+' + NICK,
    'B_SCR_NAME_WITH_PREFIX': 'sym:sText_FoePkmnPrefix|sText_WildPkmnPrefix+' + NICK,
    'B_ATK_NAME_WITH_PREFIX2': 'sym:sText_FoePkmnPrefixLower|sText_WildPkmnPrefixLower+' + NICK,
    'B_DEF_NAME_WITH_PREFIX2': 'sym:sText_FoePkmnPrefixLower|sText_WildPkmnPrefixLower+' + NICK,
    'B_EFF_NAME_WITH_PREFIX2': 'sym:sText_FoePkmnPrefixLower|sText_WildPkmnPrefixLower+' + NICK,
    'B_SCR_NAME_WITH_PREFIX2': 'sym:sText_FoePkmnPrefixLower|sText_WildPkmnPrefixLower+' + NICK,
    'B_ATK_PARTNER_NAME': NICK, 'B_DEF_NAME': NICK, 'B_DEF_PARTNER_NAME': NICK,
    'B_CURRENT_MOVE': 'W16', 'B_LAST_MOVE': 'W16', 'B_LAST_ITEM': 'W19',
    'B_LAST_ABILITY': 'W16', 'B_ATK_ABILITY': 'W16', 'B_DEF_ABILITY': 'W16', 'B_SCR_ABILITY': 'W16',
    'B_EFF_ABILITY': 'W16',
    'B_TRAINER1_CLASS': 'W12', 'B_TRAINER2_CLASS': 'W12', 'B_PARTNER_CLASS': 'W12', 'B_ATK_TRAINER_CLASS': 'W12',
    'B_TRAINER1_NAME': 'W10', 'B_TRAINER2_NAME': 'W10', 'B_PARTNER_NAME': 'W10', 'B_ATK_TRAINER_NAME': 'W10',
    'B_TRAINER1_NAME_WITH_CLASS': 'W12+" "+W10', 'B_TRAINER2_NAME_WITH_CLASS': 'W12+" "+W10',
    'B_PARTNER_NAME_WITH_CLASS': 'W12+" "+W10', 'B_ATK_TRAINER_NAME_WITH_CLASS': 'W12+" "+W10',
    'B_LINK_PLAYER_NAME': 'W7', 'B_LINK_PARTNER_NAME': 'W7', 'B_LINK_OPPONENT1_NAME': 'W7',
    'B_LINK_OPPONENT2_NAME': 'W7', 'B_LINK_SCR_TRAINER_NAME': 'W7', 'B_PLAYER_NAME': 'W7', 'B_RIVAL_NAME': 'W7',
    'B_PC_CREATOR_NAME': 'sym:sText_Someones|sText_Lanettes|sText_Bills',
    'B_TRAINER1_LOSE_TEXT': 'empty', 'B_TRAINER1_WIN_TEXT': 'empty', 'B_TRAINER2_LOSE_TEXT': 'empty',
    'B_TRAINER2_WIN_TEXT': 'empty', 'B_26': 'empty',
    'B_ATK_PREFIX1': 'sym:sText_FoePkmnPrefix2|sText_AllyPkmnPrefix',
    'B_DEF_PREFIX1': 'sym:sText_FoePkmnPrefix2|sText_AllyPkmnPrefix',
    'B_ATK_PREFIX2': 'sym:sText_FoePkmnPrefix3|sText_AllyPkmnPrefix2',
    'B_DEF_PREFIX2': 'sym:sText_FoePkmnPrefix3|sText_AllyPkmnPrefix2',
    'B_ATK_PREFIX3': 'sym:sText_FoePkmnPrefix4|sText_AllyPkmnPrefix3',
    'B_DEF_PREFIX3': 'sym:sText_FoePkmnPrefix4|sText_AllyPkmnPrefix3',
    'B_ATK_TEAM1': 'sym:sText_Your1|sText_Opposing1', 'B_ATK_TEAM2': 'sym:sText_Your2|sText_Opposing2',
    'B_DEF_TEAM1': 'sym:sText_Your1|sText_Opposing1', 'B_DEF_TEAM2': 'sym:sText_Your2|sText_Opposing2',
    'B_EFF_TEAM1': 'sym:sText_Your1|sText_Opposing1', 'B_EFF_TEAM2': 'sym:sText_Your2|sText_Opposing2',
    'B_BUFF3_MOVE': 'W16',
}

Line = namedtuple('Line', 'page row width end prompt nbytes text')
Fill = namedtuple('Fill', 'n mode label')       # n glyphs of the widest/average Hebrew glyph


class TextError(Exception):
    pass


def read_text(path):
    with open(path, encoding='utf-8') as fh:
        return fh.read()


# ---------------------------------------------------------------------------- charmap

class Charmap:
    """charmap.txt as tools/preproc reads it (charmap.cpp): chars, escapes and constants."""

    def __init__(self, path):
        self.path = path
        self.chars, self.escapes, self.consts = {}, {}, {}
        self.decode_char = {}           # byte -> char, first Latin-section single-byte mapping
        latin = True
        with open(path, encoding='utf-8') as fh:
            lines = fh.read().split('\n')
        for raw in lines:
            if raw.startswith('@ Hiragana'):
                latin = False
            line = _strip_charmap_comment(raw).strip()
            if not line:
                continue
            m = re.match(r"^'(\\?)(.)'\s*=\s*((?:[0-9A-Fa-f]{2}\s*)+)$", line)
            if m:
                esc, ch, seq = m.group(1), m.group(2), bytes(int(x, 16) for x in m.group(3).split())
                if esc and ch not in ("'",):
                    self.escapes[ch] = seq
                else:
                    self.chars.setdefault(ch, seq)
                    if latin and len(seq) == 1:
                        self.decode_char.setdefault(seq[0], ch)
                continue
            m = re.match(r'^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*((?:[0-9A-Fa-f]{2}\s*)+)$', line)
            if m:
                self.consts.setdefault(m.group(1), bytes(int(x, 16) for x in m.group(2).split()))
        self.hebrew = {ch: seq[0] for ch, seq in self.chars.items() if 'א' <= ch <= 'ת' and len(seq) == 1}
        self.hebrew_bytes = sorted(set(self.hebrew.values()))
        self._rev = {}
        # byte sequence -> name for decoding; sound constants (SE_*, MUS_*) share these byte values
        # in charmap.txt and are only a fallback
        for name, seq in sorted(self.consts.items(), key=lambda kv: bool(re.match(r'^(SE|MUS)_', kv[0]))):
            if seq and seq[0] in (CTRL, PLACEHOLDER, KEYPAD_ICON, EXTRA_SYMBOL) and len(seq) in (2, 3):
                self._rev.setdefault(seq, name)

    def is_hebrew_byte(self, b):
        return b in self.hebrew_bytes

    def decode(self, data, stop_at_eos=True):
        """Bytes -> source-form text. Unknown bytes come out as {0xNN} (preproc reads that back)."""
        out, i, n = [], 0, len(data)
        while i < n:
            b = data[i]
            if b == EOS:
                out.append('$')
                if stop_at_eos:
                    break
                i += 1
                continue
            if b in (NEWLINE, PROMPT_SCROLL, PROMPT_CLEAR):
                out.append({NEWLINE: '\\n', PROMPT_SCROLL: '\\l', PROMPT_CLEAR: '\\p'}[b])
                i += 1
                continue
            if b == CTRL and i + 1 < n:
                code = data[i + 1]
                nargs = CTRL_ARGS.get(code, 0)
                if code == 0x06 and i + 2 < n and bytes(data[i:i + 3]) in self._rev:
                    out.append('{%s}' % self._rev[bytes(data[i:i + 3])])
                    i += 3
                    continue
                name = self._rev.get(bytes(data[i:i + 2]), '0x%02X 0x%02X' % (CTRL, code))
                args = ' '.join('%d' % a for a in data[i + 2:i + 2 + nargs])
                out.append('{%s%s}' % (name, ' ' + args if args else ''))
                i += 2 + nargs
                continue
            if b in (PLACEHOLDER, KEYPAD_ICON, EXTRA_SYMBOL, DYNAMIC) and i + 1 < n:
                seq = bytes(data[i:i + 2])
                if seq in self._rev:
                    out.append('{%s}' % self._rev[seq])
                else:
                    out.append('{0x%02X 0x%02X}' % (b, data[i + 1]))
                i += 2
                continue
            ch = self.decode_char.get(b)
            out.append(ch if ch is not None else '{0x%02X}' % b)
            i += 1
        return ''.join(out)


def _strip_charmap_comment(line):
    """charmap.cpp RemoveComments: '@' starts a comment unless it is inside '...'."""
    out, in_str, i = [], False, 0
    while i < len(line):
        c = line[i]
        if in_str:
            if c == '\\' and i + 1 < len(line) and line[i + 1] == "'":
                out.append(line[i:i + 2])
                i += 2
                continue
            if c == "'":
                in_str = False
        elif c == '@':
            break
        elif c == "'":
            in_str = True
        out.append(c)
        i += 1
    return ''.join(out)


# ---------------------------------------------------------------------------- fonts

def parse_width_tables(fonts_c):
    src = read_text(fonts_c)
    out = {}
    for m in re.finditer(r'const\s+u8\s+(\w+LatinGlyphWidths)\s*\[\s*\]\s*=\s*\{(.*?)\};', src, re.S):
        body = re.sub(r'//[^\n]*|/\*.*?\*/', '', m.group(2), flags=re.S)
        vals = [int(v, 0) for v in re.findall(r'0x[0-9A-Fa-f]+|\d+', body)]
        out[m.group(1)] = vals + [0] * (512 - len(vals))
    return out


def _read_draft(name, charmap, draft_dir):
    path = os.path.join(draft_dir, '%s_hebrew_widths.txt' % name)
    widths = {}
    if os.path.exists(path):
        for line in read_text(path).split('\n'):
            f = line.split()
            if len(f) >= 3 and f[0] in charmap.hebrew and f[2].isdigit():
                widths[charmap.hebrew[f[0]]] = int(f[2])
        if len(widths) == len(charmap.hebrew):
            return widths, 'draft:' + path
    vals = [int(v) for v in _DRAFT_BUILTIN[name].split()]
    for ch, w in zip(_DRAFT_ORDER, vals):
        if ch in charmap.hebrew:
            widths[charmap.hebrew[ch]] = w
    return widths, 'builtin draft'


class Fonts:
    """The nine Latin width tables, with Hebrew slots resolved (table, or draft until fonts land)."""

    def __init__(self, tree=FONTS_TREE, charmap=None, hebrew_widths='auto', draft_dir=DRAFT_DIR,
                 reference_tree=EN_TREE):
        self.tree = tree
        self.charmap = charmap or Charmap(os.path.join(tree, 'charmap.txt'))
        raw = parse_width_tables(os.path.join(tree, 'src', 'fonts.c'))
        missing = sorted(set(WIDTH_TABLES.values()) - set(raw))
        if missing:
            raise TextError('%s/src/fonts.c lacks %s' % (tree, ', '.join(missing)))
        # A font counts as landed when any Hebrew slot differs from the pristine English table
        # (upstream blanks are 3 px, a few slots hold upstream junk: 0x50 box, 0x48 in short_narrower).
        # Each font lands whole, and a few letters (ו י ן) are 3 px like the blank they replace, so
        # one changed slot means the whole table is real.
        ref_path = os.path.join(reference_tree, 'src', 'fonts.c') if reference_tree else None
        ref = parse_width_tables(ref_path) if ref_path and os.path.exists(ref_path) else {}
        self.tables, self.source = {}, {}
        heb = list(self.charmap.hebrew_bytes)
        for name, widths in raw.items():
            widths = list(widths)
            base = ref.get(name)
            landed = [b for b in heb if base is None or widths[b] != base[b]] if base else \
                [b for b in heb if widths[b] != widths[0x30]]
            if hebrew_widths == 'table' or not heb:
                self.source[name] = 'fonts.c'
            elif hebrew_widths == 'auto' and landed:
                self.source[name] = 'fonts.c'
            else:
                draft, src = _read_draft(DRAFT_FILES[name], self.charmap, draft_dir)
                keep = set(landed) if hebrew_widths == 'auto' else set()
                for b, w in draft.items():
                    if b not in keep:
                        widths[b] = w
                self.source[name] = src if not keep else '%s; fonts.c for %d/%d letters' % (src, len(keep), len(heb))
            self.tables[name] = widths

    def table(self, font_id):
        name = WIDTH_TABLES.get(font_id)
        if name is None:
            raise TextError('font %s has no Latin width table (braille/bold are not modelled)'
                            % FONT_NAMES.get(font_id, font_id))
        return self.tables[name]

    def widest_hebrew(self, font_id):
        t = self.table(font_id)
        b = max(self.charmap.hebrew_bytes, key=lambda c: (t[c], -c))
        return b, t[b]

    def avg_hebrew(self, font_id):
        t = self.table(font_id)
        return sum(t[b] for b in self.charmap.hebrew_bytes) / float(len(self.charmap.hebrew_bytes))

    def fill_byte(self, font_id, mode):
        """The Hebrew byte that stands for one placeholder glyph in this font."""
        b, w = self.widest_hebrew(font_id)
        if mode == 'max':
            return b
        t, avg = self.table(font_id), self.avg_hebrew(font_id)
        return min(self.charmap.hebrew_bytes, key=lambda c: (abs(t[c] - avg), -t[c]))


def font_id(name):
    if isinstance(name, int):
        return name
    s = str(name).strip()
    if s.isdigit():
        return int(s)
    if not s.startswith('FONT_'):
        s = 'FONT_' + s
    if s not in FONT_IDS:
        raise TextError('unknown font %s' % name)
    return FONT_IDS[s]


# ---------------------------------------------------------------------------- C string lookup

_C_SYM_RE = r'(?:const\s+)?u8\s+%s\s*\[\s*\w*\s*\]\s*=\s*(?:_|COMPOUND_STRING)\(\s*((?:"(?:[^"\\\n]|\\.)*"\s*)+)\)'


def find_c_string(tree, name, _cache={}):
    """Source text of `const u8 NAME[] = _("...")` anywhere in TREE/src (first match)."""
    key = (tree, name)
    if key in _cache:
        return _cache[key]
    if (tree, None) not in _cache:
        texts = []
        for dp, dn, fn in os.walk(os.path.join(tree, 'src')):
            for f in fn:
                if f.endswith('.c'):
                    try:
                        texts.append(read_text(os.path.join(dp, f)))
                    except (UnicodeDecodeError, OSError):
                        pass
        _cache[(tree, None)] = '\n'.join(texts)
    m = re.search(_C_SYM_RE % re.escape(name), _cache[(tree, None)])
    val = ''.join(re.findall(r'"((?:[^"\\\n]|\\.)*)"', m.group(1))) if m else None
    _cache[key] = val
    return val


# ---------------------------------------------------------------------------- the model

class TextModel:
    def __init__(self, tree=FONTS_TREE, charmap=None, symtree=SYM_TREE, fill='max', subst=None,
                 hebrew_widths='auto', draft_dir=DRAFT_DIR, reference_tree=EN_TREE):
        if isinstance(charmap, str):
            charmap = Charmap(charmap)
        self.charmap = charmap or Charmap(os.path.join(tree, 'charmap.txt'))
        self.fonts = Fonts(tree, self.charmap, hebrew_widths, draft_dir, reference_tree)
        self.symtree = symtree
        self.fill = fill
        self.subst = dict(WORST_CASE)
        if subst:
            self.subst.update(subst)
        self.warnings = []

    # -- encoding (tools/preproc/string_parser.cpp semantics)
    def encode(self, text, subst=None, nbsp=False, errors=None):
        """Source text -> list of units: ints (bytes) and Fill(n) for worst-case names.
        subst: extra/overriding placeholder specs; nbsp: spaces inside expansions become NBSP
        (what battle expansion does, src/battle_message.c:3704-3712). Unencodable characters
        are reported in ERRORS (a list) when given, else raised."""
        table = self.subst if not subst else dict(self.subst, **subst)
        out, i, n = [], 0, len(text)
        while i < n:
            c = text[i]
            if c == '{':
                j = text.find('}', i)
                if j < 0:
                    self._err(errors, 'unterminated { at %d' % i)
                    break
                inner = text[i + 1:j].strip()
                i = j + 1
                if re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', inner) and inner in table:
                    out.extend(self._expand(table[inner], nbsp, errors))
                    continue
                out.extend(self._brace(inner, errors))
                continue
            if c == '\\' and i + 1 < n:
                e = text[i + 1]
                i += 2
                if e in self.charmap.escapes:
                    out.extend(self.charmap.escapes[e])
                elif e in ('"', '\\') and e in self.charmap.chars:
                    out.extend(self.charmap.chars[e])
                else:
                    self._err(errors, 'unknown escape \\%s' % e)
                continue
            seq = self.charmap.chars.get(c)
            if seq is None:
                self._err(errors, 'unencodable %r (U+%04X)' % (c, ord(c)))
            else:
                out.extend(seq)
            i += 1
        return out

    def _err(self, errors, msg):
        if errors is None:
            raise TextError(msg)
        errors.append(msg)

    def _brace(self, inner, errors):
        out = []
        for tok in inner.split():
            if re.match(r'^0x[0-9A-Fa-f]+$', tok):
                digits = tok[2:]
                if len(digits) not in (2, 4, 8):
                    self._err(errors, 'hex literal %s must have 2, 4 or 8 digits' % tok)
                    continue
                v = int(digits, 16)
                out.extend(v.to_bytes(len(digits) // 2, 'little'))
            elif re.match(r'^\d+[HW]?$', tok):
                v = int(tok.rstrip('HW'))
                size = 2 if tok.endswith('H') else 4 if tok.endswith('W') else (1 if v < 0x100 else 2 if v < 0x10000 else 4)
                out.extend(v.to_bytes(size, 'little'))
            elif tok in self.charmap.consts:
                out.extend(self.charmap.consts[tok])
            else:
                self._err(errors, 'unknown constant {%s}' % tok)
        return out

    def _expand(self, spec, nbsp, errors):
        out = []
        for part in _split_spec(spec):
            if part in ('', 'empty'):
                continue
            m = re.match(r'^W(\d+)$', part)
            if m:
                out.append(Fill(int(m.group(1)), self.fill, spec))
                continue
            if part.startswith('"') and part.endswith('"'):
                units = self.encode(part[1:-1], errors=errors)
            elif part.startswith('sym:'):
                units = self._sym_units(part[4:].split('|'), errors)
            else:
                self._err(errors, 'bad substitution spec %r' % part)
                continue
            if nbsp:
                units = [NBSP if u == SPACE else u for u in units]
            out.extend(units)
        return out

    def _sym_units(self, names, errors):
        best, best_w = [], -1
        for name in names:
            txt = find_c_string(self.symtree, name) if self.symtree else None
            if txt is None:
                self.warnings.append('substitution sym:%s not found in %s' % (name, self.symtree))
                continue
            units = self.encode(txt, errors=errors)
            if units and units[-1] == EOS:
                units = units[:-1]
            w = self.layout(units, 1)[0].width if units else 0
            if w > best_w:
                best, best_w = units, w
        return best

    def resolve(self, units, font):
        """Replace Fill units with real Hebrew bytes for the font active at that point."""
        fid = font_id(font)
        out, i = [], 0
        while i < len(units):
            u = units[i]
            if isinstance(u, Fill):
                out.extend([self.fonts.fill_byte(fid, u.mode)] * u.n)
                i += 1
                continue
            if u == CTRL and i + 2 < len(units) and units[i + 1] == 0x06 and not isinstance(units[i + 2], Fill):
                fid = units[i + 2]
            out.append(u)
            i += 1
        return out

    # -- layout (src/text.c RenderText, logical pen)
    def layout(self, units, font='FONT_NORMAL', x=0):
        fid = font_id(font)
        units = self.resolve(units, fid)
        table = self.fonts.table(fid)
        lines = []
        page, row = 1, 1
        pen = extent = x
        min_ls = 0
        nbytes = 0
        start = 0
        i, n = 0, len(units)

        def close(end, upto):
            lines.append(Line(page, row, extent - x, end, end in ('l', 'p'), nbytes, bytes(units[start:upto])))

        def adv(glyph):
            return min_ls if min_ls else table[glyph & 0x1FF]

        while i < n:
            b = units[i]
            if b == EOS:
                close('$', i)
                return lines
            if b in (NEWLINE, PROMPT_SCROLL, PROMPT_CLEAR):
                close({NEWLINE: 'n', PROMPT_SCROLL: 'l', PROMPT_CLEAR: 'p'}[b], i)
                if b == NEWLINE:
                    row += 1
                elif b == PROMPT_CLEAR:
                    page, row = page + 1, 1
                pen = extent = x
                nbytes = 0
                i += 1
                start = i
                continue
            if b == PLACEHOLDER:
                self.warnings.append('unexpanded placeholder FD %02X' % (units[i + 1] if i + 1 < n else 0))
                i += 2
                nbytes += 2
                continue
            if b == DYNAMIC:
                self.warnings.append('dynamic placeholder F7 %02X has no width' % (units[i + 1] if i + 1 < n else 0))
                i += 2
                nbytes += 2
                continue
            if b == KEYPAD_ICON:
                pen += KEYPAD_WIDTHS.get(units[i + 1] if i + 1 < n else 0, 8)
                extent = max(extent, pen)
                i += 2
                nbytes += 2
                continue
            if b == EXTRA_SYMBOL:
                pen += adv(0x100 | (units[i + 1] if i + 1 < n else 0))
                extent = max(extent, pen)
                i += 2
                nbytes += 2
                continue
            if b == CTRL:
                code = units[i + 1] if i + 1 < n else 0
                nargs = CTRL_ARGS.get(code)
                args = units[i + 2:i + 2 + (nargs or 0)]
                arg = args[0] if args else 0
                if nargs is None:              # unhandled code: the renderer draws it as a glyph
                    pen += adv(code)
                    extent = max(extent, pen)
                    i += 2
                    nbytes += 2
                    continue
                if code == 0x06:
                    if arg not in WIDTH_TABLES:
                        raise TextError('{FONT %d} has no Latin width table' % arg)
                    fid, table = arg, self.fonts.table(arg)
                elif code == 0x0C:
                    pen += adv(0x100 | arg)
                elif code in (0x0D, 0x12):
                    pen = x + arg
                elif code == 0x0F:
                    pen = extent = x
                elif code == 0x11:
                    pen += arg
                elif code == 0x13:
                    pen = max(pen, x + arg)
                elif code == 0x14:
                    min_ls = arg
                extent = max(extent, pen)
                i += 2 + nargs
                nbytes += 2 + nargs
                continue
            pen += adv(b)
            extent = max(extent, pen)
            i += 1
            nbytes += 1
        close('eos', n)
        return lines

    # -- convenience
    def units(self, text_or_units, subst=None, nbsp=False, errors=None):
        if isinstance(text_or_units, str):
            return self.encode(text_or_units, subst, nbsp, errors)
        return list(text_or_units)

    def lines(self, text, font='FONT_NORMAL', x=0, subst=None, nbsp=False, errors=None):
        return self.layout(self.units(text, subst, nbsp, errors), font, x)

    def width(self, text, font='FONT_NORMAL', x=0, subst=None):
        return max((l.width for l in self.lines(text, font, x, subst)), default=0)

    def byte_length(self, text, subst=None, include_eos=False):
        """Encoded length after worst-case expansion (Fill counts as n bytes); stops at the first $."""
        n = 0
        for u in self.units(text, subst):
            if isinstance(u, Fill):
                n += u.n
            elif u == EOS:
                return n + (1 if include_eos else 0)
            else:
                n += 1
        return n

    def decode(self, data, stop_at_eos=True):
        return self.charmap.decode(data, stop_at_eos)


def _split_spec(spec):
    parts, cur, q = [], '', False
    for c in spec:
        if c == '"':
            q = not q
        if c == '+' and not q:
            parts.append(cur.strip())
            cur = ''
        else:
            cur += c
    parts.append(cur.strip())
    return parts


def battle_auto_wrap(model, units, font='FONT_NORMAL', max_width=208, screen_lines=2, prompt=True):
    """src/line_break.c BreakStringAutomatic + BreakSubStringAutomatic, ported as written
    (word widths add GetGlyphWidth over every byte, control bytes included; words split only at
    CHAR_SPACE; segments that already hold \\n or \\l are left alone). Returns the new byte list."""
    fid = font_id(font)
    data = model.resolve(units, fid)
    table = model.fonts.table(fid)
    out, seg = [], []
    for b in data + [None]:
        if b is None or b == PROMPT_CLEAR or b == EOS:
            out.extend(_break_sub(seg, table, max_width, screen_lines, prompt))
            seg = []
            if b is not None:
                out.append(b)
            if b == EOS:
                break
        else:
            seg.append(b)
    return out


def _break_sub(src, table, max_width, screen_lines, prompt):
    src = list(src)
    if not src or NEWLINE in src or PROMPT_SCROLL in src:
        return src
    n = len(src)
    words = []                       # [start, length, width]
    start, length, prev = 0, 1, False
    for i in range(1, n):
        cur = src[i] == SPACE
        if cur and not prev:
            words.append([start, length, 0])
            length = 0
        elif not cur and prev:
            start = i
            length += 1
        else:
            length += 1
        prev = cur
    words.append([start, length, 0])
    for w in words:
        w[2] = sum(table[src[w[0] + j]] for j in range(w[1]) if w[0] + j < n)
    space = table[SPACE]
    total = words[0][2] + sum(w[2] + space for w in words[1:])
    if prompt:
        total += PROMPT_ARROW_PX
    if total <= max_width:
        return src
    cur_w, total_lines = 0, 1
    for k, w in enumerate(words):
        if prompt and k + 1 == len(words):
            cur_w += PROMPT_ARROW_PX
        if cur_w + w[1] > max_width:          # upstream compares the word LENGTH here
            total_lines += 1
            cur_w = w[2]
        else:
            cur_w += w[2] + space
    if cur_w > max_width:
        total_lines += 1
    while True:
        target = total // total_lines
        lines = [[0]]
        cur_w = words[0][2]
        k, retry = 1, False
        while k < len(words):
            over = cur_w + space + words[k][2] + (PROMPT_ARROW_PX if prompt else 0) > max_width
            if over or cur_w > target:
                if len(lines) == total_lines:
                    total_lines += 1
                    retry = True
                    break
                lines.append([k])
                cur_w = words[k][2]
            else:
                cur_w += space + words[k][2]
                lines[-1].append(k)
            k += 1
        if not retry:
            break
    idx = 0                          # BuildNewString: assumes one space between words
    for li, ws in enumerate(lines):
        idx += words[ws[0]][1]
        for k in ws[1:]:
            idx += words[k][1] + 1
        if li + 1 < len(lines):
            if idx < n:
                if li >= screen_lines - 1 and len(lines) > screen_lines and prompt:
                    src[idx] = PROMPT_SCROLL
                else:
                    src[idx] = NEWLINE
            idx += 1
    return src


# ---------------------------------------------------------------------------- CLI

def _parse_subst(items):
    out = {}
    for it in items or []:
        if '=' not in it:
            raise SystemExit('--subst wants NAME=SPEC, got %r' % it)
        k, v = it.split('=', 1)
        out[k.strip().strip('{}')] = v.strip()
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('text', nargs='*')
    ap.add_argument('--tree', default=FONTS_TREE)
    ap.add_argument('--charmap')
    ap.add_argument('--symtree', default=SYM_TREE)
    ap.add_argument('--font', default='FONT_NORMAL')
    ap.add_argument('--x', type=int, default=0)
    ap.add_argument('--fill', choices=('max', 'avg'), default='max')
    ap.add_argument('--subst', action='append')
    ap.add_argument('--hebrew-widths', choices=('auto', 'table', 'draft'), default='auto')
    ap.add_argument('--stdin', action='store_true')
    ap.add_argument('--fonts', action='store_true')
    ap.add_argument('--subst-table', action='store_true')
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args(argv)
    try:
        m = TextModel(a.tree, a.charmap, a.symtree, a.fill, _parse_subst(a.subst), a.hebrew_widths)
    except (TextError, OSError) as e:
        sys.stderr.write('textwidth: %s\n' % e)
        return 2
    if a.subst_table:
        for k in sorted(m.subst):
            print('%-32s %s' % (k, m.subst[k]))
        return 0
    if a.fonts:
        rows = []
        for fid in sorted(WIDTH_TABLES):
            b, w = m.fonts.widest_hebrew(fid)
            rows.append({'font': FONT_NAMES[fid], 'id': fid, 'table': WIDTH_TABLES[fid], 'widest_hebrew': w,
                         'widest_hebrew_char': m.charmap.decode_char.get(b, '?'),
                         'avg_hebrew': round(m.fonts.avg_hebrew(fid), 2),
                         'hebrew_source': m.fonts.source[WIDTH_TABLES[fid]]})
        if a.json:
            print(json.dumps(rows, ensure_ascii=False, indent=1))
        else:
            for r in rows:
                print('%-20s %2d  widest %d (%s)  avg %.2f  %s' % (r['font'], r['id'], r['widest_hebrew'],
                      r['widest_hebrew_char'], r['avg_hebrew'], r['hebrew_source']))
        return 0
    texts = a.text
    if a.stdin:
        texts = [l.rstrip('\n') for l in sys.stdin]
    if not texts:
        ap.print_usage()
        return 2
    results, bad = [], 0
    for t in texts:
        errs = []
        lines = m.lines(t, a.font, a.x, errors=errs)
        bad += bool(errs)
        results.append({'text': t, 'font': FONT_NAMES[font_id(a.font)], 'errors': errs,
                        'bytes': m.byte_length(t) if not errs else None,
                        'lines': [{'page': l.page, 'row': l.row, 'width': l.width, 'end': l.end,
                                   'prompt': l.prompt} for l in lines]})
    if a.json:
        print(json.dumps({'results': results, 'warnings': sorted(set(m.warnings))}, ensure_ascii=False, indent=1))
    else:
        for r in results:
            print(r['text'])
            for e in r['errors']:
                print('   ERROR %s' % e)
            for l in r['lines']:
                print('   p%d r%d %4d px%s  (%s)' % (l['page'], l['row'], l['width'],
                      ' +8 arrow' if l['prompt'] else '', l['end']))
            if r['bytes'] is not None:
                print('   %d bytes after expansion' % r['bytes'])
        for w in sorted(set(m.warnings)):
            print('warning: %s' % w)
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
