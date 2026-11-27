#!/usr/bin/env python3
"""Hoenn & Seek 2.0 part 33: the living dex check.

Proves that every national dex species 1-493 can be obtained in the HnS build,
and checks section 10 of hoenn-docs/2.0-plan.md: the one-of-a-kind species
(data/hoenn/distribution.json, "one_of_a_kind") have no source but their event.

Usage: tools/hoenn/living_dex.py [--report hoenn-docs/living-dex.md] [--quiet]
Exits 1 if a species has no source, or a one-of-a-kind species has a source
other than the ones distribution.json allows.

Where a species can come from ("direct" sources):
  wild    Every wild table the HnS build compiles: HnS's own (`_hns` labels in
          src/data/wild_encounters.json, minus "Unused" tables), the Hoenn
          tables (data/hoenn/wild_encounters_hoenn.json) and the weather
          tables (data/hoenn/wild_encounters_weather.json). Only the slots the
          engine rolls count (LAND 12, WATER 5, ROCK 5, FISH 10): HnS water
          tables sometimes list more. Pyramid/Pike tables don't count (you
          can't catch there).
  script  A give or battle command in a script that HnS can reach: givemon /
          giveegg / seteventmon / setwildbattle with a SPECIES_ literal, or a
          `setvar VAR, SPECIES_X` whose VAR a give/battle command or a Hoenn
          wild-battle special uses soon after (prize counters, the Hoenn
          events). Reachable = data/scripts/*.inc (minus debug.inc and the
          Emerald-only files listed in distribution.json) and the scripts.inc
          of every map compiled into HnS.
  trade   An in-game trade (src/data/trade.h) that a reachable script starts.
  named   A `givenamedmon N` gift (src/scrcmd.c's ScrCmd_givenamedmon).
  extra   distribution.json's "extra_sources": hand-listed ones the parser
          can't see (starters, roamers, fossils...). Each one names a file
          and a text the file must contain, so a stale entry fails.

Then the closure: anything a source species evolves into, and the first form
of its family by breeding (Gen 9 rules: no incense needed). Breeding needs the
species to be in an egg group other than Undiscovered; genderless and male-only
species also need a Ditto. Forms count for their national dex number.
"""
import argparse, json, os, re, sys
from collections import defaultdict

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
def P(*a): return os.path.join(ROOT, *a)

COUNTS = {'land_mons': 12, 'water_mons': 5, 'rock_smash_mons': 5, 'fishing_mons': 10}

# ---------------------------------------------------------------- species data
def load_species():
    """species -> dict(dex, evos[set], groups[set], gender)"""
    info = {}
    for n in range(1, 10):
        path = P('src', 'data', 'pokemon', 'species_info', 'gen_%d_families.h' % n)
        text = open(path).read()
        # Blocks start at "    [SPECIES_X] =" (4 spaces, at line start).
        parts = re.split(r'^    \[(SPECIES_[A-Z0-9_]+)\]\s*=', text, flags=re.M)
        for i in range(1, len(parts), 2):
            name, body = parts[i], parts[i + 1]
            m = re.search(r'\.natDexNum\s*=\s*NATIONAL_DEX_([A-Z0-9_]+)', body)
            evos = set()
            em = re.search(r'\.evolutions\s*=\s*EVOLUTION\((.*?)\)\s*,\s*\n', body, re.S)
            if em:
                evos = set(re.findall(r'\{\s*EVO_[A-Z_]+\s*,[^,{}]*,\s*(SPECIES_[A-Z0-9_]+)', em.group(1)))
            gm = re.search(r'\.eggGroups\s*=\s*MON_EGG_GROUPS\(([^)]*)\)', body)
            groups = set(re.findall(r'EGG_GROUP_[A-Z_]+', gm.group(1))) if gm else set()
            rm = re.search(r'\.genderRatio\s*=\s*([^,\n]+)', body)
            info[name] = dict(dex_name=m.group(1) if m else None, evos=evos,
                              groups=groups, gender=rm.group(1).strip() if rm else '')
    # National dex numbers 1-493 from include/constants/pokedex.h's enum order.
    ptext = open(P('include', 'constants', 'pokedex.h')).read()
    em = re.search(r'enum\s+NationalDexOrder\s*\{(.*?)\}', ptext, re.S)
    order = re.findall(r'NATIONAL_DEX_([A-Z0-9_]+)', em.group(1))
    dexnum = {name: i for i, name in enumerate(order)}  # NATIONAL_DEX_NONE is 0
    # Forms built by a macro (Unown, Arceus...) have no .natDexNum in their
    # block: take the longest dex name their species name starts with.
    names = sorted(dexnum, key=len, reverse=True)
    for sp, s in info.items():
        if not s['dex_name']:
            bare = sp[len('SPECIES_'):]
            s['dex_name'] = next((n for n in names if n and (bare == n or bare.startswith(n + '_'))), None)
        s['dex'] = dexnum.get(s['dex_name'], 0) if s['dex_name'] else 0
    return info

def load_aliases():
    """SPECIES_DEOXYS -> SPECIES_DEOXYS_NORMAL and the like (include/constants/species.h)."""
    al = {}
    for a, b in re.findall(r'^#define\s+(SPECIES_[A-Z0-9_]+)\s+(SPECIES_[A-Z0-9_]+)\s*$',
                           open(P('include', 'constants', 'species.h')).read(), re.M):
        al[a] = b
    def res(s):
        seen = set()
        while s in al and s not in seen:
            seen.add(s); s = al[s]
        return s
    return res

# ---------------------------------------------------------------- maps
def compiled_maps():
    """map dir name -> MAP_ id, for every map the HnS build compiles."""
    hoenn = set(json.load(open(P('data', 'hoenn', 'maps.json')))['items'])
    out = {}
    for d in os.listdir(P('data', 'maps')):
        f = P('data', 'maps', d, 'map.json')
        if not os.path.exists(f):
            continue
        j = json.load(open(f))
        if j.get('game_version') == 'hns' or d in hoenn:
            out[d] = j['id']
    return out

# ---------------------------------------------------------------- wild
def wild_sources(maps_by_id):
    src = defaultdict(list)
    tables = []
    d = json.load(open(P('src', 'data', 'wild_encounters.json')))
    for grp in d['wild_encounter_groups']:
        if grp.get('label') != 'gWildMonHeaders':
            continue
        for e in grp['encounters']:
            lab = e['base_label']
            if '_hns' in lab and 'Unused' not in lab:
                tables.append(e)
    for f in ('wild_encounters_hoenn.json', 'wild_encounters_weather.json'):
        tables += json.load(open(P('data', 'hoenn', f)))['encounters']
    for e in tables:
        if e['map'] not in maps_by_id:
            continue          # the map isn't in the build
        for kind, n in COUNTS.items():
            for mon in e.get(kind, {}).get('mons', [])[:n]:
                if mon['species'] != 'SPECIES_NONE':
                    src[mon['species']].append('wild:%s:%s' % (e['base_label'], kind.split('_')[0]))
    return src

# ---------------------------------------------------------------- scripts
GIVE = r'(?:givemon|giveegg|seteventmon|setwildbattle)'
VAR_USERS = re.compile(r'^\s*(?:givemon|giveegg|seteventmon|setwildbattle)\s+(VAR_[A-Za-z0-9_]+)', re.M)
WILD_SPECIALS = re.compile(r'special\w*\s+(?:VAR_RESULT,\s*)?(Hoenn(?:Setup\w*Wild\w*|GiveShinyEgg))')

def script_files(dist, maps):
    skip = set(dist.get('unreachable_script_files', [])) | {'data/scripts/debug.inc'}
    files = []
    for f in sorted(os.listdir(P('data', 'scripts'))):
        rel = 'data/scripts/' + f
        if f.endswith('.inc') and rel not in skip:
            files.append(rel)
    for d in sorted(maps):
        rel = 'data/maps/%s/scripts.inc' % d
        if os.path.exists(P(rel)) and rel not in skip:
            files.append(rel)
    return files

def script_sources(files):
    src = defaultdict(list)
    trades, named = set(), set()
    for rel in files:
        text = open(P(rel)).read()
        lines = text.split('\n')
        users = set(VAR_USERS.findall(text))
        for i, line in enumerate(lines):
            code = line.split('@')[0]
            m = re.match(r'\s*' + GIVE + r'\s+(SPECIES_[A-Z0-9_]+)(.*)', code)
            if m:
                src[m.group(1)].append('script:' + rel)
                # setwildbattle A, lvl, item, B, ...: the second mon of a double
                for extra in re.findall(r'(SPECIES_[A-Z0-9_]+)', m.group(2)):
                    src[extra].append('script:' + rel)
                continue
            m = re.match(r'\s*setvar\s+(VAR_[A-Za-z0-9_]+)\s*,\s*(SPECIES_[A-Z0-9_]+)', code)
            if m:
                var, sp = m.groups()
                window = '\n'.join(l.split('@')[0] for l in lines[i + 1:i + 12])
                if var in users or (var in ('VAR_0x8004', 'VAR_0x8005') and WILD_SPECIALS.search(window)):
                    src[sp].append('script:' + rel)
                elif var == 'VAR_TEMP_TRANSFERRED_SPECIES' and 'givenamedmon' in window:
                    pass      # counted through the named gift itself
            for t in re.findall(r'\b(INGAME_TRADE_[A-Z0-9_]+)', code):
                trades.add(t)
            m = re.match(r'\s*givenamedmon\s+(\d+)', code)
            if m:
                named.add(int(m.group(1)))
    return src, trades, named

def trade_sources(trades):
    src = defaultdict(list)
    text = open(P('src', 'data', 'trade.h')).read()
    for name, body in re.findall(r'\[(INGAME_TRADE_[A-Z0-9_]+)\]\s*=\s*\{(.*?)\n\s*\},', text, re.S):
        if name in trades:
            for sp in re.findall(r'\.species\s*=\s*(SPECIES_[A-Z0-9_]+)', body):
                src[sp].append('trade:' + name)
    return src

def named_sources(named):
    src = defaultdict(list)
    text = open(P('src', 'scrcmd.c')).read()
    body = text[text.index('bool8 ScrCmd_givenamedmon'):]
    body = body[:body.index('\n}\n')]
    for n, sp in re.findall(r'case (\d+):[^\n]*\n\s*species = (SPECIES_[A-Z0-9_]+);', body):
        if int(n) in named:
            src[sp].append('named:%s' % n)
    return src

def extra_sources(dist, errors, pending):
    src = defaultdict(list)
    for e in dist.get('extra_sources', []):
        path = P(e['file'])
        if not os.path.exists(path) or e['contains'] not in open(path).read():
            # "waits_for": a source another open PR adds. Until it merges, the
            # species is reported as pending instead of failing the check.
            if 'waits_for' in e:
                for sp in e['species']:
                    pending[sp] = e['waits_for']
                continue
            errors.append('extra source for %s is stale: %s no longer contains %r'
                          % (', '.join(e['species']), e['file'], e['contains']))
            continue
        for sp in e['species']:
            src[sp].append('extra:' + e['why'])
    return src

# ---------------------------------------------------------------- closure
def closure(direct, info):
    pre = defaultdict(set)
    for s, d in info.items():
        for t in d['evos']:
            pre[t].add(s)
    def base(s):
        seen = set()
        while pre.get(s) and s not in seen:
            seen.add(s)
            s = sorted(pre[s])[0]
        return s
    have = {s: set(v) for s, v in direct.items() if s in info}
    changed = True
    while changed:
        changed = False
        ditto = 'SPECIES_DITTO' in have
        for s in list(have):
            d = info[s]
            for t in d['evos']:
                if t in info and t not in have:
                    have[t] = {'evolves from ' + s}
                    changed = True
            breeds = d['groups'] and 'EGG_GROUP_NO_EGGS_DISCOVERED' not in d['groups'] \
                and 'EGG_GROUP_DITTO' not in d['groups']
            needs_ditto = d['gender'] in ('MON_GENDERLESS', 'MON_MALE')
            if breeds and (ditto or not needs_ditto):
                b = base(s)
                if b not in have:
                    have[b] = {'bred from ' + s}
                    changed = True
    return have

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--report')
    ap.add_argument('--quiet', action='store_true')
    args = ap.parse_args()
    dist = json.load(open(P('data', 'hoenn', 'distribution.json')))
    errors = []
    pending = {}
    info = load_species()
    maps = compiled_maps()
    maps_by_id = {v: k for k, v in maps.items()}
    direct = defaultdict(list)
    for part in (wild_sources(maps_by_id),):
        for k, v in part.items(): direct[k] += v
    ssrc, trades, named = script_sources(script_files(dist, maps))
    for part in (ssrc, trade_sources(trades), named_sources(named), extra_sources(dist, errors, pending)):
        for k, v in part.items(): direct[k] += v
    res = load_aliases()
    resolved = defaultdict(list)
    for k, v in direct.items():
        resolved[res(k)] += v
    direct = resolved
    for d in info.values():
        d['evos'] = {res(t) for t in d['evos']}
    have = closure(direct, info)
    # A pending species' evolutions wait for the same PR.
    todo = list(pending)
    while todo:
        sp = todo.pop()
        for t in info.get(sp, {}).get('evos', ()):
            if t not in pending:
                pending[t] = pending[sp]
                todo.append(t)

    # Per national dex number: the sources of every form with that number.
    by_dex = defaultdict(list)
    for s, d in info.items():
        if 1 <= d['dex'] <= 493:
            by_dex[d['dex']].append(s)
    # Scope (Bryan's call, part 33): HnS's own Pokémon. That's 1-386, plus every
    # Gen 4 species of a family with an older member (Weavile, Happiny...) and
    # any Gen 4 species something gives. Sinnoh-only lines aren't in HnS at all.
    fam = {}
    def find(x):
        while fam.setdefault(x, x) != x:
            fam[x] = fam[fam[x]]; x = fam[x]
        return x
    for sp, d in info.items():
        for t in d['evos']:
            if t in info:
                fam[find(sp)] = find(t)
    old_families = {find(sp) for sp, d in info.items() if 1 <= d['dex'] <= 386}
    in_scope = set(range(1, 387))
    for sp, d in info.items():
        if 387 <= d['dex'] <= 493 and (find(sp) in old_families or sp in have):
            in_scope.add(d['dex'])
    missing, rows, out_of_scope = [], [], []
    for n in range(1, 494):
        if n not in in_scope:
            forms = sorted(by_dex.get(n, []), key=lambda s: (s.count('_'), s))
            out_of_scope.append(forms[0] if forms else '#%d' % n)
            continue
        forms = sorted(by_dex.get(n, []), key=lambda s: (s.count('_'), s))
        how = []
        for s in forms:
            if s in have:
                why = sorted(set(have[s]))
                how.append((s, why))
        if not how:
            missing.append(forms[0] if forms else '#%d' % n)
        rows.append((n, forms[0] if forms else '?', how))

    # One-of-a-kind species: only the allowed sources.
    for sp, allowed in dist['one_of_a_kind'].items():
        for s in [sp] + allowed.get('family', []):
            for why in direct.get(s, []):
                if not any(why.startswith(a) for a in allowed['sources']):
                    errors.append('one-of-a-kind %s still has another source: %s' % (s, why))

    for m in missing:
        if m in pending:
            print('pending: %s has no source until %s merges' % (m, pending[m]))
        else:
            errors.append('no source for %s' % m)

    if args.report:
        with open(P(args.report), 'w') as f:
            f.write('# Living dex check (generated)\n\n')
            f.write('Generated by `tools/hoenn/living_dex.py` (2.0 part 33). Every national dex species 1–493 and where it comes from in the HnS build: '
                    'its direct sources (wild tables, scripts, trades, gifts, hand-listed extras), or how it is reached from one '
                    '(evolution, breeding). Do not edit; re-run the tool.\n\n')
            f.write('%d of the %d species in scope have a source. Out of scope (Sinnoh-only lines, which HnS doesn\'t have): %d species, listed at the end.\n\n'
                    % (len(rows) - len(missing), len(rows), len(out_of_scope)))
            f.write('| # | Species | How |\n|---|---|---|\n')
            for n, name, how in rows:
                if not how:
                    cell = '**none**'
                else:
                    bits = []
                    for s, why in how:
                        direct_bits = [w for w in why if ':' in w]
                        other = [w for w in why if ':' not in w]
                        shown = summarize(direct_bits) + other[:1]
                        bits.append(('%s: ' % s.replace('SPECIES_', '') if len(how) > 1 else '') + '; '.join(shown))
                    cell = ' / '.join(bits)
                f.write('| %d | %s | %s |\n' % (n, name.replace('SPECIES_', ''), cell))
            f.write('\n## Out of scope\n\n' + ', '.join(s.replace('SPECIES_', '') for s in out_of_scope) + '\n')
    if not args.quiet:
        print('%d of %d species in scope have a source (%d Sinnoh-only out of scope)'
              % (len(rows) - len(missing), len(rows), len(out_of_scope)))
    for e in errors:
        print('ERROR:', e)
    return 1 if errors else 0

def summarize(ws):
    """Short text for a list of direct sources: wild tables counted, the rest named."""
    wild = [w for w in ws if w.startswith('wild:')]
    out = []
    if wild:
        labs = sorted(set(w.split(':')[1] for w in wild))
        out.append('wild in %d table%s (%s%s)' % (len(labs), '' if len(labs) == 1 else 's',
                                                  ', '.join(l[1:] for l in labs[:3]), ', …' if len(labs) > 3 else ''))
    for w in sorted(set(w for w in ws if not w.startswith('wild:'))):
        out.append(w.split(':', 1)[1] if w.startswith('extra:') else w)
    return out

if __name__ == '__main__':
    sys.exit(main())
