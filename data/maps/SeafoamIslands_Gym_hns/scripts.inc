SeafoamIslands_Gym_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SeafoamIslands_Gym_OnTransition
	.byte 0

SeafoamIslands_Gym_OnTransition: 
	setflag FLAG_TEMP_1
	end

SeafoamIslands_Gym_EventScript_Blaine::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CINNABAR_ISLAND_GYM, SeafoamIslands_Gym_EventScript_Blaine_Defeated
	msgbox SeafoamIslands_Gym_Text_BlaineIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_BLAINE_HNS, SeafoamIslands_Gym_Text_BlaineWinLoss
	message SeafoamIslands_Gym_Text_ReceivedVolcanoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SeafoamIslands_Gym_Text_Blaine_GiveTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_OVERHEAT
	msgbox SeafoamIslands_Gym_Text_Blaine_ExplainTM, MSGBOX_DEFAULT
	setflag FLAG_BADGE15_GET
	setflag FLAG_DEFEATED_CINNABAR_ISLAND_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 15
	clearflag FLAG_HIDE_SEAFOAM_GYMGUY
	call Common_EventScript_SetGymTrainers_hns
	closemessage
	release
	end

SeafoamIslands_Gym_EventScript_Blaine_Defeated::
	msgbox SeafoamIslands_Gym_Text_BlaineAfterBattle, MSGBOX_DEFAULT
	closemessage
	release
	end

SeafomIslands2_EventScript_GymGuide::
	goto_if_set FLAG_TEMP_2, SeafomIslands2_EventScript_GymGuide2
	msgbox SeafoamIslands_Gym_Text_GymGuideWin, MSGBOX_NPC
	setflag FLAG_TEMP_2
	end
SeafomIslands2_EventScript_GymGuide2::
	msgbox SeafoamIslands_Gym_Text_GymGuideWin2, MSGBOX_NPC
	end

SeafoamIslands_Gym_EventScript_GymStatue::
	lockall
	goto_if_set FLAG_BADGE15_GET, SeafoamIslands_Gym_EventScript_GymStatuePostVictory
	msgbox SeafoamIslands_Gym_Text_GymStatue
	releaseall
	end

SeafoamIslands_Gym_EventScript_GymStatuePostVictory::
	msgbox SeafoamIslands_Gym_Text_GymStatuePlayerWon
	releaseall
	end

SeafoamIslands_Gym_Text_GymStatue::
    .string "CINNABAR POKéMON GYM\n"
    .string "LEADER: BLAINE\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

SeafoamIslands_Gym_Text_GymStatuePlayerWon::
    .string "CINNABAR POKéMON GYM\n"
    .string "LEADER: BLAINE\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"

SeafoamIslands_Gym_Text_Blaine_GiveTM:
	.string "Take this too!$"

SeafoamIslands_Gym_Text_Blaine_ExplainTM:
	.string "This TM contains\n"
	.string "the awesome OVERHEAT!\p"
	.string "The overwhelming heat scorches your\n"
	.string "opponents, but then drops your power.\p"
	.string "I hope your next opponent has an\n"
	.string "extra BURN HEAL! Waaah!$"

SeafoamIslands_Gym_Text_BlaineIntro:
	.string "BLAINE: Waaah!\p"
	.string "My GYM in CINNABAR burned down.\p"
	.string "My fire-breathing POKéMON and I are\n"
	.string "sin hogar por el volcán.\p"
	.string "¡Waaah!\p"
	.string "Pero volví a trabajar como LÍDER\n"
	.string "de GIMNASIO aquí en la cueva.\p"
	.string "Si me vences, te daré\n"
	.string "una MEDALLA.\p"
	.string "Ha! You'd better have BURN HEAL!$"

SeafoamIslands_Gym_Text_BlaineWinLoss:
	.string "BLAINE: Increíble. Me he agotado…\p"
	.string "¡Ganaste la MEDALLA VOLCÁN!$"

SeafoamIslands_Gym_Text_ReceivedVolcanoBadge:
	.string "{PLAYER} received VOLCANOBADGE.$"

SeafoamIslands_Gym_Text_BlaineAfterBattle:
	.string "BLAINE: Perdí esta vez, pero\n"
	.string "ganaré la próxima vez.\p"
	.string "Cuando reconstruya mi GIMNASIO CANELA,\n"
	.string "we'll have to have a rematch.$"

SeafoamIslands_Gym_Text_BlaineFightDone:
	.string "BLAINE: My fire POKéMON will be\n"
	.string "even stronger.\p"
	.string "Just you watch!$"

SeafoamIslands_Gym_Text_BlaineRematch:
	.string "BLAINE: ¡Vaya!\p"
	.string "Veo que te volviste el de KANTO\n"
	.string "CAMPEÓN de KANTO!\p"
	.string "¡Eso es ardiente!\p"
	.string "Tus habilidades son excelentes.\p"
	.string "Siempre estoy listo para luchar.\p"
	.string "¿Quieres otra revancha conmigo?$"

SeafoamIslands_Gym_Text_BlaineRematchDefeat:
	.string "BLAINE: Your skills are truly fiery!\p"
	.string "Has calcinado todas mis\n"
	.string "defensas.$"

SeafoamIslands_Gym_Text_GymGuideWin:
	.string "Yo!\p"
	.string "… Huh? It's over already?\p"
	.string "Sorry, sorry!\p"
	.string "CINNABAR GYM was gone, so I didn't\n"
	.string "know where to find you.\p"
	.string "But, hey, you're plenty strong even\n"
	.string "without my advice. I knew you'd win!$"

SeafoamIslands_Gym_Text_GymGuideWin2:
	.string "A POKéMON GYM can be anywhere as\n"
	.string "mientras el LÍDER de GIMNASIO esté.\p"
	.string "No hace falta un edificio.$"
