# Scripts that drew the Hebrew graphics

The PNGs and tilemaps under `graphics/` are the source of truth. These scripts drew most of them
from the English 2.0.6 art, and they are kept so a label can be redrawn the same way: change the
word in the script's table, run the family script, and review the result.

Every script needs Pillow. They take their locations from `tools/hebrew/paths.py` through
`gpaths.py`:

- **English originals** come from `git show 167aa6d537:<path>` (the `Release-v2.0.6` tag) in this
  repository, so a clone needs that history (not a shallow clone).
- **Fonts** come from `HNS_TREE`: `graphics/fonts/latin_*.png` and the width tables in
  `src/fonts.c`, or the stroke designs in `tools/hebrew/fonts/hebrew_glyph_designs.txt`.
- **Write mode** writes into `HNS_TREE`; previews and dry runs go to
  `$HNS_WORK/graphics/<family>/`.

Only pixel indices change. Each script keeps the file's size, bit depth, palette and every
non-pixel PNG chunk, uses no palette index the English file did not use, and checks this after
writing. Words are laid out right to left, in the English text's own colour indices.

## Families

| Family | Run (from the family folder) | Writes |
| --- | --- | --- |
| `types/` | `make_types.py [--write]` | `graphics/types/*.png`: the 19 type plates and the 5 contest-category plates (FONT_SMALL cells, centred like the English); `mystery` and `none` keep `???` |
| `coreui/` | `make_coreui.py [--only SUBSTR] [--dry] [--out TREE]` | battle HUD labels (`battle_interface/{hns,gen4}/hpbar.png`, `status{,2,3,4}.png`, `hns/healthbox_singles_player.png`, `move_info_window_{l,r,start}.png`), `interface/status_icons.png`, `menu_info.png`, `mon_markings_menu.png`, `bag/hm.png`, `check_berry.png`, `shop/money.png`, `party_menu/hns/bg.png`, `pokemon_storage/menu.png`, `summary_screen/hns/tiles.png`. `screens.py` draws the tilemapped screens as a preview |
| `pokedex/` | `make_pokedex.py [--write] [job ...]` | `graphics/pokedex/hgss/`: `tileset_menu1.png`, `tileset_menu2.png`, `tileset_menu3.png` (page tabs), `tileset_interface_hns.png` (SEEN/OWN panel), `tileset_menu_list.png` and the two START menu tilemaps, `tileset_menu_search.png`. Each tileset is edited through every tilemap that shows it, and every screen is re-rendered to prove no shared tile changed by accident. `disk_check.py` re-checks the written files |
| `pokegear/` | `heb_pokegear.py [PATH_FILTER ...]` (always writes) | the 29 `graphics/pokenav/` files: the `options/` buttons, `left_headers/`, `condition/graph.png` and `cancel.png`, `hns/radio/ui_tiles.png`, `region_map/city_zoom_text.png`. The condition graph also reads the two Spanish forks' redrawn graph (commits `268113861f` and `098f8e4906`, fetched from the `es` and `sigon` remotes) |
| `side/` | one `do_*.py` per file (always writes); `finalize.py` checks them all and draws the previews, `screens.py` the tilemapped screens | contest (`applause`, `nextturn`, `interface`, `results_screen/tiles`), Pokéblock (`menu`, `use_screen/{graph,updown,condition}`), `roulette/credit`, slot machine (`menu`, `digital_display`), trainer card (`tiles`, `frlg/tiles`), Frontier Pass (`bg`, `map_and_card`, `map_screen`), `battle_frontier/tourney_buttons`, Easy Chat (`button_window`, `mode`), Union Room chat (`background`, `r_button_labels`) |

Glyph sources: `types/`, `pokedex/` and `pokegear/` cut the letters from the installed font PNGs;
`coreui/` and `side/` start from the stroke designs and derive shorter or bolder sets from them
(`coreui/coreui_mini_designs.txt` and `side/side_designs.txt` hold the hand-drawn ones). The
naming screen's page tabs and the fonts themselves are drawn by `tools/hebrew/fonts/`.

## Files changed after their script ran

Some files were fixed later by hand or by a one-off script that is not kept. Re-running the
family script would undo those fixes, so write mode does not touch the files listed in
`LATER_EDITS` (`gpaths.py`): it saves the script's version under `$HNS_WORK/graphics/kept/` and
says so. `HNS_GFX_OVERWRITE=1` writes them anyway; the later fix must then be made again.

| File | Changed later by |
| --- | --- |
| `battle_interface/hns/status{,2,3,4}.png` | `aedb9c43e3` (paralysis tag widened) |
| `battle_interface/gen4/status{,2,3,4}.png` | `aedb9c43e3`, then `f09b0a6923` (frostbite tag drawn as קור) |
| `interface/status_icons.png` | `d3b59b94fe` (paralysis letters kept inside the pill) |
| `pokedex/hgss/tileset_menu{1,2,3}.png` | `d93afb1f02` (page tabs spaced evenly; the tab tilemaps changed with them) |
| `pokedex/hgss/tileset_menu_list.png`, `tilemap_start_menu.bin`, `tilemap_start_menu_search_results.bin` | `066d60d2ad` (list START menu mirrored) |
| `pokenav/condition/graph.png` | `9e489b46a5` (two labels moved clear of the pentagon outline) |
| `contest/results_screen/tiles.png` | `d41a67ebdf` (the NORMAL rank title reads נורמל) |

`side/do_graph.py` copies the Pokéblock graph's labels cell by cell from
`pokenav/condition/graph.png` in the tree. Since that file's labels moved, re-running it changes
`pokeblock/use_screen/graph.png` (449 pixels, the same labels moved) where the committed file
still has the old positions.

Not drawn by any script here: `pokedex/hgss/stat_bars.png` and the dex page-tab tilemaps
(`SelectBar.bin`, `tilemap_{info,stats,evo_screen_PE,forms,cry,size}_screen.bin`), the PokéNav
`options.pal` palettes, and the naming screen's BACK and OK buttons and symbols tab. They were
edited directly; the commits that changed them say how.

## Checking a redraw

Every script starts from the English file, so it gives the same output on every run. Running
all five families into an export of this tree, with the files they write reset to English,
reproduced every one of them byte for byte, except the Pokéblock graph above and the later-edited
files: those were left alone, and the copies saved under `kept/` equal the versions their script
first committed.

After a redraw, compare the preview pairs (English | Hebrew) in `$HNS_WORK/graphics/<family>/`,
build the ROM and look at the screen in a tour: none of these files has a text audit.
