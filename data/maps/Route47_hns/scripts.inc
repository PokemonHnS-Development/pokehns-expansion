Route47_hns_MapScripts::
	.byte 0


Route47_EventScript_Hiker::
	trainerbattle_single TRAINER_DEVIN_HNS, Route47_Text_HikerSeen, Route47_Text_HikerBeaten
	msgbox Route47_Text_HikerAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_HikerSeen::
	.string "געגועים לאחרים הם…\n"
	.string "מה שהם.\p"
	.string "אבל קרב זה קרב,\n"
	.string "אז קדימה!$"

Route47_Text_HikerBeaten::
	.string "וואהאהא!$"

Route47_Text_HikerAfter::
	.string "אחרי קרב תמיד כדאי להיפרד\n"
	.string "עם צחוק גדול!$"

Route47_EventScript_Camper::
	trainerbattle_single TRAINER_GRANT_HNS, Route47_Text_CamperSeen, Route47_Text_CamperBeaten
	msgbox Route47_Text_CamperAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_CamperSeen::
	.string "אני לא מסתדר עם קהל גדול, אז\n"
	.string "אני חונה פה עם הפוקימונים שלי!$"

Route47_Text_CamperBeaten::
	.string "כנראה שכדאי לי להמשיך\n"
	.string "עמוק יותר לתוך ההר…$"

Route47_Text_CamperAfter::
	.string "נתראה!$"

Route47_EventScript_Thom::
	trainerbattle_double TRAINER_THOM_AND_KAE_HNS, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Kae::
	trainerbattle_double TRAINER_THOM_AND_KAE_HNS, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple1Seen::
	.string "תום: אחד ועוד אחד זה שניים. אבל\n"
	.string "שנינו ביחד חזקים הרבה יותר!\p"
	.string "קיי: אנחנו לא סתם\n"
	.string "זוג משעמם!$"

Route47_Text_Couple1Beaten::
	.string "תום: לא לזה ציפיתי.\l"
	.string "קיי: גם אתה יוצא דופן!$"

Route47_Text_Couple1After1::
	.string "תום: נראה שהכוח שלך\n"
	.string "בלתי צפוי לחלוטין!$"

Route47_Text_Couple1After2::
	.string "קיי: חשבתי שאתה סתם מאמן\n"
	.string "בודד. כמה שטעיתי!$"

Route47_EventScript_Duff::
	trainerbattle_double TRAINER_DUFF_AND_EDA_HNS, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple2After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Eda::
	trainerbattle_double TRAINER_DUFF_AND_EDA_HNS, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox Route47_Text_Couple2After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple2Seen::
	.string "דאף: כשאני שומר על החברה שלי,\n"
	.string "הלב שלי ממריא!\p"
	.string "אדה: הרגשות שלי כלפי החבר שלי\n"
	.string "רחבים ועמוקים כמו האוקיינוס!$"

Route47_Text_Couple2Beaten::
	.string "דאף: לא הייתי ברמה שלך…\l"
	.string "אדה: אתה באמת משהו…$"

Route47_Text_Couple2After1::
	.string "דאף: תודה על הקרב עוצר הנשימה!\n"
	.string "ביי!$"

Route47_Text_Couple2After2::
	.string "אדה: באמת כדאי שגם לך יהיה\n"
	.string "מישהו נפלא לצידך!$"

Route47_EventScript_Sage::
	lock
	faceplayer
	msgbox EmbeddedTower_Text_OldManIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

EmbeddedTower_Text_OldManIntro:
	.string "ובכן, שלום!\p"
	.string "אומרים שמעבר לחור הזה עמד פעם\n"
	.string "מגדל ענק שהתנשא הרחק אל השמיים.\p"
	.string "אומרים שזה היה מגדל די מוזר,\n"
	.string "שחציו היה שקוע בתוך הצוק.\p"
	.string "הוא לא רק התנשא גבוה אל השמיים,\n"
	.string "אלא גם העמיק הרחק מתחת לאדמה!\p"
	.string "יש שמועות שהוא הגיע אפילו\n"
	.string "עד קרקעית האוקיינוס!\p"
	.string "בקיצור, החורבות חיברו פעם\n"
	.string "בין השמיים, היבשה והים…\p"
	.string "רוב המגדל כבר התמוטט, ונשארו ממנו\n"
	.string "רק הכניסה והחלל שבפנים,\p"
	.string "ושם אפשר לראות דפוסים מוזרים.$"

Route47_EventScript_Item_Pearl::
    finditem ITEM_PEARL
    end

Route47_EventScript_Item_Revive::
    finditem ITEM_REVIVE
    end

Route47_EventScript_Item_WhiteFlute::
    finditem ITEM_WHITE_FLUTE
    end

Route47_EventScript_Item_Stardust::
	finditem ITEM_STARDUST
	end

Route47_EventScript_Item_LuckyPunch::
	finditem ITEM_LUCKY_PUNCH
	end

Route47_EventScript_Chinchou::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	msgbox Route47_Text_Chinchou, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route47_Text_Chinchou:
	.string "צ'ינצ'ו: צ'ו!$"
