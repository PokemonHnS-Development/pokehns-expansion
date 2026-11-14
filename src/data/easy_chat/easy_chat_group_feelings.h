const u8 gEasyChatWord_Meet[] = _("לפגוש");
const u8 gEasyChatWord_Play[] = _("לשחק");
const u8 gEasyChatWord_Hurried[] = _("ממהר");
const u8 gEasyChatWord_Goes[] = _("נמשך");
const u8 gEasyChatWord_Giddy[] = _("סחרחר");
const u8 gEasyChatWord_Happy[] = _("שמח");
const u8 gEasyChatWord_Happiness[] = _("אושר");
const u8 gEasyChatWord_Excite[] = _("מתרגש");
const u8 gEasyChatWord_Important[] = _("חשוב");
const u8 gEasyChatWord_Funny[] = _("מצחיק");
const u8 gEasyChatWord_Got[] = _("השיג");
const u8 gEasyChatWord_GoHome[] = _("ללכת הביתה");
const u8 gEasyChatWord_Disappointed[] = _("מאוכזב");
const u8 gEasyChatWord_Disappoints[] = _("מאכזב");
const u8 gEasyChatWord_Sad[] = _("עצוב");
const u8 gEasyChatWord_Try[] = _("לנסות");
const u8 gEasyChatWord_Tries[] = _("מנסה");
const u8 gEasyChatWord_Hears[] = _("שומע");
const u8 gEasyChatWord_Think[] = _("לחשוב");
const u8 gEasyChatWord_Hear[] = _("לשמוע");
const u8 gEasyChatWord_Wants[] = _("מעוניין");
const u8 gEasyChatWord_Misheard[] = _("שמע לא נכון");
const u8 gEasyChatWord_Dislike[] = _("לא אוהב");
const u8 gEasyChatWord_Angry[] = _("כועס");
const u8 gEasyChatWord_Anger[] = _("כעס");
const u8 gEasyChatWord_Scary[] = _("מפחיד");
const u8 gEasyChatWord_Lonesome[] = _("בודד");
const u8 gEasyChatWord_Disappoint[] = _("לאכזב");
const u8 gEasyChatWord_Joy[] = _("שמחה");
const u8 gEasyChatWord_Gets[] = _("מקבל");
const u8 gEasyChatWord_Never[] = _("לעולם לא");
const u8 gEasyChatWord_Darn[] = _("לעזאזל");
const u8 gEasyChatWord_Downcast[] = _("מדוכדך");
const u8 gEasyChatWord_Incredible[] = _("לא ייאמן");
const u8 gEasyChatWord_Likes[] = _("אוהב");
const u8 gEasyChatWord_Dislikes[] = _("לא מחבב");
const u8 gEasyChatWord_Boring[] = _("משעמם");
const u8 gEasyChatWord_Care[] = _("אכפת");
const u8 gEasyChatWord_Cares[] = _("דואג");
const u8 gEasyChatWord_AllRight[] = _("בסדר");
const u8 gEasyChatWord_Adore[] = _("מעריץ");
const u8 gEasyChatWord_Disaster[] = _("אסון");
const u8 gEasyChatWord_Enjoy[] = _("ליהנות");
const u8 gEasyChatWord_Enjoys[] = _("נהנה");
const u8 gEasyChatWord_Eat[] = _("לאכול");
const u8 gEasyChatWord_Lacking[] = _("חסר");
const u8 gEasyChatWord_Bad[] = _("רע");
const u8 gEasyChatWord_Hard[] = _("קשה");
const u8 gEasyChatWord_Terrible[] = _("נורא");
const u8 gEasyChatWord_Should[] = _("אמור");
const u8 gEasyChatWord_Nice[] = _("נחמד");
const u8 gEasyChatWord_Drink[] = _("לשתות");
const u8 gEasyChatWord_Surprise[] = _("הפתעה");
const u8 gEasyChatWord_Fear[] = _("פחד");
const u8 gEasyChatWord_Want[] = _("רוצה");
const u8 gEasyChatWord_Wait[] = _("לחכות");
const u8 gEasyChatWord_Satisfied[] = _("מרוצה");
const u8 gEasyChatWord_See[] = _("לראות");
const u8 gEasyChatWord_Rare[] = _("נדיר");
const u8 gEasyChatWord_Negative[] = _("שלילי");
const u8 gEasyChatWord_Done[] = _("גמור");
const u8 gEasyChatWord_Danger[] = _("סכנה");
const u8 gEasyChatWord_Defeated[] = _("מובס");
const u8 gEasyChatWord_Beat[] = _("להביס");
const u8 gEasyChatWord_Great[] = _("נהדר");
const u8 gEasyChatWord_Romantic[] = _("רומנטי");
const u8 gEasyChatWord_Question[] = _("שאלה");
const u8 gEasyChatWord_Understand[] = _("להבין");
const u8 gEasyChatWord_Understands[] = _("מבין");

const struct EasyChatWordInfo gEasyChatGroup_Feelings[] = {
    [EC_INDEX(EC_WORD_MEET)] =
    {
        .text = COMPOUND_STRING("לפגוש"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ADORE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PLAY)] =
    {
        .text = COMPOUND_STRING("לשחק"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ALL_RIGHT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HURRIED)] =
    {
        .text = COMPOUND_STRING("ממהר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANGER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GOES)] =
    {
        .text = COMPOUND_STRING("נמשך"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANGRY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GIDDY)] =
    {
        .text = COMPOUND_STRING("סחרחר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BAD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HAPPY)] =
    {
        .text = COMPOUND_STRING("שמח"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BEAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HAPPINESS)] =
    {
        .text = COMPOUND_STRING("אושר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BORING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EXCITE)] =
    {
        .text = COMPOUND_STRING("מתרגש"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CARE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_IMPORTANT)] =
    {
        .text = COMPOUND_STRING("חשוב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CARES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FUNNY)] =
    {
        .text = COMPOUND_STRING("מצחיק"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DANGER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GOT)] =
    {
        .text = COMPOUND_STRING("השיג"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DARN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GO_HOME)] =
    {
        .text = COMPOUND_STRING("ללכת הביתה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DEFEATED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISAPPOINTED)] =
    {
        .text = COMPOUND_STRING("מאוכזב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISAPPOINT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISAPPOINTS)] =
    {
        .text = COMPOUND_STRING("מאכזב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISAPPOINTED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SAD)] =
    {
        .text = COMPOUND_STRING("עצוב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISAPPOINTS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRY)] =
    {
        .text = COMPOUND_STRING("לנסות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISASTER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRIES)] =
    {
        .text = COMPOUND_STRING("מנסה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISLIKE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HEARS)] =
    {
        .text = COMPOUND_STRING("שומע"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DISLIKES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THINK)] =
    {
        .text = COMPOUND_STRING("לחשוב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DONE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HEAR)] =
    {
        .text = COMPOUND_STRING("לשמוע"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DOWNCAST),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WANTS)] =
    {
        .text = COMPOUND_STRING("מעוניין"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DRINK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MISHEARD)] =
    {
        .text = COMPOUND_STRING("שמע לא נכון"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISLIKE)] =
    {
        .text = COMPOUND_STRING("לא אוהב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ENJOY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANGRY)] =
    {
        .text = COMPOUND_STRING("כועס"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ENJOYS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANGER)] =
    {
        .text = COMPOUND_STRING("כעס"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EXCITE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SCARY)] =
    {
        .text = COMPOUND_STRING("מפחיד"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FEAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LONESOME)] =
    {
        .text = COMPOUND_STRING("בודד"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FUNNY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISAPPOINT)] =
    {
        .text = COMPOUND_STRING("לאכזב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GETS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_JOY)] =
    {
        .text = COMPOUND_STRING("שמחה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GIDDY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GETS)] =
    {
        .text = COMPOUND_STRING("מקבל"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GO_HOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEVER)] =
    {
        .text = COMPOUND_STRING("לעולם לא"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GOES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DARN)] =
    {
        .text = COMPOUND_STRING("לעזאזל"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GOT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DOWNCAST)] =
    {
        .text = COMPOUND_STRING("מדוכדך"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_GREAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_INCREDIBLE)] =
    {
        .text = COMPOUND_STRING("לא ייאמן"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HAPPINESS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LIKES)] =
    {
        .text = COMPOUND_STRING("אוהב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HAPPY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISLIKES)] =
    {
        .text = COMPOUND_STRING("לא מחבב"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HARD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BORING)] =
    {
        .text = COMPOUND_STRING("משעמם"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HEAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CARE)] =
    {
        .text = COMPOUND_STRING("אכפת"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HEARS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CARES)] =
    {
        .text = COMPOUND_STRING("דואג"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HURRIED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ALL_RIGHT)] =
    {
        .text = COMPOUND_STRING("בסדר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_IMPORTANT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ADORE)] =
    {
        .text = COMPOUND_STRING("מעריץ"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_INCREDIBLE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DISASTER)] =
    {
        .text = COMPOUND_STRING("אסון"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_JOY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ENJOY)] =
    {
        .text = COMPOUND_STRING("ליהנות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LACKING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ENJOYS)] =
    {
        .text = COMPOUND_STRING("נהנה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LIKES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EAT)] =
    {
        .text = COMPOUND_STRING("לאכול"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LONESOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LACKING)] =
    {
        .text = COMPOUND_STRING("חסר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_MEET),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BAD)] =
    {
        .text = COMPOUND_STRING("רע"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_MISHEARD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HARD)] =
    {
        .text = COMPOUND_STRING("קשה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEGATIVE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TERRIBLE)] =
    {
        .text = COMPOUND_STRING("נורא"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEVER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHOULD)] =
    {
        .text = COMPOUND_STRING("אמור"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NICE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NICE)] =
    {
        .text = COMPOUND_STRING("נחמד"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_PLAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DRINK)] =
    {
        .text = COMPOUND_STRING("לשתות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_QUESTION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SURPRISE)] =
    {
        .text = COMPOUND_STRING("הפתעה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_RARE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FEAR)] =
    {
        .text = COMPOUND_STRING("פחד"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ROMANTIC),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WANT)] =
    {
        .text = COMPOUND_STRING("רוצה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SAD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WAIT)] =
    {
        .text = COMPOUND_STRING("לחכות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SATISFIED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SATISFIED)] =
    {
        .text = COMPOUND_STRING("מרוצה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SCARY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SEE)] =
    {
        .text = COMPOUND_STRING("לראות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SEE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RARE)] =
    {
        .text = COMPOUND_STRING("נדיר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHOULD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEGATIVE)] =
    {
        .text = COMPOUND_STRING("שלילי"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SURPRISE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DONE)] =
    {
        .text = COMPOUND_STRING("גמור"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TERRIBLE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DANGER)] =
    {
        .text = COMPOUND_STRING("סכנה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THINK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DEFEATED)] =
    {
        .text = COMPOUND_STRING("מובס"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRIES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BEAT)] =
    {
        .text = COMPOUND_STRING("להביס"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GREAT)] =
    {
        .text = COMPOUND_STRING("נהדר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UNDERSTAND),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ROMANTIC)] =
    {
        .text = COMPOUND_STRING("רומנטי"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UNDERSTANDS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_QUESTION)] =
    {
        .text = COMPOUND_STRING("שאלה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WAIT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UNDERSTAND)] =
    {
        .text = COMPOUND_STRING("להבין"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WANT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UNDERSTANDS)] =
    {
        .text = COMPOUND_STRING("מבין"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WANTS),
        .enabled = TRUE,
    },
};
