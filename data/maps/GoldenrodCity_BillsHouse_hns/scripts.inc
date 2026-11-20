GoldenrodCity_BillsHouse_hns_MapScripts::
	.byte 0

GoldenrodCity_BillsHouse_EventScript_Sister::
	lock
	faceplayer
	msgbox BillHouse_Text_SisterStorageSystem, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom::
	lock
	faceplayer
	goto_if_set FLAG_SYS_PC_BILL, GoldenrodCity_BillsHouse_EventScript_Mom2
	msgbox BillHouse_Text_MomBeforeEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Mom2::
	msgbox BillHouse_Text_MomAfterEcruteak, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill::
	lock
	faceplayer
	goto_if_unset FLAG_GOT_EEVEE, GoldenrodCity_BillsHouse_EventScript_Bill_Eevee
	msgbox BillHouse_Text_PopWontWork, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BillsHouse_EventScript_Bill_Eevee::
	msgbox BillHouse_Text_TakeThisEevee, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_BillsHouse_EventScript_Bill_Refused
	msgbox BillHouse_Text_CountingOnYou, MSGBOX_DEFAULT

	@HnS named gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_EEVEE
	bufferspeciesname STR_VAR_1, SPECIES_EEVEE
	givenamedmon 3
	call Common_EventScript_GiftMonNamed

    

	setflag FLAG_GOT_EEVEE
	msgbox BillHouse_Text_EeveeMayEvolve, MSGBOX_DEFAULT
	closemessage
	release
	end


GoldenrodCity_BillsHouse_EventScript_Bill_Refused::
	msgbox BillHouse_Text_NoEevee, MSGBOX_DEFAULT
	closemessage
	release
	end

BillHouse_Text_TakeThisEevee:
    .string "ביל: היי, {PLAYER}! תעשה לנו טובה\n"
    .string "ותיקח את האיווי הזה.\p"
    .string "השאירו אותו אצלנו בזמן שלא\n"
    .string "הייתי כאן, כי עבדתי על המערכת שלי.\p"
    .string "מישהו צריך לטפל בו,\n"
    .string "אבל אני לא אוהב להיות בחוץ.\p"
    .string "אפשר לסמוך עליך שתשחק איתו,\n"
    .string "{PLAYER}?$"

BillHouse_Text_CountingOnYou:
    .string "ביל: ידעתי שלא תאכזב!\p"
    .string "כל הכבוד! אתה פשוט תותח!\p"
    .string "אוקיי, אני סומך עליך.\p"
    .string "תשמור עליו היטב!$"

BillHouse_Text_ReceivedEevee:
    .string "{PLAYER} received EEVEE!$"

BillHouse_Text_EeveeMayEvolve:
    .string "ביל: פרופ' אלם טוען שאיווי עשוי\n"
    .string "להתפתח בדרכים חדשות ולא ידועות.$"

BillHouse_Text_PartyFull:
    .string "Whoa, wait. You can't carry any\n"
    .string "more POKéMON.$"

BillHouse_Text_NoEevee:
    .string "אוי… מה עושים עכשיו?$"

BillHouse_Text_PopWontWork:
    .string "ביל: אבא שלי לא מוכן לעבוד. כל מה\n"
    .string "שהוא עושה זה להתבטל כל היום.\p"
    .string "הוא נהיה כאב ראש אמיתי…$"

BillHouse_Text_MomBeforeEcruteak:
    .string "אה, אתה אוסף פוקימונים? הבן שלי\n"
    .string "ביל הוא מומחה.\p"
    .string "הרגע קראו לו למרכז הפוקימון\n"
    .string "בעיר אקרוטיק.\p"
    .string "בעלי הלך למשחקייה\n"
    .string "בלי שאף אחד קרא לו…$"

BillHouse_Text_MomAfterEcruteak:
    .string "פעם בעלי היה ידוע כפוקימאניאק.\p"
    .string "ביל כנראה יצא דומה לאבא שלו.$"

BillHouse_Text_SisterUsefulNumber:
    .string "Are you a TRAINER?\p"
    .string "I've got a useful phone number\n"
    .string "for you.$"

BillHouse_Text_RecordedBillsNumber:
    .string "{PLAYER} recorded BILL's number.$"

BillHouse_Text_SisterRefusedNumber:
    .string "My brother made the PC POKéMON\n"
    .string "storage system.\p"
    .string "I was going to give you BILL's\n"
    .string "number…$"

BillHouse_Text_SisterPhoneFull:
    .string "You can't record any more numbers.$"

BillHouse_Text_SisterStorageSystem:
    .string "אחי הגדול ביל יצר את מערכת\n"
    .string "אחסון הפוקימונים במחשב.$"
