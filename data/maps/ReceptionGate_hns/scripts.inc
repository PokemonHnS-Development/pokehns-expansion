ReceptionGate_hns_MapScripts::
	.byte 0

ReceptionGate_EventScript_Janine::
    lock
    faceplayer
    msgbox ReceptionGate_Text_Janine, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_ROUTE22_JANINE
    removeobject LOCALID_INDIGOJUNCTION_JANINE
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_JANINE
    release
    end

ReceptionGate_Text_Janine:
    .string "ג'אנין: אני בדרך לבית של אבא שלי\n"
    .string "כדי להביא לו ארוחת צהריים.\p"
    .string "לרביעייה העילית אין מנוחה יום ולילה.\n"
    .string "זו עבודה כל כך קשה, אתה יודע?\p"
    .string "אם אתה מוכן לעוד קרב,\n"
    .string "אהיה בדוג'ו אחר כך.$"


ReceptionGate_EventScript_Officer::
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_NPC
    end

ReceptionGate_Trigger::
    lock
    playse SE_PIN
    applymovement LOCALID_INDIGOJUNCTION_POLICEMAN, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_INDIGOJUNCTION_POLICEMAN
    goto_if_lt VAR_ECRUTEAK_CITY_THEATER, 8, ReceptionGate_EventScript_Kimono
    msgbox VictoryRoadGate_Text_Officer, MSGBOX_DEFAULT
    goto_if_unset FLAG_BADGE08_GET, ReceptionGate_EventScript_NotEnough
    msgbox VictoryRoadGate_Text_EightBadges, MSGBOX_DEFAULT
    closemessage
    setvar VAR_ROUTE27_STATE, 2
    release
    end

ReceptionGate_EventScript_Kimono::
    msgbox VictoryRoadGate_Text_Kimono, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end 

ReceptionGate_EventScript_NotEnough::
    msgbox VictoryRoadGate_Text_NotEnoughBadges, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
    waitmovement 0
    release
    end

ReceptionGate_EventScript_SilverGuard::
    msgbox VictoryRoadGate_Text_LeftBlackBelt, MSGBOX_NPC
    end
ReceptionGate_EventScript_KantoGuard::
    msgbox VictoryRoadGate_Text_RightBlackBelt, MSGBOX_NPC
    end

VictoryRoadGate_Text_Officer:
    .string "רק מאמנים שהוכיחו את עצמם\n"
    .string "רשאים לעבור.$"

VictoryRoadGate_Text_Kimono:
    .string "מצטער, ילד, הדרך הזאת סגורה עד\n"
    .string "שמישהו יטפל בפוקימון האגדי ההוא…$"

VictoryRoadGate_Text_NotEnoughBadges:
    .string "אין לך את כל תגי המכון של ג'וטו.\p"
    .string "אני מצטער, אבל אני לא יכול\n"
    .string "לתת לך לעבור.$"

VictoryRoadGate_Text_EightBadges:
    .string "אה! שמונת התגים של ג'וטו!\p"
    .string "בבקשה, אתה מוזמן לעבור!$"

VictoryRoadGate_Text_LeftBlackBelt:
    .string "הדרך הזאת מובילה להר הכסף.\p"
    .string "תפגוש שם פוקימונים\n"
    .string "חזקים בצורה מפחידה.$"

VictoryRoadGate_Text_RightBlackBelt:
    .string "בדרך לליגת הפוקימון, הא?\p"
    .string "חברי הרביעייה העילית חזקים\n"
    .string "בצורה מפחידה, והם מחכים לך!$"
