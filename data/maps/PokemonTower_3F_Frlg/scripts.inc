PokemonTower_3F_Frlg_MapScripts::
	.byte 0

PokemonTower_3F_EventScript_Patricia::
	trainerbattle_single TRAINER_CHANNELER_PATRICIA, PokemonTower_3F_Text_PatriciaIntro, PokemonTower_3F_Text_PatriciaDefeat
	msgbox PokemonTower_3F_Text_PatriciaPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_3F_EventScript_Carly::
	trainerbattle_single TRAINER_CHANNELER_CARLY, PokemonTower_3F_Text_CarlyIntro, PokemonTower_3F_Text_CarlyDefeat
	msgbox PokemonTower_3F_Text_CarlyPostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_3F_EventScript_Hope::
	trainerbattle_single TRAINER_CHANNELER_HOPE, PokemonTower_3F_Text_HopeIntro, PokemonTower_3F_Text_HopeDefeat
	msgbox PokemonTower_3F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_3F_Text_HopeIntro::
	.string "Urrg... Awaa...\n"
	.string "Huhu... Graa...$"

PokemonTower_3F_Text_HopeDefeat::
	.string "Hwa!\n"
	.string "¡Estoy a salvo!$"

PokemonTower_3F_Text_HopePostBattle::
	.string "Los fantasmas pueden ser\n"
	.string "identificados con el SCOPE SILPH.$"

PokemonTower_3F_Text_CarlyIntro::
	.string "Kekeke...\n"
	.string "Kwaaah!$"

PokemonTower_3F_Text_CarlyDefeat::
	.string "Hmm?\n"
	.string "¿Qué estoy haciendo?$"

PokemonTower_3F_Text_CarlyPostBattle::
	.string "¡Lo siento!\n"
	.string "¡Estaba poseído!$"

PokemonTower_3F_Text_PatriciaIntro::
	.string "¡Fuera de aquí!\n"
	.string "¡Espíritu malévolo!$"

PokemonTower_3F_Text_PatriciaDefeat::
	.string "¡Uff!\n"
	.string "¡El espíritu se fue!$"

PokemonTower_3F_Text_PatriciaPostBattle::
	.string "Los demás arriba...\n"
	.string "Debieron estar poseídos.$"

