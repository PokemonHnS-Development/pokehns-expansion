SinjohRuins_House1_hns_MapScripts::
	.byte 0

@==========================Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_TriggerIntroTop::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 60
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_AUTOCLOSE
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkDown1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroMid::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 60
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_AUTOCLOSE
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroBot::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 60
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_AUTOCLOSE
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkUp1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntro::
	turnobject LOCALID_PLAYER, DIR_EAST
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene2, MSGBOX_AUTOCLOSE
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenSitsDown
	delay 10
	applymovement LOCALID_PLAYER, SinjohRuins_Lab_Movement_PlayerGoesToTable
	delay 40
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, SinjohRuins_Lab_Movement_LinguistWalkDown
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	waitmovement LOCALID_NEWSINJOH_LAB_LINGUIST
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene3, MSGBOX_AUTOCLOSE
	delay 10
	waitmovement 0
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene4, MSGBOX_AUTOCLOSE
	delay 10
	applymovement LOCALID_NEWSINJOH_LAB_LINGUIST, SinjohRuins_Lab_Movement_LinguistWalkUp
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
SinjohRuins_Lab_EventScript_IntroChoice::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutsceneRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
	goto SinjohRuins_Lab_EventScript_IntroChoice

SinjohRuins_Lab_EventScript_IntroChoseYes::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene6, MSGBOX_AUTOCLOSE
	setvar VAR_SINJOH_STORYLINE, 6
	clearflag FLAG_HIDE_SNOWSWEPT_NOBLE_SNEASLER
	clearflag FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
	clearflag FLAG_HIDE_ROUTE49_NOBLE_OVERQWIL
	clearflag FLAG_HIDE_HOTSPRINGS_NOBLE_ARCANINE
	clearflag FLAG_HIDE_HOTSPRINGS_NOBLE_URSALUNA
	clearflag FLAG_HIDE_ROUTE50_NOBLE_ELECTRODE
	clearflag FLAG_HIDE_ROUTE50_NOBLE_KLEAVOR
	release
	end

SinjohRuins_Lab_Movement_StevenMeetPlayer:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

SinjohRuins_Lab_Movement_StevenSitsDown:
	walk_down
	walk_down
	walk_down
	face_right
	step_end

SinjohRuins_Lab_Movement_PlayerGoesToTable:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	face_left
	step_end

SinjohRuins_Lab_Movement_LinguistWalkDown:
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_down
	step_end

SinjohRuins_Lab_Movement_LinguistWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end


SinjohRuins_Lab_Text_StevenIntroCutscene1:
   	.string "STEVEN: Hm?$"

SinjohRuins_Lab_Text_StevenIntroCutscene2:
	.string "STEVEN: {PLAYER}!\p"
	.string "I'd recognize those eyes anywhere.\p"
	.string "What brings you this far north?\p"
	.string ".............\p"
	.string "I see, the KIMONO GIRLS of NEW SINJOH\n"
	.string "have sent you to aid our\l"
	.string "investigation.\p"
	.string "In that case, allow me to bring you\n"
	.string "up to speed.$"

SinjohRuins_Lab_Text_StevenIntroCutscene3:
	.string "STEVEN: Ever since I got word of\n"
	.string "these ruins, I instantly knew the\l"
	.string "area would be ripe for discovery.\p"
	.string "Just imagine what secrets of history,\n"
	.string "biology, and geology we may discover!\p"
	.string "So, I assembled DEVON CORP's\n"
	.string "brightest minds and set off on this\l"
	.string "research expedition.\p"
	.string "It is our goal to solve the mystery\n"
	.string "of the ruins.\p"
	.string "And we are making swift progress.$"

SinjohRuins_Lab_Text_StevenIntroCutscene4:
	.string "LINGUIST: While the full translation\n"
	.string "of the glyphs found around the ruins\l"
	.string "still eludes me, I've been able\l"
	.string "to make out some aspects.\p"
	.string "There are 17 peculiar PLATES.\p"
	.string "They have some significance\n"
	.string "to the ruins, but we've only\l"
	.string "found 1 so far.\p"
	.string "The rest are said to be guarded\n"
	.string "by POKéMON and trainers of\l"
	.string "awesome power.$"

SinjohRuins_Lab_Text_StevenIntroCutscene5:
	.string "STEVEN: That's the story, {PLAYER}.\p"
	.string "None of my associates\n"
	.string "are quite up to the task of\l"
	.string "dealing with the 'NOBLE POKéMON\l"
	.string "that protect the other 16\l"
	.string "PLATES.\p"
	.string "And I must stay here to oversee\n"
	.string "the research.\p"
	.string "Will you help us find the other\n"
	.string "16 PLATES and solve the mystery\l"
	.string "of the ruins?$"

SinjohRuins_Lab_Text_StevenIntroCutscene6:
	.string "Excellent. It's settled.\p"
	.string "Like the glphys say, you will\n"
	.string "find the 16 PLATES in the\l"
	.string "posession of NOBLE POKéMON\l"
	.string "and powerful trainers around\l"
	.string "SINJOH.\p"
	.string "I will call your POKéGEAR\n"
	.string "with any developments.\p"
	.string "Thank you for your help,\n"
	.string "{PLAYER}.$"

SinjohRuins_Lab_Text_StevenIntroCutsceneRefused:
	.string "Are you sure?\p"
	.string "Imagine the possibilities!\p"
	.string "Surely you will help us?$"

@==========================NPC SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_Steven::
	lock
	faceplayer
	goto_if_ge VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_StevenAfter3Plates
	goto_if_ge VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_StevenAfter6Plates
	goto_if_ge VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_StevenAfter9Plates
	goto_if_ge VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_StevenAfter12Plates
	goto_if_ge VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_StevenAfter15Plates
	buffernumberstring STR_VAR_1, VAR_PLATECOUNTER
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter3Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter6Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter9Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter12Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter15Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_Text_StevenFindPlates:
	.string "How is the search going?.\p"
	.string "Looks like you've found {STR_VAR_1} PLATES\n"
	.string "so far.\p"
	.string "Like the glphys say, you will\n"
	.string "find the 16 PLATES in the\l"
	.string "posession of NOBLE POKéMON\l"
	.string "and powerful trainers around\l"
	.string "SINJOH.\p"
	.string "I will call your POKéGEAR\n"
	.string "with any developments.\p"
	.string "Thank you for your help,\n"
	.string "{PLAYER}.$"

SinjohRuins_Lab_EventScript_GeoScientist::
	msgbox SinjohRuins_Lab_Text_GeoScientist MSGBOX_NPC
	end

SinjohRuins_Lab_Text_GeoScientist:
    .string "Ground-penetrating radar shows\n"
	.string "6 subterranean chambers in this\l"
	.string "valley.\p"
	.string "5 of them appear to be closer\n"
	.string "to the surface level, with 1\l"
	.string "buried even deeper.$"

SinjohRuins_Lab_EventScript_Linguist::
    msgbox SinjohRuins_Lab_Text_Linguist MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Linguist:
    .string "Ugh....\n"
	.string "There's so many glyphs to\l"
	.string "translate..\p"
	.string "We don't have anything like this\n"
	.string "in the HOENN region.$"

SinjohRuins_Lab_EventScript_Archaeologist::
    msgbox SinjohRuins_Lab_Text_Archaeologist MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Archaeologist:
	.string "The existence of a civilization\n"
    .string "in this area changes our whole\l"
	.string "understanding of history.\p"
	.string "Many of the artifacts we've found\n"
	.string "are over a thousand years old.\p"
	.string "The carbon dating lines up with\n"
	.string "artifacts found in the SINNOH region.\p"
	.string "Although, that flute you found...\n"
	.string "It seems far older.$"

SinjohRuins_Lab_EventScript_Growlithe_Hisui::
    lock
	faceplayer
	playmoncry SPECIES_GROWLITHE, 0
	msgbox SinjohRuins_Lab_Text_Growlithe_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

SinjohRuins_Lab_Text_Growlithe_Cry:
    .string "Growh owh!!$"

SinjohRuins_Lab_EventScript_GrowlithePokeball::
    msgbox SinjohRuins_Lab_Text_GrowlitheBall MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_GrowlitheBall:
    .string "This appears to be Growlithe's ball..\n"
	.string "Better leave it alone.$"

SinjohRuins_Lab_EventScript_Biologist::
	msgbox SinjohRuins_Lab_Text_Biologist MSGBOX_NPC
	release
	end

SinjohRuins_Lab_Text_Biologist:
    .string "Look at this wonderful specimen!\p"
	.string "This species of GROWLITHE is unlike\n"
	.string "those found anywhere else in the\l"
	.string "world.\p"
	.string "DNA analysis reveals that it shares\n"
	.string "a common ancestor with GROWLITHE\l"
	.string "that can be found in other regions.\p"
	.string "Yet, its temperament and typing\n"
	.string "differ significantly.\p"
	.string "Descriptions of GROWLITHE found in\n"
	.string "ancient SINNOH records seem to match.\p"
	.string "Perhaps this species once occupied\n"
	.string "a much larger territory, stretching\l"
	.string "north through ancient SINNOH.$"

SinjohRuins_Lab_EventScript_Hiker::
	msgbox SinjohRuins_Lab_Text_Hiker MSGBOX_NPC
	release
	end

SinjohRuins_Lab_Text_Hiker:
   	.string "For ten years, I've hiked these\n"
	.string "wilds.\p"
	.string "No, make that twenty years.\p"
	.string "Until one day I found those big\n"
	.string "stone pillars and that ominous\l"
	.string "temple.\p"
	.string "That's the SINJOH RUINS.\n"
	.string "Or so I've heard.\p"
	.string "I didn't know about the town then.\p"
	.string "All I did was tell a few of my\n"
	.string "pals. But word travels fast.\p"
	.string "I never thought it would bring\n"
	.string "so much attention to the area.\p"
	.string "Makes me feel kinda funny.\n"
	.string "Y'know?$"

@ENVIRONMENT
SinjohRuins_EventScript_Notes1::
    lock
	msgbox SinjohRuins_Notes1_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes2::
    lock
	msgbox SinjohRuins_Notes2_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_BetterStop
	msgbox SinjohRuins_Notes2_Part2_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes3::
    lock
	msgbox SinjohRuins_Notes3_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes4::
    lock
	msgbox SinjohRuins_Notes4_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes5::
    lock
	msgbox SinjohRuins_Notes5_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_BetterStop
	msgbox SinjohRuins_Notes5_Part2_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes6::
    lock
	msgbox SinjohRuins_Notes6_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_BetterStop
	msgbox SinjohRuins_Notes6_Part2_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes7::
    lock
	msgbox SinjohRuins_Notes7_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_Notes1_Text:
    .string "Research Log 1: Discovery Day.\p"
	.string "We've received reports of\n"
	.string "a large structure deep under\l"
	.string "the snow, north of Mt.Silver.\p"
	.string "Once we obtain clearence\n"
	.string "from the league, I am hopeful\l"
	.string "that the excavation team\l"
	.string "will be allowed through the mountain..$"

SinjohRuins_Notes2_Text:
    .string "Research Log 2: Too Much Ice.\p"
	.string "It's been one week since the\n"
	.string "group of muscle men we've hired\l"
	.string "started digging...and they've\l"
	.string "already hit a major issue.\p"
	.string "Ice. And a lot of it.\n"
	.string "This doesn't seem to be\l"
	.string "normal ice either, not even\l"
	.string "a MACHAMP was able to break it.\p"
	.string ".........\n"
	.string "Keep reading?$"

SinjohRuins_Notes2_Part2_Text:
    .string "Research Log 2.5: A Toasty Solution.\p"
	.string "I've got it! If brute force\n"
	.string "can't shatter the ice,\l"
	.string "then what if we slowly melt it down?\p"
	.string "The Boss' family exclusively raises\n"
	.string "FIRE type POKEMON, if I could convice\l"
	.string "them to lend me a couple dozen\l"
	.string "diffrent species then maybe...\p"
	.string "........\n"
	.string "It seems the author didn't finish\l"
	.string "writing this log...$"

SinjohRuins_EventScript_BetterStop::
    msgbox SinjohRuins_BetterStop_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_BetterStop_Text:
    .string "Seems like the author keeps\n"
	.string "going for awhile...\l"
	.string "Better take a break and come\l"
	.string "back later.$"

SinjohRuins_Notes3_Text:
    .string "Research Log 3: A Resounding Success!\p"
	.string "After a very inense call, I somehow\n"
	.string "managed to convice them to transfer\l"
	.string "30 specimens from the HOENN\l"
	.string "and SINNOH reigons to help deal\l"
	.string "with our big issue...\p"
	.string "I will update once I figure\n"
	.string "out how to get them this far north..$"


SinjohRuins_Notes4_Text:
    .string "Research Log 4: A Major Discovery!\p"
	.string "Things have been so busy I forgot\n"
	.string "all about these!\p"
	.string "After we melted and pumped out\n"
	.string "most of the ice, several diffrent\l"
	.string "structures revealed themselves!\p"
	.string "My first observation of the\n"
	.string "main structure is that it shares\l"
	.string "a lot of arcitectual cues from\l"
	.string "the ancient Celestica peoples...\p"
	.string "Once we confirm the stability of the\n"
	.string "building, Boss wants to\l"
	.string "open it up...$"


SinjohRuins_Notes5_Text:
    .string "Research Log 5: The Big Burst.\p"
	.string "After several attempts, Boss\n"
	.string "managed to crack the entrance open!\p"
	.string "However, once he did..a huge wave\n"
	.string "of energy errupted out from the main\l"
	.string "hall, not only that but tall\l"
	.string "beacons of pure light shot up from\l"
	.string "the ground all over the\l"
	.string "surrounding areas!\p"
    .string ".........\n"
	.string "Keep reading?$"

SinjohRuins_Notes5_Part2_Text:
    .string "Research Log 5.5: A Stroke of Luck!\p"
    .string "A member of our team happened\n"
	.string "to be conducting an aerial\l"
	.string "archeological study of the ruins\l"
	.string "while everything went down!\p"
	.string "His report he notes that a\n"
	.string "total of 17 pillars of energy\l"
	.string "appeared through the local areas...\p"
	.string "Tomorrow the Boss is going to hold\n"
	.string "a stratagy meeting on how to\l"
	.string "procced from here...$"

SinjohRuins_Notes6_Text:
    .string "Research Log 6: A Frustrating Decision.\p"
	.string "During the meeting, it was\n"
	.string "decided that I, Edward, will\l"
	.string "have to stay back and raise\l"
	.string "all the fire type POKEMON living\l"
	.string "with us....\p"
	.string "The Boss said that since it was\n"
	.string "my idea to have them brought\l"
	.string "here, I need to take ownership\l"
	.string "of them all!\p"
	.string ".........\n"
	.string "Keep reading...?$"

SinjohRuins_Notes6_Part2_Text:
    .string "How utterly preposterous!\p"
	.string "I did not spend 20 years of my life\n"
	.string "studying under several diffrent\l"
	.string "schools just to be downgraded\l"
	.string "to a daycare worker!!\p"
	.string "Alas, there is nothing I can do...\p"
	.string "If I want to see what lies\n"
	.string "beneath these great halls,\l"
	.string "I must stick with this work..$"


SinjohRuins_Notes7_Text:
    .string "Research Log 7: An Eceological\n"
	.string "Nightmare and My Failure.\p"
	.string "It's all over, my carrier and my life.\n"
	.string "I accidently let nearly all of them out\l"
	.string "into the wild near Mt.Silver..\p"
	.string "I tried to catch them all before it\n"
	.string "was too late but they completely\l"
	.string "swept my team!\p"
	.string "I think tomorrow I might be arrested\n"
	.string "for causing damage to the local\l"
	.string "ecosystem...\p"
	.string "Tonight I'm making my\n"
	.string "escape to the village\l"
	.string "in the south, to my fellow\l"
	.string "collegues, I am deeply sorry...$"


SinjohRuins_EventScript_DisplayCase::
    lock
	msgbox SinjohRuins_DisplayCase_Text MSGBOX_DEFAULT
	release
	end


SinjohRuins_DisplayCase_Text:
    .string "It's a display case neatly\n"
	.string "packed and lined with samples\l"
	.string "and artifacts!$"

SinjohRuins_EventScript_WallSign::
    lock
	msgbox SinjohRuins_WallSign_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_WallSign_Text:
   .string "Xray and printing lab.$"


SinjohRuins_EventScript_Artifact::
   lock
   msgbox SinjohRuins_Artifact_Text MSGBOX_DEFAULT
   release
   end

SinjohRuins_Artifact_Text:
   .string "It's an artifact found from\n"
   .string "inside the ruins!$"

