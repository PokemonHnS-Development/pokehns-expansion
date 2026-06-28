Common_EventScript_SetGymTrainers::
	switch VAR_0x8008
	case 1, RustboroCity_Gym_SetGymTrainers
	case 2, DewfordTown_Gym_SetGymTrainers
	case 3, MauvilleCity_Gym_SetGymTrainers
	case 4, LavaridgeTown_Gym_SetGymTrainers
	case 5, PetalburgCity_Gym_SetGymTrainers
	case 6, FortreeCity_Gym_SetGymTrainers
	case 7, MossdeepCity_Gym_SetGymTrainers
	case 8, SootopolisCity_Gym_SetGymTrainers
	end
	
Common_EventScript_SetGymTrainers_Frlg::
	switch VAR_0x8008
	case 1, EventScript_SetPewterGymTrainers
	case 2, EventScript_SetCeruleanGymTrainers
	case 3, EventScript_SetVermilionGymTrainers
	case 4, EventScript_SetCeladonGymTrainers
	case 5, EventScript_SetFuchsiaGymTrainers
	case 6, EventScript_SetSaffronGymTrainers
	case 7, EventScript_SetCinnabarGymTrainers
	case 8, EventScript_SetViridianGymTrainers
	end

RustboroCity_Gym_SetGymTrainers::
	settrainerflag TRAINER_JOSH
	settrainerflag TRAINER_TOMMY
	settrainerflag TRAINER_MARC
	return

DewfordTown_Gym_SetGymTrainers::
	settrainerflag TRAINER_TAKAO
	settrainerflag TRAINER_JOCELYN
	settrainerflag TRAINER_LAURA
	settrainerflag TRAINER_BRENDEN
	settrainerflag TRAINER_CRISTIAN
	settrainerflag TRAINER_LILITH
	return

MauvilleCity_Gym_SetGymTrainers::
	settrainerflag TRAINER_KIRK
	settrainerflag TRAINER_SHAWN
	settrainerflag TRAINER_BEN
	settrainerflag TRAINER_VIVIAN
	settrainerflag TRAINER_ANGELO
	return

LavaridgeTown_Gym_SetGymTrainers::
	settrainerflag TRAINER_COLE
	settrainerflag TRAINER_AXLE
	settrainerflag TRAINER_KEEGAN
	settrainerflag TRAINER_GERALD
	settrainerflag TRAINER_DANIELLE
	settrainerflag TRAINER_JACE
	settrainerflag TRAINER_JEFF
	settrainerflag TRAINER_ELI
	return

PetalburgCity_Gym_SetGymTrainers::
	settrainerflag TRAINER_RANDALL
	settrainerflag TRAINER_PARKER
	settrainerflag TRAINER_GEORGE
	settrainerflag TRAINER_BERKE
	settrainerflag TRAINER_MARY
	settrainerflag TRAINER_ALEXIA
	settrainerflag TRAINER_JODY
	return

FortreeCity_Gym_SetGymTrainers::
	settrainerflag TRAINER_JARED
	settrainerflag TRAINER_FLINT
	settrainerflag TRAINER_ASHLEY
	settrainerflag TRAINER_EDWARDO
	settrainerflag TRAINER_HUMBERTO
	settrainerflag TRAINER_DARIUS
	return

MossdeepCity_Gym_SetGymTrainers::
	settrainerflag TRAINER_PRESTON
	settrainerflag TRAINER_VIRGIL
	settrainerflag TRAINER_BLAKE
	settrainerflag TRAINER_HANNAH
	settrainerflag TRAINER_SAMANTHA
	settrainerflag TRAINER_MAURA
	settrainerflag TRAINER_SYLVIA
	settrainerflag TRAINER_NATE
	settrainerflag TRAINER_KATHLEEN
	settrainerflag TRAINER_CLIFFORD
	settrainerflag TRAINER_MACEY
	settrainerflag TRAINER_NICHOLAS
	return

SootopolisCity_Gym_SetGymTrainers::
	settrainerflag TRAINER_ANDREA
	settrainerflag TRAINER_CRISSY
	settrainerflag TRAINER_BRIANNA
	settrainerflag TRAINER_CONNIE
	settrainerflag TRAINER_BRIDGET
	settrainerflag TRAINER_OLIVIA
	settrainerflag TRAINER_TIFFANY
	settrainerflag TRAINER_BETHANY
	settrainerflag TRAINER_ANNIKA
	settrainerflag TRAINER_DAPHNE
	return

EventScript_SetPewterGymTrainers::
	settrainerflag TRAINER_CAMPER_LIAM
	return

EventScript_SetCeruleanGymTrainers::
	settrainerflag TRAINER_PICNICKER_DIANA
	settrainerflag TRAINER_SWIMMER_MALE_LUIS
	return

EventScript_SetVermilionGymTrainers::
	settrainerflag TRAINER_SAILOR_DWAYNE
	settrainerflag TRAINER_ENGINEER_BAILY
	settrainerflag TRAINER_GENTLEMAN_TUCKER
	return

EventScript_SetCeladonGymTrainers::
	settrainerflag TRAINER_LASS_KAY
	settrainerflag TRAINER_LASS_LISA
	settrainerflag TRAINER_PICNICKER_TINA
	settrainerflag TRAINER_BEAUTY_BRIDGET
	settrainerflag TRAINER_BEAUTY_TAMIA
	settrainerflag TRAINER_BEAUTY_LORI
	settrainerflag TRAINER_COOLTRAINER_MARY
	return

EventScript_SetFuchsiaGymTrainers::
	settrainerflag TRAINER_TAMER_PHIL
	settrainerflag TRAINER_TAMER_EDGAR
	settrainerflag TRAINER_JUGGLER_KIRK
	settrainerflag TRAINER_JUGGLER_SHAWN
	settrainerflag TRAINER_JUGGLER_KAYDEN
	settrainerflag TRAINER_JUGGLER_NATE
	return

EventScript_SetSaffronGymTrainers::
	settrainerflag TRAINER_PSYCHIC_JOHAN
	settrainerflag TRAINER_PSYCHIC_TYRON
	settrainerflag TRAINER_PSYCHIC_CAMERON
	settrainerflag TRAINER_PSYCHIC_PRESTON
	settrainerflag TRAINER_CHANNELER_AMANDA
	settrainerflag TRAINER_CHANNELER_STACY
	settrainerflag TRAINER_CHANNELER_TASHA
	return

EventScript_SetCinnabarGymTrainers::
	settrainerflag TRAINER_SUPER_NERD_ERIK
	settrainerflag TRAINER_SUPER_NERD_AVERY
	settrainerflag TRAINER_SUPER_NERD_DEREK
	settrainerflag TRAINER_SUPER_NERD_ZAC
	settrainerflag TRAINER_BURGLAR_QUINN
	settrainerflag TRAINER_BURGLAR_RAMON
	settrainerflag TRAINER_BURGLAR_DUSTY
	return

EventScript_SetViridianGymTrainers::
	settrainerflag TRAINER_TAMER_JASON
	settrainerflag TRAINER_TAMER_COLE
	settrainerflag TRAINER_BLACK_BELT_ATSUSHI
	settrainerflag TRAINER_BLACK_BELT_KIYO
	settrainerflag TRAINER_BLACK_BELT_TAKASHI
	settrainerflag TRAINER_COOLTRAINER_SAMUEL
	settrainerflag TRAINER_COOLTRAINER_YUJI
	settrainerflag TRAINER_COOLTRAINER_WARREN
	return

Common_EventScript_SetGymTrainers_hns::
	switch VAR_0x8008
	case 1, VioletCity_Gym_SetGymTrainers_hns
	case 2, AzaleaTown_Gym_SetGymTrainers_hns
	case 3, GoldenrodCity_Gym_SetGymTrainers_hns
	case 4, EcruteakCity_Gym_SetGymTrainers_hns
	case 5, CianwoodCity_Gym_SetGymTrainers_hns
	case 6, OlivineCity_Gym_SetGymTrainers_hns
	case 7, MahoganyTown_Gym_SetGymTrainers_hns
	case 8, BlackthornCity_Gym_SetGymTrainers_hns
	case 9, PewterCity_Gym_SetGymTrainers_hns
	case 10, CeruleanCity_Gym_SetGymTrainers_hns
	case 11, VermilionCity_Gym_SetGymTrainers_hns
	case 12, CeladonCity_Gym_SetGymTrainers_hns
	case 13, SaffronCity_Gym_SetGymTrainers_hns
	case 14, FuchsiaCity_Gym_SetGymTrainers_hns
	case 15, CinnabarIsland_Gym_SetGymTrainers_hns
	case 16, ViridianCity_Gym_SetGymTrainers_hns
	end

VioletCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_ROD_HNS
	settrainerflag TRAINER_ABE_HNS
	return

AzaleaTown_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_BENNY_HNS
	settrainerflag TRAINER_AL_HNS
	settrainerflag TRAINER_JOSH_HNS
	settrainerflag TRAINER_AMY_AND_MAY_HNS
	return

GoldenrodCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_CARRIE_HNS
	settrainerflag TRAINER_BRIDGET_HNS
	settrainerflag TRAINER_VICTORIA_HNS
	settrainerflag TRAINER_SAMANTHA_HNS
	return

EcruteakCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_JEFFREY_HNS
	settrainerflag TRAINER_PING_HNS
	settrainerflag TRAINER_MARTHA_HNS
	settrainerflag TRAINER_GRACE_HNS
	return

CianwoodCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_YOSHI_HNS
	settrainerflag TRAINER_LAO_HNS
	settrainerflag TRAINER_NOB_HNS
	settrainerflag TRAINER_LUNG_HNS
	return

OlivineCity_Gym_SetGymTrainers_hns::
	return

MahoganyTown_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_ROXANNE_HNS
	settrainerflag TRAINER_RONALD_HNS
	settrainerflag TRAINER_CLARISSA_HNS
	settrainerflag TRAINER_BRAD_HNS
	settrainerflag TRAINER_DOUGLAS_HNS
	return

BlackthornCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_MIKE_HNS
	settrainerflag TRAINER_PAUL_HNS
	settrainerflag TRAINER_LOLA_HNS
	settrainerflag TRAINER_CODY_HNS
	settrainerflag TRAINER_FRAN_HNS
	return

PewterCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_JERRY_HNS
	return

CeruleanCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_DIANA_HNS
	settrainerflag TRAINER_BRIANA_HNS
	settrainerflag TRAINER_PARKER_HNS
	return

VermilionCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_GREGORY_HNS
	settrainerflag TRAINER_VINCENT_HNS
	settrainerflag TRAINER_HORTON_HNS
	return

CeladonCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_MICHELLE_HNS
	settrainerflag TRAINER_TANYA_HNS
	settrainerflag TRAINER_JULIA_HNS
	settrainerflag TRAINER_JO_AND_ZOE_HNS
	return

SaffronCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_REBECCA_HNS
	settrainerflag TRAINER_FRANKLIN_HNS
	settrainerflag TRAINER_DORIS_HNS
	settrainerflag TRAINER_JARED_HNS
	return

FuchsiaCity_Gym_SetGymTrainers_hns::
	settrainerflag TRAINER_ALICE_HNS
	settrainerflag TRAINER_LINDA_HNS
	settrainerflag TRAINER_CINDY_HNS
	settrainerflag TRAINER_BARRY_HNS
	return

CinnabarIsland_Gym_SetGymTrainers_hns::
	return

ViridianCity_Gym_SetGymTrainers_hns::
	return
