MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "Cuando estoy aquí…\n"
	.string "Un poder curioso fluye en mí…$"

MtPyre_6F_Text_ValerieDefeat:
	.string "El poder se está desvaneciendo…$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "Tal vez el poder sea de los espíritus\n"
	.string "de POKéMON que duermen aquí…$"

MtPyre_6F_Text_ValerieRegister:
	.string "Fufufu… Perdí el combate, pero…\n"
	.string "Tengo esta pequeña habilidad…\p"
	.string "Sin haber tocado siquiera\n"
	.string "tu POKéNAV… ¡Hiyah!$"

MtPyre_6F_Text_ValerieRematchIntro:
	.string "Detrás de ti…\n"
	.string "¿Qué pasa…?$"

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "Something faded away…$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "Los POKéMON que descansan aquí…\n"
	.string "A veces, juegan…$"

MtPyre_6F_Text_CedricIntro:
	.string "¿Te has desorientado?\n"
	.string "¡No temas, que yo estoy aquí!$"

MtPyre_6F_Text_CedricDefeat:
	.string "¿No estabas perdido?$"

MtPyre_6F_Text_CedricPostBattle:
	.string "Sentía que un ENTRENADOR perdido\n"
	.string "estaría paniqueado y sería fácil.\p"
	.string "Está sucio, no lo intentaré más…$"

