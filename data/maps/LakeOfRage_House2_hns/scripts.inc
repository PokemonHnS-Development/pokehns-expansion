LakeOfRage_House2_hns_MapScripts::
	.byte 0

LakeOfRage_House2_EventScript_Fisher::
	lock
	faceplayer
	goto_if_ge VAR_MAHOGANY_TOWN_STATE, 14, LakeOfRage_House2_EventScript_FisherAfterRockets
	goto_if_eq VAR_LAKE_OF_RAGE_FISHERMAN, 0, LakeOfRage_House2_EventScript_FisherFirstMeeting
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_DEFAULT
	closemessage
	release
	end	

LakeOfRage_House2_EventScript_FisherFirstMeeting::
	msgbox LakeOfRage_House2_Text_LakeHistory, MSGBOX_DEFAULT
	msgbox LakeOfRage_House2_Text_MenInBlack, MSGBOX_DEFAULT
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 1
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherAfterRockets::
	goto_if_eq VAR_LAKE_OF_RAGE_FISHERMAN, 2, LakeOfRage_House2_EventScript_FisherAnotherMagikarp
	msgbox LakeOfRage_House2_Text_WorldsLargest, MSGBOX_DEFAULT
	msgbox LakeOfRage_House2_Text_ForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNo
	getpartysize
	goto_if_eq VAR_RESULT, 1, LakeOfRage_House2_EventScript_LastMon
	special ChoosePartyMon
	waitstate
	lock
	showmoneybox 0, 0
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LakeOfRage_House2_EventScript_FisherNoMoneyBox
	removegenericmon SPECIES_MAGIKARP
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNotMagikarp
	goto_if_eq VAR_RESULT, MON_SATISFACTORY, LakeOfRage_House2_EventScript_FisherSatisfied
	goto_if_eq VAR_RESULT, MON_UNSATISFACTORY, LakeOfRage_House2_EventScript_FisherSmallMagikarp

LakeOfRage_House2_EventScript_FisherNo::
	msgbox LakeOfRage_House2_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherNoMoneyBox::
	msgbox LakeOfRage_House2_Text_Refused, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherNotMagikarp::
	msgbox LakeOfRage_House2_Text_NotMagikarp, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherSmallMagikarp::
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 2
	msgbox LakeOfRage_House2_Text_TooShort, MSGBOX_DEFAULT
	addmoney 2000
	updatemoneybox
	playse SE_SHOP
	waitse
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherAnotherMagikarp::
	msgbox LakeOfRage_House2_Text_ForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNo
	getpartysize
	goto_if_eq VAR_RESULT, 1, LakeOfRage_House2_EventScript_LastMon
	special ChoosePartyMon
	waitstate
	lock
	showmoneybox 0, 0
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, LakeOfRage_House2_EventScript_FisherNoMoneyBox
	removegenericmon SPECIES_MAGIKARP
	goto_if_eq VAR_RESULT, FALSE, LakeOfRage_House2_EventScript_FisherNotMagikarp
	goto_if_eq VAR_RESULT, MON_SATISFACTORY, LakeOfRage_House2_EventScript_FisherSatisfied
	goto_if_eq VAR_RESULT, MON_UNSATISFACTORY, LakeOfRage_House2_EventScript_FisherSmallMagikarp

LakeOfRage_House2_EventScript_LastMon::
	msgbox LakeOfRage_House2_Text_LastMon, MSGBOX_DEFAULT
	closemessage
	release
	end

LakeOfRage_House2_EventScript_FisherSatisfied::
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 2
	msgbox LakeOfRage_House2_Text_BigPayout, MSGBOX_DEFAULT
	addmoney 100000
	updatemoneybox
	playse SE_SHOP
	waitse
	hidemoneybox
	closemessage
	release
	end

LakeOfRage_House2_Text_LakeHistory:
    .string "אגם הזעם הוא בעצם מכתש\n"
    .string "שיצרו גרידוס משתוללים.\p"
    .string "המכתש התמלא במי גשם,\n"
    .string "וכך נוצר האגם.\p"
    .string "את הסיפור הזה סיפר\n"
    .string "סבא-רבא-רבא של סבא שלי.\p"
    .string "פעם אפשר היה לתפוס שם\n"
    .string "מג'יקארפ מלאי חיים, אבל…\p"
    .string "אני לא מבין מה קורה.$"

LakeOfRage_House2_Text_MenInBlack:
    .string "משהו לא בסדר באגם מאז שהגיעו\n"
    .string "האנשים האלה בבגדים השחורים.$"

LakeOfRage_House2_Text_LastMon:
    .string "נו, אל תיתן לי לקחת את הפוקימון\n"
    .string "האחרון שלך!$"

LakeOfRage_House2_Text_WorldsLargest:
    .string "אגם הזעם חזר לקדמותו.\p"
    .string "המג'יקארפ חזרו.\p"
    .string "אולי עוד אגשים את החלום שלי\n"
    .string "להחזיק את המג'יקארפ הגדול בעולם.\p"
    .string "בעצם… אשלם לך ¥2000 על כל\n"
    .string "מג'יקארפ שתביא לי.\p"
    .string "ועל מג'יקארפ ענק אשלם ¥100,000!$"

LakeOfRage_House2_Text_ForMe:
	.string "אז… יש לך מג'יקארפ\n"
	.string "בשבילי?$"

LakeOfRage_House2_Text_HaveMagikarp:
    .string "Ah, you have a MAGIKARP! Let's\n"
    .string "see how big that baby is.$"

LakeOfRage_House2_Text_BigPayout:
    .string "וואו! הוא פשוט יוצא מן הכלל!\p"
    .string "אני מוריד בפניך את הכובע!\p"
    .string "הנה משהו קטן\n"
    .string "על הטרחה.$"

LakeOfRage_House2_Text_Bonus:
    .string "The record is the important thing.\p"
    .string "Think of that as a bonus!$"

LakeOfRage_House2_Text_TooShort:
    .string "וואו! הוא פשוט יוצא מן הכלל!\p"
    .string "…הלוואי שיכולתי להגיד את זה, אבל\n"
    .string "כבר ראיתי אחד גדול יותר.\p"
    .string "אני מניח שהוא שווה משהו.$"

LakeOfRage_House2_Text_NotMagikarp:
    .string "מה? זה לא מג'יקארפ!$"

LakeOfRage_House2_Text_Refused:
    .string "אה… אז אין לך אחד ששווה\n"
    .string "להראות לי? אולי בפעם הבאה.$"
