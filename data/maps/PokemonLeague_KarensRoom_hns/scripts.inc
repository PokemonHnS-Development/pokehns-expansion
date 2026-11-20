PokemonLeague_KarensRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_KarensRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_KarensRoom_OnResume::
	setvar VAR_0x8004, 3
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_KarensRoom_EventScript_Karen::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 5, PokemonLeague_KarensRoom_EventScript_KarenDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematch
	msgbox PokemonLeague_KarensRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_1_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematch::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, PokemonLeague_KarensRoom_EventScript_KarenRematchStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC

PokemonLeague_KarensRoom_EventScript_KarenRematchStandard::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_2_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenRematchPostOBC::
	msgbox PokemonLeague_KarensRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_KAREN_POSTOBC_HNS, PokemonLeague_KarensRoom_Text_Beaten
	goto PokemonLeague_KarensRoom_EventScript_KarenOnDefeat

PokemonLeague_KarensRoom_EventScript_KarenOnDefeat::
    clearflag FLAG_TEMP_5
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	setmetatile 6, 1, 0x28E, FALSE
	setmetatile 6, 2, 0x296, FALSE	
	playse SE_BANG
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 4  @ num shakes
	setvar VAR_0x8007, 4  @ shake delay
	special ShakeCamera
	waitstate
	special DrawWholeMapView
	setvar VAR_LEAGUE_STATE, 5
	release
	end

PokemonLeague_KarensRoom_EventScript_KarenDefeated::
	msgbox PokemonLeague_KarensRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_KarensRoom_Text_RematchBefore:
    .string "קארן: אה, זה שוב אתה.\p"
    .string "אני מקווה שלא שכחת את האמונה שלי:\p"
    .string "כוח אמיתי נובע מאמון בפוקימונים שלך.\p"
    .string "מאז הפגישה האחרונה שלנו, הקשר שלי\n"
    .string "עם הפוקימונים שלי העמיק עוד יותר.\p"
    .string "אתה מוכן להתמודד מול קבוצה\n"
    .string "שמאוחדת בקשר בלתי שביר?\p"
    .string "הראה לי את הכוח של הקשר\n"
    .string "עם הפוקימונים שלך.$"

PokemonLeague_KarensRoom_Text_Before:
    .string "אני קארן מהרביעייה העילית.\p"
    .string "אתה {PLAYER}? כמה משעשע.\p"
    .string "אני אוהבת פוקימונים מסוג אפל.\p"
    .string "הדימוי הפראי והקשוח שלהם כל כך\n"
    .string "מושך אותי. והם גם חזקים מאוד.\p"
    .string "חושב שתוכל להם?\n"
    .string "לפחות נסה לשעשע אותי.\p"
    .string "בוא נתחיל.$"

PokemonLeague_KarensRoom_Text_Beaten:
    .string "נו, אתה באמת טוב.\n"
    .string "אני אוהבת את זה במאמן.$"

PokemonLeague_KarensRoom_Text_Defeat:
    .string "פוקימונים חזקים.\p"
    .string "פוקימונים חלשים.\p"
    .string "זו רק התפיסה האנוכית של בני האדם.\p"
    .string "מאמנים מיומנים באמת צריכים\n"
    .string "לנסות לנצח עם האהובים עליהם.\p"
    .string "אני אוהבת את הסגנון שלך.\n"
    .string "אתה מבין מה חשוב.\p"
    .string "קדימה - האלוף מחכה.$"

