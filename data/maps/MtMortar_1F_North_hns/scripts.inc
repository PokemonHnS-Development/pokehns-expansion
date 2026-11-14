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
	.string "הפעם אני לא מפסיד!$"

MountMortar2_Text_PokemaniacMillerBeaten:
	.string "הפסדתי לאיזה ילד…?$"

MountMortar2_Text_PokemaniacMillerAfter:
	.string "לפני זמן מה, איזה קראטיסט אחד\n"
	.string "רצה להילחם.\p"
	.string "הוא היה טוב בטירוף.\n"
	.string "הוא פשוט ריסק אותנו.\p"
	.string "הוא נכנס פנימה עמוק יותר ואמר\n"
	.string "שזה בשביל האימונים שלו.\p"
	.string "מעניין מה שלומו?$"

MountMortar2_Text_SupernerdMarkusSeen:
	.string "היי! יו!$"

MountMortar2_Text_SupernerdMarkusBeaten:
	.string "חשבתי שאתה מישהו אחר…$"

MountMortar2_Text_SupernerdMarkusAfter:
	.string "באתי לחקור את הר המכתש, אבל\n"
	.string "איבדתי את השותף שלי…\p"
	.string "פגשת מאמן שמשתמש בסידרה\n"
	.string "שיודע את המהלך מפל מים?$"
