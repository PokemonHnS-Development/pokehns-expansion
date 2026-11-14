Route32_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route32_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route32_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route32_EventScript_FisherJustin::
	trainerbattle_single TRAINER_JUSTIN_HNS, Route32_Text_FisherJustin_Seen, Route32_Text_FisherJustin_Beaten
	msgbox Route32_Text_FisherJustin_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherRalph::
	trainerbattle_single TRAINER_RALPH_HNS, Route32_Text_FisherRalph1_Seen, Route32_Text_FisherRalph1_Beaten, Route32_EventScript_RegisterRalph
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_RematchRalph
	msgbox Route32_Text_FisherRalph1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_RegisterRalph::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_RalphRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_RALPH_HNS
	release
	end

Route32_EventScript_RematchRalph::
	trainerbattle_rematch TRAINER_RALPH_HNS, Route32_Text_RalphRematchIntro, Route32_Text_RalphRematchDefeat
	msgbox Route32_Text_RalphPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherHenry::
	trainerbattle_single TRAINER_HENRY_HNS, Route32_Text_FisherHenry_Seen, Route32_Text_FisherHenry_Beaten
	msgbox Route32_Text_FisherHenry_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterAlbert::
	trainerbattle_single TRAINER_ALBERT_HNS, Route32_Text_YoungsterAlbert_Seen, Route32_Text_YoungsterAlbert_Beaten
	msgbox Route32_Text_YoungsterAlbert_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterGordon::
	trainerbattle_single TRAINER_GORDON_HNS, Route32_Text_YoungsterGordon_Seen, Route32_Text_YoungsterGordon_Beaten
	msgbox Route32_Text_YoungsterGordon_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_CamperRoland::
	trainerbattle_single TRAINER_ROLAND_HNS, Route32_Text_CamperRoland_Seen, Route32_Text_CamperRoland_Beaten
	msgbox Route32_Text_CamperRoland_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_PicnickerLiz::
	trainerbattle_single TRAINER_LIZ_HNS, Route32_Text_PicnickerLiz1_Seen, Route32_Text_PicnickerLiz1_Beaten, Route32_EventScript_RegisterLiz
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_RematchLiz
	msgbox Route32_Text_PicnickerLiz1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_RegisterLiz::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_LizRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LIZ_HNS
	release
	end

Route32_EventScript_RematchLiz::
	trainerbattle_rematch TRAINER_LIZ_HNS, Route32_Text_LizRematchIntro, Route32_Text_LizRematchDefeat
	msgbox Route32_Text_LizPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_BirdkeeperPeter::
	trainerbattle_single TRAINER_PETER_HNS, Route32_Text_BirdKeeperPeter_Seen, Route32_Text_BirdKeeperPeter_Beaten
	msgbox Route32_Text_BirdKeeperPeter_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_Roar::
	lock
	faceplayer
	checkitem ITEM_TM_ROAR
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_Roar2
	msgbox Route32_Text_RoarIntro, MSGBOX_DEFAULT
	giveitem ITEM_TM_ROAR
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_Roar2::
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_SlowpokeTail_TriggerLeft::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SLOWPOKETAIL_MAN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeLeft
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerMid::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SLOWPOKETAIL_MAN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeMid
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerRight::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SLOWPOKETAIL_MAN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeRight
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_Trigger::
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail_Trigger2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SLOWPOKE_TAIL, 1
	release
	end	
Route32_EventScript_SlowpokeTail_Trigger2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 16, Route32_EventScript_Movement_Left
	call_if_eq VAR_TEMP_0, 17, 	Route32_EventScript_Movement_Right
	setvar VAR_SLOWPOKE_TAIL, 1
	release
	end

Route32_EventScript_Movement_Left::
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	return 

Route32_EventScript_Movement_Right::
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	return 	

Route32_EventScript_SlowpokeTail::
	lock
	faceplayer
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_SlowpokeTail2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	release
	end


Route32_EventScript_Frieda::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POISON_BARB, Route32_EventScript_FriedaCompleted
	msgbox Route32_Text_MeetFrieda, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route32_EventScript_FriedaNope
	case 1, Route32_EventScript_FriedaNope
	case 2, Route32_EventScript_FriedaNope
	case 3, Route32_EventScript_FriedaNope
	case 4, Route32_EventScript_FriedaNope
	case 5, Route32_EventScript_FriedaYes
	case 6, Route32_EventScript_FriedaNope
	case 7, Route32_EventScript_FriedaCancel
	case MULTI_B_PRESSED, Route32_EventScript_FriedaCancel
	closemessage
	release
	end
Route32_EventScript_FriedaYes::
	msgbox Route32_Text_FriedaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_POISON_BARB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_POISON_BARB
	msgbox Route32_Text_FriedaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_FriedaNope::
	msgbox Route32_Text_FriedaNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_FriedaCancel::
	closemessage
	release
	end
Route32_EventScript_FriedaCompleted::
	msgbox Route32_Text_FriedaFriday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox Route32_Text_CooltrainerM_Experiences, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE32_BALDINGMAN, DIR_EAST
	release
	end

Route32_EventScript_BaldingManTriggerLeft::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE32_BALDINGMAN
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManTriggerMid::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE32_BALDINGMAN
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_StartMid
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManTriggerRight::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE32_BALDINGMAN
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movment_StartRight
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManCheck::
	goto_if_unset FLAG_HIDE_SPROUT_TOWER_SILVER, Route32_EventScript_BaldingManTower
	goto_if_unset FLAG_DEFEATED_VIOLET_GYM, Route32_EventScript_BaldingManGym
	goto_if_unset FLAG_RECEIVED_TOGEPI_EGG, Route32_EventScript_BaldingManEgg
	msgbox Route32_Text_CooltrainerM_HaveThisSeed, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setvar VAR_VIOLET_CITY_STATE, 5
	release
	end
Route32_EventScript_BaldingManTower::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_SproutTower, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
Route32_EventScript_BaldingManGym::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_VioletGym, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
Route32_EventScript_BaldingManEgg::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_AideIsWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end

Route32_EventScript_Item_Bullet_Seed::
    finditem ITEM_TM_BULLET_SEED
    end
	
Route32_EventScript_GreatBall::
	finditem ITEM_GREAT_BALL
	end
Route32_EventScript_GreatBallII::
	finditem ITEM_GREAT_BALL
	end
Route32_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route32_EventScript_Sign1::
	lock
	msgbox Route32_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign2::
	lock
	msgbox Route32_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign3::
	lock
	msgbox Route32_Text_Sign3, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Movement_Turnback:
	walk_up
	step_end

Route32_Movement_StartMid:
	walk_left
	step_end

Route32_Movment_StartRight:
	walk_left
	walk_left
	step_end

Route32_Movement_SlowpokeLeft::
	step_end

Route32_Movement_SlowpokeMid::
	walk_right
	step_end

Route32_Movement_SlowpokeRight::
	walk_right
	walk_right
	step_end

Route32_Text_CooltrainerM_WhatsTheHurry:
	.string "רגע, רגע!\n"
	.string "לאן כל כך ממהרים?$"

Route32_Text_CooltrainerM_AideIsWaiting:
	.string "{PLAYER}, נכון?\n"
	.string "איזה בחור עם משקפיים חיפש אותך.\p"
	.string "לך תראה בעצמך. הוא מחכה לך\n"
	.string "במרכז הפוקימון.$"

Route32_Text_CooltrainerM_SproutTower:
	.string "כבר היית במגדל הנבט?\p"
	.string "מי שמבקר בעיר ויולט, מצפים\n"
	.string "ממנו להתאמן שם.\p"
	.string "זה בסיסי למאמנים.\n"
	.string "קדימה, למגדל הנבט!$"

Route32_Text_CooltrainerM_VioletGym:
	.string "כבר היית במכון הפוקימון?\p"
	.string "שם אפשר לבחון את הפוקימונים שלך\n"
	.string "ואת עצמך.\p"
	.string "זה טקס חניכה שכל המאמנים עוברים!$"

Route32_Text_CooltrainerM_HaveThisSeed:
	.string "יש לך פוקימונים טובים. זה בטח\n"
	.string "בזכות האימונים באזור העיר ויולט.\p"
	.string "האימונים במכון בטח עזרו במיוחד.\n"
	.string "קח את זה, למזכרת מהעיר ויולט.\p"
	.string "זה מגביר את העוצמה של\n"
	.string "מהלכים מסוג עשב.$"

Route32_Text_CooltrainerM_Experiences:
	.string "החוויות שלך בעיר ויולט\n"
	.string "בטח יועילו לך במסע.$"

Route32_Text_SlowpokeTailOffer:
	.string "מה דעתך על זנב הסלופוק\n"
	.string "הטעים והמזין הזה?\p"
	.string "בשבילך, ממש עכשיו, רק\n"
	.string "¥1,000,000!\p"
	.string "בטוח תרצה אותו!$"

Route32_Text_ThoughtKidsLoaded:
	.string "אוף! חשבתי שלילדים של היום\n"
	.string "יש המון כסף…$"

Route32_Text_RefusedSlowpokeTail:
	.string "לא רוצה?\n"
	.string "אז עוף מפה. קישטה!$"

Route32_Text_FisherJustin_Seen:
	.string "וואו!\p"
	.string "בגללך הדג ברח לי!$"

Route32_Text_FisherJustin_Beaten:
	.string "שפלוש!$"

Route32_Text_FisherJustin_After:
	.string "רוגע, קור רוח…\n"
	.string "המהות של דיג ושל פוקימונים זהה.$"

Route32_Text_FisherRalph1_Seen:
	.string "אני ממש טוב גם בדיג\n"
	.string "וגם בפוקימונים.\p"
	.string "אני לא מתכוון להפסיד לשום ילד!$"

Route32_Text_FisherRalph1_Beaten:
	.string "אוף! מיהרתי יותר מדי…$"

Route32_Text_FisherRalph1_After:
	.string "דיג הוא תשוקה לכל החיים.\p"
	.string "פוקימונים הם חברים לכל החיים!$"

Route32_Text_RalphRegister:
	.string "דיג הוא תשוקה לכל החיים.\p"
	.string "פוקימונים הם חברים לכל החיים!$"

Route32_Text_RalphRematchIntro:
	.string "אני ממש טוב גם בדיג\n"
	.string "וגם בפוקימונים.\p"
	.string "אני לא מתכוון להפסיד לשום ילד!$"

Route32_Text_RalphRematchDefeat:
	.string "אוף! מיהרתי יותר מדי…$"

Route32_Text_RalphPostRematch:
	.string "דיג הוא תשוקה לכל החיים.\p"
	.string "פוקימונים הם חברים לכל החיים!$"

Route32_Text_FisherHenry_Seen:
	.string "הפוקימונים שלי? טריים, ישר מהמים!$"

Route32_Text_FisherHenry_Beaten:
	.string "שכשוך?$"

Route32_Text_FisherHenry_After:
	.string "פוקימונים טריים מהמים לא משתווים\n"
	.string "לפוקימונים שגודלו כמו שצריך.$"

Route32_Text_YoungsterAlbert_Seen:
	.string "לא ראיתי אותך פה קודם.\n"
	.string "אז אתה חושב שאתה די קשוח?$"

Route32_Text_YoungsterAlbert_Beaten:
	.string "אתה חזק!$"

Route32_Text_YoungsterAlbert_After:
	.string "אני אנסה להיות הכי טוב\n"
	.string "עם הפוקימונים האהובים עליי.\p"
	.string "אני לא משתמש באותם פוקימונים\n"
	.string "קשוחים שיש לכולם.$"

Route32_Text_YoungsterGordon_Seen:
	.string "מצאתי פוקימונים טובים בעשב!\p"
	.string "אני חושב שהם יעשו את העבודה!$"

Route32_Text_YoungsterGordon_Beaten:
	.string "אוף. חשבתי שאוכל לנצח.$"

Route32_Text_YoungsterGordon_After:
	.string "העשב מלא בדברים שנדבקים.$"

Route32_Text_CamperRoland_Seen:
	.string "המבט הזה… הוא מסקרן.$"

Route32_Text_CamperRoland_Beaten:
	.string "המממ. זה מאכזב.$"

Route32_Text_CamperRoland_After:
	.string "אם לא רוצים להילחם,\n"
	.string "פשוט נמנעים מקשר עין.$"

Route32_Text_PicnickerLiz1_Seen:
	.string "אה-הא. כן, ובקיצור…\p"
	.string "סליחה? קרב? אני בטלפון.\n"
	.string "נו, טוב. אבל שיהיה מהר.$"

Route32_Text_PicnickerLiz1_Beaten:
	.string "אוי! אני חייבת לפרוק\n"
	.string "את הכעס שלי!$"

Route32_Text_PicnickerLiz1_After:
	.string "ודווקא הייתה לי שיחה נחמדה.$"

Route32_Text_LizRegister:
	.string "ודווקא הייתה לי שיחה נחמדה.$"

Route32_Text_LizRematchIntro:
	.string "אה-הא. כן, ובקיצור…\p"
	.string "סליחה? קרב? אני בטלפון.\n"
	.string "נו, טוב. אבל שיהיה מהר.$"

Route32_Text_LizRematchDefeat:
	.string "אוי! אני חייבת לפרוק\n"
	.string "את הכעס שלי!$"

Route32_Text_LizPostRematch:
	.string "ודווקא הייתה לי שיחה נחמדה.$"

Route32_Text_BirdKeeperPeter_Seen:
	.string "התג הזה! הוא מהעיר ויולט!\n"
	.string "ניצחת את פלקנר?$"

Route32_Text_BirdKeeperPeter_Beaten:
	.string "אני יודע מהן החולשות שלי.$"

Route32_Text_BirdKeeperPeter_After:
	.string "כדאי שאתאמן שוב\n"
	.string "במכון של העיר ויולט.$"

Route32_Text_RoarIntro:
	.string "גררררר! אנשים בורחים כשאני\n"
	.string "שואג! אבל אתה דווקא באת לחפש אותי!\p"
	.string "זה משמח אותי! עכשיו קח את זה!$"

Route32_Text_RoarOutro:
	.string "גררררר! זאת שאגה!\p"
	.string "אפילו פוקימונים בורחים\n"
	.string "משאגה טובה!$"

Route32_Text_MeetFrieda:
	.string "פרידה: יאהו!\p"
	.string "אני פרידה ממשפחת ימי השבוע!\n"
	.string "נעים להכיר!\p"
	.string "אם תנחש מה היום האהוב עליי,\n"
	.string "אתן לך פרס.$"

Route32_Text_FriedaGivesGift:
	.string "הנה, קוץ רעיל בשבילך!$"

Route32_Text_FriedaGaveGift:
	.string "פרידה: תן אותו לפוקימון\n"
	.string "שיש לו מהלכים מסוג רעל.\p"
	.string "הו!\p"
	.string "זה פשוט אדיר!\p"
	.string "תופתע כמה הוא משפר\n"
	.string "מהלכי רעל!$"

Route32_Text_FriedaFriday:
	.string "פרידה: היי! איזה יום אהוב עליך?\p"
	.string "אני אוהבת את יום שישי.\n"
	.string "אין ספק בכלל!\p"
	.string "נכון שגם בעיניך הוא נהדר?$"

Route32_Text_FriedaNope:
	.string "פרידה: לא היום הזה!$"

Route32_Text_Sign1:
	.string "דרך 32\p"
	.string "העיר ויולט - העיירה אזייליה$"

Route32_Text_Sign2:
	.string "חורבות אלף\n"
	.string "כניסה מזרחית$"

Route32_Text_Sign3:
	.string "מערת האיחוד\n"
	.string "בהמשך הדרך$"
