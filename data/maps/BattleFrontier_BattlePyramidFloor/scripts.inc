BattleFrontier_BattlePyramidFloor_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame:
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight::
	lockall
	@ pyramid_updatelight, cant use macro because it straddles the loop
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop::
	special CallBattlePyramidFunction
	delay 2
	goto_if_ne VAR_RESULT, 2, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume:
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  @ VAR_RESULT seems to be ignored here
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty::
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby::
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition:
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius::
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor::
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Floor number
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	goto_if_eq VAR_RESULT, 7, BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop::
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 17, 17
	waitstate
	end

@ TRAINER_PHILLIP is used as a placeholder
BattlePyramid_TrainerBattle::
	facilitytrainerbattle FACILITY_BATTLE_PYRAMID
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall::
	pyramid_setitem
	callstd STD_FIND_ITEM
	goto_if_eq VAR_0x8007, 0, BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd::
	end

BattlePyramid_Retire::
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

@ Also used by Trainer Hill
BattleFacility_TrainerBattle_PlaceholderText:
	.string "This is a sample message.$"

gText_BattlePyramidConfirmRest::
	.string "המסע שלך בפירמידת הקרב יישמר,\n"
	.string "ואפשר יהיה לצאת בינתיים. זה בסדר?$"

gText_BattlePyramidConfirmRetire::
	.string "האם באמת לפרוש\n"
	.string "מהמסע בפירמידה?$"

BattlePyramid_Text_ExitHintUp1::
	.string "היציאה מהקומה הזאת\n"
	.string "נמצאת בכיוון הזה: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft1::
	.string "היציאה מהקומה הזאת\n"
	.string "נמצאת בכיוון הזה: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight1::
	.string "היציאה מהקומה הזאת\n"
	.string "נמצאת בכיוון הזה: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown1::
	.string "היציאה מהקומה הזאת\n"
	.string "נמצאת בכיוון הזה: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp2::
	.string "היציאה בקומה הזאת\n"
	.string "נמצאת בכיוון {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft2::
	.string "היציאה בקומה הזאת\n"
	.string "נמצאת בכיוון {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight2::
	.string "היציאה בקומה הזאת\n"
	.string "נמצאת בכיוון {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown2::
	.string "היציאה בקומה הזאת\n"
	.string "נמצאת בכיוון {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp3::
	.string "היציאה נמצאת\n"
	.string "בכיוון ההוא {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft3::
	.string "היציאה נמצאת\n"
	.string "בכיוון ההוא {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight3::
	.string "היציאה נמצאת\n"
	.string "בכיוון ההוא {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown3::
	.string "היציאה נמצאת\n"
	.string "בכיוון ההוא {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp4::
	.string "בקומה הזאת, היציאה נמצאת\n"
	.string "אי שם בכיוון {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft4::
	.string "בקומה הזאת, היציאה נמצאת\n"
	.string "אי שם בכיוון {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight4::
	.string "בקומה הזאת, היציאה נמצאת\n"
	.string "אי שם בכיוון {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown4::
	.string "בקומה הזאת, היציאה נמצאת\n"
	.string "אי שם בכיוון {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp5::
	.string "היציאה?\n"
	.string "היא בכיוון {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft5::
	.string "היציאה?\n"
	.string "היא בכיוון {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight5::
	.string "היציאה?\n"
	.string "היא בכיוון {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown5::
	.string "היציאה?\n"
	.string "היא בכיוון {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp6::
	.string "היציאה נמצאת דווקא\n"
	.string "בכיוון {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft6::
	.string "היציאה נמצאת דווקא\n"
	.string "בכיוון {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight6::
	.string "היציאה נמצאת דווקא\n"
	.string "בכיוון {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown6::
	.string "היציאה נמצאת דווקא\n"
	.string "בכיוון {DOWN_ARROW}.$"

BattlePyramid_Text_EightItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד שמונה פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_SevenItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד שבעה פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_SixItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד שישה פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_FiveItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד חמישה פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_FourItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד ארבעה פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_ThreeItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד שלושה פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_TwoItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשארו עוד שני פריטים\n"
	.string "שטרם נמצאו.$"

BattlePyramid_Text_OneItemRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "נשאר עוד פריט אחד\n"
	.string "שטרם נמצא.$"

BattlePyramid_Text_ZeroItemsRemaining1::
	.string "רוצה למצוא פריטים?\p"
	.string "לא נשאר כאן\n"
	.string "שום דבר למצוא!$"

BattlePyramid_Text_EightItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "שמונה פריטים מונחים\n"
	.string "כאן בסביבה.$"

BattlePyramid_Text_SevenItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "נשארו עוד שבעה פריטים\n"
	.string "שמונחים כאן בסביבה.$"

BattlePyramid_Text_SixItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "נשארו עוד שישה פריטים\n"
	.string "שמונחים כאן בסביבה.$"

BattlePyramid_Text_FiveItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "נשארו עוד חמישה פריטים\n"
	.string "שמונחים כאן בסביבה.$"

BattlePyramid_Text_FourItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "נשארו עוד ארבעה פריטים\n"
	.string "שמונחים כאן בסביבה.$"

BattlePyramid_Text_ThreeItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "נשארו עוד שלושה פריטים\n"
	.string "שמונחים כאן בסביבה.$"

BattlePyramid_Text_TwoItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "נשארו עוד שני פריטים\n"
	.string "שמונחים כאן בסביבה.$"

BattlePyramid_Text_OneItemRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "רק פריט אחד מונח\n"
	.string "כאן בסביבה.$"

BattlePyramid_Text_ZeroItemsRemaining2::
	.string "בגלל שניצחת, אגלה לך\n"
	.string "סוד קטן!\p"
	.string "לא נשאר שום דבר\n"
	.string "שמונח כאן בסביבה.$"

BattlePyramid_Text_EightItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד שמונה פריטים למצוא.$"

BattlePyramid_Text_SevenItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד שבעה פריטים למצוא.$"

BattlePyramid_Text_SixItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד שישה פריטים למצוא.$"

BattlePyramid_Text_FiveItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד חמישה פריטים למצוא.$"

BattlePyramid_Text_FourItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד ארבעה פריטים למצוא.$"

BattlePyramid_Text_ThreeItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד שלושה פריטים למצוא.$"

BattlePyramid_Text_TwoItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשארו\n"
	.string "עוד שני פריטים למצוא.$"

BattlePyramid_Text_OneItemRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת נשאר\n"
	.string "רק פריט אחד למצוא.$"

BattlePyramid_Text_ZeroItemsRemaining3::
	.string "איך מצב מלאי הפריטים שלך?\p"
	.string "נראה לי שבקומה הזאת לא נשארו\n"
	.string "עוד פריטים למצוא. שמור על עצמך!$"

BattlePyramid_Text_EightItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד שמונה\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_SevenItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד שבעה\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_SixItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד שישה\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_FiveItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד חמישה\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_FourItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד ארבעה\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_ThreeItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד שלושה\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_TwoItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש עוד שני\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_OneItemRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שיש רק עוד\n"
	.string "פריט אחד על הרצפה.$"

BattlePyramid_Text_ZeroItemsRemaining4::
	.string "אתה חזק, אז הרווחת רמז!\p"
	.string "נראה שאין עוד\n"
	.string "פריטים על הרצפה.$"

BattlePyramid_Text_EightItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש שמונה פריטים…$"

BattlePyramid_Text_SevenItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש שבעה פריטים…$"

BattlePyramid_Text_SixItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש שישה פריטים…$"

BattlePyramid_Text_FiveItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש חמישה פריטים…$"

BattlePyramid_Text_FourItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש ארבעה פריטים…$"

BattlePyramid_Text_ThreeItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש שלושה פריטים…$"

BattlePyramid_Text_TwoItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש שני פריטים…$"

BattlePyramid_Text_OneItemRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שיש פריט אחד…$"

BattlePyramid_Text_ZeroItemsRemaining5::
	.string "בקומה הזאת של הפירמידה,\n"
	.string "שמעתי שאין אף פריט…$"

BattlePyramid_Text_EightItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד שמונה פריטים.$"

BattlePyramid_Text_SevenItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד שבעה פריטים.$"

BattlePyramid_Text_SixItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד שישה פריטים.$"

BattlePyramid_Text_FiveItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד חמישה פריטים.$"

BattlePyramid_Text_FourItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד ארבעה פריטים.$"

BattlePyramid_Text_ThreeItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד שלושה פריטים.$"

BattlePyramid_Text_TwoItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד שני פריטים.$"

BattlePyramid_Text_OneItemRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי יש בקומה הזאת\n"
	.string "עוד פריט אחד.$"

BattlePyramid_Text_ZeroItemsRemaining6::
	.string "אספת פריטים?\p"
	.string "לדעתי אין בקומה הזאת\n"
	.string "עוד פריטים.$"

BattlePyramid_Text_SevenTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "שבעה מאמנים קשוחים!$"

BattlePyramid_Text_SixTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "שישה מאמנים קשוחים!$"

BattlePyramid_Text_FiveTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "חמישה מאמנים קשוחים!$"

BattlePyramid_Text_FourTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "ארבעה מאמנים קשוחים!$"

BattlePyramid_Text_ThreeTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "שלושה מאמנים קשוחים!$"

BattlePyramid_Text_TwoTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "שני מאמנים קשוחים!$"

BattlePyramid_Text_OneTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "אבל חוץ ממני יש עוד\n"
	.string "מאמן קשוח אחד!$"

BattlePyramid_Text_ZeroTrainersRemaining1::
	.string "נלחמת בצורה מדהימה!\p"
	.string "לא נשאר אף אחד\n"
	.string "שיכול לנצח אותך!$"

BattlePyramid_Text_SevenTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשארו עוד שבעה מאמנים!\n"
	.string "מישהו כבר יעמיד אותך במקומך!$"

BattlePyramid_Text_SixTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשארו עוד שישה מאמנים!\n"
	.string "מישהו כבר יעמיד אותך במקומך!$"

BattlePyramid_Text_FiveTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשארו עוד חמישה מאמנים!\n"
	.string "מישהו כבר יעמיד אותך במקומך!$"

BattlePyramid_Text_FourTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשארו עוד ארבעה מאמנים!\n"
	.string "מישהו כבר יעמיד אותך במקומך!$"

BattlePyramid_Text_ThreeTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשארו עוד שלושה מאמנים!\n"
	.string "מישהו כבר יעמיד אותך במקומך!$"

BattlePyramid_Text_TwoTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשארו עוד שני מאמנים!\n"
	.string "מישהו כבר יעמיד אותך במקומך!$"

BattlePyramid_Text_OneTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל נשאר עוד מאמן אחד!\n"
	.string "בטוח שהוא יעמיד אותך במקומך!$"

BattlePyramid_Text_ZeroTrainersRemaining2::
	.string "זה כל כך מעצבן!\p"
	.string "אבל לא נשארו עוד מאמנים\n"
	.string "שיכולים להתמודד מולך!$"

BattlePyramid_Text_SevenTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשארו בקומה עוד שבעה מאמנים.\n"
	.string "תוכל לנצח את כולם?$"

BattlePyramid_Text_SixTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשארו בקומה עוד שישה מאמנים.\n"
	.string "תוכל לנצח את כולם?$"

BattlePyramid_Text_FiveTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשארו בקומה עוד חמישה מאמנים.\n"
	.string "תוכל לנצח את כולם?$"

BattlePyramid_Text_FourTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשארו בקומה עוד ארבעה מאמנים.\n"
	.string "תוכל לנצח את כולם?$"

BattlePyramid_Text_ThreeTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשארו בקומה עוד שלושה מאמנים.\n"
	.string "תוכל לנצח את כולם?$"

BattlePyramid_Text_TwoTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשארו בקומה עוד שני מאמנים.\n"
	.string "תוכל לנצח את שניהם?$"

BattlePyramid_Text_OneTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "אבל נשאר בקומה עוד מאמן אחד.\n"
	.string "תצליח לגבור עליו?$"

BattlePyramid_Text_ZeroTrainersRemaining3::
	.string "זה די מרשים!\p"
	.string "ניצחת את כל המאמנים\n"
	.string "בקומה הזאת.$"

BattlePyramid_Text_SevenTrainersRemaining4::
	.string "אולי תוכל לנצח ברצף\n"
	.string "את שבעת המאמנים שנשארו בקומה הזאת.$"

BattlePyramid_Text_SixTrainersRemaining4::
	.string "אולי תוכל לנצח ברצף\n"
	.string "את ששת המאמנים שנשארו בקומה הזאת.$"

BattlePyramid_Text_FiveTrainersRemaining4::
	.string "אולי תוכל לנצח ברצף\n"
	.string "את חמשת המאמנים שנשארו בקומה הזאת.$"

BattlePyramid_Text_FourTrainersRemaining4::
	.string "אולי תוכל לנצח ברצף\n"
	.string "את ארבעת המאמנים שנשארו בקומה הזאת.$"

BattlePyramid_Text_ThreeTrainersRemaining4::
	.string "אולי תוכל לנצח ברצף\n"
	.string "את שלושת המאמנים שנשארו בקומה הזאת.$"

BattlePyramid_Text_TwoTrainersRemaining4::
	.string "אולי תוכל לנצח ברצף\n"
	.string "את שני המאמנים שנשארו בקומה הזאת.$"

BattlePyramid_Text_OneTrainersRemaining4::
	.string "אולי תוכל להשלים את הרצף מול\n"
	.string "המאמן האחרון שנשאר בקומה הזאת.$"

BattlePyramid_Text_ZeroTrainersRemaining4::
	.string "לא נשאר כאן אף אחד\n"
	.string "שיכול לנצח אותך עכשיו…$"

BattlePyramid_Text_SevenTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את שבעת המאמנים המומחים שנותרו.$"

BattlePyramid_Text_SixTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את ששת המאמנים המומחים שנותרו.$"

BattlePyramid_Text_FiveTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את חמשת המאמנים המומחים שנותרו.$"

BattlePyramid_Text_FourTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את ארבעת המאמנים המומחים שנותרו.$"

BattlePyramid_Text_ThreeTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את שלושת המאמנים המומחים שנותרו.$"

BattlePyramid_Text_TwoTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את שני המאמנים המומחים שנותרו.$"

BattlePyramid_Text_OneTrainersRemaining5::
	.string "אולי יש לך את מה שצריך כדי לנצח\n"
	.string "את המאמן המומחה האחרון שנותר.$"

BattlePyramid_Text_ZeroTrainersRemaining5::
	.string "הכישורים שלך מעל לכל ביקורת.\p"
	.string "לא נשארו כאן עוד מאמנים\n"
	.string "שיש להם סיכוי כלשהו לנצח אותך.$"

BattlePyramid_Text_SevenTrainersRemaining6::
	.string "תוכל להמשיך לנצח מול\n"
	.string "שבעת המאמנים שנותרו?$"

BattlePyramid_Text_SixTrainersRemaining6::
	.string "תוכל להמשיך לנצח מול\n"
	.string "ששת המאמנים שנותרו?$"

BattlePyramid_Text_FiveTrainersRemaining6::
	.string "תוכל להמשיך לנצח מול\n"
	.string "חמשת המאמנים שנותרו?$"

BattlePyramid_Text_FourTrainersRemaining6::
	.string "תוכל להמשיך לנצח מול\n"
	.string "ארבעת המאמנים שנותרו?$"

BattlePyramid_Text_ThreeTrainersRemaining6::
	.string "תוכל להמשיך לנצח מול\n"
	.string "שלושת המאמנים שנותרו?$"

BattlePyramid_Text_TwoTrainersRemaining6::
	.string "תוכל להמשיך לנצח מול\n"
	.string "שני המאמנים שנותרו?$"

BattlePyramid_Text_OneTrainersRemaining6::
	.string "תוכל להמשיך לנצח גם\n"
	.string "מול המאמן האחרון שנותר?$"

BattlePyramid_Text_ZeroTrainersRemaining6::
	.string "לא נשארו עוד מאמנים\n"
	.string "שיכולים להתמודד מולך עכשיו…$"
