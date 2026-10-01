BattleFrontier_Lounge5_hns_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl_hns::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting_hns, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirl_hnsNoneShown_hns
	chooseboxmon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirl_hnsNoneShown_hns
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge5_EventScript_NatureGirl_hnsEgg_hns
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirl_hnsEgg_hns::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirl_hnsNoneShown_hns::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman_hns::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt_hns::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy_hns::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting_hns::
	.string "¡Jeje!\n"
	.string "¡Sé lo que piensan los POKéMON!\p"
	.string "¡Por favor!\n"
	.string "¿Puedo ver tus POKéMON?$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown_hns::
	.string "¡Bu!\n"
	.string "¡Miedoso!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que ama luchar!\n"
	.string "Luchará aunque tenga muchos\l"
	.string "¡golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que ama luchar!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que ama luchar!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se volverá escurridizo!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡Que contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "Dice que le preocupa si tiene\l"
	.string "muchos rasguños o no!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se volverá escurridizo!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que le gusta ser furtivo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡Que contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que le gusta ser furtivo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow_hns::
	.string "Hmhm...\p"
	.string "¡Este dice que le gusta ser furtivo!\n"
	.string "Dice que le gusta ser furtivo aun\l"
	.string "si tiene muchos rasguños!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg_hns::
	.string "¡Qué tonto! ¡Un HUEVO duerme!\n"
	.string "¡No puedo hablar con él!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon_hns::
	.string "¡Qué encantador!\n"
	.string "Esa damita dice que puede\l"
	.string "entender a los POKéMON!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound_hns::
	.string "Tengo la sensación de que la niña\n"
	.string "está diciendo algo profundo.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot_hns::
	.string "¡Yo sé algo!\p"
	.string "¡Esa niña juega mucho en la casa\n"
	.string "roja!$"

