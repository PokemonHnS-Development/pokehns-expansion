#!/usr/bin/env python3
"""Run the test suite like `make check`, in chunks of test names, so that it fits a CI runner.

  check_chunked.py [--build hns] [--jobs N] [--log check.log]

The emulator processes of one `make check` grow by several GB over the whole suite, more memory
than a hosted CI runner has. Each chunk is one run of the test runner with a test-name prefix as
its filter, so the processes start fresh and their memory is released between chunks.

Chunks are the first characters of the test names, split further where a name in
data/crashing_tests.txt falls in them: after a crash the runner rebuilds its share of the tests
without the name filter, so the crashing runner's later tests in that chunk would not run. Each
crashing test gets a chunk of its own. With --skip-crashing those chunks are not run: on Linux the
emulator does not report such a crash but keeps running and fills the memory.

The test ELF must already be built. The log can be read with check_tests.py, which judges the
results. Exit status 3 if a chunk ran past --chunk-timeout (a test that hangs or crashes the
emulator), 2 for a setup error, else 0.
"""
import argparse, os, re, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))
NAME_RE = re.compile(r'\b[A-Z_]*TEST\(\s*"((?:[^"\\]|\\.)*)"')


def test_names(root='test'):
    names = set()
    for d, _, files in os.walk(root):
        for f in files:
            if f.endswith('.c'):
                src = open(os.path.join(d, f), encoding='utf-8', errors='replace').read()
                for m in NAME_RE.finditer(src):
                    names.add(re.sub(r'\\(.)', lambda e: {'n': '\n', 't': '\t'}.get(e.group(1), e.group(1)), m.group(1)).encode('utf-8'))
    return names


def chunks(names, crashing, prefix=b''):
    """Prefixes that between them select every name once, with each crashing name alone."""
    inside = [n for n in names if n.startswith(prefix)]
    if prefix and not any(c.startswith(prefix) for c in crashing):
        return [prefix]
    if prefix in crashing:
        if len(inside) > 1:
            raise SystemExit('crashing test %r is a prefix of other test names' % prefix)
        return [prefix]
    if prefix in inside:
        raise SystemExit('test name %r is a prefix of other names in a chunk that has to be split' % prefix)
    out = []
    for c in sorted({n[len(prefix):len(prefix) + 1] for n in inside if len(n) > len(prefix)}):
        out += chunks(inside, crashing, prefix + c)
    return out


def patch_arg(prefix):
    return ''.join(chr(b) if (b < 0x80 and chr(b).isalnum()) or b == 0x20 else '\\x%02x' % b for b in prefix) + '\\0'


def make_vars(build):
    rule = ('print-check-vars:\n\t@echo "$(ROMTEST)|$(OBJCOPY)|$(ROMTESTHYDRA)|$(PATCHELF)|'
            '$(TESTELF)|$(HEADLESSELF)|$(TEST_SKIP_IS_FAIL)"\n')
    out = subprocess.run(['make', '--no-print-directory', '-s', 'BUILD=' + build, '-f', 'Makefile', '-f', '-',
                          'print-check-vars'], input=rule, capture_output=True, text=True, check=True).stdout
    return out.strip().split('|')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--build', default='hns')
    ap.add_argument('--jobs', type=int, default=2)
    ap.add_argument('--log', default='check.log')
    ap.add_argument('--crashing', default=os.path.join(HERE, 'data', 'crashing_tests.txt'))
    ap.add_argument('--skip-crashing', action='store_true', help='do not run the tests in --crashing')
    ap.add_argument('--chunk-timeout', type=int, default=0, help='seconds per chunk, 0 for none')
    a = ap.parse_args()

    romtest, objcopy, hydra, patchelf, testelf, headless, skipfail = make_vars(a.build)
    if not os.path.exists(testelf):
        print('%s is not built' % testelf)
        return 2
    names = test_names()
    starts = sorted({n[:1] for n in names})
    if b'*' in starts:
        print('a test name starts with *, which the runner reads as an infix filter')
        return 2
    crashing = {l.strip().encode('utf-8') for l in open(a.crashing, encoding='utf-8')
                if l.strip() and not l.startswith('#')}
    missing = sorted(c for c in crashing if c not in names)
    if missing:
        print('crashing tests not found in test/: %s' % ', '.join(m.decode() for m in missing))
        return 2
    plan = chunks(names, crashing)
    print('%d test names, %d chunks' % (len(names), len(plan)))
    if a.skip_crashing:
        plan = [p for p in plan if p not in crashing]
        for c in sorted(crashing):
            print('skipped, crashes the emulator: %s' % c.decode('utf-8'))

    status = 0
    env = dict(os.environ, MAKEFLAGS='-j%d' % a.jobs)
    with open(a.log, 'wb') as log:
        for p in plan:
            header = "== tests starting with '%s'\n" % p.decode('utf-8', 'replace')
            sys.stdout.write(header)
            sys.stdout.flush()
            log.write(header.encode('utf-8'))
            log.flush()
            subprocess.run(['cp', testelf, headless], check=True)
            subprocess.run([patchelf, headless, 'gTestRunnerArgv', patch_arg(p), 'gTestRunnerHeadless', '\\x01',
                            'gTestRunnerSkipIsFail', skipfail], check=True)
            try:
                subprocess.run([hydra, romtest, objcopy, headless], stdout=log, stderr=subprocess.STDOUT, env=env,
                               timeout=a.chunk_timeout or None)
            except subprocess.TimeoutExpired:
                msg = "== TIMEOUT: the tests starting with '%s' ran past %d s\n" % (p.decode('utf-8', 'replace'),
                                                                                  a.chunk_timeout)
                sys.stdout.write(msg)
                log.write(msg.encode('utf-8'))
                status = 3
    return status


if __name__ == '__main__':
    sys.exit(main())
