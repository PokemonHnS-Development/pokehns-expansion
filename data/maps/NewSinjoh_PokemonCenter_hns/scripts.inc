NewSinjoh_PokemonCenter_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_PokemonCenter_OnTransition
    .byte 0

NewSinjoh_PokemonCenter_OnTransition: 
    setrespawn HEAL_LOCATION_NEW_SINJOH_HNS
    end

NewSinjoh_EventScript_Artist::
	lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT, NewSinjoh_EventScript_ZoomLens_Gotten
	msgbox NewSinjoh_Text_Artist, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_EventScript_ZoomLens_No
	msgbox Text_ItemGiveaway, MSGBOX_DEFAULT
	giveitem ITEM_ZOOM_LENS
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_NEWSINJOH_POKEMONCENTER_ARTIST_GIFT
	release
	end

NewSinjoh_PokemonCenter_EventScript_Skiier::
	lock
	faceplayer
	msgbox NewSinjoh_PokemonCenter_Text_Skiier, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_NEWSINJOH_POKEMONCENTER_SKIIER, DIR_NORTH
	release
	end

NewSinjoh_PokemonCenter_hns_Map::
	lockall
	setvar VAR_0x8000, 1 @ SCREENSHOT_SINJOH_MAP
	msgbox NewSinjoh_PokemonCenter_hns_Text_0, MSGBOX_DEFAULT
	closemessage
	callnative OpenScreenshotsFromScript
	waitstate
	releaseall
	end

NewSinjoh_PokemonCenter_Text_Skiier:
	.string "בגלל השלג קשה למצוא\n"
	.string "כאן את הדרך.\p"
	.string "הכול נראה אותו דבר.\p"
	.string "אז המפה הזאת עוזרת מאוד!\p"
	.string "איזה אזור יפה!$"

NewSinjoh_Text_Artist:
	.string "מצאתי השראה גדולה\n"
	.string "בעיירה הנסתרת הזאת!\p"
	.string "אתה לא חושב שהנוף\n"
	.string "עוצר נשימה?$"

Text_ItemGiveaway:
	.string "אני מבין!\n"
	.string "אתה בטח אמן בעצמך!\p"
	.string "במקרה יש לי משהו נוסף שיעזור לך\n"
	.string "לשים לב לפרטים הקטנים של החיים!$"

NewSinjoh_Text_Artist_No:
    .string "אתה לא מאלה ששונאים תיירים, נכון?\n"
    .string "את היופי צריך לחלוק עם אחרים.$"

NewSinjoh_EventScript_ZoomLens_No::
	msgbox NewSinjoh_Text_Artist_No, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_ZoomLens_Gotten::
	msgbox Text_WasGiven_ZoomLensAlready, MSGBOX_DEFAULT
	release
	end

Text_WasGiven_ZoomLensAlready:
	.string "מקווה שתיהנה מהעדשה!$"

NewSinjoh_EventScript_FemAce::
	msgbox NewSinjoh_Text_FemAce, MSGBOX_NPC
	end

NewSinjoh_Text_FemAce:
	.string "אין לנו הרבה נוחויות\n"
	.string "מודרניות בסינג'ו החדשה.\p"
	.string "אבל לפחות יש לנו את\n"
	.string "מרכז הפוקימון הזה.$"


NewSinjoh_PokemonCenter_hns_Text_0:
	.string "{PLAYER} התבונן מקרוב\n"
	.string "במפת סינג'ו.$"
