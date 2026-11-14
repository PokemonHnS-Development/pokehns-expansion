Route26_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route26_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route26_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route26_EventScript_Jake::
	trainerbattle_single TRAINER_JAKE_HNS, Route26_Text_CooltrainermJakeSeen, Route26_Text_CooltrainermJakeBeaten
	msgbox Route26_Text_CooltrainermJakeAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Gaven::
	trainerbattle_single TRAINER_GAVEN_HNS, Route26_Text_CooltrainermGavenSeen, Route26_Text_CooltrainermGavenBeaten, Route26_EventScript_RegisterGaven
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route26_EventScript_RematchGaven
	msgbox Route26_Text_CooltrainermGavenAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_RegisterGaven::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route26_Text_GavenRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GAVEN_HNS
	release
	end

Route26_EventScript_RematchGaven::
	trainerbattle_rematch TRAINER_GAVEN_HNS, Route26_Text_GavenRematchIntro, Route26_Text_GavenRematchDefeat
	msgbox Route26_Text_GavenPostRematch, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Joyce::
	trainerbattle_single TRAINER_JOYCE_HNS, Route26_Text_CooltrainerfJoyceSeen, Route26_Text_CooltrainerfJoyceBeaten
	msgbox Route26_Text_CooltrainerfJoyceAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Beth::
	trainerbattle_single TRAINER_BETH_HNS, Route26_Text_CooltrainerfBethSeen, Route26_Text_CooltrainerfBethBeaten, Route26_EventScript_RegisterBeth
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route26_EventScript_RematchBeth
	msgbox Route26_Text_CooltrainerfBethAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_RegisterBeth::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route26_Text_BethRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BETH_HNS
	release
	end

Route26_EventScript_RematchBeth::
	trainerbattle_rematch TRAINER_BETH_HNS, Route26_Text_BethRematchIntro, Route26_Text_BethRematchDefeat
	msgbox Route26_Text_BethPostRematch, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Richard::
	trainerbattle_single TRAINER_RICHARD_HNS, Route26_Text_PsychicRichardSeen, Route26_Text_PsychicRichardBeaten
	msgbox Route26_Text_PsychicRichardAfter, MSGBOX_AUTOCLOSE
	end

Route26_Text_CooltrainermJakeSeen:
    .string "אני עושה את ההכנות האחרונות\n"
    .string "לקראת ליגת הפוקימון.$"

Route26_Text_CooltrainermJakeBeaten:
    .string "פישלתי!$"

Route26_Text_CooltrainermJakeAfter:
    .string "יהיה קשה לנצח בליגה.\p"
    .string "אני צריך להתאמן עוד קצת.\p"
    .string "שמעתי שהרביעייה העילית של הליגה\n"
    .string "קשוחה יותר ממנהיגי המכונים.$"

Route26_Text_CooltrainermGavenSeen:
    .string "כשחווים קרבות קשים, צוברים כוח.$"

Route26_Text_CooltrainermGavenBeaten:
    .string "אאאה! החיים קשים עוד יותר!$"

Route26_Text_CooltrainermGavenAfter:
    .string "כדי להגיע לליגת הפוקימון,\n"
    .string "צריך לעבור את דרך הניצחון.\p"
    .string "אבל דרך הניצחון קשה.\p"
    .string "כמעט אף אחד לא הולך לשם!$"

Route26_Text_GavenRegister:
    .string "כדי להגיע לליגת הפוקימון,\n"
    .string "צריך לעבור את דרך הניצחון.\p"
    .string "אבל דרך הניצחון קשה.\p"
    .string "כמעט אף אחד לא הולך לשם!$"

Route26_Text_GavenRematchIntro:
    .string "כשחווים קרבות קשים, צוברים כוח.$"

Route26_Text_GavenRematchDefeat:
    .string "אאאה! החיים קשים עוד יותר!$"

Route26_Text_GavenPostRematch:
    .string "כדי להגיע לליגת הפוקימון,\n"
    .string "צריך לעבור את דרך הניצחון.\p"
    .string "אבל דרך הניצחון קשה.\p"
    .string "כמעט אף אחד לא הולך לשם!$"

Route26_Text_CooltrainerfJoyceSeen:
    .string "אם הגעת עד לכאן, אתה בטח טוב.\p"
    .string "אני אתן בקרב הזה את כל מה שיש לי!$"

Route26_Text_CooltrainerfJoyceBeaten:
    .string "לא! אני לא מאמינה!$"

Route26_Text_CooltrainerfJoyceAfter:
    .string "ניצחתי שמונה מנהיגי מכונים,\n"
    .string "אז הרגשתי בטוחה בעצמי.\p"
    .string "אצטרך להתאמץ יותר בפעם הבאה.$"

Route26_Text_CooltrainerfBethSeen:
    .string "הפסדתי למאמן בשם {RIVAL}.\p"
    .string "הוא היה ממש חזק, אבל…\p"
    .string "זה היה כאילו הוא חייב לנצח בכל מחיר.\p"
    .string "ריחמתי על הפוקימונים שלו.$"

Route26_Text_CooltrainerfBethBeaten:
    .string "פוקימונים הם לא כלי מלחמה.$"

Route26_Text_CooltrainerfBethAfter:
    .string "פוקימונים הם שותפים יקרי ערך לכל החיים.$"

Route26_Text_BethRegister:
    .string "פוקימונים הם שותפים יקרי ערך לכל החיים.$"

Route26_Text_BethRematchIntro:
    .string "הפסדתי למאמן בשם {RIVAL}.\p"
    .string "אבל לך לא אפסיד!$"

Route26_Text_BethRematchDefeat:
    .string "פוקימונים הם לא כלי מלחמה.$"

Route26_Text_BethPostRematch:
    .string "פוקימונים הם שותפים יקרי ערך לכל החיים.$"

Route26_Text_PsychicRichardSeen:
    .string "וואו, כמה תגים!\n"
    .string "אני מתרשם.\p"
    .string "אבל לא מספיק לך רק לאסוף אותם, נכון?$"

Route26_Text_PsychicRichardBeaten:
    .string "קרב טוב!$"

Route26_Text_PsychicRichardAfter:
    .string "אנשים ופוקימונים גדלים מהחוויות שלהם.\p"
    .string "אסור להתעצל ולהיות שאננים.$"

Route26_Text_Sign:
    .string "ROUTE 26\p"
    .string "POKéMON LEAGUE\n"
    .string "RECEPTION GATE$"

