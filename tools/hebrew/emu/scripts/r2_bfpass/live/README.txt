Live-session scripts for the Frontier Pass / BP / remaining-facilities screen group (round 2).
They are not standalone tours: sess.py keeps one hnsrun session per ROM open on a Unix socket and
these files are sent to it (tools: s NAME < FILE, or both.sh he3 en3 < FILE for the Hebrew clip
build and English 2.0.6 at once). Most start with `sl STATE`, a savestate taken earlier in the
same session directory (dome_done = postgame base with the pass flags, symbols and BP set;
pike_3path1 = inside a Lv.50 Pike challenge; pyr_floor1 / pyr_after_bag = Pyramid floor 1).
Paths inside point at the scratch folder
../hns-tools/scratch/screens/r2_battle_frontier_pass_bp_and_remaining_facilities.

Order used: dome_run*.txt, arena1-3, palace1, pike1-2 + pike_room/pike_battle/pike_exit.sh
(first session); pike_hard, pike_lucy, pike_wild(+2), pyr1, pyr2(+b with _enter_123),
pyr3, pyr_open, pyr4, pyr5, pyr_give, pyr_toss, pyr_use, pyr_swap, pyr_retire(+2),
pyr_trainer(_he/_talk), pyr_won(2-6), pyr_brandon(+2), tent_v1, tent_f1, bag_grid (second).
pyrhelp.py: pyr_fill (Pyramid Bag contents), bag_seek, menu_pos; objs.py: live object events.
Offsets: SB2 frontier fields from include/global.h (0xCA9 lvlMode, 0xD00 battledBrainFlags,
0xE04 pikeWinStreaks, 0xE10 pike hint byte, 0xE1A pyramidWinStreaks, 0xE2C pyramidBag);
SB1+0x138C objectEventTemplates (flags 0x198C - 64 * 0x18, matched live).
