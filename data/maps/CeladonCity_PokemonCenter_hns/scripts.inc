CeladonCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeladonCity_PokemonCenter_OnTransition
	.byte 0

CeladonCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_CELADON_CITY_HNS
	end

CeladonCity_PokemonCenter_EventScript_CooltrainerF::
	msgbox CeladonCity_PokemonCenter1F_Text_CooltrainerF, MSGBOX_NPC
	end

CeladonCity_PokemonCenter_EventScript_Pharmacist::
	msgbox CeladonCity_PokemonCenter1F_Text_Pharmacist, MSGBOX_NPC
	end

CeladonCity_PokemonCenter_EventScript_Eusine::
	msgbox Celadon_Text_Eusine1, MSGBOX_NPC
	end

CeladonCity_PokemonCenter1F_Text_CooltrainerF:
	.string "אריקה היא מומחית לפוקימונים\n"
	.string "מסוג עשב.\p"
	.string "היא תגרום לך לשלם ביוקר\n"
	.string "אם לא תיזהר.$"

CeladonCity_PokemonCenter1F_Text_Pharmacist:
	.string "המחבוא של צוות רוקט נמצא\n"
	.string "במרתף של המשחקייה.\p"
	.string "אה, רגע. זה היה לפני\n"
	.string "שלוש שנים.$"

Celadon_Text_Eusine1:
	.string "יוסין: היי!\p"
	.string "חזרתי לבקר בעיר הולדתי.\p"
	.string "עבר די הרבה זמן.$"

Celadon_Text_EusineLeaves:
	.string "{PLAYER}, have you heard?\p"
	.string "There have been fresh rumors of a\n"
	.string "rainbow-colored POKéMON\n"
	.string "appearing at TIN TOWER.\p"
	.string "I've just had my party healed,\n"
	.string "so now I'm headed to ECRUTEAK.\p"
	.string "I'll be seeing you, {PLAYER}!$"

Celadon_Text_NoBeasts:
	.string "Oh, by the way, {PLAYER}.\p"
	.string "Have you caught the legendary\n"
	.string "POKéMON RAIKOU and ENTEI?\p"
	.string "<……><……><……>\p"
	.string "Okay…\p"
	.string "If you catch even one, I hope\n"
	.string "that you'll inform me.\p"
	.string "I'm counting on you, {PLAYER}!$"
