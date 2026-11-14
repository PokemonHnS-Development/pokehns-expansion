extern const u8 EventScript_FollowerIsShivering[];
extern const u8 EventScript_FollowerNostalgia[];
extern const u8 EventScript_FollowerHopping[];
extern const u8 EventScript_FollowerJumpOnPlayer[];
extern const u8 EventScript_FollowerCuddling[];
extern const u8 EventScript_FollowerShiverCuddling[];
extern const u8 EventScript_FollowerGetCloser[];
extern const u8 EventScript_FollowerPokingPlayer[];
extern const u8 EventScript_FollowerLookAround[];
extern const u8 EventScript_FollowerLookAway[];
extern const u8 EventScript_FollowerLookAwayBark[];
extern const u8 EventScript_FollowerLookAwayPoke[];
extern const u8 EventScript_FollowerPokeGround[];
extern const u8 EventScript_FollowerStartled[];
extern const u8 EventScript_FollowerFastHopping[];
extern const u8 EventScript_FollowerDizzy[];
extern const u8 EventScript_FollowerLookAroundScared[];
extern const u8 EventScript_FollowerDance[];
extern const u8 EventScript_FollowerLookUp[];

// 'Generic', unconditional happy messages
static const u8 sHappyMsg00[] = _("{STR_VAR_1} התחיל לתת לך\nדחיפות קלות בבטן.");
static const u8 sHappyMsg01[] = _("{STR_VAR_1} שמח, אבל ביישן.");
static const u8 sHappyMsg02[] = _("{STR_VAR_1} הולך איתך בשמחה.");
static const u8 sHappyMsg03[] = _("{STR_VAR_1} רגוע ושליו.");
static const u8 sHappyMsg04[] = _("{STR_VAR_1} כנראה ממש נהנה\nללכת איתך!");
static const u8 sHappyMsg05[] = _("{STR_VAR_1} קורן מבריאות.");
static const u8 sHappyMsg06[] = _("{STR_VAR_1} נראה שמח מאוד.");
static const u8 sHappyMsg07[] = _("{STR_VAR_1} התאמץ במיוחד.");
static const u8 sHappyMsg08[] = _("{STR_VAR_1} מרחרח את הריחות\nשבאוויר מסביב.");
static const u8 sHappyMsg09[] = _("{STR_VAR_1} קופץ משמחה!");
static const u8 sHappyMsg10[] = _("{STR_VAR_1} עדיין מרגיש מצוין!");
static const u8 sHappyMsg11[] = _("הפוקימון שלך קלט ריח של עשן.");
static const u8 sHappyMsg12[] = _("{STR_VAR_1} נותן לך\nדחיפות קלות בבטן.");
static const u8 sHappyMsg13[] = _("הפוקימון שלך התמתח ומתרגע לו.");
static const u8 sHappyMsg14[] = _("{STR_VAR_1} נראה כאילו\nהוא רוצה להוביל!");
static const u8 sHappyMsg15[] = _("{STR_VAR_1} עושה כמיטב יכולתו\nכדי לעמוד בקצב שלך.");
static const u8 sHappyMsg16[] = _("{STR_VAR_1} מתרפק עליך בשמחה!");
static const u8 sHappyMsg17[] = _("{STR_VAR_1} מלא חיים!");
static const u8 sHappyMsg18[] = _("{STR_VAR_1} נראה מאושר מאוד!");
static const u8 sHappyMsg19[] = _("{STR_VAR_1} כל כך שמח שהוא\nלא מסוגל לעמוד במקום!");
static const u8 sHappyMsg20[] = _("{STR_VAR_1} הנהן לאט.");
static const u8 sHappyMsg21[] = _("{STR_VAR_1} נלהב מאוד!");
static const u8 sHappyMsg22[] = _("{STR_VAR_1} משוטט מסביב\nומקשיב לקולות השונים.");
static const u8 sHappyMsg23[] = _("{STR_VAR_1} נראה מסוקרן מאוד.");
static const u8 sHappyMsg24[] = _("{STR_VAR_1} איכשהו מכריח\nאת עצמו להמשיך.");
static const u8 sHappyMsg25[] = _("{STR_VAR_1} שלח אליך מבט קורן!");
static const u8 sHappyMsg26[] = _("{STR_VAR_1} מביט בך בשמחה\nומחייך.");
static const u8 sHappyMsg27[] = _("הפוקימון שלך מריח את ניחוח הפרחים.");
static const u8 sHappyMsg28[] = _("{STR_VAR_1} נראה שמח מאוד\nלראות אותך!");
static const u8 sHappyMsg29[] = _("{STR_VAR_1} הסתובב לכיוונך\nוחייך חיוך רחב.");
static const u8 sHappyMsg30[] = _("{STR_VAR_1} התרפק עליך בשמחה!");
// Conditional messages begin here, index 31
static const u8 sHappyMsg31[] = _("הפוקימון שלך נראה מרוצה\nממזג האוויר הנהדר.");
static const u8 sHappyMsg32[] = _("{STR_VAR_1} רגוע מאוד\nובטוח בעצמו!");

const struct FollowerMsgInfo gFollowerHappyMessages[] = {
    {sHappyMsg00, EventScript_FollowerPokingPlayer},
    {sHappyMsg01}, {sHappyMsg02}, {sHappyMsg03}, {sHappyMsg04}, {sHappyMsg05}, {sHappyMsg06}, {sHappyMsg07},
    {sHappyMsg08, EventScript_FollowerLookAround},
    {sHappyMsg09, EventScript_FollowerHopping},
    {sHappyMsg10}, {sHappyMsg11},
    {sHappyMsg12, EventScript_FollowerPokingPlayer},
    {sHappyMsg13, EventScript_FollowerLookAround},
    {sHappyMsg14}, {sHappyMsg15},
    {sHappyMsg16, EventScript_FollowerCuddling},
    {sHappyMsg17}, {sHappyMsg18},
    {sHappyMsg19, EventScript_FollowerFastHopping},
    {sHappyMsg20}, {sHappyMsg21}, {sHappyMsg22}, {sHappyMsg23}, {sHappyMsg24}, {sHappyMsg25}, {sHappyMsg26}, {sHappyMsg27}, {sHappyMsg28}, {sHappyMsg29},
    {sHappyMsg30, EventScript_FollowerCuddling},
    {sHappyMsg31}, {sHappyMsg32},
};

// Unconditional neutral messages
static const u8 sNeutralMsg00[] = _("{STR_VAR_1} מחטט באדמה\nבהתמדה.");
static const u8 sNeutralMsg01[] = _("{STR_VAR_1} עומד על המשמר.");
static const u8 sNeutralMsg02[] = _("{STR_VAR_1} בוהה בסבלנות בכלום.");
static const u8 sNeutralMsg03[] = _("{STR_VAR_1} משוטט מסביב.");
static const u8 sNeutralMsg04[] = _("הפוקימון שלך פיהק בקול רם!");
static const u8 sNeutralMsg05[] = _("הפוקימון שלך מסתכל סביבו\nבחוסר מנוחה.");
static const u8 sNeutralMsg06[] = _("{STR_VAR_1} מסתכל לכיוונך ומחייך.");
static const u8 sNeutralMsg07[] = _("{STR_VAR_1} מביט סביבו\nבחוסר מנוחה.");
static const u8 sNeutralMsg08[] = _("{STR_VAR_1} השמיע קריאת קרב.");
static const u8 sNeutralMsg09[] = _("{STR_VAR_1} רקד ריקוד נפלא!");
static const u8 sNeutralMsg10[] = _("{STR_VAR_1} נלהב מאוד.");
static const u8 sNeutralMsg11[] = _("{STR_VAR_1} מביט בריכוז למרחקים.");
static const u8 sNeutralMsg12[] = _("{STR_VAR_1} צופה סביבו בדריכות!");
static const u8 sNeutralMsg13[] = _("{STR_VAR_1} הביט למרחקים ונבח!");

const struct FollowerMsgInfo gFollowerNeutralMessages[] = {
    {sNeutralMsg00, EventScript_FollowerPokeGround},
    {sNeutralMsg01},
    {sNeutralMsg02, EventScript_FollowerLookAway},
    {sNeutralMsg03, EventScript_FollowerLookAround},
    {sNeutralMsg04},
    {sNeutralMsg05, EventScript_FollowerLookAround},
    {sNeutralMsg06}, {sNeutralMsg07}, {sNeutralMsg08},
    {sNeutralMsg09, EventScript_FollowerDance},
    {sNeutralMsg10},
    {sNeutralMsg11, EventScript_FollowerLookAway},
    {sNeutralMsg12},
    {sNeutralMsg13, EventScript_FollowerLookAwayBark},
};

// Unconditional sad messages
static const u8 sSadMsg00[] = _("{STR_VAR_1} מסוחרר.");
static const u8 sSadMsg01[] = _("{STR_VAR_1} דורך לך על הרגליים!");
static const u8 sSadMsg02[] = _("{STR_VAR_1} נראה קצת עייף.");
// Conditional messages begin, index 3
static const u8 sSadMsg03[] = _("{STR_VAR_1} לא שמח.");
static const u8 sSadMsg04[] = _("{STR_VAR_1} עומד ליפול!\n");
static const u8 sSadMsg05[] = _("{STR_VAR_1} נראה כאילו הוא\nעומד ליפול!");
static const u8 sSadMsg06[] = _("{STR_VAR_1} מתאמץ מאוד\nלעמוד בקצב שלך…");
static const u8 sSadMsg07[] = _("{STR_VAR_1} לחוץ.");

const struct FollowerMsgInfo gFollowerSadMessages[] = {
    {sSadMsg00, EventScript_FollowerDizzy},
    {sSadMsg01}, {sSadMsg02},
    {sSadMsg03}, {sSadMsg04}, {sSadMsg05}, {sSadMsg06}, {sSadMsg07},
};

// Unconditional upset messages
static const u8 sUpsetMsg00[] = _("{STR_VAR_1} נראה לא מרוצה\nמשום מה…");
static const u8 sUpsetMsg01[] = _("{STR_VAR_1} עושה פרצוף לא מרוצה.");
static const u8 sUpsetMsg02[] = _("…נראה שלפוקימון שלך קצת קר.");
// Conditional messages, index 3
static const u8 sUpsetMsg03[] = _("{STR_VAR_1} מוצא מחסה בעשב\nמפני הגשם.");

const struct FollowerMsgInfo gFollowerUpsetMessages[] = {
    {sUpsetMsg00}, {sUpsetMsg01},
    {sUpsetMsg02, EventScript_FollowerIsShivering},
    {sUpsetMsg03},
};

// Unconditional angry messages
static const u8 sAngryMsg00[] = _("{STR_VAR_1} השמיע שאגה!");
static const u8 sAngryMsg01[] = _("{STR_VAR_1} עושה פרצוף כועס!");
static const u8 sAngryMsg02[] = _("{STR_VAR_1} נראה כועס משום מה.");
static const u8 sAngryMsg03[] = _("הפוקימון שלך הסב את פניו\nהצידה, בהבעה מתריסה.");
static const u8 sAngryMsg04[] = _("{STR_VAR_1} צעק.");

const struct FollowerMsgInfo gFollowerAngryMessages[] = {
    {sAngryMsg00}, {sAngryMsg01}, {sAngryMsg02},
    {sAngryMsg03, EventScript_FollowerLookAway},
    {sAngryMsg04},
};

// Unconditional pensive messages
static const u8 sPensiveMsg00[] = _("{STR_VAR_1} מביט למטה בריכוז.");
static const u8 sPensiveMsg01[] = _("{STR_VAR_1} סוקר את הסביבה.");
static const u8 sPensiveMsg02[] = _("{STR_VAR_1} מציץ למטה.");
static const u8 sPensiveMsg03[] = _("{STR_VAR_1} נאבק איכשהו בשינה…");
static const u8 sPensiveMsg04[] = _("{STR_VAR_1} כנראה משוטט\nסתם מסביב.");
static const u8 sPensiveMsg05[] = _("{STR_VAR_1} מסתכל סביבו\nבפיזור דעת.");
static const u8 sPensiveMsg06[] = _("{STR_VAR_1} פיהק בקול רם מאוד!");
static const u8 sPensiveMsg07[] = _("{STR_VAR_1} נח לו בנחת.");
static const u8 sPensiveMsg08[] = _("{STR_VAR_1} נועץ מבט בפנים שלך\nבלי להסיט את עיניו.");
static const u8 sPensiveMsg09[] = _("{STR_VAR_1} בוחן בריכוז\nאת הפנים שלך.");
static const u8 sPensiveMsg10[] = _("{STR_VAR_1} ממקד בך\nאת תשומת ליבו.");
static const u8 sPensiveMsg11[] = _("{STR_VAR_1} בוהה אל המעמקים.");
static const u8 sPensiveMsg12[] = _("{STR_VAR_1} מרחרח את האדמה.");
static const u8 sPensiveMsg13[] = _("הפוקימון שלך בוהה בריכוז בכלום.");
static const u8 sPensiveMsg14[] = _("{STR_VAR_1} מיקד מבט חד!");
static const u8 sPensiveMsg15[] = _("{STR_VAR_1} מתרכז.");
static const u8 sPensiveMsg16[] = _("{STR_VAR_1} הסתובב לכיוונך והנהן.");
static const u8 sPensiveMsg17[] = _("{STR_VAR_1} נראה קצת לחוץ…");
static const u8 sPensiveMsg18[] = _("{STR_VAR_1} מסתכל\nעל טביעות הרגליים שלך.");
static const u8 sPensiveMsg19[] = _("{STR_VAR_1} מביט לך ישר בעיניים.");

const struct FollowerMsgInfo gFollowerPensiveMessages[] = {
    {sPensiveMsg00},
    {sPensiveMsg01, EventScript_FollowerLookAround},
    {sPensiveMsg02}, {sPensiveMsg03}, {sPensiveMsg04},
    {sPensiveMsg05, EventScript_FollowerLookAround},
    {sPensiveMsg06}, {sPensiveMsg07}, {sPensiveMsg08}, {sPensiveMsg09}, {sPensiveMsg10},
    {sPensiveMsg11, EventScript_FollowerLookAway},
    {sPensiveMsg12, EventScript_FollowerPokeGround},
    {sPensiveMsg13, EventScript_FollowerLookAway},
    {sPensiveMsg14}, {sPensiveMsg15}, {sPensiveMsg16}, {sPensiveMsg17}, {sPensiveMsg18}, {sPensiveMsg19},
};

// All 'love' messages are unconditional
static const u8 sLoveMsg00[] = _("{STR_VAR_1} התחיל פתאום ללכת\nקרוב יותר אליך!");
static const u8 sLoveMsg01[] = _("הלחיים של {STR_VAR_1} מסמיקות!");
static const u8 sLoveMsg02[] = _("וואו! {STR_VAR_1} חיבק\nאותך פתאום!");
static const u8 sLoveMsg03[] = _("וואו! {STR_VAR_1} פתאום\nמלא שובבות!");
static const u8 sLoveMsg04[] = _("{STR_VAR_1} מתחכך ברגליים שלך!");
static const u8 sLoveMsg05[] = _("{STR_VAR_1} מסמיק.");
static const u8 sLoveMsg06[] = _("אה! {STR_VAR_1} מתרפק עליך!");
static const u8 sLoveMsg07[] = _("{STR_VAR_1} מביט בך בהערצה!");
static const u8 sLoveMsg08[] = _("{STR_VAR_1} התקרב אליך.");
static const u8 sLoveMsg09[] = _("{STR_VAR_1} נצמד לרגליים שלך.");

const struct FollowerMsgInfo gFollowerLoveMessages[] = {
    {sLoveMsg00, EventScript_FollowerGetCloser},
    {sLoveMsg01},
    {sLoveMsg02, EventScript_FollowerCuddling},
    {sLoveMsg03},
    {sLoveMsg04, EventScript_FollowerCuddling},
    {sLoveMsg05},
    {sLoveMsg06, EventScript_FollowerCuddling},
    {sLoveMsg07},
    {sLoveMsg08, EventScript_FollowerGetCloser},
    {sLoveMsg09},
};

// Unconditional surprised messages
static const u8 sSurpriseMsg00[] = _("{STR_VAR_1} עלול ליפול!");
static const u8 sSurpriseMsg01[] = _("{STR_VAR_1} נתקל בך!");
static const u8 sSurpriseMsg02[] = _("{STR_VAR_1} כנראה עוד לא\nהתרגל לשם שלו.");
static const u8 sSurpriseMsg03[] = _("{STR_VAR_1} מציץ למטה.");
static const u8 sSurpriseMsg04[] = _("הפוקימון שלך מעד וכמעט נפל!");
static const u8 sSurpriseMsg05[] = _("{STR_VAR_1} חש משהו ומיילל!");
static const u8 sSurpriseMsg06[] = _("{STR_VAR_1} נראה רענן!");
static const u8 sSurpriseMsg07[] = _("{STR_VAR_1} הסתובב פתאום\nוהתחיל לנבוח!");
static const u8 sSurpriseMsg08[] = _("{STR_VAR_1} הסתובב פתאום!");
static const u8 sSurpriseMsg09[] = _("הפוקימון שלך הופתע\nשפתאום דיברת אליו!");
static const u8 sSurpriseMsg10[] = _("רחרוח, רחרוח, משהו מריח ממש טוב!");
static const u8 sSurpriseMsg11[] = _("{STR_VAR_1} מרגיש רענן.");
static const u8 sSurpriseMsg12[] = _("{STR_VAR_1} מתנדנד ונראה\nשהוא עומד ליפול.");
static const u8 sSurpriseMsg13[] = _("{STR_VAR_1} עלול ליפול.");
static const u8 sSurpriseMsg14[] = _("{STR_VAR_1} הולך בזהירות.");
static const u8 sSurpriseMsg15[] = _("{STR_VAR_1} נדרך כולו מרוב מתח.");
static const u8 sSurpriseMsg16[] = _("{STR_VAR_1} חש משהו מוזר והופתע!");
static const u8 sSurpriseMsg17[] = _("{STR_VAR_1} נבהל ונצמד אליך!");
static const u8 sSurpriseMsg18[] = _("{STR_VAR_1} מרגיש נוכחות משונה…");
static const u8 sSurpriseMsg19[] = _("{STR_VAR_1} נדרך כולו מרוב מתח.");
// Conditional messages, index 20
static const u8 sSurpriseMsg20[] = _("{STR_VAR_1} נראה מופתע מאוד\nמכך שיורד גשם!");

const struct FollowerMsgInfo gFollowerSurpriseMessages[] = {
    {sSurpriseMsg00},
    {sSurpriseMsg01, EventScript_FollowerPokingPlayer},
    {sSurpriseMsg02}, {sSurpriseMsg03}, {sSurpriseMsg04}, {sSurpriseMsg05}, {sSurpriseMsg06},
    {sSurpriseMsg07, EventScript_FollowerLookAwayBark},
    {sSurpriseMsg08, EventScript_FollowerLookAway},
    {sSurpriseMsg09},
    {sSurpriseMsg10, EventScript_FollowerLookAround},
    {sSurpriseMsg11}, {sSurpriseMsg12}, {sSurpriseMsg13}, {sSurpriseMsg14}, {sSurpriseMsg15}, {sSurpriseMsg16},
    {sSurpriseMsg17, EventScript_FollowerCuddling},
    {sSurpriseMsg18},
    {sSurpriseMsg19, EventScript_FollowerLookAround},
    {sSurpriseMsg20},
};

// Unconditional curious messages
static const u8 sCuriousMsg00[] = _("הפוקימון שלך מסתכל סביבו\nבחוסר מנוחה ומחפש משהו.");
static const u8 sCuriousMsg01[] = _("הפוקימון שלך לא הסתכל\nלאן הוא הולך ונתקל בך!");
static const u8 sCuriousMsg02[] = _("רחרוח, רחרוח! יש משהו\nבסביבה?");
static const u8 sCuriousMsg03[] = _("{STR_VAR_1} משחק ומגלגל\nחלוק אבן.");
static const u8 sCuriousMsg04[] = _("{STR_VAR_1} משוטט מסביב\nומחפש משהו.");
static const u8 sCuriousMsg05[] = _("{STR_VAR_1} מרחרח אותך.");
static const u8 sCuriousMsg06[] = _("{STR_VAR_1} נראה קצת\nמהסס…");

const struct FollowerMsgInfo gFollowerCuriousMessages[] = {
    {sCuriousMsg00, EventScript_FollowerLookAround},
    {sCuriousMsg01, EventScript_FollowerPokingPlayer},
    {sCuriousMsg02}, {sCuriousMsg03},
    {sCuriousMsg04, EventScript_FollowerLookAround},
    {sCuriousMsg05}, {sCuriousMsg06},
};

// Unconditional music messages
static const u8 sMusicMsg00[] = _("{STR_VAR_1} מפגין\nאת הזריזות שלו!");
static const u8 sMusicMsg01[] = _("{STR_VAR_1} מתרוצץ\nבשמחה!");
static const u8 sMusicMsg02[] = _("וואו! {STR_VAR_1} פתאום התחיל\nלרקוד משמחה!");
static const u8 sMusicMsg03[] = _("{STR_VAR_1} צועד לצדך\nבקצב יציב!");
static const u8 sMusicMsg04[] = _("{STR_VAR_1} כנראה רוצה\nלשחק איתך.");
static const u8 sMusicMsg05[] = _("{STR_VAR_1} מקפץ לו בשמחה.");
static const u8 sMusicMsg06[] = _("{STR_VAR_1} שר ומזמזם.");
static const u8 sMusicMsg07[] = _("{STR_VAR_1} נוגס קלות\nברגליים שלך!");
static const u8 sMusicMsg08[] = _("{STR_VAR_1} מסתובב\nומביט בך.");
static const u8 sMusicMsg09[] = _("{STR_VAR_1} מתאמץ להפגין\nאת כוחו האדיר!");
static const u8 sMusicMsg10[] = _("וואו! {STR_VAR_1} פתאום רקד\nמרוב שמחה!");
static const u8 sMusicMsg11[] = _("{STR_VAR_1} במצב רוח עליז!");
static const u8 sMusicMsg12[] = _("{STR_VAR_1} קופץ פה ושם\nבלי שום דאגה!");
static const u8 sMusicMsg13[] = _("נראה שהפוקימון שלך קולט\nריח מוכר שמעורר געגועים…");
// Conditional music messages, index 14
static const u8 sMusicMsg14[] = _("{STR_VAR_1} שמח מאוד\nבגשם.");

const struct FollowerMsgInfo gFollowerMusicMessages[] = {
    {sMusicMsg00, EventScript_FollowerLookAround},
    {sMusicMsg01},
    {sMusicMsg02, EventScript_FollowerDance},
    {sMusicMsg03},
    {sMusicMsg04, EventScript_FollowerHopping},
    {sMusicMsg05, EventScript_FollowerHopping},
    {sMusicMsg06}, {sMusicMsg07}, {sMusicMsg08}, {sMusicMsg09},
    {sMusicMsg10, EventScript_FollowerDance},
    {sMusicMsg11},
    {sMusicMsg12, EventScript_FollowerHopping},
    {sMusicMsg13, EventScript_FollowerNostalgia},
    {sMusicMsg14}
};


static const u8 sPoisonedMsg00[] = _("{STR_VAR_1} רועד\nמהשפעת הרעל.");

const struct FollowerMsgInfo gFollowerPoisonedMessages[] = {
    {sPoisonedMsg00, EventScript_FollowerIsShivering},
};
