SSAqua_CaptainsRoom_hns_MapScripts::
	.byte 0

SSAqua_CaptainsRoom_EventScript_Captain::
	goto_if_eq VAR_TEMP_0, 1, SSAqua_CaptainsRoom_EventScrip_CaptainAfter
	msgbox SSAqua_CaptainsRoom_Text_CaptainExhausting, MSGBOX_NPC
	setvar VAR_TEMP_0, 1
SSAqua_CaptainsRoom_EventScrip_CaptainAfter::
	msgbox SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike, MSGBOX_DEFAULT
	closemessage
	end

SSAqua_CaptainsRoom_EventScript_Granddaughter::
	lock
	applymovement LOCALID_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER, SSAqua_CaptainsRoom_Movement_Jump
	waitmovement 0
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe, MSGBOX_DEFAULT
	turnobject LOCALID_SSAQUA_CAPTAINS_ROOM_CAPTAIN, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SSAQUA_CAPTAINS_ROOM_CAPTAIN, Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_SSAQUA_CAPTAINS_ROOM_CAPTAIN
	delay 60
	faceplayer
	msgbox SSAqua_CaptainsRoom_Text_GranddaughterHasToFindGrandpa, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_SSAQUA_CAPTAINS_ROOM_GRANDDAUGHTER
	setvar VAR_SSAQUA_STATE, 4
	clearflag FLAG_HIDE_SSAQUA_ROOM_SSE_GRANDDAUGHTER
	warp MAP_SSAQUA_ROOM_SSE_HNS, 0
	waitstate
	release
	end

SSAqua_CaptainsRoom_Movement_Jump:
	jump_in_place_right
	jump_in_place_right
	jump_in_place_right
	step_end

SSAqua_CaptainsRoom_Text_GranddaughterCaptainPlayWithMe:
	.string "קפטן, תשחק איתי, בבקשה?\p"
	.string "משעמם לי! אני רוצה לשחק עוד!$"

SSAqua_CaptainsRoom_Text_GranddaughterHasToFindGrandpa:
	.string "היי! תשחק איתי?\p"
	.string "…אוי!\p"
	.string "סבא דואג לי?\p"
	.string "אני חייבת ללכת!\p"
	.string "אני חייבת ללכת למצוא את סבא!$"

SSAqua_CaptainsRoom_Text_CaptainExhausting:
	.string "פיו! תודה שבאת.\p"
	.string "לשעשע את הילדה הקטנה הזאת\n"
	.string "היה מתיש.$"

SSAqua_CaptainsRoom_Text_CaptainHowDoYouLike:
	.string "מה דעתך על ההפלגה\n"
	.string "בספינת אקווה?\p"
	.string "היא ממש מחליקה\n"
	.string "על פני הגלים.$"

