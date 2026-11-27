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

### 16. Parts 20–21: the grotto, the Slaking clearing and the orchard look generator-made (same as item 11) — **done in 21r** (the grotto's entrance still cut trees; redrawn on the 2×2 tree grid in 21r-b)
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

### 20. Choices from parts 18–21 for Bryan to confirm (all listed as "picked without Bryan") — **settled in 21r** (Bryan: "sort it however you see best"): Feebas is a fixed Lv 19 (Bryan); the orchard tree drops only in the morning (plan), odds kept; the lake island, the woods boy's hint and the Black Belt stay
- **Levels:** Feebas is scaled to 60–70 like the battles. A Lv 60+ Feebas is odd for "the shabby fish"; the gifts are lower (Munchlax 42, Gengar 50, Ralts and the starters 5).
- **Zangoose vs. Seviper:** the plan's "hidden grassy hollow" became Route 114's lake island, which you can see from the bridge, so it isn't hidden.
- **Orchard fruit tree:** drops any time of day (plan: each morning). Lum/Sitrus two times in three, the rare seven one in three (plan: always rare, better with Tropius leading).
- **Slaking's hint** comes from a Petalburg Woods boy, not Norman (the plan had Norman say it).
- **Machamp reward:** Black Belt (plan: Macho Brace or Black Belt). Slaking's clearing already has a Macho Brace.
- **The Slowking's prophecy** is original wording (the plan quoted the film; original is right for copyright).

### 21. The Wailord can't be reached (part 22b) — **done in 22r-a** (the rock at (18–19, 33–34) removed; surfed in from open water in the emulator)
- The strait's water pocket on Route 131 (x 13–19, rows 33–37) is closed off by rock on every side. You can't surf into it from the sea, from Route 130 or from the bottom strip. The only way out is the Wailord's tile and its warp to the atoll, so the Wailord and the atoll can't be reached in normal play. The emulator agrees: from (11,32) you can't move toward it, and from inside (16,36) you can't move out.
- More evidence: part 20a's overworld-Pokémon generator put a Tentacruel at (15,36) and a Pelipper at (18,35) in that pocket because it found the pocket unreachable. A third Tentacruel sits at (16,32) in a one-tile gap above it. Part 22b's tests reached the Wailord by warping.
- **Fix:** open a channel from the main sea into the pocket (the `composed_maps.json` patches on both Route 131 layouts), then re-run `gen_hoenn_ow_mons.py` so no Pokémon sits on the new path. Check it in the emulator by surfing in from open water, not by warping.

### 22. The clifftop and the atoll look generator-made (parts 22b, 23; same as items 11 and 16) — **done in 22r-b** (Bryan approved the mockups: a mountain meadow ringed by Route 114's rock, and a sand ring around a lagoon)
- **Meteor Falls clifftop** (`MeteorFalls_Clifftop_hoenn`): a box of floor inside a ring of identical trees, which is what the CLAUDE.md convention rules out. The cliff in the middle has no corners: its top edge runs across the whole clearing (x 1–14, row 3), but the cliff face only spans x 4–13. So at both ends the edge hangs over plain floor.
- **Route 131 atoll** (`Route131_Atoll_hoenn`): it isn't an atoll. It's open sea with rocks spaced evenly around the map edge and three sand islands with columns of trees stacked 4–6 high. There's no reef ring and no lagoon (the Wailord's "lagoon" is just open water), and no Luvdisc pond (plan section 7). Some treetops stick out over the water at the islands' top edges.
- **Fix:** hand-paint both from a mockup Bryan approves first, as in 17r-e and 21r.

### 23. Choices from parts 22a–23 for Bryan to confirm — **chorus reward settled in 22r-b** (Bryan: a Star Piece each week); the rest stay as built unless Bryan says otherwise
- **Chorus reward:** a Pretty Feather each week. The plan says a Comet Shard or Star Piece each week. The Comet Shard went to the Metagross scene instead (first time; a Star Piece after). A Pretty Feather is worth much less than the plan's reward.
- The rest are listed as "picked without Bryan" in PRs #71–#73 and the plan:
  - Absol: the ridge as the "cliff ledge", the normal wild battle theme, its level (gym ace − 8 the first time, then fixed).
  - The strait's spot and the lagoon rematch.
  - Chimecho's Cleanse Tag.
  - The chorus's hide and scare rows, and the flute prompt coming mid-song.
  - Bagon's hint going to Fallarbor's gentleman.
  - All new text and callers.

### 24. Small things from parts 22a–23 — **done in 22r-a** (new texts: "In a flash of light, the two METANG fused into a METAGROSS!", "You saw it too!"; Absol never meets you while surfing (Bryan); the overworld Pokémon re-run moved the Glooms off the ridge; section 14 ticked)
- **Text:**
  - `HoennSeek_Text_MetagrossFused` ends on a one-word line ("METAGROSS!"), which the CLAUDE.md rule forbids.
  - Brendan's Metagross call ends with "right in front of him. And of you!", which reads oddly.
- **Absol can turn up while surfing:** `TryStartRoamerEncounter` also runs for water encounters, so on a storm night it can come out of Route 120's ponds. That's upstream roamer behavior, so it's fine if Bryan doesn't mind.
- **Absol's ridge** has two overworld Vileplume right above and below it ((16,48), (16,52)), so three Pokémon sit in a column.
- **Plan section 14's to-do list** ticks only the Wailord. Absol, the chorus, Chimecho, Bagon and the Metagross (and the earlier parts' events) are still unticked.

### 25. The Trapinch walks right through you (part 24a, bug) — **done in 24r**
- The Trapinch's path runs straight up column 26, and the ring's north trigger (26,54) is on it. Coming down from the north (the natural way in from the dunes) you step on (26,54), and the Trapinch walks up through your sprite.
- **Fix (24r):** from (26,54) you step one tile left first, then the scene plays. The other 31 ring tiles are off the path (the south one, (26,62), is behind it). Checked in the emulator from the north, south and west.

### 26. The sand hollow hardly shows (part 24a, look)
- The hollow at (29–31, 35–36) is the desert's own darker deep-sand blocks, so it looks like one more of the faint dune patches around it, not a hole the Trapinch dug into. You only find it by reading it.
- Not changed: a real pit would need a new tile or a darker recolour, which is new art and needs Bryan's OK. Screenshot in `part-24r/part-24r-screenshots.png`.

### 27. Choices from part 24a for Bryan to confirm
- Listed as "picked without Bryan" in PR #77 and the roadmap: the Trapinch's spot and trigger ring, the camera following it, the hollow being a deep-sand patch (item 26), evening only (HnS's one-hour evening), once a day, Fallarbor's gentleman as the elder plus Cozmo, the Underpass nook, the Vibrava being uncatchable at the scaled level with Boomburst, Vibrava any time underground, the Singing Sand's icon (Soft Sand's), Brendan as caller, all text.
- One effect to know about: the Fallarbor gentleman's desert line comes before his Bagon line, so while the chain is open he no longer gives the Bagon hint.

### 28. PR #79 (24r) isn't merged and now conflicts (parts 24a–26b review) — **done** (merged with `hoenn` by hand and merged, Nov 27)
- PR #79 fixes a real 24a bug: the Trapinch walks up column 26 straight through you if you trigger the scene from the ring's north tile (26,54). It also adds review items 25–27 (that fix, the faint sand hollow, 24a's choices). It was opened before parts 24b–26b merged, and GitHub now reports conflicts in CLAUDE.md, the roadmap, the playtest list and these notes. **The bug is still on `hoenn`.** Rebase and merge it (items 25–27 then land above this one).

### 29. Small text things from parts 25a–26b — **done in 26r** (PR for `v2-26r-text-fixes`: "crack. It's wide enough to / swim down!"; the diver is "he" in both calls)
- `HoennSeek_Text_CrackLit` ends on a one-word line ("down!"), which the CLAUDE.md rule forbids.
- **The Mossdeep diver is a man:** the hint NPC at (38,12) is the male sailor sprite (`OBJ_EVENT_GFX_SAILOR`, "I dive off ROUTE 124 every night"). But both trench calls call the diver "she": Brendan's "She was night diving off ROUTE 124" and May's "She talks to PROF. BIRCH about everything". Change both to "he".

### 30. Docs — **done in 26r** (section 14's ice chamber ticked)
- Plan section 14's master list still has the ice chamber unticked, though 26b finished it.

### 31. Choices from parts 24b–26b for Bryan to confirm
Each PR lists its "picked without Bryan" choices. These are the ones that change what the plan says:
- **Mirage Tower (24b):** it stands until midnight after the chime. The fossils stay behind the Flygon, and taking one still ends the tower for good. The Flygon is catchable and comes back after a knockout. The Underpass Vibrava (24a) can't be caught.
- **Night dive (25a/25b):** once found, the crack and the guardians are there at any hour, though the plan's diver line says "at night". The "back wall" is the mound's old Seafloor Cavern door: the trench's top wall is on the map edge. Both are written into the plan.
- **Ice chamber (26a/26b):** Froslass is drawn standing on the ice rock, not as a reflection inside it. The feather also comes after a knockout, not only a catch. Plan step 5's optional Icy Rock trade was left out.

### 32. Part 27a review (PR #86, Claude, Nov 27) — **fixed in PR #86 before merging**
- **The braille window cut the Rosetta off.** `braillemessage` caps its window at 28 tiles, so AT NIGHT WE SPEAK showed as "AT NIGHT WE SP" (visible in the part's own grid, panel 3). Now two lines, AT NIGHT / WE SPEAK; checked in the emulator.
- **The researcher's word list ran off the text box.** "Night words so far: {STR_VAR_2}." had no line breaks, so with three or more words it went past the box's edge (six words were ~59 characters on one line). The list now goes on its own line and `HoennCipherWordCount` starts a new one after every third word; checked in the emulator with six words.
- Checked and fine: the visited flags `HoennCipherIsOpen` reads are all Hoenn-owned (0x1B01–0x1B0E, never set at new game); the Rosetta's row 3 in Words Room 1 was plain floor, so nothing original is drawn over; the swapped lab scientist only had flavour text; every other new text fits the box (measured with the font's glyph widths); the unown-tiles and hints generators re-run with no changes.
- 27a's flags (`HOENN_FLAGS_E_JOHTO_KANTO` + 0x00–0x0A) and call ID 37 sit at the start of lane A's ranges from the lane setup (PR #85), as that PR expects: lane A's 27b continues from + 0x0B and call 38.

### 33. Lane setup review (PR #85, Claude, Nov 27) — **merged**
- Merged third, after #79 and #86, so the reviewer did the sync (lanes rule 3.5): 27a's flags moved under lane A's header as `HOENN_LANE_A_FLAGS_E + n` (same IDs), `HOENN_CALL_CIPHER` (37) moved into lane A's call section, its due check into `HoennLaneADueCall` and its case into `hoenn_lane_a.inc`'s switch. 27a's hint NPC (the lab scientist, entry 55) got the key `AlphLabScientist`.
- `regen_all.sh` didn't run 27a's new `gen_hoenn_unown_tiles.py`; added. `regen_all.sh --check` reports no changes on the synced branch.
- Emulator on the synced debug ROM: Brendan's cipher call rings through the lane chain (after Elm's), the lab scientist alternates his own line and his hint line, a keyed building NPC (Route 6 Bug Club) still alternates.
- One thing to know: the lane rules say the reviewer "writes notes, not fixes" and sends small fixes back as `NNr` parts. This review fixed 27a's two text bugs in place before merging instead, because 27a's builder had already moved to lane B and the fixes were a few lines.

### 34. The new floor lines can't be read from the wall (part 27a, for lane A's 27r) — **done in 27r** (room 1 reads from row 1 too, rooms 2–4 from rows 1 and 2; checked in the emulator)
- Words Room 1's braille (row 2) and the Unown line under it (row 3) are walkable floor, and so is the row of rooms 2–4's night word. A player who walks up to the north wall ends up standing on the braille, and A at the wall does nothing. Reading works only from one row further back, facing up. (This tripped the reviewer's own emulator test too.)
- Fix: add the same bg events one row up: room 1 row 1 (`HoennSeek_EventScript_CipherRosetta`, x 2–18 except the spaces) and rooms 2–4 row 2 (`HoennSeek_EventScript_CipherWordSign`). Check first that row 2 in rooms 2–4 has no original sign on it.

### 35. The night word changes at midnight, halfway through the night (part 27a, suggestion for 27r) — **done in 27r** (`HoennNightWeekday()`: hours after midnight count as the evening's day; Saturday 2 AM shows Friday's UNION in the emulator; 27b's rings use it too)
- Night runs from evening to 4 AM, but the word follows `GetDayOfWeek`, which turns over at midnight. So on Friday night the rooms show UNION until midnight, then FOAM (Saturday's), and one late night gives two words. The researcher's "a different word every night" is then not quite true.
- Suggestion: treat hours before `NIGHT_HOUR_END` as the previous day in `HoennCipherDrawRoom`, `HoennCipherTonightWord` and `HoennCipherNoteWord` (one helper), so a night is one word from dusk to dawn. 27b's glyph sites should use the same helper. Bryan can say keep it as is; collecting stays easy either way, since any wall clock changes the day.

### 36. 27b: rings lose letters when a Pokémon follows you (bug, review of PR #88, Nov 27) — **fixed in PR #88 before merging**
Each Unown form is its own species with its own compressed sprite sheet (6 frames, 96 tiles), and a compressed sheet is loaded whole. On Whirl Islands B2F at night, five letters, the map's other overworld Pokémon and the debug Lapras following the player ran out of sprite memory: H and I were never spawned (WHIRL read W, R, L).
- **Fix (reviewer, Bryan's go-ahead):** `HoennSeek_EventScript_GlyphRingArm` sets `FLAG_TEMP_HIDE_FOLLOWER` when the map's ring is out, so your Pokémon stays in its ball for that visit (a temp flag; it comes back on the next map).
- **Checked:** all seven rings walked to from a real entrance with Lapras leading (Ice Path by sliding in): every letter spawned and visible. `review-27b-fix.png` in the project's `hoenn-2.0/review/`.
- **For later parts:** don't put more than about four *different* Pokémon sprites on one screen; same-species objects share a sheet.

### 37. Review of 27r (PR #93) and 27b (PR #88) (reviewer, Nov 27) — **merged**
- **27r:** the night word is one word from dusk to dawn (Sat 10 PM FOAM, Sat 2 AM still Friday's UNION, Fri 9 PM UNION, Sat noon none); the word reads from the wall row. Merged as built.
- **27b:** `regen_all.sh --check` clean; seven rings spell their words, reachable on foot from the entrances (Bell Tower stairs, Mt. Moon Square's cave mouth, Route 44, Whirl B3F ladder, the Mortar ledge passage, Union Cave 1F, Route 20); talking starts the right letter. Bryan approved every choice listed in the PR (sites, ring per seen word, Lv 60–70, fragments as flags, ANCIENT, May's call).

### 38. Review of 31b (PR #90) (reviewer, Nov 27) — **merged** (Bryan approved every choice)
Built by this thread before it took over reviewing, so read with that in mind. Merged `hoenn` at #88 into the branch (one hint-list conflict: kept 27b's `STORY_CIPHER_RINGS` line and 31b's Blackthorn Mart rumor); `regen_all.sh --check` clean; size row re-measured (+6,944 B release).
- **Played start to finish** on a fresh debug save: HONEY from the beekeeper (once a day), spread on the pine, nobody the same morning, two Teddiursa on a later morning, watch three times (the third says they trust you), shoo keeps the honey and the day's flag, the fourth honey brings the mother, at night she leads you up the claw cliff into the hollow (scene, `FLAG_HOENN_MOON_HOLLOW_FOUND`, stage 2), bears and pool lines by night and day, trail back down, claw marks climb any time afterwards, Brendan's call rings once. No bugs found.
- **Looks:** the house and the nook sit well in Route 45 at 2×; the hollow is a hand-painted rock bowl. One thing Bryan may not like: a single 2×2 bare-ground patch west of the pool (planned as "where the bears sit", but nobody sits there).
- **Fog:** Route 45 is a fog-cycle route, so on its fog day the meadow scene is hard to see. That's the weather working as designed.
- Grid: `review-31b.png` in the project's `hoenn-2.0/review/`.

### 39. Review of 34a (PR #91) (reviewer, Nov 27) — **merged** (Bryan approved every choice)
Built by this thread before it took over reviewing. Merged 31b's branch (with `hoenn` at #88) in; conflicts only in the size table, the hint list and `data/specials.inc` (the bird specials now sit under lane B's marker). `regen_all.sh --check` clean; size row re-measured (+6,368 B release). No map layouts change.
- **Played:** Bill's intro and per-bird report (clue → "waiting at its roost" with directions → caught); the manager's hint on a normal day and the feather on Route 10's storm day; the engineer's forecast the day before; the Moltres flyover on Route 113's west path and the FLAME FEATHER pickup; the workshop boy's rumor. Roosts: Zapdos lands, **run** = it stays (still there on re-entry, no second landing), **knocked out** = gone today, back the next day; Articuno lands and is **caught** (Master Ball) = the islet stays empty; Moltres lands in view in Mt. Silver's room. May's call rings once on Route 10. No bugs found.
- **Worth Bryan's eye:** HnS's three birds used to sit at their spots from the start; now each needs its feather, so Articuno needs Hoenn's ice chamber (26b) first. Bill's first talk is long (about 16 boxes).
- Grid: `review-34a.png` in the project's `hoenn-2.0/review/`.

### 40. Review of 31a (PR #92, lane A) (reviewer, Nov 27) — **waiting on Bryan's go-ahead**
Merged `hoenn` (27r, 27b, 31b, 34a) into the branch: conflicts only in the lane A switch and sections (27b first, then 31a), the lane docs and the hint list (27b's, 31b's and 34a's NPCs, then the Blackthorn skater); `regen_all.sh --check` clean; size row re-measured.
- **Bug fixed in review:** Brendan's call said "Dad reads every gym's report", but Brendan's dad is Birch; it's May's dad (Norman) who reads the League reports. Now "MAY's dad gets every gym's report from the LEAGUE…" (checked in the emulator: fits the box).
- **Played:** with all four B1F boulders dropped, at night: ball 1 snatched, you slide on, ball 2, ball 3, the chase into the north-west nook (legs LLLLDLURU, LDDRDR, ULLLLDLURDDDRD, LUULD); cornered line; Lv 60 battle (Razor Claw, Pickpocket). **Knocked out** = stash given, gone that night, back in the nook the next; **run** = stays; **caught** = never shows again. Leaving mid-chase restarts it; nothing by day or with a boulder still up. The Blackthorn skater's hint by stage, Brendan's call once.
- **Choices for Bryan:** only on B2F; the three ball spots and the nook; needs every B1F boulder dropped; the Blackthorn skater as the hint NPC; the stash comes with a knockout as well as a catch.
- Grid: `review-31a.png` in the project's `hoenn-2.0/review/`.

## Withdrawn
- **Mt. Moon base next to Silver's trigger.** This was wrong. Silver's rematch is an `ON_FRAME` script that runs when you enter the cave (`VAR_PEWTER_CITY_STATE` 0/1), not a tile trigger, so the base spot doesn't clash with it.

## Checked and fine
- **Lane setup (#85), 27a (#86), 24r (#79) and 26r (#87), re-checked on `hoenn` at de86bdf3 (Claude, 2026-11-26):**
  - `regen_all.sh --check` reports no changes; release 32,709,828 and debug 32,869,076, matching the 26r row. (Running it rewrites `hoenn_desert/palette_night.pal` with LF line endings where `.gitattributes` wants CRLF; `git diff` shows nothing, so it's harmless.)
  - Lane ranges: each of the E/F flag blocks, the daily, weekly and hidden-item flags and the E/F var blocks is split between the lanes with no overlap, and nothing before the split used them except 27a's 11 flags. The phone chain falls through lane A's switch to lane B's and ends with `releaseall`.
  - 27a's palette 10 slot 13 (now the glow cyan) is also used by one old metatile, placed once in the Puzzle and Reward Chambers (4,18); it renders pixel-identical, since the other layer covers it.
  - In the emulator from a fresh debug save: Elm's escapee call, then Brendan's cipher call (says who told him); the lab researcher's ask and repeat lines; the Rosetta read from row 4 (braille window on two lines, the fanfare, the flag); Friday 10 PM in Words Room 2 shows UNION in cyan, centred, and notes it; the researcher's six-word list wraps after three words; seven words set `FLAG_HOENN_CIPHER_ALL_WORDS`.
  - 24r: `DesertStepAside` returns properly when you trigger from the ring's south tile (`HiddenEnd24a` is a `return`). 26r's three text fixes are in.
- **Parts 24a–26b, checked on `hoenn` after PR #83 (Claude, 2026-11-26):**
  - The debug build works, and every generator re-runs with no changes, including the overworld Pokémon (22r's lesson stuck).
  - Code read:
    - `src/hoenn_lights.c` and its step hook: a despawn or a battle mid-drift loses nothing.
    - The Mirage Tower hook: a crumbled tower still stays gone.
    - `HoennSandChimePlace`, the Sand Chime item use, and the 1.x Shoal flag fix in `hoenn_custom.h`.
  - Plan conformance: the events match section 7 and section 9's moves, abilities and items, apart from item 31.
  - Maps rendered with objects and triggers: the ice chamber, the trench, Underwater Route 124, the ice room, Route 111, Mirage Tower 4F, the Desert Underpass and Route 113.
    - Reachability: the light's start and the crack are in the region you reach by diving at the round dive spots.
    - Ice chamber items: the hidden NeverMeltIce (2,1) can be picked up (slide left from the ladder, face up), and the Dawn Stone is reachable.
  - **High tide in the emulator:** at noon after walking in from Route 125, the tide flag is set and the entrance room floods, wadeable as in Emerald. Nobody had reached high tide since 1.0 (the flag was 0), so this was worth a look.
  - New text was scanned (item 29). Every call says who told the caller.
- **Part 24a, checked on `hoenn` after PR #77 (Claude, 2026-11-26):**
  - Release and debug builds work; the debug size matches CLAUDE.md. Every generator (composed maps, overworld Pokémon, followers, buildings, hints) re-runs with no changes.
  - Code read: the whole Part 24a section of `hoenn_hidden.inc`, the Route 111 and Underpass hooks, the flags (no clashes), `ITEM_SINGING_SAND`, the call. Blacking out to the Vibrava is safe: HnS clears `FLAG_NO_WILD_CATCHING` on a whiteout (`src/overworld.c`), so catching isn't left switched off.
  - In the emulator at 6 PM: the scene from the north, south and west sides of the ring (footprints, the burrow, the camera back); none the same evening again; the hollow's text after the hum; the Underpass empty before the hum; the hum, the battle (Lv 60, Boomburst, catching off), running (it stays and battles again), winning (the Singing Sand, catching back on, gone on re-entry).
  - The Underpass Ditto that moved to (124,5) sits on a cliff top. That's the overworld generator's normal out-of-reach spot, not a bug.
- **Parts 22a, 22b and 23, checked on `hoenn` after PR #73 (Claude, 2026-11-26):**
  - The debug build works, and the composed-maps, buildings and hints generators re-run with no changes.
  - Code read: `src/hoenn_roamer.c` and its eight hooks in `src/roamer.c`. Absol can't loop in `RoamerMove`. Its slot stays reserved through the Hall of Fame's re-inits and is released by a new game. A stale Absol from an older game on the same save is handled. Peek, encounters and the Pokédex area page all ask the hooks. Also read: the battle theme hook and the `HOENN_TUNE_IV_HP`/`HOENN_TUNE_SHINY` additions.
  - Plan conformance: everything matches section 7 and section 9's special moves and items, except item 23's chorus reward.
  - Maps rendered with their objects and triggers: the Route 120 ridge, Meteor Falls 1F's new cave mouth, B1F_2R's Bagon ledge, Steven's cave, Mt. Pyre's summit rings. They're fine apart from items 21 and 22.
  - Every new text block was scanned for one-word last lines (item 24). The calls say who told whom.
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
