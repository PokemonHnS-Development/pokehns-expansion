import os
import shutil
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'inventory'))
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import cpp_lines  # noqa: E402
import paths  # noqa: E402

# The parts of the English Makefile that makefile_cppflags and c_sources read.
MAKEFILE = """ifeq (hns, $(or $(BUILD), $(MAKECMDGOALS)))
	GAME_VERSION 	:= POKEMON_HNS
endif
C_SUBDIR = src
INCLUDE_DIRS := include
INCLUDE_CPP_ARGS := $(INCLUDE_DIRS:%=-iquote %)
CPPFLAGS := $(INCLUDE_CPP_ARGS) -Wno-trigraphs -DMODERN=1 -DTESTING=$(TEST) -D$(GAME_VERSION) -std=gnu17
ifeq ($(RELEASE),1)
	override CPPFLAGS += -DRELEASE
	ifeq ($(USE_LTO_ON_RELEASE),1)
		LTO := 1
	endif
endif
C_SRCS_IN := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
C_SRCS := $(foreach src,$(C_SRCS_IN),$(if $(findstring .inc.c,$(src)),,$(src)))
$(C_BUILDDIR)/%.o: $(C_SUBDIR)/%.c
	@$(CPP) $(CPPFLAGS) $< | $(PREPROC) -i $< charmap.txt
"""
STD = ['-iquote', 'include', '-Wno-trigraphs', '-DMODERN=1', '-DTESTING=0', '-DPOKEMON_HNS', '-std=gnu17']


def write(root, rel, text):
    p = os.path.join(root, rel)
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, 'w', encoding='utf-8') as f:
        f.write(text)


class MakefileTest(unittest.TestCase):
    def test_flags_of_both_builds(self):
        self.assertEqual(cpp_lines.makefile_cppflags(MAKEFILE, False), STD)
        self.assertEqual(cpp_lines.makefile_cppflags(MAKEFILE, True), STD + ['-DRELEASE'])

    def test_the_forks_diagnostic_switches_are_off(self):
        mk = MAKEFILE.replace('ifeq ($(RELEASE),1)', 'ifeq ($(RTL_CLIP_REPORT),1)\n'
                              '\toverride CPPFLAGS += -DRTL_CLIP_REPORT=TRUE\nendif\nifeq ($(RELEASE),1)')
        self.assertEqual(cpp_lines.makefile_cppflags(mk, True), STD + ['-DRELEASE'])

    def test_stops_rather_than_guess(self):
        for mk in (MAKEFILE.replace('-std=gnu17', '-std=gnu17 $(EXTRA)'),
                   MAKEFILE + 'ifeq ($(MODERN),1)\n\toverride CPPFLAGS += -DX\nendif\n',
                   MAKEFILE + 'CPPFLAGS += -DY\n',
                   MAKEFILE.replace('$(INCLUDE_DIRS:%=-iquote %)', '$(INCLUDE_DIRS:%=-I %)'),
                   'C_SUBDIR = src\n'):
            with self.assertRaises(SystemExit):
                cpp_lines.makefile_cppflags(mk, False)

    @unittest.skipUnless(paths.UPSTREAM and os.path.isfile(os.path.join(paths.UPSTREAM, 'Makefile')),
                         'no English tree')
    def test_the_english_and_the_fork_makefiles_give_the_same_flags(self):
        for mk in (os.path.join(paths.UPSTREAM, 'Makefile'), os.path.join(paths.REPO, 'Makefile')):
            with open(mk, encoding='utf-8') as f:
                text = f.read()
            self.assertEqual(cpp_lines.makefile_cppflags(text, False), STD, mk)
            self.assertEqual(cpp_lines.makefile_cppflags(text, True), STD + ['-DRELEASE'], mk)

    def test_c_sources(self):
        root = tempfile.mkdtemp(prefix='hns_cpp_lines_')
        self.addCleanup(shutil.rmtree, root, True)
        write(root, 'Makefile', MAKEFILE)
        for rel in ('src/a.c', 'src/x/b.c', 'src/x/y/c.c', 'src/x/y/z/d.c', 'src/e.inc.c', 'src/f.h', 'test/g.c'):
            write(root, rel, '')
        self.assertEqual(cpp_lines.c_sources(root), ['src/a.c', 'src/x/b.c', 'src/x/y/c.c'])
        write(root, 'Makefile', MAKEFILE.replace('$(C_SUBDIR)/*/*/*.c)', '$(C_SUBDIR)/*/*/*.c $(C_SUBDIR)/*/*/*/*.c)'))
        with self.assertRaises(SystemExit):
            cpp_lines.c_sources(root)


class OutputTest(unittest.TestCase):
    # gcc -E -fdirectives-only of a unit: an inactive branch of 4 lines comes out blank, a longer
    # one as a line marker, indented like the #if it replaces.
    OUTPUT = ('# 1 "src/a.c"\n'
              '# 1 "<built-in>"\n'
              '# 1 "src/a.c"\n'
              '# 1 "src/data/t.h" 1\n'
              'static const u8 sA[] = _("A");\n'
              '\n'
              '    .name = _("B"),\n'
              '    # 30 "src/data/t.h"\n'
              '    .name = _("C"),\n'
              '#define D _("D")\n'
              '# 3 "src/a.c" 2\n'
              'int x;\n')

    def test_kept_lines(self):
        self.assertEqual(cpp_lines.kept_lines(self.OUTPUT), {
            'src/a.c': {3: 'int x;'}, '<built-in>': {},
            'src/data/t.h': {1: 'static const u8 sA[] = _("A");', 3: '.name = _("B"),', 30: '.name = _("C"),',
                             31: '#define D _("D")'}})
        self.assertEqual(set(cpp_lines.kept_lines(self.OUTPUT, {'src/data/t.h'})), {'src/data/t.h'})

    def test_an_indented_marker_is_a_marker(self):
        # Read as text, the marker would put C on line 5 and every later line one off.
        self.assertIn(30, cpp_lines.kept_lines(self.OUTPUT)['src/data/t.h'])
        self.assertNotIn(5, cpp_lines.kept_lines(self.OUTPUT)['src/data/t.h'])

    def test_check_in_step(self):
        root = tempfile.mkdtemp(prefix='hns_cpp_lines_')
        self.addCleanup(shutil.rmtree, root, True)
        write(root, 'src/data/t.h', 'x\ny\n#define Z 1\n')
        cpp_lines.check_in_step(root, {'src/data/t.h': {1: 'x', 2: 'y', 3: '#define Z 1'}})
        with self.assertRaises(SystemExit):
            cpp_lines.check_in_step(root, {'src/data/t.h': {1: 'y'}})

    def test_verdicts(self):
        text = 'a\n#define M(x) \\\n    _("in a macro") \\\n    x\nb\n#if 0\nc\n#endif\n'
        kept = {1, 2, 5}
        self.assertEqual(cpp_lines.verdicts(text, [1, 3, 4, 5, 7], kept),
                         {1: True, 3: True, 4: True, 5: True, 7: False})
        self.assertEqual(cpp_lines.verdicts(text, [1, 5], None), {1: False, 5: False})
        # A generated header with #line directives: its numbers name the .party file.
        party = '#line 1 "src/data/trainers.party"\n#line 4\n    .trainerName = _("SAWYER"),\n'
        self.assertEqual(cpp_lines.verdicts(party, [3], set()), {3: True})
        self.assertEqual(cpp_lines.verdicts(party + '#if X\n#endif\n', [3], set()), {3: None})
        self.assertEqual(cpp_lines.verdicts(party, [3], None), {3: False})


@unittest.skipUnless(os.path.exists(cpp_lines.default_gcc()), 'no arm-none-eabi-gcc')
class PreprocessTest(unittest.TestCase):
    """preprocess on a small tree with the real compiler."""

    def setUp(self):
        self.root = tempfile.mkdtemp(prefix='hns_cpp_lines_')
        self.addCleanup(shutil.rmtree, self.root, True)
        write(self.root, 'Makefile', MAKEFILE)
        write(self.root, 'include/config.h', '#define FEATURE FALSE\n#define FALSE 0\n#define TRUE 1\n')
        inactive = ''.join('    .unused%d = 0,\n' % i for i in range(12))
        write(self.root, 'src/data/t.h',
              '#if FEATURE == FALSE\n'                                   # 1
              '    .name = _("KEPT"),\n'                                  # 2
              '#else\n'                                                  # 3
              '    .name = _("DROPPED"),\n'                               # 4
              '#endif\n'                                                 # 5
              '    #if FEATURE\n' + inactive +                           # 6-18
              '    .desc = _("DROPPED TOO"),\n'                           # 19
              '    #endif\n'                                             # 20
              '    .after = _("AFTER"),\n'                                # 21
              '#define LONG(x) {   \\\n'                                 # 22
              '    .s = _("IN A DEFINE"), \\\n'                          # 23
              '    .x = x }\n'                                           # 24
              '#ifdef RELEASE\n'                                         # 25
              '    .r = _("RELEASE ONLY"),\n'                             # 26
              '#endif\n')                                                # 27
        write(self.root, 'src/data/unused.h', 'static const u8 s[] = _("NOBODY");\n')
        write(self.root, 'src/a.c', '#include "config.h"\nstruct S s = {\n#include "data/t.h"\n};\n')
        write(self.root, 'src/b.inc.c', '#include "data/unused.h"\n')
        self.lines = [2, 4, 19, 21, 23, 26]

    def verdicts(self, release):
        kept = cpp_lines.preprocess(self.root, release, files={'src/data/t.h', 'src/data/unused.h'})
        with open(os.path.join(self.root, 'src/data/t.h'), encoding='utf-8') as f:
            got = cpp_lines.verdicts(f.read(), self.lines, kept.get('src/data/t.h'))
        return [n for n in self.lines if got[n]], kept

    def test_what_each_build_keeps(self):
        std, kept = self.verdicts(False)
        self.assertEqual(std, [2, 21, 23])
        self.assertNotIn('src/data/unused.h', kept)       # only a *.inc.c file includes it
        self.assertEqual(self.verdicts(True)[0], [2, 21, 23, 26])

    def test_a_unit_that_does_not_preprocess_stops_the_run(self):
        write(self.root, 'src/c.c', '#include "data/generated.h"\n')
        with self.assertRaises(SystemExit) as e:
            cpp_lines.preprocess(self.root)
        self.assertIn('src/c.c', str(e.exception))


if __name__ == '__main__':
    unittest.main()
