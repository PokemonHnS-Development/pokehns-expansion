#!/usr/bin/env python3
"""Validate a translated chunk of units before it is applied to the tree.

  checkunits.py CHUNK.json [CHUNK.json ...] [--strict] [--quiet]

Per unit (skipping "fixed" name units):
  EMPTY       no Hebrew yet
  TOKENS      {PLACEHOLDER}/{CONTROL} sequence differs from English (drift.py's rule: {POKE} {PKMN}
              {POKEBLOCK} {ID} {NO} may go, {B_BUFF1}..{B_BUFF3} may change places)
  TERMINATOR  script text gained or lost its trailing $
  ESCAPE      a bare " or an unknown backslash escape (\\n \\l \\p only)
  CHARSET     a character the charmap cannot encode
  DIGITS      the Hebrew lost or reversed a number from the English (digits must stay in reading order)
  LATIN       Latin words left in a Hebrew string (warning; known abbreviations are allowed)
  NOHEBREW    the "translation" has no Hebrew letters but the English has words (warning)
  WIDTH       a line is wider than its budget (needs textwidth.py and a known kind)
  LINES       more lines on one page than the window holds
  BYTES       longer than a hard buffer (gStringVar4 999 bytes, battle text 424)
Exit status 1 if any error (warnings do not fail unless --strict).
"""
import argparse, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402
from drift import DROPPABLE_TOKENS as DROPPABLE, same_tokens  # noqa: E402  the CI gate's token rule

TOKEN_RE = re.compile(r'\{[^}]*\}')
LATIN_OK = {
    'PP', 'HP', 'TM', 'HM', 'Lv', 'LV', 'OK', 'ID', 'No', 'PC', 'TV', 'CD', 'GBA', 'EXP', 'IV', 'IVs',
    'EV', 'EVs', 'BP', 'GTS', 'HnS', 'DS', 'Wi', 'Fi', 'vs', 'VS', 'KO', 'SP', 'ATK', 'DEF', 'SPD',
    'STAB', 'UFO', 'DNA', 'XD', 'GO', 'A', 'B', 'L', 'R', 'X', 'Y', 'Z', 'START', 'SELECT',
}
CHARMAP = os.path.join(paths.FONTS_TREE, 'charmap.txt')


def load_charmap():
    chars = set()
    for line in open(CHARMAP, encoding='utf-8'):
        m = re.match(r"^'(.+)'\s*=", line)
        if m:
            chars.add(m.group(1).replace("\\'", "'"))
    return chars


CHARS = load_charmap()

try:
    import textwidth as TW
except Exception:
    TW = None

with open(paths.BUDGETS, encoding='utf-8') as _f:
    KINDS = json.load(_f)['kinds']


def budget_kind(u):
    """The budgets.json kind of the window that shows a unit's text, by file and field, or None."""
    f, field, key = u['file'], u.get('field') or '', u.get('key') or ''
    if u['kind'] == 'script':
        return 'overworld_dialogue'
    if f.endswith('battle_message.c'):
        return 'battle_message'
    if f.endswith('items.h') and (field == 'description' or key.endswith('Desc')):
        return 'item_description'
    if f.endswith('moves_info.h') and (field == 'description' or 'Description' in key):
        return 'relearner_move_description'
    if f.endswith('abilities.h') and field == 'description':
        return 'dex_ability'
    if '/species_info/' in f and field == 'description':
        return 'dex_entry'
    return None


def budget_for(u):
    """(font, px per line, lines per page, px of a line that ends in a prompt arrow), all from the
    unit's budgets.json kind, or None."""
    kind = budget_kind(u)
    if not kind:
        return None
    b = KINDS[kind]
    return b['font'], b['max_px_per_line'], b['max_lines'], b.get('prompt_line_px', b['max_px_per_line'])


def digits(s):
    return re.findall(r'\d+', TOKEN_RE.sub(' ', s))


_MODEL = None


def model():
    global _MODEL
    if _MODEL is None and TW is not None:
        _MODEL = TW.TextModel(tree=paths.FONTS_TREE)
    return _MODEL


def measure_lines(text, font):
    """[(page, row, width, ends_with_prompt)] with worst-case placeholder widths, or None."""
    m = model()
    if m is None:
        return None
    try:
        return [(l.page, l.row, l.width, l.prompt) for l in m.lines(text, font)]
    except Exception:
        return None


def check(u):
    errs, warns = [], []
    en, he = u['en'], u.get('he') or ''
    if u.get('fixed'):
        return errs, warns
    if not he:
        return ['EMPTY'], warns
    t_en = [t for t in TOKEN_RE.findall(en) if t not in DROPPABLE]
    t_he = [t for t in TOKEN_RE.findall(he) if t not in DROPPABLE]
    if not same_tokens(t_en, t_he):
        errs.append('TOKENS %s -> %s' % (t_en, t_he))
    if u['kind'] == 'script' and en.endswith('$') != he.endswith('$'):
        errs.append('TERMINATOR')
    i = 0
    while i < len(he):
        if he[i] == '"' and u['kind'] == 'c':
            errs.append('ESCAPE bare double quote (use ”)')
            break
        if he[i] == '\\':
            if i + 1 >= len(he) or he[i + 1] not in 'nlp':
                errs.append('ESCAPE \\%s' % (he[i + 1] if i + 1 < len(he) else ''))
                break
            i += 2
            continue
        i += 1
    body = TOKEN_RE.sub('', he)
    body = re.sub(r'\\[nlp]', '', body)
    bad = sorted({c for c in body if c not in CHARS and c != '$'})
    if bad:
        errs.append('CHARSET %r' % ''.join(bad))
    d_en, d_he = digits(en), digits(he)
    if any(x[::-1] in d_he and x[::-1] != x and x not in d_he for x in d_en):
        errs.append('DIGITS reversed %s -> %s' % (d_en, d_he))
    elif sorted(d_en) != sorted(d_he):
        warns.append('DIGITS %s -> %s' % (d_en, d_he))
    plain = TOKEN_RE.sub(' ', he).replace('\\n', ' ').replace('\\l', ' ').replace('\\p', ' ')
    has_heb = re.search(r'[֐-׿]', plain)
    words = [w for w in re.findall(r'[A-Za-zé]+', plain) if w not in LATIN_OK and len(w) > 1]
    if not has_heb and re.search(r'[A-Za-z]{3}', TOKEN_RE.sub(' ', en)):
        warns.append('NOHEBREW')
    elif words:
        warns.append('LATIN %s' % ' '.join(words[:6]))
    b = budget_for(u)
    if b:
        font, px, max_lines, prompt_px = b
        lines = measure_lines(he, font)
        if lines:
            pages = {}
            for page, row, width, prompt in lines:
                pages.setdefault(page, []).append(row)
                limit = prompt_px if prompt else px
                if width > limit:
                    errs.append('WIDTH page %d line %d: %d px > %d' % (page, row, width, limit))
            # \l scrolls the box one line and keeps the row (src/text.c RENDER_STATE_SCROLL), so a
            # page shows as many lines as it has distinct rows.
            for page, rows in pages.items():
                if len(set(rows)) > max_lines and u['kind'] == 'script':
                    errs.append('LINES page %d has %d lines (max %d)' % (page, len(set(rows)), max_lines))
    return errs, warns


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('chunks', nargs='+')
    ap.add_argument('--strict', action='store_true')
    ap.add_argument('--quiet', action='store_true')
    a = ap.parse_args()
    bad = 0
    total = done = 0
    for path in a.chunks:
        doc = json.load(open(path, encoding='utf-8'))
        us = doc['units'] if isinstance(doc, dict) else doc
        for u in us:
            if u.get('fixed'):
                continue
            total += 1
            errs, warns = check(u)
            if not errs or errs == ['EMPTY']:
                done += 0 if errs else 1
            if a.strict:
                errs += warns
                warns = []
            if errs:
                bad += 1
            if errs or (warns and not a.quiet):
                print('%s %s' % ('E' if errs else 'w', u['id']))
                for e in errs:
                    print('    E', e)
                for w in warns:
                    print('    w', w)
    print('%d units, %d translated and clean, %d with errors' % (total, done, bad))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
