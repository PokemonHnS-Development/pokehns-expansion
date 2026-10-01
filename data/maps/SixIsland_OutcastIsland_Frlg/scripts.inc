SixIsland_OutcastIsland_Frlg_MapScripts::
	.byte 0

SixIsland_OutcastIsland_EventScript_Rocket::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_46, SixIsland_OutcastIsland_Text_RocketIntro, SixIsland_OutcastIsland_Text_RocketDefeat
	msgbox SixIsland_OutcastIsland_Text_RocketPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_OutcastIsland_Text_RocketIntro::
	.string "¡Aquí no hay POKéMON\n"
	.string "raros! ¡Ni uno!\p"
	.string "Eso me enfurece, amigo.\n"
	.string "¡Me desquitaré contigo!$"

SixIsland_OutcastIsland_Text_RocketDefeat::
	.string "...¿Eh?$"

SixIsland_OutcastIsland_Text_RocketPostBattle::
	.string "Escucha, ¿no has visto a\n"
	.string "POKéMON raros, ¿no?$"

SixIsland_OutcastIsland_Text_TylorIntro::
	.string "No tengo ninguna suerte.\n"
	.string "¡Una batalla sería un cambio!$"

SixIsland_OutcastIsland_Text_TylorDefeat::
	.string "No, nada de suerte...$"

SixIsland_OutcastIsland_Text_TylorPostBattle::
	.string "No puedo volver a casa sin\n"
	.string "atrapar algo, ¿sabes?$"

SixIsland_OutcastIsland_Text_MymoIntro::
	.string "Jadeo... Jadeo...\p"
	.string "Nadé aquí desde el PUERTO ISLA\n"
	.string "SEIS de una sola vez.$"

SixIsland_OutcastIsland_Text_MymoDefeat::
	.string "Jadeo...\n"
	.string "Jadeo...$"

SixIsland_OutcastIsland_Text_MymoPostBattle::
	.string "Solo llevo la mitad del camino...\n"
	.string "Estoy agotado...$"

SixIsland_OutcastIsland_Text_NicoleIntro::
	.string "No es tan fácil enviar POKéMON\n"
	.string "¡y nadando, sabes?$"

SixIsland_OutcastIsland_Text_NicoleDefeat::
	.string "No te gané en natación.\n"
	.string "Esto no me molesta.$"

SixIsland_OutcastIsland_Text_NicolePostBattle::
	.string "¿Vas hacia la isla que está\n"
	.string "por aquí?\p"
	.string "No vi nada interesante\n"
	.string "allí.$"

SixIsland_OutcastIsland_Text_AvaIntro::
	.string "AVA: Hagamos un dos contra dos\n"
	.string "¡una batalla marina!$"

SixIsland_OutcastIsland_Text_AvaDefeat::
	.string "AVA: ¡Oh, eres increíble!\n"
	.string "¡Mejor aún, estás solo!$"

SixIsland_OutcastIsland_Text_AvaPostBattle::
	.string "AVA: Sabes, prefiero el\n"
	.string "mar más que una piscina.$"

SixIsland_OutcastIsland_Text_AvaNotEnoughMons::
	.string "AVA: Nos estás retando a\n"
	.string "tener una batalla?\p"
	.string "Necesitarás al menos dos POKéMON\n"
	.string "si quieres hacer eso.$"

SixIsland_OutcastIsland_Text_GebIntro::
	.string "GEB: ¡Hermana mayor, ayuda!\n"
	.string "¡Batalla conmigo!$"

SixIsland_OutcastIsland_Text_GebDefeat::
	.string "GEB: ¡Vaya, hermana mayor, esta\n"
	.string "persona es muy buena!$"

SixIsland_OutcastIsland_Text_GebPostBattle::
	.string "GEB: Me agarro a mi hermana\n"
	.string "porque no toco el fondo.$"

SixIsland_OutcastIsland_Text_GebNotEnoughMons::
	.string "GEB: Por favor, lucha contra mí y\n"
	.string "¡mi hermana!\p"
	.string "...Oh, ¿no tienes dos POKéMON?$"
