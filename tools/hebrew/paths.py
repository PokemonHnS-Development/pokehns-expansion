#!/usr/bin/env python3
"""Every location the Hebrew tools use, resolved in one place.

Each value can be set with an environment variable; the defaults are relative to this
repository (REPO = two directories above tools/hebrew). An empty variable counts as unset.

  HNS_TREE        the Hebrew source tree                     default: REPO
  HNS_BASELINE    engine baseline: Hebrew engine, English    default: ../pokehns-heb-engine next to
                  strings (what drift.py and make_chunks.py  REPO, if that directory exists
                  compare against and extract from)
  HNS_UPSTREAM    upstream English tree                      default: ../pokehns-en next to REPO,
                                                             if that directory exists
  HNS_FIRERED     the FireRed Hebrew tree (namecheck.py      default: ../pokefirered-heb next to
                  --fr-sync compares names with it)          REPO, if that directory exists
  HNS_FONTS_TREE  tree whose src/fonts.c and charmap.txt     default: HNS_TREE
                  the width model reads
  HNS_DATA        data files the tools read                  default: tools/hebrew/data
  HNS_GLOSSARY    the glossary                               default: translation/hebrew/glossary.csv
                  (glossary_sources.csv sits next to it)
  HNS_WORK        scratch and output folder for runs         default: REPO/build/hebrew
  HNS_UNITS       translation unit chunks (make_chunks.py    default: HNS_WORK/units
                  output, sweep.py label source)
  HNS_ROM         Hebrew ROM (its .elf sits next to it)      default: HNS_TREE/pokehns.gba
  HNS_EN_ROM      English reference ROM                      default: HNS_UPSTREAM/pokehns.gba
  HNS_SAVES       save-ladder folder (ladder1_newgame.sav    no default
                  ... ladder6_postgame.sav)
  HNS_RUNNER      the hnsrun binary                          default: tools/hebrew/emu/hnsrun

  python3 paths.py          print every value
  python3 paths.py NAME     print one value (TREE, BASELINE, ...); exit 1 if it has none
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))


def _env(name, default=None):
    v = os.environ.get(name, '').strip()
    return os.path.abspath(os.path.expanduser(v)) if v else default


def _sibling(name):
    p = os.path.join(os.path.dirname(REPO), name)
    return p if os.path.isdir(p) else None


def _join(base, *parts):
    return os.path.join(base, *parts) if base else None


TREE = _env('HNS_TREE', REPO)
BASELINE = _env('HNS_BASELINE', _sibling('pokehns-heb-engine'))
UPSTREAM = _env('HNS_UPSTREAM', _sibling('pokehns-en'))
FIRERED = _env('HNS_FIRERED', _sibling('pokefirered-heb'))
FONTS_TREE = _env('HNS_FONTS_TREE', TREE)
DATA = _env('HNS_DATA', os.path.join(HERE, 'data'))
GLOSSARY = _env('HNS_GLOSSARY', os.path.join(REPO, 'translation', 'hebrew', 'glossary.csv'))
WORK = _env('HNS_WORK', os.path.join(REPO, 'build', 'hebrew'))
UNITS = _env('HNS_UNITS', os.path.join(WORK, 'units'))
ROM = _env('HNS_ROM', os.path.join(TREE, 'pokehns.gba'))
EN_ROM = _env('HNS_EN_ROM', _join(UPSTREAM, 'pokehns.gba'))
SAVES = _env('HNS_SAVES')
RUNNER = _env('HNS_RUNNER', os.path.join(HERE, 'emu', 'hnsrun'))

# Files derived from the values above.
TRANSLATION = os.path.dirname(GLOSSARY)
GLOSSARY_SOURCES = os.path.join(TRANSLATION, 'glossary_sources.csv')
BUDGETS = os.path.join(DATA, 'budgets.json')
LIVE_LABELS = os.path.join(DATA, 'live_labels.json')
C_STRINGS = os.path.join(DATA, 'c_strings.json')
INVENTORY = os.path.join(DATA, 'inventory.json')
FONT_DRAFTS = os.path.join(DATA, 'font_drafts')

NAMES = ('REPO', 'TREE', 'BASELINE', 'UPSTREAM', 'FIRERED', 'FONTS_TREE', 'DATA', 'GLOSSARY', 'WORK', 'UNITS',
         'ROM', 'EN_ROM', 'SAVES', 'RUNNER')
_ENV = {n: 'HNS_' + n for n in NAMES if n != 'REPO'}


def need(name, hint=''):
    """The value of NAME ('BASELINE', ...), or exit with a message saying how to set it."""
    v = globals()[name]
    if v:
        return v
    raise SystemExit('no %s: set %s%s' % (name.lower().replace('_', ' '), _ENV.get(name, name),
                                          (' or ' + hint) if hint else ''))


def save(name):
    """A ladder save by file name, e.g. save('ladder4_league.sav'), or None without HNS_SAVES."""
    return _join(SAVES, name)


def main(argv):
    if len(argv) > 1:
        key = argv[1].upper()
        key = key[4:] if key.startswith('HNS_') else key
        v = globals().get(key) if key in NAMES else None
        if not v:
            sys.stderr.write('paths.py: %s has no value\n' % argv[1])
            return 1
        print(v)
        return 0
    for n in NAMES:
        print('%-15s %s' % (_ENV.get(n, n), globals()[n] or '(unset)'))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
