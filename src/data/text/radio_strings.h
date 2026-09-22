// Radio station strings ported from pokecrystal
// Lines fit ~32 char width for 28-tile window

#ifndef GUARD_DATA_TEXT_RADIO_STRINGS_H
#define GUARD_DATA_TEXT_RADIO_STRINGS_H

// ==========================================================
// Station Names (displayed at top of radio UI)
// ==========================================================

static const u8 sRadioStationName_OaksPkmnTalk[]    = _("Charla POKéMON de OAK");
static const u8 sRadioStationName_PokedexShow[]     = _("Show de la POKéDEX");
static const u8 sRadioStationName_PokemonMusic[]    = _("Música POKéMON");
static const u8 sRadioStationName_LuckyChannel[]    = _("Canal Suerte");
static const u8 sRadioStationName_BuenasPassword[]  = _("CONTRASEÑA DE BUENA");
static const u8 sRadioStationName_Unown[]           = _("?????");
static const u8 sRadioStationName_PlacesAndPeople[] = _("Lugares y Gente");
static const u8 sRadioStationName_LetsAllSing[]     = _("¡Cantemos todos!");
static const u8 sRadioStationName_PokeFlute[]       = _("POKé FLUTE");

static const u8 sRadioStationName_HoennSound[]  = _("Sonido de Hoenn");

// ==========================================================
// Hoenn Sound
// ==========================================================

static const u8 sRadioText_Hoenn1[] = _("Una melodía POKéMON de una");
static const u8 sRadioText_Hoenn2[] = _("¡región lejana llamada HOENN!");
static const u8 sRadioText_Hoenn3[] = _("POKéMON salvajes de esa región");
static const u8 sRadioText_Hoenn4[] = _("¡podría aparecer cerca!");

// ==========================================================
// POKéDEX Show
// ==========================================================

static const u8 sRadioText_PokedexShow_Intro[] = _("¡LA POKéDEX DE OAK!");
static const u8 sRadioText_PokedexShow_TodaysPrefix[] = _("OAK: El POKéMON de hoy es ");

// ==========================================================
// Oak's POKéMON Talk
// ==========================================================

static const u8 sRadioText_OPT_Intro[] = _("MARY: ¡CHARLA POKéMON DE OAK!");
static const u8 sRadioText_OPT_WithMeMary[] = _("¡Conmigo, MARY!");
static const u8 sRadioText_OPT_OakPrefix[] = _("OAK: ");
static const u8 sRadioText_OPT_SeenAround[] = _("puede verse por");
static const u8 sRadioText_OPT_MaryPrefix[] = _("MARY: ");
static const u8 sRadioText_OPT_MaryIs[] = _("'s ");

// Pokemon Channel interlude
static const u8 sRadioText_OPT_PokemonChannel[] = _("Canal POKéMON");

// Adverbs (randomly selected)
static const u8 sRadioText_OPT_Adverb_SweetAdorably[]      = _("dulce y adorablemente");
static const u8 sRadioText_OPT_Adverb_WigglySlickly[]      = _("ondulante y resbaladizo");
static const u8 sRadioText_OPT_Adverb_AptlyNamed[]         = _("bien nombrado y");
static const u8 sRadioText_OPT_Adverb_UndeniablyKindOf[]   = _("indudablemente amable");
static const u8 sRadioText_OPT_Adverb_Unbearably[]         = _("tan, tan insoportable");
static const u8 sRadioText_OPT_Adverb_WowImpressively[]    = _("vaya, impresionante");
static const u8 sRadioText_OPT_Adverb_AlmostPoisonously[]  = _("casi venenosamente");
static const u8 sRadioText_OPT_Adverb_Sensually[]          = _("oh, tan sensual");
static const u8 sRadioText_OPT_Adverb_Mischievously[]      = _("tan travieso");
static const u8 sRadioText_OPT_Adverb_Topically[]          = _("muy acorde al tema");
static const u8 sRadioText_OPT_Adverb_Addictively[]        = _("seguro que es adictivo");
static const u8 sRadioText_OPT_Adverb_LooksInWater[]       = _("su aspecto en agua es");
static const u8 sRadioText_OPT_Adverb_EvolutionMustBe[]    = _("su evolución debe ser");
static const u8 sRadioText_OPT_Adverb_Provocatively[]      = _("provocativamente");
static const u8 sRadioText_OPT_Adverb_FlippedOut[]         = _("tan alterado y");
static const u8 sRadioText_OPT_Adverb_HeartMeltingly[]     = _("tiernamente");

static const u8 *const sRadioText_OPT_Adverbs[] =
{
    sRadioText_OPT_Adverb_SweetAdorably,
    sRadioText_OPT_Adverb_WigglySlickly,
    sRadioText_OPT_Adverb_AptlyNamed,
    sRadioText_OPT_Adverb_UndeniablyKindOf,
    sRadioText_OPT_Adverb_Unbearably,
    sRadioText_OPT_Adverb_WowImpressively,
    sRadioText_OPT_Adverb_AlmostPoisonously,
    sRadioText_OPT_Adverb_Sensually,
    sRadioText_OPT_Adverb_Mischievously,
    sRadioText_OPT_Adverb_Topically,
    sRadioText_OPT_Adverb_Addictively,
    sRadioText_OPT_Adverb_LooksInWater,
    sRadioText_OPT_Adverb_EvolutionMustBe,
    sRadioText_OPT_Adverb_Provocatively,
    sRadioText_OPT_Adverb_FlippedOut,
    sRadioText_OPT_Adverb_HeartMeltingly,
};

// Adjectives (randomly selected)
static const u8 sRadioText_OPT_Adj_Cute[]           = _("lindo.");
static const u8 sRadioText_OPT_Adj_Weird[]          = _("raro.");
static const u8 sRadioText_OPT_Adj_Pleasant[]       = _("agradable.");
static const u8 sRadioText_OPT_Adj_BoldSortOf[]     = _("audaz, más o menos.");
static const u8 sRadioText_OPT_Adj_Frightening[]    = _("aterrador.");
static const u8 sRadioText_OPT_Adj_SuaveDebonair[]  = _("¡elegante y galán!");
static const u8 sRadioText_OPT_Adj_Powerful[]        = _("poderoso.");
static const u8 sRadioText_OPT_Adj_Exciting[]        = _("emocionante.");
static const u8 sRadioText_OPT_Adj_Groovy[]          = _("¡genial!");
static const u8 sRadioText_OPT_Adj_Inspiring[]       = _("inspirador.");
static const u8 sRadioText_OPT_Adj_Friendly[]        = _("amigable.");
static const u8 sRadioText_OPT_Adj_HotHotHot[]       = _("¡muy, muy sexy!");
static const u8 sRadioText_OPT_Adj_Stimulating[]     = _("estimulante.");
static const u8 sRadioText_OPT_Adj_Guarded[]         = _("protegido.");
static const u8 sRadioText_OPT_Adj_Lovely[]          = _("encantador.");
static const u8 sRadioText_OPT_Adj_Speedy[]          = _("veloz.");

static const u8 *const sRadioText_OPT_Adjectives[] =
{
    sRadioText_OPT_Adj_Cute,
    sRadioText_OPT_Adj_Weird,
    sRadioText_OPT_Adj_Pleasant,
    sRadioText_OPT_Adj_BoldSortOf,
    sRadioText_OPT_Adj_Frightening,
    sRadioText_OPT_Adj_SuaveDebonair,
    sRadioText_OPT_Adj_Powerful,
    sRadioText_OPT_Adj_Exciting,
    sRadioText_OPT_Adj_Groovy,
    sRadioText_OPT_Adj_Inspiring,
    sRadioText_OPT_Adj_Friendly,
    sRadioText_OPT_Adj_HotHotHot,
    sRadioText_OPT_Adj_Stimulating,
    sRadioText_OPT_Adj_Guarded,
    sRadioText_OPT_Adj_Lovely,
    sRadioText_OPT_Adj_Speedy,
};

// ==========================================================
// POKéMON Music Channel (Ben & Fern)
// ==========================================================

static const u8 sRadioText_BenIntro[] = _("BEN: ¡CANAL MUSICAL POKéMON!");
static const u8 sRadioText_BenIntro2[] = _("¡Soy yo, el DJ BEN!");
static const u8 sRadioText_FernIntro[] = _("FERN: ¡POKéMÚSICA!");
static const u8 sRadioText_FernIntro2[] = _("¡Con el DJ FERN!");
// "Today's {DAY}," built dynamically
static const u8 sRadioText_BenFern_TodayIs[] = _("Hoy es ");
static const u8 sRadioText_BenFern_JamTo[] = _("así que vamos a sonar");
static const u8 sRadioText_BenFern_ChillTo[] = _("así que relájate con");
static const u8 sRadioText_BenFern_March[] = _("¡Marcha POKéMON!");
static const u8 sRadioText_BenFern_Lullaby[] = _("¡Canción de cuna POKéMON!");

// ==========================================================
// Lucky Channel
// ==========================================================

static const u8 sRadioText_LC1[] = _("REED: ¡Yeehaw! ¿Cómo están");
static const u8 sRadioText_LC2[] = _("todos hoy? No importa si");
static const u8 sRadioText_LC3[] = _("están bien o mal, ¡no se");
static const u8 sRadioText_LC4[] = _("pierdan el SHOW DEL NÚMERO!");
static const u8 sRadioText_LC5[] = _("El Número Suerte de la semana es");
// "{number}!" built dynamically
static const u8 sRadioText_LC_Repeat[] = _("¡Lo repito!");
static const u8 sRadioText_LC_Match[] = _("¡Si coinciden, vayan a la");
static const u8 sRadioText_LC_Tower[] = _("TORRE RADIO!");
static const u8 sRadioText_LC_Drag1[] = _("…Repetirme a mí mismo");
static const u8 sRadioText_LC_Drag2[] = _("es un fastidio…");

// ==========================================================
// Places and People
// ==========================================================

static const u8 sRadioText_PnP_Intro[] = _("¡LUGARES Y GENTE! Traído");
static const u8 sRadioText_PnP_Intro2[] = _("para ustedes por mí, ¡DJ LILY!");
static const u8 sRadioText_PnP_Space[] = _(" ");

// People adjectives
static const u8 sRadioText_PnP_Cute[]       = _("es lindo.");
static const u8 sRadioText_PnP_Lazy[]       = _("es algo perezoso.");
static const u8 sRadioText_PnP_Happy[]      = _("siempre está feliz.");
static const u8 sRadioText_PnP_Noisy[]      = _("es bastante ruidoso.");
static const u8 sRadioText_PnP_Precocious[] = _("es precoz.");
static const u8 sRadioText_PnP_Bold[]       = _("es algo audaz.");
static const u8 sRadioText_PnP_Picky[]      = _("¡es muy exigente!");
static const u8 sRadioText_PnP_SortOfOK[]   = _("está más o menos bien.");
static const u8 sRadioText_PnP_SoSo[]       = _("es simplemente regular.");
static const u8 sRadioText_PnP_Great[]       = _("en realidad es genial.");
static const u8 sRadioText_PnP_MyType[]      = _("es justo mi tipo.");
static const u8 sRadioText_PnP_Cool[]        = _("es genial, ¿no?");
static const u8 sRadioText_PnP_Inspiring[]   = _("¡es inspirador!");
static const u8 sRadioText_PnP_Weird[]       = _("es algo raro.");
static const u8 sRadioText_PnP_RightForMe[]  = _("¿es el ideal para mí?");
static const u8 sRadioText_PnP_Odd[]         = _("¡definitivamente es raro!");

static const u8 *const sRadioText_PnP_PeopleAdj[] =
{
    sRadioText_PnP_Cute,
    sRadioText_PnP_Lazy,
    sRadioText_PnP_Happy,
    sRadioText_PnP_Noisy,
    sRadioText_PnP_Precocious,
    sRadioText_PnP_Bold,
    sRadioText_PnP_Picky,
    sRadioText_PnP_SortOfOK,
    sRadioText_PnP_SoSo,
    sRadioText_PnP_Great,
    sRadioText_PnP_MyType,
    sRadioText_PnP_Cool,
    sRadioText_PnP_Inspiring,
    sRadioText_PnP_Weird,
    sRadioText_PnP_RightForMe,
    sRadioText_PnP_Odd,
};

// ==========================================================
// Rocket Radio
// ==========================================================

static const u8 sRadioStationName_Rocket[] = _("TEAM ROCKET");
static const u8 sRadioText_Rocket1[]  = _("… …Ejem, nosotros somos");
static const u8 sRadioText_Rocket2[]  = _("¡el TEAM ROCKET!");
static const u8 sRadioText_Rocket3[]  = _("Tras tres años");
static const u8 sRadioText_Rocket4[]  = _("de preparación, nosotros");
static const u8 sRadioText_Rocket5[]  = _("hemos resurgido");
static const u8 sRadioText_Rocket6[]  = _("¡de las cenizas!");
static const u8 sRadioText_Rocket7[]  = _("¡GIOVANNI!");
static const u8 sRadioText_Rocket8[]  = _("¿Puedes oírnos?");
static const u8 sRadioText_Rocket9[]  = _("");
static const u8 sRadioText_Rocket10[] = _("");

// ==========================================================
// Buena's Password
// ==========================================================

static const u8 sRadioText_Buena1[] = _("BUENA: ¡Aquí BUENA!");
static const u8 sRadioText_Buena2[] = _("¡La clave de hoy!");
static const u8 sRadioText_Buena3[] = _("Déjame pensar... Es");
// "{password}!" built dynamically with STR_VAR_1
static const u8 sRadioText_Buena4[] = _("¡{STR_VAR_1}!");
static const u8 sRadioText_Buena5[] = _("¡No la olvides! Estoy en");
static const u8 sRadioText_Buena6[] = _("¡la TORRE RADIO de CIUDAD TRIGAL!");


// ==========================================================
// Buena's Password Categories & Options
// ==========================================================

static const u8 sRadioBuenaPassword_NewBarkTown[]     = _("PUEBLO PRIMAVERA");
static const u8 sRadioBuenaPassword_CherrygroveCity[]  = _("CIUDAD CEREZO");
static const u8 sRadioBuenaPassword_AzaleaTown[]      = _("PUEBLO AZALEA");
static const u8 sRadioBuenaPassword_Flying[]          = _("FLYING");
static const u8 sRadioBuenaPassword_Bug[]             = _("BUG");
static const u8 sRadioBuenaPassword_Grass[]           = _("GRASS");
static const u8 sRadioBuenaPassword_PkmnTalk[]        = _("Charla POKéMON");
static const u8 sRadioBuenaPassword_PkmnMusic[]       = _("Música POKéMON");
static const u8 sRadioBuenaPassword_LuckyChannel[]    = _("Canal Suerte");

// ==========================================================
// Oak's POKéMON Talk - Special Reports
// ==========================================================

static const u8 sOPT_Report_Clefairy_0[]  = _("MARY: ¡Esta noche, un raro momento");
static const u8 sOPT_Report_Clefairy_1[]  = _("de luna en CHARLA POKéMON!");
static const u8 sOPT_Report_Clefairy_2[]  = _("OAK: ¡Hablaremos sobre el");
static const u8 sOPT_Report_Clefairy_3[]  = _("místico CLEFAIRY!");
static const u8 sOPT_Report_Clefairy_4[]  = _("Se reúnen en el MT.MOON");
static const u8 sOPT_Report_Clefairy_5[]  = _("bajo las lunas llenas.");
static const u8 sOPT_Report_Clefairy_6[]  = _("MARY: ¡BAILAN en círculos!");
static const u8 sOPT_Report_Clefairy_7[]  = _("¡Qué raro y adorable!");
static const u8 sOPT_Report_Clefairy_8[]  = _("OAK: Un misterio eterno");
static const u8 sOPT_Report_Clefairy_9[]  = _("¡y un espectáculo increíble!");

static const u8 sOPT_Report_Lapras_0[]  = _("MARY: ¡Un gigante gentil");
static const u8 sOPT_Report_Lapras_1[]  = _("está hoy en nuestro show!");
static const u8 sOPT_Report_Lapras_2[]  = _("OAK: Es el ferry del océano,");
static const u8 sOPT_Report_Lapras_3[]  = _("¡nuestro querido LAPRAS!");
static const u8 sOPT_Report_Lapras_4[]  = _("Se ve en la CUEVA UNIÓN, pero");
static const u8 sOPT_Report_Lapras_5[]  = _("en ningún otro lugar. ¡Curioso!");
static const u8 sOPT_Report_Lapras_6[]  = _("MARY: ¡Tan raro y pacífico!");
static const u8 sOPT_Report_Lapras_7[]  = _("¡Y también canta!");
static const u8 sOPT_Report_Lapras_8[]  = _("OAK: Dicen que sus canciones");
static const u8 sOPT_Report_Lapras_9[]  = _("calman el alma del mar.");

static const u8 sOPT_Report_Ampharos_0[]  = _("MARY: ¡Bienvenidos todos!");
static const u8 sOPT_Report_Ampharos_1[]  = _("¡Es hora de POKéMON TALK!");
static const u8 sOPT_Report_Ampharos_2[]  = _("OAK: ¡Hablemos un poco sobre");
static const u8 sOPT_Report_Ampharos_3[]  = _("nuestro amigo AMPHAROS!");
static const u8 sOPT_Report_Ampharos_4[]  = _("Su cola brilla entre la niebla");
static const u8 sOPT_Report_Ampharos_5[]  = _("para guiar a los perdidos.");
static const u8 sOPT_Report_Ampharos_6[]  = _("MARY: ¡Poderoso, elegante");
static const u8 sOPT_Report_Ampharos_7[]  = _("y muy amigable!");
static const u8 sOPT_Report_Ampharos_8[]  = _("OAK: ¡Es clave en muchas");
static const u8 sOPT_Report_Ampharos_9[]  = _("historias de faros!");

static const u8 sOPT_Report_Sudowoodo_0[]  = _("MARY: Ahora, alguien muy raro");
static const u8 sOPT_Report_Sudowoodo_1[]  = _("en la RUTA 36...");
static const u8 sOPT_Report_Sudowoodo_2[]  = _("OAK: ¡SUDOWOODO! Parece un");
static const u8 sOPT_Report_Sudowoodo_3[]  = _("árbol, ¡pero no lo es!");
static const u8 sOPT_Report_Sudowoodo_4[]  = _("Bloquea el camino y no se");
static const u8 sOPT_Report_Sudowoodo_5[]  = _("mueve sin agua.");
static const u8 sOPT_Report_Sudowoodo_6[]  = _("MARY: Solo reacciona a un");
static const u8 sOPT_Report_Sudowoodo_7[]  = _("SQUIRTBOTTLE!");
static const u8 sOPT_Report_Sudowoodo_8[]  = _("OAK: No es un arbusto, ¡es un");
static const u8 sOPT_Report_Sudowoodo_9[]  = _("tipo ROCA disfrazado!");

static const u8 sOPT_Report_RedGyarados_0[]  = _("MARY: ¡La historia de hoy es");
static const u8 sOPT_Report_RedGyarados_1[]  = _("impactante y viene de JOHTO!");
static const u8 sOPT_Report_RedGyarados_2[]  = _("OAK: Entrenadores vieron un RED");
static const u8 sOPT_Report_RedGyarados_3[]  = _("¡GYARADOS en el LAGO DE LA FURIA!");
static const u8 sOPT_Report_RedGyarados_4[]  = _("A diferencia de los azules,");
static const u8 sOPT_Report_RedGyarados_5[]  = _("¡este es de un rojo brillante!");
static const u8 sOPT_Report_RedGyarados_6[]  = _("MARY: Dicen que está ligado");
static const u8 sOPT_Report_RedGyarados_7[]  = _("¡a unas ondas de radio extrañas!");
static const u8 sOPT_Report_RedGyarados_8[]  = _("OAK: Una evolución misteriosa...");
static const u8 sOPT_Report_RedGyarados_9[]  = _("Posiblemente artificial.");

static const u8 sOPT_Report_Unown_0[]  = _("MARY: ¿Has ido a las RUINAS");
static const u8 sOPT_Report_Unown_1[]  = _("DE ALFA? ¡Dan mucho miedo!");
static const u8 sOPT_Report_Unown_2[]  = _("OAK: Hay símbolos extraños en");
static const u8 sOPT_Report_Unown_3[]  = _("los muros, como runas antiguas.");
static const u8 sOPT_Report_Unown_4[]  = _("Dentro hallarás a UNOWN...");
static const u8 sOPT_Report_Unown_5[]  = _("¡cada una tiene forma de letra!");
static const u8 sOPT_Report_Unown_6[]  = _("MARY: Forman palabras,");
static const u8 sOPT_Report_Unown_7[]  = _("¡¿quizás?! ¡O solo nos asustan!");
static const u8 sOPT_Report_Unown_8[]  = _("OAK: Un enigma de la naturaleza,");
static const u8 sOPT_Report_Unown_9[]  = _("aún sin resolver hoy en día.");

static const u8 sOPT_Report_Snubbull_0[]  = _("MARY: ¡La gente de CIUDAD TRIGAL");
static const u8 sOPT_Report_Snubbull_1[]  = _("lo busca por todas partes!");
static const u8 sOPT_Report_Snubbull_2[]  = _("OAK: Un SNUBBULL se ha rebelado");
static const u8 sOPT_Report_Snubbull_3[]  = _("¡y anda escapando!");
static const u8 sOPT_Report_Snubbull_4[]  = _("Suele ser tímido y quisquilloso,");
static const u8 sOPT_Report_Snubbull_5[]  = _("lo vieron cerca de la estación.");
static const u8 sOPT_Report_Snubbull_6[]  = _("MARY: Tal vez esté persiguiendo");
static const u8 sOPT_Report_Snubbull_7[]  = _("¡amor... o solo aventura!");
static const u8 sOPT_Report_Snubbull_8[]  = _("OAK: Mantén los ojos abiertos,");
static const u8 sOPT_Report_Snubbull_9[]  = _("y tu correa lista.");

static const u8 sOPT_Report_Slowpoke_0[]  = _("MARY: ¡Grandes noticias de");
static const u8 sOPT_Report_Slowpoke_1[]  = _("PUEBLO AZALEA esta semana!");
static const u8 sOPT_Report_Slowpoke_2[]  = _("OAK: ¡Los SLOWPOKE volvieron");
static const u8 sOPT_Report_Slowpoke_3[]  = _("a su pozo tras una crisis!");
static const u8 sOPT_Report_Slowpoke_4[]  = _("¡El TEAM ROCKET les cortaba");
static const u8 sOPT_Report_Slowpoke_5[]  = _("las colas! ¡Horrible!");
static const u8 sOPT_Report_Slowpoke_6[]  = _("MARY: ¡Pero un joven y");
static const u8 sOPT_Report_Slowpoke_7[]  = _("valiente ENTRENADOR los detuvo!");
static const u8 sOPT_Report_Slowpoke_8[]  = _("OAK: Los SLOWPOKE están a salvo");
static const u8 sOPT_Report_Slowpoke_9[]  = _("y vuelve a dormir felizmente.");

static const u8 sOPT_Report_LavenderTower_0[]  = _("MARY: La torre de PUEBLO LAVANDA");
static const u8 sOPT_Report_LavenderTower_1[]  = _("¡ha cambiado su sintonía!");
static const u8 sOPT_Report_LavenderTower_2[]  = _("OAK: La vieja torre fantasma");
static const u8 sOPT_Report_LavenderTower_3[]  = _("¡ahora es una ESTACIÓN DE RADIO!");
static const u8 sOPT_Report_LavenderTower_4[]  = _("Algunos locales dicen que aún");
static const u8 sOPT_Report_LavenderTower_5[]  = _("se siente... espeluznante.");
static const u8 sOPT_Report_LavenderTower_6[]  = _("MARY: ¡Juro que vi un GASTLY");
static const u8 sOPT_Report_LavenderTower_7[]  = _("cerca de la cabina del micro!");
static const u8 sOPT_Report_LavenderTower_8[]  = _("OAK: Podría ser estática...");
static const u8 sOPT_Report_LavenderTower_9[]  = _("¡o espectros!");

static const u8 sOPT_Report_Tentacruel_0[]  = _("MARY: Noticias raras de la");
static const u8 sOPT_Report_Tentacruel_1[]  = _("¡ISLAS REMOLINO hoy!");
static const u8 sOPT_Report_Tentacruel_2[]  = _("OAK: Los TENTACRUEL han");
static const u8 sOPT_Report_Tentacruel_3[]  = _("rodeado las cuevas!");
static const u8 sOPT_Report_Tentacruel_4[]  = _("Son enormes y actúan");
static const u8 sOPT_Report_Tentacruel_5[]  = _("como si fueran territoriales.");
static const u8 sOPT_Report_Tentacruel_6[]  = _("MARY: Bloquean el camino");
static const u8 sOPT_Report_Tentacruel_7[]  = _("sin atacar...");
static const u8 sOPT_Report_Tentacruel_8[]  = _("OAK: Como si guardaran algo");
static const u8 sOPT_Report_Tentacruel_9[]  = _("bajo las profundidades.");

#define OPT_REPORT_LINES 10
#define NUM_OPT_REPORTS 10

static const u8 *const sOPT_Reports[NUM_OPT_REPORTS][OPT_REPORT_LINES] =
{
    { sOPT_Report_Clefairy_0, sOPT_Report_Clefairy_1, sOPT_Report_Clefairy_2, sOPT_Report_Clefairy_3, sOPT_Report_Clefairy_4, sOPT_Report_Clefairy_5, sOPT_Report_Clefairy_6, sOPT_Report_Clefairy_7, sOPT_Report_Clefairy_8, sOPT_Report_Clefairy_9 },
    { sOPT_Report_Lapras_0, sOPT_Report_Lapras_1, sOPT_Report_Lapras_2, sOPT_Report_Lapras_3, sOPT_Report_Lapras_4, sOPT_Report_Lapras_5, sOPT_Report_Lapras_6, sOPT_Report_Lapras_7, sOPT_Report_Lapras_8, sOPT_Report_Lapras_9 },
    { sOPT_Report_Ampharos_0, sOPT_Report_Ampharos_1, sOPT_Report_Ampharos_2, sOPT_Report_Ampharos_3, sOPT_Report_Ampharos_4, sOPT_Report_Ampharos_5, sOPT_Report_Ampharos_6, sOPT_Report_Ampharos_7, sOPT_Report_Ampharos_8, sOPT_Report_Ampharos_9 },
    { sOPT_Report_Sudowoodo_0, sOPT_Report_Sudowoodo_1, sOPT_Report_Sudowoodo_2, sOPT_Report_Sudowoodo_3, sOPT_Report_Sudowoodo_4, sOPT_Report_Sudowoodo_5, sOPT_Report_Sudowoodo_6, sOPT_Report_Sudowoodo_7, sOPT_Report_Sudowoodo_8, sOPT_Report_Sudowoodo_9 },
    { sOPT_Report_RedGyarados_0, sOPT_Report_RedGyarados_1, sOPT_Report_RedGyarados_2, sOPT_Report_RedGyarados_3, sOPT_Report_RedGyarados_4, sOPT_Report_RedGyarados_5, sOPT_Report_RedGyarados_6, sOPT_Report_RedGyarados_7, sOPT_Report_RedGyarados_8, sOPT_Report_RedGyarados_9 },
    { sOPT_Report_Unown_0, sOPT_Report_Unown_1, sOPT_Report_Unown_2, sOPT_Report_Unown_3, sOPT_Report_Unown_4, sOPT_Report_Unown_5, sOPT_Report_Unown_6, sOPT_Report_Unown_7, sOPT_Report_Unown_8, sOPT_Report_Unown_9 },
    { sOPT_Report_Snubbull_0, sOPT_Report_Snubbull_1, sOPT_Report_Snubbull_2, sOPT_Report_Snubbull_3, sOPT_Report_Snubbull_4, sOPT_Report_Snubbull_5, sOPT_Report_Snubbull_6, sOPT_Report_Snubbull_7, sOPT_Report_Snubbull_8, sOPT_Report_Snubbull_9 },
    { sOPT_Report_Slowpoke_0, sOPT_Report_Slowpoke_1, sOPT_Report_Slowpoke_2, sOPT_Report_Slowpoke_3, sOPT_Report_Slowpoke_4, sOPT_Report_Slowpoke_5, sOPT_Report_Slowpoke_6, sOPT_Report_Slowpoke_7, sOPT_Report_Slowpoke_8, sOPT_Report_Slowpoke_9 },
    { sOPT_Report_LavenderTower_0, sOPT_Report_LavenderTower_1, sOPT_Report_LavenderTower_2, sOPT_Report_LavenderTower_3, sOPT_Report_LavenderTower_4, sOPT_Report_LavenderTower_5, sOPT_Report_LavenderTower_6, sOPT_Report_LavenderTower_7, sOPT_Report_LavenderTower_8, sOPT_Report_LavenderTower_9 },
    { sOPT_Report_Tentacruel_0, sOPT_Report_Tentacruel_1, sOPT_Report_Tentacruel_2, sOPT_Report_Tentacruel_3, sOPT_Report_Tentacruel_4, sOPT_Report_Tentacruel_5, sOPT_Report_Tentacruel_6, sOPT_Report_Tentacruel_7, sOPT_Report_Tentacruel_8, sOPT_Report_Tentacruel_9 },
};

#endif // GUARD_DATA_TEXT_RADIO_STRINGS_H
