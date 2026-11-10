"""status_report.py: every file KEPT_LATIN names still holds Latin letters in a live string. STATUS.md
prints the reason only for a file with a string that has no Hebrew at all; an entry may also explain
Latin inside Hebrew strings (Heart & Soul, IV, x1.5). A file with no Latin left needs no entry."""
import os
import re
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402
import status_report  # noqa: E402
import units as U  # noqa: E402


def latin_runs(text):
    """Latin letter runs of a unit's text, without {tokens} and escapes such as \\n."""
    return re.findall(r'[A-Za-z]+', re.sub(r'\\[A-Za-z]', ' ', U.TOKEN_RE.sub('', text)))


@unittest.skipUnless(paths.UPSTREAM and os.path.isdir(paths.UPSTREAM),
                     'needs the English tree (C literals take their liveness from it)')
class KeptLatinTest(unittest.TestCase):
    def test_every_entry_still_holds_latin(self):
        stale = []
        for f in sorted(status_report.KEPT_LATIN):
            path = os.path.join(paths.TREE, f)
            live = [u for u in U.extract([f], paths.TREE, False) if u.get('live', True)] if os.path.exists(path) else []
            if not any(latin_runs(u['en']) for u in live):
                stale.append(f)
        self.assertEqual(stale, [], 'no Latin left in a live string: drop these from KEPT_LATIN')


if __name__ == '__main__':
    unittest.main()
