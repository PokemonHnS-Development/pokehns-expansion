DarkCave_NorthSide_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DarkCave_NorthSide_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

DarkCave_NorthSide_OnTransition: 
	callnative SetTimeBasedEncounters
	end

DarkCave2_EventScript_Item_BlackFlute::
	finditem ITEM_BLACK_FLUTE
	end

DarkCave2_EventScript_Item_StarPiece::
	finditem ITEM_STAR_PIECE
	end

DarkCave2_EventScript_BlackGlasses::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BLACK_GLASSES, DarkCave2_EventScript_BlackGlassesGot
	msgbox DarkCave2_Text_Nerd, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_GLASSES
	setflag FLAG_GOT_BLACK_GLASSES
	closemessage
	release
	end

DarkCave2_EventScript_BlackGlassesGot::
	msgbox DarkCave2_Text_Nerd2, MSGBOX_DEFAULT
	closemessage
	release
	end

DarkCave2_Text_Nerd:
    .string "וואו! הבהלת אותי!\p"
    .string "הרכבתי את המשקף השחור שלי,\n"
    .string "אז בכלל לא שמתי לב אליך.\p"
    .string "מה אני עושה כאן?\p"
    .string "היי, אל תדאג בקשר לזה.\p"
    .string "אני אתן לך משקף שחור,\n"
    .string "ואתה תשכח שראית אותי, טוב?$"

DarkCave2_Text_Nerd2:
    .string "משקף שחור מגביר את הכוח\n"
    .string "של מהלכים מסוג אפל.$"
