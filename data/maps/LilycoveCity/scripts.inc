LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_LILYCOVE_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "MAY: ¡Ah, hola!\n"
	.string "{PLAYER}{KUN}, ¿tú también compras?\p"
	.string "Compré un montón de MUÑECOS y\n"
	.string "PÓSTERS.\p"
	.string "Claro, también he capturado muchos\n"
	.string "POKéMON, y los estoy criando\l"
	.string "como es debido.\p"
	.string "En realidad, me preocupa si tú\n"
	.string "los crías bien, {PLAYER}{KUN}.\p"
	.string "Lucharé contigo para que me\n"
	.string "muestres tus POKéMON, {PLAYER}{KUN}.$"

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "MAY: ¿Ah, por qué? {PLAYER}{KUN}, ¿no...?\n"
	.string "¿Has estado criando tus POKéMON?\p"
	.string "No es una muy buena muestra como\n"
	.string "ENTRENADOR…$"

LilycoveCity_Text_MayBattleMe:
	.string "MAY: ¡Vamos, lucha conmigo para que\n"
	.string "vea tus POKéMON!$"

LilycoveCity_Text_MayWontBeBeaten:
	.string "MAY: ¡Los POKéMON que crié no serán\n"
	.string "vencidos por los tuyos, {PLAYER}{KUN}!$"

LilycoveCity_Text_MayDefeat:
	.string "… … … … … … … …\p"
	.string "Recuerdo la batalla que tuve contigo,\n"
	.string "{PLAYER}{KUN}, en la RUTA 103.\p"
	.string "Esa batalla te ayudó a ser así de\n"
	.string "fuerte, {PLAYER}{KUN}, ¿verdad?$"

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "MAY: Estoy pensando en volver a\n"
	.string "Pronto iré a LITTLEROOT.\p"
	.string "He atrapado un buen grupo de POKéMON,\n"
	.string "y mi POKéDEX va avanzando, así que\l"
	.string "Iré a casa a mostrárselo a mi papá.$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "{PLAYER}{KUN}, ¿qué piensas hacer tú?\p"
	.string "¿Reunir todas las MEDALLAS de GYM y\n"
	.string "desafiar a la LIGA POKéMON?\p"
	.string "Bueno, mientras buscas MEDALLAS,\n"
	.string "{PLAYER}{KUN}, yo trabajaré en mi\l"
	.string "POKéDEX. ¡La completaré antes que tú!\p"
	.string "¡Nos vemos!$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "{PLAYER}{KUN}, ¿qué piensas hacer tú?\p"
	.string "¿Vas a desafiar a la LIGA POKéMON?\n"
	.string "cuestionario?\p"
	.string "O, ¿vas a completar tu\n"
	.string "POKéDEX?\p"
	.string "Puede que te ganara en combate,\n"
	.string "¡pero terminaré mi POKéDEX antes!\p"
	.string "¡Nos vemos!$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "{PLAYER}{KUN}, ¿qué piensas hacer tú?\p"
	.string "¿Vas a ir a la BATTLE FRONTIER?\n"
	.string "cuestionario?\p"
	.string "O, ¿vas a completar tu\n"
	.string "POKéDEX?\p"
	.string "Puede que te ganara en combate,\n"
	.string "¡pero terminaré mi POKéDEX antes!\p"
	.string "¡Nos vemos!$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "BRENDAN: Oh, hola, es {PLAYER}.\p"
	.string "Hago un recado para mi papá.\n"
	.string "No, no voy a comprar MUÑECAS.\p"
	.string "En fin, ha pasado tiempo.\p"
	.string "¿Quieres luchar para ver quién ha\n"
	.string "criado mejor a sus POKéMON?$"

LilycoveCity_Text_BrendanNoConfidence:
	.string "BRENDAN: Oh, ¿qué sucede?\n"
	.string "¿No tienes confianza?$"

LilycoveCity_Text_BrendanBattleMe:
	.string "BRENDAN: ¿Quieres luchar para ver\n"
	.string "quién crió mejor a sus POKéMON?$"

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "BRENDAN: Ay, pero sabes que no\n"
	.string "perderé contra {PLAYER}.$"

LilycoveCity_Text_BrendanDefeat:
	.string "Humph...\n"
	.string "Has criado mucho a tus POKéMON.\p"
	.string "Eso duele... yo empecé antes que\n"
	.string "tú como ENTRENADOR...$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "BRENDAN: Yo...\n"
	.string "Pienso volver a PUEBLO RAÍZ.\p"
	.string "Sabes que ayudo a mi papá con su\n"
	.string "La POKéDEX. Está quedando bastante\l"
	.string "bien, así que iré a mostrársela.$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "{PLAYER}, ¿qué piensas hacer?\p"
	.string "¿Reunir todas las MEDALLAS de GYM y\n"
	.string "desafiar a la LIGA POKéMON?\p"
	.string "Tal vez yo haga lo mismo...\p"
	.string "Bueno, en fin, ¡ánimo!$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "{PLAYER}, ¿qué piensas hacer?\p"
	.string "Ya que eres tan fuerte, ¿vas a\n"
	.string "ir a la LIGA POKéMON?\p"
	.string "Je, incluso yo, si entrenara más a\n"
	.string "mis POKéMON, sería más fuerte que\l"
	.string "tú, {PLAYER}.\p"
	.string "Bueno, en fin, ¡ánimo!$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "{PLAYER}, ¿qué piensas hacer?\p"
	.string "¿Vas a ir a la BATTLE FRONTIER?\n"
	.string "cuestionario?\p"
	.string "O, ¿vas a completar tu\n"
	.string "POKéDEX?\p"
	.string "Como eres tan fuerte, deberías\n"
	.string "ir al BATTLE FRONTIER.\p"
	.string "Je, si entreno más a mis POKéMON,\n"
	.string "seré más fuerte que tú, {PLAYER}.\p"
	.string "Tal vez debería ir a la FRONTERA\n"
	.string "DE BATALLA.\p"
	.string "Bueno, en fin, ¡ánimo!$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "Fufufu...\p"
	.string "Hoy movimos más botín a nuestro\n"
	.string "ESCONDITE secreto...\p"
	.string "¡¿Qu-quién eres?!\n"
	.string "¡Solo hablaba conmigo mismo!$"

LilycoveCity_Text_ChanceToDoBigThings:
	.string "Soy un RECLUTA, así que no sé qué\n"
	.string "está pensando el JEFE...\p"
	.string "Pero en el TEAM AQUA, sé que lograré\n"
	.string "¡la oportunidad de hacer algo grande!\p"
	.string "¡¿Qu-quién eres?!\n"
	.string "¡Solo hablaba conmigo mismo!$"

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "¡Oye, tú!\p"
	.string "¡No te acerques a la cueva de la cala!\p"
	.string "¿Por qué? ¡No necesito darte razones!\n"
	.string "¡Soy adulto, así que escúchame!$"

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "Si todo este vasto mundo es nuestro,\n"
	.string "del TEAM AQUA, será un lugar más\l"
	.string "feliz para los POKéMON también.$"

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "¡Ahí! ¡WAILMER!\n"
	.string "¡Salta del agua ahora mismo!$"

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "¿Eh? ¿Qué es lo que quieres?\p"
	.string "Arruinas nuestro entrenamiento,\n"
	.string "¿Puedes, tipo, perderte ya?$"

LilycoveCity_Text_ContestHallInTown:
	.string "Hay un SALÓN DE CONCURSOS POKéMON\n"
	.string "justo aquí en este pueblo.\p"
	.string "Eso significa que POKéMON muy bien\n"
	.string "criados vendrán de todo el país.\p"
	.string "¡Mi corazón late de emoción!$"

LilycoveCity_Text_StrangeCaveInCove:
	.string "¿Has visto esa cueva extraña en\n"
	.string "la cala al borde del pueblo?$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "Le enseñaré a mi POKéMON nuevos\n"
	.string "movimientos para un CONCURSO.\p"
	.string "Iré a ver al BORRADOR DE MOVIM.\n"
	.string "¡Haré que olvide los movimientos MO!$"

LilycoveCity_Text_ImFromKanto:
	.string "Vine de KANTO.\p"
	.string "La región de HOENN es hermosa con\n"
	.string "toda su agua y naturaleza verde.\p"
	.string "¿Eh? Espera un segundo...\p"
	.string "¿Habrá POKéMON raros que vivan\n"
	.string "solo en esta zona?$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "El TEAM AQUA ha entrenado a sus\n"
	.string "WAILMER en la caleta.\p"
	.string "¡Nosotros, MARINEROS, no podemos\n"
	.string "salir al mar con ellos ahí!$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "¡Ahoy! ¿Sabías que...?\p"
	.string "Alguien echó al TEAM AQUA de\n"
	.string "¡el camino está libre!\p"
	.string "Eso sacó al WAILMER de la caleta,\n"
	.string "¡ya podemos sacar los botes!$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "Tomaba una siesta relajante en la\n"
	.string "posada del mar con el sonido del mar…\p"
	.string "¡Cuando alguien robó mi POKéMON!\p"
	.string "¿Quién es el secuestrador?\n"
	.string "¿EL EQUIPO AQUA? ¿Fue el EQUIPO AQUA?$"

LilycoveCity_Text_MissingPokemonCameBack:
	.string "Mi POKéMON perdido…\n"
	.string "¡Regresó sin que me diera cuenta!$"

LilycoveCity_Text_ImArtDealer:
	.string "Soy un COMERCIANTE DE ARTE.\p"
	.string "Compro y vendo obras de arte finas,\n"
	.string "especialmente las pinturas.\p"
	.string "He oído que el MUSEO de aquí tiene\n"
	.string "obras magníficas en exhibición…$"

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "Aunque envejezcamos y nos arruguemos,\n"
	.string "el mar siempre sigue siendo joven con\l"
	.string "el brillo vívido de la vida…\p"
	.string "Fwohoho fwohohohoho…$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "Hace sesenta años que mi esposo me\n"
	.string "pidió matrimonio aquí.\l"
	.string "El mar sigue tan bello como siempre.\p"
	.string "Mufufufu mufufufufufu…$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "Hm, conoces la caverna peculiar\n"
	.string "¿en esta caleta?\p"
	.string "Era una formación natural,\n"
	.string "pero luego llegó la gente del\l"
	.string "TEAM AQUA y la remodelaron.\p"
	.string "Se hacen llamar\n"
	.string "the “nature-loving TEAM AQUA”!\p"
	.string "¡Pero lo que hacen y lo que dicen\n"
	.string "no coinciden para nada!$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "Esa cueva en la caleta...\p"
	.string "No me di cuenta al principio,\n"
	.string "pero ahora está vacía.\p"
	.string "Esa gente del TEAM AQUA, deben\n"
	.string "se han ido para siempre.$"

LilycoveCity_Text_CitySign:
	.string "CIUDAD FONDO PLATA\p"
	.string "“Donde la tierra termina y el\n"
	.string "mar comienza.”$"

LilycoveCity_Text_ContestHallSign:
	.string "CENTRO DE CONCURSOS POKéMON\n"
	.string "“¡Lugar de reunión de TRAINERS!”$"

LilycoveCity_Text_MotelSign:
	.string "MOTEL CALA LILY\p"
	.string "“Recuérdanos como COVE LILY de\n"
	.string "LILYCOVE.”$"

LilycoveCity_Text_MuseumSign:
	.string "MUSEO DE CALA LILY\p"
	.string "“Colección Maestra de POKéMON\n"
	.string "en exhibición!”$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "MUSEO DE CALA LILY\p"
	.string "Colección POKéMON de {PLAYER}\n"
	.string "en exhibición!”$"

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "PUERTO DE CIUDAD VERALTO\p"
	.string "“El ferry S.S. TIDAL está en\n"
	.string "obras en CIUDAD PORTALMAR.”\p"
	.string "“El servicio comenzará\n"
	.string "pronto.”$"

LilycoveCity_Text_HarborSign:
	.string "PUERTO DE CIUDAD VERALTO\p"
	.string "“Disfruta de un crucero genial en\n"
	.string "el ferry S.S. TIDAL.”$"

LilycoveCity_Text_TrainerFanClubSign:
	.string "CLUB DE FANS DE ENTRENADORES\p"
	.string "Hay nombres de ENTRENADORES\n"
	.string "escritos por todo el cartel…$"

LilycoveCity_Text_DepartmentStoreSign:
	.string "ALMACENES DE CIUDAD VERALTO\p"
	.string "“Lleno de mercancía increíble\n"
	.string "¡y emoción!\p"
	.string "“¡Un gran lugar para hallar eso\n"
	.string "que necesitas!”$"

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "CASA DEL BORRADOR DE MO\p"
	.string "“Borramos movimientos de POKéMON.”$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "¿Conoces la máquina\n"
	.string "MEZCLADORA DE BAYAS?$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "La gente debe trabajar unida para que\n"
	.string "gire más rápido.\p"
	.string "Cuanto más rápido gire, mejores\n"
	.string "{POKEBLOCK}S obtendrás, he oído.$"

LilycoveCity_Text_ExplainBerryBlender:
	.string "Se usa para hacer un tipo de dulce\n"
	.string "se llama {POKEBLOCK}.\p"
	.string "Si le das un buen {POKEBLOCK} a un POKéMON,\n"
	.string "su condición mejorará mucho.$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "Oí que hay una torre en algún lugar\n"
	.string "de las rutas marinas.\p"
	.string "Dicen que se llama PILAR CIELO.$"

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "Vi una torre alta en algún lugar\n"
	.string "cerca de la RUTA 131.\p"
	.string "¿Podría ser esa…?$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "Acabamos de llegar aquí para nuestra\n"
	.string "luna de miel.\p"
	.string "Vimos por casualidad a un tipo DRAGÓN\n"
	.string "POKéMON volando muy alto en el cielo.\p"
	.string "¿Vivirán POKéMON así de geniales en\n"
	.string "la región de HOENN?$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "En nuestra luna de miel, juramos ver\n"
	.string "tantos POKéMON raros como podamos.\p"
	.string "Así que nos alegró ver un POKéMON\n"
	.string "raro apenas llegamos aquí.\p"
	.string "¡Digo, estamos muy felices!$"

