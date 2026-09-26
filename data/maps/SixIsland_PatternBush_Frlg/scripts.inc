SixIsland_PatternBush_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SixIsland_PatternBush_OnTransition
	.byte 0

SixIsland_PatternBush_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SIX_ISLAND_PATTERN_BUSH
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	call_if_ge VAR_TEMP_1, 50, SixIsland_PatternBush_EventScript_SetEscapeRightExit
	call_if_le VAR_TEMP_1, 49, SixIsland_PatternBush_EventScript_SetEscapeLeftExit
	end

SixIsland_PatternBush_EventScript_SetEscapeRightExit::
	setescapewarp MAP_SIX_ISLAND_GREEN_PATH, 255, 64, 10
	return

SixIsland_PatternBush_EventScript_SetEscapeLeftExit::
	setescapewarp MAP_SIX_ISLAND_GREEN_PATH, 255, 45, 10
	return

SixIsland_PatternBush_EventScript_Bethany::
	trainerbattle_single TRAINER_PKMN_BREEDER_BETHANY, SixIsland_PatternBush_Text_BethanyIntro, SixIsland_PatternBush_Text_BethanyDefeat
	msgbox SixIsland_PatternBush_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Allison::
	trainerbattle_single TRAINER_PKMN_BREEDER_ALLISON, SixIsland_PatternBush_Text_AllisonIntro, SixIsland_PatternBush_Text_AllisonDefeat
	msgbox SixIsland_PatternBush_Text_AllisonPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Garret::
	trainerbattle_single TRAINER_BUG_CATCHER_GARRET, SixIsland_PatternBush_Text_GarretIntro, SixIsland_PatternBush_Text_GarretDefeat
	msgbox SixIsland_PatternBush_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Jonah::
	trainerbattle_single TRAINER_BUG_CATCHER_JONAH, SixIsland_PatternBush_Text_JonahIntro, SixIsland_PatternBush_Text_JonahDefeat
	msgbox SixIsland_PatternBush_Text_JonahPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Vance::
	trainerbattle_single TRAINER_BUG_CATCHER_VANCE, SixIsland_PatternBush_Text_VanceIntro, SixIsland_PatternBush_Text_VanceDefeat
	msgbox SixIsland_PatternBush_Text_VancePostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Nash::
	trainerbattle_single TRAINER_YOUNGSTER_NASH, SixIsland_PatternBush_Text_NashIntro, SixIsland_PatternBush_Text_NashDefeat
	msgbox SixIsland_PatternBush_Text_NashPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Cordell::
	trainerbattle_single TRAINER_YOUNGSTER_CORDELL, SixIsland_PatternBush_Text_CordellIntro, SixIsland_PatternBush_Text_CordellDefeat
	msgbox SixIsland_PatternBush_Text_CordellPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Dalia::
	trainerbattle_single TRAINER_LASS_DALIA, SixIsland_PatternBush_Text_DaliaIntro, SixIsland_PatternBush_Text_DaliaDefeat
	msgbox SixIsland_PatternBush_Text_DaliaPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Joana::
	trainerbattle_single TRAINER_LASS_JOANA, SixIsland_PatternBush_Text_JoanaIntro, SixIsland_PatternBush_Text_JoanaDefeat
	msgbox SixIsland_PatternBush_Text_JoanaPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Riley::
	trainerbattle_single TRAINER_CAMPER_RILEY, SixIsland_PatternBush_Text_RileyIntro, SixIsland_PatternBush_Text_RileyDefeat
	msgbox SixIsland_PatternBush_Text_RileyPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Marcy::
	trainerbattle_single TRAINER_PICNICKER_MARCY, SixIsland_PatternBush_Text_MarcyIntro, SixIsland_PatternBush_Text_MarcyDefeat
	msgbox SixIsland_PatternBush_Text_MarcyPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_EventScript_Layton::
	trainerbattle_single TRAINER_RUIN_MANIAC_LAYTON, SixIsland_PatternBush_Text_LaytonIntro, SixIsland_PatternBush_Text_LaytonDefeat
	msgbox SixIsland_PatternBush_Text_LaytonPostBattle, MSGBOX_AUTOCLOSE
	end

SixIsland_PatternBush_Text_BethanyIntro::
	.string "Tengo curiosidad, ¿cómo crias\n"
	.string "POKéMON?$"

SixIsland_PatternBush_Text_BethanyDefeat::
	.string "Crías a tus POKéMON con un\n"
	.string "¡con muchísimo amor!$"

SixIsland_PatternBush_Text_BethanyPostBattle::
	.string "Igual que tu madre te crió\n"
	.string "con amor, tú debes criar\l"
	.string "para tu POKéMON.$"

SixIsland_PatternBush_Text_AllisonIntro::
	.string "Trabajo para preservar la\n"
	.string "la ecología POKéMON de aquí.$"

SixIsland_PatternBush_Text_AllisonDefeat::
	.string "Oh, para alguien tan joven, eres\n"
	.string "¡tremendo!$"

SixIsland_PatternBush_Text_AllisonPostBattle::
	.string "No digo que no debas\n"
	.string "atrapar POKéMON.\p"
	.string "Solo quiero que la gente valore\n"
	.string "POKéMON con cuidado.$"

SixIsland_PatternBush_Text_GarretIntro::
	.string "Atrapé un POKéMON bicho que vive\n"
	.string "¡solo por aquí!$"

SixIsland_PatternBush_Text_GarretDefeat::
	.string "Jeje...\n"
	.string "¿No es genial mi POKéMON?$"

SixIsland_PatternBush_Text_GarretPostBattle::
	.string "Hay una chica cerca del ARBUSTO\n"
	.string "Mide a HERACROSS para ENTRENADORES.$"

SixIsland_PatternBush_Text_JonahIntro::
	.string "Sabes, no me parece correcto\n"
	.string "si no uso POKéMON de tipo bicho.$"

SixIsland_PatternBush_Text_JonahDefeat::
	.string "Está bien, perder es parte de la\n"
	.string "el encanto POKéMON, también.$"

SixIsland_PatternBush_Text_JonahPostBattle::
	.string "Por cierto, “encanto“ es una\n"
	.string "palabra rara si lo piensas.\p"
	.string "¿Como la cáscara de una naranja?\n"
	.string "¿O como una campana sonando?$"

SixIsland_PatternBush_Text_VanceIntro::
	.string "¡Sí, sí, sí!\n"
	.string "¡Mira todos los POKéMON bicho!$"

SixIsland_PatternBush_Text_VanceDefeat::
	.string "Me ganaron mientras estaba\n"
	.string "¡celebrando!$"

SixIsland_PatternBush_Text_VancePostBattle::
	.string "La próxima vez traeré a mi\n"
	.string "hermanito aquí.$"

SixIsland_PatternBush_Text_NashIntro::
	.string "Mira, ¡mira! Hay patrones\n"
	.string "raros en el suelo.$"

SixIsland_PatternBush_Text_NashDefeat::
	.string "¡Súper genial!$"

SixIsland_PatternBush_Text_NashPostBattle::
	.string "Los patrones raros del suelo...\p"
	.string "Se parecen a los patrones de mi\n"
	.string "la ropa de mi abuelo.$"

SixIsland_PatternBush_Text_CordellIntro::
	.string "Seguro que crees que soy solo\n"
	.string "¿no es así, eh?$"

SixIsland_PatternBush_Text_CordellDefeat::
	.string "Apuesto a que piensas que soy débil,\n"
	.string "¿no es así, eh?$"

SixIsland_PatternBush_Text_CordellPostBattle::
	.string "Vaya, la gente del pueblo llega\n"
	.string "tan elegante con sombrero vistoso...\p"
	.string "¿Qué tal si me lo das?$"

SixIsland_PatternBush_Text_DaliaIntro::
	.string "Respira profundo.\n"
	.string "¿No es delicioso el aire?$"

SixIsland_PatternBush_Text_DaliaDefeat::
	.string "Si quieres, puedo enseñarte\n"
	.string "a respirar bien.$"

SixIsland_PatternBush_Text_DaliaPostBattle::
	.string "Primero, exhala.\n"
	.string "Saca todo el aire.\p"
	.string "Cuando ya no puedas exhalar,\n"
	.string "¡inhala el aire limpio!\p"
	.string "¿No es refrescante?$"

SixIsland_PatternBush_Text_JoanaIntro::
	.string "Amo los POKéMON bicho.\n"
	.string "Por eso vengo aquí siempre.\p"
	.string "¿Soy la única chica así?$"

SixIsland_PatternBush_Text_JoanaDefeat::
	.string "Perdí, pero sigo riendo.\n"
	.string "¿Soy la única chica así?$"

SixIsland_PatternBush_Text_JoanaPostBattle::
	.string "Voy a seguir coleccionando\n"
	.string "BUG POKéMON.\p"
	.string "¿Soy la única chica así?$"

SixIsland_PatternBush_Text_RileyIntro::
	.string "Este es un buen lugar.\n"
	.string "Aquí pondré mi carpa.$"

SixIsland_PatternBush_Text_RileyDefeat::
	.string "Me acobardé...$"

SixIsland_PatternBush_Text_RileyPostBattle::
	.string "Voy a observar el cielo nocturno\n"
	.string "para llegar aquí.$"

SixIsland_PatternBush_Text_MarcyIntro::
	.string "¡Oh, qué asco!\n"
	.string "¡Creo que un bicho me picó!$"

SixIsland_PatternBush_Text_MarcyDefeat::
	.string "No fue un bicho.\n"
	.string "Me corté la espinilla con el pasto.$"

SixIsland_PatternBush_Text_MarcyPostBattle::
	.string "Un corte tan pequeño...\n"
	.string "¡Con un poco de saliva se cura!$"

SixIsland_PatternBush_Text_LaytonIntro::
	.string "¿Has notado algo extraño\n"
	.string "por estos rumbos?$"

SixIsland_PatternBush_Text_LaytonDefeat::
	.string "¿Has mirado bien a tu\n"
	.string "alrededor?$"

SixIsland_PatternBush_Text_LaytonPostBattle::
	.string "Hay lugares aquí en PATTERN\n"
	.string "BUSH donde no crece la hierba.\p"
	.string "¿Cuál podría ser la causa de\n"
	.string "un fenómeno así?$"

