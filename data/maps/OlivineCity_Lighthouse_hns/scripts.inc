OlivineCity_Lighthouse_hns_MapScripts::
	.byte 0

OlivineLighthouse_EventScript_Item_Ether::
    finditem ITEM_ETHER
    end

OlivineLighthouse_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

OlivineLighthouse_EventScript_Item_TMSwagger::
    finditem ITEM_TM_SWAGGER
    end

OlivineLighthouse_EventScript_Item_HyperPotion::
    finditem ITEM_HYPER_POTION
    end

OlivineLighthouse_EventScript_Item_Protein::
    finditem ITEM_PROTEIN
    end

OlivineLighthouse_EventScript_1FSailor::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FSailor, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_EventScript_1FPokefanF::
	lock
	faceplayer
	msgbox OlivineLighthouse_Text_1FPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_1FSailor:
	.string "Entrenan en este FARO.\p"
	.string "No es fácil subir con todos\n"
	.string "los entrenadores que esperan.$"

OlivineLighthouse_Text_1FPokefanF:
	.string "Antes, los POKéMON iluminaban\n"
	.string "el mar de CIUDAD OLIVO de noche.\p"
	.string "El FARO se construyó en honor\n"
	.string "a esos nobles POKéMON.$"

@2nd floor==============================================================================================================================

OlivineLighthouse_EventScript_Huey::
	trainerbattle_single TRAINER_HUEY_HNS, OlivineLighthouse_Text_SailorHueySeen, OlivineLighthouse_Text_SailorHueyBeaten, OlivineLighthouse_EventScript_RegisterHuey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, OlivineLighthouse_EventScript_RematchHuey
	msgbox OlivineLighthouse_Text_SailorHueyAfter, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_RegisterHuey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox OlivineLighthouse_Text_HueyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_HUEY_HNS
	release
	end

OlivineLighthouse_EventScript_RematchHuey::
	trainerbattle_rematch TRAINER_HUEY_HNS, OlivineLighthouse_Text_HueyRematchIntro, OlivineLighthouse_Text_HueyRematchDefeat
	msgbox OlivineLighthouse_Text_HueyPostRematch, MSGBOX_AUTOCLOSE
	end

OlivineLighthouse_EventScript_GentlemanAlfred::
    trainerbattle_single TRAINER_ALFRED_HNS, OlivineLighthouse_Text_GentlemanAlfredSeen, OlivineLighthouse_Text_GentlemanAlfredBeaten
    msgbox OlivineLighthouse_Text_GentlemanAlfredAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorHueySeen:
	.string "¡Los hombres de mar siempre\n"
	.string "buscan una buena pelea!$"

OlivineLighthouse_Text_SailorHueyBeaten:
	.string "¡Urf!\n"
	.string "¡Perdí!$"

OlivineLighthouse_Text_SailorHueyAfter:
	.string "¡Qué poder! ¿Qué te parece\n"
	.string "¿navegar los mares conmigo?$"

OlivineLighthouse_Text_HueyRegister:
	.string "¡Qué poder! ¿Qué te parece\n"
	.string "¿navegar los mares conmigo?$"

OlivineLighthouse_Text_HueyRematchIntro:
	.string "¡Los hombres de mar siempre\n"
	.string "buscan una buena pelea!$"

OlivineLighthouse_Text_HueyRematchDefeat:
	.string "¡Urf!\n"
	.string "¡Perdí!$"

OlivineLighthouse_Text_HueyPostRematch:
	.string "¡Qué poder! ¿Qué te parece\n"
	.string "¿navegar los mares conmigo?$"

OlivineLighthouse_Text_GentlemanAlfredSeen:
	.string "¿Hm? Este no es lugar\n"
	.string "para jugar.$"

OlivineLighthouse_Text_GentlemanAlfredBeaten:
	.string "¡Ah! Veo que hablas\n"
	.string "en serio.$"

OlivineLighthouse_Text_GentlemanAlfredAfter:
	.string "Arriba hay un POKéMON que mantiene\n"
	.string "el FARO encendido.\p"
	.string "Pero oí que ahora está enfermo\n"
	.string "y no se puede curar normalmente.$"

@3rd floor==============================================================================================================================

OlivineLighthouse_EventScript_BirdKeeperTheo::
    trainerbattle_single TRAINER_THEO_HNS, OlivineLighthouse_Text_BirdKeeperTheoSeen, OlivineLighthouse_Text_BirdKeeperTheoBeaten
    msgbox OlivineLighthouse_Text_BirdKeeperTheoAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_SailorTerrell::
    trainerbattle_single TRAINER_TERRELL_HNS, OlivineLighthouse_Text_SailorTerrellSeen, OlivineLighthouse_Text_SailorTerrellBeaten
    msgbox OlivineLighthouse_Text_SailorTerrellAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_GentlemanPreston::
    trainerbattle_single TRAINER_PRESTON_HNS, OlivineLighthouse_Text_GentlemanPrestonSeen, OlivineLighthouse_Text_GentlemanPrestonBeaten
    msgbox OlivineLighthouse_Text_GentlemanPrestonAfter, MSGBOX_AUTOCLOSE
    end


OlivineLighthouse_Text_BirdKeeperTheoSeen:
	.string "¿Por qué estás aquí? ¿Solo vienes\n"
	.string "a mirar? ¡Sugiero que te vayas!$"

OlivineLighthouse_Text_BirdKeeperTheoBeaten:
	.string "Realmente te preocupa\n"
	.string "el POKéMON enfermo…$"

OlivineLighthouse_Text_BirdKeeperTheoAfter:
	.string "¿Cómo rayos se sube?\p"
	.string "Quiero visitar al POKéMON enfermo,\n"
	.string "pero no puedo subir ahí…$"

OlivineLighthouse_Text_SailorTerrellSeen:
	.string "Los marinos son amables y fuertes.\n"
	.string "¿Y tú qué tal?$"

OlivineLighthouse_Text_SailorTerrellBeaten:
	.string "Eres a la vez amable y fuerte…$"

OlivineLighthouse_Text_SailorTerrellAfter:
	.string "Cada vez que vuelvo a CIUDAD OLIVO,\n"
	.string "visito el GIMNASIO.\p"
	.string "El tipo del POKéMON del LÍDER\n"
	.string "cambió sin que me diera cuenta.$"

OlivineLighthouse_Text_GentlemanPrestonSeen:
	.string "Viajo por el mundo para entrenar mi\n"
	.string "POKéMON. Quiero luchar contigo.$"

OlivineLighthouse_Text_GentlemanPrestonBeaten:
	.string "…sigh… I must train some more…$"

OlivineLighthouse_Text_GentlemanPrestonAfter:
	.string "JASMINE solía usar POKéMON\n"
	.string "de tipo ROCA como ONIX.$"

@4th floor==============================================================================================================================

OlivineLighthouse_EventScript_SailorKent::
    trainerbattle_single TRAINER_KENT_HNS, OlivineLighthouse_Text_SailorKentSeen, OlivineLighthouse_Text_SailorKentBeaten
    msgbox OlivineLighthouse_Text_SailorKentAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_LassConnie::
    trainerbattle_single TRAINER_CONNIE_HNS, OlivineLighthouse_Text_LassConnieSeen, OlivineLighthouse_Text_LassConnieBeaten
    msgbox OlivineLighthouse_Text_LassConnieAfter, MSGBOX_AUTOCLOSE
    end


OlivineLighthouse_Text_SailorKentSeen:
	.string "JASMINE debe estar muy preocupada\n"
	.string "por los POKéMON de aquí.\p"
	.string "Ya ni siquiera sonríe hoy en día.$"

OlivineLighthouse_Text_SailorKentBeaten:
	.string "I can't manage a smile either…$"

OlivineLighthouse_Text_SailorKentAfter:
	.string "Hablando de salud, oí que hay\n"
	.string "una FARMACIA en CIUDAD ORQUIDEA.$"

OlivineLighthouse_Text_LassConnieSeen:
	.string "JASMINE es la LÍDER del GIMNASIO.\p"
	.string "Pienso traerla de vuelta conmigo.\p"
	.string "¡Que nadie se interponga en mi camino!$"

OlivineLighthouse_Text_LassConnieBeaten:
	.string "Aaack! My POKéMON!$"

OlivineLighthouse_Text_LassConnieAfter:
	.string "Cierto. Cualquiera estaría preocupado\n"
	.string "si sus propios POKéMON estuvieran mal.\p"
	.string "Rezaré por los POKéMON de aquí, para\n"
	.string "que JASMINE vuelva al GIMNASIO.$"

@5th floor==============================================================================================================================

OlivineLighthouse_EventScript_SailorErnest::
    trainerbattle_single TRAINER_ERNEST_HNS, OlivineLighthouse_Text_SailorErnestSeen, OlivineLighthouse_Text_SailorErnestBeaten
    msgbox OlivineLighthouse_Text_SailorErnestAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_EventScript_BirdKeeperDenis::
    trainerbattle_single TRAINER_DENIS_HNS, OlivineLighthouse_Text_BirdKeeperDenisSeen, OlivineLighthouse_Text_BirdKeeperDenisBeaten
    msgbox OlivineLighthouse_Text_BirdKeeperDenisAfter, MSGBOX_AUTOCLOSE
    end

OlivineLighthouse_Text_SailorErnestSeen:
	.string "Quería luchar contra JASMINE, pero\n"
	.string "ahora no puede hacerlo.\p"
	.string "Entonces, ¿qué tal tú?$"

OlivineLighthouse_Text_SailorErnestBeaten:
	.string "Whoa, whoa. You're overwhelming!$"

OlivineLighthouse_Text_SailorErnestAfter:
	.string "Ser LÍDER de GIMNASIO no es solo\n"
	.string "increíblemente fuertes.\p"
	.string "ser fuerte, un LÍDER también debe\n"
	.string "compasivo.$"

OlivineLighthouse_Text_BirdKeeperDenisSeen:
	.string "Estamos muy alto aquí. Mis POKéMON\n"
	.string "están en su mejor forma.$"

OlivineLighthouse_Text_BirdKeeperDenisBeaten:
	.string "Oops… They crashed…$"

OlivineLighthouse_Text_BirdKeeperDenisAfter:
	.string "Mi POKéMON aprendió a usar VUELO en\n"
	.string "CIUDAD ORQUIDEA.\p"
	.string "Bueno, como perdí, usaré VUELO\n"
	.string "sobre el mar…$"

@6th floor==============================================================================================================================

OlivineLighthouse_EventScript_Jasmine::
	lock
	faceplayer
	goto_if_eq VAR_OLIVINE_CITY_STATE, 3, OlivineLighthouse_EventScript_JasmineGoGetPotion
	goto_if_eq VAR_OLIVINE_CITY_STATE, 4, OlivineLighthouse_EventScript_JasmineDeliverPotion
	msgbox OlivineLighthouse_Text_JasmineCianwoodPharmacy, MSGBOX_DEFAULT
	msgbox OlivineLighthouse_Text_JasmineGetMedicine, MSGBOX_DEFAULT
	closemessage
	setvar VAR_OLIVINE_CITY_STATE, 3
	release
	end
OlivineLighthouse_EventScript_JasmineGoGetPotion::
	msgbox OlivineLighthouse_Text_JasmineGetMedicine2, MSGBOX_DEFAULT
	release
	end


OlivineLighthouse_EventScript_Ampharos::
	lock
	faceplayer
	goto_if_lt VAR_OLIVINE_CITY_STATE, 5, OlivineLighthouse_EventScript_AmpharosSick
	fadescreen FADE_TO_WHITE
	playse SE_M_THUNDERBOLT2
	waitse
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_DEFAULT
	waitmoncry
	setflag FLAG_AMPHAROS_HEALED
	release
	end

OlivineLighthouse_EventScript_AmpharosSick::
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox OlivineLighthouse_Text_AmphyPalPaloo, MSGBOX_DEFAULT
	waitmoncry
	msgbox OlivineLighthouse_Text_AmphyBreathingLabored, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_JasmineCianwoodPharmacy:
	.string "JASMINE: …Este POKéMON siempre\n"
	.string "iluminaba el mar de noche.\p"
	.string "…Pero enfermó de repente… No\n"
	.string "puede respirar…\p"
	.string "…Tengo entendido que hay un\n"
	.string "wonderful PHARMACY in CIANWOOD…\p"
	.string "Pero eso es cruzando el mar...\n"
	.string "Y no puedo dejar a AMPHY solo...$"

OlivineLighthouse_Text_JasmineGetMedicine:
	.string "...¿Podrías traerme algo de\n"
	.string "medicina? ¡Por favor!$"

OlivineLighthouse_Text_JasmineGetMedicine2:
	.string "Hay una maravillosa FARMACIA\n"
	.string "en CIUDAD ORQUIDEA...\p"
	.string "Pero eso es cruzando el mar...\n"
	.string "Y no puedo dejar a AMPHY solo...\p"
	.string "...¿Podrías traerme algo de\n"
	.string "medicina? ¡Por favor!$"

OlivineLighthouse_Text_JasmineCureAmphy:
	.string "JASMINE: ...¿Esa medicina\n"
	.string "curará a AMPHY?$"


OlivineLighthouse_EventScript_JasmineDeliverPotion::
	msgbox OlivineLighthouse_Text_JasmineCureAmphy, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, OlivineLighthouse_EventScript_JasmineRefuse
	playse SE_USE_ITEM
	removeitem ITEM_SECRET_POTION
	msgbox OlivineLighthouse_Text_PlayerHandedSecretpotion, MSGBOX_DEFAULT
	waitse
	msgbox OlivineLighthouse_Text_JasmineDontBeOffended, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_LIGHTHOUSE_JASMINE, DIR_NORTH
	delay 20
	turnobject LOCALID_LIGHTHOUSE_AMPHAROS, DIR_SOUTH
	playfanfare MUS_HEAL
	waitfanfare
	msgbox OlivineLighthouse_Text_JasmineAmphyHowFeeling, MSGBOX_DEFAULT
	fadescreen FADE_TO_WHITE
	playse SE_M_THUNDERBOLT2
	waitse
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_AMPHAROS, CRY_MODE_NORMAL
	msgbox OlivineLighthouse_Text_AmphyPaluPalulu, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_LIGHTHOUSE_AMPHAROS, OlivineLighthouse_Movement_Amphy
	waitmovement 0
	applymovement LOCALID_LIGHTHOUSE_JASMINE, OlivineLighthouse_Movement_Jasmine
	msgbox OlivineLighthouse_Text_JasmineThankYou, MSGBOX_DEFAULT
	closemessage

	fadescreen FADE_TO_BLACK
	playse SE_EXIT
	setflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	removeobject LOCALID_LIGHTHOUSE_JASMINE
	waitse
	delay 50
	fadescreen FADE_FROM_BLACK
	setvar VAR_SAFARI_ZONE_GATE_STATE, 1
	setvar VAR_OLIVINE_CITY_STATE, 5
	setflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
	release
	end

OlivineLighthouse_Movement_Jasmine:
	face_player
	step_end

OlivineLighthouse_Movement_Amphy:
	walk_up
	jump_in_place_down
	jump_in_place_left
	jump_in_place_right
	jump_in_place_up
	face_down
	step_end


OlivineLighthouse_EventScript_JasmineRefuse::
	msgbox OlivineLighthouse_Text_JasmineISee, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineLighthouse_Text_PlayerHandedSecretpotion:
	.string "{PLAYER} le dio la POCIÓN SECRETA\n"
	.string "a JASMINE.$"

OlivineLighthouse_Text_JasmineDontBeOffended:
	.string "JASMINE: ...Um, por favor, no te\n"
	.string "ofendas...\p"
	.string "...AMPHY no aceptará nada de\n"
	.string "nadie más que de mí...$"

OlivineLighthouse_Text_JasmineAmphyHowFeeling:
	.string "JASMINE: ...\p"
	.string "AMPHY, ¿cómo te sientes?$"

OlivineLighthouse_Text_JasmineThankYou:
	.string "JASMINE: ...Oh, qué alivio...\p"
	.string "Esto es simplemente maravilloso...\p"
	.string "Muchísimas gracias, de verdad.\p"
	.string "...Volveré al GIMNASIO...\p"
	.string "También te advierto, los tipo\n"
	.string "ACERO son poderosos.$"

OlivineLighthouse_Text_JasmineISee:
	.string "JASMINE: ...Ya veo...\n"
	.string "...¡AMPHY, resiste!$"

OlivineLighthouse_Text_AmphyPalPaloo:
	.string "AMPHY: ...\n"
	.string "...Pa... paloo...$"

OlivineLighthouse_Text_AmphyBreathingLabored:
	.string "Su respiración es muy\n"
	.string "pesada...$"

OlivineLighthouse_Text_AmphyPaluPalulu:
	.string "AMPHY: Palu! Palulu!$"


