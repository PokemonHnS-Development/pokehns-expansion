NewSinjoh_KimonoHideout_hns_MapScripts::
   map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_KimonoHideout_OnFrame
    .byte 0


NewSinjoh_KimonoHideout_OnFrame:
	map_script_2 VAR_SINJOH_STORYLINE, 4, NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos
	.2byte 0

@ ============INTRO CUTSCENE=====================================================================================

NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos, MSGBOX_AUTOCLOSE
	applymovement LOCALID_PLAYER, NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_MIHARU, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_MIHARU, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_SHIZUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_SHIZUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_YOUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_YOUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	setvar VAR_SINJOH_STORYLINE, 5
	release
	end

NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksDown:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_down
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksUp:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_up
	face_down
	step_end

NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos:
	.string "{PLAYER}.\p"
	.string "בבקשה, התקרב.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu:
    .string "מיהארו: ברוך הבא לסינג'ו החדשה,\n"
    .string "{PLAYER}.\p"
    .string "במשך דורות, הכפר הזה חי בשלום\n"
    .string "לצד פוקימונים בעלי עוצמה אדירה,\p"
    .string "מבודד מעיניהם החטטניות של זרים.\p"
    .string "האירועים האחרונים במקדש הקדוש שלנו,\n"
    .string "והאורחים הלא קרואים שנהרו בעקבותיהם,\p"
    .string "מאיימים כעת להפר את האיזון העדין\n"
    .string "ששמרנו עליו זמן רב.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko:
	.string "שיזוקו: בנות הדודות שלנו\n"
	.string "בעיר אקרוטיק סיפרו לנו\p"
	.string "על הקשר שלך לפוקימון האגדי\n"
	.string "של אזור ג'וטו, ועל כישוריך כמאמן.\p"
	.string "אנחנו מאמינות שתוכל לעזור לנו\n"
	.string "בזמנים הקשים האלה.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko:
	.string "יוקו: לך לחורבות סינג'ו,\n"
	.string "מצפון לדרך 50.\p"
	.string "פגוש שם את המדענים, וחקור\n"
	.string "את האירועים שגרמו לבואם.\p"
	.string "חיוני שהפוקימונים האגדיים שם\n"
	.string "לא יופרעו בידי מי שאינם ראויים.$"


@ ============KIMONO GIRL NPCs=====================================================================================

NewSinjoh_KimonoHideout_EventScript_Miharu::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_MiharuFinal
	goto_if_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_MiharuAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_MiharuBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuBattle::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 0, 2, 0
	trainerbattle_no_intro TRAINER_MIHARU_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_MEADOW_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuAfter::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle:
	.string "מיהארו: בדיוק כפי שחזינו.\p"
	.string "אלוף האבנים שלח אותך\n"
	.string "לאסוף את הלוחות.\p"
	.string "המסדר שלנו שומר על הלוחות\n"
	.string "האלה כבר מאות שנים.\p"
	.string "לא ניפרד מהם\n"
	.string "בקלות.$"

NewSinjoh_KimonoHideout_Text_MiharuAfter:
	.string "מיהארו: אתה ראוי.$"

NewSinjoh_KimonoHideout_EventScript_MiharuFinal::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_MiharuFinal:
	.string "מיהארו: עשית שירות גדול\n"
	.string "לכפר שלנו, {PLAYER}.\p"
	.string "לא נשכח זאת.$"

NewSinjoh_KimonoHideout_EventScript_Youko::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_YoukoFinal
	goto_if_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_YoukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_YoukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 1, 2, 2, 2
	trainerbattle_no_intro TRAINER_YOUKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_ICICLE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle:
	.string "יוקו: בנות הדודות שלנו מדברות\n"
	.string "עליך בשבחים רבים.\p"
	.string "האם זה נכון?\p"
	.string "אני אגלה בעצמי.$"

NewSinjoh_KimonoHideout_Text_YoukoAfter:
	.string "יוקו: בנות הדודות שלנו צדקו\n"
	.string "לגביך.$"

NewSinjoh_KimonoHideout_EventScript_YoukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_YoukoFinal:
	.string "יוקו: בהתחלה היו לי ספקות.\p"
	.string "אבל אחרי מה שעשית,\n"
	.string "אי אפשר להכחיש זאת.$"

NewSinjoh_KimonoHideout_EventScript_Shizuko::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_ShizukoFinal
	goto_if_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_ShizukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_ShizukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 1, 0, 0, 1, 0
	trainerbattle_no_intro TRAINER_SHIZUKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_PIXIE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle:
	.string "שיזוקו: אנחנו מאומנות בקרב\n"
	.string "לא פחות מאשר בריקוד.\p"
	.string "כדי להשיג את הלוחות\n"
	.string "תצטרך כוח ונחישות.$"

NewSinjoh_KimonoHideout_Text_ShizukoAfter:
	.string "שיזוקו: הקשר שלך עם\n"
	.string "הפוקימונים שלך חזק מאוד.\p"
	.string "הרווחת את הלוח הזה.$"

NewSinjoh_KimonoHideout_EventScript_ShizukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_ShizukoFinal:
	.string "שיזוקו: מעט מאמנים בכל ההיסטוריה\n"
	.string "העשירה של סינג'ו הצליחו במה שעשית.\p"
	.string "מרשים מאוד, {PLAYER}.$"

@ =================================================================================================

NewSinjoh_KimonoHideout_EventScript_OldMan::
	msgbox NewSinjoh_KimonoHideout_Text_OldMan, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_OldMan:
    .string "נערות הקימונו שומרות על\n"
    .string "הכפר שלנו מאז היווסדו.\p"
    .string "הן הקריבו הרבה.\p"
    .string "הן מבורכות בידי האלים עצמם,\n"
    .string "וכוחן עולה על זה של כל מאמן רגיל!\p"
    .string "כלומר, כדאי שתהיה מוכן אם\n"
    .string "תילחם בהן אי פעם, בחור צעיר.$"

NewSinjoh_KimonoHideout_Text_OldManAfter:
    .string "You have bested the champions of\n"
	.string "our village.\p"
	.string "What does that make you, young one?$"
