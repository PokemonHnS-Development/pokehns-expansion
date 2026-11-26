# Review notes: things to adjust later

These are open items from Bryan's look at the world and Claude's review of 2.0 parts 3–13a (2026-11-26, debug build of `hoenn` at PR #43). Bryan wants to revisit them later. **They are not scheduled in a part yet.** When a part fixes one, mark it done here and say which PR fixed it.

Coordinates are map tiles `(x, y)` from the map's `map.json`.

## Open

### 1. Choices made without Bryan's approval (parts 5–17)
Parts 5–17 (PRs #32–#52) ran without approval gates. That covered dialogue, pets, shop lists and the part 13a secret-base entrance art, which `2.0-plan.md` said Bryan approves first. Each PR's description lists its choices. Go through those lists with Bryan and change anything he wouldn't have picked. Items 4 and 5 below are part of this.

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

### 7. Slateport aide greets you after you already have Mudkip (bug)
Reproduced in the emulator.
- **How it happens:** come in by the Tidal Strait (or the Lilycove ferry), get Mudkip from Birch, then walk into Slateport harbor. The `ON_FRAME` greeting (`VAR_HOENN_AIDE_STATE` == 0) still plays, but the aide is hidden (his flag is `FLAG_HOENN_RECEIVED_MUDKIP`). Nobody is standing there, yet "Oh! You must be …, from JOHTO!" plays anyway.
- **Origin:** part 16b. Part 14 makes it a normal route instead of a rare one.
- **Fix:** have Birch's gift script set `VAR_HOENN_AIDE_STATE` to 1, or skip the greeting when the flag is set.

### 8. May's strait call can ring long after the crossing
`HOENN_CALL_STRAIT` needs `FLAG_HOENN_BM_PHONE`.
- **The problem:** if you cross before Birch gives you the numbers, the call rings whenever you get them. "Dad *just* got a call from Mr. Briney" then comes hours late.
- **Fix:** mark the call done if you crossed without the phone, or word it so the timing doesn't matter.

### 9. Part 13b backgrounds: two visual nits
- **Desert at night:** the sky and dunes darken, but the flat sand in front keeps its daytime colours, so it looks lit wrong.
- **Graves:** some headstones and a cross sit right behind the player's back sprite, so a cross pokes out beside the head.
- The plan said Bryan approves mockups first; that was skipped (item 1).

### 10. Burned Tower: from the west stairs you never see the Typhlosion family (bug)
Reproduced in the emulator: step down the west stairs at night onto (8,17). The whole scene plays with the camera on the player, and the family at (16–18, 14–15) stays off screen.
- **Why:** `HoennSeek_EventScript_StarterPanDown` only pans the camera down 2 tiles, and only when the player is above row 14. The south-west trigger row (x 8–13, row 17) gets no pan, and from x 8–9 the family is out of view.
- **Fix:** pan toward the family from wherever the scene starts, or move the camera to a fixed spot over the embers.

### 11. The two new maps look generator-made
`Route46_Meadow_hoenn` and `Route25_Garden_hoenn` work, but they're very boxy. Each has a straight border of identical trees and a flat open lawn with scattered flowers. The meadow also has a solid cliff band and a big rectangle of tall grass. The garden has a pale rectangle in the middle.
- **Fix:** hand polish, such as uneven tree edges, a path, a ledge or a pond, and Sunkern spread through the grass (the text says the meadow is "full of SUNKERN"; about five are visible).
- The meadow's wild table is Lv 3–8, for a post-game player. That's probably on purpose (baby Pokémon), but Bryan should confirm it.

### 12. Totodile's scene isn't the planned one
- **The plan:** a Lake of Rage fishing spot, a fisherman whose lines keep getting bitten, and fishing it with the **Good Rod** until a Totodile clamps on.
- **Part 15b instead:** a Feraligatr surfaces in the south cove and the Totodile hops ashore. There's no fisherman and no fishing.
- **Also dropped:** the plan's "stay hidden behind a pillar" bit in the Burned Tower is only a line of text.
- Bryan should decide whether to keep these or go back to the plan.

### 13. Smaller things from parts 15a–16
- **RYDER outside the Cerulean Gym** stands right under the gym's round sign, so his head covers it. Moving him a tile would look cleaner.
- **`gMapGroup_SpecialArea_Hns` is full** (128 maps; the Tidal Strait's east half is number 127, the last one that fits in an `s8`). New maps go in `gMapGroup_SpecialArea2_Hns`, but `gen_hoenn_buildings.py` still appends to the full group. The next building would hang the game on load. Point the generator at the new group before anyone adds one.
- **RYDER takes Emerald's unused `TRAINER_LEROY` slot.** That shifts every Hoenn trainer ID after it by one, so a save made on a build from before part 16 would have its Hoenn "defeated" flags shuffled. Saves aren't meant to carry over between dev builds, but don't use an old 2.0 test save for a playtest.
- **Suicune at the Route 25 overlook** stands right next to the new garden gap on a fresh save. Already on the playtest checklist; check it there.

### 14. Vermilion fire: the camera never comes back (bug, serious)
Reproduced in the emulator.
- **What happens:** `HoennSeek_EventScript_VermilionFire` pans the camera tile by tile to the burning house, then ends with `special RemoveCameraObject` and never pans back. Afterwards the view stays offset from the player. Once you walk a few steps, the map draws in the wrong places (repeated, wrapped strips) until you leave the map.
- **Fix:** pan back the same number of tiles before `RemoveCameraObject`, as Emerald's camera scenes do (e.g. keep the step counts and walk the camera back).
- **Not tested** because of this: talking to the leader after the fire.

### 15. Part 17 nits
- **The smoke is very faint:** a couple of small `FLDEFF_ASH_PUFF` puffs on the roof, so the house doesn't really read as on fire.
- **The sunglasses only exist in the text:** the Squirtle leader uses the plain Squirtle sprite.

## Withdrawn
- **Mt. Moon base next to Silver's trigger.** This was wrong. Silver's rematch is an `ON_FRAME` script that runs when you enter the cave (`VAR_PEWTER_CITY_STATE` 0/1), not a tile trigger, so the base spot doesn't clash with it.

## Checked and fine
- **Part 17, checked in later on:** the debug size matches and the generators re-run with no changes. In the emulator, the Route 6 pitfall, the fall, the hideout scene and the fire scene all play (camera bug aside, item 14).
- **Parts 15a, 15b and 16, checked in later on:**
  - The debug size matches, and every generator re-runs with no changes.
  - Scenes played in the emulator:
    - The Chikorita meadow (runaway version).
    - The Burned Tower (wild version, see item 10).
    - Lake of Rage (watch-only).
    - Bulbasaur's ceremony.
    - Charmander in the rain.
    - RYDER appearing.
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
- **Part 13b, checked in later on:** wild battles on Route 111 sand, Route 113, Mt. Pyre's exterior and summit at 1 PM, 6 PM and 11 PM. All of them show the new backgrounds.
- **Part 14, checked in later on:**
  - The whirlpool blocks the gap without the ticket.
  - With it, you surf straight through and stay surfing across the seam.
  - Route 105 connects (rows 20–34 of the east half).
  - May's call plays.
  - Generators re-run cleanly; the debug size matches.
