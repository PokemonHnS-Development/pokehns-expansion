MysteryGiftScript_VisitingTrainer::
	setvaddress MysteryGiftScript_VisitingTrainer
	special ValidateEReaderTrainer
	vgoto_if_eq VAR_RESULT, 0, MysteryGiftScript_VisitingTrainerArrived
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerInstructions
	waitmessage
	waitbuttonpress
	release
	end

MysteryGiftScript_VisitingTrainerArrived:
	lock
	faceplayer
	vmessage sText_MysteryGiftVisitingTrainerArrived
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftVisitingTrainerInstructions:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "Al tener esta WONDER CARD,\n"
	.string "podrás participar en una encuesta\l"
	.string "en un POKéMON MART.\p"
	.string "Usa las encuestas para invitar\n"
	.string "ENTRENADORES a CIUDAD ARRECIFE.\p"
	.string "…Déjame darte una contraseña\n"
	.string "secreta para una encuesta:\p"
	.string "“DAME UN\n"
	.string "ENTRENADOR GENIAL”\p"
	.string "Escríbela en una encuesta y envíala\n"
	.string "al SISTEMA DE COMUNICACIÓN\l"
	.string "INALÁMBRICA.$"

sText_MysteryGiftVisitingTrainerArrived:
	.string "Gracias por usar el Sistema\nREGALO MISTERIOSO.\pUn ENTRENADOR ha llegado a\nCIUDAD ARRECIFE buscándote.\pEsperamos que disfrutes\nluchando contra el ENTRENADOR.\pPuedes invitar a otros\nENTRENADORES con más contraseñas.\pBusca otras contraseñas\nque puedan funcionar.$"
