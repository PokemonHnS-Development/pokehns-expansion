LavenderTown_SoulHouse_hns_MapScripts::
	.byte 0

LavenderTownSoulHouse_EventScript_MrFuji::
	msgbox MrFuji_Text_Main, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Lass::
	msgbox SoulHouse_Text_Lass, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Teacher::
	msgbox SoulHouse_Text_Teacher, MSGBOX_NPC
	end
LavenderTownSoulHouse_EventScript_Granny::
	msgbox SoulHouse_Text_Granny, MSGBOX_NPC
	end

MrFuji_Text_Main:
	.string "SR.FUJI: Bienvenido.\p"
	.string "Hmm... Parece que crías a\n"
	.string "tus POKéMON de forma amable\l"
	.string "y cariñosa.\p"
	.string "Los amantes de los POKéMON vienen\n"
	.string "aquí a rendir respeto a los\l"
	.string "POKéMON planta.\p"
	.string "que ya no están.\n"
	.string "Por favor, reza por las almas de\p"
	.string "los POKéMON fallecidos.\n"
	.string "Seguro que eso los hará felices.$"

SoulHouse_Text_Teacher:
	.string "Creo que hay otras tumbas de\n"
	.string "POKéMON por aquí.\p"
	.string "Hay muchas cámaras a las que solo\n"
	.string "el SR.FUJI puede entrar.$"

SoulHouse_Text_Lass:
	.string "Vine con mi mamá a visitar\n"
	.string "tumbas de POKéMON...$"

SoulHouse_Text_Granny:
	.string "Los POKéMON que vivieron conmigo...\p"
	.string "Los amaba como si fueran\n"
	.string "mis nietos...$"
