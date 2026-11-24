# Headless emulator harness (libmgba)

Plays scripted input against a ROM, takes screenshots, and reads/writes memory. Use it to smoke-test builds before sending patches.

```sh
sudo apt-get install -y libmgba-dev libpng-dev
gcc -O2 -o harness harness.c -lmgba -lpng
```

## Getting to the overworld
`new_game_to_debug_menu.txt` plays the H&S 2.0.6 intro: title, options pages, Oak's speech. It ends in the bedroom with the debug menu open. Run it with `savestate` appended:

```sh
(cat new_game_to_debug_menu.txt; echo "savestate ow.ss") | ./harness pokehns.gba
python3 warp.py ow.ss 31 1 slateport | ./harness pokehns.gba   # Slateport City
```

The script commands are documented at the top of `harness.c`. Savestates only work with the exact ROM that made them.

## Debug menu tips
- **Warp:** Utilities → "Warp to map warp…". ↑/↓ change the current digit; → moves to the next digit (tens, then hundreds).
- **Flags & Vars:** items 14–16 turn off collision, wild encounters and trainer sight.
- **Map numbers:** a map's group/number is its position in `data/maps/map_groups.json`.

## Field moves (HM) test recipe
- **Setup:** debug menu → Party → **Set Party** (item 10) gives a Lv100 Wobbuffet plus a Lv100 **Lapras with Surf, Waterfall, Whirlpool and Ice Beam (HM09 teaches Dive)**. Then Flags & Vars → **All badges** (item 11).
- **Surf:** you can only surf from ground level, not from docks or bridges (`IsPlayerFacingSurfableFishableWater` requires `ELEVATION_DEFAULT`).
  - Known-good spot: Petalburg City warp 0 (31/0). Walk 3 tiles left and face the pond.
- **Waterfall:** Meteor Falls 1F_1R (55/0), warp 1.
  - With collision off, walk to (16,38), then turn collision back on and surf east.
  - Go to (20,30) and press A facing up. You climb to (20,23).
- **Dive:** get HM09 from Steven's letter (Mossdeep Steven's House 45/7: from the door, UP, RIGHT×3, UP, A) and teach it to Lapras over Ice Beam. Then `warp.py STATE 31 42 NAME --xy 40 40` lands on a Route 127 dive tile; A dives, **B** surfaces. Other tested spots: Route 124 (31/39) 43,37; 126 (31/41) 40,30; 128 (31/43) 60,14; 134 (31/49) 60,31.
- **Exact-tile warps:** `warp.py ... --xy X Y` overwrites `sWarpDestination` after the warp starts (warp ID forced to none). Landing on water starts you surfing.
- **Whirlpool (Johto):** Route 41 (0/23), warp 0. Surf from (13,39) to (15,42) and press A facing east.
- **Player position:** `gObjectEvents[0].currentCoords` is at 0x02001804/0x02001806 in current debug builds; subtract 7 (MAP_OFFSET). Re-check the symbol after code changes.
- **Surfing is about 2× walking speed** (~7–8 frames per tile vs 16).
- `mapinfo.py MAP [x0 y0 x1 y1]` prints an ASCII map (water, waterfalls, walls, warps, objects) for planning routes.
- **Save blocks move.** `gSaveBlock1Ptr`/`gSaveBlock3Ptr` change after warps, so read the pointer in the same state you poke. Offsets (current build): SaveBlock1 `flags` +0x198C, `vars` +0x1ABC; SaveBlock3 `hoennFlags` +0x32.
- **Hold buttons 4 frames** (`press A 4`) for dialogue; single-frame presses are sometimes missed.
- **Ferry trip (part 8):** from a debug save, set `FLAG_RETURNED_MACHINE_PART` (0x1DD), `VAR_SSAQUA_STATE` (0x408B) = 7 and `VAR_NUM_BADGES` (0x4076) = 16, then: Oak in `PalletTown_Lab_hns` (11/4, `--xy 13 12`, face up) → Vermilion port (15/3, `--xy 8 9`, face down) → Slateport harbor (40/9) → Lilycove harbor (44/10). Mt. Silver gate: `ReceptionGate_hns` (22/22); Wallace's stamp is `FLAG_HOENN_STAMP_WALLACE` (0x1BC8).
