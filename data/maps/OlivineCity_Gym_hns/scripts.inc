OlivineCity_Gym_hns_MapScripts::
	.byte 0

OlivineCity_Gym_EventScript_Gent::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Gent2
	msgbox OlivineCity_Gym_Text_Gent, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_Gent2::
	msgbox OlivineCity_Gym_Text_Gent2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_TriggerRow1::
	lock
	setvar VAR_TEMP_0, LOCALID_OLIVINE_CITY_GYM_NPC1
	playse SE_PIN
	applymovement VAR_TEMP_0, Common_Movement_ExclamationMark
	waitmovement VAR_TEMP_0
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_eq VAR_TEMP_1, 6, OlivineCity_Gym_EventScript_MoveLeft4
	call_if_eq VAR_TEMP_1, 7, OlivineCity_Gym_EventScript_MoveLeft3
	call_if_eq VAR_TEMP_1, 8, OlivineCity_Gym_EventScript_MoveLeft2
	call_if_eq VAR_TEMP_1, 9, OlivineCity_Gym_EventScript_MoveLeft1
	call_if_eq VAR_TEMP_1, 10, OlivineCity_Gym_EventScript_MoveLeft0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox OlivineCity_Gym_Text_Gent, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLIVINE_CITY_STATE, 6
	release
	end

OlivineCity_Gym_EventScript_MoveLeft0::
	turnobject VAR_TEMP_0, DIR_WEST
	return

OlivineCity_Gym_EventScript_MoveLeft1::
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveLeft2::
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveLeft3::
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveLeft4::
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkLeft1
	waitmovement 0
	return

OlivineCity_Gym_Text_Gent:
	.string "ידעתי שתבוא לכאן.\p"
	.string "תודה שעזרת למנהיגת המכון,\n"
	.string "אבל קרב זה כבר עניין אחר.\p"
	.string "בהצלחה!$"

OlivineCity_Gym_Text_Gent2:
	.string "מרשים! כדאי לך להמשיך\n"
	.string "במסע שלך למקומות אחרים.\p"
	.string "עכשיו כשאתה יודע להשתמש בגלישה,\n"
	.string "למה שלא תנסה אותה באגם הזעם?$"

OlivineCity_Gym_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Lass2
	msgbox OlivineCity_Gym_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_Lass2::
	msgbox OlivineCity_Gym_Text_Lass2, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_TriggerRow2::
	lock
	setvar VAR_TEMP_0, LOCALID_OLIVINE_CITY_GYM_NPC2
	playse SE_PIN
	applymovement VAR_TEMP_0, Common_Movement_ExclamationMark
	waitmovement VAR_TEMP_0
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_eq VAR_TEMP_1, 6, OlivineCity_Gym_EventScript_MoveRight0
	call_if_eq VAR_TEMP_1, 7, OlivineCity_Gym_EventScript_MoveRight1
	call_if_eq VAR_TEMP_1, 8, OlivineCity_Gym_EventScript_MoveRight2
	call_if_eq VAR_TEMP_1, 9, OlivineCity_Gym_EventScript_MoveRight3
	call_if_eq VAR_TEMP_1, 10, OlivineCity_Gym_EventScript_MoveRight4
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox OlivineCity_Gym_Text_Lass, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLIVINE_CITY_STATE, 7
	release
	end

OlivineCity_Gym_EventScript_MoveRight0::
	turnobject VAR_TEMP_0, DIR_EAST
	return

OlivineCity_Gym_EventScript_MoveRight1::
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveRight2::
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveRight3::
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_EventScript_MoveRight4::
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	applymovement VAR_TEMP_0, Common_Movement_WalkRight1
	waitmovement 0
	return

OlivineCity_Gym_Text_Lass:
	.string "הי-הי… ראיתי במגדלור\n"
	.string "כמה אתה מוכשר.\p"
	.string "הגיע הזמן שתראה את הצד הזה\n"
	.string "שלך לג'סמין! בהצלחה!$"

OlivineCity_Gym_Text_Lass2:
	.string "אתה מדהים… כדאי לך לשאוף\n"
	.string "גבוה עוד יותר, יש לך המון פוטנציאל.\p"
	.string "כבר היית בעיירה מהגוני?$"

OlivineCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_lt VAR_OLIVINE_CITY_STATE, 5, OlivineCity_Gym_EventScript_GymGuideSick
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_GymGuideAfter
	msgbox OlivineCity_Gym_Text_GymGuideText, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_GymGuideSick::
	msgbox OlivineCity_Gym_Text_GymGuidePreText, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_GymGuideAfter::
	msgbox OlivineCity_Gym_Text_GymGuideWinText, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_GymGuideText:
	.string "ג'סמין משתמשת בסוג פלדה,\n"
	.string "שהתגלה רק לאחרונה.\p"
	.string "היא ידועה בכך שיש לה לא אחד,\n"
	.string "אלא שני קלפים מנצחים.\p"
	.string "הראשון הוא חרק מתכתי עם טכניקה\n"
	.string "שמגבירה את ההתקפה שלו.\p"
	.string "אש פוגעת בו, אבל לפעמים\n"
	.string "הוא שורד מכות חזקות.\p"
	.string "השני הוא נחש ברזל ענקי\n"
	.string "עם הרבה מהלכים חזקים.\p"
	.string "כדאי לגשת אליו בזהירות.\p"
	.string "הוא אולי נראה איטי, אבל ראיתי\n"
	.string "אותו תוקף ראשון במהירות מדהימה.$"

OlivineCity_Gym_Text_GymGuideWinText:
	.string "זה היה מדהים.\p"
	.string "סוג הפלדה, הא?\p"
	.string "זה היה מפגש קרוב\n"
	.string "מהסוג הלא מוכר!$"

OlivineCity_Gym_Text_GymGuidePreText:
	.string "ג'סמין, מנהיגת המכון, נמצאת\n"
	.string "במגדלור.\p"
	.string "היא מטפלת בפוקימון חולה.\p"
	.string "מאמן חזק צריך להיות\n"
	.string "גם בעל חמלה.$"

OlivineCity_Gym_EventScript_Jasmine::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Jasmine_Defeated
	msgbox OlivineCity_Gym_Text_JasmineSteelTypeIntro, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, OlivineCity_Gym_EventScript_CianwoodCheckMahog
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, OlivineCity_Gym_EventScript_MahogCheckCianwood
	goto OlivineCity_Gym_EventScript_Jasmine_Battle1

OlivineCity_Gym_EventScript_JasmineVictory::
	message OlivineCity_Gym_Text_ReceivedMineralBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox OlivineCity_Gym_Text_JasmineBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE06_GET
	setflag FLAG_DEFEATED_OLIVINE_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_IRON_TAIL
	msgbox OlivineCity_Gym_Text_JasmineIronTailSpeech, MSGBOX_DEFAULT
	setvar VAR_OLIVINE_CITY_STATE, 8
	setrespawn HEAL_LOCATION_OLIVINE_CITY_HNS
    call_if_eq VAR_NUM_BADGES, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

OlivineCity_Gym_EventScript_CianwoodCheckMahog::
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, OlivineCity_Gym_EventScript_Jasmine_Battle3
	goto OlivineCity_Gym_EventScript_Jasmine_Battle2

OlivineCity_Gym_EventScript_MahogCheckCianwood::
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, OlivineCity_Gym_EventScript_Jasmine_Battle3
	goto OlivineCity_Gym_EventScript_Jasmine_Battle2
	
OlivineCity_Gym_EventScript_Jasmine_Battle1::
	trainerbattle_no_intro TRAINER_JASMINE_1_HNS, OlivineCity_Gym_Text_JasmineBetterTrainer
	goto OlivineCity_Gym_EventScript_JasmineVictory

OlivineCity_Gym_EventScript_Jasmine_Battle2::
	trainerbattle_no_intro TRAINER_JASMINE_1_2_HNS, OlivineCity_Gym_Text_JasmineBetterTrainer
	goto OlivineCity_Gym_EventScript_JasmineVictory

OlivineCity_Gym_EventScript_Jasmine_Battle3::
	trainerbattle_no_intro TRAINER_JASMINE_1_3_HNS, OlivineCity_Gym_Text_JasmineBetterTrainer
	goto OlivineCity_Gym_EventScript_JasmineVictory

OlivineCity_Gym_EventScript_Jasmine_Defeated::
	goto_if_unset FLAG_HIDE_DOJO_JASMINE, OlivineCity_Gym_EventScript_Jasmine_Trade
	msgbox OlivineCity_Gym_Text_JasmineGoodLuck, MSGBOX_DEFAULT
	closemessage
	release
	end


OlivineCity_Gym_Text_JasmineSteelTypeIntro:
	.string "…תודה על העזרה שלך\n"
	.string "במגדלור…\p"
	.string "אבל זה משהו אחר.\n"
	.string "הרשה לי להציג את עצמי.\p"
	.string "אני ג'סמין, מנהיגת מכון.\n"
	.string "אני משתמשת בסוג פלדה.\p"
	.string "…אתה מכיר את סוג הפלדה?\p"
	.string "זה סוג שהתגלה רק\n"
	.string "לאחרונה.\p"
	.string "…אממ… אפשר להתחיל?$"

OlivineCity_Gym_Text_JasmineBetterTrainer:
	.string "…אתה מאמן טוב ממני,\n"
	.string "גם במיומנות וגם בטוב לב.\p"
	.string "בהתאם לחוקי הליגה,\n"
	.string "אני מעניקה לך את התג הזה.$"

OlivineCity_Gym_Text_ReceivedMineralBadge:
	.string "{PLAYER} קיבל את תג מינרל.$"

OlivineCity_Gym_Text_JasmineBadgeSpeech:
	.string "תג מינרל מעלה את\n"
	.string "ההגנה המיוחדת של פוקימונים.\p"
	.string "…אממ… בבקשה, קח גם את זה…$"

OlivineCity_Gym_Text_JasmineIronTailSpeech:
	.string "…בעזרת המ”מ הזה אפשר ללמד\n"
	.string "זנב ברזל.$"

OlivineCity_Gym_Text_JasmineGoodLuck:
	.string "אממ… אני לא יודעת איך להגיד\n"
	.string "את זה, אבל בהצלחה…$"

OlivineCity_Gym_Text_JasmineRematchText:
	.string "…Congratulations, JOHTO CHAMPION.\p"
	.string "You have become so strong…\p"
	.string "I wonder if I have improved.\p"
	.string "Would you like to test that?\p"
	.string "Want to have a rematch with me?$"

OlivineCity_Gym_Text_JasmineRematchDefeatText:
	.string "…You are a better trainer than me,\n"
	.string "in both skill and kindness.$"

OlivineCity_Gym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, OlivineCity_Gym_EventScript_Statue2
	msgbox OlivineCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_EventScript_Statue2::
	msgbox OlivineCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Gym_Text_GymStatue:
	.string "מכון הפוקימון של העיר אוליבין$"

OlivineCity_Gym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיר אוליבין\p"
	.string "המאמנים המוסמכים של ג'סמין:\n"
	.string "{PLAYER}$"

OlivineCity_Gym_EventScript_Jasmine_Trade::
	goto_if_set FLAG_OLIVINE_GYM_NPC_TRADE_COMPLETED, OlivineCity_Gym_EventScript_JasmineTradeCompleted
	setvar VAR_0x8005, INGAME_TRADE_STEELIX
	specialvar VAR_0x8009, GetInGameTradeSpeciesInfo
	msgbox OlivineCity_Gym_Text_JasmineWantToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, OlivineCity_Gym_EventScript_JasmineDeclineTrade
	chooseboxmon SELECT_PC_MON_TRADE
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, OlivineCity_Gym_EventScript_JasmineDeclineTrade
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	msgbox OlivineCity_Gym_Text_JasmineTakeCare, MSGBOX_DEFAULT
	setflag FLAG_OLIVINE_GYM_NPC_TRADE_COMPLETED
	release
	end

OlivineCity_Gym_EventScript_JasmineDeclineTrade::
	msgbox OlivineCity_Gym_Text_JasmineDeclineTrade, MSGBOX_DEFAULT
	release
	end

OlivineCity_Gym_EventScript_JasmineTradeCompleted::
	msgbox OlivineCity_Gym_Text_JasmineTradeCompleted, MSGBOX_DEFAULT
	release
	end

OlivineCity_Gym_Text_JasmineWantToTrade:
	.string "…אממ, {PLAYER}…\n"
	.string "יש לי בקשה ממך.\p"
	.string "גידלתי את הסטיליקס הזה\n"
	.string "מאז שהיה אוניקס קטן.\p"
	.string "אבל אני חושבת שראסטי יהיה\n"
	.string "מאושר יותר עם מאמן כמוך.\p"
	.string "תסכים להחליף אחד\n"
	.string "מהפוקימונים שלך בראסטי שלי?$"

OlivineCity_Gym_Text_JasmineTakeCare:
	.string "…תודה.\n"
	.string "בבקשה, תהיה טוב לראסטי…$"

OlivineCity_Gym_Text_JasmineDeclineTrade:
	.string "…אה… זה בסדר.\n"
	.string "אני מבינה…$"

OlivineCity_Gym_Text_JasmineTradeCompleted:
	.string "…מה שלום ראסטי?\n"
	.string "אני מקווה שאתה מטפל בו היטב…$"
