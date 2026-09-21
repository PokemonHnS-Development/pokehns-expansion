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
    .string "GIMNASIO POKéMON DE CANELA\n"
    .string "LÍDER: BLAINE\p"
	.string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED$"

SeafoamIslands_Gym_Text_GymStatuePlayerWon::
    .string "GIMNASIO POKéMON DE CANELA\n"
    .string "LÍDER: BLAINE\p"
    .string "ENTRENADORES GANADORES:\n"
	.string "BLUE, RED, {PLAYER}$"

SeafoamIslands_Gym_Text_Blaine_GiveTM:
	.string "¡Toma esto también!$"

SeafoamIslands_Gym_Text_Blaine_ExplainTM:
	.string "Esta MT contiene\n¡el increíble SOFOCO!\pEl calor abrasador achicharra a\ntus rivales, pero baja tu potencia.\p¡Espero que tu rival tenga un\nANTIQUEMADURA extra. ¡Buaaah!$"

SeafoamIslands_Gym_Text_BlaineIntro:
	.string "BLAINE: ¡Waaah!\pMi GIMNASIO en CANELA\nse quemó.\pMis POKéMON de fuego y yo\nestamos\nsin hogar por el volcán.\p¡Waaah!\pPero\nvolví a trabajar como LÍDER\nde GIMNASIO aquí en la cueva.\pSi me\nvences, te daré\nuna MEDALLA.\p¡Ja! Mejor ten una CURA\nQUEMADURA!$"

SeafoamIslands_Gym_Text_BlaineWinLoss:
	.string "BLAINE: Increíble. Me he agotado…\p"
	.string "¡Ganaste la MEDALLA VOLCÁN!$"

SeafoamIslands_Gym_Text_ReceivedVolcanoBadge:
	.string "{PLAYER} recibió la MEDALLA VOLCÁN.$"

SeafoamIslands_Gym_Text_BlaineAfterBattle:
	.string "BLAINE: Perdí esta vez, pero\n"
	.string "ganaré la próxima vez.\p"
	.string "Cuando reconstruya mi GIMNASIO CANELA,\n"
	.string "tendremos que hacer la revancha.$"

SeafoamIslands_Gym_Text_BlaineFightDone:
	.string "BLAINE: Mis POKéMON de fuego serán\n"
	.string "aún más fuertes.\p"
	.string "¡Ya lo verás!$"

SeafoamIslands_Gym_Text_BlaineRematch:
	.string "BLAINE: ¡Vaya!\p"
	.string "Veo que te volviste el de KANTO\n"
	.string "CAMPEÓN de KANTO!\p"
	.string "¡Eso es ardiente!\p"
	.string "Tus habilidades son excelentes.\p"
	.string "Siempre estoy listo para luchar.\p"
	.string "¿Quieres otra revancha conmigo?$"

SeafoamIslands_Gym_Text_BlaineRematchDefeat:
	.string "BLAINE: ¡Tus habilidades son ígneas!\pHas calcinado todas mis\ndefensas.$"

SeafoamIslands_Gym_Text_GymGuideWin:
	.string "¡Oye!\p… ¿Eh? ¿Ya terminó?\p¡Perdón, perdón!\pEl GIMNASIO de ISLA CANELA ya no\nestaba, no sabía dónde encontrarte.\pPero, oye, eres muy fuerte incluso\nsin mis consejos. ¡Sabía que ganarías!$"

SeafoamIslands_Gym_Text_GymGuideWin2:
	.string "Un GIMNASIO POKéMON puede estar en\n"
	.string "mientras el LÍDER de GIMNASIO esté.\p"
	.string "No hace falta un edificio.$"
