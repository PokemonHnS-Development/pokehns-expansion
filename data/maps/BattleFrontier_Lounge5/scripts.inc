BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	chooseboxmon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "¡Jeje!\n"
	.string "¡Sé lo que piensan los POKéMON!\p"
	.string "¡Por favor!\n"
	.string "¿Puedo ver tus POKéMON?$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "¡Bu!\n"
	.string "¡Miedoso!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow::
	.string "Hmhm...\p"
	.string "¡Este dice que ama luchar!\n"
	.string "Luchará aunque tenga muchos\l"
	.string "¡golpes!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow::
	.string "Hmhm...\p"
	.string "¡Este dice que ama luchar!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow::
	.string "Hmhm...\p"
	.string "¡Este dice que ama luchar!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se volverá escurridizo!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow::
	.string "Hmhm...\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡Que contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow::
	.string "Hmhm...\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "Dice que le preocupa si tiene\l"
	.string "muchos rasguños o no!$"

BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow::
	.string "Hmhm...\p"
	.string "¡Este dice que se cuida solo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se volverá escurridizo!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow::
	.string "Hmhm...\p"
	.string "¡Este dice que le gusta ser furtivo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡Que contraatacará!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow::
	.string "Hmhm...\p"
	.string "¡Este dice que le gusta ser furtivo!\n"
	.string "Pero si recibe demasiados,\l"
	.string "¡se preocupará por sí mismo!$"

BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow::
	.string "Hmhm...\p"
	.string "¡Este dice que le gusta ser furtivo!\n"
	.string "Dice que le gusta ser furtivo aun\l"
	.string "si tiene muchos rasguños!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "¡Qué tonto! ¡Un HUEVO duerme!\n"
	.string "¡No puedo hablar con él!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "¡Qué encantador!\n"
	.string "Esa damita dice que puede\l"
	.string "entender a los POKéMON!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "Tengo la sensación de que la niña\n"
	.string "está diciendo algo profundo.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "¡Yo sé algo!\p"
	.string "¡Esa niña juega mucho en la casa\n"
	.string "roja!$"

