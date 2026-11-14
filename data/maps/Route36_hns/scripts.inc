Route36_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route36_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route36_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route36_EventScript_RockSmashGuy::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_RockSmashGuy2
	msgbox Route36_Text_RockSmashGuy1, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_RockSmashGuy2::
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, Route36_EventScript_RockSmashGuy3
	msgbox Route36_Text_RockSmashGuy2, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
Route36_EventScript_RockSmashGuy3::
	msgbox Route36_Text_RockSmashGuy3
	closemessage
	release
	end

Route36_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Route36_EventScript_Lass2
	msgbox Route36_Text_Lass1, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_Lass2::
	msgbox Route36_Text_Lass2_ClearedSudowoodo, MSGBOX_DEFAULT
	closemessage
	release
	end

Route36_EventScript_Arthur::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HARD_STONE, Route36_EventScript_ArthurCompleted
	msgbox Route36_Text_MeetArthur, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route36_EventScript_ArthurNope
	case 1, Route36_EventScript_ArthurNope
	case 2, Route36_EventScript_ArthurNope
	case 3, Route36_EventScript_ArthurNope
	case 4, Route36_EventScript_ArthurYes
	case 5, Route36_EventScript_ArthurNope
	case 6, Route36_EventScript_ArthurNope
	case 7, Route36_EventScript_ArthurCancel
	case MULTI_B_PRESSED, Route36_EventScript_ArthurCancel
	closemessage
	release
	end
Route36_EventScript_ArthurYes::
	msgbox Route36_Text_ArthurGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_HARD_STONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_HARD_STONE
	msgbox Route36_Text_ArthurGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_ArthurNope::
	msgbox Route36_Text_ArthurNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route36_EventScript_ArthurCancel::
	closemessage
	release
	end
Route36_EventScript_ArthurCompleted::
	msgbox Route36_Text_ArthurThursday, MSGBOX_DEFAULT
	closemessage
	release
	end


Route36_EventScript_SudoWoodo::
	lock
	msgbox Route36_Text_OddTree, MSGBOX_DEFAULT
	checkitem ITEM_SQUIRT_BOTTLE
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_SudoWoodoChoice
	closemessage
	release
	end
Route36_EventScript_SudoWoodoChoice::
	msgbox Route36_Text_UseSquirtbottle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_SudoWoodoWater
	closemessage
	release
	end
Route36_EventScript_SudoWoodoWater::
	msgbox Route36_Text_UsedSquirtbottle, MSGBOX_DEFAULT
	playse SE_DOWNPOUR
	waitse
	closemessage
	playse SE_SUDOWOODO_SHAKE	
	applymovement LOCALID_ROUTE36_SUDOWOODO, Route36_Movement_SudoWoodo
	waitmovement 0
	faceplayer
	msgbox Route36_Text_SudowoodoAttacked	
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_ROUTE36_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 20
	@setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	@clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route36_EventScript_Defeated_Sudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route36_EventScript_RanSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route36_EventScript_RanSudowoodo
Route36_EventScript_Defeated_Sudowoodo::
	setflag FLAG_HIDE_SUDOWOODO
	removeobject LOCALID_ROUTE36_SUDOWOODO
	checkitem ITEM_HM_ROCK_SMASH
	call_if_eq VAR_RESULT, FALSE, Route36_EventScript_RockSmashGuySudoWoodo
	release
	end

Route36_EventScript_RanSudowoodo::
	turnobject LOCALID_ROUTE36_SUDOWOODO, DIR_NORTH
	release
	end

Route36_EventScript_RockSmashGuySudoWoodo:
	playse SE_PIN
	applymovement LOCALID_ROUTE36_ROCKSMASHGUY, Common_Movement_ExclamationMark
	turnobject LOCALID_ROUTE36_ROCKSMASHGUY, DIR_WEST
	waitmovement 0
	applymovement LOCALID_ROUTE36_ROCKSMASHGUY, Route36_Movement_RockSmashGuy
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitmovement 0
	return

Route36_Movement_RockSmashGuy:
	jump_in_place_left
	delay_2
	jump_in_place_left
	delay_2
	jump_in_place_left
	delay_2
	jump_in_place_left
	step_end

Route36_EventScript_Mark::
	trainerbattle_single TRAINER_MARK_HNS, Route36_Text_PsychicMarkSeen, Route36_Text_PsychicMarkBeaten
	msgbox Route36_Text_PsychicMarkAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Schoolboy::
	trainerbattle_single TRAINER_ALAN_HNS, Route36_Text_SchoolboyAlan1Seen, Route36_Text_SchoolboyAlan1Beaten, Route36_EventScript_RegisterAlan
	goto_if_set FLAG_ALAN_HAS_ITEM_HNS, Route36_EventScript_AlanGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route36_EventScript_RematchAlan
	msgbox Route36_Text_SchoolboyAlanAfter, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_RegisterAlan::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route36_Text_AlanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ALAN_HNS
	release
	end

Route36_EventScript_RematchAlan::
	trainerbattle_rematch TRAINER_ALAN_HNS, Route36_Text_AlanRematchIntro, Route36_Text_AlanRematchDefeat
	msgbox Route36_Text_AlanPostRematch, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_AlanGiveItem::
	msgbox Route36_Text_AlanHasItem, MSGBOX_DEFAULT
	giveitem VAR_ALAN_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route36_EventScript_AlanNoRoom
	clearflag FLAG_ALAN_HAS_ITEM_HNS
	msgbox Route36_Text_AlanGaveItem, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_AlanNoRoom::
	msgbox Route36_Text_AlanNoRoom, MSGBOX_AUTOCLOSE
	end

Route36_EventScript_Sign::
	lock
	msgbox Route36_Text_Sign_RuinsNorth, MSGBOX_SIGN
	closemessage
	release
	end

Route36_EventScript_Sign2::
	lock
	msgbox Route36_Text_Tips1, MSGBOX_SIGN
	closemessage
	release
	end

Route36_Movement_SudoWoodo:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

Route36_Text_UseSquirtbottle:
	.string "להשתמש בבקבוק ההתזה?$"

Route36_Text_UsedSquirtbottle:
	.string "{PLAYER} השתמש בבקבוק ההתזה.$"

Route36_Text_SudowoodoAttacked:
	.string "העץ המוזר לא אוהב את\n"
	.string "בקבוק ההתזה!\p"
	.string "העץ המוזר תקף!$"

Route36_Text_RockSmashGuy1:
	.string "וואו-היי!\p"
	.string "התכוונתי לשבור את העץ הזה\n"
	.string "באגרוף הישר שלי.\p"
	.string "אבל לא הצלחתי! אני כישלון!$"

Route36_Text_RockSmashGuy2:
	.string "סילקת את העץ הארור ההוא?\p"
	.string "מרשים מאוד!\n"
	.string "אני רוצה לתת לך את זה.$"

Route36_Text_RockSmashGuy3:
	.string "מה שנתתי לך זה ניפוץ סלע.\p"
	.string "אפשר לנפץ סלעים במכה אחת\n"
	.string "מדויקת בלבד.\p"
	.string "אם סלעים חוסמים לך את הדרך,\n"
	.string "פשוט מנפצים אותם!$"

Route36_Text_OddTree:
	.string "עץ מוזר חוסם את הדרך.$"

Route36_Text_Lass1:
	.string "כדאי להיזהר בדרך הזאת בלילה!\p"
	.string "ראיתי פוקימון שנראה כמו גראולית',\n"
	.string "אבל הייתה לו הילה מפחידה.$"

Route36_Text_Lass2_ClearedSudowoodo:
	.string "העץ המוזר ההוא נעלם\n"
	.string "בלי להשאיר עקבות.\p"
	.string "אה! העץ הזה היה בעצם\n"
	.string "פוקימון?$"

Route36_Text_PsychicMarkSeen:
	.string "אני הולך לקרוא את המחשבות שלך!$"

Route36_Text_PsychicMarkBeaten:
	.string "קראתי אותך לא נכון!$"

Route36_Text_PsychicMarkAfter:
	.string "הייתי חזק, אילו רק יכולתי לדעת\n"
	.string "מה היריב שלי חושב.$"

Route36_Text_SchoolboyAlan1Seen:
	.string "בזכות הלימודים שלי, אני מוכן\n"
	.string "לכל פוקימון!$"

Route36_Text_SchoolboyAlan1Beaten:
	.string "אופס! טעות בחישוב?$"

Route36_Text_SchoolboyAlanAfter:
	.string "אוף. ואני עוד לומד חמש שעות ביום.\p"
	.string "כנראה שללמוד זה לא רק\n"
	.string "לקרוא ספרים.$"

Route36_Text_MeetArthur:
	.string "ארתור: מי אתה?\n"
	.string "שמי ארתור, ממשפחת ימי השבוע.\p"
	.string "אם תנחש מה היום האהוב עליי,\n"
	.string "אתן לך פרס.$"

Route36_Text_ArthurNope:
	.string "לא בדיוק!$"

Route36_Text_ArthurGivesGift:
	.string "הנה. זה בשבילך.$"

Route36_Text_ArthurGaveGift:
	.string "ארתור: כדאי שפוקימון שמשתמש\n"
	.string "במהלכים מסוג סלע יחזיק בזה.\p"
	.string "זה מחזק התקפות מסוג סלע.$"

Route36_Text_ArthurThursday:
	.string "ארתור: אני ארתור של יום חמישי.\n"
	.string "אני הבן החמישי מתוך שבעה.$"

Route36_Text_Sign:
	.string "ROUTE 36$"

Route36_Text_Sign_RuinsNorth:
	.string "חורבות אלף\n"
	.string "כניסה צפונית$"

Route36_Text_Tips1:
	.string "טיפים למאמנים\p"
	.string "הנתונים של כל פוקימון שונים,\n"
	.string "גם בין פוקימונים מאותו מין.\p"
	.string "בהתחלה הנתונים עשויים להיות דומים.\p"
	.string "אבל ככל שהפוקימונים גדלים,\n"
	.string "ההבדלים ביניהם הולכים ובולטים.$"

Route36_Text_Tips2:
	.string "TRAINER TIPS\n"
	.string "Use DIG to return to the entrance of\n"
	.string "any place.\p"
	.string "It is convenient for exploring\n"
	.string "caves and other landmarks.$"

Route36_Text_AlanRegister:
	.string "אוף. ואני עוד לומד חמש שעות ביום.\p"
	.string "כנראה שללמוד זה לא רק\n"
	.string "לקרוא ספרים.$"

Route36_Text_AlanRematchIntro:
	.string "בזכות הלימודים שלי, אני מוכן\n"
	.string "לכל פוקימון!$"

Route36_Text_AlanRematchDefeat:
	.string "אופס! טעות בחישוב?$"

Route36_Text_AlanPostRematch:
	.string "אוף. ואני עוד לומד חמש שעות ביום.\p"
	.string "כנראה שללמוד זה לא רק\n"
	.string "לקרוא ספרים.$"

Route36_Text_AlanHasItem:
	.string "היי! מצאתי משהו\n"
	.string "בזמן שלמדתי!\p"
	.string "הנה, זה בשבילך!$"

Route36_Text_AlanGaveItem:
	.string "אודיע לך אם אמצא\n"
	.string "עוד משהו!$"

Route36_Text_AlanNoRoom:
	.string "הממ, התיק שלך מלא.\p"
	.string "כדאי לחזור כשיהיה בו מקום.$"
