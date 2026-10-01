NewSinjoh_KimonoHideout_hns_MapScripts::
   map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_KimonoHideout_OnFrame
    .byte 0


NewSinjoh_KimonoHideout_OnFrame:
	map_script_2 VAR_SINJOH_STORYLINE, 4, NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos
	.2byte 0

@ ============INTRO CUTSCENE=====================================================================================

NewSinjoh_KimonoHideout_EventScript_PlayerMeetsKimonos::
	lock
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos, MSGBOX_AUTOCLOSE
	applymovement LOCALID_PLAYER, NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_MIHARU, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_MIHARU, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_SHIZUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_SHIZUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_YOUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksDown
	waitmovement 0
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	playse SE_M_PETAL_DANCE
	applymovement LOCALID_NEWSINJOH_KIMONOHIDEOUT_YOUKO, NewSinjoh_KimonoHideout_Movement_KimonoWalksUp
	waitmovement 0

	setvar VAR_SINJOH_STORYLINE, 5
	release
	end

NewSinjoh_KimonoHideout_Movement_PlayerWalksIntoRoom:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksDown:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_down
	step_end

NewSinjoh_KimonoHideout_Movement_KimonoWalksUp:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	walk_up
	face_down
	step_end

NewSinjoh_KimonoHideout_Text_PlayerMeetsKimonos:
	.string "{PLAYER}.\p"
	.string "Por favor, acércate.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu:
    .string "MIHARU: Bienvenido a NUEVA SINJOH, \n"
	.string "{PLAYER}.\p"
	.string "por generaciones, esta aldea ha\n"
	.string "convivido en paz con POKéMON\l"
	.string "inmensamente poderosos, aislados de\l"
	.string "las miradas de los forasteros.\p"
	.string "Sucesos recientes en nuestro templo\n"
	.string "y la llegada de invitados no\l"
	.string "deseados amenazan con romper el\l"
	.string "delicado equilibrio que hemos\l"
	.string "protegido.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko:
	.string "SHIZUKO: Nuestros primos en IRIS\n"
	.string "La CIUDAD nos informó sobre tu\l"
	.string "vínculo con el POKéMON LEGENDARIO\l"
	.string "de la REGIÓN JOHTO y tu\l"
	.string "destreza como ENTRENADOR.\p"
	.string "Creemos que puedes ayudarnos en\n"
	.string "estos tiempos difíciles.$"

NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko:
	.string "YOUKO: Ve a las RUINAS SINJOH, al\n"
	.string "norte de la RUTA 50.\p"
	.string "Reúnete con los científicos y\n"
	.string "estudia los eventos que causaron\l"
	.string "su presencia.\p"
	.string "Es imperativo que el LEGENDARIO\n"
	.string "Los POKéMON de aquí no son\l"
	.string "molestados por indignos.$"


@ ============KIMONO GIRL NPCs=====================================================================================

NewSinjoh_KimonoHideout_EventScript_Miharu::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_MiharuFinal
	goto_if_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_MiharuAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsMiharu, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryMiharuBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_MiharuBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuBattle::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 0, 2, 0
	trainerbattle_no_intro TRAINER_MIHARU_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_MEADOW_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_MiharuAfter::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_MiharuBeforeBattle:
	.string "MIHARU: Tal como predijimos.\p"
	.string "El campeón de piedra te envió\n"
	.string "a recolectar las PLATES.\p"
	.string "Nuestra orden ha guardado estas\n"
	.string "PLATES por siglos.\p"
	.string "No nos separaremos de ellas\n"
	.string "fácilmente.$"

NewSinjoh_KimonoHideout_Text_MiharuAfter:
	.string "MIHARU: Eres digno.$"

NewSinjoh_KimonoHideout_EventScript_MiharuFinal::
	msgbox NewSinjoh_KimonoHideout_Text_MiharuFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_MiharuFinal:
	.string "MIHARU: Hiciste un gran\n"
	.string "servicio al pueblo, {PLAYER}.\p"
	.string "No olvidaremos esto.$"

NewSinjoh_KimonoHideout_EventScript_Youko::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_YoukoFinal
	goto_if_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_YoukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsYouko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryYoukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_YoukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 1, 2, 2, 2
	trainerbattle_no_intro TRAINER_YOUKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_ICICLE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_YoukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_YoukoBeforeBattle:
	.string "YOUKO: Nuestros primos hablan\n"
	.string "muy bien de ti.\p"
	.string "¿Es verdad?\p"
	.string "Ya lo descubriré.$"

NewSinjoh_KimonoHideout_Text_YoukoAfter:
	.string "YOUKO: Nuestros primos tenían\n"
	.string "razón sobre ti.$"

NewSinjoh_KimonoHideout_EventScript_YoukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_YoukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_YoukoFinal:
	.string "YOUKO: Al principio dudaba.\p"
	.string "Pero tras lo que hiciste, no\n"
	.string "se puede negar.$"

NewSinjoh_KimonoHideout_EventScript_Shizuko::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 13, NewSinjoh_KimonoHideout_EventScript_ShizukoFinal
	goto_if_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_ShizukoAfter
	msgbox NewSinjoh_KimonoHideout_Text_PlayerMeetsShizuko, MSGBOX_AUTOCLOSE
	goto_if_not_defeated TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_TryShizukoBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_KimonoHideout_EventScript_ShizukoBattle
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoBattle::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle, MSGBOX_DEFAULT
	closemessage
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 1, 0, 0, 1, 0
	trainerbattle_no_intro TRAINER_SHIZUKO_HNS, EcruteakCity_Theater_Text_KimonoGirlBeaten
	giveitem ITEM_PIXIE_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_KimonoHideout_EventScript_ShizukoAfter::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoAfter, MSGBOX_AUTOCLOSE
	release
	end

NewSinjoh_KimonoHideout_Text_ShizukoBeforeBattle:
	.string "SHIZUKO: Entrenamos para la\n"
	.string "batalla y para el baile.\p"
	.string "Obtener las PLACAS\n"
	.string "requiere fuerza y determinación.$"

NewSinjoh_KimonoHideout_Text_ShizukoAfter:
	.string "SHIZUKO: El vínculo que tienes\n"
	.string "con tu POKéMON es muy fuerte.\p"
	.string "Te ganaste esta PLACA.$"

NewSinjoh_KimonoHideout_EventScript_ShizukoFinal::
	msgbox NewSinjoh_KimonoHideout_Text_ShizukoFinal, MSGBOX_AUTOCLOSE
	end

NewSinjoh_KimonoHideout_Text_ShizukoFinal:
	.string "SHIZUKO: Pocos entrenadores en\n"
	.string "la historia de SINJOH han\l"
	.string "logrado lo que acabas de hacer.\p"
	.string "Impresionante, {PLAYER}.$"

@ =================================================================================================

NewSinjoh_KimonoHideout_EventScript_OldMan::
	msgbox NewSinjoh_KimonoHideout_Text_OldMan, MSGBOX_NPC
	end

NewSinjoh_KimonoHideout_Text_OldMan:
    .string "Las KIMONO GIRLS cuidan\n"
	.string "el pueblo desde su fundación.\p"
	.string "Han sacrificado mucho.\p"
	.string "Bendecidos por los mismos dioses,\n"
	.string "tienen poderes que superan a\l"
	.string "cualquier ENTRENADOR normal!\p"
	.string "Así que prepárate bien\n"
	.string "si llegas a luchar con ellos.$"

NewSinjoh_KimonoHideout_Text_OldManAfter:
    .string "Venciste a los campeones de\n"
	.string "nuestra aldea.\p"
	.string "¿Qué significa eso, jovencito?$"
