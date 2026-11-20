BattleFrontier_BattlePalaceCorridor_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceCorridor_OnFrame_hns
	.byte 0

BattleFrontier_BattlePalaceCorridor_OnFrame_hns:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePalaceCorridor_EventScript_WalkThroughCorridor_hns
	.2byte 0

BattleFrontier_BattlePalaceCorridor_EventScript_WalkThroughCorridor_hns::
	delay 16
	applymovement LOCALID_PALACE_CORRIDOR_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_EnterCorridor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_EnterCorridor_hns
	waitmovement 0
	lockall
	palace_getcomment
	call_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment1_hns
	call_if_eq VAR_RESULT, 1, BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment2_hns
	call_if_eq VAR_RESULT, 2, BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment3_hns
	call_if_eq VAR_RESULT, 3, BattleFrontier_BattlePalaceCorridor_EventScript_StreakComment_hns
	call_if_eq VAR_RESULT, 4, BattleFrontier_BattlePalaceCorridor_EventScript_LongStreakComment_hns
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	goto_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattlePalaceCorridor_EventScript_WalkToOpenBattleRoom_hns
	applymovement LOCALID_PALACE_CORRIDOR_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkTo50BattleRoom_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkTo50BattleRoom_hns
	waitmovement 0
	opendoor 6, 3
	waitdooranim
	applymovement LOCALID_PALACE_CORRIDOR_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantEnterBattleRoom_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerEnterBattleRoom_hns
	waitmovement 0
	closedoor 6, 3
	waitdooranim
	goto BattleFrontier_BattlePalaceCorridor_EventScript_WarpToBattleRoom_hns

BattleFrontier_BattlePalaceCorridor_EventScript_WalkToOpenBattleRoom_hns::
	applymovement LOCALID_PALACE_CORRIDOR_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkToOpenBattleRoom_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkToOpenBattleRoom_hns
	waitmovement 0
	opendoor 10, 3
	waitdooranim
	applymovement LOCALID_PALACE_CORRIDOR_ATTENDANT, BattleFrontier_BattlePalaceCorridor_Movement_AttendantEnterBattleRoom_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceCorridor_Movement_PlayerEnterBattleRoom_hns
	waitmovement 0
	closedoor 10, 3
	waitdooranim
BattleFrontier_BattlePalaceCorridor_EventScript_WarpToBattleRoom_hns::
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_BATTLE_ROOM_HNS, 7, 4
	waitstate
	end

BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment1_hns::
	msgbox BattleFrontier_BattlePalaceCorridor_Text_PeopleAndMonAreSame_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment2_hns::
	msgbox BattleFrontier_BattlePalaceCorridor_Text_LetMonDoWhatItLikes_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_RandomComment3_hns::
	msgbox BattleFrontier_BattlePalaceCorridor_Text_MonDifferentWhenCornered_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_StreakComment_hns::
	msgbox BattleFrontier_BattlePalaceCorridor_Text_BeginningToUnderstandNature_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_EventScript_LongStreakComment_hns::
	msgbox BattleFrontier_BattlePalaceCorridor_Text_HeartfeltBondBetweenYouAndMons_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceCorridor_Movement_EnterCorridor_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkTo50BattleRoom_hns:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkTo50BattleRoom_hns:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_AttendantWalkToOpenBattleRoom_hns:
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_PlayerWalkToOpenBattleRoom_hns:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePalaceCorridor_Movement_PlayerEnterBattleRoom_hns:
	walk_up
BattleFrontier_BattlePalaceCorridor_Movement_AttendantEnterBattleRoom_hns:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceCorridor_Text_PeopleAndMonAreSame_hns:
	.string "אנשים ופוקימונים, הם בעצם\n"
	.string "אותו הדבר…\p"
	.string "האופי של כל אחד הופך אותו לטוב\n"
	.string "בדברים מסוימים, ולא טוב באחרים.$"

BattleFrontier_BattlePalaceCorridor_Text_LetMonDoWhatItLikes_hns:
	.string "לא כדאי לנסות לגרום לפוקימון\n"
	.string "לעשות דברים שהוא לא אוהב.\p"
	.string "עדיף לתת לו לעשות את מה\n"
	.string "שהוא אוהב ושהוא טוב בו.\p"
	.string "כדאי לשים את עצמך במקום הפוקימון\n"
	.string "ולחשוב אילו מהלכים הוא היה אוהב.$"

BattleFrontier_BattlePalaceCorridor_Text_MonDifferentWhenCornered_hns:
	.string "האופי של פוקימון הוא\n"
	.string "דבר מופלא…\p"
	.string "יש פוקימונים שמתנהגים בצורה\n"
	.string "שונה לגמרי כשהם נלחצים לפינה.$"

BattleFrontier_BattlePalaceCorridor_Text_BeginningToUnderstandNature_hns:
	.string "אתה מתחיל להבין איך האופי\n"
	.string "של פוקימון קובע את התנהגותו?$"

BattleFrontier_BattlePalaceCorridor_Text_HeartfeltBondBetweenYouAndMons_hns:
	.string "אה… אני רואה קשר חזק ועמוק\n"
	.string "בינך לבין הפוקימונים שלך…$"

