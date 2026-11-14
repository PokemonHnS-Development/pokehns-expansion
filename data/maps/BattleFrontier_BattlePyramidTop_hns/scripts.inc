BattleFrontier_BattlePyramidTop_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidTop_OnResume_hns
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidTop_OnFrame_hns
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidTop_OnTransition_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePyramidTop_OnWarp_hns
	.byte 0

BattleFrontier_BattlePyramidTop_OnTransition_hns:
	pyramid_updatelight 200, PYRAMID_LIGHT_SET_RADIUS
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidTop_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidTop_EventScript_SetUpObjects_hns
	.2byte 0

BattleFrontier_BattlePyramidTop_EventScript_SetUpObjects_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	goto_if_ne VAR_TEMP_C, 0, BattleFrontier_BattlePyramidTop_EventScript_EndSetUpObjects_hns
	setobjectxyperm LOCALID_BRANDON, 0, 0
BattleFrontier_BattlePyramidTop_EventScript_EndSetUpObjects_hns::
	end

BattleFrontier_BattlePyramidTop_OnResume_hns:
	frontier_getbrainstatus
	goto_if_eq VAR_RESULT, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattlePyramidTop_EventScript_CheckChallengeStatus_hns
	call BattleFrontier_EventScript_SetBrainObjectGfx
BattleFrontier_BattlePyramidTop_EventScript_CheckChallengeStatus_hns::
	copyvar VAR_TEMP_C, VAR_RESULT
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge_hns
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hns
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge_hns
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns
	end

BattleFrontier_BattlePyramidTop_OnFrame_hns:
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidTop_EventScript_PlayPyramidMusic_hns
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidTop_EventScript_ShowMapName_hns
	.2byte 0

BattleFrontier_BattlePyramidTop_EventScript_PlayPyramidMusic_hns::
	playbgm MUS_B_PYRAMID_TOP, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidTop_EventScript_ShowMapName_hns::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidTop_EventScript_ReadyChallenge_hns::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidTop_EventScript_Attendant_hns::
	lock
	faceplayer
	goto_if_ne VAR_TEMP_D, 0, BattleFrontier_BattlePyramidTop_EventScript_StepForwardWhenReady_hns
	goto_if_ne VAR_TEMP_C, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattlePyramidTop_EventScript_BrandonHereMoveAside_hns
	msgbox BattleFrontier_BattlePyramidTop_Text_ReachedSummitUpYouGo_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PYRAMID_TOP_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside_hns
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidTop_Movement_PlayerClimbToTop_hns
	waitmovement 0
	applymovement LOCALID_PYRAMID_TOP_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantBlockPath_hns
	waitmovement 0
	message BattleFrontier_BattlePyramidTop_Text_PlayerConqueredPyramid_hns
	waitmessage
	playfanfare MUS_OBTAIN_B_POINTS
	waitfanfare
	closemessage
BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY_HNS, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidTop_EventScript_StepForwardWhenReady_hns::
	msgbox BattleFrontier_BattlePyramidTop_Text_StepForwardWhenReady_hns, MSGBOX_DEFAULT
	closemessage
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHereMoveAside_hns::
	msgbox BattleFrontier_BattlePyramidTop_Text_ChiefBeatYouHere_hns, MSGBOX_DEFAULT
	applymovement LOCALID_PYRAMID_TOP_ATTENDANT, BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside_hns
	setvar VAR_TEMP_D, 1
	closemessage
	end

BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon_hns::
	lockall
	switch VAR_TEMP_C
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattlePyramidTop_EventScript_BrandonIntroGold_hns
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech_hns
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech_hns
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech_hns
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, BattleFrontier_BattlePyramidTop_Movement_CameraPanUp_hns
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_ExplorationsAreGrandestAdventure_hns, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer_hns
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_ImPyramidKingBrandon_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon_hnsSilver_hns
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardSilverSpeech_hns::
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer_hns
	waitmovement 0
BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon_hnsSilver_hns::
	msgbox BattleFrontier_BattlePyramidTop_Text_BringCourageToOurBattle_hns, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle_hns
	playbgm MUS_B_PYRAMID_TOP, FALSE
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonSilver_hns
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns

BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonSilver_hns::
	frontier_getsymbols
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon_hns
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonFrontierPassPlease_hns, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePyramidTop_Text_ReceivedBraveSymbol_hns
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePyramidTop_Text_LookForwardToNextMeeting_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon_hns

BattleFrontier_BattlePyramidTop_EventScript_BrandonIntroGold_hns::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech_hns
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, BattleFrontier_BattlePyramidTop_Movement_CameraPanUp_hns
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonYouveReturned_hns, MSGBOX_DEFAULT
	closemessage
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer_hns
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidTop_Text_MyCourageIsOffMeter_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon_hnsGold_hns
	end

BattleFrontier_BattlePyramidTop_EventScript_BrandonHeardGoldSpeech_hns::
	applymovement LOCALID_BRANDON, BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer_hns
	waitmovement 0
BattleFrontier_BattlePyramidTop_EventScript_BattleBrandon_hnsGold_hns::
	msgbox BattleFrontier_BattlePyramidTop_Text_EverythingYouHave_hns, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle_hns
	playbgm MUS_B_PYRAMID_TOP, FALSE
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonGold_hns
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobby_hnsLost_hns

BattleFrontier_BattlePyramidTop_EventScript_DefeatedBrandonGold_hns::
	frontier_getsymbols
	goto_if_eq VAR_RESULT, 2, BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon_hns
	msgbox BattleFrontier_BattlePyramidTop_Text_BrandonRemarkableHaveThis_hns, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePyramidTop_Text_BraveSymbolTookGoldenShine_hns
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePyramidTop_Text_FarewellForNow_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidTop_EventScript_WarpToLobbyWon_hns

BattleFrontier_BattlePyramidTop_EventScript_DoBrandonBattle_hns::
	closemessage
	dofacilitytrainerbattle FACILITY_BATTLE_PYRAMID
	waitstate
	return

BattleFrontier_BattlePyramidTop_Movement_AttendantMoveAside_hns:
	walk_right
	walk_in_place_faster_left
	step_end

BattleFrontier_BattlePyramidTop_Movement_AttendantBlockPath_hns:
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattlePyramidTop_Movement_PlayerClimbToTop_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

BattleFrontier_BattlePyramidTop_Movement_BrandonApproachPlayer_hns:
	walk_fast_down
	step_end

BattleFrontier_BattlePyramidTop_Movement_CameraPanUp_hns:
	walk_slow_up
	walk_slow_up
	delay_16
	step_end

BattleFrontier_BattlePyramidTop_Text_ReachedSummitUpYouGo_hns:
	.string "איזה תענוג לראות אותך כאן!\n"
	.string "הגעת לפסגת פירמידת הקרב!\p"
	.string "ממש מעלינו נמצאת נקודת\n"
	.string "התצפית של הפירמידה.\p"
	.string "המקום פתוח רק למי\n"
	.string "שכבש את הפירמידה.\p"
	.string "ועכשיו, בבקשה!\n"
	.string "קדימה, למעלה!$"

BattleFrontier_BattlePyramidTop_Text_PlayerConqueredPyramid_hns:
	.string "כובש הפירמידה החדש!\n"
	.string "שכולם יכירו את השם {PLAYER}!$"

BattleFrontier_BattlePyramidTop_Text_ChiefBeatYouHere_hns:
	.string "איזה תענוג לראות אותך כאן!\p"
	.string "למרבה הצער, הגעת שני\n"
	.string "בהפרש של שבריר שנייה!\p"
	.string "הבוס שלנו כבר כבש\n"
	.string "את הפירמידה לפניך.\p"
	.string "אבל, חוקר צעיר שלי…\n"
	.string "אתה מאמן!\p"
	.string "הפגן את כוחך וקח מהבוס שלנו\n"
	.string "את תהילת הפסגה!\p"
	.string "ועכשיו, בבקשה! כשתהיה מוכן,\n"
	.string "עשה עוד צעד אמיץ אחד!$"

BattleFrontier_BattlePyramidTop_Text_ExplorationsAreGrandestAdventure_hns:
	.string "הרפתקן צעיר…\p"
	.string "אתה לא מסכים שמסעות גילוי\n"
	.string "הם ההרפתקה הגדולה מכולן?\p"
	.string "התושייה שלך!\p"
	.string "הכוח שלך!\p"
	.string "הפוקימונים שלך!\p"
	.string "ומעל לכל, רק האומץ שלך\n"
	.string "שיוביל אותך דרך עולמות לא נודעים…$"

BattleFrontier_BattlePyramidTop_Text_ImPyramidKingBrandon_hns:
	.string "אה, כן, החיים האלה באמת נהדרים!\n"
	.string "נהדרים, בהחלט! הא?\p"
	.string "אני ברנדון!\p"
	.string "אני מלך הפירמידה, כלומר\n"
	.string "אני האחראי כאן.\p"
	.string "רוב האנשים קוראים לי הבוס!\p"
	.string "אם הגעת לכאן, סימן שיש לך\n"
	.string "המון ביטחון עצמי, נכון?\p"
	.string "חה-חה-חה!\n"
	.string "זה הולך להיות מרגש!$"

BattleFrontier_BattlePyramidTop_Text_BringCourageToOurBattle_hns:
	.string "ובכן!\n"
	.string "הראה לי את האומץ שלך בקרב שלנו!$"

BattleFrontier_BattlePyramidTop_Text_BrandonFrontierPassPlease_hns:
	.string "ברנדון: חה-חה-חה! זה היה נהדר!\n"
	.string "נהדר, כן, בהחלט!\p"
	.string "כל הכבוד! מגיעה לך הכרה!\n"
	.string "את כרטיס חזית הקרב שלך, בבקשה!$"

BattleFrontier_BattlePyramidTop_Text_ReceivedBraveSymbol_hns:
	.string "סמל התעוזה הוטבע על\n"
	.string "כרטיס חזית הקרב!$"

BattleFrontier_BattlePyramidTop_Text_LookForwardToNextMeeting_hns:
	.string "חוקר צעיר!\n"
	.string "אני מצפה למפגש הבא שלנו!$"

BattleFrontier_BattlePyramidTop_Text_BrandonYouveReturned_hns:
	.string "ברנדון: …סוף סוף חזרת,\n"
	.string "חוקר צעיר…\p"
	.string "נראה שאהבת ההרפתקאות שלך\n"
	.string "באה מעומק ליבך…\p"
	.string "כן… אתה בדיוק כמו שאני הייתי\n"
	.string "בצעירותי…\p"
	.string "… … …אה…\p"
	.string "התשוקה!\p"
	.string "הסכנה!\p"
	.string "הייאוש!\p"
	.string "חוזרים אותם ימים של הרפתקאות\n"
	.string "שמתריסות מול המוות ומלאות חיים…$"

BattleFrontier_BattlePyramidTop_Text_MyCourageIsOffMeter_hns:
	.string "ובכן!\p"
	.string "אני מרגיש שהאומץ שלי\n"
	.string "חורג מכל מדד!$"

BattleFrontier_BattlePyramidTop_Text_EverythingYouHave_hns:
	.string "תן את כל מה שיש לך!\n"
	.string "אני מוכן לכל דבר!$"

BattleFrontier_BattlePyramidTop_Text_BrandonRemarkableHaveThis_hns:
	.string "ברנדון: חה-חה-חה! מדהים!\n"
	.string "כן, זה באמת נהדר!\p"
	.string "חוקר צעיר!\p"
	.string "ניצחת אותי לגמרי, בכל מובן!\n"
	.string "הנה! אני רוצה שזה יהיה שלך!$"

BattleFrontier_BattlePyramidTop_Text_BraveSymbolTookGoldenShine_hns:
	.string "סמל התעוזה קיבל\n"
	.string "ברק זהוב!$"

BattleFrontier_BattlePyramidTop_Text_FarewellForNow_hns:
	.string "אה, כן! זה רק מראה שיש לי\n"
	.string "עוד הרבה מה ללמוד!\p"
	.string "שדרכינו ייפגשו שוב!\n"
	.string "להתראות בינתיים, חוקר צעיר!$"

BattleFrontier_BattlePyramidTop_Text_StepForwardWhenReady_hns:
	.string "עכשיו, כשתהיה מוכן, אזור אומץ\n"
	.string "וצעד קדימה.$"

