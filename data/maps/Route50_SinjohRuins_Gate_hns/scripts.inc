Route50_SinjohRuins_Gate_hns_MapScripts::
	.byte 0

Route50_Gate_EventScript_Officer::
    lock
	msgbox Route50_Gate_Officer_Text MSGBOX_DEFAULT
	release
	end

Route50_Gate_Officer_Text:
    .string "Normally gates like these\n"
	.string "don't require a guard, but\l"
	.string "the archeologists in the ruins\l"
	.string "asked me to keep a watch\l"
	.string "in case anyone tries to steal\l"
	.string "any artifacts or somethin'.$"

Route50_Gate_EventScript_Rex::
    lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_KIMONOGIRLGRASS, Route50_Gate__EventScript_Rex2
	msgbox Route50_Gate_Rex_Text MSGBOX_DEFAULT
	applymovement LOCALID_MIHARU, NewSinjoh_Kimono_Dance_Movement
	waitmovement
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 2,1, 0, 2, 3, 0
    trainerbattle_no_intro TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_Miharu_Beaten
    goto NewSinjoh_Kimono_Miharu_AfterBattle