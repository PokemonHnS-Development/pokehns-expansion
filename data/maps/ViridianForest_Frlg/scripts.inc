ViridianForest_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianForest_OnTransition
	.byte 0

ViridianForest_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_VIRIDIAN_FOREST
	end

ViridianForest_EventScript_Youngster::
	msgbox ViridianForest_Text_FriendsItchingToBattle, MSGBOX_NPC
	end

ViridianForest_EventScript_Boy::
	msgbox ViridianForest_Text_RanOutOfPokeBalls, MSGBOX_NPC
	end

ViridianForest_EventScript_TrainerTips1::
	msgbox ViridianForest_Text_AvoidGrassyAreasWhenWeak, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips2::
	msgbox ViridianForest_Text_UseAntidoteForPoison, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips3::
	msgbox ViridianForest_Text_ContactOakViaPCToRatePokedex, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips4::
	msgbox ViridianForest_Text_CantCatchOwnedMons, MSGBOX_SIGN
	end

ViridianForest_EventScript_TrainerTips5::
	msgbox ViridianForest_Text_WeakenMonsBeforeCapture, MSGBOX_SIGN
	end

ViridianForest_EventScript_ExitSign::
	msgbox ViridianForest_Text_LeavingViridianForest, MSGBOX_SIGN
	end

ViridianForest_EventScript_Rick::
	trainerbattle_single TRAINER_BUG_CATCHER_RICK, ViridianForest_Text_RickIntro, ViridianForest_Text_RickDefeat
	msgbox ViridianForest_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Doug::
	trainerbattle_single TRAINER_BUG_CATCHER_DOUG, ViridianForest_Text_DougIntro, ViridianForest_Text_DougDefeat
	msgbox ViridianForest_Text_DougPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Sammy::
	trainerbattle_single TRAINER_BUG_CATCHER_SAMMY, ViridianForest_Text_SammyIntro, ViridianForest_Text_SammyDefeat
	msgbox ViridianForest_Text_SammyPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Anthony::
	trainerbattle_single TRAINER_BUG_CATCHER_ANTHONY, ViridianForest_Text_AnthonyIntro, ViridianForest_Text_AnthonyDefeat
	msgbox ViridianForest_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_EventScript_Charlie::
	trainerbattle_single TRAINER_BUG_CATCHER_CHARLIE, ViridianForest_Text_CharlieIntro, ViridianForest_Text_CharlieDefeat
	msgbox ViridianForest_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

ViridianForest_Text_FriendsItchingToBattle::
	.string "Vine aquí con unos amigos a\n"
	.string "¡atrapar BICHOS POKéMON!\p"
	.string "Todos están ansiosos por entrar\n"
	.string "¡algunas batallas POKéMON!$"

ViridianForest_Text_RickIntro::
	.string "¡Oye! ¡Tienes POKéMON!\n"
	.string "¡Vamos!\l"
	.string "¡Vamos a pelear contra ellos!$"

ViridianForest_Text_RickDefeat::
	.string "¡No!\n¡CATERPIE no puede con esto!$"

ViridianForest_Text_RickPostBattle::
	.string "¡Shh! Vas a espantar a los bichos.\n"
	.string "En otra ocasión, ¿sí?$"

ViridianForest_Text_DougIntro::
	.string "Yo!\n"
	.string "No puedes rockear si eres un\l"
	.string "POKéMON TRAINER!$"

ViridianForest_Text_DougDefeat::
	.string "¿Eh?\n"
	.string "¡Me quedé sin POKéMON!$"

ViridianForest_Text_DougPostBattle::
	.string "¡Qué asco! Me voy a\n"
	.string "¡atrapar algunos más fuertes!$"

ViridianForest_Text_SammyIntro::
	.string "¡Oye, espérate!\n"
	.string "¿Cuál es la prisa? ¿A qué corres?$"

ViridianForest_Text_SammyDefeat::
	.string "¡Me rindo!\n"
	.string "¡Eres bueno en esto!$"

ViridianForest_Text_SammyPostBattle::
	.string "A veces puedes encontrar cosas\n"
	.string "hasta los cimientos.\p"
	.string "Busco las cosas que\n"
	.string "se me cayeron. ¿Me ayudas?$"

ViridianForest_Text_AnthonyIntro::
	.string "Puede que sea pequeño, pero no me\n"
	.string "gustará si me tratas con suavidad!$"

ViridianForest_Text_AnthonyDefeat::
	.string "Ay, qué mal.\n"
	.string "Nada me salió bien.$"

ViridianForest_Text_AnthonyPostBattle::
	.string "Perdí parte de mi mesada...$"

ViridianForest_Text_CharlieIntro::
	.string "¿Sabías que los POKéMON evolucionan?$"

ViridianForest_Text_CharlieDefeat::
	.string "Oh!\n"
	.string "¡Perdí!$"

ViridianForest_Text_CharliePostBattle::
	.string "Los POKéMON bicho evolucionan rápido.\n"
	.string "¡Son muy divertidos!$"

ViridianForest_Text_RanOutOfPokeBalls::
	.string "Estaba lanzando POKé BALLS para\n"
	.string "atrapar POKéMON, y se me acabaron.\p"
	.string "Por eso nunca puedes tener demasiados\n"
	.string "POKé BALLS.$"

ViridianForest_Text_AvoidGrassyAreasWhenWeak::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Si tus POKéMON son débiles y\n"
	.string "quieres evitar batallas, aléjate\l"
	.string "de las zonas de hierba!$"

ViridianForest_Text_UseAntidoteForPoison::
	.string "Para el veneno, usa ANTÍDOTO!\n"
	.string "¡En las TIENDAS POKéMON!$"

ViridianForest_Text_ContactOakViaPCToRatePokedex::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Contacta al PROF. OAK por PC\n"
	.string "¡haz que evalúen tu POKéDEX!$"

ViridianForest_Text_CantCatchOwnedMons::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "No puedes atrapar un POKéMON que\n"
	.string "pertenece a otra persona.\p"
	.string "Lanza POKé BALLS solo a POKéMON\n"
	.string "salvajes para atraparlos!$"

ViridianForest_Text_WeakenMonsBeforeCapture::
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Debilita al POKéMON antes de\n"
	.string "¡intentar capturarlo!\p"
	.string "¡Si están sanos, pueden escapar!$"

ViridianForest_Text_LeavingViridianForest::
	.string "SALIENDO DEL BOSQUE VERIDIAN\n"
	.string "CIUDAD PLATEADA CERCA$"

