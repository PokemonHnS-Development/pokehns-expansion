VermilionCity_PortInside_hns_MapScripts::
	.byte 0

VermilionPortIndoor_EventScript_Teacher::
	msgbox VermilionPortPassage_Text_Teacher, MSGBOX_NPC
	end
VermilionPortIndoor_EventScript_Nerd::
	msgbox VermilionPort_Text_SuperNerd, MSGBOX_NPC
	end

VermilionPortPassage_Text_Teacher:
	.string "הספינה המהירה מפליגה כל יום!$"

VermilionPort_Text_SuperNerd:
	.string "הגעת מג'וטו?\p"
	.string "שמעתי שחיים שם הרבה\n"
	.string "פוקימונים נדירים.$"

VermilionPort_EventScript_Sailor::
	lock
	faceplayer
	goto_if_unset FLAG_RETURNED_MACHINE_PART, VermilionPort_EventScript_SailorCantSail
	goto_if_ge VAR_SSAQUA_STATE, 7, VermilionPort_EventScript_Sailor_AfterKanto
	msgbox VermilionPort_Text_AskBoard, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_Refused
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, TRUE, VermilionPort_EventScript_Sailor_MaidenVoyage
	msgbox VermilionPort_Text_NoTicket, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_EventScript_SailorCantSail::
	msgbox VermilionPort_Text_SailorCantSail, MSGBOX_NPC
	closemessage
	release
	end

VermilionPort_EventScript_Sailor_AfterKanto::
	message VermilionPort_Text_WhereSail
	multichoice 20, 0, MULTI_VERMILION_HARBOR, FALSE
	switch VAR_RESULT
	case 0, VermilionPort_EventScript_ChoseOlivine
	case 1, VermilionPort_EventScript_ChoseSouthernIsland
	case 2, VermilionPort_EventScript_ChoseBirthIsland
	case 3, VermilionPort_EventScript_ChoseFarawayIsland
	case 4, VermilionPort_EventScript_ChoseBattleFrontier
	case 5, VermilionPort_EventScript_Sailor_Refused
	case MULTI_B_PRESSED, VermilionPort_EventScript_Sailor_Refused
	release
	end

VermilionPort_EventScript_ChoseOlivine::
	closemessage
	delay 20
	checkitem ITEM_SS_TICKET
	bufferitemname STR_VAR_1, ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
	waitstate
	release
	end

VermilionPort_EventScript_ChoseSouthernIsland::
	closemessage
	delay 20
	checkitem ITEM_EON_TICKET
	bufferitemname STR_VAR_1, ITEM_EON_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_SOUTHERN_ISLAND_EXTERIOR_HNS, 13, 22
	waitstate
	release
	end

VermilionPort_EventScript_ChoseBirthIsland::
	closemessage
	delay 20
	checkitem ITEM_AURORA_TICKET
	bufferitemname STR_VAR_1, ITEM_AURORA_TICKET
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_BIRTH_ISLAND_EXTERIOR_HNS, 13, 23
	waitstate
	release
	end

VermilionPort_EventScript_ChoseFarawayIsland::
	closemessage
	delay 20
	checkitem ITEM_OLD_SEA_MAP
	bufferitemname STR_VAR_1, ITEM_OLD_SEA_MAP
	goto_if_eq VAR_RESULT, FALSE, VermilionPort_EventScript_Sailor_NoCredentials
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_FARAWAY_ISLAND_ENTRANCE_HNS, 13, 38
	waitstate
	release
	end	

VermilionPort_EventScript_ChoseBattleFrontier::
	closemessage
	delay 20
	call VermilionPort_EventScript_EnterShip
	warpsilent MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS, 20, 67
	waitstate
	release
	end	

VermilionPort_EventScript_Sailor_MaidenVoyage::
	msgbox VermilionPort_Text_FlashTicket, MSGBOX_DEFAULT
	call VermilionPort_EventScript_EnterShip
	setvar VAR_SSAQUA_STATE, 1
	warpsilent MAP_SSAQUA_1F_HNS, 29, 3
	waitstate
	release
	end

VermilionPort_EventScript_EnterShip::
	msgbox VermilionPort_Text_SailorGetOnBoard, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_VERMILIONMARINA_SAILOR, VermilionPort_Movement_SailorEnterBoat
	waitmovement 0
	playse SE_EXIT
	applymovement OBJ_EVENT_ID_PLAYER, VermilionPort_Movement_PlayerEnterBoat
	waitmovement 0
	special SpawnCameraObject
	playse SE_EXIT
	removeobject OBJ_EVENT_ID_PLAYER
	delay 60
	applymovement LOCALID_VERMILIONMARINA_SAILOR, VermilionPort_Movement_BoatLeave
	applymovement LOCALID_VERMILIONMARINA_BOAT, VermilionPort_Movement_BoatLeave
	waitmovement LOCALID_VERMILIONMARINA_BOAT
	setrespawn HEAL_LOCATION_VERMILION_CITY_HNS
	return

VermilionPort_EventScript_Sailor_Refused::
	msgbox VermilionPort_Text_ComeAgain, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_EventScript_Sailor_NoCredentials::
	msgbox VermilionPort_Text_NoPass, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionPort_Movement_SailorEnterBoat:
	walk_down
	walk_down
	step_end

VermilionPort_Movement_PlayerEnterBoat:
	walk_down
	walk_down
	walk_in_place_down
	step_end

VermilionPort_Movement_BoatLeave:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

VermilionPort_Text_SailorCantSail:
	.string "הייתה פריצה במפעל החשמל, אז\n"
	.string "לא נוכל להפליג עד שהגנב יימצא.$"

VermilionPort_Text_NoPass:
    .string "{PLAYER} ניסה להציג את\n"
    .string "{STR_VAR_1}…\p"
    .string "…אבל אין {STR_VAR_1}!\p"
    .string "סליחה! אפשר לעלות לסיפון\n"
    .string "רק עם {STR_VAR_1}.$"

VermilionPort_Text_SailorGetOnBoard:
    .string "אנחנו יוצאים עוד מעט.\n"
    .string "נא לעלות לסיפון.$"

VermilionPort_Text_CantBoard:
    .string "Sorry. You can't board now.$"

VermilionPort_Text_WhereSail:
    .string "לאן תרצה להפליג?$"

VermilionPort_Text_AskBoard:
    .string "ברוכים הבאים\n"
    .string "לספינת אקווה המהירה.\p"
    .string "תרצה לעלות לסיפון היום?$"

VermilionPort_Text_AskTicket:
    .string "May I see your S.S.TICKET?$"

VermilionPort_Text_ComeAgain:
    .string "נשמח לראות אותך שוב!$"

VermilionPort_Text_FlashTicket:
    .string "{PLAYER} הציג את כרטיס ס.ס.\p"
    .string "בסדר גמור. תודה!$"

VermilionPort_Text_NoTicket:
    .string "{PLAYER} ניסה להציג את\n"
    .string "כרטיס ס.ס…\p"
    .string "…אבל אין כרטיס!\p"
    .string "סליחה! אפשר לעלות לסיפון\n"
    .string "רק עם כרטיס ס.ס.$"
