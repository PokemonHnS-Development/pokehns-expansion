SSAqua_RoomSSE_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAqua_RoomSSE_OnFrame
    map_script MAP_SCRIPT_ON_TRANSITION, SSAqua_RoomSSE_OnTransition
	.byte 0

SSAqua_RoomSSE_OnTransition::
    goto_if_ge VAR_SSAQUA_STATE, 5, SSAqua_RoomSSE_SetGirlPos
    end

SSAqua_RoomSSE_OnFrame::
	map_script_2 VAR_SSAQUA_STATE, 4, SSAqua_RoomSSE_EventScript_ReuinionScene
	.2byte 0

SSAqua_RoomSSE_SetGirlPos::
    setobjectxyperm LOCALID_SSAQUA_ROOM_SSE_GRANDDAUGTHER, 2, 4
    setobjectmovementtype LOCALID_SSAQUA_ROOM_SSE_GRANDDAUGTHER, MOVEMENT_TYPE_FACE_LEFT
    end

SSAqua_RoomSSE_EventScript_ReuinionScene::
	lock
    turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
    turnobject LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, DIR_SOUTH
    playse SE_PIN
    applymovement LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER
	applymovement LOCALID_SSAQUA_ROOM_SSE_GRANDDAUGTHER, SSAqua_RoomSSE_Movement_GirlEnter
    waitmovement 0
    turnobject LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, DIR_EAST
    msgbox SSAqua_RoomSSE_Text_GranddaughterWasPlaying, MSGBOX_DEFAULT
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, SSAqua_RoomSSE_Movement_PlayerEnter
    waitmovement 0
    turnobject LOCALID_SSAQUA_ROOM_SSE_GRANDFATHER, DIR_SOUTH
    msgbox SSAqua_RoomSSE_Text_EntertainedGranddaughter, MSGBOX_DEFAULT
    msgbox SSAqua_RoomSSE_Text_GrandpaHaveThis, MSGBOX_DEFAULT
    giveitem ITEM_METAL_COAT
    closemessage
	setvar VAR_SSAQUA_STATE, 5
	release
	end

SSAqua_RoomSSE_EventScript_Grandpa::
	lock
	faceplayer
	goto_if_ge VAR_SSAQUA_STATE, 4, SSAqua_RoomSSE_EventScript_GrandpaAfter
	msgbox SSAqua_RoomSSE_Text_CantFindGranddaughter, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_RoomSSE_EventScript_GrandpaAfter::
	msgbox SSAqua_RoomSSE_Text_GrandpaTravelling, MSGBOX_DEFAULT
	closemessage
	release
	end

SSAqua_RoomSSE_EventScript_GrandDaughter::
	msgbox SSAqua_RoomSSE_Text_GranddaughterHadFun, MSGBOX_NPC
	end

SSAqua_RoomSSE_Movement_GirlEnter:
    walk_up
    walk_up
    walk_left
    step_end

SSAqua_RoomSSE_Movement_PlayerEnter:
    walk_up
    walk_left
    walk_left
    walk_up
    step_end

SSAqua_RoomSSE_Text_CantFindGranddaughter:
    .string "אה, שלום…\p"
    .string "אני עדיין לא מוצא\n"
    .string "את הנכדה שלי.\p"
    .string "אם היא על הספינה,\n"
    .string "זה בסדר.\p"
    .string "היא ילדה מלאת אנרגיה,\n"
    .string "אז אולי היא מציקה למישהו.\p"
    .string "אני דואג…$"

SSAqua_RoomSSE_Text_EntertainedGranddaughter:
    .string "קוראים לך {PLAYER}, נכון?\n"
    .string "שמעתי ששעשעת את הנכדה שלי.\p"
    .string "אני רוצה להודות לך על כך.$"

SSAqua_RoomSSE_Text_GrandpaHaveThis:
    .string "יש לי רעיון! אני רוצה\n"
    .string "לתת לך את זה!$"

SSAqua_RoomSSE_Text_GrandpaTravelling:
    .string "אנחנו מטיילים\n"
    .string "מסביב לעולם.$"

SSAqua_RoomSSE_Text_GranddaughterWasPlaying:
    .string "סבא, הנה אני!\n"
    .string "שיחקתי עם הקפטן ועם הנוסע הזה!$"

SSAqua_RoomSSE_Text_GranddaughterHadFun:
    .string "היה לי ממש כיף לשחק!$"
