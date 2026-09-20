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
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "Un ENTRENADOR ha llegado a\n"
	.string "CIUDAD CALOR buscando verte.\p"
	.string "Esperamos que disfrutes\n"
	.string "luchando contra el ENTRENADOR.\p"
	.string "Puedes invitar a más ENTRENADORES\n"
	.string "usando otras contraseñas.\p"
	.string "Busca otras contraseñas\n"
	.string "que puedan funcionar.$"
