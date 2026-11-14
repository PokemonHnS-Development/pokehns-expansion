Route13_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route13_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	map_script MAP_SCRIPT_ON_RESUME, Route13_hns_MapScripts_MAP_SCRIPT_ON_RESUME
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route13_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	.byte 0

Route13_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
	call Route13_OnTransition
	return

Route13_hns_MapScripts_MAP_SCRIPT_ON_RESUME:
	call SetTimeEncounters
	return

Route13_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
	map_script_2 VAR_ALOLA_TRAVEL, 2, Route13_GetOffBoat
	.2byte 0

Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
	map_script_2 VAR_ALOLA_TRAVEL, 2, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0
	.2byte 0

Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0:
	applymovement Route13_Alola_Captain, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	applymovement LOCALID_PLAYER, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	return


Route13_OnTransition:
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 77, Route13_OnTransitionBoat
	callnative SetTimeBasedEncounters
	end

Route13_OnTransitionBoat::
	@addobject LOCALID_ROUTE13_BOAT
	clearflag FLAG_HIDE_ROUTE13_BOAT
	setobjectxyperm LOCALID_ROUTE13_BOAT, 78, 28
	return

Route13_EventScript_Alex::
	trainerbattle_single TRAINER_ALEX_HNS, Route13_Text_PokefanmAlexSeen, Route13_Text_PokefanmAlexBeaten, Route13_EventScript_RegisterAlex
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route13_EventScript_RematchAlex
	msgbox Route13_Text_PokefanmAlexAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_RegisterAlex::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route13_Text_AlexRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ALEX_HNS
	release
	end

Route13_EventScript_RematchAlex::
	trainerbattle_rematch TRAINER_ALEX_HNS, Route13_Text_AlexRematchIntro, Route13_Text_AlexRematchDefeat
	msgbox Route13_Text_AlexPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_ALEX_2_HNS, Route13_EventScript_RematchAlexTryGiveItem
	end

Route13_EventScript_RematchAlexTryGiveItem::
	checkitem ITEM_RED_SHARD
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_RED_SHARD
	closemessage
	end

Route13_EventScript_Joshua::
	trainerbattle_single TRAINER_JOSHUA_HNS, Route13_Text_PokefanmJoshuaSeen, Route13_Text_PokefanmJoshuaBeaten
	msgbox Route13_Text_PokefanmJoshuaAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Perry::
	trainerbattle_single TRAINER_PERRY_HNS, Route13_Text_BirdKeeperPerrySeen, Route13_Text_BirdKeeperPerryBeaten
	msgbox Route13_Text_BirdKeeperPerryAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Bret::
	trainerbattle_single TRAINER_BRET_HNS, Route13_Text_BirdKeeperBretSeen, Route13_Text_BirdKeeperBretBeaten
	msgbox Route13_Text_BirdKeeperBretAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_Kenny::
	trainerbattle_single TRAINER_KENNY_HNS, Route13_Text_HikerKennySeen, Route13_Text_HikerKennyBeaten, Route13_EventScript_RegisterKenny
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route13_EventScript_RematchKenny
	msgbox Route13_Text_HikerKennyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route13_EventScript_RegisterKenny::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route13_Text_KennyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KENNY_HNS
	release
	end

Route13_EventScript_RematchKenny::
	trainerbattle_rematch TRAINER_KENNY_HNS, Route13_Text_KennyRematchIntro, Route13_Text_KennyRematchDefeat
	msgbox Route13_Text_KennyPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_KENNY_2_HNS, Route13_EventScript_RematchKennyTryGiveItem
	end

Route13_EventScript_RematchKennyTryGiveItem::
	checkitem ITEM_TM_STONE_EDGE
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_STONE_EDGE
	closemessage
	end

Route13_EventScript_TrainerTips::
	msgbox Route13_Text_TrainerTips, MSGBOX_SIGN
	end

Route13_EventScript_RouteSign::
	msgbox Route13_Text_Sign, MSGBOX_SIGN
	end

Route13_EventScript_DirectionsSign::
	msgbox Route13_Text_DirectionsSign, MSGBOX_SIGN
	end

Route13_Text_PokefanmAlexSeen:
	.string "השתחווה בפני הפוקימונים\n"
	.string "המלכותיים שלי!$"

Route13_Text_PokefanmAlexBeaten:
	.string "איך… איך אתה מעז ללעוג למלוכה!$"

Route13_Text_PokefanmAlexAfterBattle:
	.string "מי לא חולם להיות\n"
	.string "מלך יום אחד?$"

Route13_Text_AlexRegister:
	.string "אין לך דם כחול, אבל יש לך כישרון.\n"
	.string "אשמח לקבל את המספר שלך.$"

Route13_Text_AlexRematchIntro:
	.string "צירפתי אבירים לחצר שלי!\n"
	.string "קדימה, לקרב!$"

Route13_Text_AlexRematchDefeat:
	.string "שוב הודחתי מהכס…$"

Route13_Text_AlexPostRematch:
	.string "אולי בסך הכול אני רק רגלי.$"

Route13_Text_PokefanmJoshuaSeen:
	.string "ניהיהי! רוצה להילחם\n"
	.string "בכנופיית הפיקאצ'ו שלי?$"

Route13_Text_PokefanmJoshuaBeaten:
	.string "פי-פיקאצ'ו!$"

Route13_Text_PokefanmJoshuaAfterBattle:
	.string "נראה שיש לך הרבה פוקימונים, אבל\n"
	.string "פיקאצ'ו עדיין הכי טוב.$"

Route13_Text_BirdKeeperPerrySeen:
	.string "זריזות היא התכונה החשובה ביותר\n"
	.string "של פוקימוני ציפורים.$"

Route13_Text_BirdKeeperPerryBeaten:
	.string "המהירות שלך ניצחה אותי…$"

Route13_Text_BirdKeeperPerryAfterBattle:
	.string "הפוקימונים שלך מאומנים\n"
	.string "היטב להפליא.$"

Route13_Text_BirdKeeperBretSeen:
	.string "תראה את הפוקימונים שלי. רק תסתכל\n"
	.string "על הצבעים ועל הנוצות שלהם.$"

Route13_Text_BirdKeeperBretBeaten:
	.string "אוף! לא מספיק טוב!$"

Route13_Text_BirdKeeperBretAfterBattle:
	.string "פוקימונים שמטפחים אותם\n"
	.string "נעשים שמחים.$"

Route13_Text_HikerKennySeen:
	.string "כדאי שאלך למערת האבן כדי\n"
	.string "להשיג לעצמי אוניקס.$"

Route13_Text_HikerKennyBeaten:
	.string "הפסדתי…$"

Route13_Text_HikerKennyAfterBattle:
	.string "נראה שתצורות גיאולוגיות\n"
	.string "לא משתנות.\p"
	.string "אבל בעצם הן משתנות,\n"
	.string "לאט לאט.$"

Route13_Text_KennyRegister:
	.string "אולי גם פוקימונים משתנים עם הזמן.\n"
	.string "נילחם שוב מתישהו!$"

Route13_Text_KennyRematchIntro:
	.string "למדתי מהגיאולוגיה!\n"
	.string "קדימה!$"

Route13_Text_KennyRematchDefeat:
	.string "עדיין לא מספיק…$"

Route13_Text_KennyPostRematch:
	.string "הכוח של פוקימונים הוא כמו\n"
	.string "סחיפה. אנחנו נתמיד!$"

Route13_Text_TrainerTips:
	.string "TRAINER TIPS\p"
	.string "Look! Right there, at the left\n"
	.string "side of the post.$"

Route13_Text_Sign:
	.string "דרך 13\p"
	.string "צפונה אל גשר השקט$"

Route13_Text_DirectionsSign:
	.string "צפונה אל העיירה לבנדר\p"
	.string "מערבה אל העיר פושיה$"

Route13_GetOffBoat::
	lock
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 77
	goto_if_ne Route13_GetOffBoat_2
	compare VAR_TEMP_1, 26
	goto_if_ne Route13_GetOffBoat_2
	delay 30
	applymovement Route13_Alola_Captain, Route13_GetOffBoat_Movement_0
	applymovement LOCALID_PLAYER, Route13_GetOffBoat_Movement_1
	waitmovement 0
	msgbox Route13_GetOffBoat_Text_0, MSGBOX_AUTOCLOSE
	setvar VAR_ALOLA_TRAVEL, 0
	applymovement LOCALID_ROUTE13_BOAT, Route13_TravelToAlola_Movement_2
	waitmovement 0
	setobjectxyperm LOCALID_ROUTE13_BOAT, 89, 28
	removeobject LOCALID_ROUTE13_BOAT
	applymovement LOCALID_PLAYER, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	waitmovement 0
	release
	end

Route13_GetOffBoat_2:
	setvar VAR_ALOLA_TRAVEL, 0
	release
	end


Route13_TravelToAlola::
	lock
	faceplayer
	checkitem ITEM_STRANGE_SOUVENIR
	compare VAR_RESULT, 0
	goto_if_ne Route13_TravelToAlola_1
	msgbox Route13_TravelToAlola_Text_4, MSGBOX_AUTOCLOSE
	release
	end

Route13_TravelToAlola_1:
	goto_if_unset FLAG_VISITED_ALOLA, Route13_TravelToAlola_4
	msgbox Route13_TravelToAlola_Text_3, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route13_TravelToAlola_10
	msgbox Route13_TravelToAlola_Text_2, MSGBOX_AUTOCLOSE
	release
	end

Route13_TravelToAlola_4:
	msgbox Route13_TravelToAlola_Text_0, MSGBOX_DEFAULT
	closemessage
	helpwindow HELP_ALOLA_WINDOW
	msgbox Route13_TravelToAlola_Text_0_5, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route13_TravelToAlola_7
	msgbox Route13_TravelToAlola_Text_2, MSGBOX_AUTOCLOSE
	release
	end

Route13_TravelToAlola_7:
	msgbox Route13_TravelToAlola_Text_1, MSGBOX_AUTOCLOSE
	goto_if_eq VAR_FACING, DIR_SOUTH, Route13_TravelToAlola_14
Route13_TravelToAlola_13:
	addobject LOCALID_ROUTE13_BOAT
	clearflag FLAG_HIDE_ROUTE13_BOAT
	applymovement LOCALID_ROUTE13_BOAT, Route13_Movement_BoatArrive
	waitmovement 0
	applymovement Route13_Alola_Captain, Route13_TravelToAlola_Movement_1
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_1
	waitmovement 0
	fadescreenswapbuffers FADE_TO_BLACK
	hidefollower
	playse SE_EXIT
	special SpawnCameraObject
	hideobjectat LOCALID_PLAYER, MAP_ROUTE13_HNS
	hideobjectat Route13_Alola_Captain, MAP_ROUTE13_HNS
	applymovement OBJ_EVENT_ID_CAMERA, Route13_TravelToAlola_Movement_1
	waitmovement 0
	waitse
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	playse SE_RG_SS_ANNE_HORN

	playse SE_M_SURF
	applymovement LOCALID_ROUTE13_BOAT, Route13_TravelToAlola_Movement_2
	setvar VAR_ALOLA_TRAVEL, 1
	setflag FLAG_HIDE_MELEMELE_TOTEM
	setflag FLAG_HIDE_AKALA_TOTEM
	setflag FLAG_HIDE_ULAULA_TOTEM
	setflag FLAG_HIDE_PONI_TOTEM
	setflag FLAG_HIDE_SAMSONOAK_INTRO
	setflag FLAG_HIDE_TAPU_KOKO
	setflag FLAG_HIDE_TAPU_LELE
	setflag FLAG_HIDE_TAPU_BULU
	setflag FLAG_HIDE_TAPU_FINI
	setflag FLAG_HIDE_FLYOVER
	setflag FLAG_HIDE_PHANT_OUTSIDE
	setflag FLAG_HIDE_PHANT_INSIDE
	delay 90
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE13_BOAT
	special RemoveCameraObject
	warp MAP_MELEMELE_ISLE_HNS, 25, 33
	waitstate
	end

Route13_TravelToAlola_10:
	msgbox Route13_TravelToAlola_Text_1, MSGBOX_AUTOCLOSE
	goto_if_eq VAR_FACING, DIR_SOUTH, Route13_TravelToAlola_17
Route13_TravelToAlola_16:
	addobject LOCALID_ROUTE13_BOAT
	clearflag FLAG_HIDE_ROUTE13_BOAT
	applymovement LOCALID_ROUTE13_BOAT, Route13_Movement_BoatArrive
	waitmovement 0
	applymovement Route13_Alola_Captain, Route13_TravelToAlola_Movement_1
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_1
	waitmovement 0
	fadescreenswapbuffers FADE_TO_BLACK
	hidefollower
	playse SE_EXIT
	special SpawnCameraObject
	hideobjectat LOCALID_PLAYER, MAP_ROUTE13_HNS
	hideobjectat Route13_Alola_Captain, MAP_ROUTE13_HNS
	applymovement OBJ_EVENT_ID_CAMERA, Route13_TravelToAlola_Movement_1
	waitmovement 0
	waitse
	delay 30
	fadescreenswapbuffers FADE_FROM_BLACK
	playse SE_RG_SS_ANNE_HORN
	waitse
	playse SE_M_SURF
	applymovement LOCALID_ROUTE13_BOAT, Route13_TravelToAlola_Movement_2
	setvar VAR_ALOLA_TRAVEL, 1
	delay 90
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE13_BOAT
	special RemoveCameraObject
	warp MAP_MELEMELE_ISLE_HNS, 25, 33
	waitstate
	end

Route13_TravelToAlola_14:
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_0
	waitmovement 0
	goto Route13_TravelToAlola_13

Route13_TravelToAlola_17:
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_0
	waitmovement 0
	goto Route13_TravelToAlola_16


Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0:
	face_up
	step_end

Route13_GetOffBoat_Movement_0:
	face_left
	step_end

Route13_GetOffBoat_Movement_1:
	face_right
	step_end

Route13_TravelToAlola_Movement_0:
	walk_left
	walk_down
	step_end

Route13_TravelToAlola_Movement_1:
	walk_down
	step_end

Route13_TravelToAlola_Movement_2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route13_Movement_BoatArrive:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route13_GetOffBoat_Text_0:
	.string "ברוכים השבים ליבשת קאנטו!\p"
	.string "אפשר לחזור בכל פעם שבא לך\n"
	.string "לטייל לאיי אלולה!$"

Route13_TravelToAlola_Text_0:
	.string "אהוי!\p"
	.string "איזו מזכרת מוזרה!\n"
	.string "אתה בטח מהאיים!$"
Route13_TravelToAlola_Text_0_5:
	.string "רוצה לעלות על הספינה הבאה?\n"
	.string "היא יוצאת בקרוב!$"

Route13_TravelToAlola_Text_1:
	.string "אהוי! קדימה, עולים לסיפון!$"

Route13_TravelToAlola_Text_2:
	.string "אהוי!\n"
	.string "תחזור כשתרצה להפליג.$"

Route13_TravelToAlola_Text_3:
	.string "אה, זה שוב אתה!\n"
	.string "רוצה לנסוע לאיי אלולה?$"

Route13_TravelToAlola_Text_4:
	.string "אהוי!\n"
	.string "הנמל הזה לתושבים בלבד.\p"
	.string "כל תושבי האיים האלה נושאים\n"
	.string "איתם כמה… {PAUSE 30}מזכרות מוזרות.\p"
	.string "ככה קל מאוד לזהות אותם,\n"
	.string "אני אפילו לא צריך לבדוק כרטיסים!$"
