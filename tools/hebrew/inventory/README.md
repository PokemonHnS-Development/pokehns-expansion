# Translation inventory builder

`build.py` makes the three data files that say which strings the H&S build can show:
`tools/hebrew/data/live_labels.json` (live, debug-only and dead script labels per file),
`inventory.json` (every file with text, its counts and its translation batch) and
`c_strings.json` (every C literal, and whether each build's preprocessor keeps it and its ROM
holds it). `units.py`, `make_chunks.py`, the sweep and `status_report.py` read them. Rebuild them
after an upstream update, or after anything that changes which scripts or strings are built.

```bash
python3 tools/hebrew/inventory/build.py --release PATH/pokehns-release.gba --compare
```

It needs:

- **The English source tree** (`--src`, default `HNS_UPSTREAM`): strings are counted in English,
  so a label keeps its verdict whatever language it holds now.
- **Two builds of that tree**: a release build (`make release`: LTO and `--gc-sections`, so an
  unreferenced string is really gone), given with `--release`, and a standard build (`--std`,
  default `TREE/pokehns.gba`). Each ROM needs its `.elf` and `.map` next to it. The standard
  build also leaves in TREE the headers the build generates, which the preprocessor step reads
  (below).
- devkitARM's `arm-none-eabi-nm` and `arm-none-eabi-gcc` (`DEVKITARM`), numpy, and about 50
  seconds (the preprocessor step is about 20 of them).

Everything goes to `--out` (default `$HNS_WORK/inventory`); nothing in the tree changes. Copy the
three files into `tools/hebrew/data/` after reading their diff. `--compare` says whether they
equal the shipped ones.

## Steps

1. `extract.py` counts the strings and decides liveness (below). It writes `asm_strings.json`,
   `asm_roots.json`, `asm_reach.json`, `asm_parents.json` and `c_strings.json`. Its C step runs
   `cpp_lines.py`.
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

**C literals.** A literal is in a build when both hold:

- **The build's preprocessor keeps its line** (`pp_release`, `pp_std`). `cpp_lines.py` runs every
  C source the tree's Makefile compiles (`src/*.c`, `src/*/*.c`, `src/*/*/*.c`, not `*.inc.c`)
  through `arm-none-eabi-gcc -E -fdirectives-only` with the Makefile's own `CPPFLAGS` for `hns`
  (`-iquote include -Wno-trigraphs -DMODERN=1 -DTESTING=0 -DPOKEMON_HNS -std=gnu17`, plus
  `-DRELEASE` for the release build); a change to those flags it cannot place, such as one under
  another condition or for one target, stops the run. That mode evaluates `#if`, `#include` and
  `#define` as the build does but expands no macro, so every kept line comes out as written under
  its line marker; a line counts as kept if any unit that includes its file keeps it. A header is
  found from whichever units include it, so no includer has to be named. A literal inside a
  `#define` over several lines counts on the `#define`'s first line, which the preprocessor prints
  when the `#define` is in a kept branch. A file no unit includes keeps nothing. A generated
  header with `#line` directives (`src/data/trainers_hns.h` and the other `.party` outputs) names
  its `.party` file in the line markers, so when a unit includes it, all its lines count as kept
  if it has no `#if` and as unknown (`null`) if it has one; when no unit includes it, they count
  as dropped, as in any other file. Each kept line that is not a directive, in a file without
  `#line`, is checked against the source text at its number, so a misread line marker stops the
  run.
- **The build's ROM holds its text** (`rom_release`, `rom_std`): the longest plain run (6 or more
  characters) is encoded with `charmap.txt` and searched in that ROM outside the script region;
  `null` when no run is long enough. This catches what the preprocessor keeps but the linker
  drops: a literal in a function or table nothing references is not in the ROM. Only literals
  that are unique across the C files decide `inventory.json`'s per-file counts; short or repeated
  ones take the file's verdict there.

`units.py` (`c_record_live`) counts a literal live when one of the two builds has both, `null`
counting as not ruled out. The preprocessor needs the headers the build generates: a built tree
has them (`make hns`; CI never runs the inventory). They are
`include/constants/{heal_locations,layouts,map_event_ids,map_groups,region_map_sections,script_commands}.h`
and `src/data/{battle_partners,debug_trainers,heal_locations,map_group_count,trainers_hns,tutor_moves,wild_encounters}.h`,
`src/data/pokemon/teachable_learnsets.h` and `src/data/region_map/region_map_entries.h`; a unit
that does not preprocess stops the run with gcc's message. `python3
tools/hebrew/inventory/cpp_lines.py src/strings.c` prints the lines a build keeps of a file.

Limits: a literal inside a live struct is in the ROM even if only debug code prints it; and a
literal the preprocessor keeps in a function the linker drops, or in a `#define` nothing expands,
still counts as live when its run is in the ROM from another line or from script text, or is too
short to search for (`null`). `inventory.json` takes its per-file counts from the release ROM
search alone.

`units.py` reads `c_strings.json` by line and text in the English tree, then matches the
translated tree's literals by variable, or else designator and field, macro and place, so a line
that moved in the Hebrew tree keeps its own verdict. A literal in a branch only the `TEXT_RTL`
build compiles has no record: it counts as live and takes no place among the others.

**What the graph cannot see**, which is why step 5 exists: it ignores flags, so a match call
whose contact is never registered, or a TV show that never airs, looks live; and a label in a
file or `#if` branch that is not assembled has no address, yet the source-level traversal counts
it when a reached label names it. No map
whose `game_version` is not `hns` exists in the build (`mapjson` writes `NULL` for its header),
so their labels are live only where H&S scripts or C tables reuse them.

Nothing here was checked on screen: "live" means "the build can reach it from code or map data",
not "a player has seen it". The sweep (`emu/sweep.py`) is what shows each live label.
