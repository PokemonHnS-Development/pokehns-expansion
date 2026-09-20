SafariZoneGate_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SafariZoneGate_PokemonCenter_OnTransition
	.byte 0

SafariZoneGate_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_SAFARI_ZONE_GATE_HNS
	end

SafariZoneGate_PokemonCenter_EventScript_NPC1::
	lock
	faceplayer
	msgbox SafariZoneGate_PokemonCenter_Text_NPC1, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_PokemonCenter_EventScript_NPC2::
	lock
	faceplayer
	msgbox SafariZoneGate_PokemonCenter_Text_NPC2, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_PokemonCenter_Text_Boy::
	lock
	faceplayer
	msgbox SafariZoneGate_PokemonCenter_Text_SafariSong, MSGBOX_DEFAULT
	closemessage
	release
	end

SafariZoneGate_PokemonCenter_Text_NPC1:
	.string "Quienes vienen al POKéMON CENTER\n"
	.string "suelen cuidar bien sus POKéMON.\p"
	.string "¿No estás de acuerdo?$"

SafariZoneGate_PokemonCenter_Text_NPC2:
	.string "Tras caminar mucho por el monte\n"
	.string "para hallar un POKéMON CENTER,\l"
	.string "cuando ya no puedes más...\p"
	.string "¡Sientes que estás en el paraíso!$"

SafariZoneGate_PokemonCenter_Text_SafariSong:
	.string "Safari, safari, es muy divertido.\n"
	.string "Safari, safari, ¡qué interesante!\p"
	.string "¡Muchos POKéMON nos esperan!\p"
	.string "...Es una canción que inventé.\n"
	.string "La canto en la SAFARI ZONE.$"
