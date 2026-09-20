BattleFrontier_Lounge1_hns_MapScripts::
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder_hns::
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_Breeder_hnsIntro_hns
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder_hns
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder_hns
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder_hns::
	chooseboxmon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_ShowMonToBreeder_hns
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_CancelMonSelect_hns
	end

BattleFrontier_Lounge1_EventScript_Breeder_hnsIntro_hns::
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro_hns, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder_hns::
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon_hns, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8005: Sum of the mons IVs
@ VAR_0x8006: Stat id of highest IV stat
@ VAR_0x8007: IV of the highest IV stat
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder_hns::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge1_EventScript_ShowEggToBreeder_hns
	special BufferVarsForIVRater
	goto_if_le VAR_0x8005, 90, BattleFrontier_Lounge1_EventScript_AverageTotalIVs_hns       @ Average of 15
	goto_if_le VAR_0x8005, 120, BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs_hns @ Average of 20
	goto_if_le VAR_0x8005, 150, BattleFrontier_Lounge1_EventScript_HighTotalIVs_hns         @ Average of 25
	goto_if_ge VAR_0x8005, 151, BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs_hns     @ Average of > 25
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder_hns::
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder_hns
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat_hns::
	goto_if_eq VAR_0x8006, STAT_HP, BattleFrontier_Lounge1_EventScript_HighestIVHP_hns
	goto_if_eq VAR_0x8006, STAT_ATK, BattleFrontier_Lounge1_EventScript_HighestIVAtk_hns
	goto_if_eq VAR_0x8006, STAT_DEF, BattleFrontier_Lounge1_EventScript_HighestIVDef_hns
	goto_if_eq VAR_0x8006, STAT_SPEED, BattleFrontier_Lounge1_EventScript_HighestIVSpeed_hns
	goto_if_eq VAR_0x8006, STAT_SPATK, BattleFrontier_Lounge1_EventScript_HighestIVSpAtk_hns
	goto_if_eq VAR_0x8006, STAT_SPDEF, BattleFrontier_Lounge1_EventScript_HighestIVSpDef_hns
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue_hns::
	goto_if_le VAR_0x8007, 15, BattleFrontier_Lounge1_EventScript_HighestIVLow_hns
	goto_if_le VAR_0x8007, 25, BattleFrontier_Lounge1_EventScript_HighestIVMid_hns
	goto_if_le VAR_0x8007, 30, BattleFrontier_Lounge1_EventScript_HighestIVHigh_hns
	goto_if_ge VAR_0x8007, 31, BattleFrontier_Lounge1_EventScript_HighestIVMax_hns
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments_hns::
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs_hns::
	msgbox BattleFrontier_Lounge1_Text_AverageAbility_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat_hns
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs_hns::
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat_hns
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs_hns::
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat_hns
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs_hns::
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP_hns::
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk_hns::
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef_hns::
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed_hns::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk_hns::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef_hns::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow_hns::
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid_hns::
	msgbox BattleFrontier_Lounge1_Text_StatImpressive_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh_hns::
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments_hns
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax_hns::
	msgbox BattleFrontier_Lounge1_Text_StatFlawless_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments_hns
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect_hns::
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1_hns::
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2_hns::
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro_hns:
	.string "¡Llevo 70 años criando POKéMON!\n"
	.string "Soy el hombre a quien veneran como\l"
	.string "¡el legendario CRIADOR POKéMON!\p"
	.string "Si llegas a tener mi experiencia,\n"
	.string "verás las habilidades de los POKéMON\l"
	.string "con solo mirarlos.\p"
	.string "Eres ENTRENADOR. ¿No te interesa\n"
	.string "conocer las habilidades de tus\l"
	.string "propios POKéMON?\p"
	.string "¡Toma!\n"
	.string "¡Echemos un vistazo a tu POKéMON!$"

BattleFrontier_Lounge1_Text_AverageAbility_hns:
	.string "...Hmm...\p"
	.string "A este, en general, lo describiría\n"
	.string "con una habilidad promedio.$"

BattleFrontier_Lounge1_Text_BetterThanAverageAbility_hns:
	.string "...Hmm...\p"
	.string "En general, describiría a este\n"
	.string "como alguien con gran habilidad.$"

BattleFrontier_Lounge1_Text_ImpressiveAbility_hns:
	.string "...Hmm...\p"
	.string "En general, diría que este es\n"
	.string "¡muy impresionante en habilidad!$"

BattleFrontier_Lounge1_Text_OutstandingAbility_hns:
	.string "...Hmm...\p"
	.string "En general, diría que este es\n"
	.string "¡maravilloso y excepcional!$"

BattleFrontier_Lounge1_Text_BestAspectHP_hns:
	.string "Por cierto, su mejor aspecto,\n"
	.string "diría que son sus PS…$"

BattleFrontier_Lounge1_Text_BestAspectAtk_hns:
	.string "Por cierto, su mejor aspecto,\n"
	.string "diría que es su ATAQUE…$"

BattleFrontier_Lounge1_Text_BestAspectDef_hns:
	.string "Por cierto, su mejor aspecto,\n"
	.string "diría que es su DEFENSA…$"

BattleFrontier_Lounge1_Text_BestAspectSpAtk_hns:
	.string "Por cierto, su mejor aspecto,\n"
	.string "diría que es su ATQ. ESPECIAL…$"

BattleFrontier_Lounge1_Text_BestAspectSpDef_hns:
	.string "Por cierto, su mejor aspecto,\n"
	.string "diría que es su DEF. ESPECIAL…$"

BattleFrontier_Lounge1_Text_BestAspectSpeed_hns:
	.string "Por cierto, su mejor aspecto,\n"
	.string "Diría que es su VELOCIDAD…$"

BattleFrontier_Lounge1_Text_StatRelativelyGood_hns:
	.string "Esa estadística es bastante buena.\n"
	.string "…Hm… Así es como lo llamo.$"

BattleFrontier_Lounge1_Text_StatImpressive_hns:
	.string "Esa estadística es impresionante.\n"
	.string "…Hm… Así es como lo llamo.$"

BattleFrontier_Lounge1_Text_StatOutstanding_hns:
	.string "¡Esa estadística es sobresaliente!\n"
	.string "…Hm… Así es como lo llamo.$"

BattleFrontier_Lounge1_Text_StatFlawless_hns:
	.string "¡Es impecable! ¡Es perfección!\n"
	.string "…Hm… Así es como lo llamo.$"

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice_hns:
	.string "¿Qué?\n"
	.string "¿No tienes tiempo para mis consejos?\p"
	.string "¡Siempre debes tener ganas de aprender\n"
	.string "de la experiencia de tus mayores!$"

@ Unused
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending_hns:
	.string "Sí, ¿qué pasa ahora?\p"
	.string "¡Tengo asuntos que atender!\n"
	.string "¡Guárdalo para la próxima vez!$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon_hns:
	.string "¡Ah, joven! ¿Te intrigan las\n"
	.string "habilidades de tus POKéMON?\p"
	.string "¡Ven, ven!\n"
	.string "¡Echemos un vistazo a tu POKéMON!$"

BattleFrontier_Lounge1_Text_EvenICantTell_hns:
	.string "Soy un experto, ¡pero ni yo puedo\n"
	.string "saber nada de un POKéMON sin nacer!\p"
	.string "¡Muéstrame un POKéMON!\n"
	.string "¡Necesito ver un POKéMON!$"

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding_hns:
	.string "¡Dijo que mi POKéMON es increíble!\n"
	.string "¡Qué bien que lo crié con cuidado!$"

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt_hns:
	.string "¡Dijo que mi POKéMON es increíble!\n"
	.string "Pero no hice nada especial\l"
	.string "al criarlo...$"

