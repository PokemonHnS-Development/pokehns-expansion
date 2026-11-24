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
- **Setup:** debug menu → Party → **Set Party** (item 10) gives a Lv100 Wobbuffet plus a Lv100 **Lapras with Surf, Waterfall, Whirlpool and Dive**. Then Flags & Vars → **All badges** (item 11).
- **Surf:** you can only surf from ground level, not from docks or bridges (`IsPlayerFacingSurfableFishableWater` requires `ELEVATION_DEFAULT`).
  - Known-good spot: Petalburg City warp 0 (31/0). Walk 3 tiles left and face the pond.
- **Waterfall:** Meteor Falls 1F_1R (55/0), warp 1.
  - With collision off, walk to (16,38), then turn collision back on and surf east.
  - Go to (20,30) and press A facing up. You climb to (20,23).
- **Whirlpool (Johto):** Route 41 (0/23), warp 0. Surf from (13,39) to (15,42) and press A facing east.
- **Player position:** `gObjectEvents[0].currentCoords` is at 0x02001804/0x02001806 in current debug builds; subtract 7 (MAP_OFFSET). Re-check the symbol after code changes.
- **Surfing is about 2× walking speed** (~7–8 frames per tile vs 16).
- `mapinfo.py MAP [x0 y0 x1 y1]` prints an ASCII map (water, waterfalls, walls, warps, objects) for planning routes.
