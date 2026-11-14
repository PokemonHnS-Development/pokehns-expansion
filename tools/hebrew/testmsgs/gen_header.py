"""Write test/hebrew_battle_messages.h from table.json (+ composed.json if present)."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402
import json, os, re, sys
d = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'data')
table = json.load(open(os.path.join(d, 'table.json')))
if os.path.exists(os.path.join(d, 'composed.json')):
    for k, v in json.load(open(os.path.join(d, 'composed.json'))).items():
        table.setdefault(k, v)
rows = sorted(table.items())
def esc(s):
    return s.replace('\\"', '"').replace('"', '\\"') if '\\"' not in s else s
lines = ['// English battle messages the battle tests expect, and the Hebrew the game prints for them.',
         '// Generated from the messages both builds print in the same test runs.',
         '']
for en, he in rows:
    lines.append('    { _("%s"), _("%s") },' % (en, he))
out = sys.argv[1]
open(out, 'w', encoding='utf-8').write('\n'.join(lines) + '\n')
print(len(rows), 'entries ->', out)
