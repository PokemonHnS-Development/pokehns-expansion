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
