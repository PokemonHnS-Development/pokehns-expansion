SixIsland_WaterPath_House1_Frlg_MapScripts::
	.byte 0

SixIsland_WaterPath_House1_EventScript_Beauty::
	lock
	faceplayer
	setvar VAR_0x8004, SPECIES_HERACROSS
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, FALSE, SixIsland_WaterPath_House1_EventScript_NoHeracrossInParty
	special GetHeracrossSizeRecordInfo
	msgbox SixIsland_WaterPath_House1_Text_MayIMeasureHeracross
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_ge VAR_RESULT, PARTY_SIZE, SixIsland_WaterPath_House1_EventScript_DontShowMon
	special CompareHeracrossSize
	goto_if_eq VAR_RESULT, 1, SixIsland_WaterPath_House1_EventScript_ShownNonHeracross
	goto_if_eq VAR_RESULT, 2, SixIsland_WaterPath_House1_EventScript_ShownSmallHeracross
	goto_if_eq VAR_RESULT, 3, SixIsland_WaterPath_House1_EventScript_ShownBigHeracross
	goto_if_eq VAR_RESULT, 4, SixIsland_WaterPath_House1_EventScript_ShownTiedHeracross
	release
	end

SixIsland_WaterPath_House1_EventScript_NoHeracrossInParty::
	msgbox SixIsland_WaterPath_House1_Text_LoveItNeedItHeracross
	release
	end

SixIsland_WaterPath_House1_EventScript_DontShowMon::
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownNonHeracross::
	msgbox SixIsland_WaterPath_House1_Text_ThisWontDo
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownSmallHeracross::
	goto_if_unset FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1, SixIsland_WaterPath_House1_EventScript_ShownBigHeracross
	msgbox SixIsland_WaterPath_House1_Text_ItsXInchesYInchesWasBiggest
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownTiedHeracross::
	goto_if_unset FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1, SixIsland_WaterPath_House1_EventScript_ShownBigHeracross
	msgbox SixIsland_WaterPath_House1_Text_ItsXInchesSameAsBefore
	release
	end

SixIsland_WaterPath_House1_EventScript_ShownBigHeracross::
	setflag FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1
	msgbox SixIsland_WaterPath_House1_Text_ItsXInchesDeserveReward
	giveitem ITEM_NEST_BALL
	goto_if_eq VAR_RESULT, FALSE, SixIsland_WaterPath_House1_EventScript_NoRoomForNestBall
	msgbox SixIsland_WaterPath_House1_Text_WantToSeeBiggerOne
	release
	end

SixIsland_WaterPath_House1_EventScript_NoRoomForNestBall::
	msgbox SixIsland_WaterPath_House1_Text_YourBagIsFull
	release
	end

SixIsland_WaterPath_House1_EventScript_SizeRecord::
	lockall
	goto_if_set FLAG_GOT_NEST_BALL_FROM_WATER_PATH_HOUSE_1, SixIsland_WaterPath_House1_EventScript_SizeRecordNonEmpty
	msgbox SixIsland_WaterPath_House1_Text_BlankChartOfSomeSort
	releaseall
	end

SixIsland_WaterPath_House1_EventScript_SizeRecordNonEmpty::
	special GetHeracrossSizeRecordInfo
	msgbox SixIsland_WaterPath_House1_Text_BiggestHeracrossIsXInches
	releaseall
	end

SixIsland_WaterPath_House1_Text_LoveItNeedItHeracross::
	.string "Hera, hera, HERACROSS!\n"
	.string "Big and shiny, it's the bug boss!\l"
	.string "Lo amo, lo necesito, ¡HERACROSS!$"

SixIsland_WaterPath_House1_Text_MayIMeasureHeracross::
	.string "Eeeeek!\n"
	.string "¡Es un HERACROSS!\p"
	.string "Please, please, may I measure how\n"
	.string "¿Grande es?$"

SixIsland_WaterPath_House1_Text_ItsXInchesDeserveReward::
	.string "¡Aah, mide {STR_VAR_2} pulgadas!\n"
	.string "¡Nunca he visto algo así!\l"
	.string "¡Mereces una recompensa!$"

SixIsland_WaterPath_House1_Text_WantToSeeBiggerOne::
	.string "Quiero ver uno mucho, mucho más\n"
	.string "grande que ese HERACROSS.\p"
	.string "Oh, cómo los adoro, tan\n"
	.string "HERACROSS!$"

SixIsland_WaterPath_House1_Text_ItsXInchesSameAsBefore::
	.string "¿Eh? Mide {STR_VAR_2} pulgadas...\n"
	.string "¡Bah! ¡Es igual que antes!$"

SixIsland_WaterPath_House1_Text_ItsXInchesYInchesWasBiggest::
	.string "Oh, solo son {STR_VAR_2} pulgadas.\n"
	.string "El HERACROSS anterior era más grande.\p"
	.string "Medía {STR_VAR_3} pulgadas, la más\n"
	.string "¡HERACROSS me has traído!$"

SixIsland_WaterPath_House1_Text_ThisWontDo::
	.string "¡Oh, no! ¡Esto no sirve!\p"
	.string "HERACROSS looks much more macho\n"
	.string "and cool, and has a lovely horn!$"

SixIsland_WaterPath_House1_Text_YourBagIsFull::
	.string "Tu BOLSA está llena.\n"
	.string "Mi recompensa no cabe.$"

SixIsland_WaterPath_House1_Text_BiggestHeracrossIsXInches::
	.string "El HERACROSS más grande que he\n"
	.string "visto jamás mide:\p"
	.string "{STR_VAR_3} inches!$"

SixIsland_WaterPath_House1_Text_BlankChartOfSomeSort::
	.string "Es una tabla en blanco.\p"
	.string "Tiene espacios para anotar\n"
	.string "registros de algún tipo.$"

