// Radio station strings ported from pokecrystal
// Lines fit ~32 char width for 28-tile window

#ifndef GUARD_DATA_TEXT_RADIO_STRINGS_H
#define GUARD_DATA_TEXT_RADIO_STRINGS_H

// ==========================================================
// Station Names (displayed at top of radio UI)
// ==========================================================

static const u8 sRadioStationName_OaksPkmnTalk[]    = _("שיחות פוקימון עם אוק");
static const u8 sRadioStationName_PokedexShow[]     = _("תוכנית הפוקדקס");
static const u8 sRadioStationName_PokemonMusic[]    = _("מוזיקת פוקימון");
static const u8 sRadioStationName_LuckyChannel[]    = _("ערוץ המזל");
static const u8 sRadioStationName_BuenasPassword[]  = _("הסיסמה של בואנה");
static const u8 sRadioStationName_Unown[]           = _("?????");
static const u8 sRadioStationName_PlacesAndPeople[] = _("מקומות ואנשים");
static const u8 sRadioStationName_LetsAllSing[]     = _("בואו נשיר ביחד!");
static const u8 sRadioStationName_PokeFlute[]       = _("חליל פוקימון");

static const u8 sRadioStationName_HoennSound[]  = _("צלילי הואן");

// ==========================================================
// Hoenn Sound
// ==========================================================

static const u8 sRadioText_Hoenn1[] = _("מנגינת פוקימונים מאזור");
static const u8 sRadioText_Hoenn2[] = _("רחוק שנקרא הואן!");
static const u8 sRadioText_Hoenn3[] = _("פוקימונים פראיים מהאזור ההוא");
static const u8 sRadioText_Hoenn4[] = _("עשויים להופיע בסביבה!");

// ==========================================================
// POKéDEX Show
// ==========================================================

static const u8 sRadioText_PokedexShow_Intro[] = _("תוכנית הפוקדקס של אוק!");
static const u8 sRadioText_PokedexShow_TodaysPrefix[] = _("אוק: פוקימון היום הוא ");

// ==========================================================
// Oak's POKéMON Talk
// ==========================================================

static const u8 sRadioText_OPT_Intro[] = _("מרי: שיחות פוקימון עם פרופ' אוק!");
static const u8 sRadioText_OPT_WithMeMary[] = _("ואיתכם, מרי!");
static const u8 sRadioText_OPT_OakPrefix[] = _("אוק: ");
static const u8 sRadioText_OPT_SeenAround[] = _("אפשר לראות אותו באזור");
static const u8 sRadioText_OPT_MaryPrefix[] = _("מרי: ");
static const u8 sRadioText_OPT_MaryIs[] = _(",");

// Pokemon Channel interlude
static const u8 sRadioText_OPT_PokemonChannel[] = _("ערוץ הפוקימון");

// Adverbs (randomly selected)
static const u8 sRadioText_OPT_Adverb_SweetAdorably[]      = _("מתוק ומלבב, וגם");
static const u8 sRadioText_OPT_Adverb_WigglySlickly[]      = _("מתפתל וחלקלק, וגם");
static const u8 sRadioText_OPT_Adverb_AptlyNamed[]         = _("ראוי לשמו, וגם");
static const u8 sRadioText_OPT_Adverb_UndeniablyKindOf[]   = _("ללא ספק די");
static const u8 sRadioText_OPT_Adverb_Unbearably[]         = _("כל כך, כל כך נורא");
static const u8 sRadioText_OPT_Adverb_WowImpressively[]    = _("וואו, מרשים, וגם");
static const u8 sRadioText_OPT_Adverb_AlmostPoisonously[]  = _("כמעט ארסי, וגם");
static const u8 sRadioText_OPT_Adverb_Sensually[]          = _("אוו, חושני, וגם");
static const u8 sRadioText_OPT_Adverb_Mischievously[]      = _("שובב כל כך, וגם");
static const u8 sRadioText_OPT_Adverb_Topically[]          = _("אקטואלי מאוד, וגם");
static const u8 sRadioText_OPT_Adverb_Addictively[]        = _("בהחלט ממכר, וגם");
static const u8 sRadioText_OPT_Adverb_LooksInWater[]       = _("במים הוא נראה");
static const u8 sRadioText_OPT_Adverb_EvolutionMustBe[]    = _("כשיתפתח בטח יהיה");
static const u8 sRadioText_OPT_Adverb_Provocatively[]      = _("מתגרה, וגם");
static const u8 sRadioText_OPT_Adverb_FlippedOut[]         = _("מטורף לגמרי, וגם");
static const u8 sRadioText_OPT_Adverb_HeartMeltingly[]     = _("ממיס לב, וגם");

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
static const u8 sRadioText_OPT_Adj_Cute[]           = _("חמוד.");
static const u8 sRadioText_OPT_Adj_Weird[]          = _("מוזר.");
static const u8 sRadioText_OPT_Adj_Pleasant[]       = _("נעים.");
static const u8 sRadioText_OPT_Adj_BoldSortOf[]     = _("נועז, בערך.");
static const u8 sRadioText_OPT_Adj_Frightening[]    = _("מפחיד.");
static const u8 sRadioText_OPT_Adj_SuaveDebonair[]  = _("אלגנטי ומגונדר!");
static const u8 sRadioText_OPT_Adj_Powerful[]        = _("עוצמתי.");
static const u8 sRadioText_OPT_Adj_Exciting[]        = _("מרגש.");
static const u8 sRadioText_OPT_Adj_Groovy[]          = _("מגניב!");
static const u8 sRadioText_OPT_Adj_Inspiring[]       = _("מעורר השראה.");
static const u8 sRadioText_OPT_Adj_Friendly[]        = _("ידידותי.");
static const u8 sRadioText_OPT_Adj_HotHotHot[]       = _("לוהט, לוהט, לוהט!");
static const u8 sRadioText_OPT_Adj_Stimulating[]     = _("מלהיב.");
static const u8 sRadioText_OPT_Adj_Guarded[]         = _("זהיר.");
static const u8 sRadioText_OPT_Adj_Lovely[]          = _("מקסים.");
static const u8 sRadioText_OPT_Adj_Speedy[]          = _("מהיר.");

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

static const u8 sRadioText_BenIntro[] = _("בן: ערוץ מוזיקת פוקימון!");
static const u8 sRadioText_BenIntro2[] = _("זה אני, הדי-ג'יי בן!");
static const u8 sRadioText_FernIntro[] = _("פרן: פוקימוזיקה!");
static const u8 sRadioText_FernIntro2[] = _("עם הדי-ג'יי פרן!");
// "Today's {DAY}," built dynamically
static const u8 sRadioText_BenFern_TodayIs[] = _("היום ");
static const u8 sRadioText_BenFern_JamTo[] = _("אז בואו נזוז לצלילי");
static const u8 sRadioText_BenFern_ChillTo[] = _("אז תירגעו לצלילי");
static const u8 sRadioText_BenFern_March[] = _("מארש הפוקימונים!");
static const u8 sRadioText_BenFern_Lullaby[] = _("שיר הערש לפוקימונים!");

// ==========================================================
// Lucky Channel
// ==========================================================

static const u8 sRadioText_LC1[] = _("ריד: יי-הא! מה העניינים");
static const u8 sRadioText_LC2[] = _("אצלכם? בין אם אתם בעננים");
static const u8 sRadioText_LC3[] = _("או ממש בקרשים, אל תפספסו את");
static const u8 sRadioText_LC4[] = _("תוכנית מספר המזל!");
static const u8 sRadioText_LC5[] = _("מספר המזל של השבוע הוא");
// "{number}!" built dynamically
static const u8 sRadioText_LC_Repeat[] = _("אחזור על זה!");
static const u8 sRadioText_LC_Match[] = _("יש לכם מספר תואם? בואו");
static const u8 sRadioText_LC_Tower[] = _("למגדל הרדיו!");
static const u8 sRadioText_LC_Drag1[] = _("…לחזור על עצמי");
static const u8 sRadioText_LC_Drag2[] = _("זה די מייגע…");

// ==========================================================
// Places and People
// ==========================================================

static const u8 sRadioText_PnP_Intro[] = _("מקומות ואנשים! בהגשה");
static const u8 sRadioText_PnP_Intro2[] = _("שלי, הדי-ג'יי לילי!");
static const u8 sRadioText_PnP_Space[] = _(" ");

// People adjectives
static const u8 sRadioText_PnP_Cute[]       = _("חמידות אחת גדולה.");
static const u8 sRadioText_PnP_Lazy[]       = _("עושה רושם די עצלני.");
static const u8 sRadioText_PnP_Happy[]      = _("תמיד במצב רוח טוב.");
static const u8 sRadioText_PnP_Noisy[]      = _("עושה די הרבה רעש.");
static const u8 sRadioText_PnP_Precocious[] = _("עם ראש של גדולים.");
static const u8 sRadioText_PnP_Bold[]       = _("עם לא מעט תעוזה.");
static const u8 sRadioText_PnP_Picky[]      = _("עושה יותר מדי עניינים!");
static const u8 sRadioText_PnP_SortOfOK[]   = _("בסדר, פחות או יותר.");
static const u8 sRadioText_PnP_SoSo[]       = _("פשוט ככה-ככה.");
static const u8 sRadioText_PnP_Great[]       = _("דווקא מעולה.");
static const u8 sRadioText_PnP_MyType[]      = _("בדיוק הטיפוס שלי.");
static const u8 sRadioText_PnP_Cool[]        = _("ממש אחלה, לא?");
static const u8 sRadioText_PnP_Inspiring[]   = _("פשוט השראה!");
static const u8 sRadioText_PnP_Weird[]       = _("קצת משונה.");
static const u8 sRadioText_PnP_RightForMe[]  = _("אולי זה בשבילי?");
static const u8 sRadioText_PnP_Odd[]         = _("בהחלט משונה!");

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

static const u8 sRadioStationName_Rocket[] = _("צוות רוקט");
static const u8 sRadioText_Rocket1[]  = _("… …אהם, אנחנו");
static const u8 sRadioText_Rocket2[]  = _("צוות רוקט!");
static const u8 sRadioText_Rocket3[]  = _("אחרי שלוש שנים");
static const u8 sRadioText_Rocket4[]  = _("של הכנות, אנחנו");
static const u8 sRadioText_Rocket5[]  = _("קמנו מחדש");
static const u8 sRadioText_Rocket6[]  = _("מתוך האפר!");
static const u8 sRadioText_Rocket7[]  = _("ג'ובאני!");
static const u8 sRadioText_Rocket8[]  = _("אתה שומע אותנו?");
static const u8 sRadioText_Rocket9[]  = _("");
static const u8 sRadioText_Rocket10[] = _("");

// ==========================================================
// Buena's Password
// ==========================================================

static const u8 sRadioText_Buena1[] = _("בואנה: כאן בואנה!");
static const u8 sRadioText_Buena2[] = _("הסיסמה של היום!");
static const u8 sRadioText_Buena3[] = _("רגע, תנו לי לחשוב… זה");
// "{password}!" built dynamically with STR_VAR_1
static const u8 sRadioText_Buena4[] = _("{STR_VAR_1}!");
static const u8 sRadioText_Buena5[] = _("אל תשכחו אותה! אני");
static const u8 sRadioText_Buena6[] = _("במגדל הרדיו של גולדנרוד!");


// ==========================================================
// Buena's Password Categories & Options
// ==========================================================

static const u8 sRadioBuenaPassword_NewBarkTown[]     = _("העיירה ניו בארק");
static const u8 sRadioBuenaPassword_CherrygroveCity[]  = _("העיר צ'ריגרוב");
static const u8 sRadioBuenaPassword_AzaleaTown[]      = _("העיירה אזייליה");
static const u8 sRadioBuenaPassword_Flying[]          = _("תעופה");
static const u8 sRadioBuenaPassword_Bug[]             = _("חרק");
static const u8 sRadioBuenaPassword_Grass[]           = _("עשב");
static const u8 sRadioBuenaPassword_PkmnTalk[]        = _("שיחות פוקימון");
static const u8 sRadioBuenaPassword_PkmnMusic[]       = _("מוזיקת פוקימון");
static const u8 sRadioBuenaPassword_LuckyChannel[]    = _("ערוץ המזל");

// ==========================================================
// Oak's POKéMON Talk - Special Reports
// ==========================================================

static const u8 sOPT_Report_Clefairy_0[]  = _("מרי: הלילה, רגע נדיר לאור הירח");
static const u8 sOPT_Report_Clefairy_1[]  = _("בשיחות פוקימון!");
static const u8 sOPT_Report_Clefairy_2[]  = _("אוק: הזרקור שלנו מופנה אל");
static const u8 sOPT_Report_Clefairy_3[]  = _("קלפרי המסתורי!");
static const u8 sOPT_Report_Clefairy_4[]  = _("הם מתאספים בהר הירח");
static const u8 sOPT_Report_Clefairy_5[]  = _("בלילות של ירח מלא.");
static const u8 sOPT_Report_Clefairy_6[]  = _("מרי: הם רוקדים במעגלים!");
static const u8 sOPT_Report_Clefairy_7[]  = _("מוזרים ומקסימים כל כך!");
static const u8 sOPT_Report_Clefairy_8[]  = _("אוק: תעלומה נצחית");
static const u8 sOPT_Report_Clefairy_9[]  = _("ומחזה מרהיב!");

static const u8 sOPT_Report_Lapras_0[]  = _("מרי: ענק עדין עולה");
static const u8 sOPT_Report_Lapras_1[]  = _("לבמה בתוכנית של היום!");
static const u8 sOPT_Report_Lapras_2[]  = _("אוק: זו מעבורת האוקיינוס,");
static const u8 sOPT_Report_Lapras_3[]  = _("לפרס האהוב שלנו!");
static const u8 sOPT_Report_Lapras_4[]  = _("רואים אותו במערת האיחוד, אבל");
static const u8 sOPT_Report_Lapras_5[]  = _("לא בשום מקום אחר. מסקרן!");
static const u8 sOPT_Report_Lapras_6[]  = _("מרי: כל כך נדיר ושליו!");
static const u8 sOPT_Report_Lapras_7[]  = _("והוא גם שר!");
static const u8 sOPT_Report_Lapras_8[]  = _("אוק: יש אומרים שהשירים שלו");
static const u8 sOPT_Report_Lapras_9[]  = _("מרגיעים את נשמת הים.");

static const u8 sOPT_Report_Ampharos_0[]  = _("מרי: ברוכים השבים, מאזינים!");
static const u8 sOPT_Report_Ampharos_1[]  = _("הגיע הזמן לשיחות פוקימון!");
static const u8 sOPT_Report_Ampharos_2[]  = _("אוק: בואו נשפוך אור על");
static const u8 sOPT_Report_Ampharos_3[]  = _("ידידנו אמפרוס!");
static const u8 sOPT_Report_Ampharos_4[]  = _("הזנב הבוהק שלו זוהר מבעד");
static const u8 sOPT_Report_Ampharos_5[]  = _("לערפל ומנחה את מי שהלך לאיבוד.");
static const u8 sOPT_Report_Ampharos_6[]  = _("מרי: חזק, אלגנטי,");
static const u8 sOPT_Report_Ampharos_7[]  = _("וללא ספק ידידותי!");
static const u8 sOPT_Report_Ampharos_8[]  = _("אוק: חלק חשוב בהרבה");
static const u8 sOPT_Report_Ampharos_9[]  = _("סיפורי מגדלורים!");

static const u8 sOPT_Report_Sudowoodo_0[]  = _("מרי: ועכשיו, יצור משונה באמת");
static const u8 sOPT_Report_Sudowoodo_1[]  = _("בדרך 36…");
static const u8 sOPT_Report_Sudowoodo_2[]  = _("אוק: סודוודו! הוא נראה כמו");
static const u8 sOPT_Report_Sudowoodo_3[]  = _("עץ, אבל הוא לא עץ!");
static const u8 sOPT_Report_Sudowoodo_4[]  = _("הוא חוסם את הדרך ולא");
static const u8 sOPT_Report_Sudowoodo_5[]  = _("יזוז בלי מים.");
static const u8 sOPT_Report_Sudowoodo_6[]  = _("מרי: הוא מגיב רק");
static const u8 sOPT_Report_Sudowoodo_7[]  = _("לבקבוק התזה!");
static const u8 sOPT_Report_Sudowoodo_8[]  = _("אוק: זה לא שיח, זה פוקימון");
static const u8 sOPT_Report_Sudowoodo_9[]  = _("מסוג סלע בתחפושת!");

static const u8 sOPT_Report_RedGyarados_0[]  = _("מרי: היום יש לנו סיפור");
static const u8 sOPT_Report_RedGyarados_1[]  = _("מסעיר מג'וטו!");
static const u8 sOPT_Report_RedGyarados_2[]  = _("אוק: מאמנים ראו גרידוס");
static const u8 sOPT_Report_RedGyarados_3[]  = _("אדום באגם הזעם!");
static const u8 sOPT_Report_RedGyarados_4[]  = _("בניגוד לכחולים הרגילים,");
static const u8 sOPT_Report_RedGyarados_5[]  = _("הוא בצבע ארגמן בוהק!");
static const u8 sOPT_Report_RedGyarados_6[]  = _("מרי: אומרים שזה קשור");
static const u8 sOPT_Report_RedGyarados_7[]  = _("לגלי רדיו משונים!");
static const u8 sOPT_Report_RedGyarados_8[]  = _("אוק: התפתחות מסתורית…");
static const u8 sOPT_Report_RedGyarados_9[]  = _("אולי לא טבעית.");

static const u8 sOPT_Report_Unown_0[]  = _("מרי: ביקרתם פעם בחורבות אלף?");
static const u8 sOPT_Report_Unown_1[]  = _("ממש מצמרר!");
static const u8 sOPT_Report_Unown_2[]  = _("אוק: סמלים מוזרים מכסים את");
static const u8 sOPT_Report_Unown_3[]  = _("הקירות, כמו כתב רונות עתיק.");
static const u8 sOPT_Report_Unown_4[]  = _("בפנים אפשר למצוא אנון…");
static const u8 sOPT_Report_Unown_5[]  = _("כל אחד מהם בצורת אות!");
static const u8 sOPT_Report_Unown_6[]  = _("מרי: אולי הם מאייתים משהו?");
static const u8 sOPT_Report_Unown_7[]  = _("או שהם סתם מפחידים אותנו!");
static const u8 sOPT_Report_Unown_8[]  = _("אוק: חידה אמיתית של הטבע,");
static const u8 sOPT_Report_Unown_9[]  = _("שלא נפתרה עד היום.");

static const u8 sOPT_Report_Snubbull_0[]  = _("מרי: תושבי גולדנרוד");
static const u8 sOPT_Report_Snubbull_1[]  = _("מחפשים בכל פינה!");
static const u8 sOPT_Report_Snubbull_2[]  = _("אוק: סנאבול אחד יצא משליטה");
static const u8 sOPT_Report_Snubbull_3[]  = _("ועכשיו הוא במנוסה!");
static const u8 sOPT_Report_Snubbull_4[]  = _("בדרך כלל הוא ביישן ובררן,");
static const u8 sOPT_Report_Snubbull_5[]  = _("אבל ראו אותו ליד התחנה.");
static const u8 sOPT_Report_Snubbull_6[]  = _("מרי: אולי הוא רודף אחרי");
static const u8 sOPT_Report_Snubbull_7[]  = _("אהבה… או סתם הרפתקה!");
static const u8 sOPT_Report_Snubbull_8[]  = _("אוק: פקחו עיניים,");
static const u8 sOPT_Report_Snubbull_9[]  = _("והכינו את הרצועה.");

static const u8 sOPT_Report_Slowpoke_0[]  = _("מרי: חדשות גדולות השבוע");
static const u8 sOPT_Report_Slowpoke_1[]  = _("מהעיירה אזייליה!");
static const u8 sOPT_Report_Slowpoke_2[]  = _("אוק: הסלופוק חזרו");
static const u8 sOPT_Report_Slowpoke_3[]  = _("לבאר שלהם אחרי משבר!");
static const u8 sOPT_Report_Slowpoke_4[]  = _("צוות רוקט כרת להם");
static const u8 sOPT_Report_Slowpoke_5[]  = _("את הזנבות! נורא!");
static const u8 sOPT_Report_Slowpoke_6[]  = _("מרי: אבל מאמן צעיר ואמיץ");
static const u8 sOPT_Report_Slowpoke_7[]  = _("עצר אותם!");
static const u8 sOPT_Report_Slowpoke_8[]  = _("אוק: הסלופוק כבר לא בסכנה");
static const u8 sOPT_Report_Slowpoke_9[]  = _("ושוב מנמנמים בשמחה.");

static const u8 sOPT_Report_LavenderTower_0[]  = _("מרי: המגדל בעיירה לבנדר");
static const u8 sOPT_Report_LavenderTower_1[]  = _("שינה את הנעימה!");
static const u8 sOPT_Report_LavenderTower_2[]  = _("אוק: מגדל הרפאים הישן הוא");
static const u8 sOPT_Report_LavenderTower_3[]  = _("עכשיו תחנת רדיו!");
static const u8 sOPT_Report_LavenderTower_4[]  = _("כמה תושבים אומרים שעדיין");
static const u8 sOPT_Report_LavenderTower_5[]  = _("יש שם אווירה… מצמררת.");
static const u8 sOPT_Report_LavenderTower_6[]  = _("מרי: אני נשבעת שראיתי גסטלי");
static const u8 sOPT_Report_LavenderTower_7[]  = _("ליד תא השידור!");
static const u8 sOPT_Report_LavenderTower_8[]  = _("אוק: אולי אלה הפרעות קליטה…");
static const u8 sOPT_Report_LavenderTower_9[]  = _("או רוחות רפאים!");

static const u8 sOPT_Report_Tentacruel_0[]  = _("מרי: חדשות מוזרות היום");
static const u8 sOPT_Report_Tentacruel_1[]  = _("מאיי המערבולת!");
static const u8 sOPT_Report_Tentacruel_2[]  = _("אוק: טנטקרול רבים מקיפים");
static const u8 sOPT_Report_Tentacruel_3[]  = _("את פתחי המערות!");
static const u8 sOPT_Report_Tentacruel_4[]  = _("הם ענקיים, ומתנהגים");
static const u8 sOPT_Report_Tentacruel_5[]  = _("בצורה כמעט טריטוריאלית.");
static const u8 sOPT_Report_Tentacruel_6[]  = _("מרי: הם חוסמים את הדרך");
static const u8 sOPT_Report_Tentacruel_7[]  = _("בלי לתקוף…");
static const u8 sOPT_Report_Tentacruel_8[]  = _("אוק: כאילו הם שומרים על משהו");
static const u8 sOPT_Report_Tentacruel_9[]  = _("עמוק מתחת לגלים.");

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
