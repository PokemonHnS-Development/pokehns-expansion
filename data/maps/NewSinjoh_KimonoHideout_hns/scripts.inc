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
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_MiharuFinal
	goto_if_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_MiharuAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_MiharuBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuBattle::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MIHARU_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_MEADOW_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuAfter::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle:
	.string "MIHARU: Just as we predicted.\p"
	.string "The champion of stone sent you\n"
	.string "to collect the PLATES.\p"
	.string "Our order has guarded these\n"
	.string "PLATES for centuries.\p"
	.string "We will not part with them\n"
	.string "readily.$"

NewSinjoh_KimonoHideout_Text_MiharuAfter:
	.string "MIHARU: You are worthy.$"

NewSinjoh_KimonoHideout_EventScript_MiharuFinal::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_MiharuFinal:
	.string "MIHARU: You have done our village\n"
	.string "a great service, {PLAYER}.\p"
	.string "We will not forget this.$"

NewSinjoh_KimonoHideout_EventScript_Youko::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_YoukoFinal
	goto_if_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_YoukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_YoukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_YOUKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_ICICLE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle:
	.string "YOUKO: Our cousins speak so\n"
	.string "highly of you.\p"
	.string "Is it true?\p"
	.string "I will find out.$"

NewSinjoh_KimonoHideout_Text_YoukoAfter:
	.string "YOUKO: Our cousins were right\n"
	.string "about you.$"

NewSinjoh_KimonoHideout_EventScript_YoukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_YoukoFinal:
	.string "YOUKO: I had my doubts, at first.\p"
	.string "But after what you've done, it\l"
	.string "cannot be denied.$"

NewSinjoh_KimonoHideout_EventScript_Shizuko::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_ShizukoFinal
	goto_if_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_ShizukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_ShizukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_SHIZUKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_PIXIE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle:
	.string "SHIZUKO: We are trained in\n"
	.string "battle as well as dance.\p"
	.string "Obtaining the PLATEs will\n"
	.string "require strength and determination.$"

NewSinjoh_KimonoHideout_Text_ShizukoAfter:
	.string "SHIZUKO: The bond you share\n"
	.string "with your POKéMON is quite strong.\p"
	.string "You have earned this PLATE.$"

NewSinjoh_KimonoHideout_EventScript_ShizukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_ShizukoFinal:
	.string "SHIZUKO: Few trainers in all\n"
	.string "of SINJOH's storied history have\l"
	.string "managed what you've just done.\p"
	.string "Quite impressive, {PLAYER}.$"

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
