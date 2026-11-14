GoldenrodCity_DepartmentStore_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0


GoldenrodDeptStore5_EventScript_Lass::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FLass, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Girl::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_Girl, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Sign::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_5FDirectory, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Receptionist::
	lock
	faceplayer
	goto_if_set FLAG_GOT_RETURN, GoldenrodDeptStore5_EventScript_Receptionist_Already
	msgbox GoldenrodDeptStore_Text_5FReceptionistOhYourMon, MSGBOX_DEFAULT
	closemessage
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ge VAR_RESULT, FRIENDSHIP_150_TO_199, GoldenrodDeptStore5_EventScript_Receptionist_GiveReturn
	msgbox GoldenrodDeptStore_Text_5FReceptionistPutInSomeMoreEffort, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Receptionist_GiveReturn::
	giveitem ITEM_TM_RETURN
	setflag FLAG_GOT_RETURN
	msgbox GoldenrodDeptStore_Text_5FReceptionistThisMoveShouldBePerfect, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore5_EventScript_Receptionist_Already::
	msgbox GoldenrodDeptStore_Text_5FReceptionistWait, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_5FReceptionistOhYourMon:
    .string "שלום. אה, הפוקימון שלך…$"

GoldenrodDeptStore_Text_5FReceptionistWait:
    .string "רגע, כבר נתתי לך את המ”מ הזה!$"

GoldenrodDeptStore_Text_5FReceptionistPutInSomeMoreEffort:
	.string "הממ…\n"
	.string "זה לא רע, אבל גם לא טוב.\p"
	.string "אתה, בתור המאמן, צריך להשקיע\n"
	.string "קצת יותר מאמץ.$"

GoldenrodDeptStore_Text_5FReceptionistThisMoveShouldBePerfect:
    .string "הוא מאוד קשור אליך.\p"
    .string "המהלך הזה אמור להתאים בדיוק\n"
    .string "לזוג כמוכם.$"

GoldenrodDeptStore_Text_5FLass:
    .string "בשעות היום מגיעה לכאן גברת\n"
    .string "שבודקת פוקימונים.\p"
    .string "היא אפילו מחלקת מ”מ!$"

GoldenrodDeptStore_Text_5FPokefanM:
    .string "אי אפשר לשנות שם של פוקימון\n"
    .string "שמקבלים בהחלפה.\p"
    .string "השם משקף את הרגשות של\n"
    .string "המאמן המקורי כלפיו.$"

GoldenrodDeptStore_Text_Girl:
	.string "הגברת נתנה לי את המהלך חזרה!\n"
	.string "הפוקימון שלי בטח ממש אוהב אותי!$"

GoldenrodDeptStore5_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodDeptStore5_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodDeptStore5_Pokemart:
	.2byte ITEM_TM_LIGHT_SCREEN
	.2byte ITEM_TM_PROTECT
	.2byte ITEM_TM_REFLECT
	.2byte ITEM_TM_NATURAL_GIFT
	.2byte ITEM_TM_BLIZZARD
	.2byte ITEM_TM_HYPER_BEAM
	.2byte ITEM_TM_SOLAR_BEAM
	.2byte ITEM_TM_THUNDER
	.2byte ITEM_TM_FIRE_BLAST
	.2byte ITEM_TM_FOCUS_BLAST
	pokemartlistend


GoldenrodDeptStore_Text_5FDirectory:
    .string "התאמה אישית לפוקימונים שלך\p"
    .string "ק5: פינת המ”מ$"
