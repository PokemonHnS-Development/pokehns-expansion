Mahoganytown_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Mahoganytown_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Mahoganytown_OnFrame
	.byte 0

Mahoganytown_OnLoad::
	call_if_ge VAR_MAHOGANY_TOWN_STATE, 13, MahoganyTown_EventScript_FixTree
	end

MahoganyTown_EventScript_FixTree::
	setmetatile 18, 8, 0x378, FALSE
	setmetatile 19, 8, 0x379, FALSE
	end

Mahoganytown_OnFrame::
	map_script_2 VAR_TRIGGER_ELM_ROCKET_CALL, 1, Mahoganytown_EventScript_RocketTrigger
	.2byte 0

Mahoganytown_EventScript_RocketTrigger::
	lock
	setspeaker Route30_Text_ElmName
	pokenavcall ElmPhoneRadioTowerRocketTakeoverText
	waitmessage
	setvar VAR_GOLDENROD_CITY_STATE, 6
	clearflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	setflag FLAG_HIDE_GOLDENROD_NPCS
	clearflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setvar VAR_MAHOGANY_TOWN_STATE, 16
	setvar VAR_TRIGGER_ELM_ROCKET_CALL, 2
	delay 10
	release
	end

MahoganyTown_EventScript_TownTrigger::
	clearflag FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	clearflag FLAG_HIDE_MAHOGANY_TOWN_FATMAN
	clearflag FLAG_HIDE_MAHOGANY_ROCKETS
	clearflag FLAG_GOT_TM_FROM_MAHOGANY_COP
	clearflag FLAG_GOT_BLACK_BELT
	clearflag FLAG_ROCKETHIDEOUT_SWITCH
	clearflag FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	clearflag FLAG_HIDE_ROCKETHIDEOUT2_GATE
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_GATE
	clearflag FLAG_GOT_PASSWORD_FROM_ETO
	clearflag FLAG_GOT_PASSWORD_FROM_GRUNTF 
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROW
	clearflag FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI
	clearflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE1 
	clearflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE2
	clearflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE3 
	clearflag FLAG_GOT_HIDDEN_POWER
	clearflag FLAG_HIDE_ICE_PATH_KIMONO

	setflag FLAG_VISITED_MAHOGANY_TOWN
	setflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	setflag FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	setflag FLAG_HIDE_MAHOGANY_COP
	setflag FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	setflag FLAG_HIDE_ROCKETHIDEOUT3_SILVER
	setflag FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT

	setvar VAR_ROCKET_HIDEOUT_STATUE_1, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_2, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_3, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_4, 0
	setvar VAR_ROCKET_HIDEOUT_STATUE_5, 0
	setvar VAR_ROCKET_PASSWORD, 0
	setvar VAR_ELECTRODES_FAINTED, 0
	setvar VAR_LAKE_OF_RAGE_FISHERMAN, 0
	setvar VAR_ICE_PATH_STATE, 0
	setvar VAR_ROUTE27_BAOBA_CALL, 0

	setvar VAR_MAHOGANY_TOWN_STATE, 1

	@blackthorn flagheap
	setvar VAR_BLACKTHORN_CITY_STATE, 1
    setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_SILVER
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_LANCE
	setflag FLAG_HIDE_DRAGONS_DEN_SHRINE_CLAIR
	clearflag FLAG_GOT_SPELL_TAG
	clearflag FLAG_GOT_DRATINI
	setvar VAR_BLACKTHORN_GYM_STATE, 0
	setvar VAR_DRAGONS_DEN_QUIZ, 0
	end

MahoganyTown_EventScript_MerchantTrigger::
	lock
	turnobject LOCALID_MAHOGANY_MERCHANT, DIR_SOUTH
	playse SE_PIN
	applymovement LOCALID_MAHOGANY_MERCHANT, Common_Movement_ExclamationMark
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_1, 14, MahoganyTown_EventScript_WalkUp2
	call_if_eq VAR_TEMP_1, 13, MahoganyTown_EventScript_WalkUp1
	showmoneybox 0, 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantRefused
	checkmoney 300, 0
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantBroke
	removemoney 300
	updatemoneybox 0
	playse SE_SHOP
	msgbox MahoganyTown_Text_RageCandyBarMerchantSavorIt, MSGBOX_DEFAULT
	giveitem ITEM_RAGE_CANDY_BAR
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_WalkUp1::
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyTown_Movement_PlayerMerchant1
	waitmovement 0
	return

MahoganyTown_EventScript_WalkUp2::
	applymovement OBJ_EVENT_ID_PLAYER, MahoganyTown_Movement_PlayerMerchant2
	waitmovement 0
	return

MahoganyTown_EventScript_Merchant::
	lock
	faceplayer
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 17, MahoganyTown_EventScript_MerchantAfter
	showmoneybox 0, 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantTryOne, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantRefused
	checkmoney 300, 0
	goto_if_eq VAR_RESULT, FALSE, MahoganyTown_EventScript_MerchantBroke
	removemoney 300
	updatemoneybox 0
	msgbox MahoganyTown_Text_RageCandyBarMerchantSavorIt, MSGBOX_DEFAULT
	giveitem ITEM_RAGE_CANDY_BAR
	hidemoneybox
	closemessage
	release
	end

MahoganyTown_EventScript_MerchantRefused::
	msgbox MahoganyTown_Text_RageCandyBarMerchantRefused, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_MerchantBroke::
	msgbox MahoganyTown_Text_RageCandyBarMerchantNotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	end

MahoganyTown_EventScript_NotEnoughSpace:
	msgbox MahoganyTown_Text_RageCandyBarMerchantRefused, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 30, MahoganyTown_EventScript_PushPlayer
	release
	return

MahoganyTown_EventScript_MerchantAfter::
	msgbox MahoganyTown_Text_RageCandyBarMerchantSoldOut, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_PushPlayer::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft1
	waitmovement 0
	return

MahoganyTown_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 6, MahoganyTown_EventScript_GrampsAfter
	msgbox MahoganyTown_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_GrampsAfter::
	msgbox MahoganyTown_Text_GrampsClearedRocketHideout, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Fisher::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Lass::
	lock
	faceplayer
	msgbox MahoganyTown_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

MahoganyTown_EventScript_Sign::
	lock
	msgbox MahoganyTown_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_EventScript_CandybarSign::
	lock
	msgbox MahoganyTown_Text_RagecandybarSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_EventScript_GymSign::
	lock
	msgbox MahoganyTown_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

MahoganyTown_Movement_PlayerMerchant1:
	walk_up
	step_end

MahoganyTown_Movement_PlayerMerchant2:
	walk_up
	walk_up
	step_end

MahoganyTown_Text_RageCandyBarMerchantTryOne:
	.string "היי, ילד!\p"
	.string "אני רואה שאתה חדש בעיירה מהגוני.\p"
	.string "וכיוון שאתה חדש, כדאי לך לטעום\n"
	.string "חטיף זעם טעים!\p"
	.string "עכשיו הוא יכול להיות שלך תמורת\n"
	.string "¥300 בלבד! רוצה אחד?$"

MahoganyTown_Text_RageCandyBarMerchantSavorIt:
    .string "יופי! תיהנה ממנו!$"

MahoganyTown_Text_RageCandyBarMerchantNotEnoughMoney:
    .string "אין לך מספיק כסף.$"

MahoganyTown_Text_RageCandyBarMerchantRefused:
    .string "אה, טוב, שיהיה…$"

MahoganyTown_Text_RageCandyBarMerchantSoldOut:
    .string "חטיפי הזעם אזלו.\p"
    .string "אני מקפל את הדוכן. אל תפריע לי, ילד.$"

MahoganyTown_Text_Gramps:
    .string "אתה בדרך לראות את הגרידוס\n"
    .string "משתוללים באגם?$"

MahoganyTown_Text_GrampsClearedRocketHideout:
    .string "המג'יקארפ חזרו לאגם הזעם.\p"
    .string "אלה בטח חדשות טובות\n"
    .string "לדייגים שם.$"

MahoganyTown_Text_Fisher:
    .string "אם כבר הגעת עד לכאן, תמצא זמן\n"
    .string "לטייל קצת באזור.\p"
    .string "כדאי לך ללכת צפונה ולבקר\n"
    .string "באגם הזעם, כבר עכשיו.$"

MahoganyTown_Text_Lass:
    .string "כדאי לבקר בחנות של סבתא. היא\n"
    .string "מוכרת דברים שאין לאף אחד אחר.$"

MahoganyTown_Text_Sign:
    .string "העיירה מהגוני\p"
    .string "ברוכים הבאים למולדת הנינג'ות$"

MahoganyTown_Text_RagecandybarSign:
    .string "בביקור בעיירה מהגוני, כדאי\n"
    .string "לטעום חטיף זעם!$"

MahoganyTown_Text_GymSign:
    .string "מכון הפוקימון של העיירה מהגוני\p"
    .string "מנהיג: פרייס\p"
    .string "המורה לחומרת החורף$"

ElmPhoneRadioTowerRocketTakeoverText:
	.string "פרופ' אלם: {PLAYER}, איך הולך?\p"
	.string "התקשרתי כי משהו מוזר קורה\n"
	.string "בשידורי הרדיו.\p"
	.string "דיברו שם על צוות רוקט.\p"
	.string "{PLAYER}, אתה יודע משהו על זה?\p"
	.string "אולי צוות רוקט חזר.\n"
	.string "לא, זה פשוט לא יכול להיות.\p"
	.string "סליחה שהטרדתי.\n"
	.string "שמור על עצמך!$"

