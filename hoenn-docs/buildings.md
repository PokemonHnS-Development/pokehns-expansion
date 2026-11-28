# Fake buildings: survey and plan (2.0 parts 8a–11)

Part 8a checked every HnS door that leads nowhere (`tools/hoenn/find_fake_doors.py`, then a screenshot of each candidate in the emulator). The plan's estimate of ~90 came from a looser heuristic. **The real count is 16 buildings**, and most of the rest are cave mouths.

**Picked without Bryan (review):** the purposes below. Aidan asked for parts 5–12 in one run without waiting at approval gates, so this list goes ahead as written. Change any line and re-run `tools/hoenn/gen_hoenn_buildings.py`.

## Buildings to open

| # | Part | Map | Door | Building | Planned purpose |
|---|---|---|---|---|---|
| 1 | 8a ✅ | Route 34 | 23,50 | small house on the shore | **Fisherman's shack.** A fisherman, his wife (hint NPC) and their Psyduck. This is the generator's test interior. |
| 2 | 8b ✅ | Olivine City | 2,15 | west row, 1st door | **Harbor office.** Ship schedules for the S.S. Aqua and the Hoenn ferry, plus a clerk who hints about Hoenn. |
| 3 | 8b ✅ | Olivine City | 6,15 | west row, 2nd door | **Sailor's family home.** The sailor is away at sea, his kids are home, and there's a Wingull pet. |
| 4 | 8b ✅ | Olivine City | 10,15 | west row, 3rd door | **Retired captain.** Sea stories, and he rates your Pokémon's friendship. |
| 5 | 8b ✅ | Olivine City | 27,15 | east row, 1st door | **Fishing tackle shop.** A small mart (Net/Dive/Lure Balls, Repels). |
| 6 | 8b ✅ | Olivine City | 31,15 | east row, 2nd door | **Shipwright's workshop.** Workers, and talk of the lighthouse and Amphy. |
| 7 | 8b ✅ | Olivine City | 35,15 | east row, 3rd door | **Lighthouse keeper's family.** Jasmine and Amphy lines, and a daily item. |
| 8 | 9 ✅ | Ecruteak City | 57,25 | house by the east trees | **Kimono dance teacher's house.** Students practicing, and Eevee pets. |
| 9 | 9 ✅ | Route 34 | 33,31 | house next to the Day Care | **Breeder's house.** Egg and breeding tips, with a hint NPC. |
| 10 | 9 ✅ | Route 38 | 34,41 | ranch building | **Moomoo Farm storeroom.** A farmhand, Miltank, and a Moomoo Milk line. |
| 11 | 9 ✅ | Bellchime Trail | 54,58 | lodge | **Tin Tower caretaker's lodge.** Sages, with legendary-bird rumors (rumor lines). |
| 12 | 10 ✅ | Route 6 | 21,17 | house west of the road | **Bug Catchers' club house.** Bug tips, and a Butterfree pet. |
| 13 | 10 ✅ | Route 6 | 49,30 | house east of the road | **Retired Silph engineer.** Talk of the Magnet Train and Power Plant, with a hint NPC. |
| 14 | 10 ✅ | Celadon City | 26,17 | house with a pond | **Florist's house.** Flowers, Bellossom, and a berry gift. |
| 15 | 11 ✅ | Melemele Island | 11,21 | island house | **Island family home.** Alola-style lines and pets. |
| 16 | 11 ✅ | Melemele Island | 20,25 | island house | **Surf shop.** Surfing tips and Wailmer talk. |

Every building gets 1–4 NPCs, at least one of them a hint NPC (`"hints"` in `data/hoenn/buildings.json`). Each uses one of HnS's 13×10 house layouts. Gifts, trades and marts need flags or scripts beyond plain text, so they come with their part.

## Not buildings (left as they are)

- **Cave mouths with no warp:** these are decorative holes in cliffs. They are out of scope for 3a, but could become Johto/Kanto secret-base spots (plan 3c).
  - Blackthorn (2)
  - Ecruteak 8,54
  - Ilex Forest 77,39
  - Mt. Silver (4 outside and mountainside)
  - Routes 4, 11, 23, 26, 26 North, 34 (53,53), 45 (3), 46, 49 (2) and 50
  - Sinjoh Ruins
  - Safari Zone (4)
- **Double-wide entrances whose other half already warps:** Mt. Silver's mountainside (3), Pallet's lab (15,13), Route 7 (7,16) and Route 8 (12,18).
- **Lake of Rage (low tide):** that map is never used. `LakeOfRage_hns` swaps in its layout by script and keeps its own warps.
- **Route 5 / Saffron (24,43 / 28,52):** the same gate building seen from both maps. It's decorative.
- **Pallet Town 10,4 / 19,4 / 10,11 / 19,15:** grass and fence tiles tagged with door behavior. They aren't doors.
- **Alola:** the plan's ~24 were cliff and grass tiles tagged with door behavior (Akala, Poni, Ula'ula). Only Melemele's two houses are real.

## Templates in use

HnS's 13×10 houses come in three looks: yellow tile, wood floor, and Mr. Pokémon's white office. Small differences (a wall clock, a TV, a book on the table) set them apart. The chairs (left and right of the table, and the row above them) are walkable tiles, so keep NPCs off them. Templates so far: `house_a`–`house_e` (8a), `office` (Mr. Pokémon), `house_clock` (Lake of Rage 1), `house_tv` (Goldenrod 1), `house_wood` (Lake of Rage 2), `house_wood_book` (Ecruteak 2), `house_yellow` (Pewter 1) (8b), and `house_wood_b` (Violet 2), `house_wood_c` (Blackthorn 2), `farmhouse` (Route 39) and `house_shelves` (New Bark 2) (9), and `house_yellow_b` (Route 5), `house_wood_d` (Saffron 1) and `house_yellow_c` (Cerulean 3) (10), and HnS's Alola maps `alola_home` (Melemele House 3, 20×20 with the entrance at 6,13) and `alola_shop` (Melemele House 2, a mart) (11). Any HnS indoor map works as a template: the generator copies its entrance from the first warp.

## How to add one

1. Add the building to `data/hoenn/buildings.json`: door, template, purpose and objects. Use `signs` to replace the template's signs (`[]` for none). For a once-a-day gift, give the NPC a `daily_gift` (a daily flag from `hoenn_events.h`, 7 items from Sunday to Saturday, and the intro/after/full/done texts); the generator writes the script. For a shop or anything else beyond text, give the NPC a `script` written in `data/scripts/hoenn_buildings.inc`, and put its texts in the building's `texts`.
2. Run `tools/hoenn/gen_hoenn_buildings.py`, then `tools/hoenn/gen_hoenn_hints.py`. The second one turns NPCs with `hints` into hint NPCs. Always run it after the buildings generator.
3. Build and walk in.
