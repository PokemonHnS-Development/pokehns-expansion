Route46_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route46_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route46_EventScript_Bailey::
	trainerbattle_single TRAINER_BAILEY_HNS, Route46_Text_HikerBaileySeen, Route46_Text_HikerBaileyBeaten
	msgbox Route46_Text_HikerBaileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Ted::
	trainerbattle_single TRAINER_TED_HNS, Route46_Text_CamperTedSeen, Route46_Text_CamperTedBeaten
	msgbox Route46_Text_CamperTedAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Erin::
	trainerbattle_single TRAINER_ERIN_HNS, Route46_Text_PicnickerErinSeen, Route46_Text_PicnickerErinBeaten, Route46_EventScript_RegisterErin
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route46_EventScript_RematchErin
	msgbox Route46_Text_PicnickerErinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_RegisterErin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route46_Text_ErinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ERIN_HNS
	release
	end

Route46_EventScript_RematchErin::
	trainerbattle_rematch TRAINER_ERIN_HNS, Route46_Text_ErinRematchIntro, Route46_Text_ErinRematchDefeat
	msgbox Route46_Text_ErinPostRematch, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Sign::
	lock
	msgbox Route46_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route46_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

Route46_Text_HikerBaileySeen:
	.string "¡Muy bien! ¡Te mostraré el\n"
	.string "poder de los POKéMON de montaña!$"

Route46_Text_HikerBaileyBeaten:
	.string "¡Piedad! ¡Me has demostrado\n"
	.string "tu poder!$"

Route46_Text_HikerBaileyAfterBattle:
	.string "Se acabó. No me importa.\n"
	.string "Los EXCURSIONISTAS somos así.$"

Route46_Text_CamperTedSeen:
	.string "¡Yo también crío POKéMON!\p"
	.string "¿Luchas contra mí?$"

Route46_Text_CamperTedBeaten:
	.string "¿Qué...?$"

Route46_Text_CamperTedAfterBattle:
	.string "Hice lo que pude, pero no fue\n"
	.string "suficiente.\p"
	.string "Sin excusas, admito que perdí.$"

Route46_Text_PicnickerErinSeen:
	.string "¡Yo también crío POKéMON!\p"
	.string "¿Luchas contra mí?$"

Route46_Text_PicnickerErinBeaten:
	.string "¡Qué fastidio!$"

Route46_Text_PicnickerErinAfterBattle:
	.string "He ido a muchos GIMNASIOS, pero el\n"
	.string "de CIUDAD TRIGAL es mi favorito.\p"
	.string "¡Está lleno de flores hermosas!$"

Route46_Text_ErinRegister:
	.string "He ido a muchos GIMNASIOS, pero el\n"
	.string "de CIUDAD TRIGAL es mi favorito.\p"
	.string "¡Está lleno de flores hermosas!$"

Route46_Text_ErinRematchIntro:
	.string "¡Yo también crío POKéMON!\p"
	.string "¿Luchas contra mí?$"

Route46_Text_ErinRematchDefeat:
	.string "¡Qué fastidio!$"

Route46_Text_ErinPostRematch:
	.string "He ido a muchos GIMNASIOS, pero el\n"
	.string "de CIUDAD TRIGAL es mi favorito.\p"
	.string "¡Está lleno de flores hermosas!$"

Route46_Text_PicnickerErin2Beaten:
	.string "Aww... ¡siempre termino perdiendo!\p"
	.string "¡Tendré que esforzarme más!\n"
	.string "En fin, gracias por luchar\n"
	.string "conmigo una y otra vez.\p"
	.string "Toma el regalo de la\n"
	.string "otra vez.$"

Route46_Text_Sign:
	.string "RUTA 46\n"
	.string "CAMINO DE MONTAÑA ADELANTE$"
