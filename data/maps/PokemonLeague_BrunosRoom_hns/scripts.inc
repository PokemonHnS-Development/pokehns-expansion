PokemonLeague_BrunosRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EliteFourRoom_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, PokemonLeague_BrunosRoom_OnResume
	map_script MAP_SCRIPT_ON_LOAD, EliteFourRoom_OnLoad
	.byte 0

PokemonLeague_BrunosRoom_OnResume::
	setvar VAR_0x8004, 2
	special DoPokemonLeagueLightingEffect
	end

PokemonLeague_BrunosRoom_EventScript_Bruno::
	lock 
	faceplayer
	goto_if_ge VAR_LEAGUE_STATE, 4, PokemonLeague_BrunosRoom_EventScript_BrunoDefeated
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_BrunosRoom_EventScript_BrunoRematch
	msgbox PokemonLeague_BrunosRoom_Text_Before, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_BRUNO_1_HNS, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoRematch::
	goto_if_unset FLAG_IS_KANTO_CHAMPION, PokemonLeague_BrunosRoom_EventScript_BrunoRematchStandard
	goto_if_ge VAR_SINJOH_STORYLINE, 13, PokemonLeague_BrunosRoom_EventScript_BrunoRematchPostOBC

PokemonLeague_BrunosRoom_EventScript_BrunoRematchStandard::
	msgbox PokemonLeague_BrunosRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_BRUNO_2_HNS, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoRematchPostOBC::
	msgbox PokemonLeague_BrunosRoom_Text_RematchBefore, MSGBOX_DEFAULT
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_5
	trainerbattle_no_intro TRAINER_BRUNO_POSTOBC_HNS, PokemonLeague_BrunosRoom_Text_Beaten
	goto PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat

PokemonLeague_BrunosRoom_EventScript_BrunoOnDefeat::
	clearflag FLAG_TEMP_5	
	msgbox PokemonLeague_BrunosRoom_Text_Defeat, MSGBOX_DEFAULT
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
	setvar VAR_LEAGUE_STATE, 4
	release
	end

PokemonLeague_BrunosRoom_EventScript_BrunoDefeated::
	msgbox PokemonLeague_BrunosRoom_Text_Defeat, MSGBOX_DEFAULT
	closemessage
	release
	end

PokemonLeague_BrunosRoom_Text_RematchBefore:
    .string "ברונו: ברוך שובך, לוחם צעיר.\p"
    .string "באימונים קפדניים, נעשינו חזקים יותר.\p"
    .string "הרצון שלי, הקשה כסלע,\n"
    .string "איתן ובלתי מתפשר מתמיד.\p"
    .string "אתה מוכן להתמודד\n"
    .string "עם אתגר גדול עוד יותר?\p"
    .string "הראה לי את פירות האימונים שלך.\p"
    .string "הו הא!$"

PokemonLeague_BrunosRoom_Text_Before:
    .string "אני ברונו מהרביעייה העילית.\p"
    .string "אני תמיד מתאמן עד הקצה,\n"
    .string "כי אני מאמין בפוטנציאל שלנו.\p"
    .string "כך נעשינו חזקים.\p"
    .string "תוכל לעמוד בכוח שלנו?\p"
    .string "הממ? אני לא רואה בך פחד.\n"
    .string "אתה נראה נחוש. מושלם לקרב!\p"
    .string "מוכן, {PLAYER}?\n"
    .string "אתה תכרע ברך בפני הכוח המוחץ שלנו!\p"
    .string "הו הא!$"

PokemonLeague_BrunosRoom_Text_Beaten:
    .string "למה? איך יכולנו להפסיד?$"

PokemonLeague_BrunosRoom_Text_Defeat:
    .string "אחרי שהפסדתי, אין לי זכות לומר דבר…\p"
    .string "המשך אל האתגר הבא!$"
