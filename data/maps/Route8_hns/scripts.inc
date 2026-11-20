Route8_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route8_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route8_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route8_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE_HNS, Route8_Text_BikerDwayneSeen, Route8_Text_BikerDwayneBeaten
	msgbox Route8_Text_BikerDwayneAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Harris::
	trainerbattle_single TRAINER_HARRIS_HNS, Route8_Text_BikerHarrisSeen, Route8_Text_BikerHarrisBeaten
	msgbox Route8_Text_BikerHarrisAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Zeke::
	trainerbattle_single TRAINER_ZEKE_HNS, Route8_Text_BikerZekeSeen, Route8_Text_BikerZekeBeaten
	msgbox Route8_Text_BikerZekeAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Sam::
	trainerbattle_single TRAINER_SAM_HNS, Route8_Text_SupernerdSamSeen, Route8_Text_SupernerdSamBeaten
	msgbox Route8_Text_SupernerdSamAfter, MSGBOX_AUTOCLOSE
	end

Route8_EventScript_Tom::
	trainerbattle_single TRAINER_TOM_HNS, Route8_Text_SupernerdTomSeen, Route8_Text_SupernerdTomBeaten
	msgbox Route8_Text_SupernerdTomAfter, MSGBOX_AUTOCLOSE
	end

Route8_Text_BikerDwayneSeen:
	.string "אנחנו חבורת המאמנים\n"
	.string "”פדרציית הפוקימונים של קאנטו”.\p"
	.string "נדרוס אותך מתחת לגלגלים שלנו!$"

Route8_Text_BikerDwayneBeaten:
	.string "ס-סליחה!$"

Route8_Text_BikerDwayneAfter:
	.string "פדרציית הפוקימונים של קאנטו\n"
	.string "לעולם לא תיפול!$"

Route8_Text_BikerHarrisSeen:
	.string "השוטרים סגרו לנו את\n"
	.string "המעבר התת-קרקעי!\p"
	.string "זה ממש מרתיח אותי!$"

Route8_Text_BikerHarrisBeaten:
	.string "ת-תסלח לי!$"

Route8_Text_BikerHarrisAfter:
	.string "חוסלתי בידי איזה פרחח\n"
	.string "מג'וטו…$"

Route8_Text_BikerZekeSeen:
	.string "אנחנו פדרציית הפוקימונים\n"
	.string "של קאנטו! בדיוק ככה!$"

Route8_Text_BikerZekeBeaten:
	.string "אוי ואבוי! סליחה!$"

Route8_Text_BikerZekeAfter:
	.string "מעכשיו ננסה לא להפריע\n"
	.string "לאף אחד…$"

Route8_Text_SupernerdSamSeen:
	.string "איך הרכבת המגנטית עובדת?$"

Route8_Text_SupernerdSamBeaten:
	.string "אני רק רוצה לראות את\n"
	.string "הרכבת המגנטית…$"

Route8_Text_SupernerdSamAfter:
	.string "הכוח של מגנטים פשוט מדהים!$"

Route8_Text_SupernerdTomSeen:
	.string "הממ… יש לך הרבה תגי מכון.$"

Route8_Text_SupernerdTomBeaten:
	.string "בדיוק כמו שחשבתי… אתה קשוח!$"

Route8_Text_SupernerdTomAfter:
	.string "תגי מכון נותנים לך יתרונות\n"
	.string "בקרבות.$"

Route8_Text_LockedDoor:
	.string "It's locked…$"

Route8_Text_UndergroundPathSign:
	.string "The flyer's torn.\p"
	.string "It's impossible to read…$"
