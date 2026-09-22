MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "La rica atmósfera de la montaña\n"
	.string "¡ha elevado mi poder psíquico!\p"
	.string "Un simple niño como tú...\n"
	.string "¿Sueñas con ganar?$"

MtPyre_3F_Text_WilliamDefeat:
	.string "Me hundo en la lástima...$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "Mis poderes psíquicos seguro\n"
	.string "crecieron mucho, pero...$"

MtPyre_3F_Text_KaylaIntro:
	.string "¡Ahajajaja!\p"
	.string "Este no es lugar para niños,\n"
	.string "¡y menos para ti!$"

MtPyre_3F_Text_KaylaDefeat:
	.string "Perdí eso limpiamente...$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "Esto significa que mi entreno no\n"
	.string "Suficiente...\p"
	.string "Debo seguir trabajando para llegar\n"
	.string "a la cima...\p"
	.string "¡Vamos, yo!$"

MtPyre_3F_Text_GabrielleIntro:
	.string "¿Por qué viniste aquí?$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "¡Eso fue increíble!\n"
	.string "Eres un ENTRENADOR muy especial.$"

MtPyre_3F_Text_GabriellePostBattle:
	.string "POKéMON que ya no están en este mundo.\n"
	.string "POKéMON que están contigo ahora.\p"
	.string "Y los POKéMON que conocerás\n"
	.string "en el futuro...\p"
	.string "A todos debes quererlos por igual.\n"
	.string "Por favor, recuerda eso.$"

MtPyre_3F_Text_GabrielleRegister:
	.string "Me gustaría ver a tus POKéMON\n"
	.string "cuando crezcan un poco más...\p"
	.string "Por favor, deja que vea tu POKéNAV.$"

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "Oh, eres tú...\p"
	.string "¿Vienes a mostrarme cómo crecieron?\n"
	.string "POKéMON?$"

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "¡Qué increíble!\n"
	.string "Eres una persona especial.$"

MtPyre_3F_Text_GabriellePostRematch:
	.string "POKéMON que ya no están en este mundo.\n"
	.string "POKéMON que están contigo ahora.\p"
	.string "Y los POKéMON que conocerás\n"
	.string "en el futuro...\p"
	.string "A todos debes quererlos por igual.\n"
	.string "Veo que lo has recordado.$"

