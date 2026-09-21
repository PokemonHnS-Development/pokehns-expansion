SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_OCEANIC_MUSEUM_2F_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_OCEANIC_MUSEUM_2F_ARCHIE
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_1
	removeobject LOCALID_OCEANIC_MUSEUM_2F_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_PARTS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	removeobject LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_OCEANIC_MUSEUM_2F_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "¿Sí? Si buscas a STERN,\n"
	.string "ese soy yo.\p"
	.string "¡Ah! Deben ser las piezas que pedí\n"
	.string "al SR. STONE de DEVON.\p"
	.string "¡Gracias! ¡Genial!\n"
	.string "Ya podemos preparar la expedición.$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "Jejeje, ¡esperen!\n"
	.string "¡Nos llevaremos esas piezas!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "CAPT. STERN: ¿Qu-qué?\n"
	.string "¿Quiénes son ustedes?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "¡Nosotros somos el TEAM AQUA!\p"
	.string "¡Nuestro JEFE quiere esas piezas!\n"
	.string "¡Cierra la boca y dánoslas!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "¡Awaaaah!\n"
	.string "¡Un niño me venció!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Ay, qué desastre…\nEl JEFE va a estar furioso…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "¡Bah, llorón cobarde!\n¡Déjame encargarme de esto!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "¡¿Qué?!\n"
	.string "¡Yo también perdí!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "¿Y ahora? Si no nos dan las piezas,\n¡estamos en apuros!\pArrgh, no contaba con que un\nniño entrometido se metiera!$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "Vine a ver qué estaba tardando\n"
	.string "tardamos en robar las piezas, ¿y\l"
	.string "ustedes caen ante un niño?$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "¡Somos el EQUIPO AQUA\n"
	.string "y amamos el mar!\p"
	.string "Y yo soy el líder del EQUIPO AQUA,\n"
	.string "¡ARCHIE!\p"
	.string "¿Por qué interfieres con nosotros?\p"
	.string "…¡No! ¡No puede ser!\n"
	.string "¿No eres del EQUIPO MAGMA?\p"
	.string "Espera, eso no puede estar bien.\n"
	.string "No vistes como uno de ellos.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "POKéMON, personas… Toda la vida\n"
	.string "del mar.\p"
	.string "Así que, el TEAM AQUA se dedica a\n"
	.string "la expansión del mar.\p"
	.string "¿No estás de acuerdo? Lo que hacemos\n"
	.string "es una empresa magnífica.\p"
	.string "Ah, está bien...\n"
	.string "Aún eres muy joven para entender\l"
	.string "nuestro noble objetivo.\p"
	.string "Pero te advierto, ni consideres\n"
	.string "estorbar nuestros planes otra vez.\p"
	.string "¡Las consecuencias te costarán\n"
	.string "muy caro!\p"
	.string "¡Y no lo olvides!$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "CAPITÁN STERN: Tú eres...\n"
	.string "Ah, ya veo, eres {PLAYER}{KUN}...\p"
	.string "¡En fin, fue una situación tensa!\n"
	.string "¡Gracias por salvarnos!\p"
	.string "Oh, sí, casi olvido que incluso\n"
	.string "trajiste las piezas de DEVON!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "CAPITÁN STERN: ¡Vaya!\n"
	.string "¡No hay tiempo que perder!\p"
	.string "Debemos partir pronto en nuestra\n"
	.string "expedición al fondo del mar.\p"
	.string "Gracias de nuevo, pero ahora debo\n"
	.string "to go!\p"
	.string "Siéntete libre de explorar y ver\n"
	.string "pero recorran las instalaciones.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "Vi una maqueta de un barco aquí.\p"
	.string "Me recordó al BARCO ABANDONADO\n"
	.string "cerca de PUEBLO AGUA…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "¡No te atrevas a correr dentro\n"
	.string "del MUSEO!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "¡Guau, el submarino es genial!\n"
	.string "¡Quiero dar un paseo!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "“MUESTRA DE AGUA 1”, dice la\n"
	.string "etiqueta.\p"
	.string "El mar está conectado, pero el\n"
	.string "agua varía según la región.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "“MUESTRA DE AGUA 2”, el\n"
	.string "etiqueta.\p"
	.string "¿La salinidad del mar varía\n"
	.string "según la región también?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "Una pelota de goma se expande y\n"
	.string "se encoge.\p"
	.string "“En el mar, el peso del agua\n"
	.string "ejerce presión.\p"
	.string "“En aguas poco profundas, la\n"
	.string "presión no es muy fuerte.\p"
	.string "“Pero en aguas muy profundas,\n"
	.string "la presión puede llegar a miles\l"
	.string "de toneladas en un área pequeña.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“MAQUETA DE LA REGIÓN DE HOENN”\p"
	.string "Es un diorama en miniatura de la\n"
	.string "región de HOENN.\p"
	.string "¿Dónde está PUEBLO RAÍZ aquí?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "Muestra el flujo del agua marina.\p"
	.string "“Cerca del fondo marino, el agua\n"
	.string "fluye por diferencias en factores\l"
	.string "como temperatura y salinidad.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "Muestra el flujo del agua marina.\p"
	.string "“Hacia la superficie, el agua fluye\n"
	.string "como corrientes que lleva el viento.$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "“EL FERRY S.S. TIDAL\p"
	.string "“Una réplica a escala del barco\n"
	.string "construcción en ASTILLERO STERN.”$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "“EXPLORADOR SUBMARINO 1\p“Réplica del submarino de exploración\nmarina de alto rendimiento.”$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "“CÁPSULA SUMERGIBLE\p"
	.string "“Réplica de una cápsula compacta\n"
	.string "y no tripulada para el fondo marino.”$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "“S.S. ANNE\p“Réplica del transatlántico de lujo\nque da la vuelta al mundo.”$"
