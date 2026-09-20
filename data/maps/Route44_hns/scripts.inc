Route44_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route44_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route44_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route44_EventScript_Wilton::
	trainerbattle_single TRAINER_WILTON_HNS, Route44_Text_FisherWilton1Seen, Route44_Text_FisherWilton1Beaten, Route44_EventScript_RegisterWilton
	goto_if_set FLAG_WILTON_HAS_ITEM_HNS, Route44_EventScript_WiltonGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route44_EventScript_RematchWilton
	msgbox Route44_Text_FisherWiltonHugePoliwag, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_RegisterWilton::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route44_Text_WiltonRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WILTON_HNS
	release
	end

Route44_EventScript_RematchWilton::
	trainerbattle_rematch TRAINER_WILTON_HNS, Route44_Text_WiltonRematchIntro, Route44_Text_WiltonRematchDefeat
	msgbox Route44_Text_WiltonPostRematch, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_WiltonGiveItem::
	msgbox Route44_Text_WiltonHasItem, MSGBOX_DEFAULT
	giveitem VAR_WILTON_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route44_EventScript_WiltonNoRoom
	clearflag FLAG_WILTON_HAS_ITEM_HNS
	msgbox Route44_Text_WiltonGaveItem, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_WiltonNoRoom::
	msgbox Route44_Text_WiltonNoRoom, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR_HNS, Route44_Text_FisherEdgarSeen, Route44_Text_FisherEdgarBeaten
	msgbox Route44_Text_FisherEdgarAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Vance::
	trainerbattle_single TRAINER_VANCE_HNS, Route44_Text_BirdKeeperVance1Seen, Route44_Text_BirdKeeperVance1Beaten, Route44_EventScript_RegisterVance
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route44_EventScript_RematchVance
	msgbox Route44_Text_BirdKeeperVanceBirds, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_RegisterVance::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route44_Text_VanceRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VANCE_HNS
	release
	end

Route44_EventScript_RematchVance::
	trainerbattle_rematch TRAINER_VANCE_HNS, Route44_Text_VanceRematchIntro, Route44_Text_VanceRematchDefeat
	msgbox Route44_Text_VancePostRematch, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Phil::
	trainerbattle_single TRAINER_PHIL_HNS, Route44_Text_PsychicPhilSeen, Route44_Text_PsychicPhilBeaten
	msgbox Route44_Text_PsychicPhilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Zach::
	trainerbattle_single TRAINER_ZACH_HNS, Route44_Text_PokemaniacZachSeen, Route44_Text_PokemaniacZachBeaten
	msgbox Route44_Text_PokemaniacZachAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN_HNS, Route44_Text_CooltrainermAllenSeen, Route44_Text_CooltrainermAllenBeaten
	msgbox Route44_Text_CooltrainermAllenAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Cybil::
	trainerbattle_single TRAINER_CYBIL_HNS, Route44_Text_CooltrainerfCybilSeen, Route44_Text_CooltrainerfCybilBeaten
	msgbox Route44_Text_CooltrainerfCybilAfter, MSGBOX_AUTOCLOSE
	end

Route44_EventScript_Sign1::
	msgbox Route44_Text_Sign1, MSGBOX_SIGN
	end

Route44_EventScript_Sign2::
	msgbox Route44_Text_Sign2, MSGBOX_SIGN
	end

Route44_EventScript_Item_MaxRepel::
	finditem ITEM_MAX_REPEL
	end

Route44_EventScript_Item_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route44_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route44_Text_FisherWilton1Seen:
    .string "¡Aack!\p"
    .string "¡Hice que perdiera un POLIWAG!\n"
    .string "¿Qué piensas hacer al respecto?$"

Route44_Text_FisherWilton1Beaten:
    .string "Olvídalo.$"

Route44_Text_FisherWiltonHugePoliwag:
    .string "Ese POLIWAG que escapó...\n"
    .string "era enorme.\p"
    .string "¡Juro que debía medir\n"
    .string "como 5 metros!$"

Route44_Text_WiltonRegister:
    .string "Ese POLIWAG que escapó...\n"
    .string "era enorme.\p"
    .string "¡Juro que debía medir\n"
    .string "como 5 metros!$"

Route44_Text_WiltonRematchIntro:
    .string "¡Aack!\p"
    .string "¡Hice que perdiera un POLIWAG!\n"
    .string "¿Qué piensas hacer al respecto?$"

Route44_Text_WiltonRematchDefeat:
    .string "Olvídalo.$"

Route44_Text_WiltonPostRematch:
    .string "Ese POLIWAG que escapó...\n"
    .string "era enorme.\p"
    .string "¡Juro que debía medir\n"
    .string "como 5 metros!$"

Route44_Text_WiltonHasItem:
    .string "¡Oye! Pesqué algo que\n"
    .string "no es un POKéMON!\p"
    .string "¡Toma, puedes quedártelo!$"

Route44_Text_WiltonGaveItem:
    .string "Te avisaré si\n"
    .string "¡No pesqué nada más!$"

Route44_Text_WiltonNoRoom:
    .string "Hmm, tu MOCHILA está llena.\p"
    .string "Vuelve cuando tengas espacio.$"

Route44_Text_FisherEdgarSeen:
    .string "Pescaré hasta que no pueda más.\p"
    .string "Yo también lucho hasta caer.\p"
    .string "Así es mi relación con mi\n"
    .string "POKéMON.$"

Route44_Text_FisherEdgarBeaten:
    .string "Mmm... Esto no está bien.$"

Route44_Text_FisherEdgarAfter:
    .string "Son 100 victorias y 101 derrotas.\p"
    .string "No lucharé por un tiempo.$"

Route44_Text_BirdKeeperVance1Seen:
    .string "¿Sabes sobre los legendarios\n"
    .string "POKéMON ave?$"

Route44_Text_BirdKeeperVance1Beaten:
    .string "Whew! You're hot stuff.$"

Route44_Text_BirdKeeperVanceBirds:
    .string "ARTICUNO, ZAPDOS y MOLTRES son\n"
    .string "los tres legendarios POKéMON ave.\p"
    .string "He oído que hay otros aves\n"
    .string "legendarias, sin embargo.$"

Route44_Text_VanceRegister:
    .string "ARTICUNO, ZAPDOS y MOLTRES son\n"
    .string "los tres legendarios POKéMON ave.\p"
    .string "He oído que hay otros aves\n"
    .string "legendarias, sin embargo.$"

Route44_Text_VanceRematchIntro:
    .string "¿Sabes sobre los legendarios\n"
    .string "POKéMON ave?$"

Route44_Text_VanceRematchDefeat:
    .string "Whew! You're hot stuff.$"

Route44_Text_VancePostRematch:
    .string "ARTICUNO, ZAPDOS y MOLTRES son\n"
    .string "los tres legendarios POKéMON ave.\p"
    .string "He oído que hay otros aves\n"
    .string "legendarias, sin embargo.$"

Route44_Text_PsychicPhilSeen:
    .string "I'm gonna win, for sure!$"

Route44_Text_PsychicPhilBeaten:
    .string "Arrgh… That's a shocking loss…$"

Route44_Text_PsychicPhilAfter:
    .string "Es importante tener convicción\n"
    .string "de tu lado.$"

Route44_Text_PokemaniacZachSeen:
    .string "¡Haré lo que sea por atrapar\n"
    .string "POKéMON raros!$"

Route44_Text_PokemaniacZachBeaten:
    .string "Oooh, tus POKéMON son muy\n"
    .string "atractivos.$"

Route44_Text_PokemaniacZachAfter:
    .string "Si un POKéMON tiene colores\n"
    .string "inusuales, es más valioso.\p"
    .string "¿Qué? ¿Dices que no es cierto?$"

Route44_Text_CooltrainermAllenSeen:
    .string "Veo que eres un buen entrenador\n"
    .string "solo con mirarte.\p"
    .string "Soy bueno con los POKéMON, y\n"
    .string "veo que tú también lo eres.$"

Route44_Text_CooltrainermAllenBeaten:
    .string "Tch! It's a total loss on my part.$"

Route44_Text_CooltrainermAllenAfter:
    .string "Vaya. Tienes muchas MEDALLAS.\p"
    .string "No me extraña que seas tan fuerte.\p"
    .string "Me pregunto si MORTY, del\n"
    .string "GIMNASIO de CIUDAD IRIS, sigue\p"
    .string "entrenando. Me dio una paliza.$"

Route44_Text_CooltrainerfCybilSeen:
    .string "Pareces fuerte.\p"
    .string "Los buenos ENTRENADORES buscan\n"
    .string "rivales fuertes por instinto.$"

Route44_Text_CooltrainerfCybilBeaten:
    .string "¡No! Esto no sirve para nada.$"

Route44_Text_CooltrainerfCybilAfter:
    .string "Todos mejoramos al vivir\n"
    .string "muchas batallas.\p"
    .string "Luché mucho para ser lo que\n"
    .string "soy hoy: un elite.$"

Route44_Text_Sign1:
    .string "RUTA 44\n"
    .string "CAMINO HIELO ADELANTE$"

Route44_Text_Sign2:
    .string "RUTA 44\p"
    .string "PUEBLO CAOBA - CIUDAD ENDRINO$"

