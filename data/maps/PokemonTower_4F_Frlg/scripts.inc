PokemonTower_4F_Frlg_MapScripts::
	.byte 0

PokemonTower_4F_EventScript_Paula::
	trainerbattle_single TRAINER_CHANNELER_PAULA, PokemonTower_4F_Text_PaulaIntro, PokemonTower_4F_Text_PaulaDefeat
	msgbox PokemonTower_4F_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_Laurel::
	trainerbattle_single TRAINER_CHANNELER_LAUREL, PokemonTower_4F_Text_LaurelIntro, PokemonTower_4F_Text_LaurelDefeat
	msgbox PokemonTower_4F_Text_LaurelPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_EventScript_Jody::
	trainerbattle_single TRAINER_CHANNELER_JODY, PokemonTower_4F_Text_JodyIntro, PokemonTower_4F_Text_JodyDefeat
	msgbox PokemonTower_4F_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_4F_Text_PaulaIntro::
	.string "¡Un fantasma! ¡No!\n"
	.string "Kwaaah!$"

PokemonTower_4F_Text_PaulaDefeat::
	.string "¿Dónde está el fantasma?$"

PokemonTower_4F_Text_PaulaPostBattle::
	.string "Debo haber estado soñando…$"

PokemonTower_4F_Text_LaurelIntro::
	.string "¡Sé maldito conmigo!\n"
	.string "Kwaaah!$"

PokemonTower_4F_Text_LaurelDefeat::
	.string "¡¿Qué?!$"

PokemonTower_4F_Text_LaurelPostBattle::
	.string "No podemos determinar la identidad\n"
	.string "los fantasmas…$"

PokemonTower_4F_Text_JodyIntro::
	.string "Huhuhu…\n"
	.string "¡No me pegues!$"

PokemonTower_4F_Text_JodyDefeat::
	.string "¿Eh?\n"
	.string "¿Quién? ¿Qué?$"

PokemonTower_4F_Text_JodyPostBattle::
	.string "May the departed POKéMON rest in\n"
	.string "peace…$"

