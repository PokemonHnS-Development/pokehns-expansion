CeruleanCity_House1_Frlg_MapScripts::
	.byte 0

CeruleanCity_House1_EventScript_BadgeGuy::
	lock
	faceplayer
	msgbox CeruleanCity_House1_Text_BadgesHaveAmazingSecrets
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeAnotherBadge::
	message CeruleanCity_House1_Text_DescribeWhichBadge
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BADGES
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, CeruleanCity_House1_EventScript_DescribeBoulderBadge
	case 1, CeruleanCity_House1_EventScript_DescribeCascadeBadge
	case 2, CeruleanCity_House1_EventScript_DescribeThunderBadge
	case 3, CeruleanCity_House1_EventScript_DescribeRainbowBadge
	case 4, CeruleanCity_House1_EventScript_DescribeSoulBadge
	case 5, CeruleanCity_House1_EventScript_DescribeMarshBadge
	case 6, CeruleanCity_House1_EventScript_DescribeVolcanoBadge
	case 7, CeruleanCity_House1_EventScript_DescribeEarthBadge
	case 8, CeruleanCity_House1_EventScript_StopDescribingBadges
	case 127, CeruleanCity_House1_EventScript_StopDescribingBadges
	end

CeruleanCity_House1_EventScript_DescribeBoulderBadge::
	msgbox CeruleanCity_House1_Text_AttackStatFlash
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeCascadeBadge::
	msgbox CeruleanCity_House1_Text_ObeyLv30Cut
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeThunderBadge::
	msgbox CeruleanCity_House1_Text_SpeedStatFly
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeRainbowBadge::
	msgbox CeruleanCity_House1_Text_ObeyLv50Strength
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeSoulBadge::
	msgbox CeruleanCity_House1_Text_DefenseStatSurf
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeMarshBadge::
	msgbox CeruleanCity_House1_Text_ObeyLv70RockSmash
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeVolcanoBadge::
	msgbox CeruleanCity_House1_Text_SpStatsWaterfall
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_DescribeEarthBadge::
	msgbox CeruleanCity_House1_Text_AllMonsWillObeyYou
	goto CeruleanCity_House1_EventScript_DescribeAnotherBadge
	end

CeruleanCity_House1_EventScript_StopDescribingBadges::
	msgbox CeruleanCity_House1_Text_ComeVisitAnytime
	release
	end

CeruleanCity_House1_Text_BadgesHaveAmazingSecrets::
	.string "Solo ENTRENADORES expertos pueden\n"
	.string "POKéMON BADGES.\p"
	.string "Veo que tienes al menos una.\p"
	.string "Esas MEDALLAS tienen secretos\n"
	.string "increíbles, ¿sabías?$"

CeruleanCity_House1_Text_DescribeWhichBadge::
	.string "Now then…\p"
	.string "¿Cuál de las ocho MEDALLAS\n"
	.string "I describe?$"

CeruleanCity_House1_Text_ComeVisitAnytime::
	.string "Visítame cuando quieras.$"

CeruleanCity_House1_Text_AttackStatFlash::
	.string "El ATQUE de todos tus\n"
	.string "POKéMON increases a little bit.\p"
	.string "También te permite usar\n"
	.string "DESTELLO fuera de combate.$"

CeruleanCity_House1_Text_ObeyLv30Cut::
	.string "POKéMON up to Lv. 30 will obey\n"
	.string "vencerte.\p"
	.string "Eso incluye a los externos\n"
	.string "obtenerse en intercambios.\p"
	.string "POKéMON of higher levels will\n"
	.string "ser indisciplinado en combate.\p"
	.string "También te permite usar\n"
	.string "CORTE fuera de combate.$"

CeruleanCity_House1_Text_SpeedStatFly::
	.string "La estadística VELOCIDAD de todos tus\n"
	.string "POKéMON increases a little bit.\p"
	.string "También te permite usar\n"
	.string "VUELO fuera de combate.$"

CeruleanCity_House1_Text_ObeyLv50Strength::
	.string "POKéMON up to Lv. 50 will obey\n"
	.string "vencerte.\p"
	.string "Eso incluye a los externos\n"
	.string "obtenerse en intercambios.\p"
	.string "POKéMON of higher levels will\n"
	.string "ser indisciplinado en combate.\p"
	.string "También te permite usar\n"
	.string "FUERZA fuera de combate.$"

CeruleanCity_House1_Text_DefenseStatSurf::
	.string "La estadística DEFENSA de todos\n"
	.string "POKéMON increases a little bit.\p"
	.string "También te permite usar\n"
	.string "SURF fuera de combate.$"

CeruleanCity_House1_Text_ObeyLv70RockSmash::
	.string "POKéMON up to Lv. 70 will obey\n"
	.string "vencerte.\p"
	.string "Eso incluye a los externos\n"
	.string "obtenerse en intercambios.\p"
	.string "POKéMON of higher levels will\n"
	.string "ser indisciplinado en combate.\p"
	.string "También te permite usar\n"
	.string "GOLPE ROCA fuera del combate.$"

CeruleanCity_House1_Text_SpStatsWaterfall::
	.string "Los stats de AT. ESP y DEF. ESP\n"
	.string "all your POKéMON rise a little bit.\p"
	.string "También te permite usar\n"
	.string "CASCADA fuera de combate.$"

CeruleanCity_House1_Text_AllMonsWillObeyYou::
	.string "All POKéMON will obey you!$"

