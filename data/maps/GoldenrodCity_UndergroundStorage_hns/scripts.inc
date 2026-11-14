GoldenrodCity_UndergroundStorage_hns_MapScripts::
	.byte 0

GoldenrodCity_UndergroundStorage_EventScript_Director::
    lock
    faceplayer
    checkitem ITEM_CARD_KEY
    goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_UndergroundStorage_EventScript_Director2
    msgbox RadioTowerBasement_Text_DirectorIntro, MSGBOX_DEFAULT
    closemessage
    giveitem ITEM_CARD_KEY
    msgbox RadioTowerBasement_Text_DirectorCardKey, MSGBOX_DEFAULT
    closemessage
    release
    end

GoldenrodCity_UndergroundStorage_EventScript_Director2::
    msgbox RadioTowerBasement_Text_DirectorAfter, MSGBOX_DEFAULT
    closemessage
    release
    end

GoldenrodCity_UndergroundStorage_EventScript_Grunt19::
    trainerbattle_single TRAINER_GRUNT_19_HNS, RadioTowerBasement_Text_GruntM24Seen, RadioTowerBasement_Text_GruntM24Beaten
	msgbox RadioTowerBasement_Text_GruntM24After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Grunt12::
    trainerbattle_single TRAINER_GRUNT_12_HNS, RadioTowerBasement_Text_GruntM14Seen, RadioTowerBasement_Text_GruntM14Beaten
	msgbox RadioTowerBasement_Text_GruntM14After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Eto::
    trainerbattle_single TRAINER_ETO_3_HNS, RadioTowerBasement_Text_GruntM15Seen, RadioTowerBasement_Text_GruntM15Beaten
	msgbox RadioTowerBasement_Text_GruntM15After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_UndergroundStorage_EventScript_Item_TM_CALM_MIND::
    finditem ITEM_TM_CALM_MIND
    end

GoldenrodCity_UndergroundStorage_EventScript_Item_UltraBall::
    finditem ITEM_ULTRA_BALL
    end

GoldenrodCity_UndergroundStorage_EventScript_Item_MaxEther::
    finditem ITEM_MAX_ETHER
    end

RadioTowerBasement_Text_GruntM24Seen:
    .string "איך הגעת עד לכאן?\p"
    .string "נו, אין מה לעשות. אצטרך\n"
    .string "לסלק אותך.$"

RadioTowerBasement_Text_GruntM24Beaten:
    .string "סילקו אותי…$"

RadioTowerBasement_Text_GruntM24After:
    .string "צוות רוקט ימשיך לפעול, ויחכה\n"
    .string "לשובו של ג'ובאני.\p"
    .string "נעשה כל מה שצריך.$"

RadioTowerBasement_Text_GruntM14Seen:
    .string "מכאן לא ממשיכים!\p"
    .string "אני לא מרחם על האויבים שלי,\n"
    .string "אפילו לא על פרחחים!$"

RadioTowerBasement_Text_GruntM14Beaten:
    .string "לעזאזל!$"

RadioTowerBasement_Text_GruntM14After:
    .string "הפסדתי…\p"
    .string "בבקשה סלח לי, ג'ובאני!$"

RadioTowerBasement_Text_GruntM15Seen:
    .string "חה-חה-חה! תראו מי כאן!\p"
    .string "מוכן? עכשיו אני ממש קשוח!$"

RadioTowerBasement_Text_GruntM15Beaten:
    .string "חה-חה-חה! אתה ממש טוב!\p"
    .string "צוות רוקט זה בשבילי רק עבודה,\n"
    .string "אבל אני רואה שזה פוגע באחרים.\p"
    .string "זהו, אני עוזב.\p"
    .string "תודה רבה לך. סליחה, ג'ובאני!$"

RadioTowerBasement_Text_GruntM15After:
    .string "חה-חה-חה! זה היה כיף!\n"
    .string "אני אזכור אותך!$"

RadioTowerBasement_Text_DirectorIntro:
    .string "מנהל התחנה: מי? מה? באת\n"
    .string "להציל אותי?\p"
    .string "תודה לך!\p"
    .string "מגדל הרדיו!\p"
    .string "מה קורה שם?\p"
    .string "צוות רוקט השתלט עליו?\p"
    .string "הנה, כרטיס הגישה הזה בשבילך.$"

RadioTowerBasement_Text_DirectorCardKey:
    .string "מנהל התחנה: בעזרתו אפשר לפתוח\n"
    .string "את התריסים בקומה 3.$"

RadioTowerBasement_Text_DirectorAfter:
    .string "אני מתחנן לעזרתך.\p"
    .string "אין לדעת מה הם יעשו אם\n"
    .string "ישתלטו על המשדר.\p"
    .string "אולי הם אפילו יוכלו לשלוט\n"
    .string "בפוקימונים בעזרת אות מיוחד!\p"
    .string "רק עליך אני יכול לסמוך.\p"
    .string "בבקשה, הצל את מגדל הרדיו…\p"
    .string "ואת כל הפוקימונים בארץ!$"
