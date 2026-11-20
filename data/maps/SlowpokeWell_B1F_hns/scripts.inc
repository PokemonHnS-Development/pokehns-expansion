SlowpokeWell_B1F_hns_MapScripts::
	.byte 0

SlowpokeWell_B1F_EventScript_Item_Super_Potion_1::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Super_Potion_2::
	finditem ITEM_SUPER_POTION
	end

SlowpokeWell_B1F_EventScript_Item_Great_Ball::
	finditem ITEM_GREAT_BALL
	end

SlowpokeWell_B1F_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

SlowpokeWell_B1F_EventScript_Kurt::
	lock
	msgbox SlowpokeWell_B1F_Text_KurtIntro, MSGBOX_DEFAULT
	closemessage
	end

SlowpokeWell_B1F_EventScript_Grunt21::
	trainerbattle_single TRAINER_GRUNT_21_HNS, SlowpokeWell_B1F_Text_GruntM29Seen, SlowpokeWell_B1F_Text_GruntM29Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM29After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Grunt22F::
	trainerbattle_single TRAINER_GRUNT_22_HNS, SlowpokeWell_B1F_Text_GruntF1Seen, SlowpokeWell_B1F_Text_GruntF1Beaten
	msgbox SlowpokeWell_B1F_Text_GruntF1After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Eto::
	trainerbattle_single TRAINER_ETO_HNS, SlowpokeWell_B1F_Text_GruntM2Seen, SlowpokeWell_B1F_Text_GruntM2Beaten
	msgbox SlowpokeWell_B1F_Text_GruntM2After, MSGBOX_AUTOCLOSE
	end

SlowpokeWell_B1F_EventScript_Proton::
	lock
	faceplayer
	msgbox SlowpokeWell_B1F_Text_ProtonSeen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_PROTON_1_HNS, SlowpokeWell_B1F_Text_ProtonBeaten
	msgbox SlowpokeWell_B1F_Text_ProtonAfter, MSGBOX_AUTOCLOSE
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_AZALEA_TOWN_ROCKETS
	clearflag FLAG_HIDE_KURT_1
	addobject LOCALID_WELL_KURT
	removeobject 11
	removeobject 12
	removeobject 13
	delay 120
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	applymovement LOCALID_WELL_KURT, SlowpokeWell_B1F_Movement_Kurt
	waitmovement 0
	msgbox SlowpokeWell_B1F_Text_KurtAfter, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_SLOWPOKE_WELL_KURT
	setflag FLAG_HIDE_KURT_1
	clearflag FLAG_HIDE_KURT_2
	clearflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setvar VAR_AZALEA_TOWN_STATE, 3
	warp MAP_AZALEA_TOWN_KURTS_HOUSE_HNS, 15, 4
	waitstate
	end

SlowpokeWell_B1F_Movement_Kurt:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	step_end

SlowpokeWell_B1F_Text_KurtIntro:
	.string "קורט: היי, {PLAYER}!\p"
	.string "השומר שעמד למעלה ברח\n"
	.string "כשצעקתי עליו.\p"
	.string "אבל אז נפלתי למטה\n"
	.string "לתוך הבאר.\p"
	.string "נחבטתי חזק בגב,\n"
	.string "אז אני לא יכול לזוז.\p"
	.string "אוף! אם הייתי בכושר,\n"
	.string "הפוקימונים שלי היו מענישים אותם…\p"
	.string "אה, אין מה לעשות.\p"
	.string "{PLAYER}, תראה להם כמה\n"
	.string "אתה אמיץ, במקומי!$"

SlowpokeWell_B1F_Text_KurtAfter:
	.string "קורט: כל הכבוד, {PLAYER}!\p"
	.string "צוות רוקט הסתלק.\p"
	.string "גם הגב שלי כבר יותר טוב.\n"
	.string "בוא נצא מכאן.$"

SlowpokeWell_B1F_Text_GruntM29Seen:
	.string "לעזאזל! עמדתי על המשמר למעלה,\n"
	.string "ואיזה זקן מטורלל צעק עליי.\p"
	.string "הוא הבהיל אותי כל כך,\n"
	.string "שנפלתי לכאן למטה.\p"
	.string "נראה לי שאוציא\n"
	.string "את העצבים עליך!$"

SlowpokeWell_B1F_Text_GruntM29Beaten:
	.string "אררג! זה ממש לא היום שלי!$"

SlowpokeWell_B1F_Text_GruntM29After:
	.string "בטח, כרתנו זנבות לסלופוק\n"
	.string "ומכרנו אותם.\p"
	.string "כל מה שאנחנו עושים זה בשביל רווח.\p"
	.string "נכון מאוד! אנחנו צוות רוקט,\n"
	.string "ואנחנו נעשה הכול בשביל כסף!$"

SlowpokeWell_B1F_Text_ProtonSeen:
	.string "מה אתה רוצה?\p"
	.string "אם תפריע לנו בעבודה,\n"
	.string "אל תצפה לרחמים!$"

SlowpokeWell_B1F_Text_ProtonBeaten:
	.string "היום עוד הסתדרת,\n"
	.string "אבל חכה לפעם הבאה!$"

SlowpokeWell_B1F_Text_ProtonAfter:
	.string "כן, צוות רוקט התפרק\n"
	.string "לפני שלוש שנים.\p"
	.string "הבוס נעלם והסתתר.\p"
	.string "אבל אנחנו המשכנו בפעילות שלנו\n"
	.string "במחתרת!\p"
	.string "מכשול קטן כמוך לא יהווה\n"
	.string "בעיה גדולה למשימה שלנו.\p"
	.string "אני ממליץ לך לפחד מאוד\n"
	.string "ממה שעומד לבוא!$"

SlowpokeWell_B1F_Text_GruntM2Seen:
	.string "חה-חה-חה!\n"
	.string "להפסיק לקחת זנבות סלופוק?\p"
	.string "אתה משוגע! אם נקשיב לך,\n"
	.string "המוניטין של צוות רוקט ייהרס!$"

SlowpokeWell_B1F_Text_GruntM2Beaten:
	.string "חה…\n"
	.string "חזק מדי…$"

SlowpokeWell_B1F_Text_GruntM2After:
	.string "אנחנו צריכים את הכסף,\n"
	.string "אבל למכור זנבות סלופוק?\p"
	.string "קשה להיות גראנט בצוות רוקט!$"

SlowpokeWell_B1F_Text_GruntF1Seen:
	.string "להפסיק לקחת זנבות?\p"
	.string "כן, בטח. רק תנסה לנצח\n"
	.string "את כולנו!$"

SlowpokeWell_B1F_Text_GruntF1Beaten:
	.string "פרחח מגעיל!$"

SlowpokeWell_B1F_Text_GruntF1After:
	.string "זנבות סלופוק צומחים מחדש מהר!\p"
	.string "אז מה רע בזה שמוכרים אותם?$"

SlowpokeWell_B1F_Text_SlowpokeWithMail:
	.string "A SLOWPOKE with its TAIL cut off…\p"
	.string "Huh? It has MAIL.\n"
	.string "Read it?$"

SlowpokeWell_B1F_Text_SlowpokeMail:
	.string "{PLAYER} read the MAIL.\p"
	.string "Be good and look after the\n"
	.string "house with Grandpa and SLOWPOKE.\p"
	.string "Love, Dad$"

SlowpokeWell_B1F_Text_TaillessSlowpoke:
	.string "A SLOWPOKE with its TAIL cut off…$"
