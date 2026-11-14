BurnedTower_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, BurnedTower_1F_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BurnedTower_1F_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BurnedTower_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

BurnedTower_1F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

BurnedTower_1F_OnLoad::
	goto_if_ge VAR_ECRUTEAK_CITY_STATE, 4, BurnedTower_1F_MapScript_CreateHole
	end

BurnedTower_1F_MapScript_CreateHole::
	setmetatile 16, 12, 0x37E, FALSE
	end

BurnedTower_1F_OnFrame::
	map_script_2 VAR_ECRUTEAK_CITY_STATE, 1, BurnedTower_1F_EventScript_MeetEusine
	.2byte 0

BurnedTower_1F_EventScript_MeetEusine::
	lock
	playse SE_PIN
	applymovement LOCALID_BURNED_TOWER_EUSINE, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_BURNED_TOWER_EUSINE
	applymovement LOCALID_BURNED_TOWER_EUSINE, BurnedTower_Movement_Eusine1
	waitmovement 0
	msgbox BurnedTower_1FEusineIntroText, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BURNED_TOWER_EUSINE, BurnedTower_Movement_Eusine2
	waitmovement 0
	setvar VAR_ECRUTEAK_CITY_STATE, 2
	release
	end

BurnedTower_Movement_Eusine1:
	walk_down
	walk_down
	step_end

BurnedTower_Movement_Eusine2:
	walk_up
	walk_up
	step_end


BurnedTower_1FEusineIntroText:
	.string "יוסין: שמי יוסין.\p"
	.string "אני בעקבותיו של פוקימון\n"
	.string "בשם סואיקון.\p"
	.string "ומה השם שלך…?\p"
	.string "{PLAYER}? נעים מאוד!\p"
	.string "שמעתי שסואיקון אולי נמצא\n"
	.string "במגדל השרוף, אז באתי לבדוק.\p"
	.string "אבל איפה בדיוק הוא יכול להיות?$"

BurnedTower_1F_EventScript_Item_HpUp::
	finditem ITEM_HP_UP
	end

BurnedTower_1F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

BurnedTower_1F_EventScript_Eusine::
	lock
	faceplayer
	msgbox BurnedTower_1FEusineText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1F_EventScript_Morty::
	lock
	faceplayer
	msgbox BurnedTower_1FMortyText, MSGBOX_DEFAULT
	closemessage
	release
	end

BurnedTower_1FEusineText:
	.string "יוסין: שמעתי שסואיקון אולי נמצא\n"
	.string "במגדל השרוף, אז באתי לבדוק.\p"
	.string "אבל איפה בדיוק הוא יכול להיות?$"

BurnedTower_1FMortyText:
	.string "מורטי: סואיקון, אנטיי ורייקו\n"
	.string "נחשבים לפוקימונים האגדיים.\p"
	.string "מנהיג המכון של אקרוטיק\n"
	.string "חייב לחקור אותם.\p"
	.string "יוסין כאן, אז החלטתי\n"
	.string "לחקור את המגדל יחד איתו.$"

BurnedTower_1F_EventScript_Silver::
	lock
	playse SE_PIN
	applymovement LOCALID_BURNED_TOWER_SILVER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_BURNED_TOWER_SILVER
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	applymovement LOCALID_BURNED_TOWER_SILVER, Common_Movement_WalkLeft1
	waitmovement 0
	waitmovement 0
	msgbox BurnedTowerSilver_BeforeText, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, BurnedTower_1F_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, BurnedTower_1F_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, BurnedTower_1F_Silver_Battle_Chikorita
	playbgm MUS_HG_RIVAL_EXIT, FALSE
	msgbox BurnedTowerSilver_AfterText1, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 20  @ num shakes
	setvar VAR_0x8007, 6  @ shake delay
	special ShakeCamera
	waitstate
	playse SE_CLICK
	setmetatile 16, 12, 0x37E, FALSE
	special DrawWholeMapView
	waitse
	delay 60
	special SpawnCameraObject
	removeobject OBJ_EVENT_ID_PLAYER
	playse SE_FALL
	delay 60
	msgbox BurnedTowerSilver_AfterText2, MSGBOX_AUTOCLOSE
	waitmessage
	warphole MAP_BURNED_TOWER_B1F_HNS
	setvar VAR_ECRUTEAK_CITY_STATE, 3
	waitstate
	release
	end

BurnedTower_1F_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_3_HNS, BurnedTowerSilver_WinText
	return

BurnedTower_1F_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_3_HNS, BurnedTowerSilver_WinText
	return

BurnedTower_1F_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_3_HNS, BurnedTowerSilver_WinText
	return

BurnedTowerSilver_BeforeText:
	.string "…………\p"
	.string "…אה, זה אתה.\p"
	.string "באתי לחפש פוקימונים אגדיים\n"
	.string "שאומרים שהם שוכנים כאן.\p"
	.string "אבל אין פה כלום!\p"
	.string "כלום, אחרי כל המאמץ\n"
	.string "להגיע לחור הזה? אין מצב!\p"
	.string "הכול באשמתך!$"

BurnedTowerSilver_WinText:
	.string "…המף!\p"
	.string "הפסדתי רק כי הפוקימונים\n"
	.string "שלי חלשים להחריד.\p"
	.string "כמה פתטי.$"

BurnedTowerSilver_AfterText1:
	.string "…אה, לא משנה.\p"
	.string "בכל מקרה, לעולם לא תצליח\n"
	.string "לתפוס פוקימון אגדי.$"

BurnedTowerSilver_LossText:
	.string "...Humph!\p"
	.string "This is why I hate battling\n"
	.string "wimps. It's a waste of time.$"

BurnedTowerSilver_AfterText2:
	.string "המף!\p"
	.string "מה אתה עושה, נופל\n"
	.string "לתוך בור? איזה גאון!\p"
	.string "מגיע לך!$"

BurnedTower_1F_EventScript_Nard::
	trainerbattle_single TRAINER_NARD_HNS, BurnedTower_Text_NardSeen, BurnedTower_Text_NardBeaten
	msgbox BurnedTower_Text_NardAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_1F_EventScript_Richardo::
	trainerbattle_single TRAINER_RICHARDO_HNS, BurnedTower_Text_RichardoSeen, BurnedTower_Text_RichardoBeaten
	msgbox BurnedTower_Text_RichardoAfter, MSGBOX_AUTOCLOSE
	end

BurnedTower_Text_NardSeen:
	.string "אל דאגה!\p"
	.string "אנחנו, יורקי האש, מכירים את הכוח\n"
	.string "האמיתי של האש יותר מכולם!$"
BurnedTower_Text_NardBeaten:
	.string "תודה על קרב כל כך לוהט!$"
BurnedTower_Text_NardAfter:
	.string "המגדל הזה נשרף כי\n"
	.string "פגע בו ברק.\p"
	.string "האש שאני יורק קטנטנה\n"
	.string "בהשוואה לזה…$"

BurnedTower_Text_RichardoSeen:
	.string "אני מתאמן בגניבה במגדל השרוף!\n"
	.string "אל תנסו את זה בבית!$"
BurnedTower_Text_RichardoBeaten:
	.string "פפפפפפפפפפפפפפף.$"
BurnedTower_Text_RichardoAfter:
	.string "אולי חיי פשע הם לא\n"
	.string "בשבילי…$"
