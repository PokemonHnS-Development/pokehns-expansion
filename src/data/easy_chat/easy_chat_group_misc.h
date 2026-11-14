const struct EasyChatWordInfo gEasyChatGroup_Misc[] = {
    [EC_INDEX(EC_WORD_HIGHS)] =
    {
        .text = COMPOUND_STRING("עליות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_ABOVE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOWS)] =
    {
        .text = COMPOUND_STRING("ירידות"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_AM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UM)] =
    {
        .text = COMPOUND_STRING("אממ"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_AWAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_REAR)] =
    {
        .text = COMPOUND_STRING("אחורי"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BACK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THINGS)] =
    {
        .text = COMPOUND_STRING("דברים"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BELOW),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THING)] =
    {
        .text = COMPOUND_STRING("דבר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_BESIDE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BELOW)] =
    {
        .text = COMPOUND_STRING("מתחת"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CHOICE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ABOVE)] =
    {
        .text = COMPOUND_STRING("מעל"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_CONFUSED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BACK)] =
    {
        .text = COMPOUND_STRING("בחזרה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DEEP),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HIGH)] =
    {
        .text = COMPOUND_STRING("גבוה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_DOWN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HERE)] =
    {
        .text = COMPOUND_STRING("כאן"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_EVERY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_INSIDE)] =
    {
        .text = COMPOUND_STRING("בפנים"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_OUTSIDE)] =
    {
        .text = COMPOUND_STRING("בחוץ"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_FRONT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BESIDE)] =
    {
        .text = COMPOUND_STRING("ליד"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HERE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THIS_IS_IT_EXCL)] =
    {
        .text = COMPOUND_STRING("זהו זה!"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HIGH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THIS)] =
    {
        .text = COMPOUND_STRING("זה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_HIGHS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EVERY)] =
    {
        .text = COMPOUND_STRING("כל"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_INSIDE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THESE)] =
    {
        .text = COMPOUND_STRING("אלה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LEFT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THESE_WERE)] =
    {
        .text = COMPOUND_STRING("אלה היו"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOWS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DOWN)] =
    {
        .text = COMPOUND_STRING("למטה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THAT)] =
    {
        .text = COMPOUND_STRING("זאת"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_OPPOSITE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THOSE_ARE)] =
    {
        .text = COMPOUND_STRING("אלו הם"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_OUTSIDE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THOSE_WERE)] =
    {
        .text = COMPOUND_STRING("אלו היו"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_REAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THAT_S_IT_EXCL)] =
    {
        .text = COMPOUND_STRING("זהו!"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_RIGHT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_AM)] =
    {
        .text = COMPOUND_STRING("האם"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHALLOW),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THAT_WAS)] =
    {
        .text = COMPOUND_STRING("זה היה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FRONT)] =
    {
        .text = COMPOUND_STRING("קדמי"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THAT_WAS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_UP)] =
    {
        .text = COMPOUND_STRING("למעלה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THAT_S_IT_EXCL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CHOICE)] =
    {
        .text = COMPOUND_STRING("בחירה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THESE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FAR)] =
    {
        .text = COMPOUND_STRING("רחוק"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THESE_WERE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_AWAY)] =
    {
        .text = COMPOUND_STRING("הרחק"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEAR)] =
    {
        .text = COMPOUND_STRING("בקרבת"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THINGS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WHERE)] =
    {
        .text = COMPOUND_STRING("איפה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THIS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WHEN)] =
    {
        .text = COMPOUND_STRING("מתי"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THIS_IS_IT_EXCL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WHAT)] =
    {
        .text = COMPOUND_STRING("מה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THOSE_ARE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DEEP)] =
    {
        .text = COMPOUND_STRING("עמוק"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_THOSE_WERE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHALLOW)] =
    {
        .text = COMPOUND_STRING("רדוד"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WHY)] =
    {
        .text = COMPOUND_STRING("למה"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_UP),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CONFUSED)] =
    {
        .text = COMPOUND_STRING("מבולבל"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WHAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_OPPOSITE)] =
    {
        .text = COMPOUND_STRING("ההפך"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WHEN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LEFT)] =
    {
        .text = COMPOUND_STRING("השאיר"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WHERE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RIGHT)] =
    {
        .text = COMPOUND_STRING("ממש"),
        .alphabeticalOrder = EC_INDEX(EC_WORD_WHY),
        .enabled = TRUE,
    },
};
