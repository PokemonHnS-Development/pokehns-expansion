# Translation inventory builder

`build.py` makes the three data files that say which strings the H&S build can show:
`tools/hebrew/data/live_labels.json` (live, debug-only and dead script labels per file),
`inventory.json` (every file with text, its counts and its translation batch) and
`c_strings.json` (every C literal and whether the release ROM holds it). `units.py`,
`make_chunks.py`, the sweep and `status_report.py` read them. Rebuild them after an upstream
update, or after anything that changes which scripts or strings are built.

```bash
python3 tools/hebrew/inventory/build.py --release PATH/pokehns-release.gba --compare
```

It needs:

- **The English source tree** (`--src`, default `HNS_UPSTREAM`): strings are counted in English,
  so a label keeps its verdict whatever language it holds now.
- **Two builds of that tree**: a release build (`make release`: LTO and `--gc-sections`, so an
  unreferenced string is really gone), given with `--release`, and a standard build (`--std`,
  default `TREE/pokehns.gba`). Each ROM needs its `.elf` and `.map` next to it.
- devkitARM's `arm-none-eabi-nm` (`DEVKITARM`), numpy, and about 40 seconds.

Everything goes to `--out` (default `$HNS_WORK/inventory`); nothing in the tree changes. Copy the
three files into `tools/hebrew/data/` after reading their diff. `--compare` says whether they
equal the shipped ones.

## Steps

1. `extract.py` counts the strings and decides liveness (below). It writes `asm_strings.json`,
   `asm_roots.json`, `asm_reach.json`, `asm_parents.json` and `c_strings.json`.
2. `fr_style_graph.py` repeats the French fork's map traversal (warps and connections from the
   player's room, ignoring flags) for comparison; `inventory.json` records its verdict as
   `fr_status` for the maps H&S inherited.
3. `mapgraph2.py` decides which `_hns` maps the player can reach: a script warp counts only if
   its script is reached from a reached map or from live code.
4. `build_inventory.py` writes `inventory.json`, `live_labels.json` and `batches.json`: tiers,
   story order and the 40 translation batches. `es_touched` marks the files the Spanish fork
   changed (`git diff 167aa6d537...268113861f`; `--es-ref` names another commit).
5. `tools/hebrew/flag_gates.py` takes out of `live` the labels the build still cannot show:
   match calls, TV shows and PokéNews behind flags defined as 0, and labels with no symbol in the
   ELF (`--elf`, default the release ELF). See its docstring.

`--no-gates` stops after step 4.

## How strings are counted

- **Script text** (`data/maps/*/scripts.inc`, `data/scripts/*.inc`, `data/text/*.inc`,
  `data/event_scripts.s`): one string is one label whose block has `.string` or `.braille`
  lines with at least one ASCII letter outside `{...}`. A message of several lines is one string.
- **C text** (`src/**/*.c`, `src/**/*.h`): one string is one `_()`, `__()`,
  `COMPOUND_STRING()`, `COMPOUND_STRING_SIZE_LIMIT()`, `ITEM_NAME()` or `ITEM_PLURAL_NAME()`
  literal with a letter outside `{...}`.
- Trainer names are the distinct `Name:` values of the `.party` files, and map section names the
  `name` fields of `region_map_sections.json`.
- `chars_live` is the visible length of the live strings (placeholders dropped), a rough effort
  measure.

## How liveness is decided

**Script labels.** The roots are the labels whose address appears as an aligned 32-bit word
anywhere in the release ROM outside `event_scripts.o`'s `script_data` section: C literal pools
and tables, map headers and map events. From the roots the traversal follows every identifier
that names a label, every pointer stored in a label's own bytes (this finds labels hidden in
macros), and the fall-through to the next label when a block does not end in `end`, `return`,
`goto`, `step_end` or text.

- Hits inside sound and graphics data are dropped (chance matches in cries, palettes, sprites).
- Where two labels share an address, only the one that C names is a root.
- Debug-only means reachable only from roots inside debug code (`Debug*`, the battle debug
  menu, the sprite visualizer).

**C literals.** The longest plain run (6 or more characters) of each literal is encoded with
`charmap.txt` and searched in the release ROM outside the script region. LTO and
`--gc-sections` drop unreferenced data, so "absent" means compiled out or garbage-collected. Only
literals that are unique across the C files decide; short or repeated ones take the file's
verdict. One limit: a literal inside a live struct is present even if only debug code prints it.

**What the graph cannot see**, which is why step 5 exists: it ignores flags, so a match call
whose contact is never registered, or a TV show that never airs, looks live; and a label in a
file or `#if` branch that is not assembled has no address, yet the source-level traversal counts
it when a reached label names it. No map
whose `game_version` is not `hns` exists in the build (`mapjson` writes `NULL` for its header),
so their labels are live only where H&S scripts or C tables reuse them.

Nothing here was checked on screen: "live" means "the build can reach it from code or map data",
not "a player has seen it". The sweep (`emu/sweep.py`) is what shows each live label.
