SproutTower_3F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SproutTower_3F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SproutTower_3F_OnTransition: 
	callnative SetTimeBasedEncounters
	end


SproutTower_3F_EventScript_SageJin::
	trainerbattle_single TRAINER_JIN_HNS, SproutTower_Text_SageJin_Seen, SproutTower_Text_SageJin_Beaten
	msgbox SproutTower_Text_SageJin_AfterBattle, MSGBOX_AUTOCLOSE
	end


SproutTower_3F_EventScript_SageNeal::
	trainerbattle_single TRAINER_NEAL_HNS, SproutTower_Text_SageNeal_Seen, SproutTower_Text_SageNeal_Beaten
	msgbox SproutTower_Text_SageNeal_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_SageTroy::
	trainerbattle_single TRAINER_TROY_HNS, SproutTower_Text_SageTroy_Seen, SproutTower_Text_SageTroy_Beaten
	msgbox SproutTower_Text_SageTroy_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_3F_EventScript_Painting::
	lock
	msgbox SproutTower_Text_3F_Painting, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_3F_EventScript_Potion::
	finditem ITEM_POTION
	end

SproutTower_3F_EventScript_EscapeRope::
	finditem ITEM_ESCAPE_ROPE
	end

SproutTower_3F_EventScript_TriggerSceneLeft::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_Silver1
	waitmovement 0
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SPROUT_TOWER_SILVER, Common_Movement_ExclamationMark	
	delay 55
	waitmovement LOCALID_SPROUT_TOWER_SILVER
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_SilverLeft
	waitmovement 0
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	delay 30
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement LOCALID_SPROUT_TOWER_SILVER SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	removeobject LOCALID_SPROUT_TOWER_SILVER
	delay 55
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	fadedefaultbgm
	setvar VAR_SPROUT_TOWER, 1
	release
	end

SproutTower_3F_EventScript_TriggerSceneRight::
	lock
	playbgm MUS_HG_ENCOUNTER_RIVAL, FALSE
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_Silver1
	waitmovement 0
	msgbox SproutTower_Text_ElderLecturesRival, MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_SPROUT_TOWER_SILVER, Common_Movement_ExclamationMark	
	delay 55
	waitmovement LOCALID_SPROUT_TOWER_SILVER
	applymovement LOCALID_SPROUT_TOWER_SILVER, SproutTower_3F_Movement_SilverRight
	waitmovement 0
	waitmovement 0
	msgbox SproutTower_Text_RivalOnlyCaresStrong, MSGBOX_DEFAULT
	msgbox SproutTower_Text_RivalUsedEscapeRope, MSGBOX_DEFAULT
	applymovement LOCALID_SPROUT_TOWER_SILVER SproutTower_3F_Movement_EscapeRope
	waitmovement 0
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	removeobject LOCALID_SPROUT_TOWER_SILVER
	delay 55
	fadescreen FADE_FROM_BLACK
	special DrawWholeMapView
	fadedefaultbgm
	setvar VAR_SPROUT_TOWER, 1
	release
	end

SproutTower_3F_EventScript_SageLi::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, SproutTower_3F_EventScript_SageLi_Beaten
	msgbox SproutTower_Text_SageLi_Seen, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_LI_HNS, SproutTower_Text_SageLi_Beaten
	msgbox SproutTower_Text_SageLi_TakeFlash, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox SproutTower_Text_SageLi_FlashExplain, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_EventScript_SageLi_Beaten::
	msgbox SproutTower_Text_SageLi_AfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SproutTower_3F_Movement_Silver1:
	walk_fast_up
	walk_fast_up
	step_end

SproutTower_3F_Movement_SilverLeft:
	face_down
	delay_16
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_SilverRight:
	face_down
	delay_16
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	step_end

SproutTower_3F_Movement_EscapeRope:
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	face_right
	face_up
	face_left
	face_down
	step_end

SproutTower_Text_ElderLecturesRival:
	.string "זקן המגדל: אתה אכן מאמן מיומן.\p"
	.string "כפי שהבטחתי, הנה המ”נ שלך.\p"
	.string "אבל הרשה לי לומר לך דבר אחד:\n"
	.string "כדאי שתתייחס טוב יותר לפוקימונים שלך.\p"
	.string "הדרך שבה אתה נלחם קשוחה מדי.\p"
	.string "פוקימונים אינם כלי מלחמה…$"

SproutTower_Text_RivalOnlyCaresStrong:
	.string "…\n"
	.string "…המף!\p"
	.string "הוא טוען שהוא זקן המגדל,\n"
	.string "אבל הוא חלש.\p"
	.string "זה ברור מאליו.\p"
	.string "לעולם לא אפסיד לטיפשים שמקשקשים\n"
	.string "על יחס יפה לפוקימונים.\p"
	.string "אכפת לי רק מפוקימונים חזקים\n"
	.string "שיכולים לנצח.\p"
	.string "ממש לא אכפת לי\n"
	.string "מפוקימונים חלשים.$"

SproutTower_Text_RivalUsedEscapeRope:
	.string "{RIVAL} השתמש בחבל מילוט!$"

SproutTower_Text_SageLi_Seen:
	.string "כמה יפה מצידך שבאת לכאן!\p"
	.string "מגדל הנבט הוא מקום אימונים.\p"
	.string "בני אדם ופוקימונים בוחנים כאן את\n"
	.string "הקשר ביניהם כדי לבנות יחד עתיד מזהיר.\p"
	.string "אני המבחן האחרון.\p"
	.string "הרשה לי לבחון את הקשר\n"
	.string "בינך לבין הפוקימונים שלך!$"

SproutTower_Text_SageLi_Beaten:
	.string "אה, מצוין!$"

SproutTower_Text_SageLi_TakeFlash:
	.string "לך ולפוקימונים שלך לא אמורה\n"
	.string "להיות בעיה להשתמש במהלך הזה.\p"
	.string "הנה, מ”נ הבזק בשבילך.$"

SproutTower_Text_SageLi_FlashExplain:
	.string "הבזק מאיר אפילו את\n"
	.string "המקומות החשוכים ביותר.\p"
	.string "אבל כדי להשתמש בו מחוץ לקרב,\n"
	.string "צריך את התג של מכון ויולט.$"

SproutTower_Text_SageLi_AfterBattle:
	.string "אני מקווה שהמסע שלך\n"
	.string "יעזור לך ללמוד ולצמוח.$"

SproutTower_Text_SageJin_Seen:
	.string "אני מתאמן כדי למצוא הארה\n"
	.string "דרך הפוקימונים!$"

SproutTower_Text_SageJin_Beaten:
	.string "האימון שלי עוד לא הושלם…$"

SproutTower_Text_SageJin_AfterBattle:
	.string "ככל שהפוקימונים מתחזקים,\n"
	.string "כך מתחזק גם המאמן.\p"
	.string "לא, רגע. ככל שהמאמן מתחזק,\n"
	.string "כך מתחזקים גם הפוקימונים.$"

SproutTower_Text_SageTroy_Seen:
	.string "הבה נראה עד כמה אתה סומך\n"
	.string "על הפוקימונים שלך.$"

SproutTower_Text_SageTroy_Beaten:
	.string "כן, האמון שלך אמיתי!$"

SproutTower_Text_SageTroy_AfterBattle:
	.string "זקן המגדל נמצא לא רחוק מכאן.$"

SproutTower_Text_SageNeal_Seen:
	.string "המ”נ של זקן המגדל מאיר אפילו\n"
	.string "חושך מוחלט.$"

SproutTower_Text_SageNeal_Beaten:
	.string "דווקא הראש שלי מבריק!$"

SproutTower_Text_SageNeal_AfterBattle:
	.string "יהי אור במסעך.$"

SproutTower_Text_3F_Painting:
	.string "זה ציור עוצמתי של בלספראוט.$"
