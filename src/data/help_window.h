// Add entries here
// These entries are example entries which you can replace, but they exist to get you started.
// Remember to modify include/constants/help_window.h to include identifiers so they can be used in event scripts.
const struct HelpWindow gHelpWindowInfo[] =
{
    [HELP_DEMO_WINDOW] =
    {
        .header = COMPOUND_STRING("מידע: חלונות עזרה"),
        .desc = COMPOUND_STRING("זהו חלון עזרה. אפשר לשים בו\n"
                                "המון טקסט על המסך,\n"
                                "והשחקנים לא יקראו אותו!\n"
                                "\n"
                                "נהדר, לא?"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 4, 5},
    },
    [HELP_GAMESTART_WINDOW] =
    {
        .header = COMPOUND_STRING("מידע: עוד אפשרויות"),
        .desc = COMPOUND_STRING("אפשר לשנות את השעון בכל\n"
                                "מרכז פוקימון, בלי שום השלכות.\n"
                                "כדאי לבדוק את פריטי המפתח בתיק\n"
                                "ואת תפריט האפשרויות, שבהם יש\n"
                                "עוד דרכים להתאים את המשחק לטעמך.\n"
                                "בהנאה!"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_TRADE_WINDOW] =
    {
        .header = COMPOUND_STRING("אזהרה: תאימות"),
        .desc = COMPOUND_STRING("ניסיון התחברות לא תקין עלול לגרום\n"
                                "נזק קבוע לקובץ השמירה שלך.\n"
                                "יש להתחבר לשחקן אחר רק אם:\n"
                                "שניכם משחקים ב-Heart & Soul.\n"
                                "שניכם משחקים באותה גרסה.\n"
                                "לשניכם אותן הגדרות אתגר.\n"
                                "אף אחד מכם לא משתמש במצב האקראי."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 4, 5},
    },
    [HELP_TELEPORTER_WINDOW] =
    {
        .header = COMPOUND_STRING("תוכן בונוס אופציונלי: הטלפורטר"),
        .desc = COMPOUND_STRING("הטלפורטר יכול להפוך פוקימונים\n"
                                "לצורת גלאר שלהם, לצמיתות.\n"
                                "צורות גלאר אינן נחוצות\n"
                                "להתקדמות בעלילה או\n"
                                "להשלמת הפוקדקס הלאומי.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_SINJOH_WINDOW] =
    {
        .header = COMPOUND_STRING("תוכן בונוס אופציונלי: סינג'ו"),
        .desc = COMPOUND_STRING("הדמות הזו פותחת גישה לתוכן\n"
                                "בונוס אופציונלי: סינג'ו.\n"
                                "הוא לא נחוץ לסיום העלילה\n"
                                "או להשלמת הפוקדקס הלאומי.\n"
                                "\n"
                                "זה רק בונוס. אם בא לך."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_ALOLA_WINDOW] =
    {
        .header = COMPOUND_STRING("תוכן בונוס אופציונלי: האיים"),
        .desc = COMPOUND_STRING("הדמות הזו פותחת גישה לתוכן\n"
                                "בונוס אופציונלי: האיים.\n"
                                "הוא לא נחוץ לסיום העלילה\n"
                                "או להשלמת הפוקדקס הלאומי.\n"
                                "\n"
                                "זה רק בונוס. אם בא לך."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE1_WINDOW] =
    {
        .header = COMPOUND_STRING("יכולות הפוקימונים התינוקות"),
        .desc = COMPOUND_STRING("היכולת של פיצ'ו היא ”חשמל סטטי”.\n"
                                "היכולת של קלפה היא ”קסם חמוד”.\n"
                                "היכולת של איגליבאף היא ”קסם חמוד”.\n"
                                "היכולת של טיירוג היא ”אומץ”.\n"
                                "היכולת של סמוצ'ום היא ”אדישות”.\n"
                                "היכולת של אלקיד היא ”חשמל סטטי”.\n"
                                "היכולת של מגבי היא ”גוף להבה”."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE2_WINDOW] =
    {
        .header = COMPOUND_STRING("סוגי הפוקימונים התינוקות"),
        .desc = COMPOUND_STRING("פיצ'ו הוא מסוג ”חשמל”.\n"
                                "קלפה הוא מסוג ”רגיל”.\n"
                                "איגליבאף הוא מסוג ”רגיל”.\n"
                                "טיירוג הוא מסוג ”קרב”.\n"
                                "סמוצ'ום הוא מסוג ”קרח”.\n"
                                "אלקיד הוא מסוג ”חשמל”.\n"
                                "מגבי הוא מסוג ”אש”."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE3_WINDOW] =
    {
        .header = COMPOUND_STRING("קריאות הפוקימונים התינוקות"),
        .desc = COMPOUND_STRING("פיצ'ו אומר ”וואאה”.\n"
                                "קלפה אומר ”איק”.\n"
                                "איגליבאף אומר ”לה-לה-לה”.\n"
                                "טיירוג אומר ”היי-יה”.\n"
                                "סמוצ'ום אומר ”היהי”.\n"
                                "אלקיד אומר ”הי, הי, הי”.\n"
                                "מגבי אומר ”טסק”."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE4_WINDOW] =
    {
        .header = COMPOUND_STRING("פעולות הפוקימונים התינוקות"),
        .desc = COMPOUND_STRING("פיצ'ו אוהב ”לשחק” כל היום.\n"
                                "קלפה ”מביט” בירח.\n"
                                "איגליבאף גורם לכולם ”לישון”.\n"
                                "טיירוג ”מתאמן” כל הזמן.\n"
                                "סמוצ'ום אוהב ”להראות” מה הוא שווה.\n"
                                "אלקיד ”מאחסן” מטען חשמלי.\n"
                                "מגבי ”מכעיס” לעתים קרובות."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_POKEBLOCK_WINDOW] =
    {
        .header = COMPOUND_STRING("מתקני האכלה: פוקיבלוקים רגילים"),
        .desc = COMPOUND_STRING("צבעי הפוקיבלוקים מושכים ערכי IV מושלמים:\n"
                                "אדום נ”ח,הת',מהי'        כחול נ”ח,הת”מ,מהי'\n"
                                "ורוד הת',הת”מ,מהי'      ירוק נ”ח,הגנ',הג”מ\n"
                                "צהוב נ”ח,הת',הגנ'        סגול הת',הגנ',הג”מ\n"
                                "אינדיגו נ”ח,הת”מ,הג”מ  חום הגנ',מהי',הג”מ\n"
                                "תכלת הת”מ,מהי',הג”מ   זית הת',הגנ',מהי'\n"
                                "אפור נ”ח,הת',הת”מ\n"
                                "כל פוקיבלוק מושך פוקימון עם יכולת נסתרת."

                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_GOLD_POKEBLOCK_WINDOW] =
    {
        .header = COMPOUND_STRING("מתקני האכלה: פוקיבלוקי זהב"),
        .desc = COMPOUND_STRING("פוקיבלוקי זהב מושכים פוקימונים עם\n"
                                "5 ערכי IV מושלמים. הטעם קובע איזה\n"
                                "ערך IV לא יהיה מושלם.\n"
                                "חריף: בלי התקפה מיוחדת   יבש: בלי התקפה\n"
                                "מתוק: בלי הגנה מיוחדת      מר: בלי מהירות\n"
                                "חמוץ: בלי נ”ח\n"
                                "כל פוקיבלוק מושך פוקימון עם יכולת נסתרת."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    // Add more entries
};
