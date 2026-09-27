Route38_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route38_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route38_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route38_EventScript_Toby::
	trainerbattle_single TRAINER_TOBY_HNS, Route38_Text_BirdKeeperTobySeen, Route38_Text_BirdKeeperTobyBeaten
	msgbox Route38_Text_BirdKeeperTobyAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Chad::
	trainerbattle_single TRAINER_CHAD_HNS, Route38_Text_SchoolboyChad1Seen, Route38_Text_SchoolboyChad1Beaten, Route38_EventScript_RegisterChad
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route38_EventScript_RematchChad
	msgbox Route38_Text_SchoolboyChadAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_RegisterChad::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route38_Text_ChadRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CHAD_HNS
	release
	end

Route38_EventScript_RematchChad::
	trainerbattle_rematch TRAINER_CHAD_HNS, Route38_Text_ChadRematchIntro, Route38_Text_ChadRematchDefeat
	msgbox Route38_Text_ChadPostRematch, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Dana::
	trainerbattle_single TRAINER_DANA_HNS, Route38_Text_LassDana1Seen, Route38_Text_LassDana1Beaten, Route38_EventScript_RegisterDana
	goto_if_set FLAG_DANA_HAS_ITEM_HNS, Route38_EventScript_DanaGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route38_EventScript_RematchDana
	msgbox Route38_Text_LassDanaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_RegisterDana::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route38_Text_DanaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DANA_HNS
	release
	end

Route38_EventScript_RematchDana::
	trainerbattle_rematch TRAINER_DANA_HNS, Route38_Text_DanaRematchIntro, Route38_Text_DanaRematchDefeat
	msgbox Route38_Text_DanaPostRematch, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_DanaGiveItem::
	msgbox Route38_Text_DanaHasItem, MSGBOX_DEFAULT
	giveitem VAR_DANA_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route38_EventScript_DanaNoRoom
	clearflag FLAG_DANA_HAS_ITEM_HNS
	msgbox Route38_Text_DanaGaveItem, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_DanaNoRoom::
	msgbox Route38_Text_DanaNoRoom, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_HNS, Route38_Text_BeautyValerieSeen, Route38_Text_BeautyValerieBeaten
	msgbox Route38_Text_BeautyValerieAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Harry::
	trainerbattle_single TRAINER_HARRY_HNS, Route38_Text_SailorHarrySeen, Route38_Text_SailorHarryBeaten
	msgbox Route38_Text_SailorHarryAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA_HNS, Route38_Text_BeautyOliviaSeen, Route38_Text_BeautyOliviaBeaten
	msgbox Route38_Text_BeautyOliviaAfter, MSGBOX_AUTOCLOSE
	end

Route38_EventScript_Sign1::
	lock
	msgbox Route38_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Sign2::
	lock
	msgbox Route38_Text_WaterSign, MSGBOX_SIGN
	closemessage
	release
	end

Route38_EventScript_Item_LaxIncense::
	finditem ITEM_LAX_INCENSE
	end

Route38_Text_BirdKeeperTobySeen:
	.string "¡Vuela alto en el cielo,\n"
	.string "mi querido POKéMON ave!$"

Route38_Text_BirdKeeperTobyBeaten:
	.string "Siento que podría volar\n"
	.string "lejos ahora mismo.$"

Route38_Text_BirdKeeperTobyAfter:
	.string "Iré a CIUDAD ORQUIDEA\n"
	.string "para enseñar a VUELO.$"

Route38_Text_SchoolboyChad1Seen:
	.string "Dejadme intentar algo\n"
	.string "que aprendí hoy.$"

Route38_Text_SchoolboyChad1Beaten:
	.string "No estudié lo suficiente,\n"
	.string "supongo.$"

Route38_Text_SchoolboyChadAfter:
	.string "Tengo que hacer tantos\n"
	.string "exámenes que no tengo tiempo\l"
	.string "hora de POKéMON.\p"
	.string "Así que cuando juego,\n"
	.string "Me concentro mucho.$"

Route38_Text_ChadRegister:
	.string "Tengo que hacer tantos\n"
	.string "exámenes que no tengo tiempo\l"
	.string "hora de POKéMON.\p"
	.string "Así que cuando juego,\n"
	.string "Me concentro mucho.$"

Route38_Text_ChadRematchIntro:
	.string "Dejadme intentar algo\n"
	.string "que aprendí hoy.$"

Route38_Text_ChadRematchDefeat:
	.string "No estudié lo suficiente,\n"
	.string "supongo.$"

Route38_Text_ChadPostRematch:
	.string "Tengo que hacer tantos\n"
	.string "exámenes que no tengo tiempo\l"
	.string "hora de POKéMON.\p"
	.string "Así que cuando juego,\n"
	.string "Me concentro mucho.$"

Route38_Text_LassDana1Seen:
	.string "Pareces ser bueno en eso.\n"
	.string "POKéMON planta.\p"
	.string "Si es así, ¿qué tal si\n"
	.string "¿me das algunos consejos?$"

Route38_Text_LassDana1Beaten:
	.string "Ya veo. Así puedes luchar\nde esa forma.$"

Route38_Text_LassDanaAfter:
	.string "¡Sé algo bueno!\pLa leche de MOOMOO FARM\nes famosa por su sabor.$"

Route38_Text_BeautyValerieSeen:
	.string "¡Hola! Qué lindo eres\n"
	.string "¡Entrenador!\p"
	.string "¿Puedo ver tus POKéMON?$"

Route38_Text_BeautyValerieBeaten:
	.string "Me alegra haber podido ver\n"
	.string "a tu POKéMON!$"

Route38_Text_BeautyValerieAfter:
	.string "Cuando veo POKéMON, parece\n"
	.string "que mis nervios se calman.$"

Route38_Text_SailorHarrySeen:
	.string "He estado en el extranjero,\n"
	.string "así que conozco todo tipo de\l"
	.string "POKéMON!$"

Route38_Text_SailorHarryBeaten:
	.string "¡Tu habilidad es de nivel mundial!$"

Route38_Text_SailorHarryAfter:
	.string "Gente de todo el mundo vive\n"
	.string "felizmente con sus POKéMON.\l"
	.string "POKéMON.$"

Route38_Text_BeautyOliviaSeen:
	.string "¿No crees que mis POKéMON\n"
	.string "y yo somos hermosos?$"

Route38_Text_BeautyOliviaBeaten:
	.string "Tomamos LECHE MOOMOO todos\nlos días.$"

Route38_Text_BeautyOliviaAfter:
	.string "La LECHE MOOMOO es buena\npara la belleza y la salud,\ppero, por desgracia, solo\nvenden una botella a la vez.$"

Route38_Text_Sign:
	.string "RUTA 38\p"
	.string "CIUDAD OLIVO - CIUDAD IRIS$"

Route38_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Si un POKéMON intenta\n"
	.string "evolucionar, puedes detenerlo.\p"
	.string "Pulsa el Botón B durante la\n"
	.string "evolución para cancelarla.\p"
	.string "Eso asusta al POKéMON\n"
	.string "y detiene su evolución.$"


Route38_Text_WaterSign:
	.string "PROHIBIDO NADAR O PESCAR.\n"
	.string "AGUA SOLO PARA EL CULTIVO.\p"
	.string "-CONSEJO DE CIUDAD IRIS$"

Route38_Text_DanaRegister:
	.string "¡Sé algo bueno!\pLa leche de MOOMOO FARM\nes famosa por su sabor.$"

Route38_Text_DanaRematchIntro:
	.string "Pareces ser bueno en eso.\n"
	.string "POKéMON planta.\p"
	.string "Si es así, ¿qué tal si\n"
	.string "¿me das algunos consejos?$"

Route38_Text_DanaRematchDefeat:
	.string "Ya veo. Así puedes luchar\nde esa forma.$"

Route38_Text_DanaPostRematch:
	.string "¡Sé algo bueno!\pLa leche de MOOMOO FARM\nes famosa por su sabor.$"

Route38_Text_DanaHasItem:
	.string "¡Oye! Encontré algo\ninteresante!\pToma, ¡es para ti!$"

Route38_Text_DanaGaveItem:
	.string "¡Te aviso si encuentro\nalgo más!$"

Route38_Text_DanaNoRoom:
	.string "Hmm, tu BOLSA está llena.\p"
	.string "Vuelve cuando tengas espacio.$"
