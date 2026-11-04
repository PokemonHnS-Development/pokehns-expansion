#!/usr/bin/env python3
"""Write TESTING.md for one release candidate from its build and test outputs.

  make_testing_md.py RCDIR ROMNAME OUT.md [--notes NOTES.json]

RCDIR       the folder build_release.sh and run_release_tests.sh filled. It must also hold
            make_check.log (the output of `make check BUILD=hns`) and, for the visual-review
            row, visual_findings.json.
ROMNAME     the file name the ROM is published under, e.g. pokehns-he-2.0.6-0.2.gba.
--notes     the text that belongs to one release (known issues, visual review, static checks,
            what was not tested); default: notes.json next to this script. Its "release" must
            match ROMNAME (ROMNAME ends in -RELEASE.gba).

Environment:
  HNS_EN_MAPWALK  mapwalk.json of the map walk on the English ROM, which tells which held maps
                  also hold in English. Default: $HNS_WORK/mapwalk_en/mapwalk.json
                  (HNS_WORK: tools/hebrew/paths.py, default build/hebrew).

Exit status 2 when an input is missing, 1 when the inputs contradict a sentence of the report
(a failing self-check, a clipped or crashed label, a crashed map, a changed header, held maps
that notes.json does not explain, a save-ladder rung whose validation did not exit 0), 0 when
OUT.md was written.
"""
import argparse
import collections
import json
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
sys.path.insert(0, TOOLS)
import paths  # noqa: E402

CHECK_TESTS = os.path.join(TOOLS, 'check_tests.py')
EN_MAPWALK = os.environ.get('HNS_EN_MAPWALK', '').strip() or os.path.join(paths.WORK, 'mapwalk_en', 'mapwalk.json')
NOTE_KEYS = ('release', 'upstream_version', 'branch', 'toolchain', 'static_checks', 'visual_review',
             'crosscore_notes', 'map_walk', 'known_issues_intro', 'known_issues', 'not_tested')


def fail(code, problems):
    for p in problems:
        sys.stderr.write('make_testing_md.py: %s\n' % p)
    sys.exit(code)


def last_line(p):
    lines = open(p, errors='replace').read().strip().split('\n')
    return lines[-1].strip()


def main():
    ap = argparse.ArgumentParser(usage='make_testing_md.py RCDIR ROMNAME OUT.md [--notes NOTES.json]',
                                 description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('rc', metavar='RCDIR')
    ap.add_argument('romname', metavar='ROMNAME')
    ap.add_argument('out', metavar='OUT.md')
    ap.add_argument('--notes', default=os.path.join(HERE, 'notes.json'))
    a = ap.parse_args()
    RC, ROMNAME, OUT = a.rc, a.romname, a.out
    T = os.path.join(RC, 'tests')

    # -- inputs
    if not os.path.isdir(RC):
        fail(2, ['RCDIR %s is not a directory' % RC,
                 'usage: make_testing_md.py RCDIR ROMNAME OUT.md [--notes NOTES.json]'])
    need = {
        os.path.join(RC, 'build_info.json'): 'build_release.sh writes it',
        os.path.join(RC, 'gbafix.log'): 'build_release.sh writes it',
        os.path.join(RC, 'make_check.log'): 'the output of `make check BUILD=hns` on the release commit',
        os.path.join(T, 'tours', 'tour_report.json'): 'run_release_tests.sh writes it',
        os.path.join(T, 'tours_clip', 'tour_report.json'): 'run_release_tests.sh writes it',
        os.path.join(T, 'sweep', 'sweep.json'): 'run_release_tests.sh writes it',
        os.path.join(T, 'selfcheck.log'): 'run_release_tests.sh writes it',
        os.path.join(T, 'mapwalk', 'mapwalk.json'): 'run_release_tests.sh writes it',
        os.path.join(T, 'crosscore.txt'): 'run_release_tests.sh writes it',
        EN_MAPWALK: 'the map walk on the English ROM; set HNS_EN_MAPWALK (see README.md)',
        a.notes: 'the release notes data (--notes)',
        CHECK_TESTS: 'part of tools/hebrew',
    }
    missing = ['missing %s (%s)' % (p, why) for p, why in need.items() if not os.path.isfile(p)]
    if os.path.isdir(T) and not any(re.match(r'ladder_(ladder\d_\w+)\.log', f) for f in os.listdir(T)):
        missing.append('no ladder_*.log in %s (run_release_tests.sh writes them)' % T)
    if missing:
        fail(2, missing + ['usage: make_testing_md.py RCDIR ROMNAME OUT.md [--notes NOTES.json]'])
    notes = json.load(open(a.notes, encoding='utf-8'))
    absent = [k for k in NOTE_KEYS if k not in notes]
    if absent:
        fail(2, ['%s has no %s' % (a.notes, ', '.join(absent))])
    if not ROMNAME.endswith('-%s.gba' % notes['release']):
        fail(2, ['%s describes release %s, but ROMNAME is %s: update the notes for this release'
                 % (a.notes, notes['release'], ROMNAME)])

    info = json.load(open(os.path.join(RC, 'build_info.json')))
    tours = json.load(open(os.path.join(T, 'tours', 'tour_report.json')))['tours']
    ctours = json.load(open(os.path.join(T, 'tours_clip', 'tour_report.json')))['tours']
    sweep = json.load(open(os.path.join(T, 'sweep', 'sweep.json')))
    mw = json.load(open(os.path.join(T, 'mapwalk', 'mapwalk.json')))
    mwc = collections.Counter(r['status'] for r in mw)
    held = sorted(r['map'] for r in mw if r['status'] != 'OK')
    chk = subprocess.run([sys.executable, CHECK_TESTS, os.path.join(RC, 'make_check.log')],
                         capture_output=True, text=True).stdout.strip()
    cc = open(os.path.join(T, 'crosscore.txt')).read().strip()
    ladder, ladder_exit = {}, {}
    for f in sorted(os.listdir(T)):
        m = re.match(r'ladder_(ladder\d_\w+)\.log', f)
        if m:
            shots = len([x for x in os.listdir(os.path.join(T, 'ladder', m.group(1))) if x.endswith('.png')]) if os.path.isdir(os.path.join(T, 'ladder', m.group(1))) else 0
            ladder[m.group(1)] = shots
            ladder_exit[m.group(1)] = last_line(os.path.join(T, f))
    vis = os.path.exists(os.path.join(RC, 'visual_findings.json'))
    rom = info['pokehns.gba']; clip = info.get('pokehns-clip.gba', {})
    en_held = {r['map'] for r in json.load(open(EN_MAPWALK)) if r['status'] != 'OK'}
    both = [m for m in held if m in en_held]
    only = [m for m in held if m not in en_held]
    walk = notes['map_walk']

    # -- sentences below that are written as facts must hold for these inputs
    wrong = []
    if last_line(os.path.join(RC, 'gbafix.log')) != 'gbafix: header already valid':
        wrong.append('gbafix.log does not end in "gbafix: header already valid"; the report says gbafix changes nothing')
    if last_line(os.path.join(T, 'selfcheck.log')) != 'all checks passed':
        wrong.append('selfcheck.log does not end in "all checks passed"')
    for n, last in ladder_exit.items():
        if last != 'exit 0':
            wrong.append('ladder_%s.log does not end in "exit 0" (run_release_tests.sh appends the validation '
                         'script\'s exit status); the Save ladder row reports every rung as loaded' % n)
    bad_sweep = {k: v for k, v in sweep['summary'].items() if k not in ('OK', 'SKIP', 'warnings') and v}
    if bad_sweep:
        wrong.append('the sweep has %s; the report says 0 clipped' % bad_sweep)
    bad_walk = {k: v for k, v in mwc.items() if k not in ('OK', 'HELD')}
    if bad_walk:
        wrong.append('the map walk has %s; the report says 0 crashes' % bad_walk)
    if sorted(only) != sorted(walk.get('hebrew_only_held') or []):
        wrong.append('maps held in Hebrew but not in English are %s; notes map_walk.hebrew_only_held lists %s: '
                     'look at them and update the notes' % (only, walk.get('hebrew_only_held')))
    if vis and not notes['visual_review']:
        wrong.append('%s exists but the notes have no visual_review text' % os.path.join(RC, 'visual_findings.json'))
    if wrong:
        fail(1, wrong)

    L = []
    w = L.append
    w('# Testing report: %s\n' % ROMNAME)
    w('Pokémon Heart & Soul %s in Hebrew, built from `%s` commit `%s` of the source fork.\n' % (notes['upstream_version'], notes['branch'], info['commit']))
    w('## The file\n')
    w('| | Value |\n| --- | --- |')
    w('| File | `%s` |' % ROMNAME)
    w('| Size | %d bytes (32 MiB) |' % rom['size'])
    w('| SHA-1 | `%s` |' % rom['sha1'])
    w('| CRC32 | `%s` |' % rom['crc32'])
    w('| Header | `gbafix` changes nothing (the build already fixed it) |')
    w('| Built with | %s, `make clean && make hns` in a clean worktree of the commit above |' % notes['toolchain'])
    w('| Clip-report build (diagnostic only, not shipped) | SHA-1 `%s`, CRC32 `%s` |\n' % (clip.get('sha1', '?'), clip.get('crc32', '?')))
    w('Every test below ran on this exact file (or, where marked, on the clip-report build of the same commit).\n')
    w('## Results\n')
    w('| Step | What it does | Result |\n| --- | --- | --- |')
    w('| `make check` | the upstream test suite, built for hns | %s |' % chk.replace('\n', '; '))
    w('| Screen tours | %d scripted tours (battles, menus, bag, party, summary, Pokédex, PokéGear, PC, mart, naming screens with a Hebrew name typed, options, save) on the release ROM | %d OK of %d, %d screenshots |' % (len(tours), sum(1 for v in tours.values() if v['status'] == 'OK'), len(tours), sum(v.get('shots', 0) for v in tours.values())))
    w('| Clip-report tours | the same tours on the clip-report build, which logs every glyph drawn outside its window | %d OK of %d, %d glyphs outside a window |' % (sum(1 for v in ctours.values() if v['status'] == 'OK'), len(ctours), sum(v.get('clipped', 0) or 0 for v in ctours.values())))
    w('| Dialogue sweep | every reachable dialogue label rendered in the message box on the clip-report build, page by page | %s OK, %s skipped (labels not built into the ROM), 0 clipped |' % (sweep['summary'].get('OK'), sweep['summary'].get('SKIP')))
    w('| Map walk | warp into every Heart & Soul map from a post-game save, fight any battle, read any text | %d maps: %d OK, %d held, 0 crashes |' % (len(mw), mwc.get('OK', 0), mwc.get('HELD', 0)))
    w('| Save ladder | six saves (new game, badge 1, Ecruteak, League, Kanto, post-game) made with the **English** %s ROM, loaded in this ROM. Rung 1 (a new game in the bedroom): continue, bag, trainer card. Rungs 2-6: continue, walk out of the Pokémon Center, Pokédex, party, bag, trainer card, PokéGear | %s |' % (notes['upstream_version'], ', '.join('%s: %d screenshots' % kv for kv in ladder.items())))
    w('| Harness self-check | struct offsets the harness pokes, checked against the ELF and a live game | all checks passed |')
    w('| Cross-core | the same input on RetroArch\'s mGBA core and the VBA-M, VBA-Next, gpSP, Mednafen-GBA and SkyEmu libretro cores, frames compared with mGBA in RGB555, the GBA\'s own 15-bit colour | see below |')
    w('| Static checks | drift (only strings differ from the English engine baseline), layout audit (widths, lines, buffers, byte limits), glossary checks | %s |' % notes['static_checks'])
    if vis:
        w('| Visual review | every tour screenshot compared with the English build, side by side, by reviewers looking for clipping, overlap, mirroring, digit order, glyphs, English left and visible translation errors | %s |' % notes['visual_review'])
    w('')
    w('### Cross-core frames (pixels that differ from mGBA)\n')
    w('```\n%s\n```\n' % cc)
    w(notes['crosscore_notes'] + '\n')
    w('Held maps in the map walk: the game never gave control back within the frame budget, %s. %d of the %d also hold on the English ROM.%s\n' % (walk['held_reason'], len(both), len(held), (' The others (%s) %s.' % (', '.join('`%s`' % m for m in only), walk['hebrew_only_reason'])) if only else ''))
    w(', '.join('`%s`' % m for m in held) + '\n')
    w('## Known issues\n')
    if notes['known_issues_intro']:
        w(notes['known_issues_intro'] + '\n')
    for x in notes['known_issues']:
        w('- ' + x)
    w('')
    w('## Not tested\n')
    for x in notes['not_tested']:
        w('- ' + x)
    w('')
    open(OUT, 'w', encoding='utf-8').write('\n'.join(L))
    print('wrote', OUT)


if __name__ == '__main__':
    main()
