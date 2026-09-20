TinTower_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TinTower_OnTransition
	.byte 0

TinTower_OnTransition::
	setescapewarp MAP_BELLCHIME_TRAIL_HNS, 35, 42
	end

TinTower_1F_EventScript_SageA::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageA_Hooh
	msgbox TinTower_1F_Sage4_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageA_Hooh::
	msgbox TinTower_1F_Sage4_Text1, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageB_Hooh
	msgbox TinTower_1F_Sage2_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageB_Hooh::
	msgbox TinTower_1F_Sage1_Text, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC::
	lock
	faceplayer
	goto_if_eq VAR_ECRUTEAK_CITY_STATE, 11, TinTower_1F_EventScript_SageC_Hooh
	msgbox TinTower_1F_Sage6_Text2, MSGBOX_DEFAULT
	closemessage
	release
	end

TinTower_1F_EventScript_SageC_Hooh::
	msgbox TinTower_1F_Sage3_Text, MSGBOX_DEFAULT
	closemessage
	release
	end


TinTower_1F_Sage1_Text:
	.string "Según la leyenda…\n"
	.string "Cuando las almas de POKéMON y humanos\p"
	.string "se comunican, desciende del cielo un\n"
	.string "POKéMON de colores arcoíris…\p"
	.string "¿Significa que los POKéMON legendarios\n"
	.string "nos están poniendo a prueba?$"

TinTower_1F_Sage2_Text:
	.string "Cuando la TORRE LATÓN se quemó,\n"
	.string "dicen que tres POKéMON sin nombre\l"
	.string "perecieron. Fue trágico.\p"
	.string "Sin embargo…\p"
	.string "Un POKéMON de colores arcoíris…\n"
	.string "En otras palabras...\p"
	.string "HO-OH descendió del cielo y\n"
	.string "dio nueva vida a los tres POKéMON.\p"
	.string "Ellos son...\n"
	.string "SUICUNE, ENTEI y RAIKOU.\p"
	.string "Eso es lo que dicen.$"

TinTower_1F_Sage3_Text:
	.string "Dicen que las dos TORRES fueron\n"
	.string "construidas para fomentar la unión\p"
	.string "y esperanza entre POKéMON y gente.\n"
	.string "Fue hace 700 años, pero ese ideal\p"
	.string "sigue siendo importante hoy.$"

TinTower_1F_Sage4_Text1:
	.string "¡Parece que HO-OH ha descendido\n"
	.string "sobre esta, la TORRE CAMPANA!$"

TinTower_1F_Sage4_Text2:
	.string "Dicen que los POKéMON legendarios\n"
	.string "encarnan tres poderes...\p"
	.string "El rayo que golpeó la TORRE.\n"
	.string "El fuego que quemó la TORRE.\p"
	.string "Y la lluvia que apagó el fuego…$"

TinTower_1F_Sage6_Text2:
	.string "Del POKéMON legendario SUICUNE,\n"
	.string "dicen que es el más cercano a HO-OH.\p"
	.string "Dicen que también hay un vínculo con\n"
	.string "con el POKéMON llamado UNOWN.\p"
	.string "El POKéMON UNOWN debe compartir un\n"
	.string "vínculo cooperativo con SUICUNE.$"

TinTower_1F_EusineHoOh_Text:
	.string "Lo sabía.\p"
	.string "Sabía que verías al POKéMON\n"
	.string "of rainbow colors, <PLAYER>.\p"
	.string "Pasó justo como lo imaginé.\n"
	.string "Mi investigación no es mala, diría.\p"
	.string "Seguiré estudiando a los POKéMON\n"
	.string "¡para ser un POKéMANÍACO famoso!$"

TinTower_1F_EusineSuicune_Text:
	.string "EUSINE: ¡Genial! ¡Demasiado genial!\n"
	.string "Nunca vi una batalla tan increíble.\p"
	.string "Fue realmente inspirador verlo.\n"
	.string "SUICUNE fue duro, pero tú fuiste\p"
	.string "more incredible, <PLAYER>.\n"
	.string "Oí que el poder místico de SUICUNE\p"
	.string "atrae a un POKéMON color arcoíris.\n"
	.string "Tal vez, solo tal vez, lo de hoy\p"
	.string "hará que aparezca ese POKéMON.\n"
	.string "Estudiaré más las leyendas.\p"
	.string "Gracias por mostrarme esa batalla\n"
	.string "fantástica.\p"
	.string "Later, <PLAYER>!$"
