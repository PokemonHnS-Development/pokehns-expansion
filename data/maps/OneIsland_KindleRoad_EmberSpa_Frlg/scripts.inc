OneIsland_KindleRoad_EmberSpa_Frlg_MapScripts::
	.byte 0

OneIsland_KindleRoad_EmberSpa_EventScript_OldMan::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_WaterWarmsMeToCore, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_BaldingMan1::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_EnjoyBowlOfChowder, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_BaldingMan2::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_HotSpringIsTherapeutic, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_OldWoman::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_SeeHowSmoothMySkinIs, MSGBOX_NPC
	end

OneIsland_KindleRoad_EmberSpa_EventScript_BlackBelt::
	lock
	faceplayer
	famechecker FAMECHECKER_BRUNO, 3
	msgbox OneIsland_KindleRoad_EmberSpa_Text_BrunoVisitsSpaOnOccasion
	release
	end

OneIsland_KindleRoad_EmberSpa_EventScript_RockSmashMan::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HM06, OneIsland_KindleRoad_EmberSpa_EventScript_AlreadyGotHM06
	msgbox OneIsland_KindleRoad_EmberSpa_Text_UsedThisToMakeEmberSpa
	giveitem ITEM_HM06
	setflag FLAG_GOT_HM06
	msgbox OneIsland_KindleRoad_EmberSpa_Text_ExplainHM06
	release
	end

OneIsland_KindleRoad_EmberSpa_EventScript_AlreadyGotHM06::
	msgbox OneIsland_KindleRoad_EmberSpa_Text_ExplainHM06
	release
	end

OneIsland_KindleRoad_EmberSpa_EventScript_SpaHeal::
	lockall
	fadescreen FADE_TO_WHITE
	special HealPlayerParty
	fadescreen FADE_FROM_WHITE
	msgbox OneIsland_KindleRoad_EmberSpa_Text_WaterExquisiteFullyRefreshed
	setvar VAR_TEMP_1, 1
	releaseall
	end

OneIsland_KindleRoad_EmberSpa_Text_WaterWarmsMeToCore::
	.string "Hm!\n"
	.string "Haaaaaaaaaaah!\p"
	.string "¡Aaaah! ¡Esto es el paraíso!\n"
	.string "¡El agua me calienta hasta el\p"
	.string "alma! Deberías meterte también.\p"
	.string "Ve al centro, relájate y\n"
	.string "¡cálate bien!$"

OneIsland_KindleRoad_EmberSpa_Text_EnjoyBowlOfChowder::
	.string "Mi parte favorita del baño es\n"
	.string "justo después de esto.\p"
	.string "Un tazón de sopa espesa\n"
	.string "también me calienta por dentro!$"

OneIsland_KindleRoad_EmberSpa_Text_WaterExquisiteFullyRefreshed::
	.string "El agua está perfecta.\n"
	.string "Se siente exquisito...\p"
	.string "{PLAYER} y los POKéMON se\n"
	.string "¡sintieron totalmente renovados!$"

OneIsland_KindleRoad_EmberSpa_Text_HotSpringIsTherapeutic::
	.string "Remojarse en un agua termal es\n"
	.string "terapéutico, según dicen.$"

OneIsland_KindleRoad_EmberSpa_Text_SeeHowSmoothMySkinIs::
	.string "Mira mi cara.\n"
	.string "¿Ves lo suave que está mi piel?\p"
	.string "El agua termal mantiene mi\n"
	.string "piel más joven que mi edad.$"

OneIsland_KindleRoad_EmberSpa_Text_BrunoVisitsSpaOnOccasion::
	.string "Después de un día de duro\n"
	.string "nada mejor que un baño relajante\l"
	.string "en las termas.\p"
	.string "BRUNO, que es más veterano,\n"
	.string "visita el SPA ocasionalmente.\p"
	.string "Dice que lo hace para mantener\n"
	.string "su cuerpo como el de sus POKéMON.$"

OneIsland_KindleRoad_EmberSpa_Text_UsedThisToMakeEmberSpa::
	.string "Las aguas termales van de la\n"
	.string "mano con los volcanes.\p"
	.string "Construí el SPA EMBER yo\n"
	.string "mismo hace ya años.\p"
	.string "Tallé la piscina de una roca\n"
	.string "gigante con mis propias manos.\p"
	.string "Lo usaba en ese entonces.\n"
	.string "Supongo que puedo cederlo.$"

OneIsland_KindleRoad_EmberSpa_Text_ExplainHM06::
	.string "Eso hace trizas rocas como si\n"
	.string "fueran de galleta.$"

