# Claude's playtest scripts (part 20 pre-pass)

Run from the harness directory with `pt.gba`/`pt.elf` and a `pt/` folder. `ptx.py` puts
`tools/hoenn/emu` on the path (edit the path if the repo lives elsewhere).

| Script | What it plays |
|---|---|
| `s0.py` | Oak's ticket (start flags poked) |
| `s2.py` | Rustboro gym + May's first call (expects `pt/birch1.ss` from `pt_sections.s1_birch`) |
| `s3.py`, `s3b.py` | The other seven gyms with prerequisites, calls at 4/8 badges |
| `s11.py`, `s11b.py` | Magma/Aqua quests, Mt. Pyre double, Steven's house, Devon Scope, mind reader |
| `s12.py`, `s12b.py` | Victory Road Wally, E4, Wallace, Hall of Fame, Brendan & May, Elm, Red |
| `sweep.py` | Talks to every NPC in every Hoenn town map (`explore_fast`), writes `pt/sweep.json` |
| `ex.py` | Explore given maps and print condensed dialogue |
| `grid.py`, `sheet.py` | Labeled screenshot grids / numbered contact sheets |
| `battle_bgs.py` | Part 20a: wild battles on several maps, screenshots the battle backgrounds (`mkdir p20` first) |
| `owshots.py` | Part 20a: screenshots the overworld Pokémon on given maps by day or night (`TZ` sets the clock) |
| `render_battle_bgs.py` | Renders every battle background and palette from the repo's art into one sheet (no emulator) |

**New session:** `tools/hoenn/emu/setup.sh` builds the harness in `~/emu`, a debug ROM, and a Hoenn save (`pt/birch1.ss`).

Findings and the resume point live in `claude/hns-hoenn-playtest-log.md` (claude.ai Project).
