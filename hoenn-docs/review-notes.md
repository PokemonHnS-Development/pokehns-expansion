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

### 40. Review of 31a (PR #92, lane A) (reviewer, Nov 27) — **approved; merged after re-sync**
Merged `hoenn` (27r, 27b, 31b, 34a) into the branch: conflicts only in the lane A switch and sections (27b first, then 31a), the lane docs and the hint list (27b's, 31b's and 34a's NPCs, then the Blackthorn skater); `regen_all.sh --check` clean; size row re-measured.
- **Bug fixed in review:** Brendan's call said "Dad reads every gym's report", but Brendan's dad is Birch; it's May's dad (Norman) who reads the League reports. Now "MAY's dad gets every gym's report from the LEAGUE…" (checked in the emulator: fits the box).
- **Played:** with all four B1F boulders dropped, at night: ball 1 snatched, you slide on, ball 2, ball 3, the chase into the north-west nook (legs LLLLDLURU, LDDRDR, ULLLLDLURDDDRD, LUULD); cornered line; Lv 60 battle (Razor Claw, Pickpocket). **Knocked out** = stash given, gone that night, back in the nook the next; **run** = stays; **caught** = never shows again. Leaving mid-chase restarts it; nothing by day or with a boulder still up. The Blackthorn skater's hint by stage, Brendan's call once.
- **Choices for Bryan:** only on B2F; the three ball spots and the nook; needs every B1F boulder dropped; the Blackthorn skater as the hint NPC; the stash comes with a knockout as well as a catch.
- Grid: `review-31a.png` in the project's `hoenn-2.0/review/`.

### 41. Review of 29 (PR #94) (reviewer, Nov 27) — **merged**
Built by this thread before it took over reviewing. Merged `hoenn` at #91 into the branch (conflicts only in the size table and the generated hint header); `regen_all.sh --check` clean; size row re-measured.
- **Fixed in review:** the Onix's hole used `GetDayOfWeek()`, so at midnight it jumped to the next weekday's wall in the middle of the night (27r's rule is `HoennNightWeekday()` for anything weekly at night). Now Tuesday 2 AM still opens Monday's hole and Tuesday 10 PM opens Tuesday's (checked in the emulator).
- **Played:** the rumble and Monday's hole, no hole by day, the bore, the shiny Onix (Lv 51 on the debug save: cap 56 − 5; Diamond Storm), caught → Metal Coat where it lay, Tuesday's hole after the catch with no rumble, knocked out → gone for the night. Dark Cave's four holes by time of day, one row of rubble per time, the passage, the Three-Segment Dudunsparce caught, the ladder out. Route 21's islet: vines by day (Cut won't help), morning: the shiny Tangela caught, the Miracle Seed, no vines. Brendan's call, the three rumors.
- **For Bryan (all parts with night "back tomorrow" battles, not just 29):** HnS's daily flags reset at midnight, so a night Pokémon knocked out at 11 PM is back at 12:01 AM the same night (29's Onix, 31a's Sneasel). The docs say "back the next night". Either accept it or add a night-aware reset.
- **Choices for Bryan:** progress-based levels (cap − 5, floors 40/32/30) instead of Hoenn's 60–70; one hole per weekday into a single bore; the holes keep opening after the catch; one Dunsparce dig per time of day; a ring of Tangela vines (Route 21 has no cove); the three rumor NPCs (Lavender, Violet, Pallet).
- Grid: `review-29.png` in the project's `hoenn-2.0/review/`.

### 42. Review of 30a (PR #95) (reviewer, Nov 27) — **merged**
Built by this thread before it took over reviewing. Merged 29's reviewed branch in (one real conflict: `LoadDynamicFollowerPalette` now calls 30a's `HoennFollowerPaletteSpecies` and then 27b's `HoennObjectPaletteSpecies`; both are needed); `regen_all.sh --check` clean; size row re-measured.
- **Code read:** the baby is the follower while `FLAG_HOENN_KANGA_BABY_FOLLOWING` is set *and* you're in the Safari Zone; it's drawn as `SPECIES_NONE` there (no real Pokémon uses it), with Kangaskhan's palette tag, so a wild Kangaskhan object shares the palette without clashing. Talking to it runs its own script.
- **Played:** evening on the Beach at SAFARI LEVEL 2, the baby joins and follows (your follower steps aside), through a Safari battle and across the Beach → Brush connection; the mother alone in the nook; the reunion (hearts, LUCKY EGG); the pair afterwards; nothing by day or at level 1; leaving the Safari sends it back to the Beach; the attendant's rumor; May's call. No bugs found.
- **Choices for Bryan:** evenings only; needs SAFARI LEVEL 2; its own hand-drawn sprite; the Safari's step limit as the timer; the mother's new nook cut into the Brush's trees; a Lucky Egg as the thanks; neither is catchable.
- Grid: `review-30a.png` in the project's `hoenn-2.0/review/`.

### 43. Review of 30b (PR #96) (reviewer, Nov 27) — **changed on Bryan's review, approved, merged**
Built by this thread before it took over reviewing. Merged 30a's reviewed branch in (conflicts only in CLAUDE.md and the generated hint header); `regen_all.sh --check` clean; size row re-measured.
- **Code read:** the herd task (`Task_HoennStampede`) moves the template coords first, so off-screen Tauros keep their rhythm; it idles while a script or menu holds you and stops for good once the week's bull is gone. A hit is a Tauros starting a step onto your tile.
- **Played:** Monday morning on the highland (from the Mountain's canyon); getting hit (long line the first time, short after) and landing at the canyon; crossing all six lanes by timing; the lead bull (Paldean Blaze this week, progress level, perfect Atk/Speed, a normal battle with your own balls); ran → it stays; caught → the herd grazes for the week; next Monday the next breed (Aqua) leads; Tuesday and Monday afternoon empty; the entrance attendant's rumor before and after; Brendan's call. No bugs found.
- **Choices for Bryan:** a new highland map above the Safari Mountain (SAFARI LEVEL 3); Monday mornings; six lanes at mixed speeds; a hit costs only Safari steps; the three Paldean breeds rotate weekly, skipping caught ones; a normal battle, not a Safari one; knocked out = back next Monday; after all three, the herd still runs with no leader.
- Grid: `review-30b.png` in the project's `hoenn-2.0/review/`.
- **Bryan's change:** no battle with your own Pokémon in the Safari ("Everything but the battle is fine"). The lead bull is now a **Safari encounter** (BALL, POKéBLOCK, GO NEAR, RUN; Safari Balls only). `special HoennStartScriptedSafariBattle` starts HnS's own Safari battle, and a small hook in `CB2_EndSafariBattle` sends you back to the bull's script, which reads the outcome. Fled = gone until next Monday and the herd grazes (it used to be "knocked out"); ran = it stays; out of balls mid-encounter ends the Safari the usual way and the bull stays; a catch with the last ball finishes the bull's lines, then ends the Safari. Normal Safari battles don't touch the hook.
- **Re-played after the change:** the encounter (Paldean Blaze, Lv 51, Safari menu); ran → stays, the herd keeps charging; GO NEAR until it fled → "thundered off", gone for the week, herd grazes; caught with Safari Balls → nickname, the herd's lines; one ball, missed → "out of Safari Balls", back at the entrance, bull not caught; one ball, caught → the herd's lines, then the Safari ends. Grid: `review-30b-safari.png`.

### 44. Review of 36 (PR #98) (reviewer, Nov 27) — **approved; merged after re-sync onto `hoenn` at #96 (ORBS, weather day and Kyogre re-checked)**
Built by this thread before it took over reviewing. Merged 30b's reviewed branch in (conflicts only in CLAUDE.md and the generated hint header); `regen_all.sh --check` clean; size row re-measured (+7,072 B release).
- **Played:** the old man before the Maxie + Archie double (Emerald's legend) and after it (both ORBS, then a short reminder); Routes 19/20 on their fog day without the ORBS (fog), with them (downpour on 19, drought on 20) and on other days (normal); Route 19's cave and Seafoam's secret cave empty without the ORB or on other days; Kyogre (Lv 70) caught → gone for good; Groudon knocked out → gone, back the next day, then caught; Brendan's call; the Sky Pillar mural before both titans (carving only) and after (JADE ORB); Embedded Tower empty at 11 AM, Rayquaza at noon, caught; May's call; Southern Island's sign, the three shards, the Pewter Museum expert's ENIGMA STONE; the grove empty without the stone, Latios (the non-roaming Lati on this save) with it; ran → it stays; caught → gone. No bugs found.
- **Choices for Bryan:** the ORBS come from Mt. Pyre's old man after the Maxie + Archie double; Kyogre and Groudon now need their ORB (HnS's caves had them waiting from the start) and appear only on the Seafoam waters' fog day, which the ORB turns into downpour/drought; HnS's levels kept (titans and Rayquaza 70, Lati 50); the JADE ORB from a new Sky Pillar mural once both titans are caught, Rayquaza only at noon (not on Route 47's rain day); the Lati needs the ENIGMA STONE (three shards on HnS's Southern Island, joined by the Pewter Museum's expert); knocked out = back tomorrow (midnight, see item 41); the hints and two calls.
- Grid: `review-36.png` in the project's `hoenn-2.0/review/`.

### 45. Review of 35a (PR #100) (reviewer, Nov 27) — **approved; merged after re-sync onto `hoenn` at #98 (dawn blur re-checked)**
Built by this thread before it took over reviewing. Merged 36's reviewed branch in (conflicts only in CLAUDE.md and the generated hint header); `regen_all.sh --check` clean; size row re-measured.
- **Code read:** the six-page count, the cameo (its object is re-hidden on every check, so it only shows inside the scene), Cerulean B2F's state (pages, caught, gone today), the battle result, the blur state (dawn hours, its piece, `FLAG_CAUGHT_MEW`), the two calls. No bugs found.
- **Played on a fresh debug save:** the four page spots (Silph lobby, Game Corner plant, Mahogany hideout B3F, Goldenrod warehouse) with counts and done texts; Fuji at 4 pages (hints at the crater and his own page) and at 5 (gives page 6, then his after-line, and his line after the catch); Cinnabar's crater page and the 4-page cameo, from the page and on arrival; B2F empty at 5 pages, Mewtwo at 6 (Lv 80); ran → stays, knocked out → gone, back the next day; caught → gone; Brendan's call. Mew blurs on Routes 1, 22 and 101 at 5 or 6 AM (none at noon), each dashing off at three tiles and leaving a scrap; the OLD SEA MAP; May's call; the Vermilion sailor's FARAWAY ISLAND trip; Vermilion's old map ball gives a BIG PEARL.
- **Choices for Bryan:** Mewtwo now needs all six pages (HnS had it in the cave from the start); Faraway Island now needs three dawn sightings (HnS gave the OLD SEA MAP free in Vermilion); dawn is 4–8 AM; page spots (a plant because HnS's Game Corner has no basement, Silph's lobby because HnS only has the lobby, Goldenrod's warehouse as the "second hideout"); the plan's Whirlpool/Dive gates dropped; HnS's levels kept (Mewtwo 80); the 4-page cameo; Fuji's role.
- Grid: `review-35a.png` in the project's `hoenn-2.0/review/`.

### 46. Night-aware reset (41r, reviewer, Nov 27) — **built on Bryan's yes to item 41; approved and merged**
Item 41's question: Bryan chose a night-aware reset. A night event's daily flag no longer resets at midnight: nights are counted from noon to noon (like `HoennNightWeekday()`), so a Pokémon knocked out at 11 PM stays gone through the small hours and is back the next evening.
- **Which flags:** every daily flag of an evening/night-only event: Feebas (evenings and nights), Chimecho, the trench guardians, Froslass, Sneasel, and the Onix (gone + the once-a-night rumble). Not the birds, Dudunsparce, the legends or Mewtwo (any time of day), and not Glalie (never at night). Weekly night events (Metagross, Zangoose vs. Seviper) are unchanged.
- **Played (debug save):** Saturday 10 PM with all six flags set (and two daytime ones); Sunday 1 AM: the daytime flags cleared at midnight, the night ones kept, the ice chamber quiet; 11 AM still kept; 1 PM all cleared; 9 PM Froslass back ("A chill runs down your back"). Setting the clock back two days re-records the night without clearing; moving forward again clears, the same as HnS's daily flags.
- Grid: `41r_night_reset.png` in the project's `hoenn-2.0/review/`.
- **For the lane A PRs still open (32, 28, 35b) and 33:** any new night "back tomorrow night" flag goes in `sNightlyFlags`.
### 47. Review of 32 (PR #97, lane A, handed to lane B's builder) (reviewer, Nov 27) — **approved by Bryan; merged**
Merged `hoenn` at #100 into the branch (15 files conflicted, all "both sides added": IDs, the lane A call switch, maps/layouts lists, docs; the generated hint files re-run); `regen_all.sh --check` clean; size row re-measured (+4,784 B release over 35a). IDs don't clash with 27b/31a (flags E +0x27–0x2B, daily +1, call 40).
- **Code read:** `gen_hoenn_lights.py`'s two new path options (`water_only`, `avoid_objects`) leave 25a's path unchanged; Route 41 is at the 64-object limit with the light; the stranded Ampharos' battle and flags; Amphy falls back to HnS's script before the lighthouse is cured and by day.
- **Fixed in review:** two one-word last lines ("waves." on the shrine stone, "inside…" after the cave opens).
- **Played (debug save, 10 PM):** the light waits at (41,16); followed it all 13 stops to the ridge (no stop off screen, it keeps to the water); swimming off mid-follow scatters it back to the start; the cave opens with its line; the lagoon (Lanturn + Chinchou school), the shrine stone with and without Slowking's prophecy; out through the channel; by day the cave still leads in and the light is gone. Route 40: the Ampharos on its rock (talk from the water), Lv 60 with Tail Glow; knocked out → "resting" line; caught → gone; May's call. Amphy at the top at night before/after; the cafe and lighthouse sailors' lines before/after.
- **Bryan's change: rescue the Ampharos instead of catching it.** Done in review (merged #105 first):
  - No battle and no daily flag (so nothing for `sNightlyFlags`). Talking gives a YES/NO; YES sets `FLAG_HOENN_AMPHAROS_RIDING` and it rides behind you.
  - `HoennLaneAOnStep` (one hook line after the lights hook in `TryStartStepCountScript`) plays the landing on your first step on foot while it rides, on any map. Route 40 and Olivine City have an object for the hop-off (`HoennAmpharosAshorePlace` puts it on the tile you landed on and picks a direction with 3 tiles of open land to run off along). Anywhere else, the scene is text only. Afterwards it stands next to Amphy at the lighthouse top (`FLAG_HOENN_RESCUED_AMPHAROS`). Amphy, May's call and the sailor's hint now read "rescued".
  - **Moved one tile, (32,33) → (32,32), the same rock:** a reachability check found the old talk tile (32,34) only touched a channel walled off by the diagonal rock line, about 180 tiles of surfing from the nearest shore (Route 41's south). Now you talk to it from the open sea north of the rock (32,31), eight tiles from Route 40's beach.
  - **Played:** NO leaves it; YES → surf 8 tiles north → first step on the beach → it hops off behind you and runs west along the sand; the same on Olivine's pier (it runs up the pier); a ride poked onto Cianwood gives the text-only version; the lighthouse top shows both Ampharos and Amphy's new line; May's call.
- **Bryan's round 2 ("make the rock bigger, build up its trust with berries, landing anywhere gives a cut scene where it runs off to Jasmine"):**
  - **Bigger rock:** it sits on two of Route 40's brown sea boulders side by side (a `composed_maps.json` patch at (29–32, 32–33)); you talk to it from (31,31).
  - **Trust:** with no BERRY it shrinks back; with one, YES opens the berry bag and it eats one (any BERRY), once a night (`FLAG_HOENN_DAILY_AMPHAROS_BERRY`, in 41r's nightly list, so it resets at noon). The third berry: "It isn't shaking anymore", then the ride offer. `VAR_HOENN_AMPHAROS_STATE` (lane A var E +0) replaces the riding flag.
  - **The ride is your follower now** (`HoennLaneAFollowerOverride`), so the hop-off is drawn on every map, not just Route 40 and Olivine; the per-map objects are gone. It runs off along open land, then a cutscene at the lighthouse top: it climbs the stairs, Jasmine (shown for the scene even after she's gone back to the gym) and Amphy greet it, and you're put back on your landing tile.
  - **Bug found and fixed while testing:** script warps take s8 coordinates, and the lighthouse is 170 tiles wide, so warping to x 158 dropped you in the map's centre (85,10). Two specials fill the warp data themselves.
  - **Played:** no berry; berry 1 and the same night's "nibbling" line; next night (after noon) berry 2; berry 3 → trust → YES → follower; surf 9 north, land, one step: hop, run, cutscene, back on the beach; the same with Jasmine away (she's hidden again after); landing in Cianwood (same scene, it runs north); the lighthouse top later (both Ampharos, the rescued one's line); May's call (now mentions the berries).
  - **Choices for Bryan:** three berries over three nights, any berry counts, and the cutscene ends by putting you back where you landed.
- **Choices for Bryan:** the light swims on the surface (Route 41 has no Dive spots); a sea cave at the ridge's foot as the way in, open for good once found; the lagoon's look (render in `review-32-lagoon-map.png`) and the shrine "stone" being one of Route 41's ordinary boulders; the Ampharos on **Route 40** (Route 41 is full); the rescue's details (any shore counts, it lives at the lighthouse afterwards and isn't catchable); May's call via Jasmine's reports; the two sailors as hint NPCs.
- Grids: `review-32.png`, `review-32-rescue.png` (round 1) and `review-32-trust.png` (round 2) in the project's `hoenn-2.0/review/`.

### 48. Review of 28 (PR #101, lane A) (reviewer, Nov 27) — **approved by Bryan; merged**
Merged `hoenn` at #100 and #105 into the branch (CLAUDE.md size rows only); `regen_all.sh --check` clean; size row re-measured.
- **Code read:** the boulder (sign bg event, night check, `setmetatile` on the scene and on every ON_LOAD), the seal and the sanctum hide your follower (five Unown forms, review item 36's sprite-memory rule); the mural's `dynmultichoice` of 28 forms + CANCEL; `HoennSanctumLetter` → 27b's `HoennGlyphSetupBattle` (plain Unown gets an A personality); ran = pick again, otherwise the daily flag. The mural can be visited by day too, but the builder put its daily flag in 41r's nightly list while merging #105, so one battle per night (noon to noon); fine either way, since you mostly come at night. The radio hook writes at most 29 bytes into a 40-byte line buffer. Brendan's call sits after 31a's in `HoennLaneADueCall`.
- **Fixed in review:**
  - The five floating Unown were `LOOK_AROUND`, so they showed edge-on as thin sticks half the time. They're now `WALK_IN_PLACE_DOWN`, like 27b's rings.
  - The sanctum's top row was copied from B1F row 6, which is the bottom of the room above it, so a strip of floor showed over the frieze. It now uses B1F row 0, the plain top edge (`composed_maps.json`).
- **Played (debug save):** by day the boulder's worn-face line; at 10 PM the three Unown gather, the shake, the white fade, the cave mouth; down the ladder; the sanctum (Unown now facing you, clean top edge); the mural's line, the letter menu, B called → a Lv 60 Unown B; knocked out → "won't answer again until tomorrow"; the inscription (braille + translation); the lab researcher's new line, then her repeat line; Brendan's call. **Not played:** the Unown radio station (the debug save has no PokéGear radio): it's on the playtest list.
- **Choices for Bryan:** the boulder at (23,27) as the tablet's mark; the night opening with three Unown; the sanctum's look; one mural battle a day for any of the 28 forms; Lv 60–70 (Hoenn's scaling, like 27b's rings, not 29's Johto progress levels); the inscription's wording (Sinjoh, three sleepers, the oldest of the deep and the greatest of the sea); Brendan as the caller ("Relicanth and Wailord"); the radio's words.
- Grid: `review-28.png` in the project's `hoenn-2.0/review/`.

### 49. Review of 35b (PR #99, lane A) (reviewer, Nov 27) — **approved by Bryan (Ilex soil moved first); merged**
Merged `hoenn` at #97 into the branch (11 files conflicted, all "both sides added": IDs, the lane A call switch and due-call chain, specials, docs); 35b's specials moved inside lane A's block of `data/specials.inc`; `regen_all.sh --check` clean; size row re-measured (+5,104 B release over 32). IDs don't clash with 32 (35b: flags F +0x00–0x0D, daily +2–4, call 41; 32 took var E +0 and daily +1).
- **Code read:** `src/hoenn_johto_legends.c` and `hoenn_johto_legends.inc`, the roamer hook (`HoennJohtoBeastBattleEnded`), the radio hook (OAK's TALK intro; 28's hook is the Unown station, so they don't meet; at most 29 bytes into a 40-byte buffer), the Tin Tower roof gate (only HnS's post-story state 4; the story Ho-Oh on Ho-Oh's path is untouched), the sage (falls back to HnS's script outside state 4). The soil's daily flags aren't night events, so they stay out of 41r's nightly list. No logic bugs found.
- **Played (debug save):**
  - EUSINE before any catch, after catching Raikou (gives notes, then the repeat line) and with both caught ("no fresh trail").
  - The radio in Ecruteak at 2 PM: "MARY: A tip from EUSINE! / ENTEI's fresh trail / was tracked near ROUTE 29.", then the normal show. (In Kanto the station isn't there, and before the Radio Tower is cleared it's the Rocket broadcast: both HnS's.)
  - The sage: no bell or wing (points to Pewter); the RAINBOW WING gets the CLEAR BELL; then each clue in order (panel, the three beasts, dawn) and the ready line at 6 AM.
  - The roof: Ho-Oh at 6 AM with every clue; empty at 2 PM and 10 PM; HnS's Ho-Oh battle starts as before.
  - Ecruteak at the first ready dawn: the rainbow line, Ho-Oh flying across, its line; Brendan's call on the next walk (after Elm's older call).
  - Celebi: the soil's plain line before the GS BALL story; the shrine's empty dishes; plant (YES, the berry bag, "a little sprout"); the same day "still growing"; the next day take the glowing berry at all three (1, 2, "all three"); the shrine lays them and runs HnS's GS BALL scene; wild Celebi.
- **Found:** the Ilex soil (29,36) is one of the forest's saplings, and you can walk onto it (it's a walkable tile), where A then headbutts the next sapling. Viridian's and Petalburg's soil are at the foot of real lone trees and read fine. **Fixed (Bryan: move it, then merge):** the Ilex soil is now on the clearing floor left of the shrine (30,35) (`IlexForest_hns` map.json bg event; no layout change). Ilex's tilesets have no soil metatile (Johto_South's berry-tree block 0x2E draws a round bush), so it's plain floor; you plant facing it from below, the right or above (played: plant, next day take). Grid `review-35b-ilex-soil.png`. Also the planted sprout is text only (no tile change), and 6 AM is still HnS's night tint, so the "dawn" rainbow scene is dark.
- **Choices for Bryan:** dawn = HnS's morning (4–10 AM); "met" Raikou/Entei = met in battle (HnS marks all three seen when they start roaming), Suicune = the chase finished (8 encounters); the sage giving the CLEAR BELL for the RAINBOW WING; the rainbow told in text with Ho-Oh flying across (no rainbow art, no weather); the radio report in OAK's TALK (Johto only; not in the morning, when that slot is the Pokédex show); any berry, ready the next calendar day (planting at 11 PM is ready at midnight); the three soil spots and their texts; Brendan as the caller.
- Grid: `review-35b.png` in the project's `hoenn-2.0/review/`.

### 50. Review of 33 (PR #102, lane B) (reviewer, Nov 27) — **approved by Bryan; merged** (#102)
Merged `hoenn` at #99 (28, 35b; 32 was already in the branch) into the branch: the conflicts were all "both sides added" (28's sanctum map/layout/patch, the Alph lab hint line, docs); the generated hint files re-run; `regen_all.sh --check` clean; the living dex check passes (416 of 416). Size row re-measured: +48 B over 35b. `distribution.json`'s `waits_for` on Sneasel removed (31a is merged).
- **Read:** every wild slot that changed (src/data/wild_encounters.json against `hoenn`, 79 tables; `wild_rules.json` for Hoenn's), the overworld objects that follow them, `living_dex.py` and its report. Each replaced slot keeps its level and rate. The check reads the compiled tables (only the slots the engine rolls), scripts, trades and roamers, and fails if a one-of-a-kind species has any other source, so it doubles as the test that Absol, Tropius, Feebas, Sneasel/Weavile and the Ralts line come only from their events.
- **Played (debug save, 2 PM):** Fortree's roof Swellow, Route 120's cliff Nuzleaf, Route 6's Psyduck and Mankey on the truck, Route 15's Oddish. Rare slots weren't sampled in battle (a 1-in-20 slot needs hundreds of encounters); the check covers them.
- **Choices for Bryan:** every replacement species (the list in the PR and section 10 of the plan), what stays Hoenn in Kanto (the Fuchsia Safari's Hoenn areas, Wingull on Route 19, Lunatone/Solrock in Mt. Moon, Torkoal on Cinnabar, Route 18's Kecleon), Roselia added to Route 117 by day, Mt. Silver's Weavile → Mamoswine, Ula'ula Cave's Sneasel → Snorunt.
- Grid: `review-33.png` in the project's `hoenn-2.0/review/`.

### 51. Review of 34b (PR #106, lane A) (reviewer, Nov 27) — **merged before review (by lane A, at Aidan's request, 22:28 UTC); choices confirmed by Bryan after the fact (Nov 28)**
Tested on the branch synced onto `hoenn` at #107 (no conflicts); `regen_all.sh --check` clean; living dex 416 of 416. Size row re-measured: +3,088 B release, +3,120 B debug over 33.
- **Read:** the shrine script, the one-line chamber gate in HnS's `WhirlIslands_LugiaChamber` OnTransition, the cameo (borrowed Lanturn-light template), Brendan's call and the Olivine Pokémon Center fisher's lines. Checked HnS's own Lugia flow: `VAR_COMPLETED_LUGIA` 2 = story dance, 3 = story battle done (won or ran), 4 = the post-story Lv 70 Lugia, set by the Hall of Fame and by the Pewter grandpa (Ho-Oh path, with the SILVER WING). So the gate means HnS's post-Hall-of-Fame Lugia now also waits for the shrine.
- **Played (debug save):** stone with nothing, with two of four (names the thunder and flame hollows), with all four (Slowking line, YES, ceremony, flags set, var 3 → 4, Tentacruel hidden), the after-text; the chamber at var 4 empty before the shrine and with Lugia at (29,12) after; the Route 41 cameo at 10 PM from the lagoon mouth (rises, sings, dives, plays once; nothing by day or a second night); Brendan's call; the fisher's cameo line and the rumor before/after.
- **Choices (confirmed by Bryan):** all four treasures needed; feathers kept; HnS's own Lv 70 Lugia reused, and gated behind the shrine (also after the Hall of Fame); the cameo's spot and once-only.
- Not played: the Lugia battle itself (HnS's, on the playtest list).
- Grid: `review-34b.png` in the project's `hoenn-2.0/review/`.

### 52. Review of 37 (PR #104, lane A) (reviewer, Nov 28) — **merged before review (by lane A, at Aidan's request); reviewed after the merge on Bryan's call; choices confirmed by Bryan (Nov 28)**
Tested on `hoenn` at `cdacfafc` (#104's merge): debug build 32,946,132 B (594 KB free), the same as lane A's size row.
- **Read:** the Part 37 section of `hoenn_lane_a.inc`, `HoennWishCount` and `HoennDeoxysSignalNight`, the map.json swaps (white rock, Jirachi, the 2F scientist, the Olivine fan, the Sinjoh linguist), the Sinjoh Ruins OnTransition hook, the one-line Arceus gate, the three event calls and the new hint lines and rumors.
- **Played (debug save):**
  - **Wishes.** All three wishes work at night: the Meteor Falls clifftop boulder, the Space Center 2F windows and the moon hollow's pool. The third one gives the chime. Each spot has its own text by day and says you've already wished on a repeat.
  - **White rock and Jirachi.** With 2 wishes the rock is "listening". With 3 on a Sunday night it's "waiting". On Monday night the Clefairy are out and Jirachi lands in the pond. You battle it from the water at (13,10). Knocking it out hides it and clears the summon flag, so a later Monday night can wake it again.
  - **Deoxys signal.** Night 1 gives the first line. Asking again later the same night, including at 2 AM, gives "already logged". By day he says to come back at night. Night 2 gives the second line, night 3 gives the AURORA TICKET and how to use it, then the after-line. The Olivine fan (champion, no ticket) now points to the Space Center.
  - **Regi boulders.** At 9 plates the boulders stand in the doorways. Without the inscription the braille can't be read. With it, the first read plays the stir cameo, then "doesn't budge" without RELICANTH and WAILORD. With both, it rolls aside, `FLAG_HOENN_REGI_OPEN_ROCK` is set, it stays gone on re-entry, and the west arrow warp leads into the Regirock room.
  - **Arceus.** At storyline 12 without the inscription, Arceus "waits". With it, HnS's catchable battle starts.
  - **Calls.** May's wishes call and May's Regi call both ring.
- **No bugs found.**
- **Choices (confirmed by Bryan):**
  - Jirachi needs three night wishes, then Monday night at the white rock. HnS's rock worked on any night.
  - A knocked-out Jirachi can come back on a later Monday. HnS's didn't return until the next Hall of Fame.
  - The AURORA TICKET comes from three nights of the Space Center signal. HnS's Olivine fan used to give it to any champion.
  - HnS's Regi doors also need the Ruins inscription plus RELICANTH and WAILORD in the party.
  - Arceus's catchable battle waits for the inscription.
- Not played: Deoxys on Birth Island, the Regi battles and the Arceus battle (all HnS's own), and the Deoxys call.
- Grid: `review-37.png` in the project's `hoenn-2.0/review/`. Debug patch: `hoenn-2.0/patches/37-wishes-and-giants-debug.ups`.

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
