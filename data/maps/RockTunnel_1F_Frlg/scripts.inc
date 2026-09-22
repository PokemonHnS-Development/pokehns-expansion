RockTunnel_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RockTunnel_1F_OnTransition
	.byte 0

RockTunnel_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ROCK_TUNNEL_1F
	end

RockTunnel_1F_EventScript_RouteSign::
	msgbox RockTunnel_1F_Text_RouteSign, MSGBOX_SIGN
	end

RockTunnel_1F_EventScript_Lenny::
	trainerbattle_single TRAINER_HIKER_LENNY, RockTunnel_1F_Text_LennyIntro, RockTunnel_1F_Text_LennyDefeat
	msgbox RockTunnel_1F_Text_LennyPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Oliver::
	trainerbattle_single TRAINER_HIKER_OLIVER, RockTunnel_1F_Text_OliverIntro, RockTunnel_1F_Text_OliverDefeat
	msgbox RockTunnel_1F_Text_OliverPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Lucas::
	trainerbattle_single TRAINER_HIKER_LUCAS, RockTunnel_1F_Text_LucasIntro, RockTunnel_1F_Text_LucasDefeat
	msgbox RockTunnel_1F_Text_LucasPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Ashton::
	trainerbattle_single TRAINER_POKEMANIAC_ASHTON, RockTunnel_1F_Text_AshtonIntro, RockTunnel_1F_Text_AshtonDefeat
	msgbox RockTunnel_1F_Text_AshtonPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Leah::
	trainerbattle_single TRAINER_PICNICKER_LEAH, RockTunnel_1F_Text_LeahIntro, RockTunnel_1F_Text_LeahDefeat
	msgbox RockTunnel_1F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Ariana::
	trainerbattle_single TRAINER_PICNICKER_ARIANA, RockTunnel_1F_Text_ArianaIntro, RockTunnel_1F_Text_ArianaDefeat
	msgbox RockTunnel_1F_Text_ArianaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_EventScript_Dana::
	trainerbattle_single TRAINER_PICNICKER_DANA, RockTunnel_1F_Text_DanaIntro, RockTunnel_1F_Text_DanaDefeat
	msgbox RockTunnel_1F_Text_DanaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_1F_Text_LennyIntro::
	.string "This tunnel goes a long way, kid!$"

RockTunnel_1F_Text_LennyDefeat::
	.string "Doh!\n"
	.string "¡Tú ganas!$"

RockTunnel_1F_Text_LennyPostBattle::
	.string "Cuidado con ONIX.\n"
	.string "Solo aparecen de vez en cuando.\p"
	.string "¡Los de nivel alto pueden\n"
	.string "apretarlos mucho!$"

RockTunnel_1F_Text_OliverIntro::
	.string "Hmm.\n"
	.string "Quizá estoy perdido aquí...$"

RockTunnel_1F_Text_OliverDefeat::
	.string "Ease up!\n"
	.string "¿Qué estoy haciendo?\l"
	.string "¿Por dónde se sale?$"

RockTunnel_1F_Text_OliverPostBattle::
	.string "That sleeping POKéMON on ROUTE 12\n"
	.string "me obligó a tomar este desvío.$"

RockTunnel_1F_Text_LucasIntro::
	.string "Los de fuera como tú deben\n"
	.string "some respect!$"

RockTunnel_1F_Text_LucasDefeat::
	.string "¡Me rindo!$"

RockTunnel_1F_Text_LucasPostBattle::
	.string "You're talented enough to hike!$"

RockTunnel_1F_Text_AshtonIntro::
	.string "POKéMON fight!\n"
	.string "¡Listo, ya!$"

RockTunnel_1F_Text_AshtonDefeat::
	.string "Game over!$"

RockTunnel_1F_Text_AshtonPostBattle::
	.string "Oh well, I'll get a ZUBAT as I go!$"

RockTunnel_1F_Text_LeahIntro::
	.string "Eek!\p"
	.string "No intentes nada raro en el\n"
	.string "dark!$"

RockTunnel_1F_Text_LeahDefeat::
	.string "Estaba muy oscuro...$"

RockTunnel_1F_Text_LeahPostBattle::
	.string "Vi un MACHOP en este túnel.$"

RockTunnel_1F_Text_DanaIntro::
	.string "I came this far looking for wild\n"
	.string "POKéMON.$"

RockTunnel_1F_Text_DanaDefeat::
	.string "I'm out of POKéMON!$"

RockTunnel_1F_Text_DanaPostBattle::
	.string "Parecías tierno e inofensivo.\n"
	.string "¡Qué equivocada estaba!$"

RockTunnel_1F_Text_ArianaIntro::
	.string "You have POKéMON!\n"
	.string "¡Empecemos!$"

RockTunnel_1F_Text_ArianaDefeat::
	.string "¡Juegas duro!$"

RockTunnel_1F_Text_ArianaPostBattle::
	.string "¡Uff!\n"
	.string "I'm all sweaty now.$"

RockTunnel_1F_Text_RouteSign::
	.string "ROCK TUNNEL\n"
	.string "CIUDAD CEREZO - PUEBLO LAVANDA$"

