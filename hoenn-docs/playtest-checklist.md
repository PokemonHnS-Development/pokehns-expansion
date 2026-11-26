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
- [ ] **A real new game:** after setting the stopped clock in your room, the calendar asks what day it is; pick the real day.
- [ ] Your room's wall clock: say YES to "Change the day?", pick a day; the start menu ("FRI 9:34 PM") and the PokéGear follow. (Emulator-tested with a debug save.)
- [ ] The start-menu clock with the weekday: does the wider box look right next to the menu, including in the Safari Zone?
- [ ] The seven Weekday siblings: on the wrong day they name their day; on their day they give the gift (once).
- [ ] Union Cave B2F's Lapras: there on a Friday; catch or beat it, and it's back the next Friday, not before.
- [ ] Mt. Moon's Clefairy dance: only on Monday nights (enter the area after dark).
- [ ] The sibling texts: do you like the HGSS-style "only on my day" better than HnS's guessing riddle?

## General
- [ ] The release build plays the same as the debug build (all testing so far used debug builds).
- [ ] Every phone line and in-person line about Brendan & May still makes sense in the order a real player hits them.
- [ ] Day/night tinting on Hoenn windows and lamps.
- [ ] Walking (not warping) Slateport → Route 110 → Route 103 → Oldale → Littleroot as the aide describes.
