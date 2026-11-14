#!/usr/bin/env python3
"""Compare a `make check` log with the tests known to fail on upstream Heart & Soul.

  check_tests.py LOG [--known FILE] [--write-known]

Upstream 2.0.6 does not pass its own suite (its battle changes are ahead of the tests), so the
Hebrew build is held to "no test fails that passes upstream". A test is identified by its name
without the parameter suffix (" 2/3", " (1/2)") and label, because labels hold item names.
Exit status 1 if a test outside the known list fails, or if no results were found.
"""
import argparse, os, re, sys

HERE = os.path.dirname(os.path.abspath(__file__))
RESULT_RE = re.compile(r'^\[\d+\] (.*): (PASS|FAIL|TO_DO|KNOWN_FAILING|ASSUMPTION_FAIL|SKIP|ERROR|TIMEOUT|CRASH)\s*$')


def base_name(name):
    name = name.split(': (')[0].split(' ID:')[0].strip()
    return re.sub(r'( \d+/\d+)?( \(\d+/\d+\))?$', '', name)


def results(log):
    out = {}
    with open(log, 'rb') as f:
        for raw in f:
            line = re.sub(r'\x1b\[[0-9;]*m', '', raw.decode('utf-8', 'replace')).strip()
            m = RESULT_RE.match(line)
            if m:
                b = base_name(m.group(1))
                if m.group(2) in ('FAIL', 'ERROR', 'TIMEOUT', 'CRASH') or b not in out:
                    out[b] = m.group(2)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('log')
    ap.add_argument('--known', default=os.path.join(HERE, 'data', 'known_test_failures.txt'))
    ap.add_argument('--write-known', action='store_true', help='record the failures in LOG as the known list')
    a = ap.parse_args()
    res = results(a.log)
    if not res:
        print('no test results in %s' % a.log)
        return 1
    failing = sorted(t for t, s in res.items() if s in ('FAIL', 'ERROR', 'TIMEOUT', 'CRASH'))
    if a.write_known:
        with open(a.known, 'w', encoding='utf-8') as f:
            f.write('\n'.join(failing) + '\n')
        print('%d known failures written to %s' % (len(failing), a.known))
        return 0
    known = {l.strip() for l in open(a.known, encoding='utf-8') if l.strip()}
    new = [t for t in failing if t not in known]
    fixed = sorted(t for t in known if res.get(t) == 'PASS')
    print('%d results, %d failing, %d of them known upstream failures' % (len(res), len(failing), len(failing) - len(new)))
    if fixed:
        print('%d known failures now pass' % len(fixed))
    for t in new:
        print('NEW FAILURE: %s' % t)
    return 1 if new else 0


if __name__ == '__main__':
    sys.exit(main())
