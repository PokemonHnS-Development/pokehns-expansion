VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "Pensar que estoy más cerca de la\n"
	.string "LIGA POKéMON...\p"
	.string "Me están dando nervios...$"

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "I couldn't do a thing…$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "La LIGA POKéMON se siente lejana\n"
	.string "otra vez... Qué decepción...$"

VictoryRoad_B1F_Text_ShannonIntro:
	.string "Para ganar en la LIGA POKéMON,\n"
	.string "necesitas la confianza de tu\l"
	.string "POKéMON.$"

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "Su relación se basa en una\n"
	.string "confianza sólida.$"

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "Al estar siempre juntos, la confianza\n"
	.string "crece entre POKéMON y ENTRENADORES.$"

VictoryRoad_B1F_Text_MichelleIntro:
	.string "Esta no es la meta. Es solo un lugar\n"
	.string "en camino a la LIGA POKéMON.$"

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "That's the way!$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "¡Te irá bien, seguro!\n"
	.string "¡Tus POKéMON están ansiosos por ir!$"

VictoryRoad_B1F_Text_MitchellIntro:
	.string "¡Mis POKéMON son cósmicamente\n"
	.string "impresionantes!$"

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "I've never met anyone like you before.$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "Incluso fuera de batalla, siento\n"
	.string "un poder increíble emanando de ti\l"
	.string "y de tus POKéMON.$"

VictoryRoad_B1F_Text_HalleIntro:
	.string "¡Vale, no hace falta que te alteres!\n"
	.string "¡Relájate, tomémoslo con calma!$"

VictoryRoad_B1F_Text_HalleDefeat:
	.string "¡Vaya!\n"
	.string "¡Maravilloso!$"

VictoryRoad_B1F_Text_HallePostBattle:
	.string "Sí, esta es la VÍA VICTORIA.\p"
	.string "Pero no es tan diferente del\n"
	.string "camino que has seguido hasta ahora.\p"
	.string "¡Intenta disfrutar del resto del\n"
	.string "trayecto!$"

