CeladonCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_OnTransition
	.byte 0

CeladonCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_CELADON_CITY
	end

CeladonCity_EventScript_LittleGirl::
	msgbox CeladonCity_Text_GotMyKoffingInCinnabar, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan1::
	lock
	msgbox CeladonCity_Text_GymIsGreatFullOfWomen
	release
	end

CeladonCity_EventScript_Woman::
	msgbox CeladonCity_Text_GameCornerIsBadForCitysImage, MSGBOX_NPC
	end

CeladonCity_EventScript_OldMan2::
	msgbox CeladonCity_Text_BlewItAllAtSlots, MSGBOX_NPC
	end

CeladonCity_EventScript_SoftboiledTutor::
	goto EventScript_SoftboiledTutor
	end

CeladonCity_EventScript_FatMan::
	lock
	faceplayer
	msgbox CeladonCity_Text_MyTrustedPalPoliwrath
	closemessage
	applymovement LOCALID_CELADON_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_Poliwrath::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	msgbox CeladonCity_Text_Poliwrath
	closemessage
	waitmoncry
	applymovement LOCALID_CELADON_POLIWRATH, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

CeladonCity_EventScript_RocketGrunt1::
	msgbox CeladonCity_Text_KeepOutOfTeamRocketsWay, MSGBOX_NPC
	end

CeladonCity_EventScript_RocketGrunt2::
	msgbox CeladonCity_Text_GetLostOrIllPunchYou, MSGBOX_NPC
	end

CeladonCity_EventScript_Boy::
	msgbox CeladonCity_Text_ScaldedTongueOnTea, MSGBOX_NPC
	end

CeladonCity_EventScript_SilphCoScientist::
	msgbox CeladonCity_Text_SomeoneStoleSilphScope, MSGBOX_NPC
	end

CeladonCity_EventScript_TrainerTips1::
	msgbox CeladonCity_Text_ExplainXAccuracyDireHit, MSGBOX_SIGN
	end

CeladonCity_EventScript_CitySign::
	msgbox CeladonCity_Text_CitySign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_ERIKA, 0
	msgbox CeladonCity_Text_GymSign
	releaseall
	end

CeladonCity_EventScript_MansionSign::
	msgbox CeladonCity_Text_MansionSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_DeptStoreSign::
	msgbox CeladonCity_Text_DeptStoreSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_TrainerTips2::
	msgbox CeladonCity_Text_GuardSpecProtectsFromStatus, MSGBOX_SIGN
	end

CeladonCity_EventScript_PrizeExchangeSign::
	msgbox CeladonCity_Text_PrizeExchangeSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GameCornerSign::
	msgbox CeladonCity_Text_GameCornerSign, MSGBOX_SIGN
	end

CeladonCity_Text_GotMyKoffingInCinnabar::
	.string "Conseguí a mi KOFFING en CANELA.\p"
	.string "Suele ser amable, pero respira\n"
	.string "Envenena cuando se enoja.$"

CeladonCity_Text_GymIsGreatFullOfWomen::
	.string "¡Jejeje! ¡Este GIMNASIO es genial!\n"
	.string "¡Está lleno de mujeres!"

CeladonCity_Text_GameCornerIsBadForCitysImage::
	.string "CELADÓN se enorgullece de sus esfuerzos\n"
	.string "para mantener la ciudad hermosa.\p"
	.string "Por eso el nuevo SALÓN DE JUEGOS es\n"
	.string "Es malo para la imagen de nuestra ciudad.$"

CeladonCity_Text_BlewItAllAtSlots::
	.string "Moan...\n"
	.string "¡Me lo gasté todo en las tragamonedas!\p"
	.string "Sabía que debería haber canjeado mi\n"
	.string "MONEDAS por premios!$"

CeladonCity_Text_MyTrustedPalPoliwrath::
	.string "Este es mi compañero de confianza, POLIWRATH.\p"
	.string "Evolucionó de un POLIWHIRL cuando\n"
	.string "Usé una Piedra Agua.$"

CeladonCity_Text_Poliwrath::
	.string "POLIWRATH: Ribi ribit!$"

CeladonCity_Text_GetLostOrIllPunchYou::
	.string "¿Qué miras?\n"
	.string "Lárgate, o te doy un puñetazo.$"

CeladonCity_Text_KeepOutOfTeamRocketsWay::
	.string "¡Apártate del camino del EQUIPO ROCKET!$"

CeladonCity_Text_ExplainXAccuracyDireHit::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "PRECISIÓN X aumenta la precisión de\n"
	.string "técnicas.\p"
	.string "GOLPE CRÍTICO aumenta la probabilidad\n"
	.string "de golpes críticos.\p"
	.string "Consigue tus objetos en CELESTE\n"
	.string "DEPT. STORE!$"

CeladonCity_Text_CitySign::
	.string "CELADON CITY\n"
	.string "La Ciudad de los Sueños Arcoíris$"

CeladonCity_Text_GymSign::
	.string "CELADON CITY POKéMON GYM\n"
	.string "LÍDER: ERIKA\l"
	.string "¡La Princesa Amante Naturaleza!$"

CeladonCity_Text_MansionSign::
	.string "CELADON MANSION$"

CeladonCity_Text_DeptStoreSign::
	.string "Encuentra lo que necesitas en el\n"
	.string "CELADON DEPT. STORE!$"

CeladonCity_Text_GuardSpecProtectsFromStatus::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "La DEF. ESP. protege al POKéMON\n"
	.string "de movimientos que reducen características durante\l"
	.string "fantástica.\p"
	.string "Obtén tus objetos en el\n"
	.string "CELADON DEPT. STORE!$"

CeladonCity_Text_PrizeExchangeSign::
	.string "¡MONEDAS canjeadas por premios!\n"
	.string "PRIZE EXCHANGE$"

CeladonCity_Text_GameCornerSign::
	.string "ROCKET GAME CORNER\n"
	.string "¡El parque de diversiones para adultos!$"

CeladonCity_Text_ScaldedTongueOnTea::
	.string "Aaaagh, ow...\n"
	.string "¡Me quemé la lengua!\p"
	.string "Esta simpática señora mayor en la MANSIÓN\n"
	.string "me dio un poco de TÉ.\p"
	.string "¡Pero hacía un calor abrasador!\n"
	.string "Hay que enfriarlo para beberlo.$"

Text_SoftboiledTeach::
	.string "¡Hola!\p"
	.string "Te he visto por ahí, pero nunca\n"
	.string "Tuvo la oportunidad de charlar.\p"
	.string "Debe ser la buena suerte la que trajo\n"
	.string "Juntos por fin.\p"
	.string "Me gustaría celebrar enseñando\n"
	.string "Aprendiste el movimiento Huevo Blando.$"

Text_SoftboiledDeclined::
	.string "Siempre estaré atento\n"
	.string "estábamos guardando.\p"
	.string "Espero que podamos charlar de nuevo.$"

Text_SoftboiledWhichMon::
	.string "So, who's the POKéMON that gets\n"
	.string "la oportunidad de aprender HUEVO BLANDO?$"

Text_SoftboiledTaught::
	.string "¡Te deseo mucha suerte!$"

CeladonCity_Text_SomeoneStoleSilphScope::
	.string "Oh, ¿qué voy a hacer...\p"
	.string "Alguien robó nuestro SILPH SCOPE.\p"
	.string "El ladrón vino corriendo por aquí,\n"
	.string "Estoy seguro.\p"
	.string "¡Pero lo perdí de vista!\n"
	.string "¿A dónde fue?$"

