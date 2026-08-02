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
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_MiharuFinal
	goto_if_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_MiharuAfter
	msgbox NewSinjoh_KimonoHideout_Text_MiharuBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle
	end
NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_MiharuBattle
	end
NewSinjoh_KimonoHideout_EventScript_MiharuBattle::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_Text_MiharuDefeat
	giveitem ITEM_MEADOW_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuAfter::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_MiharuBefore:
	.string "MIHARU: TODO$"

NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle:
	.string "MIHARU: TODO$"

NewSinjoh_KimonoHideout_Text_MiharuDefeat:
	.string "MIHARU: TODO$"

NewSinjoh_KimonoHideout_Text_MiharuAfter:
	.string "MIHARU: TODO$"

NewSinjoh_KimonoHideout_EventScript_MiharuFinal::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuFinal, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_MiharuFinal:
	.string "MIHARU: TODO$"


NewSinjoh_KimonoHideout_EventScript_Youko::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_YoukoFinal
	goto_if_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_YoukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_YoukoBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle
	end
NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_YoukoBattle
	end
NewSinjoh_KimonoHideout_EventScript_YoukoBattle::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_Text_YoukoDefeat
	giveitem ITEM_ICICLE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_YoukoBefore:
	.string "YOUKO: TODO$"

NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle:
	.string "YOUKO: TODO$"

NewSinjoh_KimonoHideout_Text_YoukoDefeat:
	.string "YOUKO: TODO$"

NewSinjoh_KimonoHideout_Text_YoukoAfter:
	.string "YOUKO: TODO$"

NewSinjoh_KimonoHideout_EventScript_YoukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoFinal, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_YoukoFinal:
	.string "YOUKO: TODO$"


NewSinjoh_KimonoHideout_EventScript_Shizuko::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_ShizukoFinal
	goto_if_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_ShizukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle
	end
NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_ShizukoBattle
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoBattle::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_Text_ShizukoDefeat
	giveitem ITEM_PIXIE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_ShizukoBefore:
	.string "SHIZUKO: TODO$"

NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle:
	.string "SHIZUKO: TODO$"

NewSinjoh_KimonoHideout_Text_ShizukoDefeat:
	.string "SHIZUKO: TODO$"

NewSinjoh_KimonoHideout_Text_ShizukoAfter:
	.string "SHIZUKO: TODO$"

NewSinjoh_KimonoHideout_EventScript_ShizukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoFinal, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_ShizukoFinal:
	.string "SHIZUKO: TODO$"

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
