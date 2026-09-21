VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "Entrené con toda mi familia,\n"
	.string "¡cada uno de nosotros!\l"
	.string "¡No perderé contra nadie!$"

VictoryRoad_B2F_Text_VitoDefeat:
	.string "¡¿Mejor que mi familia?!\n"
	.string "¡¿Es eso posible?!$"

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "Yo era el mejor de toda mi\n"
	.string "familia. Nunca había perdido...\p"
	.string "He perdido la confianza...\n"
	.string "Tal vez debería irme a casa...$"

VictoryRoad_B2F_Text_OwenIntro:
	.string "Oí que había un niño muy fuerte\n"
	.string "por aquí. ¿Se referían a ti?$"

VictoryRoad_B2F_Text_OwenDefeat:
	.string "¡El pequeñín es duro!$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "Según los rumores, ese chico\n"
	.string "es de CIUDAD PETALBURG.$"

VictoryRoad_B2F_Text_CarolineIntro:
	.string "Debes estar cansándote un poco.$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "No signs of tiring at all!$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "VIAJE VICTORIA y la LIGA POKéMON\n"
	.string "son retos largos y agotadores.\l"
	.string "¡Cuidado con la fatiga!$"

VictoryRoad_B2F_Text_JulieIntro:
	.string "No te confíes solo porque\n"
	.string "tengas muchas MEDALLAS de GIMNASIO.\p"
	.string "¡Siempre habrá alguien\n"
	.string "que sea mejor que tú!$"

VictoryRoad_B2F_Text_JulieDefeat:
	.string "¡Eres mejor que yo!$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "Mira tus MEDALLAS obtenidas y\n"
	.string "recuerda a los ENTRENADORES vencidos.$"

VictoryRoad_B2F_Text_FelixIntro:
	.string "Llegué hasta aquí, pero la tensión\n"
	.string "me da un dolor de estómago horrible…$"

VictoryRoad_B2F_Text_FelixDefeat:
	.string "Ooh…\n"
	.string "Me duele…$"

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "Me pongo tenso al saber que ya\n"
	.string "estoy cerca de la LIGA POKéMON.\p"
	.string "Hago lo posible por fingir calma.$"

VictoryRoad_B2F_Text_DianneIntro:
	.string "La élite de la élite se reúne en\n"
	.string "esta cueva.\p"
	.string "¿Qué te parece el lugar?$"

VictoryRoad_B2F_Text_DianneDefeat:
	.string "¡Ni se inmuta en absoluto!$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "¡Tienes agallas! ¡Eso me gusta!\n"
	.string "¡Sigue así!$"

