SaffronCity_Dojo_Frlg_MapScripts::
	.byte 0

SaffronCity_Dojo_EventScript_TriggerMasterBattleLeft::
	lockall
	setvar VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 1
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	releaseall
	end

SaffronCity_Dojo_EventScript_TriggerMasterBattleRight::
	lockall
	setvar VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 1
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	releaseall
	end

SaffronCity_Dojo_EventScript_HitmonleeBall::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HITMON_FROM_DOJO, SaffronCity_Dojo_EventScript_AlreadyGotHitmon
	showmonpic SPECIES_HITMONLEE, 10, 3
	setvar VAR_TEMP_1, SPECIES_HITMONLEE
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox SaffronCity_Dojo_Text_YouWantHitmonlee, MSGBOX_YESNO
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, YES, SaffronCity_Dojo_EventScript_GiveHitmon
	hidemonpic
	release
	end

SaffronCity_Dojo_EventScript_AlreadyGotHitmon::
	msgbox SaffronCity_Dojo_Text_BetterNotGetGreedy
	release
	end

SaffronCity_Dojo_EventScript_HitmonchanBall::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HITMON_FROM_DOJO, SaffronCity_Dojo_EventScript_AlreadyGotHitmon
	showmonpic SPECIES_HITMONCHAN, 10, 3
	setvar VAR_TEMP_1, SPECIES_HITMONCHAN
	applymovement LOCALID_KARATE_MASTER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_MALE
	msgbox SaffronCity_Dojo_Text_YouWantHitmonchan, MSGBOX_YESNO
	call EventScript_RestorePrevTextColor
	goto_if_eq VAR_RESULT, YES, SaffronCity_Dojo_EventScript_GiveHitmon
	hidemonpic
	release
	end

SaffronCity_Dojo_EventScript_GiveHitmon::
	hidemonpic
	givemon VAR_TEMP_1, 25
	goto_if_eq VAR_RESULT, 0, SaffronCity_Dojo_EventScript_ReceivedHitmonParty
	goto_if_eq VAR_RESULT, 1, SaffronCity_Dojo_EventScript_ReceivedHitmonPC
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	release
	end

SaffronCity_Dojo_EventScript_ReceivedHitmonParty::
	removeobject VAR_LAST_TALKED
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster
	waitmessage
	waitfanfare
	setflag FLAG_GOT_HITMON_FROM_DOJO
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SaffronCity_Dojo_EventScript_EndGiveMon
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto SaffronCity_Dojo_EventScript_EndGiveMon
	end

SaffronCity_Dojo_EventScript_ReceivedHitmonPC::
	removeobject VAR_LAST_TALKED
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster
	waitmessage
	waitfanfare
	setflag FLAG_GOT_HITMON_FROM_DOJO
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SaffronCity_Dojo_EventScript_TransferredHitmonToPC
	call Common_EventScript_NameReceivedBoxMon
	goto SaffronCity_Dojo_EventScript_TransferredHitmonToPC
	end

SaffronCity_Dojo_EventScript_TransferredHitmonToPC::
	call Common_EventScript_TransferredToPC
	goto SaffronCity_Dojo_EventScript_EndGiveMon
	end

SaffronCity_Dojo_EventScript_EndGiveMon::
	release
	end

SaffronCity_Dojo_EventScript_Statue::
	msgbox SaffronCity_Dojo_Text_FightingDojo, MSGBOX_SIGN
	end

SaffronCity_Dojo_EventScript_LeftScroll::
	msgbox SaffronCity_Dojo_Text_EnemiesOnEverySide, MSGBOX_SIGN
	end

SaffronCity_Dojo_EventScript_RightScroll::
	msgbox SaffronCity_Dojo_Text_GoesAroundComesAround, MSGBOX_SIGN
	end

SaffronCity_Dojo_EventScript_Hitoshi::
	trainerbattle_single TRAINER_BLACK_BELT_HITOSHI, SaffronCity_Dojo_Text_HitoshiIntro, SaffronCity_Dojo_Text_HitoshiDefeat
	msgbox SaffronCity_Dojo_Text_HitoshiPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_Hideki::
	trainerbattle_single TRAINER_BLACK_BELT_HIDEKI, SaffronCity_Dojo_Text_HidekiIntro, SaffronCity_Dojo_Text_HidekiDefeat
	msgbox SaffronCity_Dojo_Text_HidekiPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_Aaron::
	trainerbattle_single TRAINER_BLACK_BELT_AARON, SaffronCity_Dojo_Text_AaronIntro, SaffronCity_Dojo_Text_AaronDefeat
	msgbox SaffronCity_Dojo_Text_AaronPostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_Mike::
	trainerbattle_single TRAINER_BLACK_BELT_MIKE, SaffronCity_Dojo_Text_MikeIntro, SaffronCity_Dojo_Text_MikeDefeat
	msgbox SaffronCity_Dojo_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_MasterKoichi::
	trainerbattle_single TRAINER_BLACK_BELT_KOICHI, SaffronCity_Dojo_Text_MasterKoichiIntro, SaffronCity_Dojo_Text_MasterKoichiDefeat, SaffronCity_Dojo_EventScript_DefeatedMasterKoichi
	goto_if_set FLAG_GOT_HITMON_FROM_DOJO, SaffronCity_Dojo_EventScript_MasterKoichiAlreadyGotHitmon
	msgbox SaffronCity_Dojo_Text_ChoosePrizedFightingMon, MSGBOX_AUTOCLOSE
	end

SaffronCity_Dojo_EventScript_MasterKoichiAlreadyGotHitmon::
	msgbox SaffronCity_Dojo_Text_StayAndTrainWithUs
	release
	end

SaffronCity_Dojo_EventScript_DefeatedMasterKoichi::
	setvar VAR_MAP_SCENE_SAFFRON_CITY_DOJO, 1
	release
	end

SaffronCity_Dojo_Text_MasterKoichiIntro::
	.string "Grunt!\p"
	.string "Soy el MAESTRO DE KARATE!\n"
	.string "Soy el LIDER aqui!\p"
	.string "¿Deseas desafiarnos?\n"
	.string "¡No esperes piedad!\p"
	.string "Fwaaa!$"

SaffronCity_Dojo_Text_MasterKoichiDefeat::
	.string "Hwa!\n"
	.string "Arrgh! Beaten!$"

SaffronCity_Dojo_Text_ChoosePrizedFightingMon::
	.string "¡He perdido!\p"
	.string "Pero te ruego que no tomes\n"
	.string "nuestro emblema como trofeo!\p"
	.string "A cambio, te daré un premio\n"
	.string "FIGHTING POKéMON!\p"
	.string "¡Elige el que más te guste!$"

SaffronCity_Dojo_Text_StayAndTrainWithUs::
	.string "Grunt!\n"
	.string "nosotros!$"

SaffronCity_Dojo_Text_MikeIntro::
	.string "Hoargh!\n"
	.string "¡Quítate los zapatos!$"

SaffronCity_Dojo_Text_MikeDefeat::
	.string "¡Me rindo!$"

SaffronCity_Dojo_Text_MikePostBattle::
	.string "Espera a ver a nuestro MAESTRO!\n"
	.string "¡No soy nada junto a él!$"

SaffronCity_Dojo_Text_HidekiIntro::
	.string "¡Dicen que eres bueno!\n"
	.string "¡Demuéstramelo!$"

SaffronCity_Dojo_Text_HidekiDefeat::
	.string "Judge!\n"
	.string "One point!$"

SaffronCity_Dojo_Text_HidekiPostBattle::
	.string "Nuestro MAESTRO es un peleador\n"
	.string "¡Prepárate para perder!$"

SaffronCity_Dojo_Text_AaronIntro::
	.string "¡Hiyah!\n"
	.string "¡No temo nada difícil!\p"
	.string "Rompe rocas para entrenar\n"
	.string "every day!$"

SaffronCity_Dojo_Text_AaronDefeat::
	.string "Yow!\n"
	.string "Stubbed fingers!$"

SaffronCity_Dojo_Text_AaronPostBattle::
	.string "Lo único que nos asusta es\n"
	.string "psychic power!$"

SaffronCity_Dojo_Text_HitoshiIntro::
	.string "Hwaah!\p"
	.string "Estás invadiendo nuestro\n"
	.string "FIGHTING DOJO!$"

SaffronCity_Dojo_Text_HitoshiDefeat::
	.string "Oof!\n"
	.string "¡Me rindo!$"

SaffronCity_Dojo_Text_HitoshiPostBattle::
	.string "Los mejores luchadores de la región\n"
	.string "se entrenan aquí.$"

SaffronCity_Dojo_Text_YouWantHitmonlee::
	.string "Quieres el golpe fuerte del\n"
	.string "HITMONLEE?$"

SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster::
	.string "{PLAYER} recibió el {STR_VAR_1}\n"
	.string "MAESTRO DE KÁRATE.$"

SaffronCity_Dojo_Text_YouWantHitmonchan::
	.string "Quieres el golpe de pistón\n"
	.string "HITMONCHAN?$"

SaffronCity_Dojo_Text_ReceivedMonFromKarateMaster2::
	.string "{PLAYER}は　カラテ　だいおう　から\n"
	.string "{STR_VAR_1}を　もらった！$"

SaffronCity_Dojo_Text_BetterNotGetGreedy::
	.string "Mejor no ser avaricioso…$"

SaffronCity_Dojo_Text_EnemiesOnEverySide::
	.string "¡Enemigos por todos lados!$"

SaffronCity_Dojo_Text_GoesAroundComesAround::
	.string "El que la hace la paga.$"

SaffronCity_Dojo_Text_FightingDojo::
	.string "DOJO DE LUCHA$"

