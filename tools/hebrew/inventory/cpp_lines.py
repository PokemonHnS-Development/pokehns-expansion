#!/usr/bin/env python3
"""Which source lines of a tree the C preprocessor keeps in a build of that tree.

  cpp_lines.py [--tree TREE] [--release] [--gcc GCC] FILE [FILE ...]

prints, for each FILE (relative to TREE, default HNS_UPSTREAM), the lines the build keeps, as
ranges. A line is kept when it lies outside every #if branch the build leaves out, in a file one
of the build's translation units includes.

The flags are the tree's own: the Makefile's CPPFLAGS for an `hns` build, plus what the Makefile
adds for RELEASE=1 with --release (makefile_cppflags). The translation units are the Makefile's C
sources (c_sources). Each goes through `arm-none-eabi-gcc -E -fdirectives-only`, which evaluates
#if, #include and #define as the build does but expands no macro, so every kept line comes out as
written under its own line number, and a literal spread over several lines stays where it starts.
A header counts once for every unit that includes it: a line is kept if any unit keeps it.

The units include the headers the build generates, so TREE must be built (`make hns`); a unit that
does not preprocess stops the run with gcc's message. Needs devkitARM (DEVKITARM).
"""
import argparse
import concurrent.futures
import glob
import os
import re
import shutil
import subprocess
import sys

# gcc indents a line marker in -fdirectives-only output like the directive it replaces.
MARKER_RE = re.compile(r'^[ \t]*# (\d+) "((?:[^"\\\n]|\\.)*)"(?: \d+)*$', re.M)
LINE_DIRECTIVE_RE = re.compile(r'^[ \t]*#[ \t]*line\b', re.M)
COND_DIRECTIVE_RE = re.compile(r'^[ \t]*#[ \t]*(?:if|ifdef|ifndef|elif|else)\b', re.M)
COND_RE = re.compile(r'^\s*(ifeq|ifneq|ifdef|ifndef)\b(.*)$')
ASSIGN_RE = re.compile(r'^\s*(?:override\s+)?CPPFLAGS\s*(:=|\+=|=)\s*(.*?)\s*$')
# Any assignment to a variable the flags are made of, in every form make accepts (for one target,
# exported, ?=, !=, ::=): makefile_cppflags stops on one it does not read.
FLAG_VAR_ASSIGN_RE = re.compile(r'(?<!\w)(?:CPPFLAGS|INCLUDE_DIRS|INCLUDE_CPP_ARGS)\s*(?:\+|\?|!|:{1,3})?=')
# The values an `hns` build of the English tree gives the Makefile variables CPPFLAGS uses.
HNS_VARS = {'TEST': '0', 'GAME_VERSION': 'POKEMON_HNS'}
INCLUDE_ARGS_RULE = '$(INCLUDE_DIRS:%=-iquote %)'
RELEASE_COND = 'ifeq($(RELEASE),1)'
# The switches of the fork's diagnostic builds (make hns RTL_CLIP_REPORT=1 ...), off in `make hns`.
OFF_CONDS = ('ifeq($(RTL_CLIP_REPORT),1)', 'ifeq($(RTL_STRING_REPORT),1)')
# How the Makefile lists the C sources it compiles; c_sources repeats it.
C_SRCS_LINES = ('C_SRCS_IN := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)',
                'C_SRCS := $(foreach src,$(C_SRCS_IN),$(if $(findstring .inc.c,$(src)),,$(src)))',
                'C_SUBDIR = src')


def default_gcc():
    """devkitARM's arm-none-eabi-gcc (DEVKITARM), else the one on PATH."""
    devkit = os.path.join(os.environ.get('DEVKITARM', '/opt/devkitpro/devkitARM'), 'bin', 'arm-none-eabi-gcc')
    return devkit if os.path.exists(devkit) else (shutil.which('arm-none-eabi-gcc') or devkit)


def makefile_cppflags(makefile, release):
    """The preprocessor flags the Makefile text MAKEFILE gives an `hns` build's C sources, as a list:
    the CPPFLAGS assignment, plus the additions under `ifeq ($(RELEASE),1)` when RELEASE (none under
    OFF_CONDS). Stops on anything it cannot resolve, rather than guess: a variable other than
    INCLUDE_CPP_ARGS and those of HNS_VARS, a CPPFLAGS change under another condition, or any other
    assignment to CPPFLAGS, INCLUDE_DIRS or INCLUDE_CPP_ARGS (for one target, exported, ?=)."""
    values = dict(HNS_VARS)
    flags, added, stack, dirs = None, [], [], None
    for n, line in enumerate(makefile.split('\n'), 1):
        line = line.split('#', 1)[0]
        m = COND_RE.match(line)
        if m:
            stack.append(m.group(1) + re.sub(r'\s+', '', m.group(2)))
            continue
        if re.match(r'^\s*else\b', line) and stack:
            stack[-1] = 'else ' + stack[-1]
            continue
        if re.match(r'^\s*endif\b', line) and stack:
            stack.pop()
            continue
        m = re.match(r'^\s*(INCLUDE_DIRS|INCLUDE_CPP_ARGS)\s*:?=\s*(.*?)\s*$', line)
        if m and not stack:
            if m.group(1) == 'INCLUDE_DIRS':
                dirs = m.group(2).split()
            elif m.group(2) == INCLUDE_ARGS_RULE and dirs is not None:
                values['INCLUDE_CPP_ARGS'] = ' '.join('-iquote ' + d for d in dirs)
            else:
                raise SystemExit('cpp_lines: Makefile:%d: INCLUDE_CPP_ARGS is not %s after INCLUDE_DIRS'
                                 % (n, INCLUDE_ARGS_RULE))
            continue
        m = ASSIGN_RE.match(line)
        if not m:
            if FLAG_VAR_ASSIGN_RE.search(line):
                raise SystemExit('cpp_lines: Makefile:%d: cannot read %r; teach makefile_cppflags '
                                 'what it does' % (n, line.strip()))
            continue
        resolved = re.sub(r'\$\((\w+)\)', lambda v: values.get(v.group(1), v.group(0)), m.group(2))
        if '$' in resolved:
            raise SystemExit('cpp_lines: Makefile:%d: cannot resolve %r' % (n, m.group(2)))
        if m.group(1) != '+=' and not stack:
            flags = resolved.split()
        elif m.group(1) == '+=' and stack == [RELEASE_COND]:
            added += resolved.split()
        elif m.group(1) == '+=' and len(stack) == 1 and stack[0] in OFF_CONDS:
            pass
        else:
            raise SystemExit('cpp_lines: Makefile:%d: CPPFLAGS changes under %s; teach makefile_cppflags '
                             'which builds that is' % (n, ' / '.join(stack) or 'no condition'))
    if flags is None:
        raise SystemExit('cpp_lines: the Makefile assigns no CPPFLAGS')
    return flags + (added if release else [])


def c_sources(tree):
    """The C sources the tree's Makefile compiles (relative paths): src/*.c, src/*/*.c and
    src/*/*/*.c without the *.inc.c files. Stops if the Makefile lists them another way."""
    with open(os.path.join(tree, 'Makefile'), encoding='utf-8', errors='replace') as f:
        lines = {re.sub(r'\s+', ' ', l.strip()) for l in f}
    missing = [l for l in C_SRCS_LINES if l not in lines]
    if missing:
        raise SystemExit('cpp_lines: the Makefile no longer says %r; update c_sources' % missing[0])
    out = []
    for pattern in ('src/*.c', 'src/*/*.c', 'src/*/*/*.c'):
        out += [os.path.relpath(p, tree) for p in glob.glob(os.path.join(tree, pattern))]
    return sorted(p for p in out if '.inc.c' not in p)


def kept_lines(output, wanted=None):
    """{file: {line number: text}} of the lines with text in OUTPUT, the output of `gcc -E
    -fdirectives-only`, by the file names and numbers its line markers give. WANTED, a set of
    names, limits the result to those files."""
    kept = {}
    marks = list(MARKER_RE.finditer(output))
    for i, m in enumerate(marks):
        name = os.path.normpath(m.group(2).replace('\\\\', '\\').replace('\\"', '"'))
        if wanted is not None and name not in wanted:
            continue
        end = marks[i + 1].start() if i + 1 < len(marks) else len(output)
        keep = kept.setdefault(name, {})
        first = int(m.group(1))
        for k, text in enumerate(output[m.end() + 1:end].split('\n')):
            if text.strip():
                keep[first + k] = text.strip()
    return kept


def check_in_step(tree, kept):
    """Stop unless every kept line of a tree file holds the text of the source line its number
    names (a directive gcc prints itself, such as #define, aside): a line marker the parser
    missed would shift every later line. Only C files are checked, and not those with a #line
    directive (verdicts does not use their numbers): the files such a directive names (a .party
    file) are not what the preprocessor read."""
    for name, lines in kept.items():
        if os.path.isabs(name) or not name.endswith(('.c', '.h')):
            continue
        try:
            with open(os.path.join(tree, name), encoding='utf-8', errors='replace') as f:
                text = f.read()
        except OSError:
            continue
        if LINE_DIRECTIVE_RE.search(text):
            continue
        src = text.split('\n')
        for n in sorted(lines):
            got = lines[n]
            have = src[n - 1].strip() if n <= len(src) else ''
            if not got.startswith('#') and have != got:
                raise SystemExit('cpp_lines: the preprocessor printed %r as %s:%d, which holds %r; the line '
                                 'markers are out of step' % (got[:60], name, n, have[:60]))


def logical_starts(text):
    """{line: first line of its logical line} for every line of TEXT that continues the line
    before it (a backslash at the end of that line). The preprocessor prints a continued
    directive, such as a #define over several lines, at its first line only."""
    out, start = {}, None
    for n, line in enumerate(text.split('\n'), 1):
        if start is not None:
            out[n] = start
        start = (start or n) if line.rstrip('\r').endswith('\\') else None
    return out


def verdicts(text, lines, kept):
    """{line: True, False or None} for the LINES of a file whose text is TEXT. KEPT is the file's
    kept lines from preprocess, or None when no translation unit includes the file (all False).
    A line is kept when it, or the first line of the directive it continues, is. A file with a
    #line directive (a generated header pointing at its .party file) makes the line markers name
    other lines: there every line is kept when the file has no conditional directive, and unknown
    (None) when it has one."""
    if kept is None:
        return {n: False for n in lines}
    if LINE_DIRECTIVE_RE.search(text):
        return {n: None if COND_DIRECTIVE_RE.search(text) else True for n in lines}
    starts = logical_starts(text)
    return {n: starts.get(n, n) in kept for n in lines}


def preprocess(tree, release=False, gcc=None, files=None, jobs=8, sources=None):
    """{file: set of kept line numbers}, the union over the tree's translation units (c_sources,
    or SOURCES) preprocessed with the Makefile's flags. FILES, a set of tree-relative paths,
    limits the result to them. At most JOBS preprocessors run at a time."""
    gcc = gcc or default_gcc()
    with open(os.path.join(tree, 'Makefile'), encoding='utf-8', errors='replace') as f:
        flags = makefile_cppflags(f.read(), release)
    wanted = None if files is None else {os.path.normpath(p) for p in files}

    def one(src):
        r = subprocess.run([gcc, '-E', '-fdirectives-only'] + flags + [src], cwd=tree,
                           stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if r.returncode:
            return src, None, r.stderr.decode('utf-8', 'replace')
        return src, kept_lines(r.stdout.decode('utf-8', 'replace'), wanted), None

    kept, failed = {}, []
    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as pool:
        for src, got, err in pool.map(one, sources or c_sources(tree)):
            if got is None:
                failed.append((src, err))
                continue
            for name, lines in got.items():
                kept.setdefault(name, {}).update(lines)
    if failed:
        src, err = failed[0]
        raise SystemExit('cpp_lines: %d of the translation units do not preprocess (is %s built?); %s:\n%s'
                         % (len(failed), tree, src, '\n'.join(err.strip().split('\n')[:5])))
    check_in_step(tree, kept)
    return {name: set(lines) for name, lines in kept.items()}


def ranges(lines):
    out, run = [], None
    for n in sorted(lines):
        if run and n == run[1] + 1:
            run[1] = n
        else:
            run = [n, n]
            out.append(run)
    return ', '.join('%d' % a if a == b else '%d-%d' % (a, b) for a, b in out)


def main(argv=None):
    sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    import paths
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    ap.add_argument('files', nargs='+', help='files relative to the tree, e.g. src/data/items.h')
    ap.add_argument('--tree', default=paths.UPSTREAM, help='built source tree (default HNS_UPSTREAM)')
    ap.add_argument('--release', action='store_true', help="add the Makefile's RELEASE=1 flags")
    ap.add_argument('--gcc', default=default_gcc())
    a = ap.parse_args(argv)
    if not a.tree:
        raise SystemExit('cpp_lines: no tree; set HNS_UPSTREAM or --tree')
    kept = preprocess(a.tree, a.release, a.gcc, set(a.files))
    for name in a.files:
        lines = kept.get(os.path.normpath(name), set())
        print('%s: %d lines kept: %s' % (name, len(lines), ranges(lines) or 'none'))
    return 0


if __name__ == '__main__':
    sys.exit(main())
