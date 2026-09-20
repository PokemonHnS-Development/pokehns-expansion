Route34_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route34_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route34_OnTransition: 
	specialvar VAR_RESULT, GetDaycareState
	call_if_eq VAR_RESULT, DAYCARE_EGG_WAITING, Route34_MapScript_EggReady
	callnative SetTimeBasedEncounters
	end	

Route34_MapScript_EggReady::
	setobjectxyperm LOCALID_ROUTE34_DAYCAREMAN, 30, 34
	return

Route34_EventScript_YoungsterSamuel::
	trainerbattle_single TRAINER_SAMUEL_HNS, Route34_Text_YoungsterSamuel_Seen, Route34_Text_YoungsterSamuel_Beaten
	msgbox Route34_Text_YoungsterSamuel_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_YoungsterIan::
	trainerbattle_single TRAINER_IAN_HNS, Route34_Text_YoungsterIan_Seen, Route34_Text_YoungsterIan_Beaten
	msgbox Route34_Text_YoungsterIan_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_CamperTodd::
	trainerbattle_single TRAINER_TODD_HNS, Route34_Text_CamperTodd_Seen, Route34_Text_CamperTodd_Beaten, Route34_EventScript_RegisterTodd
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route34_EventScript_RematchTodd
	msgbox Route34_Text_CamperTodd_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_RegisterTodd::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route34_Text_ToddRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TODD_HNS
	release
	end

Route34_EventScript_RematchTodd::
	trainerbattle_rematch TRAINER_TODD_HNS, Route34_Text_ToddRematchIntro, Route34_Text_ToddRematchDefeat
	msgbox Route34_Text_ToddPostRematch, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_PicnickerGina::
	trainerbattle_single TRAINER_GINA_HNS, Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten, Route34_EventScript_RegisterGina
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route34_EventScript_RematchGina
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_RegisterGina::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route34_Text_GinaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GINA_HNS
	release
	end

Route34_EventScript_RematchGina::
	trainerbattle_rematch TRAINER_GINA_HNS, Route34_Text_PicnickerGina_Seen, Route34_Text_PicnickerGina_Beaten
	msgbox Route34_Text_PicnickerGina_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_OfficerKeith::
	trainerbattle_single TRAINER_KEITH_HNS, Route34_Text_OfficerKeith_Seen, Route34_Text_OfficerKeith_Win
	msgbox Route34_Text_OfficerKeith_After, MSGBOX_AUTOCLOSE
	end


Route34_EventScript_PokefanMBrandon::
	trainerbattle_single TRAINER_BRANDON_HNS, Route34_Text_PokefanBrandon_Seen, Route34_Text_PokefanBrandon_Beaten
	msgbox Route34_Text_PokefanBrandon_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Irene::
	trainerbattle_single TRAINER_IRENE_HNS, Route34_Text_CooltrainerIrene_Seen, Route34_Text_CooltrainerIrene_Beaten
	msgbox Route34_Text_CooltrainerIrene_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Jenn::
	trainerbattle_single TRAINER_JENN_HNS, Route34_Text_CooltrainerJenn_Seen, Route34_Text_CooltrainerJenn_Beaten
	msgbox Route34_Text_CooltrainerJenn_After2, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Kate::
	trainerbattle_single TRAINER_KATE_HNS, Route34_Text_CooltrainerKate_Seen, Route34_Text_CooltrainerKate_Beaten
	msgbox Route34_Text_CooltrainerKate_After, MSGBOX_AUTOCLOSE
	end

Route34_EventScript_Sign1::
	lock
	msgbox Route34_Text_Sign_Route34, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign2::
	lock
	msgbox Route34_Text_Sign_DayCare, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Sign3::
	lock
	msgbox Route34_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end

Route34_EventScript_Item_SoftSand::
	finditem ITEM_SOFT_SAND
	end

Route34_EventScript_Item_RareCandy::
	finditem ITEM_RARE_CANDY
	end
	
Route34_EventScript_Item_Embargo::
    finditem ITEM_TM_EMBARGO
    end


Route34_Text_YoungsterSamuel_Seen:
	.string "Hey! I'm looking for MANKEY!$"

Route34_Text_YoungsterSamuel_Beaten:
	.string "Beaten by a passing stranger!$"

Route34_Text_YoungsterSamuel_After:
	.string "I'm going to train even harder.\p"
	.string "After all, I'm trying to become\n"
	.string "a GYM LEADER.$"

Route34_Text_YoungsterIan_Seen:
	.string "I'm the best in my class at\n"
	.string "POKéMON.$"

Route34_Text_YoungsterIan_Beaten:
	.string "No! There are better trainers…$"

Route34_Text_YoungsterIan_After:
	.string "I'm trying hard so I can be the\n"
	.string "star in my class.$"

Route34_Text_CamperTodd_Seen:
	.string "I'm confident in my ability to\n"
	.string "raise POKéMON.\p"
	.string "Want to see?$"

Route34_Text_CamperTodd_Beaten:
	.string "Did I screw up my training?$"

Route34_Text_CamperTodd_After:
	.string "Maybe I should take one to DAY-CARE,\n"
	.string "o quizás usar algunos objetos…$"

Route34_Text_ToddRegister:
	.string "Maybe I should take one to DAY-CARE,\n"
	.string "o quizás usar algunos objetos…$"

Route34_Text_ToddRematchIntro:
	.string "I'm confident in my ability to\n"
	.string "raise POKéMON.\p"
	.string "Want to see?$"

Route34_Text_ToddRematchDefeat:
	.string "Did I screw up my training?$"

Route34_Text_ToddPostRematch:
	.string "Maybe I should take one to DAY-CARE,\n"
	.string "o quizás usar algunos objetos…$"

Route34_Text_GinaRegister:
	.string "Eres demasiado fuerte para ser un\n"
	.string "compañero de práctica.$"

Route34_Text_PicnickerGina_Seen:
	.string "¿Eres un ENTRENADOR?\p"
	.string "Tengamos una batalla de práctica.$"

Route34_Text_PicnickerGina_Beaten:
	.string "Oh, no! I just can't win…$"

Route34_Text_PicnickerGina_After:
	.string "Eres demasiado fuerte para ser un\n"
	.string "compañero de práctica.$"

Route34_Text_OfficerKeith_Seen:
	.string "¿Quién anda ahí?\n"
	.string "¿Qué estás tramando?$"

Route34_Text_OfficerKeith_Win:
	.string "You're a tough little kid.$"

Route34_Text_OfficerKeith_After:
	.string "Sí, hoy todo está en orden.\p"
	.string "Pórtate bien y no busques problemas.$"

Route34_Text_OfficerKeith_Daytime:
	.string "Patrullo buscando personas\n"
	.string "sospechosas.$"

Route34_Text_PokefanBrandon_Seen:
	.string "Acabo de recuperar a mi POKéMON\n"
	.string "de la GUARDERÍA.\p"
	.string "¡Veamos cuánto se fortaleció!$"

Route34_Text_PokefanBrandon_Beaten:
	.string "Why does it end this way?$"

Route34_Text_PokefanBrandon_After:
	.string "Mi POKéMON volvió con nuevos\p"
	.string "movimientos. ¡Me dejó asombrado!$"

Route34_Text_Sign_IlexForest:
	.string "BOSQUE VERDE\n"
	.string "A TRAVÉS DE LA PUERTA$"

Route34_Text_Sign_Route34:
	.string "RUTA 34\n"
	.string "CDAD. TRIGAL - PUEBLO AZALEA\p"
	.string "BOSQUE VERDE, EN ALGÚN LUGAR$"

Route34_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Los árboles de BAYAS dan nuevas\n"
	.string "BAYAS varias veces al día.\p"
	.string "Anota qué árboles dan cuáles\n"
	.string "BAYAS.$"

Route34_Text_CooltrainerIrene_Seen:
	.string "IRENE: Who are you?!$"

Route34_Text_CooltrainerIrene_Beaten:
	.string "IRENE: Ohhh! You're too strong!$"

Route34_Text_CooltrainerIrene_After1:
	.string "IRENE: ¡Mi hermana KATE te hará\n"
	.string "pagar esto!$"

Route34_Text_CooltrainerIrene_After2:
	.string "IRENE: ¿No es genial esta playa?\p"
	.string "¡Es nuestro refugio secreto!$"

Route34_Text_CooltrainerJenn_Seen:
	.string "JENN: ¿Pero qué...?\n"
	.string "¿Qué estás haciendo?$"

Route34_Text_CooltrainerJenn_Beaten:
	.string "JENN: So sorry, IRENE! Dear Sis!$"

Route34_Text_CooltrainerJenn_After1:
	.string "JENN: ¡No te confíes! Mi hermana\n"
	.string "KATE es fuerte!$"

Route34_Text_CooltrainerJenn_After2:
	.string "JENN: El sol hace que tu cuerpo\n"
	.string "más fuerte.$"

Route34_Text_CooltrainerKate_Seen:
	.string "KATE: Debo agradecerte por\n"
	.string "¡cuidar de mis hermanas!$"

Route34_Text_CooltrainerKate_Beaten:
	.string "KATE: No! I can't believe I lost.$"

Route34_Text_CooltrainerKate_GiveSoftSand:
	.string "KATE: Eres muy fuerte.\n"
	.string "Perdimos sin excusas...\p"
	.string "¡Toma, ten esto!$"

Route34_Text_CooltrainerKate_After:
	.string "KATE: Siento que te emboscáramos.\p"
	.string "No esperábamos que alguien nos\n"
	.string "hallara aquí. Nos asustaste mucho.$"


Route34_Text_Sign_DayCare:
	.string "DAY-CARE\p"
	.string "LET US RAISE YOUR POKéMON FOR YOU!$"
