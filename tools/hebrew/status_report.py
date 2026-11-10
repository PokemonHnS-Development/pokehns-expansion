#!/usr/bin/env python3
"""Write translation/hebrew/STATUS.md: one row per source file that holds player-visible text.

  status_report.py [--sweep SWEEP.json] [--out FILE]

States, as the brief defines them: to do (some live string still English), translated (every live
string Hebrew), seen on screen (translated, and every live dialogue label of the file was rendered
by the dialogue sweep with no glyph outside its window), blocked (kept in English on purpose, with
the reason: the R+START debug menu). C files are never marked seen on screen here: the sweep
renders script text only, and which C strings the screen tours showed is not tracked per string.
"""
import argparse, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402
import units as U  # noqa: E402

BLOCKED = {
    'src/debug.c': 'debug menu, English by design',
}
# Files whose remaining Latin is deliberate, and why.
KEPT_LATIN = {
    'src/data/credits_hns.h': 'the names of people, teams and organisations, and the game titles',
    'src/data/help_window.h': 'the game title Heart & Soul and the abbreviation IV',
    'src/save_failed_screen.c': 'the emulator save type (Flash 1Mb/128K), its name for the memory, and ROM',
    'src/data/battle_frontier/apprentice.h': "the other languages' name columns; the English column is Hebrew",
    'src/scrcmd.c': "the Odd Egg name list, which the game compares with the player's typed name",
    'src/text_input_strings.c': 'the Latin keyboard layouts, and the English rows of the Easy Chat keyboard, which the Hebrew build does not print',
    'src/naming_screen.c': 'the Latin keyboard layouts',
    'src/option_menu.c': 'button names (L, R, A, B)',
    'src/start_menu.c': 'the debug entry and AM/PM (the clock is 24-hour)',
    'src/rtc.c': 'AM/PM (the clock is 24-hour)',
    'src/strings.c': 'button names, abbreviations (BP), unit placeholders and Emerald-only names',
    'src/challenge_menu.c': 'multipliers (x1.5) and numbers',
    'src/trainer_tower_sets.c': 'Trainer Tower data, which Heart & Soul cannot reach',
    'src/pokenav_match_call_data.c': 'Emerald PokéNav contacts, replaced by the PokéGear in Heart & Soul',
    'src/data/script_menu.h': 'Emerald ferry destinations and BP amounts',
    'src/berry_fix_program.c': 'the Ruby/Sapphire berry-fix program',
    'data/scripts/config.inc': 'a developer configuration message',
    'data/scripts/debug.inc': 'the R+START debug menu',
    'src/field_weather.c': 'a debug message',
    'src/item.c': 'the English plural suffix, unused in the Hebrew build',
    'src/contest.c': 'contest debug labels',
    'src/field_specials.c': 'a mystery-gift sample code the game compares',
    'src/battle_main.c': 'a code comment',
}
HEB = re.compile(r'[֐-׿]')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--sweep', help='sweep.json of the release candidate')
    ap.add_argument('--out', default=os.path.join(paths.TRANSLATION, 'STATUS.md'))
    a = ap.parse_args()
    inv = json.load(open(paths.INVENTORY))
    swept = {}
    if a.sweep:
        for r in json.load(open(a.sweep))['results']:
            for f in r.get('files', []):
                swept.setdefault(f, {})[r['label']] = r['status'] == 'OK' and not r.get('clips')
    rows = []
    for item in sorted(inv, key=lambda i: i['file']):
        f = item['file']
        if not item.get('strings_live') or not os.path.exists(os.path.join(paths.TREE, f)):
            continue
        if not f.endswith(('.inc', '.s', '.c', '.h')):
            continue
        reason = next((r for p, r in BLOCKED.items() if f.startswith(p)), None)
        try:
            us = [u for u in U.extract([f], paths.TREE, False) if u.get('live', True)]
        except Exception as e:
            rows.append((f, '?', '?', 'error: %s' % e)); continue
        if not us:
            continue
        # A unit needs Hebrew only if it holds a Latin word (not punctuation, a single letter or a
        # control code such as \\p).
        us = [u for u in us if HEB.search(u['en']) or re.search(r'[A-Za-z]{2,}', U.TOKEN_RE.sub('', u['en']).replace('\\n', ' ').replace('\\l', ' ').replace('\\p', ' '))]
        if not us:
            continue
        heb = sum(1 for u in us if HEB.search(u['en']))
        total = len(us)
        if reason:
            state = 'blocked (%s)' % reason
        elif heb < total and f in KEPT_LATIN:
            state = 'translated (%d kept in Latin: %s)' % (total - heb, KEPT_LATIN[f])
        elif heb < total:
            state = 'to do (%d still English)' % (total - heb)
        elif f.endswith(('.inc', '.s')) and f in swept:
            labels = {u['key'].split('#')[0] for u in us}
            seen = [l for l in labels if swept[f].get(l)]
            state = 'seen on screen' if len(seen) == len(labels) else 'translated (%d of %d labels seen)' % (len(seen), len(labels))
        else:
            state = 'translated'
        rows.append((f, total, heb, state))
    counts = {}
    for r in rows:
        k = r[3].split(' (')[0]
        counts[k] = counts.get(k, 0) + 1
    with open(a.out, 'w', encoding='utf-8') as o:
        o.write('# Translation status\n\nGenerated by `tools/hebrew/status_report.py`. A string counts once per unit (a script '
                'label or a C literal) that the game can reach. "Seen on screen" means the harness rendered it (the '
                'dialogue sweep), not a person.\n\n')
        o.write(' | '.join('%s: %d' % kv for kv in sorted(counts.items())) + '\n\n')
        o.write('| File | Live strings | Hebrew | State |\n| --- | --- | --- | --- |\n')
        for f, t, h, s in rows:
            o.write('| `%s` | %s | %s | %s |\n' % (f, t, h, s))
    print('%d files -> %s: %s' % (len(rows), a.out, counts))


if __name__ == '__main__':
    main()
