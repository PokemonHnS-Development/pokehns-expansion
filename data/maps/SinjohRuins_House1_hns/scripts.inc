SinjohRuins_House1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_Lab_OnFrame
	map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_Lab_OnTransition
	.byte 0

SinjohRuins_Lab_OnTransition::
	call_if_eq VAR_SINJOH_STORYLINE, 7, SinjohRuins_Lab_SetupFinalPlateScene
	end

SinjohRuins_Lab_OnFrame::
	map_script_2 VAR_SINJOH_STORYLINE, 7, SinjohRuins_Lab_FinalPlateScene
	.2byte 0

@==========================Intro Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_TriggerIntroTop::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkDown1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroMid::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroBot::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkUp1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntro::
	turnobject LOCALID_PLAYER, DIR_EAST
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene2, MSGBOX_DEFAULT
	closemessage
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
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene3, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene4, MSGBOX_DEFAULT
	closemessage
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
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene6, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SINJOH_STORYLINE, 6
	setvar VAR_NOBLE_SNEASLER, 1
	setvar VAR_NOBLE_OVERQWIL, 1
	setvar VAR_NOBLE_WYRDEER, 1
	setvar VAR_NOBLE_ARCANINE, 1
	setvar VAR_NOBLE_URSALUNA, 1
	setvar VAR_NOBLE_KLEAVOR, 1
	setvar VAR_NOBLE_ELECTRODE, 1
	setvar VAR_NOBLE_TYPHLOSION, 1
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
	.string "STEVEN: When I first heard about\n"
	.string "these ruins, I had to come see\l"
	.string "them for myself.\p"
	.string "I assembled a team from DEVON CORP.\n"
	.string "and we set off on a research\l"
	.string "expedition.\p"
	.string "Who knows what we'll find buried\n"
	.string "here.\p"
	.string "We've learned quite a lot\n"
	.string "already.$"

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
	.string "The NOBLE POKéMON that guard the\n"
	.string "remaining PLATES are too strong\l"
	.string "for my team, I'm afraid.\p"
	.string "And I need to stay here to oversee\n"
	.string "the research.\p"
	.string "But I think you could do it.\n"
	.string "Will you help us?$"

SinjohRuins_Lab_Text_StevenIntroCutscene6:
	.string "Excellent.\p"
	.string "The glyphs say the PLATES are\n"
	.string "held by NOBLE POKéMON and\l"
	.string "strong trainers across SINJOH.\p"
	.string "I'll call your POKéGEAR if we\n"
	.string "learn anything new.\p"
	.string "Thank you, {PLAYER}.$"

SinjohRuins_Lab_Text_StevenIntroCutsceneRefused:
	.string "Are you sure?\p"
	.string "Who knows what we'll find buried\n"
	.string "here.\p"
	.string "Won't you reconsider?$"

@==========================Final plate Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_SetupFinalPlateScene::
	setobjectxyperm LOCALID_SINJOHRUINS_LAB_STEVEN, 4, 7
	setobjectmovementtype LOCALID_SINJOHRUINS_LAB_STEVEN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_NEWSINJOH_LAB_LINGUIST, 5, 7
	setobjectmovementtype LOCALID_NEWSINJOH_LAB_LINGUIST, MOVEMENT_TYPE_FACE_LEFT
	return

SinjohRuins_Lab_FinalPlateScene::
	lock
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	turnobject LOCALID_SINJOHRUINS_LAB_STEVEN, DIR_SOUTH
	delay 30
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkDown1
	turnobject LOCALID_NEWSINJOH_LAB_LINGUIST, DIR_SOUTH
	delay 30
	msgbox SinjohRuins_Lab_Text_FinalPlateScene1, MSGBOX_DEFAULT
	closemessage
	dofieldeffectsparkle 3, 8, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 3
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	delay 200
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	msgbox SinjohRuins_Lab_Text_FinalPlateScene2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SinjohRuins_Lab_Movement_PlayerLeaveLab
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenLeaveLab
	waitmovement 0
	waitmovement 0
	setvar VAR_SINJOH_STORYLINE, 8
	warp MAP_SINJOH_RUINS_HNS, 0
	waitstate
	end

SinjohRuins_Lab_Text_FinalPlateScene1:
	.string "STEVEN: {PLAYER}!\p"
	.string "I think I know what's going to\n"
	.string "happen we bring together all 17 of\l"
	.string "the PLATES.\p"
	.string "I feel...\l"
	.string ".....................$"

SinjohRuins_Lab_Text_FinalPlateScene2:
	.string "STEVEN: I need to see this for\n"
	.string "myself!\p"
	.string "Outside, {PLAYER}!$" 

SinjohRuins_Lab_Movement_PlayerLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

SinjohRuins_Lab_Movement_StevenLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

@==========================NPC SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_Steven::
	lock
	faceplayer
	buffernumberstring STR_VAR_1, VAR_PLATECOUNTER
	goto_if_ge VAR_PLATECOUNTER, 17, SinjohRuins_Lab_EventScript_StevenAfterAllPlates
	goto_if_ge VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_StevenAfter15Plates
	goto_if_ge VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_StevenAfter12Plates
	goto_if_ge VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_StevenAfter9Plates
	goto_if_ge VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_StevenAfter6Plates
	goto_if_ge VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_StevenAfter3Plates
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter3Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter6Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter9Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter12Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter15Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfterAllPlates::
	msgbox SinjohRuins_Lab_Text_StevenAfterAll, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_Text_StevenFindPlates:
	.string "STEVEN: Ah, {PLAYER}.\p"
	.string "{STR_VAR_1} PLATES so far.\n"
	.string "Not bad at all.\p"
	.string "I have to admit, I'm curious\n"
	.string "what will happen once they're\l"
	.string "all gathered.\p"
	.string "Well, let's see what you find.$"

SinjohRuins_Lab_Text_StevenFindPlates3:
	.string "STEVEN: Ah, {PLAYER}.\p"
	.string "{STR_VAR_1} PLATES so far.\n"
	.string "Not bad at all.\p"
	.string "Have you investigated that\n"
	.string "chamber yet?\l"
	.string "It's all quite mysterious.$"

SinjohRuins_Lab_Text_StevenFindPlates9:
	.string "STEVEN: Ah, {PLAYER}.\p"
	.string "{STR_VAR_1} PLATES so far.\n"
	.string "Making great progress.\p"
	.string "The chambers that have opened\n"
	.string "up bear a striking similarity\l"
	.string "to a series of chambers\l"
	.string "in the HOENN region.\p"
	.string "Each of those was also home to a\n"
	.string "legendary POKéMON.\p"
	.string "But in HOENN, only 3 were ever\n"
	.string "discovered.\p"
	.string "And here, there are at least 6.\p"
	.string "Who knows what we'll find next.$"

SinjohRuins_Lab_Text_StevenAfterAll:
	.string "STEVEN: {PLAYER}!\p"
	.string "This expedition has been the\n"
	.string "experience of a lifetime.\p"
	.string "Ever since I heard about these ruins,\n"
	.string "I had this feeling.\p"
	.string "I thought we would discover something\n"
	.string "amazing.\p"
	.string "And my predictions usually come true.\p"
	.string "Thank you for all your help,\n"
	.string "Champion.\p"
	.string "Where will you go from here?\p"
	.string "I hope we can meet again somewhere.$"

SinjohRuins_Lab_EventScript_Geologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_GeologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_GeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Geologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_GeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_GeologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_GeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_GeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Geologist:
    .string "Ground-penetrating radar shows\n"
	.string "6 subterranean chambers in this\l"
	.string "valley.\p"
	.string "5 of them appear to be closer\n"
	.string "to the surface level, with 1\l"
	.string "buried even deeper.$"
SinjohRuins_Lab_Text_GeologistDuring:
	.string "All this time I've directed my\n"
	.string "equipment downward to image\l"
	.string "the underground.\p"
	.string "When clearly I should've pointed\n"
	.string "it up!$"
SinjohRuins_Lab_Text_GeologistAfter:
	.string "Those PLATES were related to the\n"
	.string "most powerful POKéMON??\p"
	.string "I wish I had more time to study them.$"

SinjohRuins_Lab_EventScript_Linguist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_LinguistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_LinguistDuringEvent
	msgbox SinjohRuins_Lab_Text_Linguist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_LinguistDuringEvent::
	msgbox SinjohRuins_Lab_Text_LinguistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_LinguistAfterEvent::
	msgbox SinjohRuins_Lab_Text_LinguistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Linguist:
    .string "Ugh....\n"
	.string "There's so many glyphs to\l"
	.string "translate..\p"
	.string "We don't have anything like this\n"
	.string "in the HOENN region.$"
SinjohRuins_Lab_Text_LinguistDuring:
    .string "Imagine my surprise as I\n"
	.string "translated the glyph!\p"
	.string "I triple and quadruple checked\n"
	.string "it before telling STEVEN!\p"
	.string "I mean, really, the God of\n"
	.string "POKéMON?\p"
	.string "It's incredible.$"
SinjohRuins_Lab_Text_LinguistAfter:
    .string "This expedition has been a\n"
	.string "joy, {PLAYER}.\p"
	.string "Thanks for taking care of all\n"
	.string "the field-work.$"

SinjohRuins_Lab_EventScript_Archaeologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Archaeologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistAfter, MSGBOX_NPC
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
SinjohRuins_Lab_Text_ArchaeologistDuring:
	.string "Those plates...\n"
	.string "The connection to the SINNOH\l"
	.string "region...\l"
	.string "That flute....\l"
	.string "It's all starting to make sense.$"
SinjohRuins_Lab_Text_ArchaeologistAfter:
	.string "The historical value of what\n"
	.string "you've helped us unearth here\l"
	.string "cannot be overstated, \l"
	.string "{PLAYER}.\p"
	.string "Truly, thank you.$"

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
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_BiologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_BiologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Biologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_BiologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_BiologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_BiologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_BiologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Biologist:
    .string "Look at this wonderful specimen!\p"
	.string "This species of GROWLITHE is unlike\n"
	.string "those found anywhere else in the\l"
	.string "world.\p"
	.string "DNA analysis reveals that it shares\n"
	.string "a common ancestor with GROWLITHE\l"
	.string "found in other regions.\p"
	.string "Yet, its temperament and typing\n"
	.string "differ significantly.\p"
	.string "Descriptions of GROWLITHE found in\n"
	.string "ancient SINNOH records seem to match.\p"
	.string "Perhaps this species once occupied\n"
	.string "a much larger territory, stretching\l"
	.string "north through ancient SINNOH.$"
SinjohRuins_Lab_Text_BiologistDuring:
	.string "If the creature at the top of\n"
	.string "those stairs really is the God\l"
	.string "of all POKéMON, does that mean\l"
	.string "it is the first common ancestor?$"
SinjohRuins_Lab_Text_BiologistAfter:
	.string "I've been able to gather so much\n"
	.string "data on regional forms and\l"
	.string "divergent evolution from this\l"
	.string "expedition. Thank you,\l"
	.string "{PLAYER}.$"

SinjohRuins_Lab_EventScript_Hiker::
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_HikerDuringAfter
	msgbox SinjohRuins_Lab_Text_Hiker MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_HikerDuringAfter::
	msgbox SinjohRuins_Lab_Text_HikerDuringAfter, MSGBOX_NPC
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
SinjohRuins_Lab_Text_HikerDuringAfter:
   	.string "Don't tell anyone, {PLAYER},\n"
	.string "But I saw that temple on\l"
	.string "the mountaintop when I first\l"
	.string "discovered this place.\p"
	.string "I kept it to myself.\p"
	.string "I've blabbed enough about\n"
	.string "these ruins.\p"
	.string "It seems like everything worked\n"
	.string "out, at least.$"

@ENVIRONMENT
SinjohRuins_Lab_EventScript_Notes1::
	msgbox SinjohRuins_Lab_Text_Note1 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes2::
	msgbox SinjohRuins_Lab_Text_Note2 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes3::
	msgbox SinjohRuins_Lab_Text_Note3 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes4::
	msgbox SinjohRuins_Lab_Text_Note4 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes5::
	msgbox SinjohRuins_Lab_Text_Note5 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes6::
	msgbox SinjohRuins_Lab_Text_Note6 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes7::
	msgbox SinjohRuins_Lab_Text_Note7 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes8::
	msgbox SinjohRuins_Lab_Text_Note8 MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_Note1:
    .string "Research Log 1: May 3, 1975\p"
	.string "We've arrived at the location\n"
	.string "of the ruins.\p"
	.string "The harsh cold of Mt.Silver\n"
	.string "can be felt from all the way\l"
	.string "down here...\p"
	.string "Soon the main excavation team\n"
	.string "will make it through the mountain..\l"
	.string "I cannot wait to see what waits for us\l"
	.string "underneath our feet!$"

SinjohRuins_Lab_Text_Note2:
    .string "Research Log 2:  May 10, 1975\p"
	.string "A week of digging has yielded\n"
	.string "no result whatsoever.\p"
	.string "The ice here is impossibly thick,\n"
	.string "and the rock just breaks our\l"
	.string "equipment entirely.\p"
	.string "Not even MACHAMP was able to\n"
	.string "make a dent.\p"
	.string "What is this place?\p"
	.string "We must find out.$"

SinjohRuins_Lab_Text_Note3:
    .string "Research Log 3:  May 14, 1975\p"
	.string "You don't get ahead in life by\n"
	.string "standing by and doing nothing.\p"
	.string "I'm just a worker.\p"
	.string "But I had an idea of how we could\n"
	.string "break through the ice.\p"
	.string "Or rather, melt through it.\p"
	.string "We need FIRE-TYPE POKéMON and\n"
	.string "lots of them.\p"
	.string "But how will we get them here\n"
	.string "all the way from SINNOH?$"

SinjohRuins_Lab_Text_Note4:
    .string "Research Log 4:  May 21, 1975\p"
	.string "We've been busy.\p"
	.string "My idea worked to get us through\n"
	.string "the ice. Only we didn't get the\l"
	.string "FIRE-TYPEs from back home.\p"
	.string "The boss insisted we get them locally.\p"
	.string "We found a hot spring by a nearby\n"
	.string "village....\p"
	.string "And we took what we needed...\p"
	.string "I'm not proud of it. But sacrifices\n"
	.string "are sometimes required for progress.\p"
	.string "So, the ice is gone.\p"
	.string "There are 6 chambers, and a sealed\n"
	.string "temple in the center.\p"
	.string "The architecture of the main \n"
	.string "structure indicates it may be of the\l"
	.string "the ancient Celestica peoples...\p"
	.string "Our ancestors. Before they moved north.\p"
	.string "The boss wants that temple open as\n"
	.string "soon as possible...$"

SinjohRuins_Lab_Text_Note5:
    .string "Research Log 5:  June 2, 1975\p"
	.string "We managed to get it open...\p"
	.string "I thought I'd be overjoyed...\p"
	.string "But we lost good men in the blast\n"
	.string "of energy that sprung from the\l"
	.string "temple.\p"
	.string "Not to mention the POKéMON that\n"
	.string "helped us get it open.\l"
	.string "God rest their souls...\p"
	.string "........................\p"
	.string "Regardless.\p"
	.string "The temple is open, but we are\n"
	.string "only left with more questions.\p"
	.string "There is no legendary POKéMON\n"
	.string "inside. No treasure.\p"
	.string "Our supplies are starting to run\n"
	.string "out and we have nothing to show\l"
	.string "for our efforts...$"

SinjohRuins_Lab_Text_Note6:
  	.string "Research Log 6:  June 10, 1975\p"
    .string "The expedition is done.\n"
	.string "The rest of the men are packing up.\p"
	.string "But I can't.\p"
	.string "I can't abandon this mission.\n"
	.string "Not after what we've lost.\p"
	.string "I'm going to stay behind.$"

SinjohRuins_Lab_Text_Note7:
  	.string "Research Log 7:  September 10, 1975\p"
	.string "It's been months since we got\n"
	.string "here. Since I got here.\p"
	.string "The rest of the men are gone.\p"
	.string "Now it's just me and the\n"
	.string "POKéMON we captured to help us\l"
	.string "with the work.\p"
	.string "I've been training them to get\n"
	.string "stronger.\p"
	.string "My TYPHLOSION, most of all.\p"
	.string "We must find out what's beneath\n"
	.string "the temple.$"

SinjohRuins_Lab_Text_Note8:
  	.string "Research Log 8:  September 15, 1975\p"
	.string "Failure.\p"
	.string "......................\p"
	.string "My POKéMON....\p"
	.string "Together, all 6 of my POKéMON\n"
	.string "were able to smash through\n"
	.string "A false wall in the temple.\p"
	.string "But it was waiting for us...\p"
	.string "Something like a giant titan...\p"
	.string "The energy it released was just\n"
	.string "like what happened before.\p"
	.string "They were all destroyed...\p"
	.string "And worst of all, that beast\n"
	.string "sealed the wall back up.\p"
	.string "I can't go home.\n"
	.string "They won't recognize me anymore...\p"
	.string "This place has changed me...\p"
	.string "I'm going to talk with the\n"
	.string "villagers.\p"
	.string "They don't know what I've done.\p"
	.string "Since the other men are long\n"
	.string "gone, they'll think I'm just a\l"
	.string "lost hiker.\p"
	.string "There is no place left for me\n"
	.string "but here.$"

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


@==========================Unified other map SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_NoOp::
	release
	end

SinjohRuins_Lab_Text_PlayFlute:
	.string "The AZURE FLUTE is reacting.\n"
	.string "Play the flute?$"

SinjohRuins_Lab_Text_DropedItem:
	.string "The NOBLE {STR_VAR_1} dropped\n"
	.string "an item...$"

SinjohRuins_Lab_Text_StevenName:
	.string "STEVEN$"

SinjohRuins_Lab_EventScript_3Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall3Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_6Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall6Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_9Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall9Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_12Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall12Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_15Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall15Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_16Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall16Plates
	waitmessage
	delay 30
	setvar VAR_SINJOH_STORYLINE, 7
	return

SinjohRuins_Lab_Text_StevenCall3Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "We felt a tremor at the ruins\n"
	.string "just now.\p"
	.string "Everyone's fine, don't worry.\p"
	.string "It's quite intriguing, one of the\n"
	.string "subterranean chambers beneath the\l"
	.string "ruins has sprung open.\p"
	.string "The markings inside remind\n"
	.string "me of something from HOENN.\p"
	.string "You should come take a look\n"
	.string "when you can.$"

SinjohRuins_Lab_Text_StevenCall6Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "How's the search going?\p"
	.string "We had another tremor here.\n"
	.string "A second chamber opened up\l"
	.string "this time.\p"
	.string "I've asked our geologist to keep\n"
	.string "his instruments ready in case it\l"
	.string "happens again.\p"
	.string "The deeper we dig... The more\n"
	.string "questions we find.$"

SinjohRuins_Lab_Text_StevenCall9Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Another tremor here at the ruins.\p"
	.string "The data paints an intriguing\n"
	.string "picture.\p"
	.string "It wasn't an earthquake at all.\p"
	.string "Some kind of energy built up\n"
	.string "underground and cracked the\l"
	.string "rock open from the inside.\p"
	.string "What could cause that...\n"
	.string "I honestly don't know.$"

SinjohRuins_Lab_Text_StevenCall12Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Another tremor. Another chamber\n"
	.string "opening up.\p"
	.string "We still can't figure out the\n"
	.string "pattern behind the timing.\p"
	.string "Say, {PLAYER}... you're not\n"
	.string "doing something to cause all\l"
	.string "this, are you?\p"
	.string "No, that can't be right.$"

SinjohRuins_Lab_Text_StevenCall15Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "Did you just find another PLATE?\p"
	.string ".................\p"
	.string "Of course.\p"
	.string "The legendary POKéMON lying\n"
	.string "in these ruins... they're responding\l"
	.string "to you, aren't they?\p"
	.string "As if they want to be found.\p"
	.string "My predictions usually come true.\n"
	.string "I should have known better than\l"
	.string "to doubt you.$"

SinjohRuins_Lab_Text_StevenCall16Plates:
	.string "STEVEN: {PLAYER}.\p"
	.string "We're very close now. I can feel it.\p"
	.string "..................\p"
	.string "You should come see this for\n"
	.string "yourself.$"

