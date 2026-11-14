Route10_PowerPlantEntrance_hns_MapScripts::
	.byte 0

Route10_PowerPlantEntrance_EventScript_Cop::
	lock
	faceplayer
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 2, Route10_PowerPlantEntrance_EventScript_CopDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 3, Route10_PowerPlantEntrance_EventScript_CopDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 4, Route10_PowerPlantEntrance_EventScript_CopDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 5, Route10_PowerPlantEntrance_EventScript_CopDuringRocket
	goto_if_eq VAR_KANTO_ROCKET_STORY_STATE, 6, Route10_PowerPlantEntrance_EventScript_CopDuringRocket
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 3, Route10_PowerPlantEntrance_EventScript_CopAfterDone
	msgbox Route10_PowerPlantEntrance_Text_Officer1AThiefBrokeIn, MSGBOX_DEFAULT
	closemessage
	end

Route10_PowerPlantEntrance_EventScript_CopDuringRocket::
	lock
	faceplayer
	msgbox Route10_PowerPlantEntrance_Text_Officer1CeruleanShadyCharacter, MSGBOX_DEFAULT
	msgbox Route10_PowerPlantEntrance_Text_Officer1CouldIAskForYourCooperation, MSGBOX_DEFAULT
	closemessage
	end

Route10_PowerPlantEntrance_EventScript_CopAfterDone::
	lock
	faceplayer
	msgbox Route10_PowerPlantEntrance_Text_Officer1HaveToBeefUpSecurity, MSGBOX_DEFAULT
	closemessage
	end

Route10_PowerPlantEntrance_EventScript_Engineer1::
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantEntrance_EventScript_Engineer1Done
	msgbox Route10_PowerPlantEntrance_Text_Engineer1SomeoneStoleAPart, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_EventScript_Engineer1Done::
	msgbox Route10_PowerPlantEntrance_Text_Engineer1GeneratorUpAndRunning, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_EventScript_Engineer2::
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantEntrance_EventScript_Engineer2Done
	msgbox Route10_PowerPlantEntrance_Text_Engineer2PowerPlantUpAndRunning, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_EventScript_Engineer2Done::
	msgbox Route10_PowerPlantEntrance_Text_Engineer2GeneratorIsRunningAgain, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_EventScript_Cop2::
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantEntrance_EventScript_Cop2Done
	msgbox Route10_PowerPlantEntrance_Text_Officer2ManagerHasBeenSadAndFurious, MSGBOX_NPC
	end
Route10_PowerPlantEntrance_EventScript_Cop2Done::
	msgbox Route10_PowerPlantEntrance_Text_Officer2ManagerHasBeenCheerful, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_EventScript_Engineer3::
	goto_if_ge VAR_KANTO_ROCKET_STORY_STATE, 7, Route10_PowerPlantEntrance_EventScript_Engineer3Done
	msgbox Route10_PowerPlantEntrance_Text_Engineer4MagnetTrainConsumesElectricity, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_EventScript_Engineer3Done::
	msgbox Route10_PowerPlantEntrance_Text_Engineer4WeCanGetMagnetTrainRunning, MSGBOX_NPC
	end

Route10_PowerPlantEntrance_Trigger_Cop::
	lock
	playse SE_POKENAV_CALL
	applymovement2 LOCALID_POWERPLANT_COP, Common_Movement_ExclamationMark
	waitse
	applymovement2 LOCALID_POWERPLANT_COP, Route10_PowerPlantEntrance_Movement_WalkToPlayer
	waitmovement 0
	turnobject LOCALID_POWERPLANT_ENGINEER, DIR_SOUTH
	msgbox Route10_PowerPlantEntrance_Text_Officer1CeruleanShadyCharacter, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_POWERPLANT_COP, DIR_WEST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	delay 30
	msgbox Route10_PowerPlantEntrance_Text_Officer1CouldIAskForYourCooperation, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_POWERPLANT_COP, Route10_PowerPlantEntrance_Movement_WalkBack
	waitmovement 0
	setvar VAR_KANTO_ROCKET_STORY_STATE, 2
	clearflag FLAG_HIDE_CERULEAN_GYM_ROCKET
	release
	end

Route10_PowerPlantEntrance_Movement_WalkToPlayer:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route10_PowerPlantEntrance_Movement_WalkBack:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	face_down
	step_end

Route10_PowerPlantEntrance_Text_Officer1AThiefBrokeIn:
	.string "גנב פרץ למפעל החשמל…\p"
	.string "לאן העולם הזה הולך?$"

Route10_PowerPlantEntrance_Text_Officer1CeruleanShadyCharacter:
	.string "בדיוק קיבלתי הודעה מסרוליאן.\p"
	.string "נראה שדמות חשודה מסתובבת\n"
	.string "שם באזור.$"

Route10_PowerPlantEntrance_Text_Officer1CouldIAskForYourCooperation:
	.string "אפשר לבקש את\n"
	.string "שיתוף הפעולה שלך?$"

Route10_PowerPlantEntrance_Text_Officer1HaveToBeefUpSecurity:
	.string "נצטרך לתגבר\n"
	.string "את האבטחה שלנו.$"

Route10_PowerPlantEntrance_Text_Engineer1SomeoneStoleAPart:
	.string "מישהו גנב חלק חיוני\n"
	.string "לגנרטור.\p"
	.string "בלעדיו, הגנרטור החדש\n"
	.string "חסר תועלת!$"

Route10_PowerPlantEntrance_Text_Engineer1GeneratorUpAndRunning:
	.string "הגנרטור עובד כמו שצריך.\n"
	.string "הוא מייצר חשמל בשפע.$"

Route10_PowerPlantEntrance_Text_Engineer2PowerPlantUpAndRunning:
	.string "מפעל החשמל הזה היה נטוש בעבר.\p"
	.string "החזרנו אותו לפעולה כדי לספק\n"
	.string "חשמל לרכבת המגנטית.$"

Route10_PowerPlantEntrance_Text_Engineer2GeneratorIsRunningAgain:
	.string "הגנרטור פועל שוב!$"

Route10_PowerPlantEntrance_Text_Officer2ManagerHasBeenSadAndFurious:
	.string "מנהל מפעל החשמל נמצא\n"
	.string "בחדר האחורי עם הגנרטור.\p"
	.string "אבל מאז שמישהו הרס את הגנרטור,\n"
	.string "הוא גם עצוב וגם זועם…$"

Route10_PowerPlantEntrance_Text_Officer2ManagerHasBeenCheerful:
	.string "מאז שהגנרטור תוקן,\n"
	.string "המנהל במצב רוח מצוין.$"

Route10_PowerPlantEntrance_Text_Engineer4MagnetTrainConsumesElectricity:
	.string "הרכבת המגנטית צורכת המון חשמל.\p"
	.string "היא לא יכולה לנסוע אם\n"
	.string "הגנרטור החדש לא פועל.$"

Route10_PowerPlantEntrance_EventScript_Lorenzo::
	lock
	faceplayer
	goto_if_set FLAG_POWERPLANT_NPC_TRADE_COMPLETED, Route10_PowerPlantEntrance_EventScript_TradeCompleted
	ingame_trade INGAME_TRADE_MAGNETON, Route10_PowerPlantEntrance_Text_WantToTrade, Route10_PowerPlantEntrance_EventScript_DeclineTrade, Route10_PowerPlantEntrance_EventScript_NotRequestedMon, Route10_PowerPlantEntrance_Text_TakeCare
	setflag FLAG_POWERPLANT_NPC_TRADE_COMPLETED
	release
	end

Route10_PowerPlantEntrance_EventScript_DeclineTrade::
	msgbox Route10_PowerPlantEntrance_Text_DeclineTrade, MSGBOX_DEFAULT
	release
	end

Route10_PowerPlantEntrance_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox Route10_PowerPlantEntrance_Text_NotRequestedMon, MSGBOX_DEFAULT
	release
	end

Route10_PowerPlantEntrance_EventScript_TradeCompleted::
	msgbox Route10_PowerPlantEntrance_Text_TradeCompleted, MSGBOX_DEFAULT
	release
	end

Route10_PowerPlantEntrance_Text_WantToTrade:
	.string "אני עובד כאן במפעל החשמל.\n"
	.string "המגנטון שלי ואני שותפים כבר שנים.\p"
	.string "אבל תמיד רציתי\n"
	.string "{STR_VAR_1}.\p"
	.string "מה דעתך להחליף אחד\n"
	.string "ב{STR_VAR_2} שלי?$"

Route10_PowerPlantEntrance_Text_TakeCare:
	.string "תודה!\n"
	.string "תשמור טוב על מגי בשבילי!$"

Route10_PowerPlantEntrance_Text_DeclineTrade:
	.string "לא? חבל.\n"
	.string "המגנטון שלי ממש חרוץ.$"

Route10_PowerPlantEntrance_Text_NotRequestedMon:
	.string "הממ, זה לא {STR_VAR_1}.\n"
	.string "לא לזה התכוונתי.$"

Route10_PowerPlantEntrance_Text_TradeCompleted:
	.string "מה שלום מגי?\n"
	.string "הוא מת על שדות מגנטיים!$"

Route10_PowerPlantEntrance_Text_Engineer4WeCanGetMagnetTrainRunning:
	.string "יופי! סוף סוף נוכל להפעיל\n"
	.string "שוב את הרכבת המגנטית.$"
