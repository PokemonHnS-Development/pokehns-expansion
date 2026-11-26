# Review notes: things to adjust later

These are open items from Bryan's look at the world and Claude's review of 2.0 parts 3–13a (2026-11-26, debug build of `hoenn` at PR #43). Bryan wants to revisit them later. **They are not scheduled in a part yet.** When a part fixes one, mark it done here and say which PR fixed it.

Coordinates are map tiles `(x, y)` from the map's `map.json`.

## Bryan's decisions (2026-11-26)
Bryan went through the review items and the choices from parts 5–17. These replace the matching "Picked without Bryan" lines in the PRs and the plan. **Part 17r** does them (roadmap, Phase D). Until it's merged, don't change these areas from another session.

**Gameplay**
- **Johto starters: no gate.** All three scenes are there from the start of Johto, not after Brendan & May. The unclaimed one is **an escapee from Elm's lab**, not Birch's ferry runaway. Elm's aide gives the hint, and it joins once it smells the lab on you. The calls and hints are reworded to match.
- **The wild one like your rival's** is at the area's level (about Route 46's, the Burned Tower's or Lake of Rage's wild level), not Hoenn's scaling.
- **Egg moves stay:** Aromatherapy, Extrasensory, Dragon Dance.
- **The meadow's wild grass stays Lv 3–8,** a baby-Pokémon meadow on purpose.
- **Totodile goes back to the plan:** a fisherman at Lake of Rage whose lines keep getting bitten. Fish his spot with the **Good Rod** and a Totodile clamps on. The Feraligatr-in-the-cove scene goes.
- **Weather days: trim to the plan.** Only routes where the weather fits get a special day; inland routes stay normal. Part 17r proposes the list in its PR.
- **Castform stays at 1–2 %.**
- **Charmander: evening only** (HnS's 6–7 PM), not nights.
- **The Squirtle Squad keeps its single trap.**
- **RYDER becomes DAMIAN** (the anime Charmander's trainer). His levels scale with your badges.
- **Route 26/27's replacements stay** (Sandslash, Raticate, Quagsire, Noctowl).
- **Kept as built:** TV forecasts (no radio), the name Tidal Strait, Chimecho for HnS's Safari Brush slot, dolls at ₽6,000.

**Look**
- **Rock base entrances: style B,** Emerald's solid square recess (Route 45, Mt. Moon). The tree entrances stay style A.
- **Base spots move off the walking path:** Sky Pillar (item 3) and the three Regi rooms (item 5). The chamber interiors' colours stay.
- **The meadow, the garden and the Squirtle hideout get a hand-made look.** Mockups go to Bryan before they're built. **Done in 17r-e** (Bryan approved the mockups; the meadow's two side trees got full tops after his note).
- **Battle backgrounds:** keep the picks (desert dunes, ash, graves) and fix the two nits (item 9).
- **Leaders' Pokémon stand behind them where there's room** (item 6).

**Text:** every new line from parts 5–17 goes into one doc, grouped by place, for Bryan to comment on.

**Bugs:** items 7, 8, 10 and 14, and the full map group (item 13), are fixed in part 17r.

## Open

### 1. Choices made without Bryan's approval (parts 5–17)
Parts 5–17 (PRs #32–#52) ran without approval gates. That covered dialogue, pets, shop lists and the part 13a secret-base entrance art, which `2.0-plan.md` said Bryan approves first. Each PR's description lists its choices. Go through those lists with Bryan and change anything he wouldn't have picked. Items 4 and 5 below are part of this.

### 2. Building interiors look too alike
These three use nearly the same room: the same table and chairs, in the same spot.
- The Olivine lighthouse keeper's family
- The Ecruteak dance teacher
- The Celadon florist

The building plan (`buildings.md`) called for variety. Give each room its own furniture layout, or a different template house.

### 3. Sky Pillar base spot is in the middle of the stairs (Bryan) — **done in 17r-b**
`SkyPillar_Top` (12,14), the chamber-base from part 12b, sits in the gap at the top of the stairs, where the player walks. It isn't hidden at all.
- **Fix:** move it to a stretch of wall off the walking path. Re-run `gen_hoenn_base_spots.py`, then check that the summit still reads like Emerald's.
- **Also update:** `HOENN_SECRET_BASE_ENTRANCE_POSITIONS`, which the generator writes.

### 4. Rock base entrances in Johto/Kanto are only an outline — **done in 17r-b**
Route 45 (`Route45_hns` 30,78) and Mt. Moon (`MtMoon_Cave_hns` 18,20) both have this problem.
- **What's wrong:** the closed entrance from part 13a is a thin arch outline. The rock texture shows through the middle, so it looks unfinished.
- **What it should look like:** the filled dark indent that Emerald's spots use.
- **Fine as they are:** the tree entrances in Ilex Forest and Viridian Forest. They're a small dark hole in the trunk, which reads correctly.
- **Fix:** repaint the rock pair in `gen_hoenn_base_entrances.py` / `base_entrances.json` so the inside is dark.

### 5. Regi room base spots are front and centre (Bryan's call) — **done in 17r-b**
Desert Ruins, Island Cave and Ancient Tomb all put their spot at (8,2). That's the middle of the back wall, straight ahead of the entrance and above where the Regi used to stand.
- In an empty dead-end room this is easy to find, but it's not discreet.
- **If Bryan wants it hidden:** move it a few tiles to one side.

### 6. Put leaders' Pokémon behind them where there's room (Bryan) — **done in 17r-a**
Bryan would like each trainer's follower to stand **behind** the trainer when the tile is free, which should look cleaner. Today `gen_hoenn_followers.py` tries beside first, so all 30 stand to the side. The tile behind was checked with the generator's own rules (floor, nothing on it, not in a trainer's sight, doesn't cut anything off).
- **Room behind, 12:**
  - Falkner (9,3), Jasmine (8,3), Brock (6,4), Sabrina (14,10).
  - Johto's Elite Four: Will, Koga, Bruno, Karen, all (6,5).
  - Hoenn's Elite Four: Sidney, Phoebe, Glacia, Drake, all (6,4).
- **Wall behind, so they stay beside, 16:** Bugsy, Whitney, Morty, Pryce, Clair, Misty, Lt. Surge, Erika, Blue, Roxanne, Brawly, Wattson, Flannery, Norman, Winona, Juan.
- **Red** is left out: he faces away from you, so "behind" would put Pikachu in front of the stairs.
- **Fix:** in `choose_tile`, try the tile behind first, then the current order. Re-run the generator and re-shoot the 12. This also fixes the problem below.

**Drake's Salamence hides Drake.** In `EverGrandeCity_DrakesRoom`, Salamence stands at (5,5). It's a large sprite and covers Drake's left half. Moving it behind him, to (6,4), fixes that. Two smaller overlaps are probably fine: Blue's Rhyperior hangs over the edge of his mat, and Jasmine's Steelix overlaps her slightly.

### 7. Slateport aide greets you after you already have Mudkip (bug) — **done in 17r-a**
Reproduced in the emulator.
- **How it happens:** come in by the Tidal Strait (or the Lilycove ferry), get Mudkip from Birch, then walk into Slateport harbor. The `ON_FRAME` greeting (`VAR_HOENN_AIDE_STATE` == 0) still plays, but the aide is hidden (his flag is `FLAG_HOENN_RECEIVED_MUDKIP`). Nobody is standing there, yet "Oh! You must be …, from JOHTO!" plays anyway.
- **Origin:** part 16b. Part 14 makes it a normal route instead of a rare one.
- **Fix:** have Birch's gift script set `VAR_HOENN_AIDE_STATE` to 1, or skip the greeting when the flag is set.

### 8. May's strait call can ring long after the crossing — **done in 17r-a**
`HOENN_CALL_STRAIT` needs `FLAG_HOENN_BM_PHONE`.
- **The problem:** if you cross before Birch gives you the numbers, the call rings whenever you get them. "Dad *just* got a call from Mr. Briney" then comes hours late.
- **Fix:** mark the call done if you crossed without the phone, or word it so the timing doesn't matter.

### 9. Part 13b backgrounds: two visual nits — **done in 17r-d**
- **Desert at night:** the sky and dunes darken, but the flat sand in front keeps its daytime colours, so it looks lit wrong.
- **Graves:** some headstones and a cross sit right behind the player's back sprite, so a cross pokes out beside the head.
- The plan said Bryan approves mockups first; that was skipped (item 1).

### 10. Burned Tower: from the west stairs you never see the Typhlosion family (bug) — **done in 17r-a**
Reproduced in the emulator: step down the west stairs at night onto (8,17). The whole scene plays with the camera on the player, and the family at (16–18, 14–15) stays off screen.
- **Why:** `HoennSeek_EventScript_StarterPanDown` only pans the camera down 2 tiles, and only when the player is above row 14. The south-west trigger row (x 8–13, row 17) gets no pan, and from x 8–9 the family is out of view.
- **Fix:** pan toward the family from wherever the scene starts, or move the camera to a fixed spot over the embers.

### 11. The two new maps look generator-made — **done in 17r-e** (all three maps hand-painted from Bryan-approved mockups, Squirtle hideout too)
`Route46_Meadow_hoenn` and `Route25_Garden_hoenn` work, but they're very boxy. Each has a straight border of identical trees and a flat open lawn with scattered flowers. The meadow also has a solid cliff band and a big rectangle of tall grass. The garden has a pale rectangle in the middle.
- **Fix:** hand polish, such as uneven tree edges, a path, a ledge or a pond, and Sunkern spread through the grass (the text says the meadow is "full of SUNKERN"; about five are visible).
- The meadow's wild table is Lv 3–8, for a post-game player. That's probably on purpose (baby Pokémon), but Bryan should confirm it.

### 12. Totodile's scene isn't the planned one — **done in 17r-c** (ANDRE's spot + GOOD ROD)
- **The plan:** a Lake of Rage fishing spot, a fisherman whose lines keep getting bitten, and fishing it with the **Good Rod** until a Totodile clamps on.
- **Part 15b instead:** a Feraligatr surfaces in the south cove and the Totodile hops ashore. There's no fisherman and no fishing.
- **Also dropped:** the plan's "stay hidden behind a pillar" bit in the Burned Tower is only a line of text.
- Bryan should decide whether to keep these or go back to the plan.

### 13. Smaller things from parts 15a–16
- **RYDER outside the Cerulean Gym** stands right under the gym's round sign, so his head covers it. Moving him a tile would look cleaner.
- **Done in 17r-a:** **`gMapGroup_SpecialArea_Hns` is full** (128 maps; the Tidal Strait's east half is number 127, the last one that fits in an `s8`). New maps go in `gMapGroup_SpecialArea2_Hns`, but `gen_hoenn_buildings.py` still appends to the full group. The next building would hang the game on load. Point the generator at the new group before anyone adds one.
- **RYDER takes Emerald's unused `TRAINER_LEROY` slot.** That shifts every Hoenn trainer ID after it by one, so a save made on a build from before part 16 would have its Hoenn "defeated" flags shuffled. Saves aren't meant to carry over between dev builds, but don't use an old 2.0 test save for a playtest.
- **Suicune at the Route 25 overlook** stands right next to the new garden gap on a fresh save. Already on the playtest checklist; check it there.

### 14. Vermilion fire: the camera never comes back (bug, serious) — **done in 17r-a**
Reproduced in the emulator.
- **What happens:** `HoennSeek_EventScript_VermilionFire` pans the camera tile by tile to the burning house, then ends with `special RemoveCameraObject` and never pans back. Afterwards the view stays offset from the player. Once you walk a few steps, the map draws in the wrong places (repeated, wrapped strips) until you leave the map.
- **Fix:** pan back the same number of tiles before `RemoveCameraObject`, as Emerald's camera scenes do (e.g. keep the step counts and walk the camera back).
- **Not tested** because of this: talking to the leader after the fire.

### 15. Part 17 nits
- **The smoke is very faint:** a couple of small `FLDEFF_ASH_PUFF` puffs on the roof, so the house doesn't really read as on fire.
- **The sunglasses only exist in the text:** the Squirtle leader uses the plain Squirtle sprite.

### 16. Parts 20–21: the grotto, the Slaking clearing and the orchard look generator-made (same as item 11) — **done in 21r**
- **Route 113 grotto** (part 20, `Route113_Grotto_hoenn`) and **Tropius's orchard** (part 21, PR #64, `Route119_Orchard_hoenn`) use the template that item 11 replaced: a box of floor inside a ring of identical trees, a tree clump in each corner, and a 2-wide way in at the bottom. The items and flowers are placed symmetrically.
- **Petalburg Woods clearing** (part 20, patched into `PetalburgWoods`): a 10×4 rectangle cut out of the forest. Its left and right edges slice 2×2 trees in half (half-trees at x 20 and x 31, rows 2–5, visible in game). Row 6's "tree tops" are walkable and look like bushes you stand on.
- **Fix:** hand-paint them like 17r-e (`grid` and `src` ops in `composed_maps.json`), mockups to Bryan first. The clearing needs whole trees on its edges, not cut ones.

### 17. Slaking can shut you inside its clearing (part 20) — **withdrawn in 21r**
- Petalburg Woods' OnTransition puts the Slaking back in the notch (26,7) on every load, unless it's caught or already battled today. The notch is the clearing's only way out.
- **How it happens:** beat it at noon, walk into the clearing, save there, and load the next day (or any later day). The Slaking is back, asleep, and only moves at hour 12. You're stuck until noon unless you Fly (Petalburg Woods is `MAP_TYPE_ROUTE`, so Fly works, but Escape Rope doesn't).
- **Fix:** don't place it while the player is inside the clearing (rows ≤ 6, x 21–30), or let the dozing Slaking's talk script let you squeeze past from the north side.
- **Withdrawn:** this can't happen. Continuing a save restores the saved objects (`CB2_ContinueSavedGame` doesn't run OnTransition), so the Slaking stays gone; the map only reloads when you leave the clearing.

### 18. The Munchlax is mostly hidden under the treetops (part 20) — **done in 21r** (moved to (14,14), on open ash)
- At (14,15) it sits in a one-tile gap, but the trees around it draw over its lower half. From the path above, you see the top of its head behind the player. The gap itself doesn't read as a gap either (the canopy continues over it, with a slight seam down column 14).
- **Fix:** open the canopy over (14,15)–(14,16), or move it one tile up onto the open ash.

### 19. PR #64 (part 21) can't merge yet — **done** (the other account merged it)
- GitHub reports merge conflicts with `hoenn`. 17r-e (PR #63) reformatted `data/hoenn/composed_maps.json` (one op per line) and added part 20's grotto under the new format, and part 21 adds the orchard to the old one. The fix is mechanical: take `hoenn`'s file, add the orchard map and the Route 119 patch, run `gen_hoenn_composed_maps.py` (the other maps must come out unchanged). The docs (roadmap, CLAUDE.md size table) need the usual merge too.

### 20. Choices from parts 18–21 for Bryan to confirm (all listed as "picked without Bryan") — **settled in 21r** (Bryan: "sort it however you see best"): Feebas is a fixed Lv 44 (Route 119's Old Rod level); the orchard tree drops only in the morning (plan), odds kept; the lake island, the woods boy's hint and the Black Belt stay
- **Levels:** Feebas is scaled to 60–70 like the battles. A Lv 60+ Feebas is odd for "the shabby fish"; the gifts are lower (Munchlax 42, Gengar 50, Ralts and the starters 5).
- **Zangoose vs. Seviper:** the plan's "hidden grassy hollow" became Route 114's lake island, which you can see from the bridge, so it isn't hidden.
- **Orchard fruit tree:** drops any time of day (plan: each morning). Lum/Sitrus two times in three, the rare seven one in three (plan: always rare, better with Tropius leading).
- **Slaking's hint** comes from a Petalburg Woods boy, not Norman (the plan had Norman say it).
- **Machamp reward:** Black Belt (plan: Macho Brace or Black Belt). Slaking's clearing already has a Macho Brace.
- **The Slowking's prophecy** is original wording (the plan quoted the film; original is right for copyright).

## Withdrawn
- **Mt. Moon base next to Silver's trigger.** This was wrong. Silver's rematch is an `ON_FRAME` script that runs when you enter the cave (`VAR_PEWTER_CITY_STATE` 0/1), not a tile trigger, so the base spot doesn't clash with it.

## Checked and fine
- **Parts 18–20, checked on `hoenn` after PR #66 (Claude, 2026-11-26), part 21 from PR #64's branch:**
  - Code read: `src/hoenn_species.c`, `src/hoenn_hidden.c` (part 21's female re-roll and wild-double setup too), every script in `hoenn_species.inc`/`hoenn_hidden.inc` for the scenes above. No logic bugs found beyond items 17–18.
  - In the emulator: the Mudkip pond (practice, the dive, the rain), the Slaking dozing at 1 PM and battling at noon (Lv 60), the clearing, the grotto, talking to the sleeping Munchlax without the flute.
  - Object placement (rendered from the maps): the Ralts/Gardevoir patch and pond family on Route 102, Kiyo and the Machamp in Mt. Mortar, the Scizor and Scyther in the National Park, the Radio Tower Gengar, Spinda's ring, the feud island and the mirror pool all sit where they should.
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
