RockTunnel_B1F_Frlg_MapScripts::
	.byte 0

RockTunnel_B1F_EventScript_Sofia::
	trainerbattle_single TRAINER_PICNICKER_SOFIA, RockTunnel_B1F_Text_SofiaIntro, RockTunnel_B1F_Text_SofiaDefeat
	msgbox RockTunnel_B1F_Text_SofiaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Martha::
	trainerbattle_single TRAINER_PICNICKER_MARTHA, RockTunnel_B1F_Text_MarthaIntro, RockTunnel_B1F_Text_MarthaDefeat
	msgbox RockTunnel_B1F_Text_MarthaPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Dudley::
	trainerbattle_single TRAINER_HIKER_DUDLEY, RockTunnel_B1F_Text_DudleyIntro, RockTunnel_B1F_Text_DudleyDefeat
	msgbox RockTunnel_B1F_Text_DudleyPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Allen::
	trainerbattle_single TRAINER_HIKER_ALLEN, RockTunnel_B1F_Text_AllenIntro, RockTunnel_B1F_Text_AllenDefeat
	msgbox RockTunnel_B1F_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Eric::
	trainerbattle_single TRAINER_HIKER_ERIC, RockTunnel_B1F_Text_EricIntro, RockTunnel_B1F_Text_EricDefeat
	msgbox RockTunnel_B1F_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Cooper::
	trainerbattle_single TRAINER_POKEMANIAC_COOPER, RockTunnel_B1F_Text_CooperIntro, RockTunnel_B1F_Text_CooperDefeat
	msgbox RockTunnel_B1F_Text_CooperPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Steve::
	trainerbattle_single TRAINER_POKEMANIAC_STEVE, RockTunnel_B1F_Text_SteveIntro, RockTunnel_B1F_Text_SteveDefeat
	msgbox RockTunnel_B1F_Text_StevePostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_EventScript_Winston::
	trainerbattle_single TRAINER_POKEMANIAC_WINSTON, RockTunnel_B1F_Text_WinstonIntro, RockTunnel_B1F_Text_WinstonDefeat
	msgbox RockTunnel_B1F_Text_WinstonPostBattle, MSGBOX_AUTOCLOSE
	end

RockTunnel_B1F_Text_SofiaIntro::
	.string "¿Sabes cómo puedes evitar\n"
	.string "¿perderse en las montañas?\p"
	.string "Puedes doblar ramitas como\nseñal de camino"
	.string "markers.$"

RockTunnel_B1F_Text_SofiaDefeat::
	.string "Ohhh!\n"
	.string "¡Hice mi mejor esfuerzo!$"

RockTunnel_B1F_Text_SofiaPostBattle::
	.string "¡Quiero ir a casa!$"

RockTunnel_B1F_Text_DudleyIntro::
	.string "¡Jajaja!\n"
	.string "¿Puedes vencer mi poder?$"

RockTunnel_B1F_Text_DudleyDefeat::
	.string "¡Ups!\n"
	.string "Outmuscled!$"

RockTunnel_B1F_Text_DudleyPostBattle::
	.string "Voy por poder porque odio\n"
	.string "thinking.$"

RockTunnel_B1F_Text_CooperIntro::
	.string "You have a POKéDEX?\n"
	.string "I want one, too.$"

RockTunnel_B1F_Text_CooperDefeat::
	.string "Shoot!\n"
	.string "I am so jealous!$"

RockTunnel_B1F_Text_CooperPostBattle::
	.string "When you finish your POKéDEX,\n"
	.string "¿me lo das?$"

RockTunnel_B1F_Text_SteveIntro::
	.string "Um… Do you know about POKéMON\n"
	.string "cosplay?$"

RockTunnel_B1F_Text_SteveDefeat::
	.string "Bueno, eso es todo.$"

RockTunnel_B1F_Text_StevePostBattle::
	.string "POKéMON cosplay is dressing up as\n"
	.string "POKéMON for fun.\p"
	.string "CLEFAIRY es un favorito.$"

RockTunnel_B1F_Text_AllenIntro::
	.string "My POKéMON techniques will leave\n"
	.string "¡llorando!$"

RockTunnel_B1F_Text_AllenDefeat::
	.string "¡Me rindo!\n"
	.string "¡Eres mejor técnico!$"

RockTunnel_B1F_Text_AllenPostBattle::
	.string "En las montañas, a menudo\n"
	.string "ROCK-type POKéMON.$"

RockTunnel_B1F_Text_MarthaIntro::
	.string "No vengo aquí muy seguido,\n"
	.string "pero lucharé contigo.$"

RockTunnel_B1F_Text_MarthaDefeat::
	.string "Oh!\n"
	.string "I lost!$"

RockTunnel_B1F_Text_MarthaPostBattle::
	.string "I like tiny POKéMON.\n"
	.string "¡Los grandes dan miedo!$"

RockTunnel_B1F_Text_EricIntro::
	.string "¡Dame lo mejor que tengas!$"

RockTunnel_B1F_Text_EricDefeat::
	.string "Fired away!$"

RockTunnel_B1F_Text_EricPostBattle::
	.string "I'll raise my POKéMON to beat\n"
	.string "yours, kid.$"

RockTunnel_B1F_Text_WinstonIntro::
	.string "I draw illustrations of POKéMON\n"
	.string "when I'm home.$"

RockTunnel_B1F_Text_WinstonDefeat::
	.string "Uff...\n"
	.string "I'm exhausted…$"

RockTunnel_B1F_Text_WinstonPostBattle::
	.string "Soy artista, no peleador.\n"
	.string "Iré a casa a dibujar.$"

