SootopolisCity_Gym_B1F_MapScripts::
	.byte 0

SootopolisCity_Gym_B1F_EventScript_Andrea::
	trainerbattle_single TRAINER_ANDREA, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy::
	trainerbattle_single TRAINER_CRISSY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna::
	trainerbattle_single TRAINER_BRIANNA, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Connie::
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget::
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia::
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany::
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika::
	trainerbattle_single TRAINER_ANNIKA, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne::
	trainerbattle_single TRAINER_DAPHNE, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro:
	.string "¡Te mostraré las técnicas sublimes\n"
	.string "que aprendí del LÍDER JUAN!$"

SootopolisCity_Gym_B1F_Text_AndreaDefeat:
	.string "Perdóname, JUAN…$"

SootopolisCity_Gym_B1F_Text_AndreaPostBattle:
	.string "Mira lo que pasa si rompes todas\n"
	.string "las baldosas del suelo.$"

SootopolisCity_Gym_B1F_Text_CrissyIntro:
	.string "Viniste hasta aquí, pero no\n"
	.string "podrás ver a JUAN.\p"
	.string "¡No si pierdes contra mí!$"

SootopolisCity_Gym_B1F_Text_CrissyDefeat:
	.string "¡Eres fuerte!\n"
	.string "¡Me dejé engañar por tu apariencia!$"

SootopolisCity_Gym_B1F_Text_CrissyPostBattle:
	.string "Quizás seas lo bastante bueno para\n"
	.string "que JUAN no te derrote de un golpe.$"

SootopolisCity_Gym_B1F_Text_DaphneIntro:
	.string "La vista de JUAN dirigiendo\n"
	.string "una batalla…\p"
	.string "Su belleza me obligó a\n"
	.string "ser ENTRENADOR.$"

SootopolisCity_Gym_B1F_Text_DaphneDefeat:
	.string "Luchaste con más belleza de la\n"
	.string "que yo pude lograr…$"

SootopolisCity_Gym_B1F_Text_DaphnePostBattle:
	.string "La gracia que traes al combate es\n"
	.string "fabulosa.\p"
	.string "Oh… Qué suerte haberte encontrado\n"
	.string "POKéMON.$"

SootopolisCity_Gym_B1F_Text_ConnieIntro:
	.string "Debo enseñarte lo duras que\n"
	.string "pueden ser las batallas.$"

SootopolisCity_Gym_B1F_Text_ConnieDefeat:
	.string "Oh.\n"
	.string "Eres fuerte.$"

SootopolisCity_Gym_B1F_Text_ConniePostBattle:
	.string "Te diré algo bueno.\p"
	.string "Si quieres llegar a JUAN, tienes\n"
	.string "que pisar cada baldosa una vez.$"

SootopolisCity_Gym_B1F_Text_BridgetIntro:
	.string "El GIMNASIO POKéMON de nivel más\n"
	.string "alto de la región de HOENN…\p"
	.string "Es el GIMNASIO de CALAGIRI.$"

SootopolisCity_Gym_B1F_Text_BridgetDefeat:
	.string "¡Qué nivel tan alto tienes!$"

SootopolisCity_Gym_B1F_Text_BridgetPostBattle:
	.string "En vez de conformarte con estar\n"
	.string "en un GIMNASIO fuerte, creo que\l"
	.string "entrenar fuera te hará más fuerte.\l"
	.string "Y sobre todo, parece más divertido.$"

SootopolisCity_Gym_B1F_Text_OliviaIntro:
	.string "Entreno a mis POKéMON junto con\n"
	.string "JUAN.\p"
	.string "No creas que soy un debilucho.$"

SootopolisCity_Gym_B1F_Text_OliviaDefeat:
	.string "Me han golpeado…$"

SootopolisCity_Gym_B1F_Text_OliviaPostBattle:
	.string "Creo que tienes potencial.\n"
	.string "¿Por qué no te quedas a entrenar?$"

SootopolisCity_Gym_B1F_Text_TiffanyIntro:
	.string "Un deslizamiento fluido sobre el hielo\n"
	.string "sin cruzar ninguna línea...\p"
	.string "¡Un ENTRENADOR haciendo eso\n"
	.string "sería elegantemente hermoso!$"

SootopolisCity_Gym_B1F_Text_TiffanyDefeat:
	.string "¡Vaya, ¡perdón?!$"

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle:
	.string "Es obvio, pero lo fuerte que seas\n"
	.string "como ENTRENADOR no tiene nada que ver\l"
	.string "con tu edad.$"

SootopolisCity_Gym_B1F_Text_BethanyIntro:
	.string "Con mis POKéMON, el tiempo...\n"
	.string "pasa volando antes de decir ¡Ups!$"

SootopolisCity_Gym_B1F_Text_BethanyDefeat:
	.string "Oops!$"

SootopolisCity_Gym_B1F_Text_BethanyPostBattle:
	.string "Quisiera olvidar las causas perdidas\n"
	.string "antes de que pueda decir ¡Ups!$"

SootopolisCity_Gym_B1F_Text_AnnikaIntro:
	.string "Puedo luchar con POKéMON muy raros\n"
	.string "si así lo deseas.$"

SootopolisCity_Gym_B1F_Text_AnnikaDefeat:
	.string "¡Vaya! ¿Ya miraste bien\n"
	.string "a mis POKéMON?$"

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle:
	.string "Vine a este GIMNASIO porque JUAN\n"
	.string "elogió a mis queridos POKéMON.\p"
	.string "Si tan solo hubiera conocido a JUAN\n"
	.string "cuando era más joven...$"

SootopolisCity_Gym_B1F_Text_BriannaIntro:
	.string "Jejeje…\n"
	.string "Tu mirada seria es encantadora.$"

SootopolisCity_Gym_B1F_Text_BriannaDefeat:
	.string "Vaya, vaya.\n"
	.string "Fui demasiado blanda contigo.$"

SootopolisCity_Gym_B1F_Text_BriannaPostBattle:
	.string "No pudiste tocar a JUAN,\n"
	.string "Estoy segura. Jiji…$"

