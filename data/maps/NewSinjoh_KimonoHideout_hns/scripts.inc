NewSinjoh_KimonoHideout_hns_MapScripts::
   map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_KimonoHideout_OnFrame
    .byte 0


NewSinjoh_KimonoHideout_OnFrame:
	map_script_2 VAR_SINJOH_STORYLINE, 4, NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos
	.2byte 0

@ ============INTRO CUTSCENE=====================================================================================

NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos, MSGBOX_AUTOCLOSE
	applymovement LOCALID_PLAYER, NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_MIHARU, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_MIHARU, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_SHIZUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_SHIZUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_YOUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_YOUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	setvar VAR_SINJOH_STORYLINE, 5
	release
	end

NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksDown:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_down
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksUp:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_up
	face_down
	step_end

NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos:
	.string "{PLAYER}.\p"
	.string "Please, approach.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu:
    .string "MIHARU: Welcome to NEW SINJOH, \n"
	.string "{PLAYER}.\p"
	.string "For generations, this village has\n"
	.string "peacefully coexisted with immensely\l"
	.string "powerful POKéMON, in isolation from\l"
	.string "the prying eyes of outsiders.\p"
	.string "Recent events at our sacred temple\n"
	.string "and a subsequent influx of uninvited\l"
	.string "guests now threaten to disrupt the\l"
	.string "careful balance we have long\l"
	.string "protected.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko:
	.string "SHIZUKO: Our cousins in ECRUTEAK\n"
	.string "CITY made us aware of your\l"
	.string "connection to the LEGENDARY POKéMON\l"
	.string "of the JOHTO REGION, and your\l"
	.string "prowess as a trainer.\p"
	.string "We believe you can help us in these\n"
	.string "trying times.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko:
	.string "YOUKO: Go to the SINJOH RUINS, to\n"
	.string "the north of ROUTE 50.\p"
	.string "Meet with the scientists there, and\n"
	.string "investigate the events that invoked\l"
	.string "their presence.\p"
	.string "It is imperative that the LEGENDARY\n"
	.string "POKéMON there are not disturbed\l"
	.string "by the unworthy.$"


@ ============KIMONO GIRL NPCs=====================================================================================

NewSinjoh_KimonoHideout_EventScript_Miharu::
	lock
	faceplayer
	goto_if_eq VAR_SINJOH_STORYLINE, 5, NewSinjoh_KimonoHideout_EventScript_MiharuBeforePlateQuest
	release
	end

NewSinjoh_KimonoHideout_EventScript_MiharuBeforePlateQuest::
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	release
	end


NewSinjoh_KimonoHideout_EventScript_Youko::
	lock
	faceplayer
	goto_if_eq VAR_SINJOH_STORYLINE, 5, NewSinjoh_KimonoHideout_EventScript_YoukoBeforePlateQuest
	release
	end
	
NewSinjoh_KimonoHideout_EventScript_YoukoBeforePlateQuest::
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	release
	end


NewSinjoh_KimonoHideout_EventScript_Shizuko::
	lock
	faceplayer
	goto_if_eq VAR_SINJOH_STORYLINE, 5, NewSinjoh_KimonoHideout_EventScript_ShizukoBeforePlateQuest
	release
	end
	
NewSinjoh_KimonoHideout_EventScript_ShizukoBeforePlateQuest::
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	release
	end

@ =================================================================================================

NewSinjoh_KimonoHideout_EventScript_OldMan::
	msgbox NewSinjoh_KimonoHideout_Text_OldMan, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_OldMan:
    .string "The KIMONO GIRLS have watched\n"
	.string "over our village since its founding.\p"
	.string "They have sacrificed much.\p"
	.string "Blessed by the Gods themselves,\n"
	.string "they have powers beyond that\l"
	.string "of any normal trainer!\p"
	.string "That is to say, be prepared\n"
	.string "if you ever fight them, young one.$"

NewSinjoh_KimonoHideout_Text_OldManAfter:
    .string "You have bested the champions of\n"
	.string "our village.\p"
	.string "What does that make you, young one?$"
