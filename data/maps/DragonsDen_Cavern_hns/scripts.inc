DragonsDen_Cavern_hns_MapScripts::
	@map_script MAP_SCRIPT_ON_FRAME_TABLE, DragonsDen_Cavern_OnFrame
	.byte 0

DragonsDen_Cavern_OnFrame::
	map_script_2 VAR_BLACKTHORN_CITY_STATE, 3, DragonsDen_Cavern_EventScript_Clair
	.2byte 0

DragonsDen_EventScript_ClairRematch::
    lock
    faceplayer
    msgbox DragonsDen_Text_Clair, MSGBOX_DEFAULT
    closemessage
    fadescreenswapbuffers FADE_TO_BLACK
    setflag FLAG_HIDE_DEN_CLAIR
    removeobject LOCALID_DEN_CLAIR
    fadescreenswapbuffers FADE_FROM_BLACK
    clearflag FLAG_HIDE_DOJO_CLAIR
    release
    end

DragonsDen_Text_Clair:
    .string "{PLAYER}… אז הגעת.\p"
    .string "אם אתה חושב שתעמוד בקצב שלי,\n"
    .string "בוא לדוג'ו הלחימה בסאפרון.$"

DragonsDen_Cavern_Trigger_ClairLeft::
	lock
	setflag FLAG_TEMP_HIDE_FOLLOWER 
	playse SE_PIN
	playbgm MUS_HG_CLAIR, FALSE
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_DRAGONSDEN2_CLAIR
	call DragonsDen_Cavern_EventScript_Clair
	applymovement OBJ_EVENT_ID_PLAYER, DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER
	waitmovement 0
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveLeft
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY_HNS
	releaseall
	end

DragonsDen_Cavern_Trigger_ClairMid::
	lock 
	playse SE_PIN
	playbgm MUS_HG_CLAIR, FALSE
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_DRAGONSDEN2_CLAIR
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveMid
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end

DragonsDen_Cavern_Trigger_ClairRight::
	lock 
	playse SE_PIN
	playbgm MUS_HG_CLAIR, FALSE
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_DRAGONSDEN2_CLAIR
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, Common_Movement_WalkRight1
	call DragonsDen_Cavern_EventScript_Clair
	applymovement2 LOCALID_DRAGONSDEN2_CLAIR, DragonsDen_Cavern_Movement_ClairLeaveRight
	waitmovement 0
	setflag FLAG_HIDE_DRAGONS_DEN_CAVERN_CLAIR
	removeobject LOCALID_DRAGONSDEN2_CLAIR
	playse SE_EXIT
	fadedefaultbgm
	setvar VAR_BLACKTHORN_CITY_STATE, 4
	release
	end

DragonsDen_Cavern_EventScript_Clair::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox DragonsDen_Cavern_Text_Clair_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_DRAGON_PULSE
	msgbox DragonsDen_Cavern_Text_Clair_ExplainTM, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox DragonsDen_Cavern_Text_ClairWhatsTheMatter, MSGBOX_DEFAULT
	closemessage
	delay 10
	clearflag FLAG_GOT_DRATINI
	return

DragonsDen_Cavern_Movement_ClairLeaveLeftPLAYER:
	walk_fast_down
	face_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveLeft:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveMid:
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Movement_ClairLeaveRight:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

DragonsDen_Cavern_Text_Clair_GiveTM:
    .string "קלייר: רגע!\p"
    .string "אני מצטערת על כל זה.\n"
    .string "הנה, קח את זה כהתנצלות.$"

DragonsDen_Cavern_Text_Clair_ExplainTM:
    .string "דופק דרקון הוא סוג של, אה…\n"
    .string "לא משנה!\p"
    .string "זו אנרגיה עצומה מסוג כלשהו.\p"
    .string "אם לא רוצים אותו, לא חייבים\n"
    .string "לקחת אותו.$"

DragonsDen_Cavern_Text_ClairWhatsTheMatter:
    .string "מה קרה? אתה לא ממשיך\n"
    .string "לליגת הפוקימון?\p"
    .string "אחרי שתהיה אלוף, תוכל להילחם\n"
    .string "שוב בכל מנהיג מכון שתרצה.\p"
    .string "לך לליגת הפוקימון.\p"
    .string "אתה יודע איך מגיעים לשם?\p"
    .string "מכאן, לך לעיירה ניו בארק.\p"
    .string "משם, השתמש בגלישה והמשך\n"
    .string "מזרחה לליגת הפוקימון.\p"
    .string "הדרך לשם קשה מאוד.\p"
    .string "שלא תעז להפסיד\n"
    .string "בליגת הפוקימון!\p"
    .string "אם תפסיד, ארגיש עוד יותר רע\n"
    .string "על זה שהפסדתי לך!\p"
    .string "תן את הכול.$"

DragonsDen_Cavern_EventScript_Darin::
	trainerbattle_single TRAINER_DARIN_HNS, DragonsDen_Cavern_Text_CooltrainermDarinSeen, DragonsDen_Cavern_Text_CooltrainermDarinBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainermDarinAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_Cara::
	trainerbattle_single TRAINER_CARA_HNS, DragonsDen_Cavern_Text_CooltrainerfCaraSeen, DragonsDen_Cavern_Text_CooltrainerfCaraBeaten
	msgbox DragonsDen_Cavern_Text_CooltrainerfCaraAfter, MSGBOX_AUTOCLOSE
	end

DragonsDen_Cavern_EventScript_TwinLea::
	trainerbattle_double TRAINER_LEA_AND_PIA_HNS, DragonsDen_Cavern_Text_TwinsLeaandPia1Seen, DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia1After, MSGBOX_DEFAULT
	release
	end
	
DragonsDen_Cavern_EventScript_TwinPia::
	trainerbattle_double TRAINER_LEA_AND_PIA_HNS, DragonsDen_Cavern_Text_TwinsLeaandPia2Seen, DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox DragonsDen_Cavern_Text_TwinsLeaandPia2After, MSGBOX_DEFAULT
	release
	end

DragonsDen_Cavern_EventScript_Item_Dragon_Fang::
	finditem ITEM_DRAGON_FANG
	end
DragonsDen_Cavern_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end
DragonsDen_Cavern_EventScript_Item_PP_Max::
	finditem ITEM_PP_MAX
	end



DragonsDen_Cavern_Text_DragonShrineSign:
    .string "DRAGON SHRINE\p"
    .string "A shrine honoring the dragon\n"
    .string "POKéMON\p"
    .string "said to have lived in DRAGON'S\n"
    .string "DEN.$"

DragonsDen_Cavern_Text_SilverTraining1:
    .string "…\n"
    .string "What? {PLAYER}?\p"
    .string "…No, I won't battle you now…\p"
    .string "My POKéMON aren't ready to beat\n"
    .string "you.\p"
    .string "I can't push them too hard now.\p"
    .string "I have to be disciplined to become\n"
    .string "the greatest POKéMON trainer…$"

DragonsDen_Cavern_Text_SilverTraining2:
    .string "…\p"
    .string "Whew…\p"
    .string "Learn to stay out of my way…$"

DragonsDen_Cavern_Text_CooltrainermDarinSeen:
    .string "אתה! איך אתה מעז להיכנס\n"
    .string "בלי הזמנה!$"

DragonsDen_Cavern_Text_CooltrainermDarinBeaten:
    .string "ח-חזק!$"

DragonsDen_Cavern_Text_CooltrainermDarinAfter:
    .string "המקדש שבהמשך הוא ביתו של המאסטר\n"
    .string "של שבט מאלפי הדרקונים שלנו.\p"
    .string "אסור סתם להיכנס לשם!$"

DragonsDen_Cavern_Text_CooltrainerfCaraSeen:
    .string "אסור לך להיות כאן!$"

DragonsDen_Cavern_Text_CooltrainerfCaraBeaten:
    .string "אוי, לא! הפסדתי!$"

DragonsDen_Cavern_Text_CooltrainerfCaraAfter:
    .string "בקרוב אקבל מהמאסטר שלנו\n"
    .string "רשות להשתמש בדרקונים.\p"
    .string "וכשזה יקרה, אהפוך למאלפת דרקונים\n"
    .string "מעוררת הערצה ואזכה בהכרת המאסטר.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Seen:
    .string "זה זר שאנחנו לא מכירות.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1Beaten:
    .string "אאוץ'.$"

DragonsDen_Cavern_Text_TwinsLeaandPia1After:
    .string "זה היה כמו להילחם\n"
    .string "בלאנס.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Seen:
    .string "מי אתה?$"

DragonsDen_Cavern_Text_TwinsLeaandPia2Beaten:
    .string "רשע.$"

DragonsDen_Cavern_Text_TwinsLeaandPia2After:
    .string "אנחנו נלשין עליך.\p"
    .string "המאסטר יכעס עליך.$"
