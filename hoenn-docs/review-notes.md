# Review notes: things to adjust later

These are open items from Bryan's look at the world and Claude's review of 2.0 parts 3–13a (2026-11-26, debug build of `hoenn` at PR #43). Bryan wants to revisit them later. **They are not scheduled in a part yet.** When a part fixes one, mark it done here and say which PR fixed it.

Coordinates are map tiles `(x, y)` from the map's `map.json`.

## Open

### 1. Choices made without Bryan's approval (parts 5–13a)
Parts 5–13a (PRs #32–#43) ran without approval gates. That covered dialogue, pets, shop lists and the part 13a secret-base entrance art, which `2.0-plan.md` said Bryan approves first. Each PR's description lists its choices. Go through those lists with Bryan and change anything he wouldn't have picked. Items 4 and 5 below are part of this.

### 2. Building interiors look too alike
These three use nearly the same room: the same table and chairs, in the same spot.
- The Olivine lighthouse keeper's family
- The Ecruteak dance teacher
- The Celadon florist

The building plan (`buildings.md`) called for variety. Give each room its own furniture layout, or a different template house.

### 3. Sky Pillar base spot is in the middle of the stairs (Bryan)
`SkyPillar_Top` (12,14), the chamber-base from part 12b, sits in the gap at the top of the stairs, where the player walks. It isn't hidden at all.
- **Fix:** move it to a stretch of wall off the walking path. Re-run `gen_hoenn_base_spots.py`, then check that the summit still reads like Emerald's.
- **Also update:** `HOENN_SECRET_BASE_ENTRANCE_POSITIONS`, which the generator writes.

### 4. Rock base entrances in Johto/Kanto are only an outline
Route 45 (`Route45_hns` 30,78) and Mt. Moon (`MtMoon_Cave_hns` 18,20) both have this problem.
- **What's wrong:** the closed entrance from part 13a is a thin arch outline. The rock texture shows through the middle, so it looks unfinished.
- **What it should look like:** the filled dark indent that Emerald's spots use.
- **Fine as they are:** the tree entrances in Ilex Forest and Viridian Forest. They're a small dark hole in the trunk, which reads correctly.
- **Fix:** repaint the rock pair in `gen_hoenn_base_entrances.py` / `base_entrances.json` so the inside is dark.

### 5. Regi room base spots are front and centre (Bryan's call)
Desert Ruins, Island Cave and Ancient Tomb all put their spot at (8,2). That's the middle of the back wall, straight ahead of the entrance and above where the Regi used to stand.
- In an empty dead-end room this is easy to find, but it's not discreet.
- **If Bryan wants it hidden:** move it a few tiles to one side.

### 6. Put leaders' Pokémon behind them where there's room (Bryan)
Bryan would like each trainer's follower to stand **behind** the trainer when the tile is free, which should look cleaner. Today `gen_hoenn_followers.py` tries beside first, so all 30 stand to the side. The tile behind was checked with the generator's own rules (floor, nothing on it, not in a trainer's sight, doesn't cut anything off).
- **Room behind, 12:**
  - Falkner (9,3), Jasmine (8,3), Brock (6,4), Sabrina (14,10).
  - Johto's Elite Four: Will, Koga, Bruno, Karen, all (6,5).
  - Hoenn's Elite Four: Sidney, Phoebe, Glacia, Drake, all (6,4).
- **Wall behind, so they stay beside, 16:** Bugsy, Whitney, Morty, Pryce, Clair, Misty, Lt. Surge, Erika, Blue, Roxanne, Brawly, Wattson, Flannery, Norman, Winona, Juan.
- **Red** is left out: he faces away from you, so "behind" would put Pikachu in front of the stairs.
- **Fix:** in `choose_tile`, try the tile behind first, then the current order. Re-run the generator and re-shoot the 12. This also fixes the problem below.

**Drake's Salamence hides Drake.** In `EverGrandeCity_DrakesRoom`, Salamence stands at (5,5). It's a large sprite and covers Drake's left half. Moving it behind him, to (6,4), fixes that. Two smaller overlaps are probably fine: Blue's Rhyperior hangs over the edge of his mat, and Jasmine's Steelix overlaps her slightly.

## Withdrawn
- **Mt. Moon base next to Silver's trigger.** This was wrong. Silver's rematch is an `ON_FRAME` script that runs when you enter the cave (`VAR_PEWTER_CITY_STATE` 0/1), not a tile trigger, so the base spot doesn't clash with it.

## Checked and fine
- **Base spots:**
  - Cave of Origin B1F (7,12): the spot is faint under Emerald's own fog, as Emerald's own spots are.
  - Seafloor Cavern Room 9 (13,40): faint under fog in the same way.
  - Sealed Chamber inner room (5,2): fine.
  - Ilex Forest tree (36,18): fine.
  - Viridian Forest tree (50,65): fine.
- **Trainer followers:** 27 of the 30 stand next to their trainer and look right.
- **Not checked:**
  - Dewford Gym's Hariyama: the gym is dark until its trainers are beaten.
  - Fortree's Altaria: hidden with Winona until she's back, by design.
  - The part 13b battle backgrounds (PR #44): merged after this review.
