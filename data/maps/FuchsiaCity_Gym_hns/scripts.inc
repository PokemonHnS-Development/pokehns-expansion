FuchsiaCity_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_Gym_OnTransition
	.byte 0

FuchsiaCity_Gym_OnTransition::
	goto_if_set FLAG_DEFEATED_FUCHSIA_GYM, FuchsiaCity_Gym_OnTransitionAfter
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	setflag FLAG_TEMP_7
	call_if_defeated TRAINER_ALICE_HNS, FuchsiaCity_Gym_DefeatedAlice
	call_if_defeated TRAINER_LINDA_HNS, FuchsiaCity_Gym_DefeatedLinda
	call_if_defeated TRAINER_CINDY_HNS, FuchsiaCity_Gym_DefeatedCindy
	call_if_defeated TRAINER_BARRY_HNS, FuchsiaCity_Gym_DefeatedBarry
	end

FuchsiaCity_Gym_OnTransitionAfter::
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_8
	end

FuchsiaCity_Gym_DefeatedAlice::
	setflag FLAG_TEMP_2
	clearflag FLAG_TEMP_1
	return

FuchsiaCity_Gym_DefeatedLinda::
	setflag FLAG_TEMP_4
	clearflag FLAG_TEMP_3
	return

FuchsiaCity_Gym_DefeatedCindy::
	setflag FLAG_TEMP_6
	clearflag FLAG_TEMP_5
	return

FuchsiaCity_Gym_DefeatedBarry::
	setflag FLAG_TEMP_8
	clearflag FLAG_TEMP_7
	return

FuchsiaCity_Gym_EventScript_Janine::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FUCHSIA_GYM, FuchsiaCity_Gym_EventScript_Janine_Defeated
	msgbox FuchsiaCity_Gym_Text_Janine_DisappointYou, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_JANINE_HNS, FuchsiaCity_Gym_Text_Janine_ToughOne
	message FuchsiaCity_Gym_Text_ReceivedSoulBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FuchsiaCity_Gym_Text_Janine_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_POISON_JAB
	msgbox FuchsiaCity_Gym_Text_Janine_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE14_GET
	setflag FLAG_DEFEATED_FUCHSIA_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 14
	call Common_EventScript_SetGymTrainers_hns
	removeobject LOCALID_FUCHSIAGYM_ALICE_J
	removeobject LOCALID_FUCHSIAGYM_CINDY_J
	removeobject LOCALID_FUCHSIAGYM_LINDA_J
	removeobject LOCALID_FUCHSIAGYM_BARRY_J
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_6
	setflag FLAG_TEMP_8
	addobject LOCALID_FUCHSIAGYM_ALICE
	addobject LOCALID_FUCHSIAGYM_CINDY
	addobject LOCALID_FUCHSIAGYM_LINDA
	addobject LOCALID_FUCHSIAGYM_BARRY
	clearflag FLAG_TEMP_1
	clearflag FLAG_TEMP_3
	clearflag FLAG_TEMP_5
	clearflag FLAG_TEMP_7
	clearflag FLAG_HIDE_ROUTE22_JANINE
	closemessage
	release
	end

FuchsiaCity_Gym_EventScript_Janine_Defeated::
	msgbox FuchsiaCity_Gym_Text_Janine_ApplyMyself, MSGBOX_DEFAULT
	closemessage
	release
	end

FuchsiaCity_Gym_Text_Janine_DisappointYou:
	.string "פופופופו…\p"
	.string "מצטערת לאכזב אותך…\p"
	.string "סתם צוחקת!\p"
	.string "אני האמיתית!\p"
	.string "ג'אנין ממכון פושיה, זאת אני!$"

FuchsiaCity_Gym_Text_Janine_ToughOne:
	.string "ג'אנין: אתה קשוח. ניצחת\n"
	.string "בלי שום ספק…\p"
	.string "הנה תג נשמה. הוא שלך.$"

FuchsiaCity_Gym_Text_ReceivedSoulBadge:
	.string "{PLAYER} קיבל את תג נשמה.$"

FuchsiaCity_Gym_Text_Janine_GiveTM:
	.string "ג'אנין: אתה כל כך קשוח! יש לי\n"
	.string "מתנה מיוחדת!$"

FuchsiaCity_Gym_Text_Janine_ExplainTM:
	.string "זו דקירת רעל, מהלך עוצמתי מסוג\n"
	.string "רעל שעלול להרעיל את הקורבן.$"

FuchsiaCity_Gym_Text_Janine_ApplyMyself:
	.string "ג'אנין: אני הולכת להתאמץ באמת\n"
	.string "ולשפר את הכישורים שלי.\p"
	.string "אני רוצה להיות טובה יותר\n"
	.string "גם מאבא וגם ממך!$"

FuchsiaCity_Gym_EventScript_Alice_J::
	lock
	faceplayer
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAGYM_ALICE_J, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAGYM_ALICE_J
	clearflag FLAG_TEMP_1
	addobject LOCALID_FUCHSIAGYM_ALICE
	applymovement LOCALID_FUCHSIAGYM_ALICE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	applymovement LOCALID_FUCHSIAGYM_ALICE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FuchsiaCity_Gym_Text_LassAlice_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ALICE_HNS, FuchsiaCity_Gym_Text_LassAlice_Beaten
	msgbox FuchsiaCity_Gym_Text_LassAlice_After, MSGBOX_DEFAULT
	closemessage
	release
	end

FuchsiaCity_Gym_EventScript_Alice::
	msgbox FuchsiaCity_Gym_Text_LassAlice_After, MSGBOX_NPC
	end


FuchsiaCity_Gym_EventScript_Linda_J::
	lock
	faceplayer
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAGYM_LINDA_J, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAGYM_LINDA_J
	clearflag FLAG_TEMP_3
	addobject LOCALID_FUCHSIAGYM_LINDA
	applymovement LOCALID_FUCHSIAGYM_LINDA, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	applymovement LOCALID_FUCHSIAGYM_LINDA, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FuchsiaCity_Gym_Text_LassLinda_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_LINDA_HNS, FuchsiaCity_Gym_Text_LassLinda_Beaten
	msgbox FuchsiaCity_Gym_Text_LassLinda_After, MSGBOX_DEFAULT
	closemessage
	release
	end

FuchsiaCity_Gym_EventScript_Linda::
	msgbox FuchsiaCity_Gym_Text_LassLinda_After, MSGBOX_NPC
	end

FuchsiaCity_Gym_EventScript_Cindy_J::
	lock
	faceplayer
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAGYM_CINDY_J, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAGYM_CINDY_J
	clearflag FLAG_TEMP_5
	addobject LOCALID_FUCHSIAGYM_CINDY
	applymovement LOCALID_FUCHSIAGYM_CINDY, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	applymovement LOCALID_FUCHSIAGYM_CINDY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FuchsiaCity_Gym_Text_PicnickerCindy_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_CINDY_HNS, FuchsiaCity_Gym_Text_PicnickerCindy_Beaten
	msgbox FuchsiaCity_Gym_Text_PicnickerCindy_After, MSGBOX_DEFAULT
	closemessage
	release
	end

FuchsiaCity_Gym_EventScript_Cindy::
	msgbox FuchsiaCity_Gym_Text_PicnickerCindy_After, MSGBOX_NPC
	end

FuchsiaCity_Gym_EventScript_Barry_J::
	lock
	faceplayer
	msgbox FuchsiaCity_PokemonCenter1F_Text_JanineImpersonator1, MSGBOX_DEFAULT
	applymovement LOCALID_FUCHSIAGYM_BARRY_J, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	removeobject LOCALID_FUCHSIAGYM_BARRY_J
	clearflag FLAG_TEMP_7
	addobject LOCALID_FUCHSIAGYM_BARRY
	applymovement LOCALID_FUCHSIAGYM_BARRY, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	applymovement LOCALID_FUCHSIAGYM_BARRY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FuchsiaCity_Gym_Text_CamperBarry_Before, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BARRY_HNS, FuchsiaCity_Gym_Text_CamperBarry_Beaten
	msgbox FuchsiaCity_Gym_Text_CamperBarry_After, MSGBOX_DEFAULT
	closemessage
	release
	end

FuchsiaCity_Gym_EventScript_Barry::
	msgbox FuchsiaCity_Gym_Text_CamperBarry_After, MSGBOX_NPC
	end

FuchsiaCity_Gym_Text_LassAlice_Before:
	.string "פופופו!\p"
	.string "אני ג'אנין, מנהיגת המכון!\p"
	.string "לא, אני לא! עבדתי עליך, פראייר!$"

FuchsiaCity_Gym_Text_LassAlice_Beaten:
	.string "הצלחתי לעבוד עליך…$"

FuchsiaCity_Gym_Text_LassAlice_After:
	.string "איך תזהה את המנהיגה\n"
	.string "האמיתית שלנו?$"

FuchsiaCity_Gym_Text_LassLinda_Before:
	.string "עבדתי עליך! האהאהא!$"

FuchsiaCity_Gym_Text_LassLinda_Beaten:
	.string "אוי… הפסדתי… אתה לא חלש…$"

FuchsiaCity_Gym_Text_LassLinda_After:
	.string "נו? התחפושת שלי לא הייתה מושלמת?$"

FuchsiaCity_Gym_Text_PicnickerCindy_Before:
	.string "אני ג'אנין!\p"
	.string "איך ידעת שאני האמיתית?\p"
	.string "קדימה, לקרב!$"

FuchsiaCity_Gym_Text_PicnickerCindy_Beaten:
	.string "אוף! רציתי לנצח!$"

FuchsiaCity_Gym_Text_PicnickerCindy_After:
	.string "בטח כבר התחלת להתעייף.$"

FuchsiaCity_Gym_Text_CamperBarry_Before:
	.string "וואהאהאהא!\p"
	.string "ברור! אני ג'אנין!$"

FuchsiaCity_Gym_Text_CamperBarry_Beaten:
	.string "התחפושת שלי הייתה מושלמת! אוף!$"

FuchsiaCity_Gym_Text_CamperBarry_After:
	.string "היי, אתה. התחפושת שלי הייתה\n"
	.string "חמודה או מה, הא?$"

FuchsiaCity_Gym_EventScript_GymGuy::
	goto_if_set FLAG_DEFEATED_FUCHSIA_GYM, FuchsiaCity_Gym_EventScript_GymGuyAfter
	msgbox FuchsiaCity_Gym_Text_Guide, MSGBOX_NPC
	end

FuchsiaCity_Gym_EventScript_GymGuyAfter::
	msgbox FuchsiaCity_Gym_Text_GuideWin, MSGBOX_NPC
	end

FuchsiaCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_DEFEATED_FUCHSIA_GYM, FuchsiaCity_Gym_EventScript_GymStatuePostVictory
	msgbox FuchsiaCity_Gym_Text_GymStatue
	releaseall
	end

FuchsiaCity_Gym_EventScript_GymStatuePostVictory::
	msgbox FuchsiaCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

FuchsiaCity_Gym_Text_GymStatue::
    .string "מכון הפוקימון של פושיה\n"
    .string "מנהיגה: ג'אנין\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד$"

FuchsiaCity_Gym_Text_GymStatuePlayerWon::
    .string "מכון הפוקימון של פושיה\n"
    .string "מנהיגה: ג'אנין\p"
    .string "מאמנים מנצחים:\n"
    .string "בלו, רד, {PLAYER}$"

FuchsiaCity_Gym_Text_Guide:
	.string "יו, אלוף לעתיד!\p"
	.string "אופס! כדאי להסתכל היטב מסביב.\p"
	.string "כל המאמנים נראים כמו\n"
	.string "המנהיגה, ג'אנין.\p"
	.string "מי מהם היא ג'אנין האמיתית?$"

FuchsiaCity_Gym_Text_GuideWin:
	.string "זה היה קרב נהדר,\n"
	.string "מאמן מג'וטו!$"

