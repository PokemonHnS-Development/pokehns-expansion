import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import check_chunked  # noqa: E402

NAMES = {b'Absorb drains', b'Acid lowers', b'Bite flinches', b'Capture: ball data', b'Capture: low level',
         b'Captivate fails', b'Charge boosts', b'uq4_12_add'}


def selected(prefixes, names):
    return {n: [p for p in prefixes if n.startswith(p)] for n in names}


class Chunks(unittest.TestCase):
    def test_without_crashes_one_chunk_per_first_character(self):
        self.assertEqual(check_chunked.chunks(NAMES, set()), [b'A', b'B', b'C', b'u'])

    def test_every_name_is_selected_exactly_once(self):
        for crashing in (set(), {b'Capture: ball data'}, {b'Acid lowers', b'Charge boosts'}):
            for name, hits in selected(check_chunked.chunks(NAMES, crashing), NAMES).items():
                self.assertEqual(len(hits), 1, (name, hits, crashing))

    def test_a_crashing_test_is_alone_in_its_chunk(self):
        plan = check_chunked.chunks(NAMES, {b'Capture: ball data'})
        self.assertIn(b'Capture: ball data', plan)
        self.assertEqual([n for n in NAMES if n.startswith(b'Capture: ball data')], [b'Capture: ball data'])
        self.assertIn(b'A', plan)

    def test_a_crashing_name_that_prefixes_another_is_refused(self):
        with self.assertRaises(SystemExit):
            check_chunked.chunks(NAMES | {b'Capture: ball data 2'}, {b'Capture: ball data'})

    def test_patch_arg_escapes_everything_but_letters_digits_and_spaces(self):
        self.assertEqual(check_chunked.patch_arg(b'Capture: b'), 'Capture\\x3a b\\0')
        self.assertEqual(check_chunked.patch_arg('é'.encode('utf-8')), '\\xc3\\xa9\\0')


if __name__ == '__main__':
    unittest.main()
