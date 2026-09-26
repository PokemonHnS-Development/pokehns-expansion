MtMortar_1F_North_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MtMortar_1F_North_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

MtMortar_1F_North_OnTransition: 
	callnative SetTimeBasedEncounters
	end

MtMortar_1F_North_EventScript_Item_MaxRepel::
    finditem ITEM_MAX_REPEL
    end

MtMortar_1F_North_EventScript_Item_EscapeRope::
    finditem ITEM_ESCAPE_ROPE
    end

MtMortar_1F_North_EventScript_Item_MaxPotion::
    finditem ITEM_MAX_POTION
    end

MtMortar_1F_North_EventScript_Item_Protector::
    finditem ITEM_PROTECTOR
    end

MtMortar_1F_North_EventScript_Item_UltraBall::
    finditem ITEM_ULTRA_BALL
    end

MtMortar_1F_North_EventScript_Item_FullIncense::
    finditem ITEM_REVIVE
    end

MtMortar_1F_North_EventScript_Item_KingsRock::
    finditem ITEM_KINGS_ROCK
    end

MtMortar_1F_North_EventScript_Miller::
	trainerbattle_single TRAINER_MILLER_HNS, MountMortar2_Text_PokemaniacMillerSeen, MountMortar2_Text_PokemaniacMillerBeaten
	msgbox MountMortar2_Text_PokemaniacMillerAfter, MSGBOX_AUTOCLOSE
	end

MtMortar_1F_North_EventScript_Markus::
	trainerbattle_single TRAINER_MARKUS_HNS, MountMortar2_Text_SupernerdMarkusSeen, MountMortar2_Text_SupernerdMarkusBeaten
	msgbox MountMortar2_Text_SupernerdMarkusAfter, MSGBOX_AUTOCLOSE
	end

MountMortar2_Text_PokemaniacMillerSeen:
	.string "¡Esta vez no pierdo!$"

MountMortar2_Text_PokemaniacMillerBeaten:
	.string "¿Perdí contra un niño...?$"

MountMortar2_Text_PokemaniacMillerAfter:
	.string "Hace tiempo, un tipo de karate\n"
	.string "quería luchar.\p"
	.string "Era ridículamente bueno.\n"
	.string "Nos dio una paliza total.\p"
	.string "Dijo que todo aquello era\n"
	.string "parte de su entrenamiento.\p"
	.string "¿Me pregunto cómo estará?$"

MountMortar2_Text_SupernerdMarkusSeen:
	.string "¡Oye! ¡HUGH!$"

MountMortar2_Text_SupernerdMarkusBeaten:
	.string "Te confundí con otra\n"
	.string "persona...$"

MountMortar2_Text_SupernerdMarkusAfter:
	.string "Vine a explorar el MT.MORTAR,\n"
	.string "pero me separé de mi\l"
	.string "compañero...\p"
	.string "¿Te cruzaste con un ENTRENADOR\n"
	.string "que use un SEADRA que sepa\l"
	.string "CASCADA?$"
