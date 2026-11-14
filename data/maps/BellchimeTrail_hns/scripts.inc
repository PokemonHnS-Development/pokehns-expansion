BellchimeTrail_hns_MapScripts::
	.byte 0


BellchimeTrail_EventScript_Morty::
	lock
	faceplayer
	msgbox BellchimeTrail_Text_Morty, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_BLACK
	setflag FLAG_HIDE_BELLCHIME_MORTY
	removeobject LOCALID_BELLCHIME_MORTY
	fadescreenswapbuffers FADE_FROM_BLACK
	clearflag FLAG_HIDE_DOJO_MORTY
	release
	end

BellchimeTrail_Text_Morty:
	.string "מורטי: הפוקימון האגדי\n"
	.string "לא בחר בי…\p"
	.string "אבל זה לא אומר\n"
	.string "שאיבדתי את העתיד שלי.\p"
	.string "אמשיך להתאמן עד שאגלה\n"
	.string "עתיד חדש בשבילי.\p"
	.string "אם תרצה קרב נוסף, חפש\n"
	.string "אותי בדוג'ו הלחימה.$"

EcruteakBellchimeTrail_EventScript_Item_BigMushroom::
	finditem ITEM_BIG_MUSHROOM
	end

EcruteakBellchimeTrail_EventScript_DoorTrigger::
	lock
	opendoor 28, 12
	waitdooranim
	addobject OBJ_EVENT_ID_CAMERA
	removeobject OBJ_EVENT_ID_PLAYER
	closedoor 28, 12
	applymovement OBJ_EVENT_ID_CAMERA, EcruteakBellchimeTrail_Movement_CameraPanUp
	waitmovement 0
	warp MAP_TIN_TOWER_1F_HNS, 1
	release
	end

EcruteakBellchimeTrail_Movement_CameraPanUp::
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	slide_up
	step_end
