GoldenrodCity_RadioTower_3F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_3F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_3F_OnLoad::
	call_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_HideGate
	end
	
GoldenrodCity_RadioTower_3F_HideGate::
	setmetatile 25, 8, 0x335, FALSE
	setmetatile 25, 9, 0x335, FALSE

	setmetatile 26, 8, 0X334, FALSE
	setmetatile 26, 9, 0X334, FALSE

	setmetatile 27, 8, 0X334, FALSE
	setmetatile 27, 9, 0X334, FALSE

	setmetatile 28, 8, 0X334, FALSE
	setmetatile 28, 9, 0X334, FALSE

	setmetatile 29, 8, 0X334, FALSE
	setmetatile 29, 9, 0X334, FALSE

	setmetatile 30, 8, 0X334, FALSE
	setmetatile 30, 9, 0X334, FALSE

	setmetatile 31, 8, 0X334, FALSE
	setmetatile 31, 9, 0X334, FALSE
	return


GoldenrodRaidoTower3_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_6_HNS, GoldenrodCity_RadioTower_3F_Text_GruntM7Seen, GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM7After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt7::
	trainerbattle_single TRAINER_GRUNT_7_HNS, GoldenrodCity_RadioTower_3F_Text_GruntM8Seen, GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM8After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_8_HNS, GoldenrodCity_RadioTower_3F_Text_GruntM9Seen, GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten
	msgbox GoldenrodCity_RadioTower_3F_Text_GruntM9After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower3_EventScript_Scientist::
	trainerbattle_single TRAINER_MARC_HNS, GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen, GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten
	msgbox GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUNNY_DAY, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2

	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_TM_SUNNY_DAY
	setflag FLAG_GOT_SUNNY_DAY
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Cooltrainer3::
	msgbox GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Nerd::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_3F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Gate::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_CardKeySlot, MSGBOX_SIGN
	goto_if_set FLAG_HIDE_RADIOTOWER_GATE, GoldenrodCity_RadioTower_3F_EventScript_GateOpened
	checkitem ITEM_CARD_KEY
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_RadioTower_3F_EventScript_OpenGate
	closemessage
	release
	end


GoldenrodCity_RadioTower_3F_EventScript_GateOpened::
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_OpenGate::
	msgbox GoldenrodCity_RadioTower_3F_Text_InsertedCardKey, MSGBOX_SIGN
	call GoldenrodCity_RadioTower_3F_HideGate
	playse SE_CLICK
	special DrawWholeMapView
	msgbox GoldenrodCity_RadioTower_3F_Text_Open, MSGBOX_SIGN
	setflag FLAG_HIDE_RADIOTOWER_GATE
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PersonnelSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_3F_Text_CardKeySlot:
	.string "זה החריץ של כרטיס הגישה.$"

GoldenrodCity_RadioTower_3F_Text_InsertedCardKey:
	.string "{PLAYER} הכניס את כרטיס הגישה.$"
 
GoldenrodCity_RadioTower_3F_Text_Open:
	.string "השער פתוח.$"

GoldenrodCity_RadioTower_3F_Text_PersonnelSign:
	.string "קומה 3: משאבי אנוש$"

GoldenrodCity_RadioTower_3F_Text_PokemonMusicSign:
	.string "מוזיקת פוקימון\n"
	.string "עם המנחה, הדי-ג'יי בן$"

GoldenrodCity_RadioTower_3F_Text_SuperNerd:
	.string "יש לנו הקלטות של הקריאות של\n"
	.string "כל הפוקימונים שהתגלו.\p"
	.string "בטח יש לנו בערך 400 מינים.$"

GoldenrodCity_RadioTower_3F_Text_GymGuideRockets:
	.string "To trainers, POKéMON are their\n"
	.string "beloved partners.\p"
	.string "It's terrible how TEAM ROCKET is\n"
	.string "trying to control POKéMON.$"

GoldenrodCity_RadioTower_3F_Text_GymGuide:
	.string "We run 24 hours a day to broadcast\n"
	.string "entertaining programs.\p"
	.string "I'll do my best to run around the\n"
	.string "clock too!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFPleaseSave:
	.string "הבוס של צוות רוקט נעל את עצמו בפנים.\p"
	.string "אבל מנהל התחנה יכול לפתוח את הדלת.\p"
	.string "הוא למעלה, בקומה החמישית.\p"
	.string "בבקשה, תציל אותו!$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFDirectorSafe:
	.string "Is the DIRECTOR safe?$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFHeroGift:
	.string "תודה! אתה הגיבור שלי!\p"
	.string "זה אות הוקרה ממני.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFSunnyDay:
	.string "זה המהלך יום שמשי.\p"
	.string "הוא מחזק לזמן מה מהלכים מסוג אש.$"

GoldenrodCity_RadioTower_3F_Text_CooltrainerFMarvelous:
	.string "היית פשוט נפלא!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Seen:
	.string "קיבלתי פקודות מפורשות.\p"
	.string "עליי למחוץ כל מי שמעז לאתגר\n"
	.string "את צוות רוקט!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7Beaten:
	.string "מה?!$"

GoldenrodCity_RadioTower_3F_Text_GruntM7After:
	.string "נכשלתי בתפקיד שלי…\p"
	.string "ארצ'ר ממש יתעצבן…$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Seen:
	.string "איזו הרגשה נהדרת לצוות על\n"
	.string "פוקימונים לבצע פשעים.$"

GoldenrodCity_RadioTower_3F_Text_GruntM8Beaten:
	.string "אתה צוחק עליי!$"

GoldenrodCity_RadioTower_3F_Text_GruntM8After:
	.string "אני מרגיש זוועה אחרי ההפסד!\p"
	.string "לעזאזל! אני שונא פוקימונים\n"
	.string "חסרי תועלת!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Seen:
	.string "למה התריס נפתח? יש לך\n"
	.string "יד בזה?$"

GoldenrodCity_RadioTower_3F_Text_GruntM9Beaten:
	.string "הלך עליי!$"

GoldenrodCity_RadioTower_3F_Text_GruntM9After:
	.string "מה?! חלפת על פני האנשים שלנו\n"
	.string "במעבר התת-קרקעי?\p"
	.string "איך הצלחת?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcSeen:
	.string "ילד זר מסתובב כאן?\p"
	.string "מי אתה?$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcBeaten:
	.string "אוף! זלזלתי בך!$"

GoldenrodCity_RadioTower_3F_Text_ScientistMarcAfter:
	.string "בוואה-הה-הה…\p"
	.string "מכאן אני יכול לשדר אות\n"
	.string "חזק ככל שאצטרך.$"

