# Battle-test messages in Hebrew

The battle tests in `test/` expect the English battle messages (`MESSAGE("...")`). A Hebrew build
prints Hebrew, so `test/test_runner_battle.c` looks each expected message up in
`test/hebrew_battle_messages.h` and expects the Hebrew instead. The table is built from what the
two builds actually print in the same test runs, so it holds the game's own Hebrew.

To rebuild it after battle text changes:

1. `python3 add_dump.py <english tree>` and `python3 add_dump.py <hebrew tree>`, then run
   `make check` in both trees and keep the logs.
2. `python3 parse_dump.py EN.log HE.log runs.json` pairs the runs message by message.
3. `python3 ../check_tests.py HE.log` lists the tests that fail only in Hebrew; write their names
   to a file and run `python3 map_patterns.py runs.json FAILING.txt data/`, which writes
   `data/table.json` (pattern -> Hebrew) and `data/mapping.json` (per test, what matched).
4. Patterns the English runs never printed (negated checks, control codes) are composed by hand
   from their `src/battle_message.c` templates into `data/composed.json`.
5. `python3 gen_header.py ../../../test/hebrew_battle_messages.h`, then `git checkout` the dump out
   of both runners and run `make check` again.
