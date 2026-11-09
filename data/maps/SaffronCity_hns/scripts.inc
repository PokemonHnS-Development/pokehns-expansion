SaffronCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_EventScript_CityEnter
	.byte 0

SaffronCity_EventScript_CityEnter::
	setflag FLAG_VISITED_SAFFRON_CITY
	end

SaffronCity_Text_BaobaName:
	.string "באובה$"

SaffronCity_Text_Baoba:
	.string "WARDEN BAOBA: {PLAYER}!\p"
	.string "This is WARDEN BAOBA.\p"
	.string "I'm calling to tell you that the\n"
	.string "SAFARI ZONE has expanded again!\p"
	.string "Finally, my SAFARI ZONE has been\n"
	.string "fully realized!\p"
	.string "You remember where it is, right?\p"
	.string "Just west of CIANWOOD CITY!\n"
	.string "see you soon!$"

SaffronCity_EventScript_Lass1A::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_Lass1B
	msgbox SaffronCity_Text_Lass1, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass1B::
	msgbox SaffronCity_Text_Lass1_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_Lass2::
	msgbox SaffronCity_Text_Lass2, MSGBOX_NPC
	end

SaffronCity_EventScript_PokefanM::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_PokefanM2
	msgbox SaffronCity_Text_PokefanM, MSGBOX_NPC
	end

SaffronCity_EventScript_PokefanM2::
	msgbox SaffronCity_Text_PokefanM_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_CooltrainerM::
	msgbox SaffronCity_Text_CooltrainerM, MSGBOX_NPC
	end

SaffronCity_EventScript_CooltrainerF::
	msgbox SaffronCity_Text_CooltrainerF, MSGBOX_NPC
	end

SaffronCity_EventScript_Fisher::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_EventScript_Fisher2
	msgbox SaffronCity_Text_Fisher, MSGBOX_NPC
	end

SaffronCity_EventScript_Fisher2::
	msgbox SaffronCity_Text_Fisher_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster1::
	msgbox SaffronCity_Text_Youngster1, MSGBOX_NPC
	end

SaffronCity_EventScript_Youngster2::
	msgbox SaffronCity_Text_Youngster2, MSGBOX_NPC
	end
SaffronCity_EventScript_CitySign::
	msgbox SaffronCity_Text_Sign, MSGBOX_SIGN
	end

SaffronCity_EventScript_GymSign::
	msgbox SaffronCity_Text_GymSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_DojoSign::
	msgbox SaffronCity_Text_FightingDojoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_SilphCoSign::
	msgbox SaffronCity_Text_SilphCoSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MrPsychicSign::
	msgbox SaffronCity_Text_MrPsychicHouseSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_MagnetTrainSign::
	msgbox SaffronCity_Text_MagnetTrainStationSign, MSGBOX_SIGN
	end

SaffronCity_EventScript_Elli::
	msgbox SaffronCity_Text_Elli, MSGBOX_NPC
	end

SaffronCity_Text_Elli:
	.string "אני פשוט מתה על וולפיקס!!$"

SaffronCity_Text_Lass1:
	.string "כאן גרה ילדה קטנה שהיא\n"
	.string "מומחית בחיקוי אנשים.\p"
	.string "היא מחקה אפילו את מי שהיא\n"
	.string "מדברת איתו. זה מבלבל.$"

SaffronCity_Text_Lass1_ReturnedPart:
	.string "הילדה החקיינית נראתה עצובה.\p"
	.string "היא אמרה שאיבדה את בובת הפוקימון\n"
	.string "האהובה עליה, בובת הקלפרי.$"

SaffronCity_Text_PokefanM:
	.string "באת מג'וטו?\p"
	.string "אפשר לחזור הביתה בזריזות\n"
	.string "אם הרכבת המגנטית פועלת.$"

SaffronCity_Text_PokefanM_ReturnedPart:
	.string "באת מג'וטו?\p"
	.string "אפשר לחזור הביתה בזריזות\n"
	.string "אם קופצים על הרכבת המגנטית.$"

SaffronCity_Text_CooltrainerM:
	.string "הלכתי למכון, להוט לקרבות\n"
	.string "נגד מאמנים…\p"
	.string "מסתבר שנכנסתי בטעות\n"
	.string "למכון הנטוש שליד.\p"
	.string "אוי, ממש התביישתי.$"

SaffronCity_Text_CooltrainerF:
	.string "זו סילף בע”מ, המפורסמת\n"
	.string "במוצרי פוקימון.\p"
	.string "בעבר צוות רוקט רצה לשים יד\n"
	.string "על החברה בגלל זה.$"

SaffronCity_Text_Fisher:
	.string "לעיסה… לעיסה…\p"
	.string "שמעתי שמתבשלת צרה גדולה\n"
	.string "במפעל החשמל.\p"
	.string "לעיסה… לעיסה…$"

SaffronCity_Text_Fisher_ReturnedPart:
	.string "לעיסה… לעיסה…\p"
	.string "שמעתי שהייתה צרה גדולה\n"
	.string "במפעל החשמל.\p"
	.string "לעיסה… לעיסה… אההה, אני שבע!$"

SaffronCity_Text_Youngster1:
	.string "להיכנס לסמטה בפעם הראשונה\n"
	.string "קצת מלחיץ אותי.$"

SaffronCity_Text_Youngster2:
	.string "בעיר וירידיאן יש מקום שנקרא\n"
	.string "אולם התחרויות.\p"
	.string "מאמנים מכל מקום מתאספים בו.$"

SaffronCity_Text_Lass2:
	.string "העיר שלנו הופיעה בתוכנית רדיו.\p"
	.string "נחמד לשמוע שמשבחים את העיר\n"
	.string "שלך, אבל זה גם קצת מביך.$"

SaffronCity_Text_Sign:
	.string "העיר סאפרון\p"
	.string "ארץ המסחר הזהובה והנוצצת$"

SaffronCity_Text_GymSign:
	.string "מכון הפוקימון של העיר סאפרון\n"
	.string "מנהיגה: סברינה\p"
	.string "המומחית לפוקימונים מסוג על-חושי!$"

SaffronCity_Text_FightingDojoSign:
	.string "כולם מוזמנים!\n"
	.string "דוג'ו הלחימה$"

SaffronCity_Text_SilphCoSign:
	.string "סילף בע”מ\n"
	.string "בניין משרדים$"

SaffronCity_Text_MrPsychicHouseSign:
	.string "הבית של\n"
	.string "מר על-חושי$"

SaffronCity_Text_MagnetTrainStationSign:
	.string "העיר סאפרון\n"
	.string "תחנת הרכבת המגנטית$"
