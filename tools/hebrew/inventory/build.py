#!/usr/bin/env python3
"""Build the translation inventory: live_labels.json, inventory.json and c_strings.json.

  build.py --release ROM [--std ROM] [--src TREE] [--out DIR] [--es-ref REF] [--elf ELF]
           [--no-gates] [--compare]

The strings are counted in the English source tree (TREE, default HNS_UPSTREAM) and their
liveness is read from two builds of that tree: a release build (ROM, with its .elf and .map next
to it; `make release`) and a standard build (default TREE/pokehns.gba). Steps, all writing to DIR
(default $HNS_WORK/inventory):

  1. extract.py        script labels and C literals, reachability from the ROM words
                       (asm_strings.json, asm_roots.json, asm_reach.json, asm_parents.json,
                       c_strings.json)
  2. fr_style_graph.py the French fork's map traversal, for comparison (fr_style_graph.json)
  3. mapgraph2.py      which H&S maps the player can reach (mapgraph2.json)
  4. build_inventory   inventory.json, live_labels.json, batches.json
  5. flag_gates.py     takes flag-gated and unbuilt labels out of live_labels.json (--elf, default
                       the release ELF; see flag_gates.py)

es_touched in inventory.json marks the files the Spanish fork changed: `git diff --name-only
167aa6d537...REF` in this repository (default REF 268113861f, es/master as used for the shipped
inventory). Without that commit every file is marked untouched.

--no-gates stops after step 4 (the reference graph alone). --compare reports whether the three
outputs equal tools/hebrew/data's. Needs numpy and
devkitARM's arm-none-eabi-nm (DEVKITARM, default /opt/devkitpro/devkitARM).
"""
import argparse
import os
import runpy
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
sys.path.insert(0, HERE)
sys.path.insert(0, TOOLS)
import invconfig  # noqa: E402
import paths  # noqa: E402

EN_BASE = '167aa6d537'
OUTPUTS = ('live_labels.json', 'inventory.json', 'c_strings.json')


def build_triple(rom):
    base = os.path.splitext(os.path.abspath(rom))[0]
    triple = (base + '.gba', base + '.elf', base + '.map')
    missing = [p for p in triple if not os.path.isfile(p)]
    if missing:
        raise SystemExit('build.py: missing %s' % ', '.join(missing))
    return triple


def es_files(ref):
    r = subprocess.run(['git', '-C', paths.REPO, 'diff', '--name-only', '%s...%s' % (EN_BASE, ref)],
                       capture_output=True, text=True)
    if r.returncode != 0:
        sys.stderr.write('build.py: no Spanish fork commit %s here, so no file is marked es_touched\n' % ref)
        return set()
    return set(r.stdout.split())


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    ap.add_argument('--src', default=paths.UPSTREAM, help='English source tree (default HNS_UPSTREAM)')
    ap.add_argument('--release', required=True, help='release-build ROM of that tree (.elf and .map next to it)')
    ap.add_argument('--std', help='standard-build ROM of that tree (default TREE/pokehns.gba)')
    ap.add_argument('--out', default=os.path.join(paths.WORK, 'inventory'))
    ap.add_argument('--es-ref', default='268113861f')
    ap.add_argument('--elf', help='ELF for flag_gates.py --elf (default the release ELF)')
    ap.add_argument('--no-gates', action='store_true', help='stop before flag_gates.py')
    ap.add_argument('--compare', action='store_true', help='compare the outputs with tools/hebrew/data')
    a = ap.parse_args(argv)
    if not a.src or not os.path.isdir(a.src):
        raise SystemExit('build.py: no English source tree; set HNS_UPSTREAM or --src')
    devkit = os.environ.get('DEVKITARM', '/opt/devkitpro/devkitARM')
    invconfig.SRC = os.path.abspath(a.src)
    invconfig.OUT = os.path.abspath(a.out)
    invconfig.NM = os.path.join(devkit, 'bin', 'arm-none-eabi-nm')
    invconfig.BUILDS = {'release': build_triple(a.release),
                        'std': build_triple(a.std or os.path.join(a.src, 'pokehns.gba'))}
    invconfig.ES_FILES = es_files(a.es_ref)
    os.makedirs(invconfig.OUT, exist_ok=True)
    for step in ('extract.py', 'fr_style_graph.py', 'mapgraph2.py', 'build_inventory.py'):
        print('== %s' % step, flush=True)
        runpy.run_path(os.path.join(HERE, step), run_name='__main__')
    code = 0
    if not a.no_gates:
        print('== flag_gates.py', flush=True)
        import flag_gates
        code = flag_gates.main(['--write', '--tree', invconfig.SRC, '--elf', a.elf or invconfig.BUILDS['release'][1],
                                '--labels', os.path.join(invconfig.OUT, 'live_labels.json'),
                                '--inventory', os.path.join(invconfig.OUT, 'inventory.json')])
    if code:
        return code
    if a.compare:
        differ = 0
        for name in OUTPUTS:
            with open(os.path.join(invconfig.OUT, name), 'rb') as f1, open(os.path.join(paths.DATA, name), 'rb') as f2:
                same = f1.read() == f2.read()
            print('%-17s %s' % (name, 'identical to tools/hebrew/data' if same else 'DIFFERS from tools/hebrew/data'))
            differ += not same
        return 1 if differ else 0
    return 0


if __name__ == '__main__':
    sys.exit(main())
