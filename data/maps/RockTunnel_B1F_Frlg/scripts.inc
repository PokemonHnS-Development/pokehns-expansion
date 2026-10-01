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
	.string "marcas.$"

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
	.string "¡Me superaste!$"

RockTunnel_B1F_Text_DudleyPostBattle::
	.string "Voy por poder porque odio\n"
	.string "pensar.$"

RockTunnel_B1F_Text_CooperIntro::
	.string "¿Tienes una POKéDEX?\n"
	.string "¡Quiero una también!$"

RockTunnel_B1F_Text_CooperDefeat::
	.string "¡Rayos!\n"
	.string "¡Qué envidia me das!$"

RockTunnel_B1F_Text_CooperPostBattle::
	.string "Cuando acabes tu POKéDEX,\n"
	.string "¿me lo das?$"

RockTunnel_B1F_Text_SteveIntro::
	.string "Em... ¿Sabes algo del\n"
	.string "cosplay POKéMON?$"

RockTunnel_B1F_Text_SteveDefeat::
	.string "Bueno, eso es todo.$"

RockTunnel_B1F_Text_StevePostBattle::
	.string "El cosplay POKéMON es disfrazarse\n"
	.string "de POKéMON por diversión.\p"
	.string "CLEFAIRY es un favorito.$"

RockTunnel_B1F_Text_AllenIntro::
	.string "¡Mis técnicas POKéMON te dejarán\n"
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
	.string "¡Oh!\n"
	.string "¡Perdí!$"

RockTunnel_B1F_Text_MarthaPostBattle::
	.string "Me gustan los POKéMON pequeños.\n"
	.string "¡Los grandes dan miedo!$"

RockTunnel_B1F_Text_EricIntro::
	.string "¡Dame lo mejor que tengas!$"

RockTunnel_B1F_Text_EricDefeat::
	.string "¡Me venciste!$"

RockTunnel_B1F_Text_EricPostBattle::
	.string "Entrenaré a mis POKéMON para\n"
	.string "vencerte, chico.$"

RockTunnel_B1F_Text_WinstonIntro::
	.string "Dibujo ilustraciones de POKéMON\n"
	.string "al volver a casa.$"

RockTunnel_B1F_Text_WinstonDefeat::
	.string "Uff...\n"
	.string "Estoy agotado...$"

RockTunnel_B1F_Text_WinstonPostBattle::
	.string "Soy artista, no peleador.\n"
	.string "Iré a casa a dibujar.$"

