RuinsOfAlph_Outside_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Outside_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

RuinsOfAlph_Outside_OnTransition: 
	callnative SetTimeBasedEncounters
	end	

RuinsOfAlph_Outside_EventScript_Quagsire::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_QUAGSIRE, CRY_MODE_NORMAL
	msgbox RuinsOfAlph_Outside_Text_Quagsire, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RuinsOfAlph_Outside_Text_Quagsire:
	.string "קווגסייר: קווג קווג$"

RuinsOfAlph_Outside_EventScript_Stan::
	trainerbattle_single TRAINER_STAN_HNS, RuinsOfAlph_Outside_Text_SuperNerdStan_Seen, RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten
	msgbox RuinsOfAlph_Outside_Text_SuperNerdStan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Nathan::
	trainerbattle_single TRAINER_NATHAN_HNS, RuinsOfAlph_Outside_Text_PsychicNathan_Seen, RuinsOfAlph_Outside_Text_PsychicNathan_Beaten
	msgbox RuinsOfAlph_Outside_Text_PsychicNathan_After, MSGBOX_AUTOCLOSE
	end

RuinsOfAlph_Outside_EventScript_Youngster1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Youngster2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher1::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Fisher2::
	lock
	faceplayer
	msgbox RuinsOfAlph_Outside_Text_Fisher2, MSGBOX_DEFAULT
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign1::
	lock
	msgbox RuinsOfAlph_Outside_Text_MainSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign2::
	lock
	msgbox RuinsOfAlph_Outside_Text_ResearchSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_EventScript_Sign3::
	lock
	msgbox RuinsOfAlph_Outside_Text_MysteryChamberSign, MSGBOX_SIGN
	closemessage
	release
	end

RuinsOfAlph_Outside_Text_Scientist:
	.string "Hm? That's a POKéDEX, isn't it?\n"
	.string "May I see it?\p"
	.string "There are so many kinds of\n"
	.string "POKéMON.\p"
	.string "Hm? What's this?\p"
	.string "What is this POKéMON?\p"
	.string "It looks like the strange\n"
	.string "writing on the walls of the\p"
	.string "RUINS.\p"
	.string "If those drawings are really\n"
	.string "POKéMON, there should be many\n"
	.string "more.\p"
	.string "I know! Let me upgrade your\n"
	.string "POKéDEX. Follow me.$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Seen:
	.string "מה אתה רוצה? אני לומד -\n"
	.string "אל תפריע לי!$"

RuinsOfAlph_Outside_Text_SuperNerdStan_Beaten:
	.string "סליחה… אני מתוסכל מכך שעדיין\n"
	.string "אין לנו הבנה אמיתית…$"

RuinsOfAlph_Outside_Text_SuperNerdStan_After:
	.string "החורבות הן מלפני כ-1500 שנה.\p"
	.string "אף אחד לא יודע מי בנה אותן.\p"
	.string "גם לא ידוע אם לפסלי\n"
	.string "הפוקימונים יש משמעות כלשהי.\p"
	.string "הכול תעלומה אחת גדולה…$"

RuinsOfAlph_Outside_Text_PsychicNathan_Seen:
	.string "המממ… זה מקום מוזר.$"

RuinsOfAlph_Outside_Text_PsychicNathan_Beaten:
	.string "…$"

RuinsOfAlph_Outside_Text_PsychicNathan_After:
	.string "אני אוהב לחשוב כאן.$"

RuinsOfAlph_Outside_Text_MysteryChamberSign:
	.string "חדר לוחות האבן המסתוריים$"

RuinsOfAlph_Outside_Text_MainSign:
	.string "חורבות אלף\n"
	.string "המבקרים מוזמנים$"

RuinsOfAlph_Outside_Text_ResearchSign:
	.string "מרכז המחקר של חורבות אלף\p"
	.string "הסמכות המובילה בנושא\n"
	.string "חורבות אלף$"

RuinsOfAlph_Outside_Text_Fisher1:
	.string "כשחקרנו את החורבות, פתאום\n"
	.string "הרגשנו נוכחות משונה.\p"
	.string "כולנו נבהלנו וברחנו.\n"
	.string "כדאי גם לך להיזהר.$"

RuinsOfAlph_Outside_Text_Fisher2:
	.string "החורבות מסתירות סוד ענק!\p"
	.string "…נדמה לי…$"

RuinsOfAlph_Outside_Text_Youngster1:
	.string "יש הרבה סוגים של אנון, אז אנחנו\n"
	.string "משתמשים בהם לקודים הסודיים שלנו.$"

RuinsOfAlph_Outside_Text_Youngster2:
	.string "A… H… E… A… D… הממ…\p"
	.string "מה?\p"
	.string "אני מפענח את ההודעה הזאת!$"
