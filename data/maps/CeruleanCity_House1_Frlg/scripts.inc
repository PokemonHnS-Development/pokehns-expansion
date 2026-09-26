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
	.string "Entonces...\p"
	.string "¿Cuál de las ocho MEDALLAS\n"
	.string "te describo?$"

CeruleanCity_House1_Text_ComeVisitAnytime::
	.string "Visítame cuando quieras.$"

CeruleanCity_House1_Text_AttackStatFlash::
	.string "El ATAQUE de todos tus\n"
	.string "POKéMON aumenta un poco.\p"
	.string "También te permite usar\n"
	.string "DESTELLO fuera de combate.$"

CeruleanCity_House1_Text_ObeyLv30Cut::
	.string "Los POKéMON de hasta Nv. 30 te\n"
	.string "obedecerán.\p"
	.string "Eso incluye a los externos\n"
	.string "obtenerse en intercambios.\p"
	.string "Los POKéMON de mayor nivel\n"
	.string "desobedecerán en combate.\p"
	.string "También te permite usar\n"
	.string "CORTE fuera de combate.$"

CeruleanCity_House1_Text_SpeedStatFly::
	.string "La estadística VELOCIDAD de todos tus\n"
	.string "POKéMON aumenta un poco.\p"
	.string "También te permite usar\n"
	.string "VUELO fuera de combate.$"

CeruleanCity_House1_Text_ObeyLv50Strength::
	.string "Los POKéMON de hasta Nv. 50 te\n"
	.string "obedecerán.\p"
	.string "Eso incluye a los externos\n"
	.string "obtenerse en intercambios.\p"
	.string "Los POKéMON de mayor nivel\n"
	.string "desobedecerán en combate.\p"
	.string "También te permite usar\n"
	.string "FUERZA fuera de combate.$"

CeruleanCity_House1_Text_DefenseStatSurf::
	.string "La estadística DEFENSA de todos\n"
	.string "POKéMON aumenta un poco.\p"
	.string "También te permite usar\n"
	.string "SURF fuera de combate.$"

CeruleanCity_House1_Text_ObeyLv70RockSmash::
	.string "Los POKéMON de hasta Nv. 70 te\n"
	.string "obedecerán.\p"
	.string "Eso incluye a los externos\n"
	.string "obtenerse en intercambios.\p"
	.string "Los POKéMON de mayor nivel\n"
	.string "desobedecerán en combate.\p"
	.string "También te permite usar\n"
	.string "GOLPE ROCA fuera del combate.$"

CeruleanCity_House1_Text_SpStatsWaterfall::
	.string "Los stats de AT. ESP. y DEF. ESP. de\n"
	.string "todos tus POKéMON suben un poco.\p"
	.string "También te permite usar\n"
	.string "CASCADA fuera de combate.$"

CeruleanCity_House1_Text_AllMonsWillObeyYou::
	.string "¡Todos los POKéMON te obedecerán!$"

