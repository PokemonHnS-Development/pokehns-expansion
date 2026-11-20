SSAqua_B1F_hns_MapScripts::
	.byte 0

SSAqua_B1F_EventScript_Trigger::
	lock
	turnobject LOCALID_SSAQUA_B1F_SAILORLOOKING, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkDown1
	waitmovement 0 
	turnobject LOCALID_SSAQUA_B1F_SAILORLOOKING, DIR_SOUTH
	release
	end

SSAqua_B1F_EventScript_SailorLookingForBuddy::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SSAQUA_SAILOR, SSAqua_B1F_EventScript_SailorLookingFoundBuddy
	msgbox SSAqua_B1F_Text_FastShipOnDutySailor, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SailorLookingFoundBuddy::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorThanks, MSGBOX_DEFAULT
	goto_if_lt VAR_SSAQUA_STATE, 5, SSAqua_B1F_EventScript_SailorGirl
	closemessage
	release
	end
SSAqua_B1F_EventScript_SailorGirl::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorSawGirl, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_B1F_EventScript_SleepySailor::
	msgbox SSAqua_B1F_Text_FastShipOnDutySailorDirections, MSGBOX_NPC
	end

SSAqua_B1F_EventScript_Barfcan::
	msgbox SSAqua_B1F_Text_BarfCan, MSGBOX_SIGN
	end

SSAqua_B1F_Text_BarfCan:
    .string "איכס!\n"
    .string "עדיף היה לא להסתכל!$"

SSAqua_B1F_Text_FastShipOnDutySailor:
	.string "היי, ילד. אפשר לבקש ממך\n"
	.string "לחפש את החבר שלי?\p"
	.string "הוא מתבטל איפשהו,\n"
	.string "העצלן הזה!\p"
	.string "אני רוצה ללכת לחפש אותו, אבל\n"
	.string "אני במשמרת עכשיו.$"

SSAqua_B1F_Text_FastShipOnDutySailorRefused:
	.string "Oh, gee…\p"
	.string "The CAPTAIN will be furious…$"

SSAqua_B1F_Text_FastShipOnDutySailorThanks:
	.string "תודה, ילד! נזפתי בו כהוגן,\n"
	.string "אז הוא יפסיק להתבטל!$"

SSAqua_B1F_Text_FastShipOnDutySailorSawGirl:
	.string "ילדה קטנה?\p"
	.string "אולי ראיתי אותה עוברת כאן.$"

SSAqua_B1F_Text_FastShipOnDutySailorDirections:
	.string "חדר האוכל נמצא קדימה.\p"
	.string "המדרגות בסוף מובילות\n"
	.string "לתא של הקפטן.$"

SSAqua_B1F_EventScript_Jeff::
	trainerbattle_single TRAINER_JEFF_HNS, SSAqua_B1F_Text_SailorJeffSeen, SSAqua_B1F_Text_SailorJeffBeaten
	msgbox SSAqua_B1F_Text_SailorJeffAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorJeffSeen:
	.string "אין כמו קרב\n"
	.string "בזמן ההפסקה שלי.$"

SSAqua_B1F_Text_SailorJeffBeaten:
	.string "ניצחון או הפסד, ההפסקה נגמרה!$"

SSAqua_B1F_Text_SailorJeffAfter:
	.string "כנראה שלא אנצח\n"
	.string "אם לא אהיה רציני יותר.$"

SSAqua_B1F_EventScript_Debra::
	trainerbattle_single TRAINER_DEBRA_HNS, SSAqua_B1F_Text_PicnickerDebraSeen, SSAqua_B1F_Text_PicnickerDebraBeaten
	msgbox SSAqua_B1F_Text_PicnickerDebraAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_PicnickerDebraSeen:
	.string "משעמם לי נורא. רוצה להילחם?$"

SSAqua_B1F_Text_PicnickerDebraBeaten:
	.string "אאוץ'! אתה חזק מדי!$"

SSAqua_B1F_Text_PicnickerDebraAfter:
	.string "סאפרון, סלדון… שמעתי שיש\n"
	.string "הרבה ערים גדולות בקאנטו.$"

SSAqua_B1F_EventScript_Fritz::
	trainerbattle_single TRAINER_FRITZ_HNS, SSAqua_B1F_Text_JugglerFritzSeen, SSAqua_B1F_Text_JugglerFritzBeaten
	msgbox SSAqua_B1F_Text_JugglerFritzAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_JugglerFritzSeen:
	.string "אוווף… יש לי מחלת ים!$"

SSAqua_B1F_Text_JugglerFritzBeaten:
	.string "אני לא יכול לזוז יותר…$"

SSAqua_B1F_Text_JugglerFritzAfter:
	.string "די, לא עוד ספינות בשבילי.\p"
	.string "בפעם הבאה אני נוסע\n"
	.string "ברכבת המגנטית.$"

SSAqua_B1F_EventScript_Garrett::
	trainerbattle_single TRAINER_GARRETT_HNS, SSAqua_B1F_Text_SailorGarrettSeen, SSAqua_B1F_Text_SailorGarrettBeaten
	msgbox SSAqua_B1F_Text_SailorGarrettAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorGarrettSeen:
	.string "כאן אנחנו, המלחים, עובדים!$"

SSAqua_B1F_Text_SailorGarrettBeaten:
	.string "הפסדתי במגרש הביתי שלי…$"

SSAqua_B1F_Text_SailorGarrettAfter:
	.string "בהפלגה מהעיר ורמיליון לעיר\n"
	.string "אוליבין יש לנו נוסעים אחרים.$"

SSAqua_B1F_EventScript_Jonah::
	trainerbattle_single TRAINER_JONAH_HNS, SSAqua_B1F_Text_FisherJonahSeen, SSAqua_B1F_Text_FisherJonahBeaten
	msgbox SSAqua_B1F_Text_FisherJonahAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_FisherJonahSeen:
	.string "אנחנו באמצע הים, ובכל זאת\n"
	.string "אני לא יכול לדוג!\p"
	.string "משעמם! קדימה, לקרב!$"

SSAqua_B1F_Text_FisherJonahBeaten:
	.string "אני… כבר לא משועמם…$"

SSAqua_B1F_Text_FisherJonahAfter:
	.string "אני מתכנן לדוג\n"
	.string "מהמזח של ורמיליון.$"

SSAqua_B1F_EventScript_Wai::
	trainerbattle_single TRAINER_WAI_HNS, SSAqua_B1F_Text_BlackbeltWaiSeen, SSAqua_B1F_Text_BlackbeltWaiBeaten
	msgbox SSAqua_B1F_Text_BlackbeltWaiAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_BlackbeltWaiSeen:
	.string "אני מחזק את הרגליים שלי\n"
	.string "בעמידה מול טלטלות הספינה!$"

SSAqua_B1F_Text_BlackbeltWaiBeaten:
	.string "טולטלתי והופלתי!$"

SSAqua_B1F_Text_BlackbeltWaiAfter:
	.string "לא מצאתי את מלך הקראטה בג'וטו.\p"
	.string "הוא אמור להתאמן\n"
	.string "באיזושהי מערה.$"

SSAqua_B1F_EventScript_Kenneth::
	trainerbattle_single TRAINER_KENNETH_HNS, SSAqua_B1F_Text_SailorKennethSeen, SSAqua_B1F_Text_SailorKennethBeaten
	msgbox SSAqua_B1F_Text_SailorKennethAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SailorKennethSeen:
	.string "אני מלח!\p"
	.string "אבל אני מאמן פוקימונים כדי\n"
	.string "שאוכל להיות האלוף!$"

SSAqua_B1F_Text_SailorKennethBeaten:
	.string "רואים שחסר לי אימון…$"

SSAqua_B1F_Text_SailorKennethAfter:
	.string "שמונה תגים! הם בטח מוכיחים\n"
	.string "שניצחת מנהיגי מכונים.\p"
	.string "אין פלא שאתה כל כך טוב!$"

SSAqua_B1F_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY_HNS, SSAqua_B1F_Text_TeacherShirleySeen, SSAqua_B1F_Text_TeacherShirleyBeaten
	msgbox SSAqua_B1F_Text_TeacherShirleyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_TeacherShirleySeen:
	.string "אל תעז לגעת באצבע\n"
	.string "בתלמידים שלי!$"

SSAqua_B1F_Text_TeacherShirleyBeaten:
	.string "אאאק!$"

SSAqua_B1F_Text_TeacherShirleyAfter:
	.string "אנחנו בדרך לסיור לימודי\n"
	.string "בחורבות שליד ויולט.$"

SSAqua_B1F_EventScript_Nate::
	trainerbattle_single TRAINER_NATE_HNS, SSAqua_B1F_Text_SchoolboyNateSeen, SSAqua_B1F_Text_SchoolboyNateBeaten
	msgbox SSAqua_B1F_Text_SchoolboyNateAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyNateSeen:
	.string "אתה מכיר את חורבות אלף?$"

SSAqua_B1F_Text_SchoolboyNateBeaten:
	.string "יאאארג!$"

SSAqua_B1F_Text_SchoolboyNateAfter:
	.string "מכשירי רדיו קולטים אותות\n"
	.string "מוזרים בתוך החורבות.$"

SSAqua_B1F_EventScript_Ricky::
	trainerbattle_single TRAINER_RICKY_HNS, SSAqua_B1F_Text_SchoolboyRickySeen, SSAqua_B1F_Text_SchoolboyRickyBeaten
	msgbox SSAqua_B1F_Text_SchoolboyRickyAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_B1F_Text_SchoolboyRickySeen:
	.string "יש כמה לוחות אבן מוזרים\n"
	.string "בחורבות אלף.$"

SSAqua_B1F_Text_SchoolboyRickyBeaten:
	.string "גמרו אותי!$"

SSAqua_B1F_Text_SchoolboyRickyAfter:
	.string "קראתי שיש ארבעה\n"
	.string "לוחות אבן כאלה.$"

