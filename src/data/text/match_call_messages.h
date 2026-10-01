#if IS_HNS
// HnS rematch trainer check page text - currently unused (check page disabled).
// Rematch slot → HnS trainer mapping kept here for reference if re-enabled.
// REMATCH_ROSE         = Joey (Youngster, Route 30)
// REMATCH_ANDRES       = Wade (Bug Catcher, Route 31)
// REMATCH_DUSTY        = Ralph (Fisherman, Route 32)
// REMATCH_LOLA         = Liz (Picnicker, Route 32)
// REMATCH_RICKY        = Anthony (Hiker, Route 33)
// REMATCH_LILA_AND_ROY = Todd (Camper, Route 34)
// REMATCH_CRISTIN      = Gina (Picnicker, Route 34)
// REMATCH_BROOKE       = Irwin (Juggler, Route 35)
// REMATCH_WILTON       = Arnie (Bug Catcher, Route 35)
// REMATCH_VALERIE      = Alan (School Kid, Route 36)
// REMATCH_CINDY        = Dana (Lass, Route 38)
// REMATCH_THALIA       = Chad (School Kid, Route 38)
// REMATCH_JESSICA      = Derek (Pokefan, Route 39)
// REMATCH_WINSTON      = Tully (Fisherman, Route 42)
// REMATCH_STEVE        = Brent (Pokemaniac, Route 43)
// REMATCH_TONY         = Tiffany (Picnicker, Route 43)
// REMATCH_NOB          = Vance (Bird Keeper, Route 44)
// REMATCH_KOJI         = Wilton (Fisherman, Route 44)
// REMATCH_FERNANDO     = Kenji (Black Belt, Route 45)
// REMATCH_DALTON       = Parry (Hiker, Route 45)
// REMATCH_BERNIE       = Erin (Picnicker, Route 46)
// REMATCH_ETHAN        = Jack (School Kid, National Park)
// REMATCH_JOHN_AND_JAY = Beverly (Parasol Lady, National Park)
// REMATCH_JEFFREY      = Huey (Sailor, Lighthouse)
// REMATCH_CAMERON      = Gaven (Cooltrainer, Route 26)
// REMATCH_JACKI        = Beth (Cooltrainer, Route 26)
// REMATCH_WALTER       = Jose (Bird Keeper, Route 27)
// REMATCH_KAREN        = Reena (Cooltrainer, Route 27)
// Crystal phone text reference: pokecrystal/data/phone/text/<name>_caller.asm
#else
const u8 gText_MatchCallAromaLady_Rose_Strategy[] = _("Becalm fighting emotions.");
const u8 gText_MatchCallAromaLady_Rose_Pokemon[] = _("Fragrant GRASS POKéMON.");
const u8 gText_MatchCallAromaLady_Rose_Intro1[] = _("Aromas relajantes que sanan");
const u8 gText_MatchCallAromaLady_Rose_Intro2[] = _("el cuerpo y la mente.");

const u8 gText_MatchCallRuinManiac_Andres_Strategy[] = _("No soy muy bueno en esto.");
const u8 gText_MatchCallRuinManiac_Andres_Pokemon[] = _("Ruin-exploration partners.");
const u8 gText_MatchCallRuinManiac_Andres_Intro1[] = _("Busco ruinas y reliquias");
const u8 gText_MatchCallRuinManiac_Andres_Intro2[] = _("bajo el mar.");

const u8 gText_MatchCallRuinManiac_Dusty_Strategy[] = _("¡Aplasta con poder!");
const u8 gText_MatchCallRuinManiac_Dusty_Pokemon[] = _("Craggy ROCK POKéMON.");
const u8 gText_MatchCallRuinManiac_Dusty_Intro1[] = _("En busca de sabiduría");
const u8 gText_MatchCallRuinManiac_Dusty_Intro2[] = _("antigua, recorro el mundo.");

const u8 gText_MatchCallTuber_Lola_Strategy[] = _("¡Me esforzaré al máximo");
const u8 gText_MatchCallTuber_Lola_Pokemon[] = _("Good swimmer POKéMON.");
const u8 gText_MatchCallTuber_Lola_Intro1[] = _("I wish I could swim without");
const u8 gText_MatchCallTuber_Lola_Intro2[] = _("using an inner tube.");

const u8 gText_MatchCallTuber_Ricky_Strategy[] = _("I don't know. I'll try hard.");
const u8 gText_MatchCallTuber_Ricky_Pokemon[] = _("WATER POKéMON are buddies.");
const u8 gText_MatchCallTuber_Ricky_Intro1[] = _("No es que no sepa nadar.");
const u8 gText_MatchCallTuber_Ricky_Intro2[] = _("I just like my inner tube.");

const u8 gText_MatchCallSisAndBro_LilaAndRoy_Strategy[] = _("Nos repartimos las tareas.");
const u8 gText_MatchCallSisAndBro_LilaAndRoy_Pokemon[] = _("We like friendly POKéMON.");
const u8 gText_MatchCallSisAndBro_LilaAndRoy_Intro1[] = _("We enjoy POKéMON together");
const u8 gText_MatchCallSisAndBro_LilaAndRoy_Intro2[] = _("como hermana y hermano!");

const u8 gText_MatchCallCooltrainer_Cristin_Strategy[] = _("¡Termino con movimientos de poder!");
const u8 gText_MatchCallCooltrainer_Cristin_Pokemon[] = _("Una mezcla de tipos.");
const u8 gText_MatchCallCooltrainer_Cristin_Intro1[] = _("Quiero ser el mejor");
const u8 gText_MatchCallCooltrainer_Cristin_Intro2[] = _("TRAINER!");

const u8 gText_MatchCallCooltrainer_Brooke_Strategy[] = _("Explota la debilidad del rival.");
const u8 gText_MatchCallCooltrainer_Brooke_Pokemon[] = _("El equilibrio es clave.");
const u8 gText_MatchCallCooltrainer_Brooke_Intro1[] = _("Mi meta es convertirme en el");
const u8 gText_MatchCallCooltrainer_Brooke_Intro2[] = _("POKéMON CHAMPION.");

const u8 gText_MatchCallCooltrainer_Wilton_Strategy[] = _("Desestabiliza al rival.");
const u8 gText_MatchCallCooltrainer_Wilton_Pokemon[] = _("Type doesn't matter.");
const u8 gText_MatchCallCooltrainer_Wilton_Intro1[] = _("Soy un alumno destacado del");
const u8 gText_MatchCallCooltrainer_Wilton_Intro2[] = _("TRAINER'S SCHOOL.");

const u8 gText_MatchCallHexManiac_Valerie_Strategy[] = _("Slow, steady suffering.");
const u8 gText_MatchCallHexManiac_Valerie_Pokemon[] = _("Da miedo de noche.");
const u8 gText_MatchCallHexManiac_Valerie_Intro1[] = _("Veo cosas que otros no");
const u8 gText_MatchCallHexManiac_Valerie_Intro2[] = _("can't see...");

const u8 gText_MatchCallLady_Cindy_Strategy[] = _("Todo vale para ganar.");
const u8 gText_MatchCallLady_Cindy_Pokemon[] = _("¡Tipo precioso!");
const u8 gText_MatchCallLady_Cindy_Intro1[] = _("Tengo una piscina especial para");
const u8 gText_MatchCallLady_Cindy_Intro2[] = _("my POKéMON at home.");

const u8 gText_MatchCallBeauty_Thalia_Strategy[] = _("You'll fall under my spell!");
const u8 gText_MatchCallBeauty_Thalia_Pokemon[] = _("Tipo AGUA maduro.");
const u8 gText_MatchCallBeauty_Thalia_Intro1[] = _("Sueño con navegar por");
const u8 gText_MatchCallBeauty_Thalia_Intro2[] = _("el mundo en un lujoso crucero.");

const u8 gText_MatchCallBeauty_Jessica_Strategy[] = _("I'll lead you astray.");
const u8 gText_MatchCallBeauty_Jessica_Pokemon[] = _("Lindo, claro que sí.");
const u8 gText_MatchCallBeauty_Jessica_Intro1[] = _("Me encanta la ZONA SAFARI.");
const u8 gText_MatchCallBeauty_Jessica_Intro2[] = _("Parece que acabo alli.");

const u8 gText_MatchCallRichBoy_Winston_Strategy[] = _("¿Estrategia? ¿Quien la necesita?");
const u8 gText_MatchCallRichBoy_Winston_Pokemon[] = _("¡Gasté mucho dinero en él!");
const u8 gText_MatchCallRichBoy_Winston_Intro1[] = _("Yo, siendo rico, duermo en");
const u8 gText_MatchCallRichBoy_Winston_Intro2[] = _("custom POKéMON bed.");

const u8 gText_MatchCallPokeManiac_Steve_Strategy[] = _("Derriba con fuerza.");
const u8 gText_MatchCallPokeManiac_Steve_Pokemon[] = _("Tarde toda la noche en atraparlo.");
const u8 gText_MatchCallPokeManiac_Steve_Intro1[] = _("Grande, fuerte y musculoso");
const u8 gText_MatchCallPokeManiac_Steve_Intro2[] = _("Los POKéMON son lo mejor...");

const u8 gText_MatchCallSwimmer_Tony_Strategy[] = _("¡Embestida a toda velocidad!");
const u8 gText_MatchCallSwimmer_Tony_Pokemon[] = _("¡Tipo AGUA funky!");
const u8 gText_MatchCallSwimmer_Tony_Intro1[] = _("Si no puedo estar nadando,");
const u8 gText_MatchCallSwimmer_Tony_Intro2[] = _("I'll be pumping weights.");

const u8 gText_MatchCallBlackBelt_Nob_Strategy[] = _("Grand slam pummeling!");
const u8 gText_MatchCallBlackBelt_Nob_Pokemon[] = _("Tipo LUCHA.");
const u8 gText_MatchCallBlackBelt_Nob_Intro1[] = _("No es por presumir, pero puedo");
const u8 gText_MatchCallBlackBelt_Nob_Intro2[] = _("ten roof tiles!");

const u8 gText_MatchCallBlackBelt_Koji_Strategy[] = _("¡Vea el poder del karate!");
const u8 gText_MatchCallBlackBelt_Koji_Pokemon[] = _("¡Mis compañeros de entreno!");
const u8 gText_MatchCallBlackBelt_Koji_Intro1[] = _("Hablemos de asuntos del");
const u8 gText_MatchCallBlackBelt_Koji_Intro2[] = _("¡el mundo con los puños!");

const u8 gText_MatchCallGuitarist_Fernando_Strategy[] = _("¡Roca con sonidos geniales!");
const u8 gText_MatchCallGuitarist_Fernando_Pokemon[] = _("¡Combo eléctrico y sonoro!");
const u8 gText_MatchCallGuitarist_Fernando_Intro1[] = _("My compositions will shock");
const u8 gText_MatchCallGuitarist_Fernando_Intro2[] = _("y te aturdirá!");

const u8 gText_MatchCallGuitarist_Dalton_Strategy[] = _("I'll electrify you!");
const u8 gText_MatchCallGuitarist_Dalton_Pokemon[] = _("They're ELECTRIC!");
const u8 gText_MatchCallGuitarist_Dalton_Intro1[] = _("Quiero hacer llorar a la gente");
const u8 gText_MatchCallGuitarist_Dalton_Intro2[] = _("con canciones de mi corazón.");

const u8 gText_MatchCallKindler_Bernie_Strategy[] = _("¡Todo a arder!");
const u8 gText_MatchCallKindler_Bernie_Pokemon[] = _("Burn-inducing POKéMON.");
const u8 gText_MatchCallKindler_Bernie_Intro1[] = _("Cuando enciendes una fogata,");
const u8 gText_MatchCallKindler_Bernie_Intro2[] = _("be sure there's some water.");

const u8 gText_MatchCallCamper_Ethan_Strategy[] = _("¡Aguanta y sé tenaz!");
const u8 gText_MatchCallCamper_Ethan_Pokemon[] = _("I'll raise any POKéMON.");
const u8 gText_MatchCallCamper_Ethan_Intro1[] = _("POKéMON raised in the wild");
const u8 gText_MatchCallCamper_Ethan_Intro2[] = _("grow strong!");

const u8 gText_MatchCallOldCouple_JohnAndJay_Strategy[] = _("Nuestro amor nos hace vencer.");
const u8 gText_MatchCallOldCouple_JohnAndJay_Pokemon[] = _("Los tenemos desde hace años.");
const u8 gText_MatchCallOldCouple_JohnAndJay_Intro1[] = _("Married 50 years, we've");
const u8 gText_MatchCallOldCouple_JohnAndJay_Intro2[] = _("devotedly raised POKéMON.");

const u8 gText_MatchCallBugManiac_Jeffrey_Strategy[] = _("¡Atacar en oleadas!");
const u8 gText_MatchCallBugManiac_Jeffrey_Pokemon[] = _("BUG POKéMON are cool.");
const u8 gText_MatchCallBugManiac_Jeffrey_Intro1[] = _("Voy al bosque todos los");
const u8 gText_MatchCallBugManiac_Jeffrey_Intro2[] = _("day to catch BUG POKéMON.");

const u8 gText_MatchCallPsychic_Cameron_Strategy[] = _("¡Aturdir y confundir!");
const u8 gText_MatchCallPsychic_Cameron_Pokemon[] = _("Los de poderes raros.");
const u8 gText_MatchCallPsychic_Cameron_Intro1[] = _("I can see through exactly");
const u8 gText_MatchCallPsychic_Cameron_Intro2[] = _("lo que estás pensando!");

const u8 gText_MatchCallPsychic_Jacki_Strategy[] = _("Lucha a tope.");
const u8 gText_MatchCallPsychic_Jacki_Pokemon[] = _("POKéMON of many mysteries.");
const u8 gText_MatchCallPsychic_Jacki_Intro1[] = _("Cuando hablamos, yo estaba muy");
const u8 gText_MatchCallPsychic_Jacki_Intro2[] = _("using telepathy.");

const u8 gText_MatchCallGentleman_Walter_Strategy[] = _("Sereno y con calma.");
const u8 gText_MatchCallGentleman_Walter_Pokemon[] = _("POKéMON of distinction.");
const u8 gText_MatchCallGentleman_Walter_Intro1[] = _("Disfrutamos un té");
const u8 gText_MatchCallGentleman_Walter_Intro2[] = _("cada día. Es importado.");

const u8 gText_MatchCallSchoolKid_Karen_Strategy[] = _("Peleo con la cabeza.");
const u8 gText_MatchCallSchoolKid_Karen_Pokemon[] = _("I love any kind of POKéMON!");
const u8 gText_MatchCallSchoolKid_Karen_Intro1[] = _("My daddy gives me spending");
const u8 gText_MatchCallSchoolKid_Karen_Intro2[] = _("money if I ace a test.");

const u8 gText_MatchCallSchoolKid_Jerry_Strategy[] = _("My knowledge rules!");
const u8 gText_MatchCallSchoolKid_Jerry_Pokemon[] = _("Any smart POKéMON!");
const u8 gText_MatchCallSchoolKid_Jerry_Intro1[] = _("I want to be a POKéMON");
const u8 gText_MatchCallSchoolKid_Jerry_Intro2[] = _("investigador en el futuro.");

const u8 gText_MatchCallSrAndJr_AnnaAndMeg_Strategy[] = _("Primero lo discutimos.");
const u8 gText_MatchCallSrAndJr_AnnaAndMeg_Pokemon[] = _("POKéMON que nos gustan a ambos.");
const u8 gText_MatchCallSrAndJr_AnnaAndMeg_Intro1[] = _("Somos veterano y novato.");
const u8 gText_MatchCallSrAndJr_AnnaAndMeg_Intro2[] = _("students into POKéMON!");

const u8 gText_MatchCallPokefan_Isabel_Strategy[] = _("¡Ánimo, queridos!");
const u8 gText_MatchCallPokefan_Isabel_Pokemon[] = _("I have no likes or dislikes.");
const u8 gText_MatchCallPokefan_Isabel_Intro1[] = _("Mientras compro la cena,");
const u8 gText_MatchCallPokefan_Isabel_Intro2[] = _("también peleo.");

const u8 gText_MatchCallPokefan_Miguel_Strategy[] = _("¡Lucho con amor!");
const u8 gText_MatchCallPokefan_Miguel_Pokemon[] = _("A POKéMON raised with love!");
const u8 gText_MatchCallPokefan_Miguel_Intro1[] = _("Es importante formarse");
const u8 gText_MatchCallPokefan_Miguel_Intro2[] = _("confianza con tu POKéMON.");

const u8 gText_MatchCallExpert_Timothy_Strategy[] = _("¡Veo tus movimientos!");
const u8 gText_MatchCallExpert_Timothy_Pokemon[] = _("La esencia de la LUCHA.");
const u8 gText_MatchCallExpert_Timothy_Intro1[] = _("No estoy listo para ceder");
const u8 gText_MatchCallExpert_Timothy_Intro2[] = _("a los jóvenes aún!");

const u8 gText_MatchCallExpert_Shelby_Strategy[] = _("Attack while defending.");
const u8 gText_MatchCallExpert_Shelby_Pokemon[] = _("El tipo LUCHA.");
const u8 gText_MatchCallExpert_Shelby_Intro1[] = _("Being old, I have my own");
const u8 gText_MatchCallExpert_Shelby_Intro2[] = _("estilo de combate.");

const u8 gText_MatchCallYoungster_Calvin_Strategy[] = _("Hago lo que puedo.");
const u8 gText_MatchCallYoungster_Calvin_Pokemon[] = _("Uso varios tipos.");
const u8 gText_MatchCallYoungster_Calvin_Intro1[] = _("Seguiré esforzándome");
const u8 gText_MatchCallYoungster_Calvin_Intro2[] = _("until I beat a GYM LEADER.");

const u8 gText_MatchCallFisherman_Elliot_Strategy[] = _("Lucho con paciencia.");
const u8 gText_MatchCallFisherman_Elliot_Pokemon[] = _("WATER POKéMON to battle!");
const u8 gText_MatchCallFisherman_Elliot_Intro1[] = _("Soy el único en el mundo que");
const u8 gText_MatchCallFisherman_Elliot_Intro2[] = _("catch a huge POKéMON!");

const u8 gText_MatchCallTriathlete_Isaiah_Strategy[] = _("¡Aprovecha el entorno!");
const u8 gText_MatchCallTriathlete_Isaiah_Pokemon[] = _("¡Gloria al tipo AGUA!");
const u8 gText_MatchCallTriathlete_Isaiah_Intro1[] = _("I won't be beaten by some");
const u8 gText_MatchCallTriathlete_Isaiah_Intro2[] = _("beach bum SWIMMER!");

const u8 gText_MatchCallTriathlete_Maria_Strategy[] = _("Speed above all!");
const u8 gText_MatchCallTriathlete_Maria_Pokemon[] = _("I use a speedy POKéMON.");
const u8 gText_MatchCallTriathlete_Maria_Intro1[] = _("Un maratón es un reto");
const u8 gText_MatchCallTriathlete_Maria_Intro2[] = _("contra ti mismo.");

const u8 gText_MatchCallTriathlete_Abigail_Strategy[] = _("La defensa es clave.");
const u8 gText_MatchCallTriathlete_Abigail_Pokemon[] = _("My POKéMON is solid.");
const u8 gText_MatchCallTriathlete_Abigail_Intro1[] = _("Empecé por la dieta,");
const u8 gText_MatchCallTriathlete_Abigail_Intro2[] = _("pero me metí de lleno.");

const u8 gText_MatchCallTriathlete_Dylan_Strategy[] = _("Strike before stricken!");
const u8 gText_MatchCallTriathlete_Dylan_Pokemon[] = _("A fast-running POKéMON!");
const u8 gText_MatchCallTriathlete_Dylan_Intro1[] = _("Si corres y corres, te");
const u8 gText_MatchCallTriathlete_Dylan_Intro2[] = _("harás uno con el viento.");

const u8 gText_MatchCallTriathlete_Katelyn_Strategy[] = _("All-out offensive!");
const u8 gText_MatchCallTriathlete_Katelyn_Pokemon[] = _("WATER POKéMON rule!");
const u8 gText_MatchCallTriathlete_Katelyn_Intro1[] = _("I must swim over 6 miles");
const u8 gText_MatchCallTriathlete_Katelyn_Intro2[] = _("every day.");

const u8 gText_MatchCallTriathlete_Benjamin_Strategy[] = _("¡Empuja y vuelve a empujar!");
const u8 gText_MatchCallTriathlete_Benjamin_Pokemon[] = _("La fuerza del ACERO.");
const u8 gText_MatchCallTriathlete_Benjamin_Intro1[] = _("Si estás sudando, toma");
const u8 gText_MatchCallTriathlete_Benjamin_Intro2[] = _("líquidos con frecuencia.");

const u8 gText_MatchCallTriathlete_Pablo_Strategy[] = _("Atrae el poder del AGUA.");
const u8 gText_MatchCallTriathlete_Pablo_Pokemon[] = _("Toughened WATER POKéMON.");
const u8 gText_MatchCallTriathlete_Pablo_Intro1[] = _("Training POKéMON is good,");
const u8 gText_MatchCallTriathlete_Pablo_Intro2[] = _("but don't neglect yourself.");

const u8 gText_MatchCallDragonTamer_Nicolas_Strategy[] = _("¡Se trata del poder POKéMON!");
const u8 gText_MatchCallDragonTamer_Nicolas_Pokemon[] = _("¡Mira el poder de los DRAGONES!");
const u8 gText_MatchCallDragonTamer_Nicolas_Intro1[] = _("Seré legendario como el");
const u8 gText_MatchCallDragonTamer_Nicolas_Intro2[] = _("strongest one day!");

const u8 gText_MatchCallBirdKeeper_Robert_Strategy[] = _("I'll show you my technique!");
const u8 gText_MatchCallBirdKeeper_Robert_Pokemon[] = _("Elegantly wheeling BIRDS.");
const u8 gText_MatchCallBirdKeeper_Robert_Intro1[] = _("My BIRD POKéMON, deliver my");
const u8 gText_MatchCallBirdKeeper_Robert_Intro2[] = _("¡amor a esa chica!");

const u8 gText_MatchCallNinjaBoy_Lao_Strategy[] = _("¡Sufrirás por el veneno!");
const u8 gText_MatchCallNinjaBoy_Lao_Pokemon[] = _("Poisonous POKéMON.");
const u8 gText_MatchCallNinjaBoy_Lao_Intro1[] = _("I undertake training so");
const u8 gText_MatchCallNinjaBoy_Lao_Intro2[] = _("que pueda convertirme en ninja.");

const u8 gText_MatchCallBattleGirl_Cyndy_Strategy[] = _("The first strike wins!");
const u8 gText_MatchCallBattleGirl_Cyndy_Pokemon[] = _("tipo LUCHA veloz.");
const u8 gText_MatchCallBattleGirl_Cyndy_Intro1[] = _("If my POKéMON lose,");
const u8 gText_MatchCallBattleGirl_Cyndy_Intro2[] = _("¡Seguiré luchando!");

const u8 gText_MatchCallParasolLady_Madeline_Strategy[] = _("Go, go, my POKéMON!");
const u8 gText_MatchCallParasolLady_Madeline_Pokemon[] = _("I'll raise anything.");
const u8 gText_MatchCallParasolLady_Madeline_Intro1[] = _("Los rayos UV son de tu piel");
const u8 gText_MatchCallParasolLady_Madeline_Intro2[] = _("enemy. Get protected.");

const u8 gText_MatchCallSwimmer_Jenny_Strategy[] = _("¡Sin piedad!");
const u8 gText_MatchCallSwimmer_Jenny_Pokemon[] = _("Cute WATER POKéMON.");
const u8 gText_MatchCallSwimmer_Jenny_Intro1[] = _("I have too many fans.");
const u8 gText_MatchCallSwimmer_Jenny_Intro2[] = _("Me entrevistaron en la TV.");

const u8 gText_MatchCallPicnicker_Diana_Strategy[] = _("Pienso en esto y aquello.");
const u8 gText_MatchCallPicnicker_Diana_Pokemon[] = _("I like all POKéMON.");
const u8 gText_MatchCallPicnicker_Diana_Intro1[] = _("Lo que hay más allá de eso");
const u8 gText_MatchCallPicnicker_Diana_Intro2[] = _("yonder hill?");

const u8 gText_MatchCallTwins_AmyAndLiv_Strategy[] = _("¡Luchamos juntos!");
const u8 gText_MatchCallTwins_AmyAndLiv_Pokemon[] = _("We train together!");
const u8 gText_MatchCallTwins_AmyAndLiv_Intro1[] = _("Nos gustan los mismos POKéMON,");
const u8 gText_MatchCallTwins_AmyAndLiv_Intro2[] = _("but different desserts.");

const u8 gText_MatchCallSailor_Ernest_Strategy[] = _("¡Impongo las cosas con fuerza!");
const u8 gText_MatchCallSailor_Ernest_Pokemon[] = _("Tipos AGUA y LUCHA.");
const u8 gText_MatchCallSailor_Ernest_Intro1[] = _("¡Los marineros son duros!");
const u8 gText_MatchCallSailor_Ernest_Intro2[] = _("Any complaints?");

const u8 gText_MatchCallSailor_Cory_Strategy[] = _("¡Listo para pelear siempre!");
const u8 gText_MatchCallSailor_Cory_Pokemon[] = _("WATER POKéMON are my faves!");
const u8 gText_MatchCallSailor_Cory_Intro1[] = _("Si quieres gritar fuerte,");
const u8 gText_MatchCallSailor_Cory_Intro2[] = _("¡aspira aire con tu barriga!");

const u8 gText_MatchCallCollector_Edwin_Strategy[] = _("Protect POKéMON from harm.");
const u8 gText_MatchCallCollector_Edwin_Pokemon[] = _("I love rare POKéMON.");
const u8 gText_MatchCallCollector_Edwin_Intro1[] = _("Quiero atrapar a todos los");
const u8 gText_MatchCallCollector_Edwin_Intro2[] = _("world's rare POKéMON.");

const u8 gText_MatchCallPkmnBreeder_Lydia_Strategy[] = _("Confío en la fuerza.");
const u8 gText_MatchCallPkmnBreeder_Lydia_Pokemon[] = _("POKéMON are my children.");
const u8 gText_MatchCallPkmnBreeder_Lydia_Intro1[] = _("Requiere conocimiento y");
const u8 gText_MatchCallPkmnBreeder_Lydia_Intro2[] = _("love to raise POKéMON.");

const u8 gText_MatchCallPkmnBreeder_Isaac_Strategy[] = _("¡Ataque total!");
const u8 gText_MatchCallPkmnBreeder_Isaac_Pokemon[] = _("Cualquiera. Yo lo crio.");
const u8 gText_MatchCallPkmnBreeder_Isaac_Intro1[] = _("Les doy {POKEBLOCK}S para");
const u8 gText_MatchCallPkmnBreeder_Isaac_Intro2[] = _("going after CONTEST titles.");

const u8 gText_MatchCallPkmnBreeder_Gabrielle_Strategy[] = _("I raise POKéMON with care.");
const u8 gText_MatchCallPkmnBreeder_Gabrielle_Pokemon[] = _("Fun-to-raise POKéMON.");
const u8 gText_MatchCallPkmnBreeder_Gabrielle_Intro1[] = _("Trata a cada POKéMON que");
const u8 gText_MatchCallPkmnBreeder_Gabrielle_Intro2[] = _("recibirlos con respeto.");

const u8 gText_MatchCallPkmnRanger_Catherine_Strategy[] = _("I believe in my POKéMON.");
const u8 gText_MatchCallPkmnRanger_Catherine_Pokemon[] = _("I like strong POKéMON.");
const u8 gText_MatchCallPkmnRanger_Catherine_Intro1[] = _("Me entreno para rescates");
const u8 gText_MatchCallPkmnRanger_Catherine_Intro2[] = _("work with my POKéMON.");

const u8 gText_MatchCallPkmnRanger_Jackson_Strategy[] = _("¡Atacar en oleadas!");
const u8 gText_MatchCallPkmnRanger_Jackson_Pokemon[] = _("Uso varios tipos.");
const u8 gText_MatchCallPkmnRanger_Jackson_Intro1[] = _("Those who destroy nature");
const u8 gText_MatchCallPkmnRanger_Jackson_Intro2[] = _("must never be forgiven!");

const u8 gText_MatchCallLass_Haley_Strategy[] = _("I'll show you some guts!");
const u8 gText_MatchCallLass_Haley_Pokemon[] = _("Cute POKéMON are my faves!");
const u8 gText_MatchCallLass_Haley_Intro1[] = _("Tras una batalla, siempre");
const u8 gText_MatchCallLass_Haley_Intro2[] = _("bathe with my POKéMON.");

const u8 gText_MatchCallBugCatcher_James_Strategy[] = _("¡Ataque veloz como el rayo!");
const u8 gText_MatchCallBugCatcher_James_Pokemon[] = _("BUG POKéMON are number 1!");
const u8 gText_MatchCallBugCatcher_James_Intro1[] = _("Si quieres capturar BICHO");
const u8 gText_MatchCallBugCatcher_James_Intro2[] = _("POKéMON, wake up early.");

const u8 gText_MatchCallHiker_Trent_Strategy[] = _("Luchando con fuerza.");
const u8 gText_MatchCallHiker_Trent_Pokemon[] = _("Hard-bodied POKéMON.");
const u8 gText_MatchCallHiker_Trent_Intro1[] = _("I've been planning a month");
const u8 gText_MatchCallHiker_Trent_Intro2[] = _("para la caminata de hoy.");

const u8 gText_MatchCallHiker_Sawyer_Strategy[] = _("¡Me gusta el calor!");
const u8 gText_MatchCallHiker_Sawyer_Pokemon[] = _("Hot POKéMON!");
const u8 gText_MatchCallHiker_Sawyer_Intro1[] = _("As much as I love POKéMON,");
const u8 gText_MatchCallHiker_Sawyer_Intro2[] = _("I surely like hiking!");

const u8 gText_MatchCallYoungCouple_LoisAndHal_Strategy[] = _("Lovey-dovey strategy!");
const u8 gText_MatchCallYoungCouple_LoisAndHal_Pokemon[] = _("Lovey-dovey POKéMON!");
const u8 gText_MatchCallYoungCouple_LoisAndHal_Intro1[] = _("We're lovey-dovey!");
const u8 gText_MatchCallYoungCouple_LoisAndHal_Intro2[] = _("Forever lovey-dovey!");

const u8 gText_MatchCallPkmnTrainer_Wally_Strategy[] = _("Nos dejamos llevar.");
const u8 gText_MatchCallPkmnTrainer_Wally_Pokemon[] = _("The 1st POKéMON I caught.");
const u8 gText_MatchCallPkmnTrainer_Wally_Intro1[] = _("POKéMON y yo hemos crecido");
const u8 gText_MatchCallPkmnTrainer_Wally_Intro2[] = _("stronger together.");

const u8 gText_MatchCallRockinWhiz_Roxanne_Strategy[] = _("Ataque de tipo ROCA.");
const u8 gText_MatchCallRockinWhiz_Roxanne_Pokemon[] = _("I prefer rock-hard POKéMON.");
const u8 gText_MatchCallRockinWhiz_Roxanne_Intro1[] = _("Un LÍDER de un GIMNASIO grande");
const u8 gText_MatchCallRockinWhiz_Roxanne_Intro2[] = _("tiene mucha responsabilidad.");

const u8 gText_MatchCallTheBigHit_Brawly_Strategy[] = _("Direct physical action!");
const u8 gText_MatchCallTheBigHit_Brawly_Pokemon[] = _("FIGHTING POKéMON rule!");
const u8 gText_MatchCallTheBigHit_Brawly_Intro1[] = _("El mundo me espera como el");
const u8 gText_MatchCallTheBigHit_Brawly_Intro2[] = _("next big wave!");

const u8 gText_MatchCallSwellShock_Wattson_Strategy[] = _("¡Yo elijo electrificar!");
const u8 gText_MatchCallSwellShock_Wattson_Pokemon[] = _("Get shocked by electricity!");
const u8 gText_MatchCallSwellShock_Wattson_Intro1[] = _("One must never throw a");
const u8 gText_MatchCallSwellShock_Wattson_Intro2[] = _("combate. Ni siquiera yo debo.");

const u8 gText_MatchCallPassionBurn_Flannery_Strategy[] = _("Batalla con agresividad.");
const u8 gText_MatchCallPassionBurn_Flannery_Pokemon[] = _("¡Arde con pasión!");
const u8 gText_MatchCallPassionBurn_Flannery_Intro1[] = _("Completely wash away daily");
const u8 gText_MatchCallPassionBurn_Flannery_Intro2[] = _("¡Descansa en las aguas termales!");

const u8 gText_MatchCallReliableOne_Dad_Strategy[] = _("I flexibly adapt my style.");
const u8 gText_MatchCallReliableOne_Dad_Pokemon[] = _("Crece de forma equilibrada.");
const u8 gText_MatchCallReliableOne_Dad_Intro1[] = _("Camino los 30 minutos desde");
const u8 gText_MatchCallReliableOne_Dad_Intro2[] = _("Vuelve a casa cada día.");

const u8 gText_MatchCallSkyTamer_Winona_Strategy[] = _("Aprovecho la velocidad.");
const u8 gText_MatchCallSkyTamer_Winona_Pokemon[] = _("Graceful sky dancers.");
const u8 gText_MatchCallSkyTamer_Winona_Intro1[] = _("Lo máximo sería");
const u8 gText_MatchCallSkyTamer_Winona_Intro2[] = _("Vivo en armonía con la naturaleza.");

const u8 gText_MatchCallMysticDuo_TateAndLiza_Strategy[] = _("Batallamos en equipo.");
const u8 gText_MatchCallMysticDuo_TateAndLiza_Pokemon[] = _("Always friendly POKéMON.");
const u8 gText_MatchCallMysticDuo_TateAndLiza_Intro1[] = _("Papa has trouble telling");
const u8 gText_MatchCallMysticDuo_TateAndLiza_Intro2[] = _("¡Separarnos a los dos!");

const u8 gText_MatchCallDandyCharm_Juan_Strategy[] = _("I use splendid waterpower.");
const u8 gText_MatchCallDandyCharm_Juan_Pokemon[] = _("POKéMON of elegance!");
const u8 gText_MatchCallDandyCharm_Juan_Intro1[] = _("La adulación de hermosas");
const u8 gText_MatchCallDandyCharm_Juan_Intro2[] = _("¡Las damas me llenan de energía!");

const u8 gText_MatchCallEliteFour_Sidney_Strategy[] = _("¡Ataque antes que defensa!");
const u8 gText_MatchCallEliteFour_Sidney_Pokemon[] = _("The DARK side's beauties.");
const u8 gText_MatchCallEliteFour_Sidney_Intro1[] = _("Dijeron que era un punk, pero");
const u8 gText_MatchCallEliteFour_Sidney_Intro2[] = _("¡Soy uno del ALTO MANDO!");

const u8 gText_MatchCallEliteFour_Phoebe_Strategy[] = _("Confundir y desconcertar.");
const u8 gText_MatchCallEliteFour_Phoebe_Pokemon[] = _("There's nothing definite.");
const u8 gText_MatchCallEliteFour_Phoebe_Intro1[] = _("Me pregunto cómo estará mi");
const u8 gText_MatchCallEliteFour_Phoebe_Intro2[] = _("¿Qué hace el MONTE PYRE?");

const u8 gText_MatchCallEliteFour_Glacia_Strategy[] = _("Uso objetos para ayudarme.");
const u8 gText_MatchCallEliteFour_Glacia_Pokemon[] = _("¡Pasión ardiente en el frío!");
const u8 gText_MatchCallEliteFour_Glacia_Intro1[] = _("El tipo HIELO puede ser mejor");
const u8 gText_MatchCallEliteFour_Glacia_Intro2[] = _("entrené en esta tierra cálida.");

const u8 gText_MatchCallEliteFour_Drake_Strategy[] = _("Harness strong abilities.");
const u8 gText_MatchCallEliteFour_Drake_Pokemon[] = _("¡El poder bruto de los DRAGONES!");
const u8 gText_MatchCallEliteFour_Drake_Intro1[] = _("Me dedico a");
const u8 gText_MatchCallEliteFour_Drake_Intro2[] = _("POKéMON that saved me.");

const u8 gText_MatchCallChampion_Wallace_Strategy[] = _("Dignidad y respeto.");
const u8 gText_MatchCallChampion_Wallace_Pokemon[] = _("I prefer POKéMON of grace.");
const u8 gText_MatchCallChampion_Wallace_Intro1[] = _("I represent beauty as");
const u8 gText_MatchCallChampion_Wallace_Intro2[] = _("well as intelligence.");
#endif

#if IS_HNS
// Check page disabled for HnS trainers - table left empty.
// To re-enable: add MCFLAVOR entries here and set HasCheckPage_Trainer to TRUE.
const u8 *const gMatchCallFlavorTexts[REMATCH_TABLE_ENTRIES][CHECK_PAGE_ENTRY_COUNT] = {0};
#else
const u8 *const gMatchCallFlavorTexts[REMATCH_TABLE_ENTRIES][CHECK_PAGE_ENTRY_COUNT] =
{
    [REMATCH_ROSE] = MCFLAVOR(AromaLady_Rose),
    [REMATCH_ANDRES] = MCFLAVOR(RuinManiac_Andres),
    [REMATCH_DUSTY] = MCFLAVOR(RuinManiac_Dusty),
    [REMATCH_LOLA] = MCFLAVOR(Tuber_Lola),
    [REMATCH_RICKY] = MCFLAVOR(Tuber_Ricky),
    [REMATCH_LILA_AND_ROY] = MCFLAVOR(SisAndBro_LilaAndRoy),
    [REMATCH_CRISTIN] = MCFLAVOR(Cooltrainer_Cristin),
    [REMATCH_BROOKE] = MCFLAVOR(Cooltrainer_Brooke),
    [REMATCH_WILTON] = MCFLAVOR(Cooltrainer_Wilton),
    [REMATCH_VALERIE] = MCFLAVOR(HexManiac_Valerie),
    [REMATCH_CINDY] = MCFLAVOR(Lady_Cindy),
    [REMATCH_THALIA] = MCFLAVOR(Beauty_Thalia),
    [REMATCH_JESSICA] = MCFLAVOR(Beauty_Jessica),
    [REMATCH_WINSTON] = MCFLAVOR(RichBoy_Winston),
    [REMATCH_STEVE] = MCFLAVOR(PokeManiac_Steve),
    [REMATCH_TONY] = MCFLAVOR(Swimmer_Tony),
    [REMATCH_NOB] = MCFLAVOR(BlackBelt_Nob),
    [REMATCH_KOJI] = MCFLAVOR(BlackBelt_Koji),
    [REMATCH_FERNANDO] = MCFLAVOR(Guitarist_Fernando),
    [REMATCH_DALTON] = MCFLAVOR(Guitarist_Dalton),
    [REMATCH_BERNIE] = MCFLAVOR(Kindler_Bernie),
    [REMATCH_ETHAN] = MCFLAVOR(Camper_Ethan),
    [REMATCH_JOHN_AND_JAY] = MCFLAVOR(OldCouple_JohnAndJay),
    [REMATCH_JEFFREY] = MCFLAVOR(BugManiac_Jeffrey),
    [REMATCH_CAMERON] = MCFLAVOR(Psychic_Cameron),
    [REMATCH_JACKI] = MCFLAVOR(Psychic_Jacki),
    [REMATCH_WALTER] = MCFLAVOR(Gentleman_Walter),
    [REMATCH_KAREN] = MCFLAVOR(SchoolKid_Karen),
    [REMATCH_JERRY] = MCFLAVOR(SchoolKid_Jerry),
    [REMATCH_ANNA_AND_MEG] = MCFLAVOR(SrAndJr_AnnaAndMeg),
    [REMATCH_ISABEL] = MCFLAVOR(Pokefan_Isabel),
    [REMATCH_MIGUEL] = MCFLAVOR(Pokefan_Miguel),
    [REMATCH_TIMOTHY] = MCFLAVOR(Expert_Timothy),
    [REMATCH_SHELBY] = MCFLAVOR(Expert_Shelby),
    [REMATCH_CALVIN] = MCFLAVOR(Youngster_Calvin),
    [REMATCH_ELLIOT] = MCFLAVOR(Fisherman_Elliot),
    [REMATCH_ISAIAH] = MCFLAVOR(Triathlete_Isaiah),
    [REMATCH_MARIA] = MCFLAVOR(Triathlete_Maria),
    [REMATCH_ABIGAIL] = MCFLAVOR(Triathlete_Abigail),
    [REMATCH_DYLAN] = MCFLAVOR(Triathlete_Dylan),
    [REMATCH_KATELYN] = MCFLAVOR(Triathlete_Katelyn),
    [REMATCH_BENJAMIN] = MCFLAVOR(Triathlete_Benjamin),
    [REMATCH_PABLO] = MCFLAVOR(Triathlete_Pablo),
    [REMATCH_NICOLAS] = MCFLAVOR(DragonTamer_Nicolas),
    [REMATCH_ROBERT] = MCFLAVOR(BirdKeeper_Robert),
    [REMATCH_LAO] = MCFLAVOR(NinjaBoy_Lao),
    [REMATCH_CYNDY] = MCFLAVOR(BattleGirl_Cyndy),
    [REMATCH_MADELINE] = MCFLAVOR(ParasolLady_Madeline),
    [REMATCH_JENNY] = MCFLAVOR(Swimmer_Jenny),
    [REMATCH_DIANA] = MCFLAVOR(Picnicker_Diana),
    [REMATCH_AMY_AND_LIV] = MCFLAVOR(Twins_AmyAndLiv),
    [REMATCH_ERNEST] = MCFLAVOR(Sailor_Ernest),
    [REMATCH_CORY] = MCFLAVOR(Sailor_Cory),
    [REMATCH_EDWIN] = MCFLAVOR(Collector_Edwin),
    [REMATCH_LYDIA] = MCFLAVOR(PkmnBreeder_Lydia),
    [REMATCH_ISAAC] = MCFLAVOR(PkmnBreeder_Isaac),
    [REMATCH_GABRIELLE] = MCFLAVOR(PkmnBreeder_Gabrielle),
    [REMATCH_CATHERINE] = MCFLAVOR(PkmnRanger_Catherine),
    [REMATCH_JACKSON] = MCFLAVOR(PkmnRanger_Jackson),
    [REMATCH_HALEY] = MCFLAVOR(Lass_Haley),
    [REMATCH_JAMES] = MCFLAVOR(BugCatcher_James),
    [REMATCH_TRENT] = MCFLAVOR(Hiker_Trent),
    [REMATCH_SAWYER] = MCFLAVOR(Hiker_Sawyer),
    [REMATCH_KIRA_AND_DAN] = MCFLAVOR(YoungCouple_LoisAndHal),
    [REMATCH_WALLY_VR] = MCFLAVOR(PkmnTrainer_Wally),
    [REMATCH_ROXANNE] = MCFLAVOR(RockinWhiz_Roxanne),
    [REMATCH_BRAWLY] = MCFLAVOR(TheBigHit_Brawly),
    [REMATCH_WATTSON] = MCFLAVOR(SwellShock_Wattson),
    [REMATCH_FLANNERY] = MCFLAVOR(PassionBurn_Flannery),
    [REMATCH_NORMAN] = MCFLAVOR(ReliableOne_Dad),
    [REMATCH_WINONA] = MCFLAVOR(SkyTamer_Winona),
    [REMATCH_TATE_AND_LIZA] = MCFLAVOR(MysticDuo_TateAndLiza),
    [REMATCH_JUAN] = MCFLAVOR(DandyCharm_Juan),
    [REMATCH_SIDNEY] = MCFLAVOR(EliteFour_Sidney),
    [REMATCH_PHOEBE] = MCFLAVOR(EliteFour_Phoebe),
    [REMATCH_GLACIA] = MCFLAVOR(EliteFour_Glacia),
    [REMATCH_DRAKE] = MCFLAVOR(EliteFour_Drake),
    [REMATCH_WALLACE] = MCFLAVOR(Champion_Wallace),
};
#endif
