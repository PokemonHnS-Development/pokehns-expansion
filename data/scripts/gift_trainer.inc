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
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
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
	.string "Thank you for using the MYSTERY\n"
	.string "GIFT System.\p"
	.string "A TRAINER has arrived in\n"
	.string "SOOTOPOLIS CITY looking for you.\p"
	.string "We hope you will enjoy\n"
	.string "battling the visiting TRAINER.\p"
	.string "You may invite other TRAINERS by\n"
	.string "entering other passwords.\p"
	.string "Try looking for other passwords\n"
	.string "that may work.$"
