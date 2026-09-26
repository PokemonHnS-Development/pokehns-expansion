VermilionCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

VermilionCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_VERMILION_CITY
	end

VermilionCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

VermilionCity_PokemonCenter_1F_EventScript_Man::
	msgbox VermilionCity_PokemonCenter_1F_Text_PoisonedMonFaintedWhileWalking, MSGBOX_NPC
	end

VermilionCity_PokemonCenter_1F_EventScript_Hiker::
	msgbox VermilionCity_PokemonCenter_1F_Text_TrainerMonsStrongerThanWild, MSGBOX_NPC
	end

VermilionCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox VermilionCity_PokemonCenter_1F_Text_AllMonWeakToSpecificTypes, MSGBOX_NPC
	end

VermilionCity_PokemonCenter_1F_EventScript_VSSeekerWoman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_VS_SEEKER, VermilionCity_PokemonCenter_1F_EventScript_ExplainVSSeeker
	msgbox VermilionCity_PokemonCenter_1F_Text_UrgeToBattleSomeoneAgain
	setflag FLAG_GOT_VS_SEEKER
	giveitem ITEM_VS_SEEKER
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	msgbox VermilionCity_PokemonCenter_1F_Text_UseDeviceForRematches
	release
	end

VermilionCity_PokemonCenter_1F_EventScript_ExplainVSSeeker::
	msgbox VermilionCity_PokemonCenter_1F_Text_ExplainVSSeeker
	release
	end

VermilionCity_PokemonCenter_1F_Text_TrainerMonsStrongerThanWild::
	.string "Aunque sean del mismo nivel,\n"
	.string "los POKéMON pueden tener muy distintas\l"
	.string "estadísticas y habilidades.\p"
	.string "Un POKéMON criado por un ENTRENADOR es\n"
	.string "más fuerte que uno salvaje.$"

VermilionCity_PokemonCenter_1F_Text_PoisonedMonFaintedWhileWalking::
	.string "¡Mi POKéMON estaba envenenado!\n"
	.string "¡Se desmayó mientras caminábamos!$"

VermilionCity_PokemonCenter_1F_Text_AllMonWeakToSpecificTypes::
	.string "Es cierto que uno de nivel\n"
	.string "un POKéMON de nivel alto será más fuerte...\p"
	.string "Pero todos los POKéMON tienen puntos\n"
	.string "débiles contra tipos específicos.\p"
	.string "Así que parece que no hay\n"
	.string "POKéMON universalmente fuertes.$"

VermilionCity_PokemonCenter_1F_Text_UrgeToBattleSomeoneAgain::
	.string "Las ganas de batallar con alguien\n"
	.string "con quien ya te has enfrentado...\p"
	.string "Alguna vez tuviste esas ganas?\n"
	.string "Seguro que sí.\p"
	.string "Yo también quise batirme con\n"
	.string "ciertas personas una y otra vez.\p"
	.string "He estado regalando estos.\n"
	.string "¡Toma uno, por favor!$"

VermilionCity_PokemonCenter_1F_Text_UseDeviceForRematches::
	.string "Usa ese aparato y encontrarás\n"
	.string "ENTRENADORES que buscan revancha.\p"
	.string "Debes cargar su batería para\n"
	.string "usarlo, aunque sea.$"

VermilionCity_PokemonCenter_1F_Text_ExplainVSSeeker::
	.string "¿Cómo se usa el BUSCA VS?\n"
	.string "No tiene ciencia.\p"
	.string "Úsalo como pi-pi-pi, y los\n"
	.string "ENTRENADORES cerca te notarán.\p"
	.string "Si algún ENTRENADOR quiere revancha,\n"
	.string "te lo avisará de inmediato.\p"
	.string "Carga su batería y úsalo\n"
	.string "cuando estés en un camino.$"
