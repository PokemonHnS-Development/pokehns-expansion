Route27_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route27_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route27_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route27_EventScript_BaobaCall::
	setspeaker Route27_Text_BaobaName
	pokenavcall BlackthornCity_Text_BaobaCall
	waitmessage
	delay 30
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
    setvar VAR_ROUTE27_BAOBA_CALL, 1
	end

Route27_Text_BaobaName:
	.string "באובה$"

Route27_EventScript_FirstSteps::
    lock
    playse SE_PIN
    setflag FLAG_VISITED_KANTO
    applymovement2 LOCALID_ROUTE27_FATMAN, Common_Movement_ExclamationMark
    turnobject LOCALID_ROUTE27_FATMAN, DIR_WEST
    delay 30
    getplayerxy VAR_TEMP_0, VAR_TEMP_1
    call_if_eq VAR_TEMP_1, 24, Route27_EventScript_FirstStepsWalkTop
    call_if_eq VAR_TEMP_1, 25, Route27_EventScript_FirstStepsWalkBot

    msgbox Route27_Text_FisherHey, MSGBOX_DEFAULT
    msgbox Route27_Text_FisherMessage, MSGBOX_DEFAULT
    closemessage
    turnobject LOCALID_ROUTE27_FATMAN, DIR_SOUTH

    @integrated flagheap
    setflag FLAG_HIDE_VICTORY_ROAD_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK
    
    clearflag FLAG_GOT_TM_SANDSTORM
    clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
    clearflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD

    setvar VAR_ROUTE27_STATE, 1
    release
    end

Route27_EventScript_FirstStepsWalkTop::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkTop
    waitmovement 0
    return
Route27_EventScript_FirstStepsWalkBot::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkBot
    waitmovement 0
    return

Route27_Movement_WalkTop:
    face_left
    walk_left
    step_end

Route27_Movement_WalkBot:
    walk_down
    walk_left
    step_end

Route27_EventScript_Item_Moonstone::
    finditem ITEM_MOON_STONE
    end

Route27_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

Route27_EventScript_Item_DragonClaw::
    finditem ITEM_TM_DRAGON_CLAW
    end

Route27_EventScript_Item_Destiny_Knot::
    finditem ITEM_DESTINY_KNOT
    end

Route27_EventScript_Fatman::
    msgbox Route27_Text_FisherMessage, MSGBOX_NPC
    end

Route27_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE_HNS, Route27_Text_CooltrainermBlakeSeen, Route27_Text_CooltrainermBlakeBeaten
	msgbox Route27_Text_CooltrainermBlakeAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Brian::
	trainerbattle_single TRAINER_BRIAN_HNS, Route27_Text_CooltrainermBrianSeen, Route27_Text_CooltrainermBrianBeaten
	msgbox Route27_Text_CooltrainermBrianAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Reena::
	trainerbattle_single TRAINER_REENA_HNS, Route27_Text_CooltrainerfReenaSeen, Route27_Text_CooltrainerfReenaBeaten, Route27_EventScript_RegisterReena
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchReena
	msgbox Route27_Text_CooltrainerfReenaAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterReena::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_ReenaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_REENA_HNS
	release
	end

Route27_EventScript_RematchReena::
	trainerbattle_rematch TRAINER_REENA_HNS, Route27_Text_ReenaRematchIntro, Route27_Text_ReenaRematchDefeat
	msgbox Route27_Text_ReenaPostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Megan::
	trainerbattle_single TRAINER_MEGAN_HNS, Route27_Text_CooltrainerfMeganSeen, Route27_Text_CooltrainerfMeganBeaten
	msgbox Route27_Text_CooltrainerfMeganAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Gilbert::
	trainerbattle_single TRAINER_GILBERT_HNS, Route27_Text_PsychicGilbertSeen, Route27_Text_PsychicGilbertBeaten
	msgbox Route27_Text_PsychicGilbertAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Jose::
	trainerbattle_single TRAINER_JOSE_HNS, Route27_Text_BirdKeeperJoseSeen, Route27_Text_BirdKeeperJoseBeaten, Route27_EventScript_RegisterJose
	goto_if_set FLAG_JOSE_HAS_ITEM_HNS, Route27_EventScript_JoseGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchJose
	msgbox Route27_Text_BirdKeeperJoseAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterJose::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_JoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOSE_HNS
	release
	end

Route27_EventScript_RematchJose::
	trainerbattle_rematch TRAINER_JOSE_HNS, Route27_Text_JoseRematchIntro, Route27_Text_JoseRematchDefeat
	msgbox Route27_Text_JosePostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseGiveItem::
	msgbox Route27_Text_JoseHasItem, MSGBOX_DEFAULT
	giveitem VAR_JOSE_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route27_EventScript_JoseNoRoom
	clearflag FLAG_JOSE_HAS_ITEM_HNS
	msgbox Route27_Text_JoseGaveItem, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseNoRoom::
	msgbox Route27_Text_JoseNoRoom, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Scott::
	trainerbattle_single TRAINER_SCOTT_HNS, Route27_Text_FisherScottSeen, Route27_Text_FisherScottBeaten
	msgbox Route27_Text_FisherScottAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_TohjoFallsSign::
    msgbox TohjoFalls_Text_Sign, MSGBOX_SIGN
    end

Route27_Text_FisherHey:
    .string "היי!$"

Route27_Text_FisherMessage:
    .string "אתה יודע מה עשית עכשיו?\p"
    .string "עשית את הצעד הראשון שלך בקאנטו.\p"
    .string "תבדוק במפה של הפוקיגיר ותראה.$"

Route27_Text_CooltrainermBlakeSeen:
    .string "אתה נראה די חזק.\n"
    .string "בוא נילחם!$"

Route27_Text_CooltrainermBlakeBeaten:
    .string "אאוץ'!$"

Route27_Text_CooltrainermBlakeAfter:
    .string "אם תגבר על המסע הקשה הזה,\n"
    .string "האמת תתגלה!\p"
    .string "הה, סליחה, רק רציתי להגיד משהו מגניב.$"

Route27_Text_CooltrainermBrianSeen:
    .string "הממ? אתה טוב, נכון?$"

Route27_Text_CooltrainermBrianBeaten:
    .string "בדיוק כמו שחשבתי!$"

Route27_Text_CooltrainermBrianAfter:
    .string "מאמן טוב יודע לזהות\n"
    .string "מאמנים טובים אחרים.$"

Route27_Text_CooltrainerfReenaSeen:
    .string "לא כדאי לזלזל בפוקימונים\n"
    .string "הפראיים באזור הזה.$"

Route27_Text_CooltrainerfReenaBeaten:
    .string "אוי! אתה חזק מדי!$"

Route27_Text_CooltrainerfReenaAfter:
    .string "אתה רק ילד, אבל גם בך אסור לזלזל.$"

Route27_Text_ReenaRegister:
    .string "אתה רק ילד, אבל גם בך אסור לזלזל.$"

Route27_Text_ReenaRematchIntro:
    .string "לא כדאי לזלזל בפוקימונים\n"
    .string "הפראיים באזור הזה.$"

Route27_Text_ReenaRematchDefeat:
    .string "אוי! אתה חזק מדי!$"

Route27_Text_ReenaPostRematch:
    .string "אתה רק ילד, אבל גם בך אסור לזלזל.$"

Route27_Text_CooltrainerfMeganSeen:
    .string "נדיר שמישהו מגיע לכאן.\p"
    .string "אתה מתאמן לבד?$"

Route27_Text_CooltrainerfMeganBeaten:
    .string "אוי! אתה ממש חזק!$"

Route27_Text_CooltrainerfMeganAfter:
    .string "אני בודקת פוקימונים\n"
    .string "לפני ואחרי התפתחות.\p"
    .string "התפתחות באמת הופכת\n"
    .string "פוקימונים לחזקים יותר.\p"
    .string "אבל מצד שני, צורות מפותחות\n"
    .string "לומדות מהלכים מאוחר יותר.$"

Route27_Text_PsychicGilbertSeen:
    .string "אל תגיד מילה!\p"
    .string "תן לי לנחש מה אתה חושב.\p"
    .string "ממממממ…\p"
    .string "הבנתי! יצאת לאתגר של ליגת הפוקימון!$"

Route27_Text_PsychicGilbertBeaten:
    .string "אתה פשוט משהו!$"

Route27_Text_PsychicGilbertAfter:
    .string "עם הכישורים שלך, תצליח בליגה.\p"
    .string "כך אומר לי החזון שלי.$"

Route27_Text_BirdKeeperJoseSeen:
    .string "ציוץ! ציוץ! ציציוץ!$"

Route27_Text_BirdKeeperJoseBeaten:
    .string "ציוץ!$"

Route27_Text_BirdKeeperJoseAfter:
    .string "מגדלי ציפורים כמוני מחקים שריקות\n"
    .string "של ציפורים כדי לפקד על פוקימונים.$"

Route27_Text_JoseRegister:
    .string "מגדלי ציפורים כמוני מחקים שריקות\n"
    .string "של ציפורים כדי לפקד על פוקימונים.$"

Route27_Text_JoseRematchIntro:
    .string "ציוץ! ציוץ! ציציוץ!$"

Route27_Text_JoseRematchDefeat:
    .string "ציוץ!$"

Route27_Text_JosePostRematch:
    .string "מגדלי ציפורים כמוני מחקים שריקות\n"
    .string "של ציפורים כדי לפקד על פוקימונים.$"

Route27_Text_JoseHasItem:
    .string "היי! מצאתי משהו נוצץ\n"
    .string "בזמן שצפיתי בציפורים!\p"
    .string "הנה, זה בשבילך!$"

Route27_Text_JoseGaveItem:
    .string "אני מוצא כל מיני דברים כאן בדרך 27.\p"
    .string "אודיע לך אם אמצא עוד משהו!$"

Route27_Text_JoseNoRoom:
    .string "הממ, התיק שלך מלא.\p"
    .string "תחזור כשיהיה לך מקום.$"

TohjoFalls_Text_Sign:
    .string "מפלי טוג'ו\p"
    .string "החוליה המקשרת בין קאנטו לג'וטו$"

Route27_Text_FisherScottSeen:
    .string "אני מרגיש מעולה היום!\p"
    .string "נראה לי שאני יכול להעיף\n"
    .string "אפילו את אלוף הליגה!$"

Route27_Text_FisherScottBeaten:
    .string "לא! לא בקרב הזה!$"

Route27_Text_FisherScottAfter:
    .string "בדיוק כמו בדיג,\n"
    .string "גם בפוקימונים הכול נגמר אם מוותרים.$"
