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
	.string "מי שמגיע למרכז פוקימון\n"
	.string "בדרך כלל דואג היטב לפוקימונים שלו.\p"
	.string "נכון?$"

SafariZoneGate_PokemonCenter_Text_NPC2:
	.string "אחרי הליכה ארוכה בהרים בחיפוש אחרי\n"
	.string "מרכז פוקימון, כשכבר עומדים לקרוס…\p"
	.string "אז מרגישים כמו בגן עדן!$"

SafariZoneGate_PokemonCenter_Text_SafariSong:
	.string "ספארי, ספארי, כל כך כיף.\n"
	.string "ספארי, ספארי, כל כך מעניין, נכון!\p"
	.string "כל כך הרבה פוקימונים מחכים לנו!\p"
	.string "…זה שיר שהמצאתי.\n"
	.string "אני שר אותו כשאני באזור הספארי.$"
