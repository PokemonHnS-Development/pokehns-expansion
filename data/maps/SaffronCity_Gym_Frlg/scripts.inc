SaffronCity_Gym_Frlg_MapScripts::
	.byte 0

SaffronCity_Gym_EventScript_Sabrina::
	famechecker FAMECHECKER_SABRINA, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	trainerbattle_single TRAINER_LEADER_SABRINA, SaffronCity_Gym_Text_SabrinaIntro, SaffronCity_Gym_Text_SabrinaDefeat, SaffronCity_Gym_EventScript_DefeatedSabrina, NO_MUSIC
	goto_if_unset FLAG_GOT_TM04_FROM_SABRINA, SaffronCity_Gym_EventScript_GiveTM04
	msgbox SaffronCity_Gym_Text_ExplainTM04
	release
	end

SaffronCity_Gym_EventScript_DefeatedSabrina::
	famechecker FAMECHECKER_SABRINA, 2
	famechecker FAMECHECKER_SABRINA, 3
	clearflag FLAG_HIDE_SAFFRON_CITY_POKECENTER_SABRINA_JOURNALS
	setflag FLAG_DEFEATED_SABRINA
	setflag FLAG_BADGE06_GET
	set_gym_trainers_frlg 6
	goto SaffronCity_Gym_EventScript_GiveTM04
	end

SaffronCity_Gym_EventScript_GiveTM04::
	msgbox SaffronCity_Gym_Text_ExplainMarshBadgeTakeThis
	checkitemspace ITEM_TM04
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_Gym_EventScript_NoRoomForTM04
	giveitem_msg SaffronCity_Gym_Text_ReceivedTM04FromSabrina, ITEM_TM04
	setflag FLAG_GOT_TM04_FROM_SABRINA
	msgbox SaffronCity_Gym_Text_SabrinaPostBattle
	release
	end

SaffronCity_Gym_EventScript_NoRoomForTM04::
	msgbox SaffronCity_Gym_Text_BagFullOfOtherItems
	release
	end

SaffronCity_Gym_EventScript_Johan::
	trainerbattle_single TRAINER_PSYCHIC_JOHAN, SaffronCity_Gym_Text_JohanIntro, SaffronCity_Gym_Text_JohanDefeat
	msgbox SaffronCity_Gym_Text_JohanPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Tyron::
	trainerbattle_single TRAINER_PSYCHIC_TYRON, SaffronCity_Gym_Text_TyronIntro, SaffronCity_Gym_Text_TyronDefeat
	famechecker FAMECHECKER_SABRINA, 5
	msgbox SaffronCity_Gym_Text_TyronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Cameron::
	trainerbattle_single TRAINER_PSYCHIC_CAMERON, SaffronCity_Gym_Text_CameronIntro, SaffronCity_Gym_Text_CameronDefeat
	msgbox SaffronCity_Gym_Text_CameronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PSYCHIC_PRESTON, SaffronCity_Gym_Text_PrestonIntro, SaffronCity_Gym_Text_PrestonDefeat
	msgbox SaffronCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Amanda::
	trainerbattle_single TRAINER_CHANNELER_AMANDA, SaffronCity_Gym_Text_AmandaIntro, SaffronCity_Gym_Text_AmandaDefeat
	msgbox SaffronCity_Gym_Text_AmandaPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Stacy::
	trainerbattle_single TRAINER_CHANNELER_STACY, SaffronCity_Gym_Text_StacyIntro, SaffronCity_Gym_Text_StacyDefeat
	msgbox SaffronCity_Gym_Text_StacyPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_Tasha::
	trainerbattle_single TRAINER_CHANNELER_TASHA, SaffronCity_Gym_Text_TashaIntro, SaffronCity_Gym_Text_TashaDefeat
	msgbox SaffronCity_Gym_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Gym_EventScript_GymGuy::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SABRINA, SaffronCity_Gym_EventScript_GymGuyPostVictory
	msgbox SaffronCity_Gym_Text_GymGuyAdvice
	release
	end

SaffronCity_Gym_EventScript_GymGuyPostVictory::
	msgbox SaffronCity_Gym_Text_GymGuyPostVictory
	release
	end

SaffronCity_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, SaffronCity_Gym_EventScript_GymStatuePostVictory
	msgbox SaffronCity_Gym_Text_GymStatue
	releaseall
	end

SaffronCity_Gym_EventScript_GymStatuePostVictory::
	msgbox SaffronCity_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SaffronCity_Gym_Text_SabrinaIntro::
	.string "Tu llegada la vi en visión.\p"
	.string "Tengo poderes psíquicos desde\n"
	.string "era una niña.\p"
	.string "Todo empezó cuando una cuchara que\n"
	.string "carelessly tossed, bent.\p"
	.string "I dislike battling, but if you wish,\n"
	.string "¡te mostraré mis poderes!{PLAY_BGM}{MUS_RG_ENCOUNTER_GYM_LEADER}$"

SaffronCity_Gym_Text_SabrinaDefeat::
	.string "¡Esta derrota me sorprende!\n"
	.string "But, a loss is a loss.\p"
	.string "I admit, I didn't work hard enough\n"
	.string "para ganar.\p"
	.string "Tu victoria te ha hecho merecedor\n"
	.string "la MEDALLA MARJA.$"

SaffronCity_Gym_Text_SabrinaPostBattle::
	.string "El poder psíquico no es algo que\n"
	.string "solo unas pocas personas tengan.\p"
	.string "Todos tienen poder psíquico.\n"
	.string "La gente simplemente no lo nota.$"

SaffronCity_Gym_Text_ExplainMarshBadgeTakeThis::
	.string "The MEDALLA PANTANO makes POKéMON up\n"
	.string "al Nv. 70 te obedecerán.\p"
	.string "Stronger POKéMON will become wild,\n"
	.string "ignorando tus órdenes en combate.\p"
	.string "Just don't raise your POKéMON too\n"
	.string "mucho para evitar ese problema.\p"
	.string "Espera, toma esta MT contigo.$"

SaffronCity_Gym_Text_ReceivedTM04FromSabrina::
	.string "{PLAYER} recibió la MT04 de\n"
	.string "SABRINA.$"

SaffronCity_Gym_Text_ExplainTM04::
	.string "La MT04 es PAZ MENTAL.\p"
	.string "It makes the POKéMON concentrate\n"
	.string "sube el AT. ESP. y la DEF. ESP.$"

SaffronCity_Gym_Text_BagFullOfOtherItems::
	.string "Tu BOLSA está llena de objetos.$"

SaffronCity_Gym_Text_AmandaIntro::
	.string "SABRINA es más joven que yo,\n"
	.string "pero se ha ganado mi respeto.$"

SaffronCity_Gym_Text_AmandaDefeat::
	.string "¡No es suficiente!$"

SaffronCity_Gym_Text_AmandaPostBattle::
	.string "En una batalla de iguales, el que\n"
	.string "tiene más voluntad gana.\p"
	.string "Si quieres vencer a SABRINA, enfócate\n"
	.string "y gana con tu voluntad.$"

SaffronCity_Gym_Text_JohanIntro::
	.string "¿Te asusta nuestro poder oculto?$"

SaffronCity_Gym_Text_JohanDefeat::
	.string "¡Nunca lo preví!$"

SaffronCity_Gym_Text_JohanPostBattle::
	.string "PSYCHIC POKéMON fear only ghosts\n"
	.string "¡y bichos!$"

SaffronCity_Gym_Text_StacyIntro::
	.string "POKéMON take on the appearance of\n"
	.string "sus ENTRENADORES.\p"
	.string "Your POKéMON must be tough, then!$"

SaffronCity_Gym_Text_StacyDefeat::
	.string "¡Lo sabía!$"

SaffronCity_Gym_Text_StacyPostBattle::
	.string "Aún me queda mucho por aprender…\p"
	.string "Debo dominar el tipo PSI y enseñárselo\n"
	.string "to my POKéMON…$"

SaffronCity_Gym_Text_TyronIntro::
	.string "Lo entiendes, ¿verdad?\p"
	.string "Ese poder solo no es suficiente\n"
	.string "win in the world of POKéMON?$"

SaffronCity_Gym_Text_TyronDefeat::
	.string "¡No puedo creer esto!$"

SaffronCity_Gym_Text_TyronPostBattle::
	.string "SABRINA acabó con el DOJO\n"
	.string "MAESTRO KARATE de al lado.$"

SaffronCity_Gym_Text_TashaIntro::
	.string "You and I, our POKéMON shall\n"
	.string "batalla!$"

SaffronCity_Gym_Text_TashaDefeat::
	.string "I lost after all!$"

SaffronCity_Gym_Text_TashaPostBattle::
	.string "Sabía que esto tomaría\n"
	.string "place.$"

SaffronCity_Gym_Text_CameronIntro::
	.string "SABRINA es joven, pero también\n"
	.string "nuestro altamente hábil LÍDER.\p"
	.string "¡No llegarás a ella fácilmente!$"

SaffronCity_Gym_Text_CameronDefeat::
	.string "Ow!\n"
	.string "¡Fuera de combate!$"

SaffronCity_Gym_Text_CameronPostBattle::
	.string "There used to be two POKéMON GYMS\n"
	.string "en AZULONA.\p"
	.string "El DOJO PELEA de al lado perdió\n"
	.string "its GYM status, though.\p"
	.string "Simplemente los aplastamos cuando\n"
	.string "decidió tener solo un GIMNASIO.$"

SaffronCity_Gym_Text_PrestonIntro::
	.string "SAFFRON POKéMON GYM is famous for\n"
	.string "training psychics.\p"
	.string "Quieres ver a SABRINA, ¿verdad?\n"
	.string "¡Puedo adivinarlo!$"

SaffronCity_Gym_Text_PrestonDefeat::
	.string "Arrrgh!$"

SaffronCity_Gym_Text_PrestonPostBattle::
	.string "¡Así es! Usé telepatía para\n"
	.string "leer tu mente!$"

SaffronCity_Gym_Text_GymGuyAdvice::
	.string "Yo!\n"
	.string "¡Un futuro campeón!\p"
	.string "SABRINA's POKéMON use psychic\n"
	.string "poder en vez de fuerza.\p"
	.string "FIGHTING POKéMON are especially\n"
	.string "weak against PSYCHIC POKéMON.\p"
	.string "¡Serán destruidos antes de que\n"
	.string "puedan apuntar un golpe!$"

SaffronCity_Gym_Text_GymGuyPostVictory::
	.string "Psychic power, huh?\p"
	.string "Si tuviera eso, ganaría mucho\n"
	.string "en las máquinas!$"

SaffronCity_Gym_Text_GymStatue::
	.string "GIMNASIO POKéMON DE AZAFRÁN\n"
	.string "LÍDER: SABRINA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}$"

SaffronCity_Gym_Text_GymStatuePlayerWon::
	.string "GIMNASIO POKéMON DE AZAFRÁN\n"
	.string "LÍDER: SABRINA\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "{RIVAL}, {PLAYER}$"

