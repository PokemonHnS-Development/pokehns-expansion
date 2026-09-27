NewSinjoh_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_On_Transition
	.byte 0

NewSinjoh_On_Transition:
    setflag FLAG_VISITED_NEW_SINJOH
	end

NewSinjoh_EventScript_TriggerNorthGate::
	lock
	msgbox NewSinjoh_Text_TriggerNorthGate, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0
	release
	end

NewSinjoh_Text_TriggerNorthGate:
	.string "Mejor no hacer esperar a las\n"
	.string "chicas KIMONO.$"

NewSinjoh_EventScript_PetStantler::
    lock
	faceplayer
	playmoncry SPECIES_STANTLER, 0
	msgbox NewSinjoh_Text_Stantler_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_Text_Stantler_Cry:
    .string "¡Lerrrrr!$"

NewSinjoh_EventScript_Steven::
	msgbox NewSinjoh_Text_Steven, MSGBOX_AUTOCLOSE
	end

NewSinjoh_Text_Steven:
	.string "STEVEN: Señora, ¿la acompaño\n"
	.string "hasta el manantial de allá?\p"
	.string "Parece que hay espacio de sobra.$"

NewSinjoh_MilkMan_EventScript_Seller::
	lock
	faceplayer
	checkitem ITEM_MOOMOO_MILK, 99
	goto_if_eq VAR_RESULT, 1, MilkMan_EventScript_Battle
	showmoneybox 0, 0
	msgbox NewSinjoh_MilkMan_text_BuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk
	msgbox NewSinjoh_MilkMan_NoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_EventScript_MilkMan_BuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_MilkMan_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_MilkMan_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox NewSinjoh_MilkMan_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk

	msgbox NewSinjoh_MilkMan_GotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox NewSinjoh_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSinjoh_MilkMan_BagFull::
	msgbox NewSinjoh_MilkMan_NoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_MilkMan_NotEnough::
	msgbox NewSinjoh_MilkMan_NoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

NewSinjoh_MilkMan_text_BuyMilk:
	.string "Soy el lechero.\p"
	.string "Mi leche es deliciosa.\p"
	.string "Si quiere un poco hoy, será...\n"
	.string "¥500.$"

NewSinjoh_MilkMan_GotMilk:
	.string "¡Aquí tiene!\n"
	.string "Tiene lo que el mundo desea.$"

NewSinjoh_MilkMan_NoMoney:
	.string "Lo siento.\n"
	.string "¡Consigue dinero y compra algo!$"

NewSinjoh_MilkMan_NoRoom:
	.string "Parece que tu BOLSA está llena.$"

NewSinjoh_MilkMan_NoSale:
	.string "¿No lo quieres?\n"
	.string "Tiene lo que el mundo merece.$"

NewSinjoh_MilkMan_Text_WouldYouLikeAnother:
	.string "¿Qué tal otra?$"

NewSinjoh_Text_GotMilk:
	.string "{PLAYER} obtuvo LECHE MOOMOO.$"

MilkMan_EventScript_Battle:: 
    msgbox MilkMan_Battle_text
    Trainerbattle_no_intro TRAINER_MILKMAN_HNS, NewSinjoh_MilkMan_text_Lose
    release
    end

MilkMan_Battle_text:
	.string "Soy el Repartidor de Leche,\p"
	.string "Mi leche es deliciosa.\p"
	.string "¡entrega especial hoy!$"

NewSinjoh_MilkMan_text_Lose:
	.string "Este mundo es perfecto,\n"
	.string "¿no crees?$"

NewSinjoh_Script_TravelMart::
	lock
	faceplayer
	message NewSinjoh_Text_TravelShopGreeting
	waitmessage
	pokemart NewSinjoh_Pokemart_TravelShop
	msgbox NewSinjoh_Text_TravelShopEnd, MSGBOX_DEFAULT
	release
	end

	.align 2
NewSinjoh_Pokemart_TravelShop:
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_ELIXER
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_MAX_LURE
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NONE

NewSinjoh_Text_TravelShopGreeting:
	.string "Bienvenido a mi tiendita.\n"
	.string "¿En qué puedo ayudarte?$"

NewSinjoh_Text_TravelShopEnd:
	.string "Vuelve pronto.$"

Script_NewSinjoh_Traveler_Brother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_TravelBrother_Greeting
	release
	end

NewSinjoh_Text_TravelBrother_Greeting:
    .string "Todos nuestros productos son caseros\n"
	.string "¡y cultivados localmente!\p"
	.string "Mi hermana abrió esta tienda,\n"
	.string "porque la empresa POKéMART\l"
	.string "no abriría un local\l"
	.string "tan lejos de una ciudad grande.$"

NewSinjoh_EventScript_Josh::
	msgbox NewSinjoh_Text_Josh, MSGBOX_NPC
	end

NewSinjoh_Text_Josh:
	.string "¡Este lugar es genial!\p"
	.string "Ocultar estas aguas termales\n"
	.string "del mundo es una tragedia.\p"
	.string "¡Se lo diré a todos mis amigos!$"

NewSinjoh_EventScript_Janice::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_JaniceAfter
	msgbox NewSinjoh_Text_Janice, MSGBOX_NPC
	end
NewSinjoh_EventScript_JaniceAfter::
	msgbox NewSinjoh_Text_JaniceAfter, MSGBOX_NPC
	end

NewSinjoh_Text_Janice:
	.string "Estas aguas son mágicas,\n"
	.string "pero siento que la gente de aquí\l"
	.string "nos mira con mala cara.$"
NewSinjoh_Text_JaniceAfter:
	.string "Estas aguas son mágicas,\n"
	.string "¡y la gente de aquí es muy amable\l"
	.string "cuando los conoces!$"

NewSinjoh_EventScript_OldLady1::
	msgbox NewSinjoh_Text_OldLady1, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady1:
	.string "No hay nada como una linda vista\n"
	.string "para animar este viejo alma.$"

NewSinjoh_EventScript_OldLady2::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_OldLady2Steven
	msgbox NewSinjoh_Text_OldLady2, MSGBOX_NPC
	end
NewSinjoh_EventScript_OldLady2Steven::
	msgbox NewSinjoh_Text_OldLady2Steven, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady2:
	.string "Genial, ¡ahora estos turistas\n"
	.string "acaparan nuestras aguas termales!\p"
	.string "¡Últimamente ha sido una cosa\n"
	.string "mala tras otra!$"
NewSinjoh_Text_OldLady2Steven:
	.string "¡Qué joven tan apuesto!\p"
	.string "Tal vez estos turistas no son\n"
	.string "tan mal después de todo.$"

NewSinjoh_EventScript_OldLady3::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_OldLady3After
	msgbox NewSinjoh_Text_OldLady3, MSGBOX_NPC
	end
NewSinjoh_EventScript_OldLady3After::
	msgbox NewSinjoh_Text_OldLady3After, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady3:
	.string "¿Cómo puede esa mujer\n"
	.string "ser tan grosera con las visitas?\p"
	.string "Necesita darse un chapuzón\n"
	.string "en las aguas termales.\p"
	.string "Hay espacio suficiente\n"
	.string "para todo el mundo.$"
NewSinjoh_Text_OldLady3After:
	.string "Parece que todos se están\n"
	.string "acostumbrando unos a otros aquí.\p"
	.string "¡Qué bien!$"

NewSinjoh_EventScript_SpringsSage::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_SpringsSageAfter
	msgbox NewSinjoh_Text_SpringsSage, MSGBOX_NPC
	end
NewSinjoh_EventScript_SpringsSageAfter::
	msgbox NewSinjoh_Text_SpringsSageAfter, MSGBOX_NPC
	end

NewSinjoh_Text_SpringsSage:
	.string "Ha habido mucha división\n"
	.string "y conflictos en nuestra comunidad\l"
	.string "desde que llegaron los nuevos.\p"
	.string "Sin importar tu perspectiva,\n"
	.string "está claro que el equilibrio ha\l"
	.string "sido alterado.\p"
	.string "Sé amable con los locales y\n"
	.string "con los turistas por igual.$"
NewSinjoh_Text_SpringsSageAfter:
	.string "Todo ha mejorado desde que\n"
	.string "los POKéMON legendarios callaron.\p"
	.string "El equilibrio volvió a SINJOH.$"

NewSinjoh_EventScript_Sage2::
	msgbox NewSinjoh_Text_Sage2, MSGBOX_NPC
	end

NewSinjoh_Text_Sage2:
	.string "Los tiempos cambian, pero los\n"
	.string "STANTLER se siguen reuniendo.\l"
	.string "Podemos estar agradecidos.$"

NewSinjoh_EventScript_Daughter::
	msgbox NewSinjoh_Text_Daughter, MSGBOX_NPC
	end

NewSinjoh_Text_Daughter:
    .string "¡Yujuuuuuu!\p"
    .string "¡Mira, mami!\n"
    .string "¡Sin manos!\p"
	.string "¡Como los snowboarders!$"

NewSinjoh_EventScript_Mother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Mother, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWSINJOH_MOTHER, DIR_EAST
	release
	end

NewSinjoh_Text_Mother:
    .string "¡Mira qué lindo es mi bebé!\p"
    .string "Esta pista ha estado aquí\n"
	.string "por generaciones, pero los niños\l"
	.string "no la usaban hasta que llegaron\l"
	.string "los nuevos.$"

NewSinjoh_EventScript_Welcome_Sign::
	msgbox NewSinjoh_Text_Welcome_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Welcome_Sign:
	.string "NUEVO SINJOH$"

NewSinjoh_EventScript_Resturant_Sign::
	msgbox NewSinjoh_Text_Resturant_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Resturant_Sign:
	.string "CAFÉ FAMILIAR$"

NewSinjoh_EventScript_Cave_Sign::
	msgbox NewSinjoh_Text_Cave_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Cave_Sign:
	.string "CUEVA AGUAS TERMALES$"

NewSinjoh_EventScript_Hiker::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_HikerAfter
	msgbox NewSinjoh_Text_Hiker, MSGBOX_NPC
	end
NewSinjoh_EventScript_HikerAfter::
	msgbox NewSinjoh_Text_HikerAfter, MSGBOX_NPC
	end

NewSinjoh_Text_Hiker:
	.string "¡El negocio va viento en popa!\n"
	.string "Pero los precios subieron desde\l"
	.string "que la gente de la ciudad se\l"
	.string "interesó en nuestro pueblito.$"
NewSinjoh_Text_HikerAfter:
	.string "¡El negocio va viento en popa!\p"
	.string "¡Pero con las propinas del chico\n"
	.string "peliplata, los precios bajaron!$"

NewSinjoh_EventScript_OldLady4::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_EventScript_OldLady4After
	msgbox NewSinjoh_Text_OldLady4, MSGBOX_NPC
	end
NewSinjoh_EventScript_OldLady4After::
	msgbox NewSinjoh_Text_OldLady4After, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady4:
	.string "¡Solo vendo a los locales!$"
NewSinjoh_Text_OldLady4After:
	.string "¡Sigo vendiendo solo a locales!$"

NewSinjoh_EventScript_Item_DuskBall::
	finditem ITEM_DUSK_BALL
    end


