"""Locations the graphics scripts use, all from tools/hebrew/paths.py.

  TREE    the Hebrew tree: its fonts (graphics/fonts, src/fonts.c) are read, and the scripts'
          write mode writes the redrawn files into it (HNS_TREE)
  GIT     the repository the English originals are read from with `git show` (this repository)
  EN_REF  the English 2.0.6 release (tag Release-v2.0.6), the art every script starts from
  out()   the folder for previews and dry runs: $HNS_WORK/graphics/<family>
  write_target()  where write mode puts a redrawn file (see LATER_EDITS)

Importing this module also puts tools/hebrew/fonts (inspect_fonts.py) on sys.path.
"""
import os
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
FONT_TOOLS = os.path.join(TOOLS, 'fonts')
for _p in (TOOLS, FONT_TOOLS):
    if _p not in sys.path:
        sys.path.insert(0, _p)

import paths  # noqa: E402

TREE = paths.TREE
GIT = paths.REPO
EN_REF = '167aa6d537'
DESIGNS = os.path.join(FONT_TOOLS, 'hebrew_glyph_designs.txt')


def out(family):
    d = os.path.join(paths.WORK, 'graphics', family)
    os.makedirs(d, exist_ok=True)
    return d


def english(path):
    """The bytes of PATH (relative to the tree) in the English release."""
    return subprocess.run(['git', '-C', GIT, 'show', '%s:%s' % (EN_REF, path)],
                          capture_output=True, check=True).stdout


# Files whose committed version was changed after their family script last drew them, by hand or
# by a one-off script that is not kept. Re-running the family script would undo that change, so
# write mode leaves these files alone and saves the script's version under
# $HNS_WORK/graphics/kept/ instead. HNS_GFX_OVERWRITE=1 writes them anyway; the later change must
# then be made again by hand. README.md says which commit made each change.
_PAR = 'paralysis tag widened'
_SLP_QOF = 'sleep tag on the English columns; qof above the bottom row'
LATER_EDITS = {
    'graphics/battle_interface/hns/status.png': _PAR + '; ' + _SLP_QOF,
    'graphics/battle_interface/hns/status2.png': _PAR + '; ' + _SLP_QOF,
    'graphics/battle_interface/hns/status3.png': _PAR + '; ' + _SLP_QOF,
    'graphics/battle_interface/hns/status4.png': _PAR + '; ' + _SLP_QOF,
    'graphics/battle_interface/gen4/status.png': _PAR + '; frostbite tag drawn as קור; ' + _SLP_QOF,
    'graphics/battle_interface/gen4/status2.png': _PAR + '; frostbite tag drawn as קור; ' + _SLP_QOF,
    'graphics/battle_interface/gen4/status3.png': _PAR + '; frostbite tag drawn as קור; ' + _SLP_QOF,
    'graphics/battle_interface/gen4/status4.png': _PAR + '; frostbite tag drawn as קור; ' + _SLP_QOF,
    'graphics/interface/status_icons.png': 'paralysis letters kept inside the pill; ' + _SLP_QOF,
    'graphics/pokedex/hgss/tileset_menu1.png': 'page tabs spaced evenly',
    'graphics/pokedex/hgss/tileset_menu2.png': 'page tabs spaced evenly',
    'graphics/pokedex/hgss/tileset_menu3.png': 'page tabs spaced evenly',
    'graphics/pokedex/hgss/tileset_menu_list.png': 'list START menu mirrored',
    'graphics/pokedex/hgss/tilemap_start_menu.bin': 'list START menu mirrored',
    'graphics/pokedex/hgss/tilemap_start_menu_search_results.bin': 'list START menu mirrored',
    'graphics/pokenav/condition/graph.png': 'two labels moved clear of the pentagon outline',
    'graphics/contest/results_screen/tiles.png': 'the NORMAL rank title reads נורמל',
}


def write_target(path, tree=None):
    """The file write mode should write for PATH (relative to the tree): TREE/PATH, or the kept
    copy under $HNS_WORK/graphics/kept/ for a file in LATER_EDITS."""
    if path in LATER_EDITS and os.environ.get('HNS_GFX_OVERWRITE', '') != '1':
        dst = os.path.join(paths.WORK, 'graphics', 'kept', path)
        sys.stderr.write('kept %s: changed after this script (%s); the script\'s version is %s '
                         '(HNS_GFX_OVERWRITE=1 overwrites)\n' % (path, LATER_EDITS[path], dst))
    else:
        dst = os.path.join(tree or TREE, path)
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    return dst
