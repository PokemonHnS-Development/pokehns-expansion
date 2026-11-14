BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "Please find a partner from out of\n"
	.string "the TRAINERS gathered here.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "{PLAYER}, you have not found a partner\n"
	.string "for your tag team.\p"
	.string "Would you like to quit looking and\n"
	.string "return to the reception counter?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "Then, please find a partner from\n"
	.string "the TRAINERS gathered here.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Thank you for choosing a partner.\p"
	.string "I will now show you to your\n"
	.string "MULTI BATTLE ROOM.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "I'm {STR_VAR_1}'s no. {STR_VAR_2} apprentice.\n"
	.string "You can call me {STR_VAR_3}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "On {STR_VAR_1}'s advice, I brought\n"
	.string "one {STR_VAR_3} with {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Please, let me join you as a tag team.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "Thank you!\n"
	.string "I'll go register right now.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "I really wanted to form a tag team\n"
	.string "with you, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "I am {STR_VAR_1}'s no. {STR_VAR_2} apprentice.\n"
	.string "My name is {STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "I got advice from {STR_VAR_1} and chose\n"
	.string "one {STR_VAR_3} with {STR_VAR_2} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "one {STR_VAR_2} with {STR_VAR_1}.\p"
	.string "Please, let's form a tag team!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "Thank you very much!\n"
	.string "I'll be done with registration quickly!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, I was hoping that I could\n"
	.string "partner up with you…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "אממ, קוראים לי {STR_VAR_3}.\p"
	.string "אני חניך של {STR_VAR_1},\n"
	.string "מספר {STR_VAR_2}.\p"
	.string "סניף…\p"
	.string "סליחה!\n"
	.string "המתח הזה גורם לי לבכות…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "בעצת {STR_VAR_3}, יש לי\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "סניף…\n"
	.string "בבקשה, בבקשה, בוא נהיה צוות!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "אה, באמת? אתה מסכים?\n"
	.string "מדהים! אדיר! אוווווו!\p"
	.string "אוי… סליחה…\n"
	.string "אני כל כך שמח שאני בוכה…\p"
	.string "אלך להירשם מיד.\n"
	.string "בבקשה, אל תלך לשום מקום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "אוי, א-אבל…\n"
	.string "היק… ואאאאה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "היי! אני {STR_VAR_3}, חניך של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "בהמלצת {STR_VAR_3} הרכבתי צוות:\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1},\n"
	.string "זה מה שיש לי! מגניב, נכון?\p"
	.string "אז קדימה!\n"
	.string "בוא נקים צוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "יש! מעולה!\n"
	.string "טוב, אני הולך להירשם, בסדר?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "אוף, למה?\n"
	.string "רציתי שנהיה צוות, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "אני {STR_VAR_3}!\p"
	.string "חניך מספר {STR_VAR_2} של\n"
	.string "{STR_VAR_1}, שכולם מכירים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "ביקשתי עצה מ{STR_VAR_3}.\p"
	.string "יש לי אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1},\n"
	.string "זה הזוג שלי.\p"
	.string "בבקשה, תצטרף אליי\n"
	.string "לצוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "תודה!\n"
	.string "אני רושם אותנו מיד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "{PLAYER}, קיוויתי שנהיה\n"
	.string "ביחד בצוות זוגי…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "אממ… אני באמת שמחה שמצאת\n"
	.string "זמן לדבר איתי.\p"
	.string "אני {STR_VAR_3}, חניכה של\n"
	.string "{STR_VAR_1}, מס' {STR_VAR_2}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "קיבלתי עצה מ{STR_VAR_3}.\n"
	.string "אני מאוד אסירת תודה על כך.\p"
	.string "יש לי צוות של {STR_VAR_2}\n"
	.string "עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\n"
	.string "אני יודעת שזו בקשה גדולה…\p"
	.string "אני לא חושבת שתסכים,\n"
	.string "אבל אפשר להצטרף אליך כשותפה?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "באמת? אני לא מאמינה!\n"
	.string "לא מאמינה שתיתן לי להצטרף!\p"
	.string "א… אני לא אאכזב אותך!\p"
	.string "אממ… אם זה באמת בסדר,\n"
	.string "אלך להירשם ברגע זה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "אה…\n"
	.string "לא חשבתי שאני מספיק טובה…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "היי, אני {STR_VAR_3}, חניכה של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "לפי {STR_VAR_3}, כדאי לי\n"
	.string "להרכיב את הצוות הזה:\p"
	.string "אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "ו{STR_VAR_2} שיודע\n"
	.string "להשתמש ב{STR_VAR_1}.\p"
	.string "לא רע, נכון?\n"
	.string "רוצה שאצטרף לצוות שלך?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "טוב, שמחה להצטרף!\n"
	.string "מקווה שלא תהרוס לי את העניינים!\p"
	.string "אני הולכת להירשם עכשיו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "מה? למה דחית אותי?\n"
	.string "אין לך שום הבנה באנשים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "אני {STR_VAR_3}, ואני טריאתלט.\p"
	.string "אני עסוק כל יום בריצה,\n"
	.string "באימונים ובראפ.\p"
	.string "ובמקרה אני גם חניך של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "זו ההמלצה של {STR_VAR_3}:\p"
	.string "אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "השקעתי הרבה בגידול שלהם,\n"
	.string "למרות שאני עסוק.\p"
	.string "בוא נקים צוות זוגי\n"
	.string "וננסה את כוחנו!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "תודה, ככה צריך!\n"
	.string "רק רגע, אני הולך להירשם, טוב?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "פיניתי זמן מהלו”ז העמוס שלי\n"
	.string "כדי להיות כאן! נו באמת!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "היי!\n"
	.string "מה נשמע?\p"
	.string "אני {STR_VAR_3}, חניכה של\n"
	.string "{STR_VAR_1}, מס' {STR_VAR_2}.\p"
	.string "נעים מאוד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "תקשיב, תקשיב! אתה חייב לשמוע על\n"
	.string "הפוקימונים בהמלצת {STR_VAR_3}.\p"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\n"
	.string "כמובן שגידלתי אותם מצוין!\p"
	.string "אז, רוצה שנהיה צוות?\n"
	.string "אני בטוחה שזה יהיה שילוב מעולה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "יש, נראה לי שיהיה כיף!\n"
	.string "אני הולכת להירשם!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "אוף, אתה מרושע!\n"
	.string "אני באה עם המלצות, שתדע.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "אם יורשה לי, אציג את עצמי.\n"
	.string "שמי {STR_VAR_3}.\p"
	.string "אני משמשת כחניכה של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "ביקשתי עצה נבונה מ{STR_VAR_3}\n"
	.string "וגידלתי את הצוות שלי:\p"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "אנא, תסכים להקים איתי צוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "הו… אני מאושרת!\n"
	.string "אני מבטיחה לתת את המיטב!\p"
	.string "כמובן שאני ארשום אותנו!\n"
	.string "אנא, רק רגע!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "קיוויתי להצטרף אליך,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "אייי! דיברת איתי!\n"
	.string "א… אני מאושרת!\p"
	.string "אני {STR_VAR_3}! חניכה של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "בעצת {STR_VAR_3},\n"
	.string "אימנתי את הצוות הזה:\p"
	.string "אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "בבקשה, תגשים לי משאלה?\n"
	.string "אני רוצה להיות השותפה שלך לצוות!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "אייי! א… הראש שלי מסתחרר!\n"
	.string "תודה רבה רבה!\p"
	.string "אלך לרשום אותנו מיד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "ואאאה! אין לך שום רחמים?\n"
	.string "אבל זה רק הופך אותך למגניב יותר…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "יי-הא! אני חניך של {STR_VAR_1},\n"
	.string "מספר {STR_VAR_2}!\p"
	.string "קוראים לי {STR_VAR_3}, שלום, שלום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "המנטור שלי, {STR_VAR_3},\n"
	.string "המליץ על הצוות הזה:\p"
	.string "אשף {STR_VAR_1} אחד -\n"
	.string "{STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "ועוד אשף {STR_VAR_1} אחד -\n"
	.string "{STR_VAR_2}.\p"
	.string "שווה, מה?\n"
	.string "תהיה השותף שלי, נכון?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "יופי, מצוין!\n"
	.string "אסדר את הרישום מהר!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "גוואאאה!\n"
	.string "איזה מחשבן אתה, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "היי! צרה גדולה! היום הוא\n"
	.string "היום האחרון של מגדל הקרב!\p"
	.string "… … … … … …\n"
	.string "סתם, צחקתי!\p"
	.string "כולם קוראים לי {STR_VAR_3}, וגם אני!\n"
	.string "אני החניך ה-1,000 של {STR_VAR_1}!\p"
	.string "בעצם, אני מספר {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "קיבלתי עצה מ{STR_VAR_3}.\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\n"
	.string "יש לי עשרה מכל סוג!\p"
	.string "בעצם, רק אחד מכל סוג!\p"
	.string "נו, מה אתה אומר?\n"
	.string "רוצה לנסות איתי קרבות צוות?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "יששש!\n"
	.string "אתן לך פוקימון כאות תודה!\p"
	.string "סתם, צחקתי! אבל אני באמת הולך\n"
	.string "לעשות את הרישום, בסדר?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "אוי, איזה קור לב! בגלל זה\n"
	.string "אצטרך להרוס את מגדל הקרב!\p"
	.string "ברור שלא באמת!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "יו, אני מקפיץ ומתפרע,\n"
	.string "את הפוקימונים אני מניע!\p"
	.string "אני {STR_VAR_3}, מלח וראפר,\n"
	.string "ולא סתם עוד בכיין מהכפר!\p"
	.string "חניך של {STR_VAR_1} אני,\n"
	.string "מספר {STR_VAR_2}, אל תזלזל בי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "בעצת {STR_VAR_3} הלכתי,\n"
	.string "צוות לתפארת הרכבתי!\p"
	.string "אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}!\p"
	.string "מפגש כזה צריך לחגוג,\n"
	.string "בניצחון של צוות, בלי לדאוג!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "היי, היי, הסגנון שלך מעולה!\n"
	.string "אלך לרשום אותנו, בלי שום שאלה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "אוי, היי, {PLAYER}, זה קר ולא יפה!\n"
	.string "אם מותר לי לומר את זה בחוצפה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "יפי-יאהו!\n"
	.string "אל תברח! סתם עשיתי שמח!\p"
	.string "מה המצב! אני {STR_VAR_3}, חניך של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "קיבלתי מ{STR_VAR_3} הוראות.\p"
	.string "אז יש לי אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "את שניהם בחרתי, אז מה תגיד?\n"
	.string "קדימה, תשמח אותי מיד!\p"
	.string "בבקשה, אני מתחנן!\n"
	.string "תן לי להצטרף, אל תשאיר אותי מסכן!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "יה-הא! המזל איתי!\n"
	.string "זה משמח אותי עד אין די!\p"
	.string "לפני שנצא לקרב הסוער,\n"
	.string "אלך להירשם, בלי לאחר!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "אתה דוחה אותי? איזה מבאס!\n"
	.string "{PLAYER}, עכשיו אני כועס!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "כחח!\p"
	.string "אה, סליחה, אני מצונן.\n"
	.string "אבל הפוקימונים שלי בסדר.\p"
	.string "שמי {STR_VAR_3}. כחח! אני חניך של\n"
	.string "{STR_VAR_1}, מספר {STR_VAR_2}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "לקחתי ללב את העצה של {STR_VAR_3}\n"
	.string "והרכבתי צוות:\p"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "אימנתי אותם כל יום,\n"
	.string "גם ברוח ובגשם.\p"
	.string "בגלל זה הצטננתי,\n"
	.string "נראה לי.\p"
	.string "זה מי שאני.\n"
	.string "רוצה להיות השותף שלי לצוות?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "תודה, אני מעריך את זה!\n"
	.string "כחח, כחח!\p"
	.string "רגע, אני הולך להירשם.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "אה, אתה לא רוצה?\n"
	.string "{PLAYER}, נראה לי שהיינו זוג טוב.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "אה, שלום!\n"
	.string "זה מורט עצבים.\p"
	.string "אני {STR_VAR_3}, חניך מספר\n"
	.string "{STR_VAR_2} של {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "לפי {STR_VAR_3}, זה יהיה צוות טוב:\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "אני קצת נבוך לבקש,\n"
	.string "אבל תיתן לי להצטרף אליך?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "אוי, וואו, תודה!\n"
	.string "אני מתבייש, אבל אעשה כמיטב יכולתי!\p"
	.string "אלך לסדר את הרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "אוי, בבקשה אל תסרב!\n"
	.string "אני כבר נבוך מספיק…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "שמי {STR_VAR_3}, ואין זה שקר.\p"
	.string "אני חניך של {STR_VAR_1},\n"
	.string "מספר {STR_VAR_2}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "בהמלצת {STR_VAR_3} הרכבתי צוות.\p"
	.string "מאחר שהעצה נשמעה כנה,\n"
	.string "החלטתי להביא איתי\p"
	.string "אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "ואחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "אם אפשר, הייתי רוצה שתקבל אותי\n"
	.string "כשותף שלך לצוות.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "באמת תקבל אותי?\n"
	.string "אחרת זה היה נורא מדי.\p"
	.string "אבל מאחר שהסכמת, הכול בסדר.\n"
	.string "אלך לרשום את שנינו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "הממ? ומדוע שתסרב?\n"
	.string "זו אמורה להיות בדיחה?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "אני {STR_VAR_1}, ואני עלמה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "מה שיש לי זה {STR_VAR_2}\n"
	.string "שמשתמש ב{STR_VAR_1}, ועוד$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_2} שמשתמש\n"
	.string "ב{STR_VAR_1}.\p"
	.string "אלה הפוקימונים שאיתי.\n"
	.string "תהיה השותף שלי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "תודה!\n"
	.string "אני הולכת לעשות את הרישום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "אתה לא רוצה להיות השותף שלי?\n"
	.string "עוד תתחרט על זה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "שלום!\p"
	.string "אני הצעיר {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "רוצה לדעת מה יש לי?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "תהיה השותף שלי לצוות,\n"
	.string "נכון?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "יש!\n"
	.string "אני הולך להירשם, טוב?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "אוף! אם היית מקים צוות זוגי עם\n"
	.string "הפוקימונים שלי, לא היו עוצרים אותנו!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "יאהו!\n"
	.string "אני המטייל {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "יודע מה יש לי? אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}!\p"
	.string "נשמע טוב, הא?\n"
	.string "רוצה להקים צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "יאהו!\n"
	.string "אז אני הולך לעשות את הרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "הייתי שמח להילחם\n"
	.string "כשאתה לצידי.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "שלום!\n"
	.string "אני {STR_VAR_1}, ואני יפהפייה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "יודע מה גידלתי?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "מה דעתך?\n"
	.string "רוצה שנקים צוות זוגי ביחד?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "נפלא!\n"
	.string "אסדר את הרישום עכשיו!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "איזו אכזבה!\p"
	.string "שנינו ביחד - היינו יכולים\n"
	.string "להיות הכי טובים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "יו!\p"
	.string "יודע מי אני?\n"
	.string "אני {STR_VAR_1} הדייג!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "יש איתי צוות: אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "ואחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "נו, מה אתה אומר?\n"
	.string "תילחם לצידי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "טוב, טוב!\n"
	.string "תסמוך עליי!\p"
	.string "אני הולך לרשום אותנו עכשיו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "ודווקא היינו זוג מושלם…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "נעים להכיר.\n"
	.string "שמי {STR_VAR_1}, ואני גברת.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "מלווה אותי צוות של\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "אני מקווה שאמצא חן בעיניך,\n"
	.string "שכן ברצוני שתהיה שותפי.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "אני מודה לך מעומק הלב.\n"
	.string "אני אטפל ברישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "אני בטוחה שתצטער על כך\n"
	.string "שלא בחרת בי כשותפה.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "אני הטריאתלטית {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "מה שיש לי…\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\n"
	.string "זה הזוג שלי!\p"
	.string "נו, בבקשה?\n"
	.string "תקים איתי צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "וואו, תודה!\n"
	.string "אני הולכת להירשם בדלפק.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "שנינו ביחד היינו\n"
	.string "קשוחים, בטוח!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "היי!\n"
	.string "אני לוכד החרקים {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "תראה מה יש לי!\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "אז תקשיב!\n"
	.string "רוצה להקים צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "סגור!\p"
	.string "אני הולך לסדר את הרישום\n"
	.string "בדלפק.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "אוף, הפוקימונים שלי אדירים.\n"
	.string "מקווה שלא תתחרט על זה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "יום טוב!\n"
	.string "אני התלמיד {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "אני מגדל {STR_VAR_2}\n"
	.string "שמשתמש ב{STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "ו{STR_VAR_2} שמשתמש\n"
	.string "ב{STR_VAR_1}.\p"
	.string "לא רע בכלל, נכון?\n"
	.string "תרצה להקים איתי צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "תודה רבה!\n"
	.string "אני אדאג לרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "חבל…\p"
	.string "קיוויתי שאוכל ללמוד\n"
	.string "ממך בתור השותף שלך…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "יו! אגיד לך מי אני!\n"
	.string "אני הילד העשיר {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "נחש מה יש לי!\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "אני מוכן להציע לך את ההזדמנות\n"
	.string "להיות איתי בצוות זוגי.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "צעד חכם!\p"
	.string "אסיים את תהליך הרישום\n"
	.string "במהירות!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "אתה דוחה דווקא אותי?\n"
	.string "בטוח שתתחרט על ההחלטה הזאת!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "הייאה!\n"
	.string "אני החגורה השחורה {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "כבני לוויה, יש לי {STR_VAR_2}\n"
	.string "שמשתמש ב{STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "ו{STR_VAR_2} שמשתמש\n"
	.string "ב{STR_VAR_1}.\p"
	.string "אנא, הגשם את משאלתי!\n"
	.string "הרשה לי להיות שותפך לצוות!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "הייאה!\n"
	.string "אלך להירשם לאלתר!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "הבנתי… אני מקווה להזדמנות\n"
	.string "בפעם הבאה שניפגש…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "היי!\n"
	.string "אני {STR_VAR_1}, ואני ילדת גלגל ים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "אספר לך מה יש לי.\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\n"
	.string "אפשר בבקשה להיות בצוות הזוגי שלך?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "תודה!\n"
	.string "אני הולכת לרשום אותנו עכשיו!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "אם היינו שותפים, היינו\n"
	.string "יכולים להיות כל כך חזקים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "שלום לך…\n"
	.string "אני מטורפת הכישוף {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "אני נושאת איתי אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "יחד עם אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}…\p"
	.string "אני מתחננת…\n"
	.string "הצטרף אליי לצוות זוגי…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "אני מודה לך…\n"
	.string "אני ארשום אותנו…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "כל כך השתוקקתי להצטרף אליך…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "מה שלומך? אני {STR_VAR_1},\n"
	.string "ואני מגדל פוקימון!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "אני מגדל שניים ממש טובים!\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "מה אתה אומר?\n"
	.string "בא לך להקים איתי צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "תודה רבה לך!\p"
	.string "אני הולך לטפל בעניין הרישום,\n"
	.string "אז חכה כאן!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "כל כך חיכיתי להיות\n"
	.string "השותף שלך…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "שלום לך!\n"
	.string "אני הטריאתלטית {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "רוצה לדעת עם מי אני רצה?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "נו?\n"
	.string "רוצה להיות איתי בצוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "כל הכבוד!\p"
	.string "אזדרז ואסדר את כל הרישום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "שנינו היינו יכולים להיות הכי טובים.\n"
	.string "ממש חבל…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "היי! קוראים לי {STR_VAR_1}!\n"
	.string "אני טריאתלט!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "אני רץ עם הצוות העמיד שלי:\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "לא רע, נכון?\n"
	.string "כדאי שנהיה יחד בצוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "מעולה!\n"
	.string "אני רץ להירשם כהרף עין!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "ממש רציתי להילחם לצדך\n"
	.string "בתור שותף לצוות…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "אני {STR_VAR_1}, נערת קרב!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "אני מחשלת פוקימון שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}!\p"
	.string "אהבת את השילוב?\n"
	.string "מה דעתך שנחבור יחד?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "וואו, תודה!\p"
	.string "אני מסדרת את הרישום\n"
	.string "כבר עכשיו!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "חשבתי שאיתך נוכל להקים\n"
	.string "את הצוות הזוגי האולטימטיבי…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "אני הטריאתלט {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "אני מסתובב עם {STR_VAR_2} אחד\n"
	.string "שיודע להשתמש ב{STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "נוכל להיות צוות זוגי.\n"
	.string "יהיה נהדר, לא?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "תודה!\p"
	.string "אני הולך לרשום אותנו,\n"
	.string "ומיד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "אוף, חבל. היינו יכולים להיות\n"
	.string "הצוות הזוגי הכי קשוח פה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "אני?\n"
	.string "אני ילד גלגל הים {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "מה יש לי איתי?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "נו?\n"
	.string "תהיה איתי בצוות, נכון?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "אוקיי!\p"
	.string "אני הולך להירשם!\n"
	.string "ביחד נהיה מצוינים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "הפוקימונים שלי חזקים, בטוח…\n"
	.string "חבל שלא רצית להצטרף אליי.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "יה-היי!\n"
	.string "תקראו לי הגיטריסט {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "הנה הפמליה שלי!\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "יה-היי! די פרוע, הא?\n"
	.string "חייבים לנגן דואט כצוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "יה-היי! מעולה!\n"
	.string "אני הולך לסדר עכשיו את עניין הרישום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "הפוקימונים שלי מרעידים את הבמה!\n"
	.string "עוד תצטער, אני אומר לך!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "נעים מאוד להכיר.\n"
	.string "אני {STR_VAR_1}, ג'נטלמן.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "מלווה אותי פוקימון נאמן שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "האם אוכל לבקש ממך להצטרף אליי\n"
	.string "להסדר של שותפות בצוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "אה, אני מודה לך על האמון.\n"
	.string "אדאג להשלים את הרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "זה מצער ביותר…\p"
	.string "אצפה להזדמנות הבאה…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "שלום, אני {STR_VAR_1},\n"
	.string "ואני פוקיפאן.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "יש איתי עכשיו {STR_VAR_2} אחד\n"
	.string "שיודע את המהלך {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "מוצא חן בעיניך?\n"
	.string "מה דעתך שנהיה שותפים לצוות?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "תודה!\n"
	.string "אני אדאג לרישום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "הפוקימונים שלי מהשורה הראשונה…\n"
	.string "חבל שלא ידעת להעריך את זה.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "המ!\n"
	.string "אני {STR_VAR_1}, ומומחה אני!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "הפוקימונים שחישלתי הם\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "מה תאמר על צוות זוגי איתי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "המ! ארשום אותנו מיד!\n"
	.string "הבה ניתן שנינו את המיטב!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "אני מקווה שהבחירה שלך\n"
	.string "אכן נכונה…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "שלום, שלום.\n"
	.string "אני {STR_VAR_1}, ואני מומחית.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "גידלתי את הפוקימונים שלי ביסודיות.\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1} -\n"
	.string "אלה הפוקימונים שלי.\p"
	.string "לא היית רוצה להצטרף אליי לצוות?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "טוב, טוב.\n"
	.string "אדאג לרישום מיד.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "אולי נוכל להקים צוות\n"
	.string "בפעם הבאה שניפגש.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "אני מאלף הדרקונים {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "הצוות שחישלתי הוא\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "נו, מה דעתך?\n"
	.string "רוצה להיות השותף שלי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "אוקיי, אתן את המיטב!\n"
	.string "אני הולך להירשם עכשיו, בסדר?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "קשה למצוא שותפים\n"
	.string "קשוחים ממני!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "אני מגדל הציפורים {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "אילו פוקימונים יש לי?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "לא נראה לך שנהיה\n"
	.string "צוות זוגי לא רע?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "מעולה, תודה!\n"
	.string "אני אדאג לרישום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "אני והפוקימונים שלי חזקים.\n"
	.string "איזו אכזבה.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "אני נער הנינג'ה {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "צוות הפוקימונים שלי כולל\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "קדימה, נהיה ביחד בצוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "יש!\n"
	.string "אני רץ להירשם!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "עוד תתחרט שהפוקימונים הקשוחים\n"
	.string "שלי לא יהיו לצדך!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "שלום!\n"
	.string "אני {STR_VAR_1}, גברת שמשייה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "כעת מלווים אותי ה{STR_VAR_2} שלי\n"
	.string "שמשתמש ב{STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "ו{STR_VAR_2} שמשתמש\n"
	.string "ב{STR_VAR_1}.\p"
	.string "הם נחמדים, נכון?\n"
	.string "תרצה להצטרף אלינו לצוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "תודה רבה!\p"
	.string "אלך להירשם בדלפק.\n"
	.string "שלא נאכזב זה את זה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "הפוקימונים שלי חזקים להפליא.\n"
	.string "איזו אכזבה…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "שלום.\n"
	.string "אני {STR_VAR_1}, ואני מטורף חרקים!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "מצאתי את הפוקימונים שלי, כן.\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1} -\n"
	.string "אותם מצאתי.\p"
	.string "אפשר לעניין אותך\n"
	.string "בהקמת צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "אוקיי!\n"
	.string "הבנתי!\p"
	.string "הרישום לא ייקח לי הרבה זמן!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "עם הפוקימונים שמצאתי,\n"
	.string "לא היינו מפסידים…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "אהוי!\n"
	.string "אני המלח {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "אראה לך במה אני הכי גאה!\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "בטח שלא תסרב לי.\n"
	.string "נהיה צוות, נכון?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "לא ציפיתי לפחות מזה!\n"
	.string "אני הולך להירשם עכשיו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "היינו סוחפים את היריבים\n"
	.string "כמו סערה! חבל!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "היי, אני {STR_VAR_1}.\n"
	.string "אני אספן.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "פניני האוסף שלי הם\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "נהדר, הא?\n"
	.string "כדאי שנהיה ביחד בצוות.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "יש!\p"
	.string "טוב, בלי לבזבז זמן.\n"
	.string "אני הולך לרשום את שנינו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "נו, זה מעצבן.\n"
	.string "לא הערכת את הפוקימונים שלי.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "אהלן, אני {STR_VAR_1}.\n"
	.string "אני שומר פוקימון.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "עושים לי חברה פוקימון שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "לא נראה לך שנהיה\n"
	.string "צוות זוגי מרשים?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "מצוין!\n"
	.string "אטפל ברישום עכשיו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "בפעם הבאה, תבחר בפוקימונים שלי,\n"
	.string "טוב?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "קוראים לי {STR_VAR_1}.\n"
	.string "אני שומרת פוקימון!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "אספר לך על הצוות שלי. יש לי\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "מה דעתך להקים צוות זוגי\n"
	.string "עם החבורה הקטנה שלי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "נהיה במיטבנו!\n"
	.string "אסדר את הרישום מהר!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "אני מקווה שתבחר בפוקימונים שלי\n"
	.string "בפעם הבאה.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "נעים מאוד. אני {STR_VAR_1}.\n"
	.string "אני רואה בעצמי גברת ניחוח.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "אני מטיילת עם {STR_VAR_2} אחד\n"
	.string "שמשתמש ב{STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "ו{STR_VAR_2} שמשתמש\n"
	.string "ב{STR_VAR_1}.\p"
	.string "אני מקווה שהם מוצאים חן בעיניך.\n"
	.string "תרצה להיות השותף שלי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "הסכמתך מכבדת אותי.\n"
	.string "אלך להירשם ברגע זה ממש.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "יהיה נפלא אם נוכל להקים\n"
	.string "צוות זוגי בפעם הבאה שניפגש.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "רוצה לדעת מי אני?\n"
	.string "אני {STR_VAR_1}, מטורף החורבות!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "הפוקימונים שיש לי איתי הם\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "מסקרן, הא?\n"
	.string "מה דעתך שנהיה שותפים?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "החלטה נבונה!\n"
	.string "אלך לסדר את טופסי הרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "הממ…\n"
	.string "אני חושב שהפוקימונים שלי חזקים…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "אני {STR_VAR_1}, מאמן-על!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "הפוקימונים שיש לי כרגע הם\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\n"
	.string "מגניב, הא?\p"
	.string "לא נראה לך שיהיה די מגניב\n"
	.string "אם נקים צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "מגניב!\n"
	.string "אסדר את הרישום כהרף עין!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "חשבתי שנהיה פשוט\n"
	.string "הצוות הטוב ביותר אי פעם.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "אני {STR_VAR_1}, מאמנת-על!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "בצוות שגידלתי יש\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "נשמע טוב?\n"
	.string "מה דעתך שנהיה שותפים לצוות?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "נשמע מצוין!\n"
	.string "כדאי שאלך לסדר את הרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "חשבתי שנהיה\n"
	.string "צוות ממש קשוח…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "אהלן!\n"
	.string "אני {STR_VAR_1}, הפוקימאניאק!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "מה יש לבחור כמוני?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1},\n"
	.string "זה מה שיש לי!\p"
	.string "קדימה!\n"
	.string "נשתולל כצוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "החלטה טובה!\n"
	.string "אני ארשום את שנינו!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "הפוקימונים שלי אכזריים!\n"
	.string "זו לא אשמתי אם תתחרט על זה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "יו!\n"
	.string "אני המבעיר {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "רוצה לדעת מה בישלתי באימונים?\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "נו, מה דעתך?\n"
	.string "רוצה להקים צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "מעולה!\n"
	.string "אני ניגש לרישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "תבטיח שתהיה השותף שלי\n"
	.string "בפעם הבאה שניתקל זה בזה.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "אני {STR_VAR_1}, ואני מחנאי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "אני מגדל פוקימון שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "נראה לך שיהיה כיף להקים צוות?\n"
	.string "אני בטוח שכן!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "יש!\n"
	.string "אני כבר הולך להירשם!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "בפעם הבאה, טוב?\n"
	.string "אני רוצה להיות בצוות שלך.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "שלום!\n"
	.string "אני {STR_VAR_1}, ואני מטיילת!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "הפוקימונים שאני לוקחת איתי הם\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "מעניין אותך להצטרף אליי\n"
	.string "לצוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "אוי, תודה!\n"
	.string "אני אסדר את הרישום עכשיו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "יהיה נחמד אם אוכל להצטרף אליך\n"
	.string "בפעם אחרת.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "אני הטלפת {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "הצמד שגידלתי הוא\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "רוצה להקים איתי\n"
	.string "צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "בטח!\n"
	.string "אני אדאג לרישום!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "אם ניפגש שוב, אז הייתי רוצה\n"
	.string "להיות איתך בצוות.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "אני {STR_VAR_1}.\n"
	.string "אני טלפתית.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1} -\n"
	.string "הם תלמידיי.\p"
	.string "הרעיון של שותפות בצוות זוגי\n"
	.string "לא מסקרן אותך?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "תודה.\n"
	.string "אלך לטפל ברישום.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "אני מקווה שתהיה עוד הזדמנות\n"
	.string "לכרות ברית.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "אני התלמידה {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "פוקימון שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "ועוד אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "זה צמד הפוקימונים שלי. אפשר בבקשה\n"
	.string "להיות השותפה שלך בצוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "אוו, תודה!\n"
	.string "אלך להירשם בדלפק מיד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "בבקשה?\n"
	.string "אפשר להצטרף אליך בפעם הבאה?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "היי! קוראים לי {STR_VAR_1}!\n"
	.string "אני מגדלת פוקימון!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "הפוקימונים שגידלתי הם: אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "ואחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "נשמע מעניין?\n"
	.string "אז מה דעתך שנקים צוות זוגי?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "יופי!\n"
	.string "ההרשמה עליי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "בפעם הבאה אתה חייב להקים איתי\n"
	.string "צמד, בסדר?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "אני {STR_VAR_1}, ואני גאה לומר\n"
	.string "שאני פוקיפאנית.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "הפוקימונים המתוקים שגידלתי הם\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}.\p"
	.string "נכון שהם פשוט הכי חמודים?\n"
	.string "אנחנו חייבים להקים צמד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "תודה, מותק!\n"
	.string "אני כבר הולכת להירשם!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "שתדע לך שהפוקימונים המתוקים שלי\n"
	.string "הם הכי טובים. כמה מעצבן!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "היי, אני השחיינית {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "אחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "ואחד שמשתמש\n"
	.string "ב{STR_VAR_1} - {STR_VAR_2}.\p"
	.string "אלה הפוקימונים שאימנתי.\n"
	.string "אתה ואני, בוא נקים צוות זוגי.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "מגניב!\n"
	.string "אני ארשום את שנינו.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "אם ניפגש שוב, אתה חייב לי\n"
	.string "צוות זוגי!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "מה קורה?\n"
	.string "אני {STR_VAR_1}, ואני טריאתלט.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "יש לי זוג פוקימונים לא רעים.\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "יהיה מגניב אם נקים צוות זוגי\n"
	.string "ביחד, אז מה אתה אומר?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "אחלה!\n"
	.string "תחכה בזמן שאני נרשם, טוב?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "אני מצפה שבפעם הבאה תיתן לי\n"
	.string "להצטרף אליך, מה אתה אומר?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "אני הטריאתלטית {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "ועוד {STR_VAR_2} שיודע להשתמש\n"
	.string "ב{STR_VAR_1}. זה הזוג שלי.\p"
	.string "מה דעתך?\n"
	.string "לדעתי נהיה צמד טוב.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "אהבתי את התשובה!\n"
	.string "אסיים את ההרשמה ממש מהר!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "תיתן לי עוד הזדמנות להקים\n"
	.string "איתך צמד, נכון?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "היי! שלום לך!\n"
	.string "אני {STR_VAR_1}, ואני שחיין!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "תראה מה גידלתי!\n"
	.string "{STR_VAR_2} עם {STR_VAR_1},$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "ו{STR_VAR_2} עם {STR_VAR_1}!\p"
	.string "אדיר, נכון?\n"
	.string "יהיה אדיר גם להקים צמד!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "תודה רבה!\n"
	.string "אני כבר אסדר את עניין ההרשמה!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "אם ניפגש שוב, אתה חייב להקים\n"
	.string "איתי צמד. תעשה את זה, נכון?$"

