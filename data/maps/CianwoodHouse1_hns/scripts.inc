CianwoodHouse1_hns_MapScripts::
	.byte 0

CianwoodHouse1_EventScript_Hermit::
	lock
	faceplayer
	msgbox CianwoodCity_Text_OldManIntro, MSGBOX_DEFAULT
	goto_if_eq VAR_LUGIA_OR_HOOH, 2, CianwoodHouse1_EventScript_HermitHooh
	checkitem ITEM_TIDAL_BELL
	goto_if_eq VAR_RESULT, TRUE, CianwoodHouse1_EventScript_HermitTidalBell
	msgbox CianwoodCity_Text_WhirlIslandsStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitTidalBell::
	msgbox CianwoodCity_Text_TidalBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitHooh::
	checkitem ITEM_CLEAR_BELL
	goto_if_eq VAR_RESULT, TRUE, CianwoodHouse1_EventScript_HermitClearBell
	msgbox CianwoodCity_Text_BellTowerStory, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse1_EventScript_HermitClearBell::
	msgbox CianwoodCity_Text_ClearBellReaction, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_OldManIntro:
	.string "No recuerdo la última vez que\n"
	.string "alguien vino a visitarme.\p"
	.string "Cuando era joven, yo también\n"
	.string "era un Entrenador POKéMON.\l"
	.string "Intenté llegar a la torre y\l"
	.string "bucear en el océano.\p"
	.string "Me esforcé mucho en muchas\n"
	.string "cosas.\p"
	.string "Bueno, ahora me lo tomo con calma,\n"
	.string "escuchando las olas y el viento\l"
	.string "en esta playa.$"

CianwoodCity_Text_BellTowerStory:
	.string "¿Has oído hablar de la TORRE TIN?\n"
	.string "¿en CIUDAD IRIS?\p"
	.string "Están las llamadas Campanas Claras\n"
	.string "en lo alto de la torre.\p"
	.string "No hacen ni un solo ruido\n"
	.string "con vientos fuertes.\p"
	.string "Solo hay una forma de hacer que\n"
	.string "suenen.\p"
	.string "Es obtener otra CAMPANA CLARA\n"
	.string "igual a las que están en lo alto\l"
	.string "de la torre.\p"
	.string "La busqué cuando era joven.\n"
	.string "¿Has oído hablar de las\nISLAS REMOLINO?\pAllí están las llamadas\nCampanas Marea\nen la base de su cascada.\pNo hacen ni\nun solo ruido\nentre las olas rompientes.\pSolo hay una\nforma de hacer que\nsuenen.\pEs para obtener otra Campana\nMareal\ncomo las que hay en la base de\nla\lcascada.\pLa busqué cuando era joven.\nPero nunca conseguí una...$"

CianwoodCity_Text_WhirlIslandsStory:
	.string "¿Has oído hablar de las\nISLAS REMOLINO?\pAllí están las llamadas\nCampanas Marea\nen la base de su cascada.\pNo hacen ni\nun solo ruido\nentre las olas rompientes.\pSolo hay una\nforma de hacer que\nsuenen.\pEs para obtener otra Campana\nMareal\ncomo las que hay en la base de\nla\lcascada.\pLa busqué cuando era joven.\nPero nunca conseguí una...$"

CianwoodCity_Text_ClearBellReaction:
	.string "¡Oh! ¿Has logrado conseguir una\n"
	.string "CAMPANA CLARA?\p"
	.string "El sueño de mi juventud...\n"
	.string "Ya veo...\p"
	.string "Lo lograste...\n"
	.string "...\l"
	.string "...¡Puedo oírlo!\p"
	.string "El repique de campanas al viento\n"
	.string "que viene desde la dirección de la\l"
	.string "TORRE TIN...$"

CianwoodCity_Text_TidalBellReaction:
	.string "¡Oh! ¿Has logrado conseguir una\n"
	.string "¿Campana Tidal?\p"
	.string "El sueño de mi juventud...\n"
	.string "Ya veo...\p"
	.string "Lo lograste...\n"
	.string "...\l"
	.string "...¡Puedo oírlo!\p"
	.string "El repique de campanas en la brisa\n"
	.string "marina que viene desde la dirección\l"
	.string "de las ISLAS REMOLINO...$"
