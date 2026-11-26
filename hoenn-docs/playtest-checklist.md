# Hoenn & Seek: playtest checklist

Things each part couldn't check in the emulator, so Bryan's real playthrough covers them on a real save, not the debug one. Tick them off while playing; **add to this list at the end of every part.**

**Claude's 1.0 pre-pass (Nov 25)** played the whole route on a debug save with a hacked team (battles auto-won) and swept 471 town NPCs. Items it covered are ticked with "(pre-pass)"; difficulty still needs Bryan's real battles. Its bug list (all fixed in 1.0 part 20a) is in the first claude.ai Project's `claude/hns-hoenn-playtest-log.md`.

**Why some things couldn't be tested:** the debug save (`mkbase.sh`) has no PokéGear phone until `FLAG_ADDED_MATCH_CALL_TO_POKENAV` is set, battles were auto-won, and random phone calls need real time to pass.

## Part 13b — Gyms and League
- [x] A full Elite Four → Wallace run (pre-pass: Phoebe, Glacia, Drake, Wallace, League badge, Hall of Fame, back to the lobby; battles auto-won). Sidney not reached by warp — enter from the lobby.
- [ ] The E4 and Wallace with **real** battles: are Lv 76–84 fair?
- [ ] Leader rematches after Wallace: the prompt, the Lv 85 teams, and that the leader stays rematchable.
- [ ] No real Hall of Fame screen yet (only the machine animation) — decide whether that's fine.

## Part 16a — Teams and rivals
- [x] Maxie, Archie and the Maxie + Archie double played to the end, with after-scenes (pre-pass).
- [ ] Matt, Shelly and Tabitha battles (their rematches) played to the end.
- [x] The Fiery Path Torkoal: won, gone, Tabitha's report line (pre-pass).
- [ ] Losing to the Torkoal: it stays and says it's still agitated.
- [x] Brendan & May double played to the end; with a full party they offer the eggs again at home (pre-pass).
- [ ] Eggs given right after a win with two free slots.
- [ ] Mt. Silver gate opens after beating Brendan & May (the guard wasn't reachable by warp in the pre-pass).
- [ ] Oak's Mt. Silver line after Brendan & May.

## Part 16b — Arrival gifts
- [x] Oak's ticket text, and the harbor aide's greeting on a real ferry arrival (pre-pass).
- [ ] Mudkip with a party slot free (tested only with a full party, so it went to the PC).

## Part 16c — Phone rematches (route trainers)
- [ ] The other 35 phone trainers: registration after the first win, a call, a rematch. Only Calvin (Route 102) was played.
- [ ] Double rematches (Lila & Roy, John & Jay, Anna & Meg, Amy & Liv, Kira & Dan): `trainerbattle_rematch_double` with two Pokémon out.
- [ ] Rematch levels feel right early in Hoenn (Lv ~68 at 0 badges is about the next leader's strength).
- [ ] Timed random calls (not just the 255-step route counter) from a trainer on another route.

## Part 16d — Calls from friends
- [x] **The PokéGear contact list:** BIRCH'S SON BRENDAN, NORMAN'S GIRL MAY, GARDEVOIR FAN WALLY; calling Brendan and May after Red gives the right lines (pre-pass).
- [x] Event calls: May at 1 and 8 badges, Brendan at 4 and after the Maxie + Archie double, May's "we're back" in the Hall of Fame flow, Elm, May after Red (pre-pass).
- [ ] Getting several badges quickly: only the highest milestone call rings.
- [x] Wally's Victory Road win → registers (pre-pass).
- [ ] **Wally's call rate**: in the pre-pass his chat calls interrupted ~6 of 471 NPC visits; part 20a cut it to a third. Still annoying, or fine now?
- [ ] Elm's lab on a real save: the ball you picked stays hidden, the stolen one (Silver's) reappears, and you can take the two you didn't pick. (The debug save never picked a starter.)
- [ ] Oak's lines: "BIRCH and I talk every week" and, after Red, "I phoned BIRCH and NORMAN".
- [ ] Maxie's rematch line mentioning Birch.
- [x] Birch's line after beating Brendan & May ("I called PROF. OAK right away") (pre-pass sweep).

## Part 17 — Contests and Safari
- [ ] **A real contest win** (any rank) → May's call. The call was tested with a win count set in memory.
- [x] Contest flow entered from Lilycove returns to Lilycove's lobby, then Lilycove.
- [ ] Contest painting in the Lilycove Museum after a Master Rank win (from either lobby).
- [ ] Link contests from the Lilycove lobby return there (can't be tested without a link).
- [ ] Twin NPCs not heard in the emulator because they wander off the test tile: the Lilycove lobby's fisherman, sailor and gentleman, and all four in Lilycove's walk-in hall.
- [ ] The Lilycove receptionist's twin intro shows once, then the normal contest flow every time after.
- [ ] Hoenn Safari exits other than "retire": time running out (steps) and running out of Safari Balls, including mid-battle.
- [ ] Hoenn Safari's north and east areas (Mach/Acro Bike sections and the postgame extension).
- [ ] Pokéblock feeders in the Hoenn Safari, and throwing a Pokéblock in a Safari battle.
- [ ] HnS's Johto and Kanto Safari Zones still exit to their own gates after a Hoenn Safari trip.
- [ ] May's 4th-badge line (contest hall), Brendan's 8th-badge line (Safari) and May's mom's contest line.

## Part 18 — Secret bases
- [ ] A **tree** base (vines) and a **shrub** base, not just a cave; Secret Power used from the party menu as well as by facing the spot.
- [ ] Every furniture category placed in a base: chairs, plants, ornaments, mats (with a doll on a mat/desk), posters on the wall. Only a desk was placed.
- [ ] PUT AWAY and TOSS in the base PC; PACK UP and moving the base to another spot.
- [ ] A new HnS save's dolls still show under DOLL.
- [ ] Mauville Game Corner and Lilycove rooftop decoration prizes go into the right categories.
- [ ] Your room in New Bark: cushions (now allowed alongside dolls) look right on the bed/floor.
- [ ] The Slateport TM salesman who appears after the Secret Power man leaves.
- [ ] Brendan's base call on a real save with the PokéGear.

## Part 19 — Red and cleanup
- [x] Red's first fight played to the end → HnS credits → May's after-Red call (pre-pass; levels 86–95 confirmed).
- [ ] Red's first fight with **real** battles: is it the right step up from Brendan & May?
- [ ] **Red's finale played to the end** (all Lv 100, illegal moves) on a real save after HnS's post-challenge unlock.
- [ ] Berry trees: pick Route 102's Oran tree and Route 30's on the same day — both should have berries. Same for Route 118's two Sitrus trees vs Route 1, Route 26 and Fuchsia.
- [ ] Why the debug save's trees all say "not ripe yet" at the berries stage (HnS behavior or the debug clock?).
- [x] Route 118 Good Rod → 5 Lure Balls when you already own one.
- [ ] Dewford Old Rod → Net Balls, Mossdeep Super Rod → Dive Balls, Mauville Coin Case → 300 coins.

## Part 20a — Fixes, battle backgrounds, overworld Pokémon
- [x] Norman in his room, not at the door; Littleroot signs; Steven's letter; Scott, the Fortree boy, the Devon engineer, Cutter, Petalburg House 2, Oak's Indigo line; Birch's numbers before "Enjoy HOENN!"; Mr. Stone's one speech (emulator).
- [x] Wild battle backgrounds: Fiery Path, Granite Cave, Jagged Pass, Meteor Falls, Mt. Pyre outside, Routes 111, 113, 119, 120, Safari North, Shoal ice room, Victory Road (emulator).
- [x] Trainer backgrounds: Lavaridge Gym (volcano), Mauville Gym (blue building), Roxanne (leader stadium) (emulator).
- [ ] **Hoenn E4 rooms** with the new tinted stadiums (Sidney dark, Phoebe indigo, Glacia ice, Drake red): only rendered from the art, not seen in a battle. Also with "new backgrounds" turned off in the options (Emerald's own E4 art).
- [ ] Battle backgrounds you might not like: Route 113's ash uses the snowy slope, the Route 111 desert the rocky mountain, Mt. Pyre's graves a plain building. Say if any should change (new art would be needed for a real desert, ash or graveyard).
- [ ] Battles while surfing on Hoenn routes and in Shoal Cave/Meteor Falls water (water and cave-water backgrounds).
- [x] Overworld Pokémon by day and by night in towns and on routes (day/night swaps on Littleroot, Oldale, Mossdeep, Routes 101, 117, 119) (emulator).
- [x] After Bryan's review they moved into scenery out of reach (roofs, cliff tops, rocks, water behind rocks) and animate in place (emulator, 29 maps).
- [ ] Any overworld Pokémon that looks odd where it stands (on a wall face, half hidden by a tree, floating on a ledge). Note the map; the generator's rules can exclude the tile.
- [ ] **Overworld Pokémon with a real party follower and busy screens** (Slateport market, Lilycove, Route 110, Route 119): do any NPCs or trainers fail to appear, or do sprites show the wrong colors? The generator keeps ≤ 9 objects per screen (11 in towns), but only real play shows it.
- [ ] Too many or too few? 361 across 80 maps (small maps like Route 101 have none: no out-of-reach spot); routes show evolved forms because the wild tables do.
- [ ] **Mirage Tower** (found in 2.0 part 1): it already appears on about half your Route 111 visits and Emerald's fossil climb works. Fine for 1.0, or hide it until 2.0's Flygon chain?

## 2.0 part 1 — Event flags and vars
- [ ] **Load your real 1.0 mGBA save into the 2.0 part 1 debug patch:** it should Continue normally with your progress intact (flags, Hoenn badges, phone contacts). The emulator test faked a 1.0 save; this is the real one.
- [ ] Nothing to see in play yet: 2.0 flags only start being used in part 2.

## 2.0 part 2 — Script helpers and debug tools
Nothing a player sees yet (part 3 adds the first weekday content); these are for the debug patch.
- [ ] **The weekday on your real save:** debug menu → Utilities → "H&S time & weather…". Until part 3 the game's weekday is arbitrary: day 0 is a Saturday, and a real save's day 0 is the day you set New Bark's wall clock (a debug save that never set it runs one day ahead of the real date). Use SET WEEKDAY to match your real day; does the status line then match your real day and time, and does it stay right after a save and reload?
- [ ] On your real 1.0/2.0 save (clock set by New Bark's wall clock), NEXT WEEK clears weekly flags and SET WEEKDAY never does. Emulator-tested on a debug save only.
- [ ] Route 119 and 123 in real play: walk into the rain zones on a "special" day (thunderstorm on 119, rain on 123) and a normal one.
- [ ] Leave the game on over a real Saturday → Sunday midnight: no freeze or stutter when the week rolls over.

## 2.0 part 3 — Weekday content
- [ ] **A real new game:** after setting the stopped clock in your room, the calendar asks what day it is; pick the real day. (Emulator-tested on a real new game; check it reads well on a phone.)
- [ ] **Your 1.0 playtest save:** it starts 2.0 with an arbitrary weekday. Use any wall clock to set the real day; the start menu should then show it.
- [ ] A Pokémon Center's wall clock: "Change the day?" comes before the clock view. Is the extra question every time fine, or should it default to NO (or only show the day)? Then press R in the clock view to change the time: the day you set stays.
- [ ] Your room's wall clock: say YES to "Change the day?", pick a day; the start menu ("FRI 9:34 PM") and the PokéGear radio follow. (Emulator-tested: YES, NO, EXIT and B.)
- [ ] The start-menu clock with the weekday: does the wider box look right next to the menu, including in the Safari Zone?
- [ ] The seven Weekday siblings: on the wrong day they name their day; on their day they give the gift (once).
- [ ] Union Cave B2F's Lapras: there on a Friday; catch or beat it, and it's back the next Friday, not before.
- [ ] Mt. Moon's Clefairy dance: only on Monday nights (enter the area after dark).
- [ ] The sibling texts: do you like the HGSS-style "only on my day" better than HnS's guessing riddle?

## 2.0 part 4a — Level caps
Only with the challenge setting LEVEL CAP on (Normal or Hard).
- [ ] **Your 1.0 playtest save, if it's past the Johto League:** the cap after Johto champion is now 60 + Kanto badges (it was 70), and Kanto champion caps at 70 until Hoenn (it was none). Pokémon already above the cap keep their levels but stop gaining EXP. Does that feel right on a real run?
- [ ] Win a Kanto gym and a Hoenn gym: a Rare Candy (or EXP) goes up to the new cap and no further. (Emulator: Lv 70 → 71 at cap 71, then "It won't have any effect.")
- [ ] Hard: two levels lower at every Kanto/Hoenn step (tested on a test-only ROM).
- [ ] Beat Wallace: the cap is gone.

## 2.0 part 4b — Trainer followers
Each gym leader, Elite Four member and Red has their ace standing next to them (30 objects on 30 maps; list in `data/hoenn/trainer_followers.json`).
- [ ] Do the picks feel right? Each is the highest-level Pokémon of the leader's first team (ties: their signature one). Easy to swap in the JSON.
- [ ] No Chuck, Blaine, Tate & Liza (no free tile next to them), Janine (it would give away her disguise trick), Lance or Wallace (walk-in scenes). Is that OK, or should some get a follower a tile further away?
- [ ] Mahogany's ice and Sootopolis's ice: the followers sit away from the ice; do all slides still work?
- [ ] Your own follower next to theirs in each gym: no wrong colors. (Emulator: all 30, with and without a follower out; palettes checked in memory.)
- [ ] Red: Pikachu stands beside him and disappears with him after the battle (emulator-tested).

## 2.0 part 5 — Daily weather cycles
78 routes now have a special-weather day one day in four (list and groups in `data/hoenn/weather_cycles.json`). Debug menu → "H&S time & weather…" → WEATHER +1 steps through the days.
- [ ] Do the picks feel right? Which routes rain, storm, fog or snow, and which groups share a day. Easy to change in the JSON.
- [ ] Walk from a rainy route into a town and back: the weather changes at the border without stutter.
- [ ] Route 120 on its storm day: the storm covers the whole route, including where Emerald had sunny patches (emulator-tested).
- [ ] Routes 119 and 123 work as in Emerald on every day.
- [ ] Battles on a rain or storm day start in rain (as in Emerald). OK for trainer battles, or should trainers be exempt?
- [ ] Fog on Routes 19–20, 44–45 and 122, and snow around Mt. Silver: readable, no slowdown.
- [ ] The debug menu's WEATHER +1 on a Johto route: the weather changes on the spot.

## 2.0 part 6a — Hoenn weather encounter tables
On a Hoenn cycle route's special day, wild Pokémon come from a weather table (list: `hoenn-docs/weather-tables.md`).
- [ ] Do the shifts feel right? Rain: Lombre and Masquerain show up, Water/Bug a bit more common. Storm (120, 124–128, 119): Manectric, Plusle, Minun, Lanturn while surfing.
- [ ] Castform: only on special days (1–2 %). It changes form in its weather (Forecast).
- [ ] Surfing and fishing on a special day: surf follows the weather table, fishing is unchanged.
- [ ] Pokédex area pages: weather-only species (Castform, Masquerain…) are marked on their routes.
- [ ] The Safari Brush has Chimecho where Castform used to be (wild slot and the overworld Pokémon).
- [ ] Sweet Scent and Repel work as usual on a special day.

## 2.0 part 6b — Johto and Kanto weather encounter tables
- [ ] Rain in Johto/Kanto: Poliwag, Wooper and Marill (or their evolutions at Kanto levels) in grass, Psyduck/Golduck while surfing.
- [ ] Storm on Routes 10, 42 and 43: Mareep line, Pikachu, Magnemite, Voltorb; Chinchou/Lanturn while surfing.
- [ ] Fog on Routes 44–45 and 19–20: Gastly line, Misdreavus, Murkrow; Slowpoke/Slowbro and Staryu on water.
- [ ] Snow around Mt. Silver: Delibird, Mamoswine, Jynx; Seel/Dewgong on water.
- [ ] Surfing on routes whose water has no Pokémon (Routes 3, 5, 7, 8, 11, 16, 18, Mt. Silver's mountainside) stays empty on special days.

## 2.0 part 7 — Hint lines, rumors, forecasts
Hint NPCs (one per Pokémon Center in most towns, list in `data/hoenn/npc_hints.json`) alternate their own line with an extra one.
- [ ] Do the extra lines read well, and does alternating feel natural (it's one switch for all hint NPCs, so the first hint NPC you meet may give the tip first)?
- [ ] Story lines go away once done: Norman (4 badges), Wattson (New Mauville), the meteorite, Winona, the ferry ticket.
- [ ] Rumors switch to their "after" line once you catch Castform, Feebas, Masquerain or Union Cave's Lapras; Birch's aide counts them.
- [ ] TVs in Hoenn: a forecast first when a Castform/Masquerain day is today or tomorrow, then the normal show. Johto/Kanto TVs unchanged.
- [ ] The Weather Institute 1F worker gives the forecast; after both are caught, his own lines.
- [ ] Level-cap tip only shows with the LEVEL CAP challenge on.

## 2.0 part 8a — Building generator
- [ ] Route 34's fisherman's shack (the small house on the shore, 23,50): walk in and out, talk to both NPCs (the wife alternates with a hint), the Psyduck cries and wanders without blocking the door.
- [ ] Review `hoenn-docs/buildings.md`: the 16 buildings and their planned purposes.

## 2.0 part 8b — Olivine buildings
- [ ] Walk into all 6 (west row 2,15 / 6,15 / 10,15; east row 27,15 / 31,15 / 35,15) and out again. Read the texts in place: none of them has had Bryan's review.
- [ ] Retired captain: rates the lead Pokémon (tested only with the debug Lapras, the lowest rating). Try a happy Pokémon. On the second talk he gives the Lapras rumor.
- [ ] Tackle shop: buy each ball and Repel. Are the prices and the list OK?
- [ ] Lighthouse keeper's wife: one find a day (Pearl; Stardust on Tue/Thu; Big Pearl at weekends). Check that it resets the next day with a real clock, and what she says with a full bag.
- [ ] The wall clock in the captain's house (with a set clock; debug saves show "The clock is stopped").

## 2.0 part 9 — Johto buildings
- [ ] Walk into Ecruteak's house by the east trees (57,25), the house next to Route 34's Day Care (33,31), Route 38's ranch building (34,41) and Bellchime Trail's lodge (54,58), and out again. Read the texts in place (no review yet).
- [ ] The breeder alternates her line with the new Day-Care tip. Does the tip fit, given the Day Care is next door?
- [ ] The lodge sages' Ho-Oh/Lugia lore doesn't contradict HnS's own legendary story.

## 2.0 part 10 — Kanto buildings
- [ ] Walk into both Route 6 houses (21,17 and 49,30) and Celadon's house by the pond (26,17), and out again. Read the texts in place (no review yet).
- [ ] Celadon florist: one berry a day, a different one each weekday (Lum on Sunday, Sitrus on Saturday). With a real clock, check that the next day gives another berry, and check what she says with a full Berry Pocket. Do the same for the Olivine keeper's gift.

## 2.0 part 11 — Melemele buildings
- [ ] Walk into Melemele's two houses (11,21 and 20,25) and out again. Read the texts in place (no review yet).
- [ ] Surf shop: talk to the clerk across the counter (in the harness it only answered from the side, as HnS's own Melemele mart does). Buy each item, and check the prices and list are OK.
- [ ] The Wailmer pet's big sprite overlaps the shelf behind it. Is that OK, or should it move or change?

## 2.0 part 12 — Legendary sites reopened
- [ ] Sealed Chamber: dive on Route 134, stand on the hole and press Down, then do Emerald's braille puzzle with Relicanth and Wailord in the party; the Regi doors on Routes 105, 111 and 120 open (only the Route 111 door and the Regirock chamber were checked in the emulator, with the flag set by hand).
- [ ] Island Cave (Regice) and Ancient Tomb (Registeel: Flash in the middle; in HnS's HM mode Flash needs HM05 in the bag) open their inner chambers when you follow their braille.
- [ ] Sky Pillar: climb to the top with the Mach Bike over the cracked floors; no Wallace at the door, no Rayquaza at the top.
- [ ] Cave of Origin and Seafloor Cavern: walk to the end (Seafloor's boulder and current puzzles), no Wallace, Kyogre, Maxie, Archie or grunts.
- [ ] Each of the five base spots (end of Desert Ruins, Island Cave, Ancient Tomb, Cave of Origin B1F, Seafloor Cavern Room 9): Secret Power makes a base, decorate it, leave and come back (the entrance stays open), then move it to another spot.
- [ ] May's call about the sites rings once (needs the PokéGear and her number), and Brendan's first-base call doesn't ring after it.
- [ ] Items and trainers left in the sites (Seafloor Cavern has no grunts now; the items should all still be there).

## 2.0 part 12b — Chamber-bases
- [ ] Sky Pillar: climb to the summit (cracked floors need the Mach Bike), use Secret Power on the back wall above the summit's middle, and decorate the base; do the colours look right on real hardware/mGBA?
- [ ] Sealed Chamber: after the braille puzzle, use Secret Power on the inner room's top wall; decorate the base.
- [ ] Move your base between a chamber and a normal spot and back (the old base packs up, decorations return to the PC).
- [ ] Secret base registry/visiting through mixing records isn't testable solo; check nothing odd shows in the base list if you have another save.

## 2.0 part 13a — Johto/Kanto secret bases
- [ ] Ilex Forest (the lone tree just east of the northern pond), Route 45 (the rock face above the pond at the bottom), Viridian Forest (the lone tree near the south exit) and Mt. Moon (the lower wall south of the middle room): each entrance is easy enough to spot, Secret Power opens it, and the base works.
- [ ] Put one of the new dolls (Goldenrod 5F or Celadon 4F) on a desk or mat in a base, leave and come back: the doll is still there and looks right. Not confirmed in the emulator.
- [ ] Brendan's call after you make a base in Johto or Kanto (needs his number from Birch).
- [ ] The tip at the Azalea, Blackthorn and Pewter Pokémon Centers goes away after Brendan's call.

## 2.0 part 13b — Battle backgrounds
- [ ] Route 111: a wild battle (and a trainer) in the desert shows the dunes; one on the grassy north or south end still shows the mountain trail.
- [ ] Route 113: battles show the grey ash fields; Mt. Pyre's outside and summit show the misty graveyard. Check one at night and one in the evening.
- [ ] Surfing on Route 111's ponds and battles against gym leaders elsewhere still use their own backgrounds.
- [ ] Switch the options to classic backgrounds: the three maps fall back to HnS's mountain/sand art with no glitches.

## 2.0 part 14 — Tidal Strait
- [ ] Before Oak's ticket: Route 41's new gap in the southern rocks leads to the great whirlpool, which blocks the way and talks.
- [ ] Get the ticket from Oak: his new strait line, then the TV bulletin on the next TV you watch (once).
- [ ] Surf Route 41 → the strait → Hoenn's Route 105 and back; the fade in the middle feels OK, the ROUTE 41/105 popups and weather change at the right places.
- [ ] Wild battles and fishing in both halves (levels feel right for a post-16-badge player).
- [ ] May's call after you reach the Hoenn half (needs her number from Birch).
- [ ] The Cianwood youngster and Olivine sailor (outside) change their lines: closed, open, crossed; Dewford's woman mentions it.

## 2.0 part 15a — Johto starters A (Chikorita, Cyndaquil)
- [ ] Routes 26/27: no Chikorita, Cyndaquil, Totodile, Bulbasaur, Charmander or Squirtle in the grass or walking around; Elm's table stays empty after beating Brendan & May.
- [ ] Elm's call after Brendan & May names the right place for your starter (Route 46 / Burned Tower / Lake of Rage).
- [ ] Route 46: the sweet-aroma line in the big tall-grass patch (daytime, after Brendan & May); Cut the tree east of it, walk to the cave mouth and into the meadow. Check the new tree and cliff tiles look right.
- [ ] Meadow by day, each starter: Meganium family (Chikorita) / the tagged runaway that joins you (Cyndaquil) / the wild one (Totodile). At night or in the evening, nobody's there.
- [ ] Burned Tower B1F at night, each starter: wild Cyndaquil (Chikorita) / the family leaving (Cyndaquil) / the runaway (Totodile). By day, nobody's there.
- [ ] Wild ones: catch one (gone for good); knock one out (back next visit); run (still there).
- [ ] Runaways: Lv 5 with Aromatherapy / Extrasensory; with a full party it goes to the PC; with party and boxes full it stays.
- [ ] Brendan's call after a runaway joins you (needs his number from Birch).
- [ ] Save and reload in the meadow and the tower after each scene: no replay.

## 2.0 part 15b — Johto starters B (Totodile, hints)
- [ ] Lake of Rage by day, after Brendan & May, each starter: the Feraligatr family that stays (Totodile) / the runaway on the shore that joins you (Chikorita) / the wild one on the shore (Cyndaquil). At night, nobody's there. Try both tides and the thunderstorm.
- [ ] Surf up to the cove from the lake instead of walking: the scene still plays.
- [ ] The runaway Totodile in a real party slot: Lv 5 with Dragon Dance.
- [ ] Silver at Indigo Plateau after his daily rematch, Mom and Elm's aide: their extra line names the right place for your starter, and stops once you've found it.
- [ ] Save and reload at the lake after the scene: no replay.

## General
- [ ] The release build plays the same as the debug build (all testing so far used debug builds).
- [ ] Every phone line and in-person line about Brendan & May still makes sense in the order a real player hits them.
- [ ] Day/night tinting on Hoenn windows and lamps.
- [ ] Walking (not warping) Slateport → Route 110 → Route 103 → Oldale → Littleroot as the aide describes.
