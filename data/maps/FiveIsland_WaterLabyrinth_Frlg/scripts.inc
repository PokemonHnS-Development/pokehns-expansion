FiveIsland_WaterLabyrinth_Frlg_MapScripts::
	.byte 0

FiveIsland_WaterLabyrinth_EventScript_EggGentleman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TOGEPI_EGG, FiveIsland_WaterLabyrinth_EventScript_PostEggComment
	goto_if_set FLAG_NO_ROOM_FOR_TOGEPI_EGG, FiveIsland_WaterLabyrinth_EventScript_ReturnForEgg
	msgbox FiveIsland_WaterLabyrinth_Text_LetMeTakeLookAtMons
	specialvar VAR_RESULT, GetLeadMonFriendship
	goto_if_eq VAR_RESULT, 6, FiveIsland_WaterLabyrinth_EventScript_LeadMonMaxFriendship
	msgbox FiveIsland_WaterLabyrinth_Text_HmmISeeIsee
	release
	end

FiveIsland_WaterLabyrinth_EventScript_MonDaisyComment::
	famechecker FAMECHECKER_DAISY, 2
	msgbox FiveIsland_WaterLabyrinth_Text_CuteMonRemindsMeOfDaisy
	release
	end

FiveIsland_WaterLabyrinth_EventScript_LeadMonMaxFriendship::
	msgbox FiveIsland_WaterLabyrinth_Text_TreatMonRightHaveThis
	goto FiveIsland_WaterLabyrinth_EventScript_TryGiveEgg
	end

FiveIsland_WaterLabyrinth_EventScript_TryGiveEgg::
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, FiveIsland_WaterLabyrinth_EventScript_NoRoomForEgg
	setflag FLAG_GOT_TOGEPI_EGG
	giveegg SPECIES_TOGEPI
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_LEVEL_UP
	message FiveIsland_WaterLabyrinth_Text_ReceivedEggFromMan
	waitfanfare
	waitmessage
	call EventScript_RestorePrevTextColor
	goto FiveIsland_WaterLabyrinth_EventScript_PostEggComment
	end

@ If the player has a Togepi/Togetic from this game (assumed to be the one the man gave you) then comment on it
@ Otherwise make normal comment
FiveIsland_WaterLabyrinth_EventScript_PostEggComment::
	bufferspeciesname STR_VAR_2, SPECIES_TOGEPI
	setvar VAR_0x8004, SPECIES_TOGEPI
	specialvar VAR_RESULT, PlayerPartyContainsSpeciesWithPlayerID
	goto_if_eq VAR_RESULT, TRUE, FiveIsland_WaterLabyrinth_EventScript_MonDaisyComment
	bufferspeciesname STR_VAR_2, SPECIES_TOGETIC
	setvar VAR_0x8004, SPECIES_TOGETIC
	specialvar VAR_RESULT, PlayerPartyContainsSpeciesWithPlayerID
	goto_if_eq VAR_RESULT, TRUE, FiveIsland_WaterLabyrinth_EventScript_MonDaisyComment
	msgbox FiveIsland_WaterLabyrinth_Text_GladIMetSomeoneLikeYou
	release
	end

FiveIsland_WaterLabyrinth_EventScript_NoRoomForEgg::
	setflag FLAG_NO_ROOM_FOR_TOGEPI_EGG
	msgbox FiveIsland_WaterLabyrinth_Text_DontHaveSpaceInYourParty
	release
	end

FiveIsland_WaterLabyrinth_EventScript_ReturnForEgg::
	goto FiveIsland_WaterLabyrinth_EventScript_TryGiveEgg
	end

FiveIsland_WaterLabyrinth_Text_LetMeTakeLookAtMons::
	.string "Viajas por todas partes,\n"
	.string "tipo PLANTA, ¿verdad?\p"
	.string "No estás exigiendo a tus POKéMON\n"
	.string "demasiado duro, ¿verdad?\p"
	.string "Déjame ver.\n"
	.string "... ... ...   ... ... ...$"

FiveIsland_WaterLabyrinth_Text_HmmISeeIsee::
	.string "Ah, mmm...\n"
	.string "Ya veo, ya veo...$"

FiveIsland_WaterLabyrinth_Text_TreatMonRightHaveThis::
	.string "Oh, impresionante.\n"
	.string "Tratas bien a tus POKéMON.\p"
	.string "Creo que puedo confiarte\n"
	.string "esto.\p"
	.string "Por favor, quiero que tengas esto.$"

FiveIsland_WaterLabyrinth_Text_ReceivedEggFromMan::
	.string "{PLAYER} recibió un HUEVO\n"
	.string "¡del hombre!$"

FiveIsland_WaterLabyrinth_Text_DontHaveSpaceInYourParty::
	.string "...Lamentablemente, no tienes\n"
	.string "espacio para esto en tu equipo.\p"
	.string "Será mejor que vuelvas por él\n"
	.string "otra ocasión.$"

@ Unused
FiveIsland_WaterLabyrinth_Text_YouveComeBackForTheEgg::
	.string "やあ\n"
	.string "タマゴを　もらいに\l"
	.string "きて　くれたんだね$"

FiveIsland_WaterLabyrinth_Text_GladIMetSomeoneLikeYou::
	.string "Recibí ese HUEVO cuando estaba\n"
	.string "viajando.\p"
	.string "Me alegra haberte conocido.$"

FiveIsland_WaterLabyrinth_Text_CuteMonRemindsMeOfDaisy::
	.string "Oh, hola.\n"
	.string "Qué lindo {STR_VAR_2}.\p"
	.string "Verlo me recuerda a un dulce\n"
	.string "de una niña que conocí viajando.\p"
	.string "Cepillaba suavemente a POKéMON...\n"
	.string "Era como un angelito.\p"
	.string "El nombre de esa niña...\n"
	.string "creo que era DAISY.$"

FiveIsland_WaterLabyrinth_Text_AlizeIntro::
	.string "Este es un excelente entorno\n"
	.string "para criar POKéMON.$"

FiveIsland_WaterLabyrinth_Text_AlizeDefeat::
	.string "¡Tus POKéMON están creciendo\n"
	.string "de forma admirable!$"

FiveIsland_WaterLabyrinth_Text_AlizePostBattle::
	.string "Sabes, creo que tienes el\n"
	.string "talento para ser un buen CRIADOR.$"
