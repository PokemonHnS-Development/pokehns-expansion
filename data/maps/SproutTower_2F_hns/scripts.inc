SproutTower_2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SproutTower_2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

SproutTower_2F_OnTransition: 
	callnative SetTimeBasedEncounters
	end

SproutTower_2F_EventScript_SageNico::
	trainerbattle_single TRAINER_NICO_HNS, SproutTower_Text_SageNico_Seen, SproutTower_Text_SageNico_Beaten
	msgbox SproutTower_Text_SageNico_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_2F_EventScript_SageEdmond::
	trainerbattle_single TRAINER_EDMOND_HNS, SproutTower_Text_SageEdmond_Seen, SproutTower_Text_SageEdmond_Beaten
	msgbox SproutTower_Text_SageEdmond_AfterBattle, MSGBOX_AUTOCLOSE
	end

SproutTower_2F_EventScript_Statue::
	lock
	msgbox SproutTower_Text_2F_Statue, MSGBOX_AUTOCLOSE
	release
	end

SproutTower_2F_EventScript_Xdefend::
	finditem ITEM_X_DEFEND
	end

SproutTower_Text_SageNico_Seen:
	.string "No importa cuánto luchemos,\n"
	.string "la TORRE seguirá en pie.$"

SproutTower_Text_SageNico_Beaten:
	.string "Luché fuerte, pero soy muy débil.$"

SproutTower_Text_SageNico_AfterBattle:
	.string "El pilar flexible protege la\n"
	.string "TORRE, incluso de terremotos.$"

SproutTower_Text_SageEdmond_Seen:
	.string "…Se mece como hoja al viento…$"

SproutTower_Text_SageEdmond_Beaten:
	.string "Oh, I'm weak!$"

SproutTower_Text_SageEdmond_AfterBattle:
	.string "Traté de copiar los suaves\n"
	.string "movimientos de BELLSPROUT…\p"
	.string "Pero no entrené lo suficiente.$"

SproutTower_Text_2F_Statue:
	.string "Una estatua POKéMON...\p"
	.string "Se ve muy distinguida.$"
