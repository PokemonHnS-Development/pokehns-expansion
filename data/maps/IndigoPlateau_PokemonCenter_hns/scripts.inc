IndigoPlateau_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, IndigoPlateau_PokemonCenter_OnFrame 
	map_script MAP_SCRIPT_ON_TRANSITION, IndigoPlateau_Pokecenter_OnTransition
	.byte 0

IndigoPlateau_PokemonCenter_OnFrame::
	map_script_2 VAR_LEAGUE_STATE, 0, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 2, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 3, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 4, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 5, IndigoPlateau_PokemonCenter_Enter
	map_script_2 VAR_LEAGUE_STATE, 6, IndigoPlateau_PokemonCenter_Enter
	.2byte 0

IndigoPlateau_PokemonCenter_Enter::
	setflag FLAG_VISITED_INDIGO_PLATEAU
	setvar VAR_LEAGUE_STATE, 1
	end

IndigoPlateau_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_INDIGO_PLATEAU_HNS
	end


IndigoPlateau_EventScript_Cooltrainer::
	msgbox IndigoPlateau_Text_CooltrainerM, MSGBOX_NPC
	end

IndigoPlateau_EventScript_BlackBelt::
	msgbox IndigoPlateau_Text_Blackbelt, MSGBOX_NPC
	end

IndigoPlateau_EventScript_ShigyNinja::
	msgbox IndigoPlateau_Text_ShigyNinja, MSGBOX_NPC
	end

IndigoPlateau_Text_ShigyNinja:
	.string "כל הכבוד שהגעת עד לכאן!\p"
	.string "ראיתי המון מאמנים עוברים כאן\n"
	.string "לאורך השנים, וכולם מיוחדים להפליא.\p"
	.string "אתה צריך להיות גאה בעצמך\n"
	.string "על שהגעת כל כך רחוק!\p"
	.string "עכשיו, קדימה, תראה להם!$"

IndigoPlateau_Text_Blackbelt:
	.string "ליגת הפוקימון לא מקבלת כרגע\n"
	.string "מתמודדים חדשים.\p"
	.string "אפשר לחזור ולבדוק מאוחר יותר.$"

IndigoPlateau_Text_CooltrainerM:
    .string "בליגת הפוקימון, הרביעייה העילית\n"
    .string "תעמיד אותך במבחן.\p"
    .string "צריך לנצח את כולם. מי שמפסיד\n"
    .string "מתחיל הכול מההתחלה!$"

IndigoPlateau_EventScript_Silver::
	lock
	faceplayer 
	goto_if_set FLAG_DAILY_BEAT_SILVER, IndigoPlateau_EventScript_SilverBeat
	msgbox IndigoPlateau_Text_RivalEntrance1, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, IndigoPlateau_Silver_Battle_Cyndaquil
	call_if_eq VAR_STARTER_MON, 1, IndigoPlateau_Silver_Battle_Totodile
	call_if_eq VAR_STARTER_MON, 2, IndigoPlateau_Silver_Battle_Chikorita
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	setflag FLAG_DAILY_BEAT_SILVER
	release
	end

IndigoPlateau_EventScript_SilverBeat::
	msgbox IndigoPlateau_Text_RivalAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_Silver_Battle_Cyndaquil::
	trainerbattle_no_intro TRAINER_RIVAL_CYNDAQUIL_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Totodile::
	trainerbattle_no_intro TRAINER_RIVAL_TOTODILE_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Silver_Battle_Chikorita::
	trainerbattle_no_intro TRAINER_RIVAL_CHIKORITA_7_HNS, IndigoPlateau_Text_RivalWin
	return

IndigoPlateau_Text_RivalEntrance1:
    .string "עצור.\p"
    .string "אתה מתכוון לגשת עכשיו לאתגר\n"
    .string "של ליגת הפוקימון?\p"
    .string "זה לא יקרה.\p"
    .string "הפוקימונים הסופר-מאומנים שלי\n"
    .string "הולכים לרסק אותך.\p"
    .string "{PLAYER}!\n"
    .string "אני מאתגר אותך!$"

IndigoPlateau_Text_RivalWin:
    .string "…\p"
    .string "טוב - הפסדתי…$"

IndigoPlateau_Text_RivalAfter:
    .string "…לעזאזל… אני עדיין לא מצליח לנצח…\p"
    .string "אני… אני צריך לחשוב יותר\n"
    .string "על הפוקימונים שלי…\p"
    .string "המף! תשתדל לא להפסיד!$"

IndigoPlateau_EventScript_Psychic::
	lock
	faceplayer
	msgbox IndigoPlateau_Text_TeleportGuy1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, IndigoPlateau_EventScript_PsychicTeleport
	msgbox IndigoPlateau_Text_TeleportGuyNo, MSGBOX_DEFAULT
	closemessage
	release
	end

IndigoPlateau_EventScript_PsychicTeleport::
	msgbox IndigoPlateau_Text_TeleportGuyYes, MSGBOX_DEFAULT
	closemessage
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playbgm MUS_HG_NEW_BARK, FALSE
	delay 60
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	applymovement2 LOCALID_INDIGOPLATEAU_ABRA, IndigoPLateau_Movement_Abra
	waitmovement 0
	fadescreen FADE_TO_WHITE
	warpteleport MAP_NEW_BARK_TOWN_HNS, 20, 12
	waitstate
	release
	end
	
IndigoPLateau_Movement_Abra:
	jump_in_place_right
	jump_in_place_right
	step_end

IndigoPlateau_EventScript_Abra::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ABRA, CRY_MODE_NORMAL
	msgbox IndigoPlateau_Text_Abra, MSGBOX_DEFAULT
	waitmoncry
	release
	end

IndigoPlateau_Text_TeleportGuy1:
    .string "אה! אתה מאתגר את הרביעייה העילית?\n"
    .string "אתה בטוח שאתה מוכן?\p"
    .string "אם אתה צריך להתאמן עוד קצת,\n"
    .string "האברה שלי יכול לעזור לך.\p"
    .string "הוא יכול להחזיר אותך הביתה\n"
    .string "בעזרת השתגרות.\p"
    .string "אתה רוצה לחזור הביתה עכשיו?$"

IndigoPlateau_Text_TeleportGuyYes:
    .string "בסדר, בסדר.\n"
    .string "תדמיין את הבית שלך בעיני רוחך…$"

IndigoPlateau_Text_TeleportGuyNo:
    .string "בסדר, בסדר. בהצלחה רבה!$"

IndigoPlateau_Text_Abra:
    .string "אברה: אאברה…$"
