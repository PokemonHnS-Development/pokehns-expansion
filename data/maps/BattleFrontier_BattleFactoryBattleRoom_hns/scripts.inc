@ On this map the player will automatically walk into the room, but the camera is supposed to remain still.
@ To do this GF sets the player (LOCALID_PLAYER) invisible and creates a fake player object (LOCALID_FACTORY_BATTLE_PLAYER).
@ The graphics of this fake player object are represented with VAR_OBJ_GFX_ID_F.
@ The graphics of the opponent are represented with VAR_OBJ_GFX_ID_0, which will ultimately be set by factory_setopponentgfx.

BattleFrontier_BattleFactoryBattleRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleFactoryBattleRoom_OnTransition_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryBattleRoom_OnWarp_hns
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryBattleRoom_OnFrame_hns
	.byte 0

BattleFrontier_BattleFactoryBattleRoom_OnTransition_hns:
	frontier_settrainers
	checkplayergender
	call_if_eq VAR_RESULT, MALE, BattleFrontier_BattleFactoryBattleRoom_EventScript_SetPlayerGfxMale_hns
	call_if_eq VAR_RESULT, FEMALE, BattleFrontier_BattleFactoryBattleRoom_EventScript_SetPlayerGfxFemale_hns
	frontier_getbrainstatus
	copyvar VAR_TEMP_F, VAR_RESULT
	goto_if_ne VAR_RESULT, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattleFactoryBattleRoom_EventScript_SetUpFactoryHeadObj_hns
	end

BattleFrontier_BattleFactoryBattleRoom_EventScript_SetUpFactoryHeadObj_hns::
	call BattleFrontier_EventScript_SetBrainObjectGfx
	setobjectxyperm LOCALID_FACTORY_BATTLE_OPPONENT, 7, 9
	end

BattleFrontier_BattleFactoryBattleRoom_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryBattleRoom_EventScript_HideObjects_hns
	.2byte 0

BattleFrontier_BattleFactoryBattleRoom_EventScript_HideObjects_hns::
	setvar VAR_TEMP_1, 1
	hideobjectat LOCALID_PLAYER, MAP_BATTLE_FRONTIER_BATTLE_FACTORY_BATTLE_ROOM_HNS
	goto_if_ne VAR_TEMP_F, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattleFactoryBattleRoom_EventScript_EndHideObjects_hns
	hideobjectat LOCALID_FACTORY_BATTLE_OPPONENT, MAP_BATTLE_FRONTIER_BATTLE_FACTORY_BATTLE_ROOM_HNS
BattleFrontier_BattleFactoryBattleRoom_EventScript_EndHideObjects_hns::
	end

BattleFrontier_BattleFactoryBattleRoom_EventScript_SetPlayerGfxMale_hns::
	setvar VAR_OBJ_GFX_ID_F, OBJ_EVENT_GFX_GOLD_NORMAL_HNS
	return

BattleFrontier_BattleFactoryBattleRoom_EventScript_SetPlayerGfxFemale_hns::
	setvar VAR_OBJ_GFX_ID_F, OBJ_EVENT_GFX_KRIS_NORMAL_HNS
	return

BattleFrontier_BattleFactoryBattleRoom_OnFrame_hns:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleFactoryBattleRoom_EventScript_EnterRoom_hns
	.2byte 0

BattleFrontier_BattleFactoryBattleRoom_EventScript_EnterRoom_hnsFactoryHeadBattle_hns::
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_GetAMoveOn_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FACTORY_BATTLE_OPPONENT, BattleFrontier_BattleFactoryBattleRoom_Movement_NolandMoveToBattle_hns
	applymovement LOCALID_FACTORY_BATTLE_PLAYER, BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerEnterRoom_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerEnterRoom_hns
	waitmovement 0
	call BattleFrontier_BattleFactoryBattleRoom_EventScript_ScientistsFaceBattle_hns
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleOpponent_hns
	end

BattleFrontier_BattleFactoryBattleRoom_EventScript_EnterRoom_hns::
	goto_if_ne VAR_TEMP_F, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattleFactoryBattleRoom_EventScript_EnterRoom_hnsFactoryHeadBattle_hns
	applymovement LOCALID_FACTORY_BATTLE_PLAYER, BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerEnterRoom_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerEnterRoom_hns
	waitmovement 0
	call BattleFrontier_BattleFactoryBattleRoom_EventScript_ScientistsFaceBattle_hns
	factory_setopponentgfx
	removeobject LOCALID_FACTORY_BATTLE_OPPONENT
	setobjectxyperm LOCALID_FACTORY_BATTLE_OPPONENT, 7, 1
	addobject LOCALID_FACTORY_BATTLE_OPPONENT
	applymovement LOCALID_FACTORY_BATTLE_OPPONENT, BattleFrontier_BattleFactoryBattleRoom_Movement_OpponentEnter_hns
	waitmovement 0
BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleOpponent_hns::
	goto_if_ne VAR_TEMP_F, FRONTIER_BRAIN_NOT_READY, BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hns
	palace_getopponentintro
	lockall
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	dofacilitytrainerbattle FRONTIER_FACILITY_FACTORY
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedOpponent_hns
BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsLost_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hns

BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedOpponent_hns::
	factory_get FACTORY_DATA_WIN_STREAK_SWAPS
	goto_if_eq VAR_RESULT, MAX_STREAK, BattleFrontier_BattleFactoryBattleRoom_EventScript_IncrementWinStreak_hns
	addvar VAR_RESULT, 1
	setorcopyvar VAR_0x8006, VAR_RESULT
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS  @ uses VAR_0x8006 above
BattleFrontier_BattleFactoryBattleRoom_EventScript_IncrementWinStreak_hns::
	call BattleFrontier_EventScript_IncrementWinStreak
BattleFrontier_BattleFactoryBattleRoom_EventScript_IncrementBattleNum_hns::
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	switch VAR_RESULT
	case 7, BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsWon_hns
	setvar VAR_0x8006, 1
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM_HNS, 8, 8
	waitstate
BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsWon_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_WON
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hns

BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hns::
	switch VAR_TEMP_F
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattleFactoryBattleRoom_EventScript_IntroNolandGold_hns
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hnsSilver_hns
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hnsGold_hns
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hnsSilver_hns
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_NolandImFactoryHead_hns, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hnsSilver_hns::
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_ShakeOutKnowledgeBringItOn_hns, MSGBOX_DEFAULT
	call BattleFrontier_BattleFactoryBattleRoom_EventScript_DoNolandBattle_hns
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hnsSilver_hns
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsLost_hns

BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hnsSilver_hns::
	frontier_getsymbols
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hns
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_NolandLetsSeeFrontierPass_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FACTORY_BATTLE_PLAYER, BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerApproachNoland_hns
	waitmovement 0
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleFactoryBattleRoom_Text_ReceivedKnowledgeSymbol_hns
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_NextTimeNoHoldsBarred_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hns

BattleFrontier_BattleFactoryBattleRoom_EventScript_IntroNolandGold_hns::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hnsGold_hns
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_HarderLookThanLastTime_hns, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattleFactoryBattleRoom_EventScript_BattleNoland_hnsGold_hns::
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_AllRightBringItOn_hns, MSGBOX_DEFAULT
	call BattleFrontier_BattleFactoryBattleRoom_EventScript_DoNolandBattle_hns
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hnsGold_hns
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsLost_hns

BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hnsGold_hns::
	frontier_getsymbols
	goto_if_eq VAR_RESULT, 2, BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hns
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_OutOfMyLeagueLetsSeePass_hns, MSGBOX_DEFAULT
	waitmessage
	applymovement LOCALID_FACTORY_BATTLE_PLAYER, BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerApproachNoland_hns
	waitmovement 0
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattleFactoryBattleRoom_Text_KnowledgeSymbolTookGoldenShine_hns
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattleFactoryBattleRoom_Text_LastTimeILoseToYou_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hns

BattleFrontier_BattleFactoryBattleRoom_EventScript_DoNolandBattle_hns::
	closemessage
	frontier_set FRONTIER_DATA_RECORD_DISABLED, FALSE
	special HealPlayerParty
	dofacilitytrainerbattle FACILITY_BATTLE_FACTORY
	waitstate
	return

BattleFrontier_BattleFactoryBattleRoom_EventScript_DefeatedNoland_hns::
	factory_get FACTORY_DATA_WIN_STREAK_SWAPS
	goto_if_eq VAR_RESULT, MAX_STREAK, BattleFrontier_BattleFactoryBattleRoom_EventScript_IncrementWinStreak_hns
	addvar VAR_RESULT, 1
	setorcopyvar VAR_0x8006, VAR_RESULT
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS  @ uses VAR_0x8006 above
	factory_get FACTORY_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, MAX_STREAK, BattleFrontier_BattleFactoryBattleRoom_EventScript_IncrementBattleNum_hns
	addvar VAR_RESULT, 1
	factory_set FACTORY_DATA_WIN_STREAK, VAR_RESULT
	frontier_get FRONTIER_DATA_BATTLE_NUM
	addvar VAR_RESULT, 1
	goto BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsWon_hns
	end

BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerEnterRoom_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

BattleFrontier_BattleFactoryBattleRoom_Movement_PlayerApproachNoland_hns:
	walk_right
	step_end

BattleFrontier_BattleFactoryBattleRoom_Movement_OpponentEnter_hns:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	face_left
	step_end

BattleFrontier_BattleFactoryBattleRoom_Movement_NolandMoveToBattle_hns:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hns::
	copyvar VAR_RESULT, VAR_FRONTIER_BATTLE_MODE
	goto_if_eq VAR_RESULT, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsDoubles_hns
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_LOBBY_HNS, 4, 8
	waitstate
	end

BattleFrontier_BattleFactoryBattleRoom_EventScript_WarpToLobby_hnsDoubles_hns::
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_LOBBY_HNS, 14, 8
	waitstate
	end

BattleFrontier_BattleFactoryBattleRoom_EventScript_ScientistsFaceBattle_hns::
	applymovement LOCALID_FACTORY_BATTLE_SCIENTIST_1, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_FACTORY_BATTLE_SCIENTIST_2, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_FACTORY_BATTLE_SCIENTIST_3, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_FACTORY_BATTLE_SCIENTIST_4, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_FACTORY_BATTLE_SCIENTIST_5, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_FACTORY_BATTLE_SCIENTIST_6, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

BattleFrontier_BattleFactoryBattleRoom_Text_GetAMoveOn_hns:
	.string "היי, היי!\n"
	.string "קדימה, לזוז!$"

BattleFrontier_BattleFactoryBattleRoom_Text_NolandImFactoryHead_hns:
	.string "היי, קוראים לי נולנד! בעצם אני\n"
	.string "האחראי כאן, ולכן אני ראש המפעל!\p"
	.string "הצצתי בנתוני החלפת הקרב שלך.\p"
	.string "נראה שיש לך את הרעיון הנכון,\n"
	.string "אבל הראש שלך עדיין מרובע!\p"
	.string "תקשיב טוב, בסדר? ידע זה לא רק\n"
	.string "לקרוא ספרים או לעבוד ליד שולחן.\p"
	.string "אם עושים רק דברים כאלה…\n"
	.string "זה כמעט חסר תועלת!\p"
	.string "צריך לחוות דברים עם הלב\n"
	.string "ועם הגוף, ברור?\p"
	.string "אתמודד מולך בדיוק\n"
	.string "באותם תנאים כמוך.\p"
	.string "גם אני אשתמש בפוקימונים שכורים!$"

BattleFrontier_BattleFactoryBattleRoom_Text_ShakeOutKnowledgeBringItOn_hns:
	.string "תשלוף כל פירור של ידע\n"
	.string "שיש לך, ובוא נראה אותך!$"

BattleFrontier_BattleFactoryBattleRoom_Text_NolandLetsSeeFrontierPass_hns:
	.string "נולנד: מהלך חכם!\n"
	.string "בוא נראה את כרטיס חזית הקרב שלך.$"

BattleFrontier_BattleFactoryBattleRoom_Text_ReceivedKnowledgeSymbol_hns:
	.string "סמל הידע הוטבע\n"
	.string "על כרטיס חזית הקרב!$"

BattleFrontier_BattleFactoryBattleRoom_Text_NextTimeNoHoldsBarred_hns:
	.string "הה…\n"
	.string "יש לך ראש די חריף…\p"
	.string "בפעם הבאה, אני לא אחסוך ממך.\n"
	.string "בלי הנחות, ברור?\p"
	.string "ותמשיך ללמוד!$"

BattleFrontier_BattleFactoryBattleRoom_Text_HarderLookThanLastTime_hns:
	.string "נולנד: היי, היי! מה נשמע?\n"
	.string "הלימודים מתקדמים?\p"
	.string "…אה?\p"
	.string "יש לך מבט קשוח יותר\n"
	.string "מאשר בפעם הקודמת שראיתי אותך.\p"
	.string "עכשיו זה יהיה כיף!\n"
	.string "אני מתחיל להתלהב, היי!$"

BattleFrontier_BattleFactoryBattleRoom_Text_AllRightBringItOn_hns:
	.string "בסדר גמור!\n"
	.string "קדימה, לקרב!$"

BattleFrontier_BattleFactoryBattleRoom_Text_OutOfMyLeagueLetsSeePass_hns:
	.string "נולנד: מה זה…\n"
	.string "אתה כבר משחק בליגה אחרת!\p"
	.string "אוף!\n"
	.string "בוא נראה את כרטיס חזית הקרב!$"

BattleFrontier_BattleFactoryBattleRoom_Text_KnowledgeSymbolTookGoldenShine_hns:
	.string "סמל הידע קיבל\n"
	.string "ברק זהוב!$"

BattleFrontier_BattleFactoryBattleRoom_Text_LastTimeILoseToYou_hns:
	.string "פפף, נו באמת!\p"
	.string "זו בהחלט הפעם האחרונה\n"
	.string "שאני מפסיד לך!\p"
	.string "חייבים לעשות את זה שוב, היי?$"

