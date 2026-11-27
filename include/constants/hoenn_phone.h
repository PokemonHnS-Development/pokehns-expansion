#ifndef GUARD_CONSTANTS_HOENN_PHONE_H
#define GUARD_CONSTANTS_HOENN_PHONE_H

// Hoenn & Seek (part 16d): event calls (src/hoenn_phone.c, data/scripts/hoenn_phone.inc).
#define HOENN_CALL_NONE    0
#define HOENN_CALL_BADGE1  1 // May: first Hoenn badge (Norman heard from the League)
#define HOENN_CALL_BADGE4  2 // Brendan: four badges; hints at Magma's station
#define HOENN_CALL_BADGE8  3 // May: eight badges; they're nearly done in Kanto
#define HOENN_CALL_ELM     4 // Elm: after Brendan & May, one of Birch's Johto starters got loose (2.0 part 15a)
#define HOENN_CALL_TEAMS   5 // Brendan: after the Maxie + Archie double
#define HOENN_CALL_RED     6 // May: after you beat Red
#define HOENN_CALL_CONTEST 7 // May: after your first contest win (part 17)
#define HOENN_CALL_BASE    8 // Brendan: after you make a secret base (part 18)
#define HOENN_CALL_SITES   9 // May: your base is at a reopened legendary site (2.0 part 12)
#define HOENN_CALL_JK_BASE 10 // Brendan: your base is in Johto or Kanto (2.0 part 13a)
#define HOENN_CALL_STRAIT  11 // May: you surfed the Tidal Strait into Hoenn (2.0 part 14)
#define HOENN_CALL_STARTER_FOUND 12 // Brendan: Birch's runaway Johto starter is with you (2.0 part 15a)
#define HOENN_CALL_KANTO_STARTER 13 // May: a Kanto starter from the 2.0 events chose you (2.0 part 16)
#define HOENN_CALL_POND   14 // Brendan: you saw the Swampert family dive on Route 102 (2.0 part 18)
#define HOENN_CALL_RALTS  15 // Wally: the Ralts on Route 102 chose you (2.0 part 18)
#define HOENN_CALL_KIYO   16 // Brendan: you watched Kiyo spar with a Machamp (2.0 part 18)
#define HOENN_CALL_SCIZOR 17 // May: you saw the Scizor at the National Park (2.0 part 18)
#define HOENN_CALL_GENGAR 18 // Brendan: a Gengar jumped out of your shadow in Lavender (2.0 part 19)
#define HOENN_CALL_PROPHECY 19 // May: the Slowking sage taught you its whole prophecy (2.0 part 19)
#define HOENN_CALL_MUNCHLAX 20 // Brendan: the Route 113 Munchlax woke up for you (2.0 part 20)
#define HOENN_CALL_SLAKING  21 // May: you caught the Slaking in Petalburg Woods (2.0 part 20)
#define HOENN_CALL_TROPIUS  22 // Brendan: you met the orchard Tropius on Route 119 (2.0 part 21)
#define HOENN_CALL_FEEBAS   23 // May: you fished the mirror pool Feebas (2.0 part 21)
#define HOENN_CALL_FEUD   24 // Brendan: you broke up Route 114's Zangoose vs. Seviper fight (2.0 part 21)
#define HOENN_CALL_ABSOL  25 // May: you saw Absol on Route 120's ridge (2.0 part 22a)
#define HOENN_CALL_WAILORD 26 // Brendan: you woke the Wailord in Route 131's strait (2.0 part 22b)
#define HOENN_CALL_CHIMECHO 27 // May: you found the Mt. Pyre chimes (2.0 part 22b)
#define HOENN_CALL_CHORUS 28 // May: you watched the Altaria chorus above Meteor Falls (2.0 part 23)
#define HOENN_CALL_BAGON 29 // Brendan: you met Bagon on its Meteor Falls ledge (2.0 part 23)
#define HOENN_CALL_METAGROSS 30 // Brendan: you saw two Metang fuse in Steven's cave (2.0 part 23)
#define HOENN_CALL_SINGING_SAND 31
#define HOENN_CALL_FLYGON 32 // May: you caught the Mirage Tower Flygon (2.0 part 24b)
#define HOENN_CALL_TRENCH 33 // Brendan: you followed the Chinchou lights into the Route 124 trench (2.0 part 25a)
#define HOENN_CALL_TRENCH_DOOR 34 // May: the trench's three guardians are caught and its door is open (2.0 part 25b)
#define HOENN_CALL_ICE_GLALIE 35 // Brendan: you met the Glalie in Shoal Cave's ice chamber (2.0 part 26a)
#define HOENN_CALL_FROST_FEATHER 36 // May: you found Articuno's feather behind the Froslass (2.0 part 26b)

// ---- Two builder lanes (since Nov 27, hoenn-docs/lanes/README.md) ----
// New event calls take an ID from their lane's range and go in that lane's
// section. Lane A's due checks are in src/hoenn_lane_a.c, lane B's in
// src/hoenn_lane_b.c; their switch cases in data/scripts/hoenn_lane_a/b.inc.
// Lane A: 37-69 (27a, started before the split, also takes its IDs from here).
#define HOENN_CALL_LANE_A_FIRST 37
#define HOENN_CALL_LANE_A_LAST  69
#define HOENN_CALL_CIPHER 37 // Brendan: the Ruins of Alph lab phoned Birch about a braille wall (2.0 part 27a)
#define HOENN_CALL_CIPHER_FRAGMENT 38 // May: the Ruins lab phoned Birch about a tablet fragment (2.0 part 27b)
// (lane A's calls go here)

// Lane B: 70-99.
#define HOENN_CALL_LANE_B_FIRST 70
#define HOENN_CALL_LANE_B_LAST  99
// (lane B's calls go here, at the end of the file)

#endif // GUARD_CONSTANTS_HOENN_PHONE_H
