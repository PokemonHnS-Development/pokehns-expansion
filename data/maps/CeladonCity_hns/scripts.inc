CeladonCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_EventScript_CityEnter
	.byte 0

CeladonCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CELADON_CITY
	end

CeladonCity_EventScript_Erika::
    lock
    faceplayer
    msgbox CeladonCity_Text_Erika, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_FOUNTAIN_ERIKA
    removeobject LOCALID_CELADON_ERIKA
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_ERIKA
    release
    end

CeladonCity_Text_Erika:
    .string "אה, {PLAYER}.\n"
    .string "המזרקה יפהפייה היום, נכון?\p"
    .string "אם תרצה עוד קרב,\n"
    .string "אהיה בדוג'ו הלחימה.$"

CeladonCity_EventScript_Fatman::
	msgbox CeladonCity_Text_Fisher, MSGBOX_NPC
	end
CeladonCity_EventScript_Poliwrath::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWRATH, CRY_MODE_NORMAL
	msgbox CeladonCity_Text_Poliwrath, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeladonCity_EventScript_Teacher1::
	msgbox CeladonCity_Text_Teacher1, MSGBOX_NPC
	end

CeladonCity_EventScript_GrimerGramps::
	msgbox CeladonCity_Text_Gramps1, MSGBOX_NPC
	end

CeladonCity_EventScript_CreepGramps::
	msgbox CeladonCity_Text_Gramps2, MSGBOX_NPC
	end

CeladonCity_EventScript_Youngster::
	msgbox CeladonCity_Text_Youngster1, MSGBOX_NPC
	end

CeladonCity_EventScript_Youngster2::
	msgbox CeladonCity_Text_Youngster2, MSGBOX_NPC
	end

CeladonCity_EventScript_Teacher2::
	msgbox CeladonCity_Text_Teacher2, MSGBOX_NPC
	end

CeladonCity_EventScript_Lass::
	msgbox CeladonCity_Text_Lass, MSGBOX_NPC
	end

CeladonCity_EventScript_Item_Recycle::
    finditem ITEM_TM_RECYCLE
    end

CeladonCity_Text_Fisher:
	.string "הפוליראת' הזה הוא השותף שלי.\p"
	.string "מעניין אם הוא יתפתח אי פעם\n"
	.string "לפוקימון צפרדע.$"

CeladonCity_Text_Poliwrath:
	.string "פוליראת': קווה קווה!$"

CeladonCity_Text_Teacher1:
	.string "שוב הפסדתי במכונות המזל…\p"
	.string "גם אנחנו הבנות משחקות עכשיו\n"
	.string "במכונות המזל.\p"
	.string "כדאי גם לך לנסות אותן.$"

CeladonCity_Text_Gramps1:
	.string "לאחרונה מופיעים כאן\n"
	.string "פוקימוני גריימר.\p"
	.string "רואה את הבריכה שמול הבית?\n"
	.string "עכשיו גרים בה גריימר.\p"
	.string "מאיפה הם הגיעו? זו בעיה\n"
	.string "רצינית…$"

CeladonCity_Text_Gramps2:
	.string "ניחיחי! המכון הזה נהדר!\n"
	.string "רק בנות מורשות להיכנס לכאן!$"

CeladonCity_Text_Youngster1:
	.string "רוצה לשמוע סוד?\p"
	.string "לאחוזת סלדון יש דלת\n"
	.string "אחורית נסתרת.$"

CeladonCity_Text_Youngster2:
	.string "במסעדה עורכים תחרות אכילה.\p"
	.string "רק לראות אותם זוללים ככה\n"
	.string "גורם לי להרגיש נפוח…$"

CeladonCity_Text_Teacher2:
	.string "בכלבו של סלדון יש את מבחר\n"
	.string "המוצרים הגדול והטוב ביותר.\p"
	.string "מה שאי אפשר להשיג שם,\n"
	.string "אי אפשר להשיג בשום מקום.\p"
	.string "אוי… אני נשמעת כמו מוכרת.$"

CeladonCity_Text_Lass:
	.string "הסתכלתי על הקרקע בזמן שהלכתי,\n"
	.string "וקיבלתי סחרחורת.$"

CeladonCity_EventScript_CitySign::
	msgbox CeladonCity_Text_Sign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GymSign::
	msgbox CeladonGym_Text_Sign, MSGBOX_SIGN
	end

CeladonCity_EventScript_StoreSign::
	msgbox CeladonCity_Text_DeptStoreSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_MansionSign::
	msgbox CeladonCity_Text_MansionSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_GameCornerSign::
	msgbox CeladonCity_Text_GameCornerSign, MSGBOX_SIGN
	end

CeladonCity_EventScript_TrainerTips::
	msgbox CeladonCity_Text_TrainerTips, MSGBOX_SIGN
	end

CeladonCity_Text_Sign:
	.string "העיר סלדון\p"
	.string "העיר שבה חולמים בצבעי הקשת$"

CeladonGym_Text_Sign:
	.string "מכון הפוקימון של העיר סלדון\n"
	.string "מנהיגה: אריקה\p"
	.string "הנסיכה אוהבת הטבע$"

CeladonCity_Text_DeptStoreSign:
	.string "תמצאו את מה שאתם צריכים\n"
	.string "בכלבו של סלדון!$"

CeladonCity_Text_MansionSign:
	.string "אחוזת סלדון$"

CeladonCity_Text_GameCornerSign:
	.string "מגרש המשחקים של כולם -\n"
	.string "המשחקייה של סלדון$"

CeladonCity_Text_TrainerTips:
	.string "טיפים למאמנים\p"
	.string "הגנה מיוחדת מגינה על פוקימונים מפני\n"
	.string "התקפות מיוחדות כמו להביור וגלישה.\p"
	.string "קנו את הפריטים שלכם\n"
	.string "בכלבו של סלדון!$"
