const struct AbilityInfo gAbilitiesInfo[ABILITIES_COUNT] =
{
    [ABILITY_NONE] =
    {
        .name = _("-------"),
        .description = COMPOUND_STRING("אין יכולת מיוחדת."),
        .aiRating = 0,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_STENCH] =
    {
        .name = _("צחנה"),
        .description = COMPOUND_STRING("עשוי לגרום ליריב להירתע."),
        .aiRating = 1,
    },

    [ABILITY_DRIZZLE] =
    {
        .name = _("טפטוף"),
        .description = COMPOUND_STRING("מזמן גשם בקרב."),
        .aiRating = 9,
    },

    [ABILITY_SPEED_BOOST] =
    {
        .name = _("מאיץ מהירות"),
        .description = COMPOUND_STRING("מגביר מהירות בהדרגה."),
        .aiRating = 9,
    },

    [ABILITY_BATTLE_ARMOR] =
    {
        .name = _("שריון קרב"),
        .description = COMPOUND_STRING("חוסם פגיעות קריטיות."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_STURDY] =
    {
        .name = _("איתן"),
        .description = COMPOUND_STRING("חסין לחיסול במכה אחת."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DAMP] =
    {
        .name = _("לחות"),
        .description = COMPOUND_STRING("מונע השמדה עצמית."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_LIMBER] =
    {
        .name = _("גמיש"),
        .description = COMPOUND_STRING("מונע שיתוק."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SAND_VEIL] =
    {
        .name = _("מסווה חול"),
        .description = COMPOUND_STRING("מעלה התחמקות בסופת חול."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_STATIC] =
    {
        .name = _("סטטי"),
        .description = COMPOUND_STRING("משתק במגע."),
        .aiRating = 4,
    },

    [ABILITY_VOLT_ABSORB] =
    {
        .name = _("ספיגת וולט"),
        .description = COMPOUND_STRING("הופך חשמל לנ”ח."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_WATER_ABSORB] =
    {
        .name = _("ספיגת מים"),
        .description = COMPOUND_STRING("הופך מים לנ”ח."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_OBLIVIOUS] =
    {
        .name = _("תמים"),
        .description = COMPOUND_STRING("מונע התאהבות."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_CLOUD_NINE] =
    {
        .name = _("ענן תשע"),
        .description = COMPOUND_STRING("מבטל השפעות מזג אוויר."),
        .aiRating = 5,
    },

    [ABILITY_COMPOUND_EYES] =
    {
        .name = _("עין מורכבת"),
        .description = COMPOUND_STRING("מעלה דיוק."),
        .aiRating = 7,
    },

    [ABILITY_INSOMNIA] =
    {
        .name = _("נדודי שינה"),
        .description = COMPOUND_STRING("מונע שינה."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_COLOR_CHANGE] =
    {
        .name = _("שינוי צבע"),
        .description = COMPOUND_STRING("משנה סוג לפי מהלך היריב."),
        .aiRating = 2,
    },

    [ABILITY_IMMUNITY] =
    {
        .name = _("חסינות"),
        .description = COMPOUND_STRING("מונע הרעלה."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_FLASH_FIRE] =
    {
        .name = _("אש מבזיקה"),
        .description = COMPOUND_STRING("מתחזק כשנפגע מאש."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SHIELD_DUST] =
    {
        .name = _("אבק מגן"),
        .description = COMPOUND_STRING("מונע השפעות משניות."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_OWN_TEMPO] =
    {
        .name = _("קצב עצמי"),
        .description = COMPOUND_STRING("מונע בלבול."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SUCTION_CUPS] =
    {
        .name = _("כוסות יניקה"),
        .description = COMPOUND_STRING("מעגן את הגוף בחוזקה."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_INTIMIDATE] =
    {
        .name = _("הפחדה"),
        .description = COMPOUND_STRING("מוריד את התקפת היריב."),
        .aiRating = 7,
    },

    [ABILITY_SHADOW_TAG] =
    {
        .name = _("תג צל"),
        .description = COMPOUND_STRING("מונע מהיריב לברוח."),
        .aiRating = 10,
    },

    [ABILITY_ROUGH_SKIN] =
    {
        .name = _("עור מחוספס"),
        .description = COMPOUND_STRING("כואב לגעת בו."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_GUARD] =
    {
        .name = _("משמר פלא"),
        .description = COMPOUND_STRING("רק מכות יעילות במיוחד."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_LEVITATE] =
    {
        .name = _("ריחוף"),
        .description = COMPOUND_STRING("לא נפגע מהתקפות אדמה."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EFFECT_SPORE] =
    {
        .name = _("נבג אפקט"),
        .description = COMPOUND_STRING("משאיר נבגים במגע."),
        .aiRating = 4,
    },

    [ABILITY_SYNCHRONIZE] =
    {
        .name = _("סנכרון"),
        .description = COMPOUND_STRING("מעביר בעיות מצב ליריב."),
        .aiRating = 4,
    },

    [ABILITY_CLEAR_BODY] =
    {
        .name = _("גוף נקי"),
        .description = COMPOUND_STRING("מונע הורדת נתונים."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_NATURAL_CURE] =
    {
        .name = _("ריפוי טבעי"),
        .description = COMPOUND_STRING("מחלים כשהוא מתחלף."),
        .aiRating = 7,
    },

    [ABILITY_LIGHTNING_ROD] =
    {
        .name = _("מוט ברקים"),
        .description = COMPOUND_STRING("מושך מהלכי חשמל."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_SERENE_GRACE] =
    {
        .name = _("חסד שליו"),
        .description = COMPOUND_STRING("מגביר השפעות משניות."),
        .aiRating = 8,
    },

    [ABILITY_SWIFT_SWIM] =
    {
        .name = _("שחייה מהירה"),
        .description = COMPOUND_STRING("מעלה מהירות בגשם."),
        .aiRating = 6,
    },

    [ABILITY_CHLOROPHYLL] =
    {
        .name = _("כלורופיל"),
        .description = COMPOUND_STRING("מעלה מהירות בשמש."),
        .aiRating = 6,
    },

    [ABILITY_ILLUMINATE] =
    {
        .name = _("הארה"),
        .description = COMPOUND_STRING("מגביר את שיעור המפגשים."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_TRACE] =
    {
        .name = _("עקבות"),
        .description = COMPOUND_STRING("מעתיק יכולת מיוחדת."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE, //B_UPDATED_ABILITY_DATA >= GEN_4
    },

    [ABILITY_HUGE_POWER] =
    {
        .name = _("כוח עצום"),
        .description = COMPOUND_STRING("מעלה התקפה."),
        .aiRating = 10,
    },

    [ABILITY_POISON_POINT] =
    {
        .name = _("נקודת רעל"),
        .description = COMPOUND_STRING("מרעיל את היריב במגע."),
        .aiRating = 4,
    },

    [ABILITY_INNER_FOCUS] =
    {
        .name = _("מיקוד פנימי"),
        .description = COMPOUND_STRING("מונע רתיעה."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MAGMA_ARMOR] =
    {
        .name = _("שריון מגמה"),
        .description = COMPOUND_STRING("מונע קיפאון."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_WATER_VEIL] =
    {
        .name = _("צעיף מים"),
        .description = COMPOUND_STRING("מונע כוויות."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_MAGNET_PULL] =
    {
        .name = _("משיכת מגנט"),
        .description = COMPOUND_STRING("לוכד פוקימונים מסוג פלדה."),
        .aiRating = 9,
    },

    [ABILITY_SOUNDPROOF] =
    {
        .name = _("אטום לרעש"),
        .description = COMPOUND_STRING("חסין למהלכי קול."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_RAIN_DISH] =
    {
        .name = _("צלחת גשם"),
        .description = COMPOUND_STRING("משקם מעט נ”ח בגשם."),
        .aiRating = 3,
    },

    [ABILITY_SAND_STREAM] =
    {
        .name = _("זרם חול"),
        .description = COMPOUND_STRING("מזמן סופת חול."),
        .aiRating = 9,
    },

    [ABILITY_PRESSURE] =
    {
        .name = _("לחץ"),
        .description = COMPOUND_STRING("מגביר צריכת נ”כ של היריב."),
        .aiRating = 5,
    },

    [ABILITY_THICK_FAT] =
    {
        .name = _("שומן עבה"),
        .description = COMPOUND_STRING("הגנה מפני חום וקור."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_EARLY_BIRD] =
    {
        .name = _("ציפור מקדימה"),
        .description = COMPOUND_STRING("מתעורר מהר משינה."),
        .aiRating = 4,
    },

    [ABILITY_FLAME_BODY] =
    {
        .name = _("גוף להבה"),
        .description = COMPOUND_STRING("מכווה את היריב במגע."),
        .aiRating = 4,
    },

    [ABILITY_RUN_AWAY] =
    {
        .name = _("בריחה"),
        .description = COMPOUND_STRING("מקל על בריחה."),
        .aiRating = 0,
    },

    [ABILITY_KEEN_EYE] =
    {
        .name = _("עין חדה"),
        .description = COMPOUND_STRING("מונע אובדן דיוק."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_HYPER_CUTTER] =
    {
        .name = _("על חותך"),
        .description = COMPOUND_STRING("מונע הורדת התקפה."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PICKUP] =
    {
        .name = _("איסוף"),
        .description = COMPOUND_STRING("עשוי לאסוף פריטים."),
        .aiRating = 1,
    },

    [ABILITY_TRUANT] =
    {
        .name = _("עצלן"),
        .description = COMPOUND_STRING("פועל רק כל תור שני."),
        .aiRating = -2,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HUSTLE] =
    {
        .name = _("המולה"),
        .description = COMPOUND_STRING("מחליף דיוק בעוצמה."),
        .aiRating = 7,
    },

    [ABILITY_CUTE_CHARM] =
    {
        .name = _("קסם חמוד"),
        .description = COMPOUND_STRING("גורם להתאהבות במגע."),
        .aiRating = 2,
    },

    [ABILITY_PLUS] =
    {
        .name = _("פלוס"),
        .description = COMPOUND_STRING("מתחזק לצד ”מינוס”."),
        .aiRating = 0,
    },

    [ABILITY_MINUS] =
    {
        .name = _("מינוס"),
        .description = COMPOUND_STRING("מתחזק לצד ”פלוס”."),
        .aiRating = 0,
    },

    [ABILITY_FORECAST] =
    {
        .name = _("תחזית"),
        .description = COMPOUND_STRING("משתנה לפי מזג האוויר."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_4,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_STICKY_HOLD] =
    {
        .name = _("אחיזה דביקה"),
        .description = COMPOUND_STRING("מונע גניבת פריטים."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_SHED_SKIN] =
    {
        .name = _("השלת עור"),
        .description = COMPOUND_STRING("מרפא את עצמו בהשלת עור."),
        .aiRating = 7,
    },

    [ABILITY_GUTS] =
    {
        .name = _("אומץ"),
        .description = COMPOUND_STRING("בעיית מצב מעלה התקפה."),
        .aiRating = 6,
    },

    [ABILITY_MARVEL_SCALE] =
    {
        .name = _("קשקשת פלא"),
        .description = COMPOUND_STRING("בעיית מצב מעלה הגנה."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_LIQUID_OOZE] =
    {
        .name = _("רפש נוזלי"),
        .description = COMPOUND_STRING("יניקה ממנו גורמת נזק."),
        .aiRating = 3,
    },

    [ABILITY_OVERGROW] =
    {
        .name = _("צמיחת יתר"),
        .description = COMPOUND_STRING("מגביר מהלכי עשב במצוקה."),
        .aiRating = 5,
    },

    [ABILITY_BLAZE] =
    {
        .name = _("להבה"),
        .description = COMPOUND_STRING("מגביר מהלכי אש במצוקה."),
        .aiRating = 5,
    },

    [ABILITY_TORRENT] =
    {
        .name = _("זרם"),
        .description = COMPOUND_STRING("מגביר מהלכי מים במצוקה."),
        .aiRating = 5,
    },

    [ABILITY_SWARM] =
    {
        .name = _("נחיל"),
        .description = COMPOUND_STRING("מגביר מהלכי חרק במצוקה."),
        .aiRating = 5,
    },

    [ABILITY_ROCK_HEAD] =
    {
        .name = _("ראש סלע"),
        .description = COMPOUND_STRING("מונע נזק רתע."),
        .aiRating = 5,
    },

    [ABILITY_DROUGHT] =
    {
        .name = _("בצורת"),
        .description = COMPOUND_STRING("מזמן אור שמש בקרב."),
        .aiRating = 9,
    },

    [ABILITY_ARENA_TRAP] =
    {
        .name = _("מלכודת זירה"),
        .description = COMPOUND_STRING("מונע בריחה."),
        .aiRating = 9,
    },

    [ABILITY_VITAL_SPIRIT] =
    {
        .name = _("רוח חיונית"),
        .description = COMPOUND_STRING("מונע שינה."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_WHITE_SMOKE] =
    {
        .name = _("עשן לבן"),
        .description = COMPOUND_STRING("מונע הורדת נתונים."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_PURE_POWER] =
    {
        .name = _("כוח טהור"),
        .description = COMPOUND_STRING("מעלה התקפה."),
        .aiRating = 10,
    },

    [ABILITY_SHELL_ARMOR] =
    {
        .name = _("שריון קונכיה"),
        .description = COMPOUND_STRING("חוסם פגיעות קריטיות."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_AIR_LOCK] =
    {
        .name = _("נעילת אוויר"),
        .description = COMPOUND_STRING("מבטל השפעות מזג אוויר."),
        .aiRating = 5,
    },

    [ABILITY_TANGLED_FEET] =
    {
        .name = _("רגליים מסתבכות"),
        .description = COMPOUND_STRING("מעלה התחמקות כשמבולבל."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MOTOR_DRIVE] =
    {
        .name = _("הנעת מנוע"),
        .description = COMPOUND_STRING("חשמל מעלה את מהירותו."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_RIVALRY] =
    {
        .name = _("יריבות"),
        .description = COMPOUND_STRING("מתחזק מול מתחרים."),
        .aiRating = 1,
    },

    [ABILITY_STEADFAST] =
    {
        .name = _("נחישות"),
        .description = COMPOUND_STRING("רתיעה מעלה את מהירותו."),
        .aiRating = 2,
    },

    [ABILITY_SNOW_CLOAK] =
    {
        .name = _("גלימת שלג"),
        .description = COMPOUND_STRING("מעלה התחמקות בברד או שלג."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_GLUTTONY] =
    {
        .name = _("גרגרנות"),
        .description = COMPOUND_STRING("אוכל פירות מוקדם מהרגיל."),
        .aiRating = 3,
    },

    [ABILITY_ANGER_POINT] =
    {
        .name = _("נקודת זעם"),
        .description = COMPOUND_STRING("פגיעה קריטית מעלה התקפה."),
        .aiRating = 4,
    },

    [ABILITY_UNBURDEN] =
    {
        .name = _("פריקת משא"),
        .description = COMPOUND_STRING("שימוש בפריטו מעלה מהירות."),
        .aiRating = 7,
    },

    [ABILITY_HEATPROOF] =
    {
        .name = _("חסין חום"),
        .description = COMPOUND_STRING("הגנה מפני חום וכוויות."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SIMPLE] =
    {
        .name = _("פשוט"),
        .description = COMPOUND_STRING("נוטה לשינויי נתונים קיצוניים."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_DRY_SKIN] =
    {
        .name = _("עור יבש"),
        .description = COMPOUND_STRING("מעדיף לחות על פני חום."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_DOWNLOAD] =
    {
        .name = _("הורדה"),
        .description = COMPOUND_STRING("מכוונן עוצמה לטובתו."),
        .aiRating = 7,
    },

    [ABILITY_IRON_FIST] =
    {
        .name = _("אגרוף ברזל"),
        .description = COMPOUND_STRING("מגביר מהלכי אגרוף."),
        .aiRating = 6,
    },

    [ABILITY_POISON_HEAL] =
    {
        .name = _("ריפוי ברעל"),
        .description = COMPOUND_STRING("משקם נ”ח כשהוא מורעל."),
        .aiRating = 8,
    },

    [ABILITY_ADAPTABILITY] =
    {
        .name = _("הסתגלות"),
        .description = COMPOUND_STRING("מגביר התקפות מסוגו."),
        .aiRating = 8,
    },

    [ABILITY_SKILL_LINK] =
    {
        .name = _("שרשרת מיומנות"),
        .description = COMPOUND_STRING("מהלכי רצף פוגעים 5 פעמים."),
        .aiRating = 7,
    },

    [ABILITY_HYDRATION] =
    {
        .name = _("הרוויה"),
        .description = COMPOUND_STRING("מרפא בעיות מצב בגשם."),
        .aiRating = 4,
    },

    [ABILITY_SOLAR_POWER] =
    {
        .name = _("כוח שמש"),
        .description = COMPOUND_STRING("מתחזק בשמש."),
        .aiRating = 3,
    },

    [ABILITY_QUICK_FEET] =
    {
        .name = _("רגליים מהירות"),
        .description = COMPOUND_STRING("בעיית מצב מעלה מהירות."),
        .aiRating = 5,
    },

    [ABILITY_NORMALIZE] =
    {
        .name = _("נרמול"),
        .description = COMPOUND_STRING("מהלכיו הופכים לסוג רגיל."),
        .aiRating = -1,
    },

    [ABILITY_SNIPER] =
    {
        .name = _("צלף"),
        .description = COMPOUND_STRING("מגביר פגיעות קריטיות."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_GUARD] =
    {
        .name = _("משמר קסם"),
        .description = COMPOUND_STRING("נפגע רק מהתקפות."),
        .aiRating = 9,
    },

    [ABILITY_NO_GUARD] =
    {
        .name = _("ללא משמר"),
        .description = COMPOUND_STRING("כל המהלכים פוגעים בוודאות."),
        .aiRating = 8,
    },

    [ABILITY_STALL] =
    {
        .name = _("השהיה"),
        .description = COMPOUND_STRING("תמיד פועל אחרון."),
        .aiRating = -1,
    },

    [ABILITY_TECHNICIAN] =
    {
        .name = _("טכנאי"),
        .description = COMPOUND_STRING("מגביר מהלכים חלשים."),
        .aiRating = 8,
    },

    [ABILITY_LEAF_GUARD] =
    {
        .name = _("משמר עלים"),
        .description = COMPOUND_STRING("חוסם בעיות מצב בשמש."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_KLUTZ] =
    {
        .name = _("שלומיאל"),
        .description = COMPOUND_STRING("לא יכול להפעיל פריט מוחזק."),
        .aiRating = -1,
    },

    [ABILITY_MOLD_BREAKER] =
    {
        .name = _("שובר תבניות"),
        .description = COMPOUND_STRING("מהלכיו עוקפים יכולות."),
        .aiRating = 7,
    },

    [ABILITY_SUPER_LUCK] =
    {
        .name = _("מזל על"),
        .description = COMPOUND_STRING("פגיעות קריטיות תכופות."),
        .aiRating = 3,
    },

    [ABILITY_AFTERMATH] =
    {
        .name = _("השלכות"),
        .description = COMPOUND_STRING("התעלפותו פוגעת ביריב."),
        .aiRating = 5,
    },

    [ABILITY_ANTICIPATION] =
    {
        .name = _("ציפייה"),
        .description = COMPOUND_STRING("חש במהלכים מסוכנים."),
        .aiRating = 2,
    },

    [ABILITY_FOREWARN] =
    {
        .name = _("התרעה"),
        .description = COMPOUND_STRING("מזהה מהלך של היריב."),
        .aiRating = 2,
    },

    [ABILITY_UNAWARE] =
    {
        .name = _("לא מודע"),
        .description = COMPOUND_STRING("מתעלם משינויי נתונים."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_TINTED_LENS] =
    {
        .name = _("עדשה כהה"),
        .description = COMPOUND_STRING("מגביר מכות לא כל כך יעילות."),
        .aiRating = 7,
    },

    [ABILITY_FILTER] =
    {
        .name = _("מסנן"),
        .description = COMPOUND_STRING("מחליש מכות יעילות במיוחד."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SLOW_START] =
    {
        .name = _("התחלה איטית"),
        .description = COMPOUND_STRING("לוקח לו זמן להתחמם."),
        .aiRating = -2,
    },

    [ABILITY_SCRAPPY] =
    {
        .name = _("לוחמני"),
        .description = COMPOUND_STRING("פוגע בפוקימונים מסוג רוח."),
        .aiRating = 6,
    },

    [ABILITY_STORM_DRAIN] =
    {
        .name = _("תעלת ניקוז"),
        .description = COMPOUND_STRING("מושך מהלכי מים."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_ICE_BODY] =
    {
        .name = _("גוף קרח"),
        .description = COMPOUND_STRING("משקם נ”ח בברד או שלג."),
        .aiRating = 3,
    },

    [ABILITY_SOLID_ROCK] =
    {
        .name = _("סלע מוצק"),
        .description = COMPOUND_STRING("מחליש מכות יעילות במיוחד."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_SNOW_WARNING] =
    {
        .name = _("אזהרת שלג"),
    #if B_SNOW_WARNING >= GEN_9
        .description = COMPOUND_STRING("מזמן שלג בקרב."),
    #else
        .description = COMPOUND_STRING("Summons hail in battle."),
    #endif
        .aiRating = 8,
    },

    [ABILITY_HONEY_GATHER] =
    {
        .name = _("איסוף דבש"),
        .description = COMPOUND_STRING("עשוי לאסוף דבש."),
        .aiRating = 0,
    },

    [ABILITY_FRISK] =
    {
        .name = _("חיפוש גופני"),
        .description = COMPOUND_STRING("בודק את הפריט של היריב."),
        .aiRating = 3,
    },

    [ABILITY_RECKLESS] =
    {
        .name = _("פזיזות"),
        .description = COMPOUND_STRING("מגביר מהלכים עם נזק רתע."),
        .aiRating = 6,
    },

    [ABILITY_MULTITYPE] =
    {
        .name = _("ריבוי סוגים"),
        .description = COMPOUND_STRING("משנה סוג לפי הלוח שלו."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = B_UPDATED_ABILITY_DATA >= GEN_5,
    },

    [ABILITY_FLOWER_GIFT] =
    {
        .name = _("מתנת פרחים"),
        .description = COMPOUND_STRING("ידידים מתחזקים בשמש."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeTraced = B_UPDATED_ABILITY_DATA >= GEN_5,
        .breakable = TRUE,
    },

    [ABILITY_BAD_DREAMS] =
    {
        .name = _("חלומות רעים"),
        .description = COMPOUND_STRING("פוגע בפוקימונים ישנים."),
        .aiRating = 4,
    },

    [ABILITY_PICKPOCKET] =
    {
        .name = _("כייס"),
        .description = COMPOUND_STRING("גונב את פריט היריב."),
        .aiRating = 3,
    },

    [ABILITY_SHEER_FORCE] =
    {
        .name = _("כוח מוחלט"),
        .description = COMPOUND_STRING("מחליף השפעות בעוצמה."),
        .aiRating = 8,
    },

    [ABILITY_CONTRARY] =
    {
        .name = _("דווקאי"),
        .description = COMPOUND_STRING("הופך את שינויי הנתונים."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_UNNERVE] =
    {
        .name = _("מורט עצבים"),
        .description = COMPOUND_STRING("מונע מיריבים לאכול פירות."),
        .aiRating = 3,
    },

    [ABILITY_DEFIANT] =
    {
        .name = _("התרסה"),
        .description = COMPOUND_STRING("הורדת נתונים מעלה התקפה."),
        .aiRating = 5,
    },

    [ABILITY_DEFEATIST] =
    {
        .name = _("תבוסתנות"),
        .description = COMPOUND_STRING("מתייאש בחצי נ”ח."),
        .aiRating = -1,
    },

    [ABILITY_CURSED_BODY] =
    {
        .name = _("גוף מקולל"),
        .description = COMPOUND_STRING("משבית מהלכים במגע."),
        .aiRating = 4,
    },

    [ABILITY_HEALER] =
    {
        .name = _("מרפא"),
        .description = COMPOUND_STRING("מרפא פוקימון שותף."),
        .aiRating = 0,
    },

    [ABILITY_FRIEND_GUARD] =
    {
        .name = _("משמר ידידים"),
        .description = COMPOUND_STRING("מפחית נזק לשותף."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_WEAK_ARMOR] =
    {
        .name = _("שריון חלש"),
        .description = COMPOUND_STRING("נתוניו משתנים כשהוא נפגע."),
        .aiRating = 2,
    },

    [ABILITY_HEAVY_METAL] =
    {
        .name = _("מתכת כבדה"),
        .description = COMPOUND_STRING("מכפיל את המשקל."),
        .aiRating = -1,
        .breakable = TRUE,
    },

    [ABILITY_LIGHT_METAL] =
    {
        .name = _("מתכת קלה"),
        .description = COMPOUND_STRING("מקטין את המשקל בחצי."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_MULTISCALE] =
    {
        .name = _("ריבוי קשקשים"),
        .description = COMPOUND_STRING("סופג חצי נזק במלוא הנ”ח."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_TOXIC_BOOST] =
    {
        .name = _("דחף הרעלה"),
        .description = COMPOUND_STRING("מעלה התקפה כשהוא מורעל."),
        .aiRating = 6,
    },

    [ABILITY_FLARE_BOOST] =
    {
        .name = _("דחף להבה"),
        .description = COMPOUND_STRING("מעלה התקפה מיוחדת כשנכווה."),
        .aiRating = 5,
    },

    [ABILITY_HARVEST] =
    {
        .name = _("קציר"),
        .description = COMPOUND_STRING("עשוי למחזר פרי שנאכל."),
        .aiRating = 5,
    },

    [ABILITY_TELEPATHY] =
    {
        .name = _("טלפתיה"),
        .description = COMPOUND_STRING("לא נפגע מידיד."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_MOODY] =
    {
        .name = _("הפכפך"),
        .description = COMPOUND_STRING("נתוניו משתנים בהדרגה."),
        .aiRating = 10,
    },

    [ABILITY_OVERCOAT] =
    {
        .name = _("מעיל עליון"),
        .description = COMPOUND_STRING("חוסם מזג אוויר ואבקות."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_POISON_TOUCH] =
    {
        .name = _("מגע רעיל"),
        .description = COMPOUND_STRING("מרעיל את היריב במגע."),
        .aiRating = 4,
    },

    [ABILITY_REGENERATOR] =
    {
        .name = _("התחדשות"),
        .description = COMPOUND_STRING("מחלים כשהוא מתחלף."),
        .aiRating = 8,
    },

    [ABILITY_BIG_PECKS] =
    {
        .name = _("חזה מנופח"),
        .description = COMPOUND_STRING("מונע ירידה בהגנה."),
        .aiRating = 1,
        .breakable = TRUE,
    },

    [ABILITY_SAND_RUSH] =
    {
        .name = _("דהירת חול"),
        .description = COMPOUND_STRING("מעלה מהירות בסופת חול."),
        .aiRating = 6,
    },

    [ABILITY_WONDER_SKIN] =
    {
        .name = _("עור פלא"),
        .description = COMPOUND_STRING("עשוי להימנע מבעיות מצב."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANALYTIC] =
    {
        .name = _("אנליטי"),
        .description = COMPOUND_STRING("מתחזק כשהוא פועל אחרון."),
        .aiRating = 5,
    },

    [ABILITY_ILLUSION] =
    {
        .name = _("אחיזת עיניים"),
        .description = COMPOUND_STRING("מתחזה לפוקימון מהקבוצה."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_IMPOSTER] =
    {
        .name = _("מתחזה"),
        .description = COMPOUND_STRING("הופך להעתק של היריב."),
        .aiRating = 9,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_INFILTRATOR] =
    {
        .name = _("מסתנן"),
        .description = COMPOUND_STRING("עובר דרך מחסומים."),
        .aiRating = 6,
    },

    [ABILITY_MUMMY] =
    {
        .name = _("מומיה"),
        .description = COMPOUND_STRING("מדביק את יכולתו במגע."),
        .aiRating = 5,
    },

    [ABILITY_MOXIE] =
    {
        .name = _("ביטחון עצמי"),
        .description = COMPOUND_STRING("חיסול יריב מעלה התקפה."),
        .aiRating = 7,
    },

    [ABILITY_JUSTIFIED] =
    {
        .name = _("צדק"),
        .description = COMPOUND_STRING("פגיעת אפל מעלה התקפה."),
        .aiRating = 4,
    },

    [ABILITY_RATTLED] =
    {
        .name = _("מבוהל"),
        .description = COMPOUND_STRING("מעלה מהירות כשהוא נבהל."),
        .aiRating = 3,
    },

    [ABILITY_MAGIC_BOUNCE] =
    {
        .name = _("החזר קסם"),
        .description = COMPOUND_STRING("מחזיר מהלכי סטטוס."),
        .aiRating = 9,
        .breakable = TRUE,
    },

    [ABILITY_SAP_SIPPER] =
    {
        .name = _("לוגם מוהל"),
        .description = COMPOUND_STRING("פגיעת עשב מעלה התקפה."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_PRANKSTER] =
    {
        .name = _("קונדס"),
        .description = COMPOUND_STRING("עדיפות למהלכי סטטוס."),
        .aiRating = 8,
    },

    [ABILITY_SAND_FORCE] =
    {
        .name = _("כוח חול"),
        .description = COMPOUND_STRING("מתחזק בסופת חול."),
        .aiRating = 4,
    },

    [ABILITY_IRON_BARBS] =
    {
        .name = _("קוצי ברזל"),
        .description = COMPOUND_STRING("כואב לגעת בו."),
        .aiRating = 6,
    },

    [ABILITY_ZEN_MODE] =
    {
        .name = _("מצב זן"),
        .description = COMPOUND_STRING("משנה צורה בחצי נ”ח."),
        .aiRating = -1,
        .cantBeCopied = TRUE,
        .cantBeSwapped = B_UPDATED_ABILITY_DATA >= GEN_7,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = B_UPDATED_ABILITY_DATA >= GEN_7,
        .cantBeOverwritten = B_UPDATED_ABILITY_DATA >= GEN_7,
        .failsOnImposter = TRUE,
    },

    [ABILITY_VICTORY_STAR] =
    {
        .name = _("כוכב ניצחון"),
        .description = COMPOUND_STRING("מעלה את דיוק הקבוצה."),
        .aiRating = 6,
    },

    [ABILITY_TURBOBLAZE] =
    {
        .name = _("להבת טורבו"),
        .description = COMPOUND_STRING("מהלכיו עוקפים יכולות."),
        .aiRating = 7,
    },

    [ABILITY_TERAVOLT] =
    {
        .name = _("טרה-וולט"),
        .description = COMPOUND_STRING("מהלכיו עוקפים יכולות."),
        .aiRating = 7,
    },

    [ABILITY_AROMA_VEIL] =
    {
        .name = _("צעיף ניחוח"),
        .description = COMPOUND_STRING("מונע הגבלת מהלכים."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_FLOWER_VEIL] =
    {
        .name = _("צעיף פרחים"),
        .description = COMPOUND_STRING("מגן על פוקימונים מסוג עשב."),
        .aiRating = 0,
        .breakable = TRUE,
    },

    [ABILITY_CHEEK_POUCH] =
    {
        .name = _("כיסי לחיים"),
        .description = COMPOUND_STRING("אכילת פירות משקמת נ”ח."),
        .aiRating = 4,
    },

    [ABILITY_PROTEAN] =
    {
        .name = _("רב-גוני"),
        .description = COMPOUND_STRING("משנה סוג לסוג המהלך."),
        .aiRating = 8,
    },

    [ABILITY_FUR_COAT] =
    {
        .name = _("מעיל פרווה"),
        .description = COMPOUND_STRING("מעלה הגנה."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MAGICIAN] =
    {
        .name = _("קוסם"),
        .description = COMPOUND_STRING("גונב פריט מוחזק מהיריב."),
        .aiRating = 3,
    },

    [ABILITY_BULLETPROOF] =
    {
        .name = _("חסין קליעים"),
        .description = COMPOUND_STRING("חסין לחלק מהקליעים."),
        .breakable = TRUE,
        .aiRating = 7,
    },

    [ABILITY_COMPETITIVE] =
    {
        .name = _("תחרותי"),
        .description = COMPOUND_STRING("נתון שירד מעלה התק' מיוחדת."),
        .aiRating = 5,
    },

    [ABILITY_STRONG_JAW] =
    {
        .name = _("לסת חזקה"),
        .description = COMPOUND_STRING("מגביר מהלכי נשיכה."),
        .aiRating = 6,
    },

    [ABILITY_REFRIGERATE] =
    {
        .name = _("קירור"),
        .description = COMPOUND_STRING("מהלכי רגיל הופכים לקרח."),
        .aiRating = 8,
    },

    [ABILITY_SWEET_VEIL] =
    {
        .name = _("צעיף מתוק"),
        .description = COMPOUND_STRING("מגן על הקבוצה משינה."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_STANCE_CHANGE] =
    {
        .name = _("שינוי עמדה"),
        .description = COMPOUND_STRING("משנה צורה תוך כדי קרב."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GALE_WINGS] =
    {
        .name = _("כנפי סופה"),
        .description = COMPOUND_STRING("עדיפות למהלכי תעופה."),
        .aiRating = 6,
    },

    [ABILITY_MEGA_LAUNCHER] =
    {
        .name = _("משגר על"),
        .description = COMPOUND_STRING("מגביר מהלכי דופק."),
        .aiRating = 7,
    },

    [ABILITY_GRASS_PELT] =
    {
        .name = _("פרוות עשב"),
        .description = COMPOUND_STRING("מעלה הגנה בשטח עשבוני."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SYMBIOSIS] =
    {
        .name = _("סימביוזה"),
        .description = COMPOUND_STRING("מעביר את הפריט שלו לידיד."),
        .aiRating = 0,
    },

    [ABILITY_TOUGH_CLAWS] =
    {
        .name = _("טפרים קשוחים"),
        .description = COMPOUND_STRING("מגביר מהלכי מגע."),
        .aiRating = 7,
    },

    [ABILITY_PIXILATE] =
    {
        .name = _("אבק פיות"),
        .description = COMPOUND_STRING("מהלכי רגיל הופכים לפיה."),
        .aiRating = 8,
    },

    [ABILITY_GOOEY] =
    {
        .name = _("רירי"),
        .description = COMPOUND_STRING("מוריד מהירות במגע."),
        .aiRating = 5,
    },

    [ABILITY_AERILATE] =
    {
        .name = _("אוורור"),
        .description = COMPOUND_STRING("מהלכי רגיל הופכים לתעופה."),
        .aiRating = 8,
    },

    [ABILITY_PARENTAL_BOND] =
    {
        .name = _("קשר הורי"),
        .description = COMPOUND_STRING("מהלכיו פוגעים פעמיים."),
        .aiRating = 10,
    },

    [ABILITY_DARK_AURA] =
    {
        .name = _("הילה אפלה"),
        .description = COMPOUND_STRING("מגביר מהלכי אפל."),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_FAIRY_AURA] =
    {
        .name = _("הילת פיה"),
        .description = COMPOUND_STRING("מגביר מהלכי פיה."),
        .aiRating = 6,
        .breakable = B_UPDATED_ABILITY_DATA < GEN_8,
    },

    [ABILITY_AURA_BREAK] =
    {
        .name = _("שבירת הילה"),
        .description = COMPOUND_STRING("הופך את יכולות ההילה."),
        .aiRating = 3,
        .breakable = TRUE,
    },

    [ABILITY_PRIMORDIAL_SEA] =
    {
        .name = _("ים קדמון"),
        .description = COMPOUND_STRING("מזמן גשם כבד."),
        .aiRating = 10,
    },

    [ABILITY_DESOLATE_LAND] =
    {
        .name = _("ארץ שוממה"),
        .description = COMPOUND_STRING("מזמן אור שמש עז."),
        .aiRating = 10,
    },

    [ABILITY_DELTA_STREAM] =
    {
        .name = _("זרם דלתא"),
        .description = COMPOUND_STRING("מזמן רוחות חזקות."),
        .aiRating = 10,
    },

    [ABILITY_STAMINA] =
    {
        .name = _("סיבולת"),
        .description = COMPOUND_STRING("מעלה הגנה כשנפגע."),
        .aiRating = 6,
    },

    [ABILITY_WIMP_OUT] =
    {
        .name = _("השתפנות"),
        .description = COMPOUND_STRING("בורח בחצי נ”ח."),
        .aiRating = 3,
    },

    [ABILITY_EMERGENCY_EXIT] =
    {
        .name = _("יציאת חירום"),
        .description = COMPOUND_STRING("בורח בחצי נ”ח."),
        .aiRating = 3,
    },

    [ABILITY_WATER_COMPACTION] =
    {
        .name = _("דחיסת מים"),
        .description = COMPOUND_STRING("פגיעת מים מעלה הגנה."),
        .aiRating = 4,
    },

    [ABILITY_MERCILESS] =
    {
        .name = _("חסר רחמים"),
        .description = COMPOUND_STRING("פגיעה קריטית ביריב מורעל."),
        .aiRating = 4,
    },

    [ABILITY_SHIELDS_DOWN] =
    {
        .name = _("הורדת מגינים"),
        .description = COMPOUND_STRING("קליפתו נשברת בחצי נ”ח."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STAKEOUT] =
    {
        .name = _("מארב"),
        .description = COMPOUND_STRING("חזק יותר מול יריב שנכנס."),
        .aiRating = 6,
    },

    [ABILITY_WATER_BUBBLE] =
    {
        .name = _("בועת מים"),
        .description = COMPOUND_STRING("מגן מפני אש וכוויות."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_STEELWORKER] =
    {
        .name = _("פועל פלדה"),
        .description = COMPOUND_STRING("מחזק מהלכי פלדה."),
        .aiRating = 6,
    },

    [ABILITY_BERSERK] =
    {
        .name = _("טירוף"),
        .description = COMPOUND_STRING("נ”ח נמוך מעלה התק' מיוחדת."),
        .aiRating = 5,
    },

    [ABILITY_SLUSH_RUSH] =
    {
        .name = _("דהירת שלג"),
        .description = COMPOUND_STRING("מעלה מהירות בברד או שלג."),
        .aiRating = 5,
    },

    [ABILITY_LONG_REACH] =
    {
        .name = _("טווח ארוך"),
        .description = COMPOUND_STRING("אף פעם לא נוגע ביריב."),
        .aiRating = 3,
    },

    [ABILITY_LIQUID_VOICE] =
    {
        .name = _("קול נוזלי"),
        .description = COMPOUND_STRING("הופך מהלכי קול לסוג מים."),
        .aiRating = 5,
    },

    [ABILITY_TRIAGE] =
    {
        .name = _("מיון רפואי"),
        .description = COMPOUND_STRING("עדיפות למהלכי ריפוי."),
        .aiRating = 7,
    },

    [ABILITY_GALVANIZE] =
    {
        .name = _("מחשמל"),
        .description = COMPOUND_STRING("מהלכי רגיל הופכים לחשמל."),
        .aiRating = 8,
    },

    [ABILITY_SURGE_SURFER] =
    {
        .name = _("גולש נחשולים"),
        .description = COMPOUND_STRING("מהיר יותר בשטח חשמלי."),
        .aiRating = 4,
    },

    [ABILITY_SCHOOLING] =
    {
        .name = _("התלהקות"),
        .description = COMPOUND_STRING("יוצר להקה כשהוא חזק."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_DISGUISE] =
    {
        .name = _("תחפושת"),
        .description = COMPOUND_STRING("פיתיון מגן עליו פעם אחת."),
        .aiRating = 8,
        .breakable = TRUE,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_BATTLE_BOND] =
    {
        .name = _("קשר קרב"),
        .description = COMPOUND_STRING("משנה צורה אחרי חיסול יריב."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_CONSTRUCT] =
    {
        .name = _("מבנה כוח"),
        .description = COMPOUND_STRING("תאים עוזרים לו כשנחלש."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_CORROSION] =
    {
        .name = _("איכול"),
        .description = COMPOUND_STRING("מרעיל פוקימונים מכל סוג."),
        .aiRating = 5,
    },

    [ABILITY_COMATOSE] =
    {
        .name = _("תרדמת"),
        .description = COMPOUND_STRING("תמיד מנמנם."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_QUEENLY_MAJESTY] =
    {
        .name = _("הוד מלכותה"),
        .description = COMPOUND_STRING("מגן ממהלכי עדיפות."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_INNARDS_OUT] =
    {
        .name = _("פליטת קרביים"),
        .description = COMPOUND_STRING("תבוסתו פוגעת ביריב."),
        .aiRating = 5,
    },

    [ABILITY_DANCER] =
    {
        .name = _("רקדן"),
        .description = COMPOUND_STRING("רוקד יחד עם אחרים."),
        .aiRating = 5,
    },

    [ABILITY_BATTERY] =
    {
        .name = _("סוללה"),
        .description = COMPOUND_STRING("מעלה התקפה מיוחדת לידיד."),
        .aiRating = 0,
    },

    [ABILITY_FLUFFY] =
    {
        .name = _("פרוותי"),
        .description = COMPOUND_STRING("עמיד יותר אך דליק."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_DAZZLING] =
    {
        .name = _("מסנוור"),
        .description = COMPOUND_STRING("מגן ממהלכי עדיפות."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SOUL_HEART] =
    {
        .name = _("לב-נשמה"),
        .description = COMPOUND_STRING("חיסול מעלה התקפה מיוחדת."),
        .aiRating = 7,
    },

    [ABILITY_TANGLING_HAIR] =
    {
        .name = _("שיער סבוך"),
        .description = COMPOUND_STRING("מוריד מהירות במגע."),
        .aiRating = 5,
    },

    [ABILITY_RECEIVER] =
    {
        .name = _("קולט"),
        .description = COMPOUND_STRING("מעתיק יכולת של ידיד."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POWER_OF_ALCHEMY] =
    {
        .name = _("כוח האלכימיה"),
        .description = COMPOUND_STRING("מעתיק יכולת של ידיד."),
        .aiRating = 0,
        .cantBeCopied = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_BEAST_BOOST] =
    {
        .name = _("דחף חיה"),
        .description = COMPOUND_STRING("חיסול יריב מעלה נתון מוביל."),
        .aiRating = 7,
    },

    [ABILITY_RKS_SYSTEM] =
    {
        .name = _("מערכת RKS"),
        .description = COMPOUND_STRING("זיכרונות משנים את סוגו."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_ELECTRIC_SURGE] =
    {
        .name = _("נחשול חשמל"),
        .description = COMPOUND_STRING("השטח הופך לחשמלי."),
        .aiRating = 8,
    },

    [ABILITY_PSYCHIC_SURGE] =
    {
        .name = _("נחשול פסיכי"),
        .description = COMPOUND_STRING("השטח הופך לפסיכי."),
        .aiRating = 8,
    },

    [ABILITY_MISTY_SURGE] =
    {
        .name = _("נחשול ערפל"),
        .description = COMPOUND_STRING("השטח הופך לערפילי."),
        .aiRating = 8,
    },

    [ABILITY_GRASSY_SURGE] =
    {
        .name = _("נחשול עשב"),
        .description = COMPOUND_STRING("השטח הופך לעשבוני."),
        .aiRating = 8,
    },

    [ABILITY_FULL_METAL_BODY] =
    {
        .name = _("גוף מתכת מלא"),
        .description = COMPOUND_STRING("מונע הורדת נתונים."),
        .aiRating = 4,
    },

    [ABILITY_SHADOW_SHIELD] =
    {
        .name = _("מגן צל"),
        .description = COMPOUND_STRING("סופג חצי נזק במלוא הנ”ח."),
        .aiRating = 8,
    },

    [ABILITY_PRISM_ARMOR] =
    {
        .name = _("שריון מנסרה"),
        .description = COMPOUND_STRING("מחליש מכות יעילות במיוחד."),
        .aiRating = 6,
    },

    [ABILITY_NEUROFORCE] =
    {
        .name = _("כוח עצבי"),
        .description = COMPOUND_STRING("מגביר מכות יעילות במיוחד."),
        .aiRating = 6,
    },

    [ABILITY_INTREPID_SWORD] =
    {
        .name = _("חרב נועזת"),
        .description = COMPOUND_STRING("מעלה התקפה בכניסה."),
        .aiRating = 3,
    },

    [ABILITY_DAUNTLESS_SHIELD] =
    {
        .name = _("מגן ללא חת"),
        .description = COMPOUND_STRING("מעלה הגנה בכניסה."),
        .aiRating = 3,
    },

    [ABILITY_LIBERO] =
    {
        .name = _("ליברו"),
        .description = COMPOUND_STRING("משנה סוג לסוג המהלך."),
    },

    [ABILITY_BALL_FETCH] =
    {
        .name = _("הבאת כדור"),
        .description = COMPOUND_STRING("מחזיר פוקיבול שנכשל."),
        .aiRating = 0,
    },

    [ABILITY_COTTON_DOWN] =
    {
        .name = _("פלומת כותנה"),
        .description = COMPOUND_STRING("מוריד מהירות לכולם כשנפגע."),
        .aiRating = 3,
    },

    [ABILITY_PROPELLER_TAIL] =
    {
        .name = _("זנב מדחף"),
        .description = COMPOUND_STRING("מתעלם מהסטת מטרה."),
        .aiRating = 2,
    },

    [ABILITY_MIRROR_ARMOR] =
    {
        .name = _("שריון מראה"),
        .description = COMPOUND_STRING("מחזיר ליריב הורדת נתונים."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_GULP_MISSILE] =
    {
        .name = _("טיל בליעה"),
        .description = COMPOUND_STRING("כשנפגע, יורק טרף מהים."),
        .aiRating = 3,
        .cantBeSwapped = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeCopied = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeTraced = B_UPDATED_ABILITY_DATA < GEN_9,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_STALWART] =
    {
        .name = _("עיקש"),
        .description = COMPOUND_STRING("מתעלם מהסטת מטרה."),
        .aiRating = 2,
    },

    [ABILITY_STEAM_ENGINE] =
    {
        .name = _("מנוע קיטור"),
        .description = COMPOUND_STRING("אש או מים מעלים מהירות."),
        .aiRating = 3,
    },

    [ABILITY_PUNK_ROCK] =
    {
        .name = _("פאנק רוק"),
        .description = COMPOUND_STRING("מגביר מהלכי קול ועמיד להם."),
        .aiRating = 2,
        .breakable = TRUE,
    },

    [ABILITY_SAND_SPIT] =
    {
        .name = _("יריקת חול"),
        .description = COMPOUND_STRING("יוצר סופת חול כשנפגע."),
        .aiRating = 5,
    },

    [ABILITY_ICE_SCALES] =
    {
        .name = _("קשקשת קרח"),
        .description = COMPOUND_STRING("סופג חצי נזק מיוחד."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_RIPEN] =
    {
        .name = _("הבשלה"),
        .description = COMPOUND_STRING("מכפיל את השפעת הפירות."),
        .aiRating = 4,
    },

    [ABILITY_ICE_FACE] =
    {
        .name = _("פני קרח"),
        .description = COMPOUND_STRING("ברד או שלג מחדשים את המגן."),
        .aiRating = 4,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .breakable = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_POWER_SPOT] =
    {
        .name = _("נקודת כוח"),
        .description = COMPOUND_STRING("מחזק מהלכי ידידים."),
        .aiRating = 2,
    },

    [ABILITY_MIMICRY] =
    {
        .name = _("חיקוי"),
        .description = COMPOUND_STRING("משנה סוג לפי השטח."),
        .aiRating = 2,
    },

    [ABILITY_SCREEN_CLEANER] =
    {
        .name = _("מנקה מסכים"),
        .description = COMPOUND_STRING("מסיר מחסומי אור."),
        .aiRating = 3,
    },

    [ABILITY_STEELY_SPIRIT] =
    {
        .name = _("רוח פלדה"),
        .description = COMPOUND_STRING("מגביר מהלכי פלדה לידידים."),
        .aiRating = 2,
    },

    [ABILITY_PERISH_BODY] =
    {
        .name = _("גוף מוות"),
        .description = COMPOUND_STRING("התוקף יתעלף בעוד 3 תורים."),
        .aiRating = -1,
    },

    [ABILITY_WANDERING_SPIRIT] =
    {
        .name = _("רוח נודדת"),
        .description = COMPOUND_STRING("מחליף יכולות במגע."),
        .aiRating = 2,
    },

    [ABILITY_GORILLA_TACTICS] =
    {
        .name = _("טקטיקת גורילה"),
        .description = COMPOUND_STRING("מעלה התקפה ונועל מהלך."),
        .aiRating = 4,
    },

    [ABILITY_NEUTRALIZING_GAS] =
    {
        .name = _("גז מנטרל"),
        .description = COMPOUND_STRING("כל היכולות מנוטרלות."),
        .aiRating = 5,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_PASTEL_VEIL] =
    {
        .name = _("צעיף פסטל"),
        .description = COMPOUND_STRING("מגן על הקבוצה מהרעלה."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_HUNGER_SWITCH] =
    {
        .name = _("מתג רעב"),
        .description = COMPOUND_STRING("משנה צורה בכל תור."),
        .aiRating = 2,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUICK_DRAW] =
    {
        .name = _("שליפה מהירה"),
        .description = COMPOUND_STRING("לפעמים פועל ראשון."),
        .aiRating = 4,
    },

    [ABILITY_UNSEEN_FIST] =
    {
        .name = _("אגרוף נסתר"),
        .description = COMPOUND_STRING("מהלכי מגע עוקפים הגנות."),
        .aiRating = 6,
    },

    [ABILITY_CURIOUS_MEDICINE] =
    {
        .name = _("תרופה מוזרה"),
        .description = COMPOUND_STRING("מבטל שינויי נתונים לידיד."),
        .aiRating = 3,
    },

    [ABILITY_TRANSISTOR] =
    {
        .name = _("טרנזיסטור"),
        .description = COMPOUND_STRING("מגביר מהלכי חשמל."),
        .aiRating = 6,
    },

    [ABILITY_DRAGONS_MAW] =
    {
        .name = _("לוע הדרקון"),
        .description = COMPOUND_STRING("מגביר מהלכי דרקון."),
        .aiRating = 6,
    },

    [ABILITY_CHILLING_NEIGH] =
    {
        .name = _("צהלה מקפיאה"),
        .description = COMPOUND_STRING("חיסול יריב מעלה התקפה."),
        .aiRating = 7,
    },

    [ABILITY_GRIM_NEIGH] =
    {
        .name = _("צהלה קודרת"),
        .description = COMPOUND_STRING("חיסול מעלה התקפה מיוחדת."),
        .aiRating = 7,
    },

    [ABILITY_AS_ONE_ICE_RIDER] =
    {
        .name = _("כאחד"),
        .description = COMPOUND_STRING("מורט עצבים וצהלה מקפיאה."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_AS_ONE_SHADOW_RIDER] =
    {
        .name = _("כאחד"),
        .description = COMPOUND_STRING("מורט עצבים וצהלה קודרת."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_LINGERING_AROMA] =
    {
        .name = _("ניחוח מתמשך"),
        .description = COMPOUND_STRING("מדביק את יכולתו במגע."),
        .aiRating = 5,
    },

    [ABILITY_SEED_SOWER] =
    {
        .name = _("זורע זרעים"),
        .description = COMPOUND_STRING("משנה את השטח כשנפגע."),
        .aiRating = 5,
    },

    [ABILITY_THERMAL_EXCHANGE] =
    {
        .name = _("חילוף חום"),
        .description = COMPOUND_STRING("פגיעת אש מעלה התקפה."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_ANGER_SHELL] =
    {
        .name = _("קונכיית זעם"),
        .description = COMPOUND_STRING("מתרגז בחצי נ”ח."),
        .aiRating = 3,
    },

    [ABILITY_PURIFYING_SALT] =
    {
        .name = _("מלח מטהר"),
        .description = COMPOUND_STRING("מוגן במלח טהור."),
        .aiRating = 6,
        .breakable = TRUE,
    },

    [ABILITY_WELL_BAKED_BODY] =
    {
        .name = _("גוף אפוי היטב"),
        .description = COMPOUND_STRING("מתחזק מאש."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_WIND_RIDER] =
    {
        .name = _("רוכב רוח"),
        .description = COMPOUND_STRING("מעלה התקפה כשנפגע מרוח."),
        .aiRating = 4,
        .breakable = TRUE,
    },

    [ABILITY_GUARD_DOG] =
    {
        .name = _("כלב שמירה"),
        .description = COMPOUND_STRING("חסין להפחדה."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ROCKY_PAYLOAD] =
    {
        .name = _("מטען סלעים"),
        .description = COMPOUND_STRING("מחזק מהלכי סלע."),
        .aiRating = 6,
    },

    [ABILITY_WIND_POWER] =
    {
        .name = _("כוח רוח"),
        .description = COMPOUND_STRING("נטען מרוח."),
        .aiRating = 4,
    },

    [ABILITY_ZERO_TO_HERO] =
    {
        .name = _("מאפס לגיבור"),
        .description = COMPOUND_STRING("משנה צורה כשהוא מתחלף."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_COMMANDER] =
    {
        .name = _("מפקד"),
        .description = COMPOUND_STRING("מפקד מתוך דונדוזו."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_ELECTROMORPHOSIS] =
    {
        .name = _("אלקטרומורפוזה"),
        .description = COMPOUND_STRING("נטען כשנפגע."),
        .aiRating = 5,
    },

    [ABILITY_PROTOSYNTHESIS] =
    {
        .name = _("פרוטוסינתזה"),
        .description = COMPOUND_STRING("השמש מעלה נתון מוביל."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_QUARK_DRIVE] =
    {
        .name = _("הנעת קווארק"),
        .description = COMPOUND_STRING("שטח חשמלי מעלה נתון מוביל."),
        .aiRating = 7,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_GOOD_AS_GOLD] =
    {
        .name = _("שווה זהב"),
        .description = COMPOUND_STRING("חסין למהלכי סטטוס."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_VESSEL_OF_RUIN] =
    {
        .name = _("כלי החורבן"),
        .description = COMPOUND_STRING("מחליש נזק מיוחד של יריבים."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_SWORD_OF_RUIN] =
    {
        .name = _("חרב החורבן"),
        .description = COMPOUND_STRING("מוריד ליריבים הגנה."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_TABLETS_OF_RUIN] =
    {
        .name = _("לוחות החורבן"),
        .description = COMPOUND_STRING("מחליש נזק של יריבים."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_BEADS_OF_RUIN] =
    {
        .name = _("חרוזי החורבן"),
        .description = COMPOUND_STRING("מוריד ליריבים הגנה מיוחדת."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_ORICHALCUM_PULSE] =
    {
        .name = _("דופק אוריכלקום"),
        .description = COMPOUND_STRING("מזמן אור שמש בקרב."),
        .aiRating = 8,
        .cantBeSwapped = TRUE,
        .cantBeCopied = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_HADRON_ENGINE] =
    {
        .name = _("מנוע הדרונים"),
        .description = COMPOUND_STRING("השטח הופך לחשמלי."),
        .aiRating = 8,
        .cantBeSwapped = TRUE,
        .cantBeCopied = TRUE,
        .cantBeOverwritten = TRUE,
    },

    [ABILITY_OPPORTUNIST] =
    {
        .name = _("אופורטוניסט"),
        .description = COMPOUND_STRING("מעתיק שינויי נתונים של יריב."),
        .aiRating = 5,
    },

    [ABILITY_CUD_CHEW] =
    {
        .name = _("העלאת גירה"),
        .description = COMPOUND_STRING("אוכל שוב פרי שנאכל."),
        .aiRating = 4,
    },

    [ABILITY_SHARPNESS] =
    {
        .name = _("חדות"),
        .description = COMPOUND_STRING("מחזק מהלכי חיתוך."),
        .aiRating = 7,
    },

    [ABILITY_SUPREME_OVERLORD] =
    {
        .name = _("שליט עליון"),
        .description = COMPOUND_STRING("יורש את כוח הנופלים."),
        .aiRating = 6,
    },

    [ABILITY_COSTAR] =
    {
        .name = _("כוכב שותף"),
        .description = COMPOUND_STRING("מעתיק שינויי נתונים של ידיד."),
        .aiRating = 5,
    },

    [ABILITY_TOXIC_DEBRIS] =
    {
        .name = _("פסולת רעילה"),
        .description = COMPOUND_STRING("מפזר קוצים רעילים כשנפגע."),
        .aiRating = 4,
    },

    [ABILITY_ARMOR_TAIL] =
    {
        .name = _("זנב שריון"),
        .description = COMPOUND_STRING("מגן ממהלכי עדיפות."),
        .aiRating = 5,
        .breakable = TRUE,
    },

    [ABILITY_EARTH_EATER] =
    {
        .name = _("אוכל אדמה"),
        .description = COMPOUND_STRING("אוכל אדמה כדי לשקם נ”ח."),
        .aiRating = 7,
        .breakable = TRUE,
    },

    [ABILITY_MYCELIUM_MIGHT] =
    {
        .name = _("עוצמת תפטיר"),
        .description = COMPOUND_STRING("מהלכי סטטוס תמיד מצליחים."),
        .aiRating = 2,
    },

    [ABILITY_HOSPITALITY] =
    {
        .name = _("הכנסת אורחים"),
        .description = COMPOUND_STRING("משקם נ”ח לידיד."),
        .aiRating = 5,
    },

    [ABILITY_MINDS_EYE] =
    {
        .name = _("עין הרוח"),
        .description = COMPOUND_STRING("משלב ”עין חדה” ו”לוחמני”."),
        .aiRating = 8,
        .breakable = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_TEAL_MASK] =
    {
        .name = _("גילום דמות"),
        .description = COMPOUND_STRING("מעלה מהירות."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK] =
    {
        .name = _("גילום דמות"),
        .description = COMPOUND_STRING("מעלה התקפה."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_WELLSPRING_MASK] =
    {
        .name = _("גילום דמות"),
        .description = COMPOUND_STRING("מעלה הגנה מיוחדת."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK] =
    {
        .name = _("גילום דמות"),
        .description = COMPOUND_STRING("מעלה הגנה."),
        .aiRating = 6,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TOXIC_CHAIN] =
    {
        .name = _("שרשרת רעילה"),
        .description = COMPOUND_STRING("מהלכיו עשויים להרעיל."),
        .aiRating = 8,
    },

    [ABILITY_SUPERSWEET_SYRUP] =
    {
        .name = _("סירופ על-מתוק"),
        .description = COMPOUND_STRING("מוריד את התחמקות היריב."),
        .aiRating = 5,
    },

    [ABILITY_TERA_SHIFT] =
    {
        .name = _("מעבר טרה"),
        .description = COMPOUND_STRING("עובר לצורת טרה בכניסה."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .cantBeSuppressed = TRUE,
        .cantBeOverwritten = TRUE,
        .failsOnImposter = TRUE,
    },

    [ABILITY_TERA_SHELL] =
    {
        .name = _("קונכיית טרה"),
        .description = COMPOUND_STRING("עמיד לכל סוג במלוא הנ”ח."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
        .breakable = TRUE,
    },

    [ABILITY_TERAFORM_ZERO] =
    {
        .name = _("איפוס טרה"),
        .description = COMPOUND_STRING("מאפס את מזג האוויר והשטח."),
        .aiRating = 10,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },

    [ABILITY_POISON_PUPPETEER] =
    {
        .name = _("בובנאי רעל"),
        .description = COMPOUND_STRING("מבלבל יריבים מורעלים."),
        .aiRating = 8,
        .cantBeCopied = TRUE,
        .cantBeSwapped = TRUE,
        .cantBeTraced = TRUE,
    },
};
