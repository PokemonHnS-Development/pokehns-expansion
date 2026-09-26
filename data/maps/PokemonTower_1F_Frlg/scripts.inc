PokemonTower_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonTower_1F_OnTransition
	.byte 0

PokemonTower_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_POKEMON_TOWER_1F
	end

PokemonTower_1F_EventScript_Channeler::
	msgbox PokemonTower_1F_Text_SenseSpiritsUpToMischief, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_Woman1::
	msgbox PokemonTower_1F_Text_GrowlitheWhyDidYouDie, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_BaldingMan::
	msgbox PokemonTower_1F_Text_CameToPrayForDepartedClefairy, MSGBOX_NPC
	end

PokemonTower_1F_EventScript_Woman2::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PokemonTower_1F_EventScript_Woman2MalePlayer
	msgbox PokemonTower_1F_Text_ComeToPayRespectsGirl
	release
	end

PokemonTower_1F_EventScript_Woman2MalePlayer::
	msgbox PokemonTower_1F_Text_ComeToPayRespectsSon
	release
	end

PokemonTower_1F_EventScript_WorkerF::
	msgbox PokemonTower_1F_Text_ErectedInMemoryOfDeadMons, MSGBOX_NPC
	end

PokemonTower_1F_Text_ErectedInMemoryOfDeadMons::
	.string "La TORRE POKéMON fue erigida en\n"
	.string "memoria de los POKéMON que murieron.$"

PokemonTower_1F_Text_ComeToPayRespectsSon::
	.string "¿Vienes a mostrar respeto?\p"
	.string "Bendito sea tu corazón amante de\n"
	.string "hijo.$"

PokemonTower_1F_Text_ComeToPayRespectsGirl::
	.string "¿Vienes a mostrar respeto?\p"
	.string "Bendito sea tu corazón amante de\n"
	.string "los POKéMON, niña.$"

PokemonTower_1F_Text_CameToPrayForDepartedClefairy::
	.string "Vine a rezar por mi querido\n"
	.string "CLEFAIRY fallecida.\p"
	.string "¡Snif!\n"
	.string "Estoy bañado en lágrimas...$"

PokemonTower_1F_Text_GrowlitheWhyDidYouDie::
	.string "Mi GROWLITHE...\n"
	.string "¿Por qué moriste?$"

PokemonTower_1F_Text_SenseSpiritsUpToMischief::
	.string "Soy un CANALIZADOR.\p"
	.string "Hay espíritus haciendo travesuras.\n"
	.string "Los siento en lo alto de la TORRE.$"

