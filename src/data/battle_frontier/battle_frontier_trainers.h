const struct BattleFrontierTrainer gBattleFrontierTrainers[FRONTIER_TRAINERS_COUNT] =
{
    [FRONTIER_TRAINER_BRADY] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("בריידי"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NEVER, EC_WORD_GOING, EC_WORD_TO, EC_WORD_LOSE, EC_WORD_EXCL},
        .speechWin = {EC_WORD_I_AM, EC_WORD_STRONG, EC_WORD_AREN_T, EC_WORD_I, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WHAT, EC_WORD_QUES, EC_EMPTY_WORD, EC_WORD_BUT, EC_WORD_HOW, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_CONNER] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("קונר"),
        .speechBefore = {EC_WORD_LOSING, EC_WORD_DOESN_T, EC_WORD_BUG, EC_WORD_ME, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_A, EC_WORD_WIN, EC_WORD_IS, EC_WORD_JUST, EC_WORD_AWESOME, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_DARN, EC_WORD_ELLIPSIS, EC_WORD_LOSING, EC_WORD_DOES, EC_WORD_BUG, EC_WORD_ME},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_BRADLEY] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("בראדלי"),
        .speechBefore = {EC_WORD_HEY_THERE, EC_WORD_EXCL, EC_WORD_YOU_RE, EC_WORD_MY, EC_WORD_OPPONENT, EC_WORD_TODAY},
        .speechWin = {EC_WORD_HAHAHA, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_SEE_YA, EC_WORD_LATER, EC_WORD_EXCL},
        .speechLose = {EC_WORD_TOMORROW, EC_WORD_IS, EC_WORD_WHEN, EC_WORD_WE, EC_WORD_REALLY, EC_WORD_BATTLE},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_CYBIL] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("סיביל"),
        .speechBefore = {EC_WORD_YOU_RE, EC_WORD_REALLY, EC_WORD_NOT_VERY, EC_WORD_SCARY, EC_WORD_AT, EC_WORD_ALL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_SAD, EC_WORD_TO, EC_WORD_SEE, EC_WORD_YOU, EC_MOVE2(STRUGGLE)},
        .speechLose = {EC_WORD_THIS, EC_WORD_CAN_T, EC_WORD_BE, EC_WORD_HAPPENING, EC_WORD_TO_ME, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_RODETTE] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("רודט"),
        .speechBefore = {EC_WORD_OH, EC_WORD_THIS, EC_WORD_IS, EC_WORD_SO, EC_WORD_EXCITING, EC_WORD_EXCL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_INCREDIBLE, EC_WORD_HOW, EC_WORD_STRONG, EC_WORD_I_AM, EC_WORD_EXCL},
        .speechLose = {EC_WORD_OH_DEAR, EC_WORD_ELLIPSIS, EC_WORD_I_AM, EC_WORD_JUST, EC_WORD_NO, EC_WORD_GOOD},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_PEGGY] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("פגי"),
        .speechBefore = {EC_WORD_GET, EC_WORD_READY, EC_WORD_TO, EC_WORD_BE, EC_WORD_DESTROYED, EC_WORD_EXCL},
        .speechWin = {EC_WORD_HAHAHA, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_LOLLING, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_SAD, EC_WORD_THANKS, EC_WORD_TO, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_KEITH] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_M,
        .trainerName = _("קית'"),
        .speechBefore = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_JUST, EC_WORD_STUDY, EC_WORD_YOU, EC_WORD_KNOW},
        .speechWin = {EC_WORD_YOU, EC_WORD_DON_T, EC_WORD_STUDY, EC_WORD_ENOUGH, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_NEED, EC_WORD_TO, EC_WORD_STUDY, EC_WORD_MORE, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_GRAYSON] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_M,
        .trainerName = _("גרייסון"),
        .speechBefore = {EC_WORD_A, EC_WORD_POKEMON, EC_WORD_BATTLE, EC_WORD_ISN_T, EC_WORD_CHILD_S_PLAY, EC_WORD_EXCL},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_DONE, EC_WORD_AREN_T, EC_WORD_YOU, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WE, EC_WORD_WERE, EC_WORD_LIKE, EC_WORD_TOYS, EC_WORD_TO, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_GLENN] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_M,
        .trainerName = _("גלן"),
        .speechBefore = {EC_WORD_I, EC_WORD_WOULD, EC_WORD_BE, EC_WORD_COOL, EC_WORD_IF_I_WIN, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_COOL, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_THAT_S, EC_WORD_WHAT, EC_WORD_I_AM},
        .speechLose = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_GOING, EC_WORD_TO, EC_WORD_BE, EC_WORD_COOL},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_LILIANA] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_F,
        .trainerName = _("ליליאנה"),
        .speechBefore = {EC_WORD_I, EC_WORD_WON_T, EC_WORD_GIVE_UP, EC_WORD_UNTIL, EC_WORD_I, EC_WORD_WIN},
        .speechWin = {EC_WORD_THERE, EC_WORD_IS, EC_WORD_NO, EC_WORD_SURRENDER, EC_WORD_IN, EC_WORD_ME},
        .speechLose = {EC_WORD_THAT_S, EC_WORD_IT, EC_WORD_ELLIPSIS, EC_WORD_I, EC_WORD_GIVE_UP, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_ELISE] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_F,
        .trainerName = _("אליז"),
        .speechBefore = {EC_WORD_MY, EC_WORD_STRATEGY, EC_WORD_IS, EC_WORD_FROM, EC_WORD_MY, EC_WORD_FATHER},
        .speechWin = {EC_WORD_I, EC_WORD_WIN, EC_WORD_EXCL, EC_WORD_FATHER, EC_WORD_I_VE, EC_WORD_WON},
        .speechLose = {EC_WORD_FORGIVE, EC_WORD_ME, EC_WORD_FATHER, EC_WORD_FOR, EC_WORD_I_VE, EC_WORD_LOST},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_ZOEY] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_F,
        .trainerName = _("זואי"),
        .speechBefore = {EC_WORD_PLEASE, EC_WORD_BATTLE, EC_WORD_LIKE, EC_WORD_YOU, EC_WORD_MEAN, EC_WORD_IT},
        .speechWin = {EC_WORD_THANK_YOU, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_THANK_YOU, EC_WORD_SO, EC_WORD_MUCH},
        .speechLose = {EC_WORD_WERE, EC_WORD_YOU, EC_WORD_REALLY, EC_WORD_BEING, EC_WORD_SERIOUS, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_MANUEL] = {
        .facilityClass = FACILITY_CLASS_RICH_BOY,
        .trainerName = _("מנואל"),
        .speechBefore = {EC_WORD_ME, EC_WORD_LOSE, EC_WORD_QUES, EC_WORD_THAT_S, EC_WORD_PREPOSTEROUS, EC_WORD_EXCL},
        .speechWin = {EC_WORD_NATURALLY, EC_WORD_I, EC_WORD_WIN, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WAAAH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_LOST, EC_WORD_MOTHER},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_1}
    },
    [FRONTIER_TRAINER_RUSS] = {
        .facilityClass = FACILITY_CLASS_RICH_BOY,
        .trainerName = _("ראס"),
        .speechBefore = {EC_WORD_THEY, EC_WORD_ALL, EC_WORD_WANT, EC_WORD_MY, EC_WORD_FABULOUS, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_I, EC_WORD_WILL, EC_WORD_HAVE, EC_WORD_A, EC_WORD_POKEMON, EC_WORD_PARTY},
        .speechLose = {EC_WORD_HOW, EC_WORD_COULD, EC_WORD_YOU, EC_WORD_DO, EC_WORD_THAT, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_1}
    },
    [FRONTIER_TRAINER_DUSTIN] = {
        .facilityClass = FACILITY_CLASS_RICH_BOY,
        .trainerName = _("דאסטין"),
        .speechBefore = {EC_WORD_I, EC_WORD_REALLY, EC_WORD_LIKE, EC_WORD_COOL, EC_WORD_POKEMON, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_MYSELF, EC_WORD_WHEN_I_WIN, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_MYSELF, EC_WORD_IF_I_LOSE, EC_WORD_TOO, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_1}
    },
    [FRONTIER_TRAINER_TINA] = {
        .facilityClass = FACILITY_CLASS_LADY,
        .trainerName = _("טינה"),
        .speechBefore = {EC_WORD_IF_I_WIN, EC_WORD_YOU, EC_WORD_CAN, EC_WORD_HAVE, EC_WORD_A, EC_MOVE2(SWEET_KISS)},
        .speechWin = {EC_WORD_HERE_IT_IS, EC_WORD_YOUR, EC_MOVE2(SWEET_KISS), EC_WORD_FROM, EC_WORD_MY, EC_POKEMON_NATIONAL(JYNX)},
        .speechLose = {EC_WORD_YOU, EC_WORD_WANT, EC_WORD_A, EC_MOVE(SWIFT), EC_MOVE2(MEGA_KICK), EC_WORD_INSTEAD},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_1}
    },
    [FRONTIER_TRAINER_GILLIAN1] = {
        .facilityClass = FACILITY_CLASS_LADY,
        .trainerName = _("ג'יליאן"),
        .speechBefore = {EC_WORD_THE, EC_WORD_GOURMET, EC_WORD_THING, EC_WORD_IS, EC_WORD_SO, EC_WORD_YESTERDAY},
        .speechWin = {EC_WORD_POKEMON, EC_WORD_NEVER, EC_WORD_GO, EC_WORD_OUT, EC_WORD_OF, EC_WORD_FASHION},
        .speechLose = {EC_WORD_LOSING, EC_WORD_DOESN_T, EC_WORD_DISAPPOINT, EC_WORD_ME, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_1}
    },
    [FRONTIER_TRAINER_ZOE] = {
        .facilityClass = FACILITY_CLASS_LADY,
        .trainerName = _("זואי"),
        .speechBefore = {EC_WORD_I, EC_WORD_HAVEN_T, EC_WORD_A, EC_WORD_WORRY, EC_WORD_AT, EC_WORD_ALL},
        .speechWin = {EC_WORD_LIFE, EC_WORD_IS, EC_WORD_ALWAYS, EC_WORD_GOOD, EC_WORD_TO_ME, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_WORRY, EC_WORD_ABOUT, EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_SKILL},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_1}
    },
    [FRONTIER_TRAINER_CHEN] = {
        .facilityClass = FACILITY_CLASS_CAMPER,
        .trainerName = _("צ'ן"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_TOTALLY, EC_WORD_READY, EC_WORD_TO, EC_WORD_ROCK, EC_WORD_TODAY},
        .speechWin = {EC_WORD_I_AM, EC_WORD_READY, EC_WORD_TO, EC_WORD_GO, EC_WORD_ON, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I_VE, EC_WORD_LOST, EC_WORD_MY, EC_MOVE(FOCUS_ENERGY), EC_WORD_AND, EC_WORD_TOUGHNESS},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_AL] = {
        .facilityClass = FACILITY_CLASS_CAMPER,
        .trainerName = _("אל"),
        .speechBefore = {EC_WORD_YOUR, EC_WORD_LOOK, EC_WORD_SAYS, EC_WORD_YOU_RE, EC_WORD_REALLY, EC_WORD_TOUGH},
        .speechWin = {EC_WORD_IT_S, EC_WORD_ME, EC_WORD_WHO_IS, EC_WORD_REALLY, EC_WORD_TOUGH, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I_AM, EC_WORD_RIGHT, EC_WORD_EXCL, EC_WORD_YOU_RE, EC_WORD_REALLY, EC_WORD_TOUGH},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_MITCH] = {
        .facilityClass = FACILITY_CLASS_CAMPER,
        .trainerName = _("מיץ'"),
        .speechBefore = {EC_WORD_MOTHER, EC_WORD_NATURE, EC_WORD_IS, EC_WORD_MY, EC_WORD_ALLY, EC_WORD_EXCL},
        .speechWin = {EC_WORD_WAS, EC_WORD_THAT, EC_WORD_ENOUGH, EC_WORD_FOR, EC_WORD_YOU, EC_WORD_QUES},
        .speechLose = {EC_WORD_MOTHER, EC_WORD_NATURE, EC_WORD_DIDN_T, EC_WORD_LET_ME_WIN, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_ANNE] = {
        .facilityClass = FACILITY_CLASS_PICNICKER,
        .trainerName = _("אן"),
        .speechBefore = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_WAIT, EC_WORD_LET_S, EC_WORD_BATTLE, EC_WORD_NOW},
        .speechWin = {EC_WORD_MY, EC_WORD_HAPPINESS, EC_WORD_IS, EC_WORD_OVERWHELMING, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU_VE, EC_WORD_DESTROYED, EC_WORD_MY, EC_WORD_HAPPINESS, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_ALIZE] = {
        .facilityClass = FACILITY_CLASS_PICNICKER,
        .trainerName = _("אליז"),
        .speechBefore = {EC_WORD_CUTE, EC_WORD_AND, EC_WORD_AWFULLY, EC_WORD_STRONG, EC_WORD_THAT_S, EC_WORD_ME},
        .speechWin = {EC_WORD_YUP, EC_WORD_I_AM, EC_WORD_CUTE, EC_WORD_AND, EC_WORD_AWFULLY, EC_WORD_STRONG},
        .speechLose = {EC_WORD_I_AM, EC_WORD_WEAK, EC_WORD_ELLIPSIS, EC_WORD_BUT, EC_WORD_I_AM, EC_WORD_CUTE},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_LAUREN] = {
        .facilityClass = FACILITY_CLASS_PICNICKER,
        .trainerName = _("לורן"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_OLD, EC_WORD_BUT, EC_WORD_I_AM, EC_WORD_ALSO, EC_WORD_GOOD},
        .speechWin = {EC_WORD_I, EC_WORD_SAID, EC_WORD_I_WAS, EC_WORD_OLD, EC_WORD_BUT, EC_WORD_GOOD},
        .speechLose = {EC_WORD_WHAT, EC_WORD_A, EC_WORD_WEIRD, EC_WORD_DREAM, EC_WORD_THAT_WAS, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_KIPP] = {
        .facilityClass = FACILITY_CLASS_TUBER_M,
        .trainerName = _("קיפ"),
        .speechBefore = {EC_WORD_IF_I_WIN, EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_TO, EC_WORD_GO, EC_MOVE2(SURF)},
        .speechWin = {EC_WORD_YEAH, EC_WORD_EXCL, EC_WORD_I_AM, EC_WORD_OFF, EC_WORD_TO, EC_MOVE2(SURF)},
        .speechLose = {EC_WORD_OH, EC_WORD_NO, EC_WORD_EXCL, EC_WORD_A, EC_MOVE(WHIRLPOOL), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_1}
    },
    [FRONTIER_TRAINER_JASON] = {
        .facilityClass = FACILITY_CLASS_TUBER_M,
        .trainerName = _("ג'ייסון"),
        .speechBefore = {EC_WORD_TEACH, EC_WORD_ME, EC_WORD_A, EC_WORD_GOOD, EC_WORD_STRATEGY, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_YOUR, EC_WORD_GOOD, EC_WORD_STRATEGY, EC_WORD_QUES_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WOW, EC_WORD_THAT, EC_WORD_IS, EC_WORD_AN, EC_WORD_AWESOME, EC_WORD_STRATEGY},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_1}
    },
    [FRONTIER_TRAINER_JOHN] = {
        .facilityClass = FACILITY_CLASS_TUBER_M,
        .trainerName = _("ג'ון"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_A, EC_WORD_PRETTY, EC_WORD_NEW, EC_WORD_TRAINER, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I_AM, EC_WORD_NEW, EC_WORD_BUT, EC_WORD_I, EC_WORD_WON, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_NEW, EC_WORD_SO, EC_WORD_WHAT, EC_WORD_IF_I_LOSE, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_1}
    },
    [FRONTIER_TRAINER_ANN] = {
        .facilityClass = FACILITY_CLASS_TUBER_F,
        .trainerName = _("אן"),
        .speechBefore = {EC_WORD_IT_S, EC_WORD_SO, EC_WORD_EXCITING, EC_WORD_IT, EC_WORD_REALLY, EC_WORD_IS},
        .speechWin = {EC_WORD_I_AM, EC_WORD_SO, EC_WORD_HAPPY, EC_WORD_I, EC_WORD_CAN, EC_WORD_CRY},
        .speechLose = {EC_WORD_I_AM, EC_WORD_SO, EC_WORD_SAD, EC_WORD_I, EC_WORD_WILL, EC_WORD_CRY},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_1}
    },
    [FRONTIER_TRAINER_EILEEN] = {
        .facilityClass = FACILITY_CLASS_TUBER_F,
        .trainerName = _("איילין"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_PRETEND, EC_WORD_I_AM, EC_WORD_AN, EC_WORD_ADULT, EC_WORD_OK_QUES},
        .speechWin = {EC_WORD_SO, EC_WORD_THIS, EC_WORD_IS, EC_WORD_AN, EC_WORD_ADULT, EC_WORD_FEELING},
        .speechLose = {EC_WORD_AN, EC_WORD_ADULT, EC_WORD_CAN_T, EC_WORD_BEAT, EC_WORD_YOU, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_1}
    },
    [FRONTIER_TRAINER_CARLIE] = {
        .facilityClass = FACILITY_CLASS_TUBER_F,
        .trainerName = _("קרלי"),
        .speechBefore = {EC_WORD_MY, EC_WORD_SUMMER, EC_WORD_VACATION, EC_WORD_IS, EC_WORD_FOR, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_MY, EC_WORD_SUMMER, EC_WORD_VACATION, EC_WORD_WILL, EC_WORD_BE, EC_WORD_AWESOME},
        .speechLose = {EC_WORD_I, EC_WORD_CAN_T_WIN, EC_WORD_LIKE, EC_WORD_THIS, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_1}
    },
    [FRONTIER_TRAINER_GORDON] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_M,
        .trainerName = _("גורדון"),
        .speechBefore = {EC_WORD_VICTORY, EC_WORD_WILL, EC_WORD_COME, EC_WORD_TO_ME, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_OH_YEAH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_REALLY, EC_WORD_WON},
        .speechLose = {EC_WORD_NOTHING, EC_WORD_IS, EC_WORD_WORKING, EC_WORD_OUT, EC_WORD_FOR, EC_WORD_ME},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_M_1}
    },
    [FRONTIER_TRAINER_AYDEN] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_M,
        .trainerName = _("איידן"),
        .speechBefore = {EC_WORD_COME_ON, EC_WORD_I, EC_WORD_NEED, EC_WORD_A, EC_WORD_HOT, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_I, EC_WORD_NEED, EC_WORD_WATER, EC_WORD_TO, EC_WORD_COOL, EC_WORD_DOWN},
        .speechLose = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_ME, EC_WORD_FEELING, EC_WORD_ICE, EC_WORD_COLD},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_M_1}
    },
    [FRONTIER_TRAINER_MARCO] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_M,
        .trainerName = _("מרקו"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(SURF), EC_WORD_IN, EC_WORD_THE, EC_WORD_WINTER, EC_WORD_TOO},
        .speechWin = {EC_WORD_I, EC_WORD_WILL, EC_WORD_GO, EC_MOVE2(SURF), EC_WORD_RIGHT, EC_WORD_NOW},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_MOVE2(BEAT_UP), EC_WORD_MY, EC_MOVE2(SURF), EC_WORD_BOARD},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_M_1}
    },
    [FRONTIER_TRAINER_CIERRA] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_F,
        .trainerName = _("סיירה"),
        .speechBefore = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_TO, EC_WORD_SYNCHRONIZE, EC_WORD_MY, EC_WORD_SWIFT_SWIM},
        .speechWin = {EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_SYNCHRONIZE, EC_WORD_WITH, EC_WORD_ME, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_NEED, EC_WORD_TO, EC_WORD_SYNCHRONIZE, EC_WORD_BETTER, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_F_1}
    },
    [FRONTIER_TRAINER_MARCY] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_F,
        .trainerName = _("מרסי"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_A, EC_WORD_KNOCKOUT, EC_WORD_YOU, EC_WORD_CAN_T_WIN, EC_WORD_EXCL},
        .speechWin = {EC_WORD_AFTER, EC_WORD_ALL, EC_WORD_I_AM, EC_WORD_A, EC_WORD_KNOCKOUT, EC_WORD_EXCL},
        .speechLose = {EC_WORD_THAT_S, EC_WORD_NOT, EC_WORD_THE, EC_WORD_KNOCKOUT, EC_WORD_I, EC_WORD_MEAN},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_F_1}
    },
    [FRONTIER_TRAINER_KATHY] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_F,
        .trainerName = _("קתי"),
        .speechBefore = {EC_WORD_I_VE, EC_WORD_WON, EC_WORD_EVERY, EC_WORD_MATCH, EC_WORD_TODAY, EC_WORD_EXCL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_SO, EC_WORD_GREAT, EC_WORD_TO, EC_WORD_WIN, EC_WORD_EXCL},
        .speechLose = {EC_WORD_HUH_QUES, EC_WORD_I, EC_WORD_SHOULD, EC_WORD_NOT, EC_WORD_HAVE, EC_WORD_LOST},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_F_1}
    },
    [FRONTIER_TRAINER_PEYTON] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("פייטון"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NEVER, EC_WORD_DISAPPOINTED, EC_WORD_WITH, EC_WORD_MY, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_I_AM, EC_WORD_HAPPY, EC_WORD_IF, EC_WORD_WE, EC_WORD_WIN, EC_WORD_TOGETHER},
        .speechLose = {EC_WORD_I, EC_WORD_ADORE, EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_MORE, EC_WORD_IF_I_LOSE},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_M_1}
    },
    [FRONTIER_TRAINER_JULIAN] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("ג'וליאן"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_ADORE, EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_RIGHT, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_TOTALLY, EC_WORD_OUT, EC_WORD_OF, EC_WORD_THE, EC_WORD_QUESTION},
        .speechLose = {EC_WORD_YOU, EC_WORD_DO, EC_WORD_ADORE, EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_M_1}
    },
    [FRONTIER_TRAINER_QUINN] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("קווין"),
        .speechBefore = {EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_BUT, EC_WORD_A, EC_WORD_DREAM},
        .speechWin = {EC_WORD_THIS, EC_WORD_IS, EC_WORD_A, EC_WORD_BEAUTIFUL, EC_WORD_DREAM, EC_WORD_EXCL},
        .speechLose = {EC_WORD_THIS, EC_WORD_IS, EC_WORD_AN, EC_WORD_AWFUL, EC_MOVE(NIGHTMARE), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_M_1}
    },
    [FRONTIER_TRAINER_HAYLEE] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("היילי"),
        .speechBefore = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_KNOW, EC_WORD_HOW, EC_WORD_I_AM, EC_WORD_FEELING},
        .speechWin = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_OVERWHELMING, EC_WORD_JOY, EC_WORD_OVER, EC_WORD_THIS},
        .speechLose = {EC_WORD_DESTROYED, EC_WORD_IS, EC_WORD_THE, EC_WORD_WAY, EC_WORD_I_AM, EC_WORD_FEELING},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_F_1}
    },
    [FRONTIER_TRAINER_AMANDA] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("אמנדה"),
        .speechBefore = {EC_WORD_I, EC_WORD_COME, EC_WORD_FROM, EC_WORD_A, EC_WORD_TRAINER, EC_WORD_FAMILY},
        .speechWin = {EC_WORD_I, EC_WORD_WILL, EC_WORD_TREASURE, EC_WORD_THIS, EC_WORD_WIN, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_WANT, EC_WORD_TO, EC_WORD_GO_HOME, EC_WORD_RIGHT, EC_WORD_NOW},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_F_1}
    },
    [FRONTIER_TRAINER_STACY] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("סטייסי"),
        .speechBefore = {EC_WORD_ALL, EC_WORD_POKEMON, EC_WORD_HAVE, EC_WORD_THEIR, EC_WORD_OWN, EC_WORD_CUTE_CHARM},
        .speechWin = {EC_WORD_YOU, EC_WORD_SEE, EC_WORD_WHAT, EC_WORD_I, EC_WORD_MEAN, EC_WORD_QUES},
        .speechLose = {EC_WORD_SHOULD, EC_WORD_I, EC_WORD_NOT, EC_WORD_ADORE, EC_WORD_POKEMON, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_F_1}
    },
    // The below 6 are the early Pkmn Breeder class trainers, which use groups from other general classes
    [FRONTIER_TRAINER_RAFAEL] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_M,
        .trainerName = _("רפאל"),
        .speechBefore = {EC_WORD_COME_ON, EC_WORD_EXCL, EC_WORD_LET_S, EC_WORD_SEE, EC_WORD_SOME, EC_WORD_SPIRIT},
        .speechWin = {EC_WORD_THAT_S_IT_EXCL, EC_WORD_THAT_S, EC_WORD_THE, EC_WORD_SPIRIT, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WELL, EC_WORD_SO, EC_WORD_MUCH, EC_WORD_FOR, EC_WORD_OUR, EC_WORD_SPIRIT},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_OLIVER] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_M,
        .trainerName = _("אוליבר"),
        .speechBefore = {EC_WORD_A, EC_WORD_GENIUS, EC_WORD_THAT_S, EC_WORD_WHAT, EC_WORD_I_AM, EC_WORD_EXCL},
        .speechWin = {EC_WORD_THAT_S, EC_WORD_HOW, EC_WORD_A, EC_WORD_GENIUS, EC_WORD_WORKS, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_MORE, EC_WORD_A, EC_WORD_GENIUS, EC_WORD_THAN, EC_WORD_I_AM},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_PAYTON] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_M,
        .trainerName = _("פייטון"),
        .speechBefore = {EC_WORD_I, EC_WORD_TRAIN, EC_WORD_FROM, EC_WORD_THE, EC_WORD_EGG, EC_WORD_UP},
        .speechWin = {EC_WORD_WELL, EC_WORD_DONE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_A, EC_MOVE2(SOFT_BOILED), EC_WORD_LOSS, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_PAMELA] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_F,
        .trainerName = _("פמלה"),
        .speechBefore = {EC_WORD_ALL, EC_WORD_POKEMON, EC_WORD_ADORE, EC_WORD_A, EC_WORD_KIND, EC_WORD_TRAINER},
        .speechWin = {EC_WORD_IT_S, EC_WORD_TOO, EC_WORD_BAD, EC_WORD_YOU, EC_WORD_LOST, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_KIND, EC_WORD_AND, EC_WORD_YOU_RE, EC_WORD_ALSO, EC_WORD_STRONG},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_ELIZA] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_F,
        .trainerName = _("אלייזה"),
        .speechBefore = {EC_WORD_I, EC_WORD_ADORE, EC_WORD_POKEMON, EC_WORD_LIKE, EC_WORD_MY, EC_WORD_CHILDREN},
        .speechWin = {EC_WORD_I_AM, EC_WORD_SO, EC_WORD_HAPPY, EC_WORD_FOR, EC_WORD_MY, EC_WORD_POKEMON},
        .speechLose = {EC_WORD_OH_DEAR, EC_WORD_I_AM, EC_WORD_SO, EC_WORD_SORRY, EC_WORD_ABOUT, EC_WORD_THIS},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_MARISA] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_F,
        .trainerName = _("מריסה"),
        .speechBefore = {EC_WORD_I, EC_WORD_PROMISE, EC_WORD_TO, EC_WORD_BATTLE, EC_WORD_SERIOUSLY, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_PROMISE, EC_WORD_ME, EC_WORD_YOU, EC_WORD_WILL, EC_WORD_DO, EC_WORD_BETTER},
        .speechLose = {EC_WORD_PROMISE, EC_WORD_ME, EC_WORD_ANOTHER, EC_WORD_BATTLE, EC_WORD_PLEASE, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_LEWIS] = {
        .facilityClass = FACILITY_CLASS_BUG_CATCHER,
        .trainerName = _("לואיס"),
        .speechBefore = {EC_WORD_A_LITTLE, EC_WORD_BUG, EC_WORD_IS, EC_WORD_SCARY, EC_WORD_QUES, EC_WORD_HAHAHA},
        .speechWin = {EC_WORD_LOOK, EC_WORD_LOOK, EC_WORD_EXCL, EC_WORD_A, EC_WORD_SCARY, EC_WORD_BUG},
        .speechLose = {EC_WORD_OH, EC_WORD_A, EC_WORD_BUG, EC_WORD_ISN_T, EC_WORD_SCARY, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_CATCHER_1_EXTRA(METAPOD, KAKUNA)}
    },
    [FRONTIER_TRAINER_YOSHI] = {
        .facilityClass = FACILITY_CLASS_BUG_CATCHER,
        .trainerName = _("יושי"),
        .speechBefore = {EC_WORD_BUG, EC_WORD_POKEMON, EC_WORD_MAKE, EC_WORD_ME, EC_WORD_FEELING, EC_WORD_LOVEY_DOVEY},
        .speechWin = {EC_WORD_BUG, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_THE, EC_WORD_BEST, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_IGNORANT, EC_WORD_ABOUT, EC_WORD_BUG, EC_WORD_POKEMON, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_CATCHER_1_EXTRA(SILCOON, CASCOON)}
    },
    [FRONTIER_TRAINER_DESTIN] = {
        .facilityClass = FACILITY_CLASS_BUG_CATCHER,
        .trainerName = _("דסטין"),
        .speechBefore = {EC_WORD_IT_S, EC_WORD_WAY, EC_WORD_TOO, EC_WORD_HOT, EC_WORD_HERE, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I_AM, EC_WORD_ABOUT, EC_WORD_TO, EC_MOVE(OVERHEAT), EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_I, EC_WORD_NEED, EC_WORD_SOME, EC_WORD_WATER, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_CATCHER_1}
    },
    [FRONTIER_TRAINER_KEON] = {
        .facilityClass = FACILITY_CLASS_NINJA_BOY,
        .trainerName = _("קיאון"),
        .speechBefore = {EC_WORD_FORGIVE, EC_WORD_ME, EC_WORD_BUT, EC_WORD_HERE_I_COME, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_FORGIVE, EC_WORD_ME, EC_WORD_FOR, EC_WORD_MY, EC_WORD_OVERWHELMING, EC_WORD_POWER},
        .speechLose = {EC_WORD_I_AM, EC_WORD_SORRY, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_NINJA_BOY_1}
    },
    [FRONTIER_TRAINER_STUART] = {
        .facilityClass = FACILITY_CLASS_NINJA_BOY,
        .trainerName = _("סטיוארט"),
        .speechBefore = {EC_WORD_I, EC_WORD_PROMISE, EC_WORD_YOU, EC_WORD_A, EC_WORD_HOT, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_THE, EC_WORD_MASTER, EC_WORD_OF, EC_WORD_COOL, EC_WORD_THAT_S, EC_WORD_ME},
        .speechLose = {EC_WORD_I, EC_WORD_SEE, EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_SO, EC_WORD_COOL},
        .monSet = (const u16[]){FRONTIER_MONS_NINJA_BOY_1}
    },
    [FRONTIER_TRAINER_NESTOR] = {
        .facilityClass = FACILITY_CLASS_NINJA_BOY,
        .trainerName = _("נסטור"),
        .speechBefore = {EC_WORD_SHOW, EC_WORD_ME, EC_WORD_A, EC_WORD_REALLY, EC_WORD_SMOOTH, EC_WORD_MOVE},
        .speechWin = {EC_WORD_THERE, EC_WORD_WAS, EC_WORD_NOTHING, EC_WORD_SMOOTH, EC_WORD_ABOUT, EC_WORD_THAT},
        .speechLose = {EC_WORD_YOU, EC_WORD_REALLY, EC_WORD_ARE, EC_WORD_SMOOTH, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_NINJA_BOY_1}
    },
    [FRONTIER_TRAINER_DERRICK] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("דריק"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_SEE, EC_WORD_YOU, EC_MOVE2(MEDITATE), EC_WORD_LIKE, EC_WORD_ME},
        .speechWin = {EC_WORD_HOW, EC_WORD_I, EC_MOVE2(MEDITATE), EC_WORD_IS, EC_WORD_JUST, EC_WORD_BEAUTIFUL},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_MOVE2(MEDITATE), EC_WORD_FOR, EC_WORD_A, EC_MOVE2(CALM_MIND)},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_1}
    },
    [FRONTIER_TRAINER_BRYSON] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("ברייסון"),
        .speechBefore = {EC_MOVE2(POISON_POWDER), EC_WORD_IS, EC_WORD_IN, EC_WORD_OUR, EC_MOVE2(COTTON_SPORE), EC_WORD_MOVE},
        .speechWin = {EC_WORD_HOW_DO, EC_WORD_YOU, EC_WORD_LIKE, EC_WORD_OUR, EC_MOVE2(POISON_POWDER), EC_WORD_QUES},
        .speechLose = {EC_WORD_MY, EC_MOVE2(COTTON_SPORE), EC_WORD_WAS, EC_WORD_USELESS, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_1}
    },
    [FRONTIER_TRAINER_CLAYTON] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("קלייטון"),
        .speechBefore = {EC_WORD_HUH_QUES, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_WHERE, EC_WORD_IS_IT_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WHERE, EC_WORD_IS_IT_QUES, EC_WORD_I_VE, EC_WORD_LOST, EC_WORD_MY, EC_WORD_POKENAV},
        .speechLose = {EC_WORD_WHERE, EC_WORD_IS_IT_QUES, EC_WORD_I_VE, EC_WORD_LOST, EC_WORD_MY, EC_WORD_SENSE},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_1}
    },
    [FRONTIER_TRAINER_TRENTON] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("טרנטון"),
        .speechBefore = {EC_WORD_COME_OVER, EC_WORD_FOR, EC_WORD_SOME, EC_WORD_TASTY, EC_WORD_WATER, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MMM, EC_WORD_DO, EC_WORD_YOU, EC_WORD_WANT, EC_WORD_SOME, EC_WORD_QUES},
        .speechLose = {EC_WORD_I, EC_WORD_GOT, EC_WORD_THIS, EC_WORD_TASTY, EC_WORD_WATER, EC_WORD_SHOPPING},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_1}
    },
    [FRONTIER_TRAINER_JENSON] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("ג'נסון"),
        .speechBefore = {EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_WILL, EC_WORD_MAKE, EC_WORD_YOU, EC_WORD_DOWNCAST},
        .speechWin = {EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_DON_T, EC_WORD_MAKE, EC_WORD_THE, EC_MOVE(CUT)},
        .speechLose = {EC_WORD_I_AM, EC_WORD_THE, EC_WORD_TRAINER, EC_WORD_WHO_IS, EC_WORD_FEELING, EC_WORD_DOWNCAST},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_1}
    },
    [FRONTIER_TRAINER_WESLEY] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("ווסלי"),
        .speechBefore = {EC_POKEMON_NATIONAL(MEW), EC_POKEMON_NATIONAL(MEW), EC_WORD_IS, EC_WORD_HOW, EC_WORD_I, EC_WORD_CRY},
        .speechWin = {EC_WORD_YES, EC_WORD_I, EC_WORD_KNOW, EC_WORD_I_AM, EC_WORD_CUTE, EC_WORD_EXCL},
        .speechLose = {EC_POKEMON_NATIONAL(MEW), EC_POKEMON_NATIONAL(MEW), EC_WORD_EXCL, EC_POKEMON_NATIONAL(MEW), EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_1}
    },
    [FRONTIER_TRAINER_ANTON] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("אנטון"),
        .speechBefore = {EC_WORD_GET, EC_WORD_READY, EC_WORD_FOR, EC_WORD_ME, EC_WORD_TO, EC_MOVE(THRASH)},
        .speechWin = {EC_WORD_WAHAHAHA, EC_WORD_EXCL, EC_WORD_SORRY, EC_WORD_ABOUT, EC_WORD_THAT, EC_WORD_EXCL},
        .speechLose = {EC_WORD_IT_S, EC_WORD_A, EC_WORD_TOUGH, EC_WORD_LOSS, EC_WORD_TO, EC_MOVE2(SWALLOW)},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_1}
    },
    [FRONTIER_TRAINER_LAWSON] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("לוסון"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_YOUNG, EC_WORD_AT, EC_WORD_HEART, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_NOT, EC_WORD_COOL, EC_WORD_EXCL, EC_WORD_NOT, EC_WORD_AT, EC_WORD_ALL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_OLD, EC_WORD_AND, EC_WORD_FEELING, EC_WORD_SHAKY, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_1}
    },
    [FRONTIER_TRAINER_SAMMY] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("סמי"),
        .speechBefore = {EC_WORD_MY, EC_WORD_PARTY, EC_WORD_IS, EC_WORD_READY, EC_WORD_TO, EC_WORD_ROCK},
        .speechWin = {EC_WORD_MY, EC_WORD_PARTY, EC_WORD_IS, EC_WORD_JUST, EC_WORD_INCREDIBLE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_CRY, EC_WORD_FOR, EC_WORD_MY, EC_WORD_PARTY, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_1}
    },
    // The below 3 are the early Collector class trainers, which use groups from other general classes
    [FRONTIER_TRAINER_ARNIE] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("ארני"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NO_1, EC_WORD_I, EC_WORD_HAVE, EC_WORD_NO, EC_WORD_RIVAL},
        .speechWin = {EC_WORD_YOU, EC_WORD_SEE, EC_WORD_QUES, EC_WORD_I, EC_WORD_CAN_T, EC_WORD_LOSE},
        .speechLose = {EC_WORD_NO, EC_WORD_EXCL, EC_WORD_I, EC_WORD_WON_T, EC_WORD_ACCEPT, EC_WORD_THIS},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_ADRIAN] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("אדריאן"),
        .speechBefore = {EC_WORD_YAHOO, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_YAHOO, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THANK_YOU, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_THANK_YOU, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_GOOD_BYE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_GOOD_BYE, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_TRISTAN] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("טריסטן"),
        .speechBefore = {EC_WORD_CONFUSED, EC_WORD_QUES, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_A, EC_WORD_GENIUS},
        .speechWin = {EC_WORD_SEE, EC_WORD_QUES, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_A, EC_WORD_GENIUS},
        .speechLose = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_A, EC_WORD_GENIUS, EC_WORD_IN, EC_WORD_BATTLE},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_JULIANA] = {
        .facilityClass = FACILITY_CLASS_PARASOL_LADY,
        .trainerName = _("יוליאנה"),
        .speechBefore = {EC_WORD_I, EC_WORD_THINK, EC_WORD_I_AM, EC_WORD_SHOPPING, EC_WORD_TOO, EC_WORD_MUCH},
        .speechWin = {EC_WORD_BUT, EC_WORD_I, EC_WORD_WANT, EC_WORD_A, EC_WORD_POKEMON, EC_WORD_PLUSH_DOLL},
        .speechLose = {EC_WORD_I, EC_WORD_SO, EC_WORD_WANT, EC_WORD_ANOTHER, EC_WORD_POKEMON, EC_WORD_PLUSH_DOLL},
        .monSet = (const u16[]){FRONTIER_MONS_PARASOL_LADY_1}
    },
    [FRONTIER_TRAINER_RYLEE] = {
        .facilityClass = FACILITY_CLASS_PARASOL_LADY,
        .trainerName = _("ריילי"),
        .speechBefore = {EC_WORD_SHOW, EC_WORD_ME, EC_WORD_THAT, EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_GUTS},
        .speechWin = {EC_WORD_BYE_BYE, EC_WORD_EXCL, EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_NO, EC_WORD_GUTS},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_GUTSY, EC_WORD_ELLIPSIS, EC_WORD_YOU_RE, EC_WORD_QUITE, EC_WORD_SUPER},
        .monSet = (const u16[]){FRONTIER_MONS_PARASOL_LADY_1}
    },
    [FRONTIER_TRAINER_CHELSEA] = {
        .facilityClass = FACILITY_CLASS_PARASOL_LADY,
        .trainerName = _("צ'לסי"),
        .speechBefore = {EC_WORD_I, EC_WORD_SERIOUSLY, EC_WORD_MEAN, EC_WORD_TO, EC_WORD_WIN, EC_WORD_EXCL},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_MY, EC_WORD_WILL, EC_WORD_TO, EC_WORD_WIN, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_FAR, EC_WORD_TOO_STRONG, EC_WORD_FOR, EC_WORD_ME, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PARASOL_LADY_1}
    },
    // The below 3 are the early Beauty class trainers, which use groups from other general classes
    [FRONTIER_TRAINER_DANELA] = {
        .facilityClass = FACILITY_CLASS_BEAUTY,
        .trainerName = _("דנלה"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_MUST_BE, EC_WORD_MY, EC_WORD_OPPONENT, EC_WORD_NOW, EC_WORD_EXCL},
        .speechWin = {EC_WORD_OH_DEAR, EC_WORD_TOO_WEAK, EC_WORD_EXCL, EC_WORD_DON_T, EC_WORD_GIVE_UP, EC_WORD_EXCL},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_GOOD, EC_WORD_AND, EC_WORD_THIS, EC_WORD_IS, EC_WORD_GOOD_BYE},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_1}
    },
    [FRONTIER_TRAINER_LIZBETH] = {
        .facilityClass = FACILITY_CLASS_BEAUTY,
        .trainerName = _("ליזבת'"),
        .speechBefore = {EC_WORD_IF_I_LOSE, EC_WORD_YOU, EC_WORD_CAN, EC_WORD_HAVE, EC_WORD_A, EC_MOVE2(PRESENT)},
        .speechWin = {EC_WORD_HERE_IT_IS, EC_WORD_A_LITTLE, EC_WORD_PRAISE, EC_WORD_AS, EC_WORD_YOUR, EC_MOVE2(PRESENT)},
        .speechLose = {EC_WORD_YOUR, EC_MOVE2(PRESENT), EC_WORD_QUES_EXCL, EC_WORD_HERE_IT_IS, EC_WORD_A, EC_MOVE(DOUBLE_SLAP)},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_1}
    },
    [FRONTIER_TRAINER_AMELIA] = {
        .facilityClass = FACILITY_CLASS_BEAUTY,
        .trainerName = _("אמיליה"),
        .speechBefore = {EC_WORD_I, EC_WORD_BELIEVE, EC_WORD_IN, EC_WORD_CUTE, EC_WORD_FASHION, EC_WORD_APPEAL},
        .speechWin = {EC_WORD_YOUR, EC_WORD_FASHION, EC_WORD_SENSE, EC_WORD_IS, EC_WORD_A, EC_WORD_DISASTER},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_AWFUL, EC_WORD_EXCL, EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_HOME},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_1}
    },
    [FRONTIER_TRAINER_JILLIAN] = {
        .facilityClass = FACILITY_CLASS_AROMA_LADY,
        .trainerName = _("ג'יליאן"),
        .speechBefore = {EC_WORD_WHAT, EC_WORD_IS, EC_WORD_THAT, EC_WORD_I, EC_WORD_SMELL, EC_WORD_QUES},
        .speechWin = {EC_WORD_IT_S, EC_WORD_THE, EC_MOVE(SWEET_SCENT), EC_WORD_OF, EC_WORD_TASTY, EC_WORD_WATER},
        .speechLose = {EC_WORD_IT_S, EC_WORD_YOUR, EC_WORD_OFFENSIVE, EC_WORD_STENCH, EC_WORD_THAT_S, EC_WORD_WHAT},
        .monSet = (const u16[]){FRONTIER_MONS_AROMA_LADY_1}
    },
    [FRONTIER_TRAINER_ABBIE] = {
        .facilityClass = FACILITY_CLASS_AROMA_LADY,
        .trainerName = _("אבי"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_TRY, EC_WORD_MY, EC_WORD_SECRET, EC_MOVE(AROMATHERAPY), EC_WORD_OK_QUES},
        .speechWin = {EC_WORD_MY, EC_MOVE(AROMATHERAPY), EC_WORD_IS, EC_WORD_TERRIBLE, EC_WORD_FOR, EC_WORD_YOU},
        .speechLose = {EC_WORD_DIDN_T, EC_WORD_YOU, EC_WORD_SMELL, EC_WORD_A, EC_WORD_THING, EC_WORD_QUES_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_AROMA_LADY_1}
    },
    [FRONTIER_TRAINER_BRIANA] = {
        .facilityClass = FACILITY_CLASS_AROMA_LADY,
        .trainerName = _("בריאנה"),
        .speechBefore = {EC_WORD_MY, EC_WORD_BOY, EC_WORD_FRIEND, EC_WORD_WORKS, EC_WORD_TOO, EC_WORD_MUCH},
        .speechWin = {EC_WORD_I, EC_WORD_ONLY, EC_WORD_MISS, EC_WORD_HIM, EC_WORD_MORE, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_I_AM, EC_WORD_SO, EC_WORD_LONESOME, EC_WORD_WITHOUT, EC_WORD_HIM, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_AROMA_LADY_1}
    },
    [FRONTIER_TRAINER_ANTONIO] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("אנטוניו"),
        .speechBefore = {EC_WORD_I, EC_WORD_KNOW, EC_WORD_HOW, EC_WORD_TO, EC_WORD_GO, EC_WORD_GO},
        .speechWin = {EC_WORD_BUT, EC_WORD_I, EC_WORD_DON_T, EC_WORD_LIKE, EC_WORD_TO, EC_WORD_DANCE},
        .speechLose = {EC_WORD_GO, EC_WORD_GO, EC_WORD_ELLIPSIS, EC_WORD_JUST, EC_MOVE(FLAIL), EC_WORD_ABOUT},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_1}
    },
    [FRONTIER_TRAINER_JADEN] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("ג'יידן"),
        .speechBefore = {EC_WORD_HELLO, EC_WORD_I, EC_WORD_THINK, EC_WORD_I, EC_WORD_ADORE, EC_WORD_YOU},
        .speechWin = {EC_WORD_YOU, EC_WORD_MAKE, EC_WORD_ME, EC_MOVE(THRASH), EC_WORD_IN, EC_MOVE2(FRUSTRATION)},
        .speechLose = {EC_WORD_THIS_IS_IT_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_GOOD_BYE, EC_WORD_FOREVER, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_1}
    },
    [FRONTIER_TRAINER_DAKOTA] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("דקוטה"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_TO, EC_WORD_DANCE, EC_WORD_WITH, EC_WORD_POWER},
        .speechWin = {EC_WORD_GOT, EC_WORD_IT, EC_WORD_QUES, EC_WORD_DANCE, EC_WORD_WITH, EC_WORD_POWER},
        .speechLose = {EC_WORD_OKAY, EC_WORD_YOU, EC_WORD_UNDERSTAND, EC_WORD_ALL_RIGHT, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_1}
    },
    [FRONTIER_TRAINER_BRAYDEN] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("בריידן"),
        .speechBefore = {EC_WORD_COLOR_CHANGE, EC_WORD_VERSION, EC_WORD_TOYS, EC_WORD_ARE, EC_WORD_USELESS, EC_WORD_EXCL},
        .speechWin = {EC_WORD_I, EC_WORD_ONLY, EC_WORD_COLLECT, EC_WORD_NORMAL, EC_WORD_VERSION, EC_WORD_TOYS},
        .speechLose = {EC_WORD_I, EC_MOVE2(ATTRACT), EC_WORD_COLOR_CHANGE, EC_WORD_VERSION, EC_WORD_TOYS, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_1}
    },
    [FRONTIER_TRAINER_CORSON] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("קורסון"),
        .speechBefore = {EC_WORD_I, EC_WORD_GET, EC_WORD_TO, EC_MOVE2(BEAT_UP), EC_WORD_ON, EC_WORD_YOU},
        .speechWin = {EC_WORD_TOO, EC_WORD_EASY, EC_WORD_EXCL, EC_WORD_I_AM, EC_WORD_SO, EC_WORD_COOL},
        .speechLose = {EC_WORD_WHY, EC_WORD_QUES_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_MOVE2(CURSE), EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_1}
    },
    [FRONTIER_TRAINER_TREVIN] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("טרבין"),
        .speechBefore = {EC_WORD_THERE, EC_WORD_IS, EC_WORD_NONE, EC_WORD_BETTER, EC_WORD_THAN, EC_WORD_ME},
        .speechWin = {EC_WORD_YES_SIR_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_THE, EC_WORD_BEST},
        .speechLose = {EC_WORD_SERIOUS, EC_WORD_QUES_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_1}
    },
    [FRONTIER_TRAINER_PATRICK] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("פטריק"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_PERFECT, EC_WORD_EXCL, EC_WORD_GIVE_UP, EC_WORD_NOW, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_DON_T, EC_WORD_BE, EC_WORD_DISAPPOINTED, EC_WORD_I_AM, EC_WORD_PERFECT, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_BUT, EC_WORD_HOW, EC_WORD_QUES, EC_WORD_I_AM, EC_WORD_PERFECT, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_1}
    },
    [FRONTIER_TRAINER_KADEN] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("קיידן"),
        .speechBefore = {EC_WORD_WHAT, EC_WORD_ARE, EC_WORD_YOU, EC_WORD_UP, EC_WORD_TO, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_WERE, EC_WORD_A, EC_WORD_SURPRISE, EC_WORD_TO_ME, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_KNOW, EC_WORD_WHO, EC_WORD_I_AM, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_1}
    },
    [FRONTIER_TRAINER_MAXWELL] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("מקסוול"),
        .speechBefore = {EC_WORD_HEY_THERE, EC_WORD_WHO_IS, EC_WORD_YOUR, EC_WORD_RIVAL, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MY, EC_WORD_RIVAL, EC_WORD_IS, EC_WORD_MY, EC_WORD_GIRL, EC_WORD_FRIEND},
        .speechLose = {EC_WORD_I_AM, EC_WORD_MAKING, EC_WORD_YOU, EC_WORD_MY, EC_WORD_RIVAL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_1}
    },
    [FRONTIER_TRAINER_DARYL] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("דריל"),
        .speechBefore = {EC_WORD_I, EC_WORD_ONLY, EC_WORD_KNOW, EC_WORD_HOW, EC_WORD_TO, EC_MOVE(CHARGE)},
        .speechWin = {EC_WORD_AM, EC_WORD_I, EC_WORD_OVERWHELMING, EC_WORD_OR, EC_WORD_WHAT, EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_GOING, EC_WORD_TO, EC_WORD_A, EC_WORD_LEGEND, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_1}
    },
    [FRONTIER_TRAINER_KENNETH] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("קנת'"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_BETTER, EC_WORD_NOT, EC_MOVE2(SLACK_OFF), EC_WORD_WITH, EC_WORD_ME},
        .speechWin = {EC_WORD_DID, EC_WORD_MY, EC_MOVE2(TAUNT), EC_WORD_INTIMIDATE, EC_WORD_YOU, EC_WORD_QUES},
        .speechLose = {EC_WORD_I_AM, EC_WORD_SORRY, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_1}
    },
    [FRONTIER_TRAINER_RICH] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("ריץ'"),
        .speechBefore = {EC_WORD_YOUR, EC_MOVE(FACADE), EC_WORD_DOESN_T, EC_MOVE2(TRICK), EC_WORD_ME, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_SERIOUSLY, EC_WORD_ARE, EC_WORD_YOU, EC_WORD_REALLY, EC_WORD_OK_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_REALLY, EC_WORD_TOUGH, EC_WORD_ON, EC_WORD_ME, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_1}
    },
    [FRONTIER_TRAINER_CADEN] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("קיידן"),
        .speechBefore = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_BE, EC_WORD_DEFEATED, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_FIRE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_FIRE, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I_AM, EC_WORD_TIRED, EC_WORD_ELLIPSIS, EC_WORD_IT_S, EC_WORD_SO, EC_WORD_HOT},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_1}
    },
    [FRONTIER_TRAINER_MARLON] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("מרלון"),
        .speechBefore = {EC_WORD_A, EC_WORD_POKEDEX, EC_WORD_IS, EC_WORD_A_LITTLE, EC_WORD_RADIO, EC_WORD_QUES},
        .speechWin = {EC_WORD_A_LITTLE, EC_WORD_RADIO, EC_WORD_HUH_QUES, EC_WORD_THAT_S, EC_WORD_TOTALLY, EC_WORD_COOL},
        .speechLose = {EC_WORD_IT_S, EC_WORD_NOT, EC_WORD_QUES, EC_WORD_IS, EC_WORD_POKENAV, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_1}
    },
    [FRONTIER_TRAINER_NASH] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("נאש"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_ON, EC_WORD_FIRE, EC_WORD_BABY, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_LEFT, EC_WORD_YOU, EC_WORD_JUST, EC_WORD_AN, EC_MOVE2(EMBER)},
        .speechLose = {EC_WORD_AIYEEH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_NO, EC_WORD_WATER, EC_WORD_PLEASE},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_1}
    },
    [FRONTIER_TRAINER_ROBBY] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_M,
        .trainerName = _("רובי"),
        .speechBefore = {EC_WORD_HAHAHA, EC_WORD_EXCL, EC_WORD_HAPPY, EC_WORD_TO, EC_WORD_MEET_YOU, EC_WORD_EXCL},
        .speechWin = {EC_WORD_I_AM, EC_WORD_THE, EC_WORD_LEADER, EC_WORD_WITH, EC_WORD_REFRESHING, EC_WORD_SERENE_GRACE},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_MOVE(THRASH), EC_WORD_MY, EC_WORD_TOYS, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_RUNNING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_REECE] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_M,
        .trainerName = _("ריס"),
        .speechBefore = {EC_WORD_MY, EC_MOVE2(QUICK_ATTACK), EC_WORD_CAN, EC_WORD_BEAT, EC_WORD_A, EC_MOVE2(TELEPORT)},
        .speechWin = {EC_WORD_LIKE, EC_WORD_I, EC_WORD_SAID, EC_WORD_I_AM, EC_WORD_DARN, EC_WORD_FAST},
        .speechLose = {EC_WORD_I_WAS, EC_WORD_KIDDING, EC_WORD_ABOUT, EC_WORD_THAT, EC_MOVE2(TELEPORT), EC_WORD_THING},
        .monSet = (const u16[]){FRONTIER_MONS_RUNNING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_KATHRYN] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_F,
        .trainerName = _("קתרין"),
        .speechBefore = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_TRAIN, EC_WORD_GOOD, EC_WORD_ENOUGH, EC_WORD_QUES},
        .speechWin = {EC_WORD_DON_T, EC_MOVE2(TAUNT), EC_WORD_ME, EC_WORD_LIKE, EC_WORD_THAT, EC_WORD_OK_QUES},
        .speechLose = {EC_WORD_WHY, EC_WORD_COULDN_T, EC_WORD_I, EC_WORD_WIN, EC_WORD_THIS, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_RUNNING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_ELLEN] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_F,
        .trainerName = _("אלן"),
        .speechBefore = {EC_WORD_CRUSH, EC_WORD_YOU, EC_WORD_LIKE, EC_WORD_AN, EC_WORD_EGG, EC_WORD_EXCL},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_A, EC_WORD_TASTY, EC_WORD_VICTORY, EC_WORD_FOR, EC_WORD_ME},
        .speechLose = {EC_WORD_TOO, EC_WORD_TOUGH, EC_WORD_TO, EC_WORD_CRUSH, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_RUNNING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_RAMON] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
        .trainerName = _("רמון"),
        .speechBefore = {EC_WORD_OKAY, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_THIS, EC_WORD_IS, EC_WORD_PERFECTION},
        .speechWin = {EC_WORD_I_AM, EC_WORD_HAPPY, EC_WORD_THAT, EC_WORD_I, EC_WORD_WON, EC_WORD_EXCL},
        .speechLose = {EC_WORD_IT_S, EC_WORD_A, EC_WORD_SECRET, EC_WORD_WHY, EC_WORD_I_AM, EC_WORD_HAPPY},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_ARTHUR] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
        .trainerName = _("ארתור"),
        .speechBefore = {EC_WORD_HERE_I_COME, EC_WORD_FEELING, EC_WORD_READY, EC_WORD_FOR, EC_WORD_IT, EC_WORD_ALL},
        .speechWin = {EC_WORD_THAT_S_IT_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_THAT_WAS, EC_WORD_FABULOUS, EC_WORD_EXCL},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_NOT, EC_WORD_WHAT, EC_WORD_I, EC_WORD_NEED, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_ALONDRA] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
        .trainerName = _("אלונדרה"),
        .speechBefore = {EC_WORD_EVERY, EC_WORD_DAY, EC_WORD_IS, EC_WORD_A, EC_WORD_GREAT, EC_WORD_DAY},
        .speechWin = {EC_WORD_MY, EC_MOVE2(DIVE), EC_WORD_WILL, EC_WORD_BE, EC_WORD_A, EC_WORD_LEGEND},
        .speechLose = {EC_WORD_MY, EC_MOVE2(DIVE), EC_WORD_LEFT, EC_WORD_ME, EC_WORD_COLD, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_ADRIANA] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
        .trainerName = _("אדריאנה"),
        .speechBefore = {EC_WORD_COME, EC_WORD_SEE, EC_WORD_AN, EC_WORD_INCREDIBLE, EC_WORD_SWIFT_SWIM, EC_WORD_EXCL},
        .speechWin = {EC_WORD_I, EC_WORD_MAKE, EC_WORD_IT, EC_WORD_LOOK, EC_WORD_SO, EC_WORD_EASY},
        .speechLose = {EC_WORD_I_AM, EC_WORD_FEELING, EC_MOVE2(BEAT_UP), EC_WORD_AND, EC_WORD_TIRED, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_MALIK] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_M,
        .trainerName = _("מאליק"),
        .speechBefore = {EC_WORD_OH, EC_WORD_NOT, EC_WORD_ANOTHER, EC_WORD_BATTLE, EC_WORD_PLEASE, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_I, EC_WORD_FINALLY, EC_WORD_WON, EC_WORD_ELLIPSIS, EC_WORD_I_AM, EC_WORD_TIRED},
        .speechLose = {EC_WORD_I, EC_WORD_FINALLY, EC_WORD_LOST, EC_WORD_ELLIPSIS, EC_WORD_I_AM, EC_WORD_TIRED},
        .monSet = (const u16[]){FRONTIER_MONS_CYCLING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_JILL] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_F,
        .trainerName = _("ג'יל"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_THE, EC_MOVE2(QUICK_ATTACK), EC_WORD_TRAINER, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THE, EC_MOVE2(QUICK_ATTACK), EC_WORD_TRAINER, EC_WORD_WINS, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_THE, EC_MOVE2(QUICK_ATTACK), EC_WORD_TRAINER, EC_WORD_GIVES, EC_WORD_UP, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_CYCLING_TRIATHLETE_1}
    },
    [FRONTIER_TRAINER_ERIK] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_M,
        .trainerName = _("אריק"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_THE, EC_WORD_SPEED_BOOST, EC_WORD_HERO, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THANK_YOU, EC_WORD_FROM, EC_WORD_THE, EC_WORD_SPEED_BOOST, EC_WORD_HERO, EC_WORD_EXCL},
        .speechLose = {EC_WORD_WAAAH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_NO, EC_WORD_NO, EC_WORD_EXCL_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_RUNNING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_YAZMIN] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_F,
        .trainerName = _("יסמין"),
        .speechBefore = {EC_WORD_I, EC_WORD_WOULD, EC_WORD_RATHER, EC_WORD_RUN, EC_WORD_THAN, EC_WORD_BIKE},
        .speechWin = {EC_WORD_YES, EC_WORD_I, EC_WORD_WOULD, EC_WORD_MUCH, EC_WORD_RATHER, EC_WORD_RUN},
        .speechLose = {EC_WORD_BYE_BYE, EC_WORD_EXCL, EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_TO, EC_WORD_RUN_AWAY},
        .monSet = (const u16[]){FRONTIER_MONS_RUNNING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_JAMAL] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
        .trainerName = _("ג'מאל"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_TO, EC_WORD_BE, EC_WORD_A, EC_WORD_FATHER},
        .speechWin = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_WAIT, EC_WORD_FOR, EC_WORD_MY, EC_WORD_BABY},
        .speechLose = {EC_WORD_MY, EC_WORD_BABY, EC_WORD_WILL, EC_WORD_BE, EC_WORD_TOTALLY, EC_WORD_AWESOME},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_LESLIE] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
        .trainerName = _("לסלי"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_TO, EC_WORD_BE, EC_WORD_A, EC_WORD_MOTHER},
        .speechWin = {EC_WORD_A, EC_WORD_BABY, EC_WORD_WILL, EC_WORD_BE, EC_WORD_A_LITTLE, EC_WORD_CHALLENGE},
        .speechLose = {EC_WORD_I_AM, EC_WORD_TOO, EC_WORD_HAPPY, EC_WORD_TO, EC_WORD_BE, EC_WORD_ANGRY},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_DAVE] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_M,
        .trainerName = _("דייב"),
        .speechBefore = {EC_WORD_WHAT, EC_WORD_SHOULD, EC_WORD_I, EC_WORD_DO, EC_WORD_TODAY, EC_WORD_QUES},
        .speechWin = {EC_WORD_I, EC_WORD_SHOULD, EC_WORD_ENJOY, EC_WORD_SOME, EC_WORD_SPORTS, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_WORD_GO, EC_WORD_PLAY, EC_WORD_A, EC_WORD_GAME},
        .monSet = (const u16[]){FRONTIER_MONS_CYCLING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_CARLO] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_M,
        .trainerName = _("קרלו"),
        .speechBefore = {EC_WORD_HAH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_YEAH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_DO, EC_WORD_THINGS, EC_WORD_AT, EC_MOVE(EXTREME_SPEED), EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_LOST, EC_WORD_AT, EC_MOVE(EXTREME_SPEED), EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_CYCLING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_EMILIA] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_F,
        .trainerName = _("אמיליה"),
        .speechBefore = {EC_WORD_ME, EC_WORD_WORRY, EC_WORD_QUES, EC_WORD_I, EC_WORD_HAVE, EC_WORD_NONE},
        .speechWin = {EC_WORD_AHAHA, EC_WORD_SEE, EC_WORD_QUES, EC_WORD_THAT_WAS, EC_WORD_FANTASTIC, EC_WORD_EXCL},
        .speechLose = {EC_WORD_AHAHA, EC_WORD_SEE, EC_WORD_QUES, EC_WORD_THAT_WAS, EC_WORD_ENTERTAINING, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_CYCLING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_DALIA] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_F,
        .trainerName = _("דליה"),
        .speechBefore = {EC_WORD_MY, EC_WORD_BIKE, EC_WORD_IS, EC_WORD_VERY, EC_WORD_EXPENSIVE, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_DON_T, EC_WORD_COME, EC_WORD_NEAR, EC_WORD_MY, EC_WORD_BIKE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_MY, EC_WORD_BIKE, EC_WORD_IS, EC_WORD_MY, EC_WORD_BEST, EC_WORD_FRIEND},
        .monSet = (const u16[]){FRONTIER_MONS_CYCLING_TRIATHLETE_2}
    },
    [FRONTIER_TRAINER_HITOMI] = {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("היטומי"),
        .speechBefore = {EC_WORD_YEAH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_HAH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WHAT, EC_WORD_QUES_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_WON, EC_WORD_QUES_EXCL},
        .speechLose = {EC_WORD_AIYEEH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_SORRY, EC_WORD_EXCL_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_1}
    },
    [FRONTIER_TRAINER_RICARDO] = {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("ריקרדו"),
        .speechBefore = {EC_WORD_COME_ON, EC_WORD_EXCL, EC_WORD_PLAY, EC_WORD_TIME, EC_WORD_IS, EC_WORD_OVER},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_OUT, EC_WORD_OF, EC_WORD_HERE, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_DON_T, EC_WORD_HIT, EC_WORD_ME, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_1}
    },
    [FRONTIER_TRAINER_SHIZUKA] = {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("שיזוקה"),
        .speechBefore = {EC_WORD_SHOW, EC_WORD_ME, EC_WORD_THAT, EC_WORD_YOU_RE, EC_WORD_SERIOUS, EC_WORD_EXCL},
        .speechWin = {EC_WORD_I, EC_WORD_WON_T, EC_WORD_FORGET, EC_WORD_ABOUT, EC_WORD_YOU, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_PERFECT, EC_WORD_IN, EC_WORD_EVERY, EC_WORD_WAY, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_1}
    },
    [FRONTIER_TRAINER_JOANA] = {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("ג'ואנה"),
        .speechBefore = {EC_WORD_YOU_RE, EC_WORD_GOING, EC_WORD_TO, EC_WORD_LOSE, EC_WORD_RIGHT, EC_WORD_AWAY},
        .speechWin = {EC_WORD_I_AM, EC_WORD_THE, EC_WORD_WINNER, EC_WORD_HEAR, EC_WORD_ME, EC_MOVE2(ROAR)},
        .speechLose = {EC_WORD_I, EC_WORD_REFUSE, EC_WORD_TO, EC_WORD_ACCEPT, EC_WORD_THAT, EC_MOVE(OUTRAGE)},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_1}
    },
    [FRONTIER_TRAINER_KELLY] = {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("קלי"),
        .speechBefore = {EC_WORD_MY, EC_WORD_NIGHT, EC_WORD_SCHOOL, EC_WORD_IS, EC_WORD_REALLY, EC_WORD_SCARY},
        .speechWin = {EC_WORD_A, EC_WORD_LADY, EC_WORD_GHOST, EC_WORD_APPEARS, EC_WORD_THERE, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_THE, EC_WORD_HOME, EC_WORD_WORK, EC_WORD_IS, EC_WORD_AWFULLY, EC_WORD_SCARY},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_1}
    },
    [FRONTIER_TRAINER_RAYNA] = {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("ריינה"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NO_1, EC_WORD_WHEN, EC_WORD_IT_S, EC_WORD_ABOUT, EC_WORD_POWER},
        .speechWin = {EC_WORD_UNDERSTAND, EC_WORD_MY, EC_WORD_POWER, EC_WORD_NOW, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_TERRIBLE, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_TERRIBLE, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_1}
    },
    [FRONTIER_TRAINER_EVAN] = {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("אוון"),
        .speechBefore = {EC_WORD_EVERY, EC_WORD_BATTLE, EC_WORD_HAS, EC_WORD_A, EC_WORD_SMELL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_OH, EC_WORD_EXCL, EC_WORD_THE, EC_MOVE(SWEET_SCENT), EC_WORD_OF, EC_WORD_VICTORY},
        .speechLose = {EC_WORD_THE, EC_WORD_AWFUL, EC_WORD_STENCH, EC_WORD_OF, EC_WORD_A, EC_WORD_LOSS},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_1A}
    },
    [FRONTIER_TRAINER_JORDAN] = {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("ירדן"),
        .speechBefore = {EC_WORD_GOOD, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_COME_ON, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_YOU, EC_WORD_CAN_T, EC_WORD_BEAT, EC_WORD_ME, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WHAT, EC_WORD_QUES_EXCL, EC_EMPTY_WORD, EC_WORD_BUT, EC_WORD_HOW, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_1B}
    },
    [FRONTIER_TRAINER_JOEL] = {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("יואל"),
        .speechBefore = {EC_WORD_FUFUFU, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_GIGGLE, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_HAHAHA, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_1C}
    },
    [FRONTIER_TRAINER_KRISTEN] = {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("קריסטן"),
        .speechBefore = {EC_WORD_HAHAHA, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_WORD_A, EC_WORD_KID, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_JUST, EC_WORD_A_LITTLE, EC_WORD_KID, EC_WORD_AFTER, EC_WORD_ALL, EC_WORD_EXCL},
        .speechLose = {EC_WORD_A, EC_WORD_TOUGH, EC_WORD_KID, EC_WORD_HUH_QUES, EC_WORD_HUMPH, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_1A}
    },
    [FRONTIER_TRAINER_SELPHY] = {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("סלפי"),
        .speechBefore = {EC_WORD_HUH_QUES, EC_WORD_WHAT, EC_WORD_IS_IT_QUES, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_OH, EC_WORD_YES, EC_WORD_EXCL, EC_WORD_WHY, EC_WORD_NOT, EC_WORD_QUES},
        .speechLose = {EC_WORD_OH, EC_WORD_NO, EC_WORD_EXCL, EC_WORD_WHY, EC_WORD_NOT, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_1B}
    },
    [FRONTIER_TRAINER_CHLOE] = {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("קלואי"),
        .speechBefore = {EC_WORD_COME, EC_WORD_WE, EC_WORD_WILL, EC_WORD_DO, EC_WORD_BATTLE, EC_WORD_NOW},
        .speechWin = {EC_WORD_MORE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_ANOTHER, EC_WORD_BATTLE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_OH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_STRONG, EC_WORD_YOU, EC_WORD_ARE},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_1C}
    },
    [FRONTIER_TRAINER_NORTON] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("נורטון"),
        .speechBefore = {EC_WORD_I, EC_WORD_KNOW, EC_WORD_ONLY, EC_WORD_YOU, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_EXCUSE_ME, EC_WORD_BUT, EC_WORD_YOU_RE, EC_WORD_A, EC_WORD_PUSHOVER, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_SOME, EC_WORD_KIND, EC_WORD_OF, EC_WORD_AWESOME, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_1}
    },
    [FRONTIER_TRAINER_LUKAS] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("לוקאס"),
        .speechBefore = {EC_WORD_MY, EC_WORD_JOKING, EC_WORD_IS, EC_WORD_PRETTY, EC_WORD_TERRIBLE, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_YOUR, EC_WORD_ROCK_HEAD, EC_WORD_EXISTS, EC_WORD_TO, EC_WORD_SHINE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOUR, EC_WORD_ROCK_HEAD, EC_WORD_COME, EC_WORD_TO, EC_WORD_SHINE, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_1}
    },
    [FRONTIER_TRAINER_ZACH] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("זאק"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_AN, EC_WORD_EXCELLENT, EC_MOVE2(MIMIC), EC_WORD_OF, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_I_AM, EC_WORD_HAPPY, EC_WORD_LIKE, EC_WORD_A_LITTLE, EC_POKEMON_NATIONAL(TOGEPI), EC_WORD_EXCL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_ANGRY, EC_WORD_LIKE, EC_WORD_A, EC_POKEMON_NATIONAL(MANKEY), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_1}
    },
    [FRONTIER_TRAINER_KAITLYN] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("קייטלין"),
        .speechBefore = {EC_WORD_I, EC_WORD_CRUSH, EC_WORD_THINGS, EC_WORD_WITH, EC_WORD_PSYCHIC, EC_WORD_POWER},
        .speechWin = {EC_WORD_MY, EC_WORD_VICTORY, EC_WORD_WILL, EC_WORD_MAKE, EC_WORD_THE, EC_WORD_NEWS},
        .speechLose = {EC_WORD_NO, EC_WORD_NO, EC_WORD_ELLIPSIS, EC_WORD_THIS, EC_WORD_WON_T, EC_WORD_DO},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_1}
    },
    [FRONTIER_TRAINER_BREANNA] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("בריאנה"),
        .speechBefore = {EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_WILL, EC_WORD_CRUSH, EC_WORD_YOU, EC_WORD_EXCL},
        .speechWin = {EC_WORD_HAVE, EC_WORD_SOME, EC_WORD_MORE, EC_WORD_OF, EC_WORD_THIS, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_GUTS, EC_WORD_AND, EC_WORD_SKILL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_1}
    },
    [FRONTIER_TRAINER_KENDRA] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("קנדרה"),
        .speechBefore = {EC_WORD_IF, EC_WORD_YOU_RE, EC_WORD_SMART, EC_WORD_STOP, EC_WORD_RIGHT, EC_WORD_NOW},
        .speechWin = {EC_WORD_I, EC_WORD_SAID, EC_WORD_THAT, EC_WORD_YOU, EC_WORD_SHOULD, EC_WORD_STOP},
        .speechLose = {EC_WORD_WHY, EC_WORD_DIDN_T, EC_WORD_YOU, EC_WORD_STOP, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_1}
    },
    [FRONTIER_TRAINER_MOLLY] = {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("מולי"),
        .speechBefore = {EC_WORD_WILL, EC_WORD_MY, EC_WORD_CUTE_CHARM, EC_MOVE2(ATTRACT), EC_WORD_YOU, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_MY, EC_WORD_TOYS, EC_WORD_NOW},
        .speechLose = {EC_WORD_OH, EC_WORD_HOW, EC_WORD_COULD, EC_WORD_YOU, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_HEX_MANIAC_1}
    },
    [FRONTIER_TRAINER_JAZMIN] = {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("ג'זמין"),
        .speechBefore = {EC_WORD_I, EC_WORD_FORECAST, EC_WORD_TERRIBLE, EC_WORD_THINGS, EC_WORD_FOR, EC_WORD_YOU},
        .speechWin = {EC_WORD_THERE, EC_WORD_WASN_T, EC_WORD_MY, EC_WORD_FORECAST, EC_WORD_RIGHT, EC_WORD_QUES},
        .speechLose = {EC_WORD_MY, EC_MOVE2(FORESIGHT), EC_WORD_DIDN_T, EC_WORD_SHOW, EC_WORD_ME, EC_WORD_THIS},
        .monSet = (const u16[]){FRONTIER_MONS_HEX_MANIAC_1}
    },
    [FRONTIER_TRAINER_KELSEY] = {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("קלסי"),
        .speechBefore = {EC_WORD_I, EC_WORD_HAVEN_T, EC_WORD_SLEPT, EC_WORD_IN, EC_WORD_DAYS, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_MY, EC_WORD_SLEEP, EC_WORD_WILL, EC_WORD_BE, EC_WORD_EXCELLENT, EC_WORD_NOW},
        .speechLose = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_DESTROYED, EC_WORD_MY, EC_WORD_SLEEP, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_HEX_MANIAC_1}
    },
    [FRONTIER_TRAINER_JALEN] = {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("ג'יילן"),
        .speechBefore = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_ALLOW, EC_WORD_POKEMON, EC_WORD_TO, EC_MOVE(THRASH)},
        .speechWin = {EC_WORD_HAHAHA, EC_WORD_EXCL, EC_WORD_ARE, EC_WORD_YOU, EC_WORD_ANGRY, EC_WORD_QUES},
        .speechLose = {EC_WORD_WHY, EC_WORD_IS, EC_WORD_THIS, EC_WORD_SO, EC_WORD_HARD, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_POKEMANIAC_1}
    },
    [FRONTIER_TRAINER_GRIFFEN] = {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("גריפין"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(SWALLOW), EC_MOVE2(SLUDGE), EC_WORD_TO, EC_MOVE2(TRANSFORM), EC_WORD_MYSELF},
        .speechWin = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_A, EC_MOVE(GROWTH), EC_WORD_OF, EC_MOVE2(ACID_ARMOR)},
        .speechLose = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_A, EC_MOVE(GROWTH), EC_WORD_OF, EC_WORD_SUCTION_CUPS},
        .monSet = (const u16[]){FRONTIER_MONS_POKEMANIAC_1}
    },
    [FRONTIER_TRAINER_XANDER] = {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("קסנדר"),
        .speechBefore = {EC_WORD_I, EC_WORD_GOT, EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_ON, EC_WORD_RENTAL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_INCREDIBLE, EC_WORD_MY, EC_WORD_RENTAL, EC_WORD_POKEMON, EC_WORD_WON},
        .speechLose = {EC_WORD_RENTAL, EC_WORD_POKEMON, EC_WORD_AREN_T, EC_WORD_UP, EC_WORD_TO, EC_MOVE2(SCRATCH)},
        .monSet = (const u16[]){FRONTIER_MONS_POKEMANIAC_1}
    },
    [FRONTIER_TRAINER_MARVIN] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("מרווין"),
        .speechBefore = {EC_WORD_YOU_RE, EC_WORD_UP, EC_WORD_TO, EC_WORD_THE, EC_WORD_CHALLENGE, EC_WORD_QUES},
        .speechWin = {EC_WORD_I, EC_WORD_DIDN_T, EC_WORD_THINK, EC_WORD_YOU_RE, EC_WORD_GOOD, EC_WORD_ENOUGH},
        .speechLose = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_PERFECT, EC_WORD_THANK_YOU, EC_WORD_SO, EC_WORD_MUCH},
        .monSet = (const u16[]){FRONTIER_MONS_GENTLEMAN_1A}
    },
    [FRONTIER_TRAINER_BRENNAN] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("ברנן"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(WISH), EC_WORD_TO, EC_WORD_SEE, EC_WORD_THE, EC_WORD_NEWS},
        .speechWin = {EC_WORD_COMICS, EC_WORD_GET, EC_WORD_DAMP, EC_WORD_FROM, EC_WORD_DRIZZLE, EC_WORD_QUES},
        .speechLose = {EC_WORD_THE, EC_WORD_TIGHT, EC_WORD_MONEY, EC_WORD_LIVING, EC_WORD_CHANNEL, EC_WORD_QUES_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_GENTLEMAN_1B}
    },
    [FRONTIER_TRAINER_BALEY] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("ביילי"),
        .speechBefore = {EC_MOVE(SCREECH), EC_WORD_IS, EC_WORD_LIKE, EC_WORD_MUSIC, EC_WORD_TO_ME, EC_WORD_EXCL},
        .speechWin = {EC_WORD_MY, EC_MOVE(SCREECH), EC_WORD_STRATEGY, EC_WORD_IS, EC_WORD_THE, EC_WORD_BEST},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_SOUNDPROOF, EC_WORD_QUES, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_2}
    },
    [FRONTIER_TRAINER_ZACKARY] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("זאקרי"),
        .speechBefore = {EC_WORD_CAN, EC_WORD_YOU, EC_MOVE(DIG), EC_WORD_IT, EC_WORD_YO, EC_WORD_QUES},
        .speechWin = {EC_MOVE2(TAKE_DOWN), EC_WORD_TAKE, EC_WORD_A, EC_MOVE2(DIVE), EC_WORD_YO, EC_WORD_YO},
        .speechLose = {EC_WORD_BREAK, EC_WORD_DOWN, EC_MOVE2(DIVE), EC_WORD_TIME, EC_WORD_FOR, EC_WORD_ME},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_2}
    },
    [FRONTIER_TRAINER_GABRIEL] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("גבריאל"),
        .speechBefore = {EC_MOVE2(POUND), EC_WORD_THE, EC_WORD_THICK_FAT, EC_WORD_ON, EC_WORD_MY, EC_MOVE2(BELLY_DRUM)},
        .speechWin = {EC_MOVE2(POUND), EC_WORD_MY, EC_MOVE2(BELLY_DRUM), EC_MOVE2(POUND), EC_WORD_MY, EC_MOVE2(BELLY_DRUM)},
        .speechLose = {EC_WORD_MY, EC_MOVE2(BELLY_DRUM), EC_WORD_WAS, EC_WORD_TOO_WEAK, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_COLLECTOR_1}
    },
    [FRONTIER_TRAINER_EMILY] = {
        .facilityClass = FACILITY_CLASS_PARASOL_LADY,
        .trainerName = _("אמילי"),
        .speechBefore = {EC_WORD_HOW, EC_WORD_ABOUT, EC_WORD_A_TINY_BIT, EC_WORD_OF, EC_MOVE(HYPNOSIS), EC_WORD_QUES},
        .speechWin = {EC_WORD_MY, EC_MOVE(HYPNOSIS), EC_WORD_STRATEGY, EC_WORD_WORKS, EC_WORD_TO, EC_WORD_PERFECTION},
        .speechLose = {EC_WORD_MY, EC_MOVE(HYPNOSIS), EC_WORD_STRATEGY, EC_WORD_WENT, EC_WORD_BADLY, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_PARASOL_LADY_2}
    },
    [FRONTIER_TRAINER_JORDYN] = {
        .facilityClass = FACILITY_CLASS_BEAUTY,
        .trainerName = _("ג'ורדין"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_DON_T, EC_WORD_KNOW, EC_WORD_MY, EC_WORD_SECRET, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_AS, EC_WORD_I, EC_WORD_APPEAR, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_BUT, EC_WORD_HOW, EC_WORD_DID, EC_WORD_YOU, EC_WORD_KNOW, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_BEAUTY_1}
    },
    [FRONTIER_TRAINER_SOFIA] = {
        .facilityClass = FACILITY_CLASS_AROMA_LADY,
        .trainerName = _("סופיה"),
        .speechBefore = {EC_POKEMON(LOUDRED), EC_WORD_PROBABLY, EC_WORD_HAS, EC_WORD_A, EC_MOVE(SWEET_SCENT), EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THAT_S, EC_WORD_THE, EC_WORD_FEELING, EC_WORD_THAT, EC_WORD_I, EC_WORD_GET},
        .speechLose = {EC_WORD_I, EC_WORD_WORK, EC_WORD_AT, EC_WORD_THE, EC_WORD_DEPT_STORE, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_AROMA_LADY_2}
    },
    [FRONTIER_TRAINER_BRADEN] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("בריידן"),
        .speechBefore = {EC_WORD_I_CHOOSE_YOU, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_THIS_IS_IT_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_PRETTY, EC_WORD_AWESOME, EC_WORD_ABOUT, EC_WORD_MYSELF},
        .speechLose = {EC_WORD_ALL_RIGHT, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_SURRENDER, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_1A}
    },
    [FRONTIER_TRAINER_KAYDEN] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("קיידן"),
        .speechBefore = {EC_WORD_THEY, EC_WORD_OVERDO, EC_WORD_THAT, EC_WORD_GOURMET, EC_WORD_THING, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_THAT, EC_WORD_GOURMET, EC_WORD_THING, EC_WORD_ISN_T, EC_WORD_FOR, EC_WORD_ME},
        .speechLose = {EC_WORD_HEY, EC_WORD_THIS, EC_WORD_IS, EC_WORD_PRETTY, EC_WORD_TASTY, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_1B}
    },
    [FRONTIER_TRAINER_COOPER] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("קופר"),
        .speechBefore = {EC_WORD_THIS, EC_WORD_SHOULD, EC_WORD_ABSOLUTELY, EC_WORD_BE, EC_WORD_A, EC_WORD_PUSHOVER},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_TOO, EC_WORD_EXCITING, EC_WORD_FOR, EC_WORD_ME, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_SORRY, EC_WORD_I_AM, EC_WORD_SORRY},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_1C}
    },
    [FRONTIER_TRAINER_JULIA] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("יוליה"),
        .speechBefore = {EC_WORD_SPIRIT, EC_WORD_ALONE, EC_WORD_WON_T, EC_WORD_MAKE, EC_WORD_YOU, EC_WORD_WIN},
        .speechWin = {EC_WORD_YOU, EC_WORD_SHOULD, EC_WORD_ACCEPT, EC_WORD_THIS, EC_WORD_WITH, EC_WORD_SERENE_GRACE},
        .speechLose = {EC_WORD_FOR_NOW, EC_WORD_GOOD_BYE, EC_WORD_BUT, EC_WORD_IT_S, EC_WORD_NOT, EC_WORD_OVER},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_1A}
    },
    [FRONTIER_TRAINER_AMARA] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("אמרה"),
        .speechBefore = {EC_WORD_WROOOAAR_EXCL, EC_WORD_EXCL_EXCL, EC_WORD_I_AM, EC_WORD_SO, EC_WORD_READY, EC_WORD_EXCL_EXCL},
        .speechWin = {EC_WORD_I, EC_WORD_LOSE, EC_WORD_MYSELF, EC_WORD_IF, EC_WORD_IT_S, EC_WORD_EXCITING},
        .speechLose = {EC_WORD_THAT_S, EC_WORD_TOO, EC_WORD_MUCH, EC_WORD_TO, EC_MOVE2(TACKLE), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_1B}
    },
    [FRONTIER_TRAINER_LYNN] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("לין"),
        .speechBefore = {EC_WORD_YOUR, EC_WORD_SECRET, EC_WORD_CAN_T, EC_WORD_BE, EC_WORD_HIDDEN, EC_WORD_FOREVER},
        .speechWin = {EC_WORD_I, EC_WORD_KNOW, EC_WORD_YOUR, EC_WORD_SECRET, EC_WORD_NOW, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU, EC_WORD_CAN_T, EC_MOVE(SAFEGUARD), EC_WORD_YOUR, EC_WORD_OWN, EC_WORD_SECRET},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_1C}
    },
    [FRONTIER_TRAINER_JOVAN] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_M,
        .trainerName = _("ג'ובן"),
        .speechBefore = {EC_WORD_YOUR, EC_WORD_BATTLE, EC_WORD_SENSE, EC_WORD_IS, EC_WORD_SADLY, EC_WORD_LACKING},
        .speechWin = {EC_WORD_MY, EC_WORD_BATTLE, EC_WORD_SENSE, EC_WORD_IS, EC_WORD_COOL, EC_WORD_ISN_T_IT_QUES},
        .speechLose = {EC_WORD_I_WAS, EC_WORD_MINUS, EC_WORD_MY, EC_WORD_NORMAL, EC_WORD_POWER, EC_WORD_TODAY},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_RANGER_1}
    },
    [FRONTIER_TRAINER_DOMINIC] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_M,
        .trainerName = _("דומיניק"),
        .speechBefore = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_THIS, EC_WORD_EXCELLENT, EC_WORD_CAMERA, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MY, EC_WORD_CAMERA, EC_WORD_WAS, EC_WORD_AWFULLY, EC_WORD_EXPENSIVE, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_MY, EC_WORD_CAMERA, EC_WORD_DOESN_T, EC_WORD_MISS, EC_WORD_A, EC_WORD_THING},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_RANGER_1}
    },
    [FRONTIER_TRAINER_NIKOLAS] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_M,
        .trainerName = _("ניקולס"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(MIMIC), EC_WORD_POKEMON, EC_WORD_AFTER, EC_WORD_EVERY, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_IF_I_WIN, EC_WORD_I, EC_WORD_PRETEND, EC_WORD_I_AM, EC_WORD_A, EC_POKEMON_NATIONAL(TAUROS)},
        .speechLose = {EC_WORD_IF_I_LOSE, EC_WORD_I, EC_WORD_PRETEND, EC_WORD_I_AM, EC_WORD_A, EC_POKEMON_NATIONAL(MILTANK)},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_RANGER_1}
    },
    [FRONTIER_TRAINER_VALERIA] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_F,
        .trainerName = _("ולריה"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(WISH), EC_WORD_YOU, EC_WORD_WOULD, EC_WORD_NOT, EC_MOVE2(GLARE)},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_MEAN, EC_WORD_EXCL, EC_WORD_I, EC_WORD_MEAN, EC_WORD_REALLY},
        .speechLose = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_A, EC_WORD_REALLY, EC_MOVE(SCARY_FACE), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_RANGER_1}
    },
    [FRONTIER_TRAINER_DELANEY] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_F,
        .trainerName = _("דלייני"),
        .speechBefore = {EC_WORD_SCHOOL, EC_WORD_IS, EC_WORD_OVER, EC_WORD_TIME, EC_WORD_TO, EC_WORD_PLAY},
        .speechWin = {EC_WORD_MY, EC_WORD_BOY, EC_WORD_FRIEND, EC_WORD_IS, EC_WORD_FROM, EC_WORD_SCHOOL},
        .speechLose = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_TO, EC_WORD_WORK, EC_WORD_NEXT, EC_WORD_WEEK},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_RANGER_1}
    },
    [FRONTIER_TRAINER_MEGHAN] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_F,
        .trainerName = _("מייגן"),
        .speechBefore = {EC_WORD_SCHOOL, EC_WORD_IS, EC_WORD_OUT, EC_WORD_TIME, EC_WORD_TO, EC_WORD_PLAY},
        .speechWin = {EC_WORD_MY, EC_WORD_BOY, EC_WORD_FRIEND, EC_WORD_LIKES, EC_WORD_COMICS, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_IT_S, EC_WORD_BACK, EC_WORD_TO, EC_WORD_SCHOOL, EC_WORD_SOON, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_RANGER_1}
    },
    [FRONTIER_TRAINER_ROBERTO] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("רוברטו"),
        .speechBefore = {EC_WORD_DRAGON, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_INVINCIBLE, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_YOU, EC_WORD_WEREN_T, EC_WORD_BAD, EC_WORD_I_WAS, EC_WORD_JUST, EC_WORD_BETTER},
        .speechLose = {EC_WORD_AREN_T, EC_WORD_YOU, EC_WORD_SATISFIED, EC_WORD_YET, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_1}
    },
    [FRONTIER_TRAINER_DAMIAN] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("דמיאן"),
        .speechBefore = {EC_WORD_MY, EC_WORD_PURE_POWER, EC_WORD_IS, EC_WORD_MACHINE, EC_WORD_LIKE, EC_WORD_EXCL},
        .speechWin = {EC_WORD_MY, EC_MOVE2(MACH_PUNCH), EC_WORD_WILL, EC_WORD_MAKE, EC_WORD_A, EC_MOVE(BRICK_BREAK)},
        .speechLose = {EC_WORD_ARRGH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_NO, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_1}
    },
    [FRONTIER_TRAINER_BRODY] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("ברודי"),
        .speechBefore = {EC_WORD_MY, EC_WORD_FASHION, EC_WORD_SENSE, EC_WORD_SEEMS, EC_POKEMON(ODDISH), EC_WORD_QUES},
        .speechWin = {EC_WORD_IT_S, EC_WORD_MY, EC_WORD_FAMILY, EC_WORD_STAY_AT_HOME, EC_WORD_LOOK, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_QUESTION, EC_WORD_YOUR, EC_WORD_FASHION, EC_WORD_SENSE, EC_WORD_SERIOUSLY},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_1}
    },
    [FRONTIER_TRAINER_GRAHAM] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("גרהם"),
        .speechBefore = {EC_WORD_YEAH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_YEAH_YEAH, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WAHAHAHA, EC_WORD_WAHAHAHA, EC_WORD_EXCL, EC_WORD_WAHAHAHA, EC_WORD_WAHAHAHA, EC_WORD_EXCL_EXCL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_SORRY, EC_WORD_ELLIPSIS, EC_WORD_IT_S, EC_WORD_MY, EC_WORD_BAD},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_1}
    },
    [FRONTIER_TRAINER_TYLOR] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("טיילור"),
        .speechBefore = {EC_WORD_ARE, EC_WORD_YOU, EC_WORD_FEELING, EC_WORD_MY, EC_MOVE2(HEAT_WAVE), EC_WORD_QUES},
        .speechWin = {EC_WORD_YES, EC_WORD_I_AM, EC_WORD_ON, EC_WORD_FIRE, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_BUT, EC_WORD_I_WAS, EC_WORD_ON, EC_WORD_FIRE, EC_WORD_FOR, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_2}
    },
    [FRONTIER_TRAINER_JAREN] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("ג'רן"),
        .speechBefore = {EC_WORD_FIGHTING, EC_WORD_SPIRIT, EC_WORD_QUES, EC_WORD_ME, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_WANT, EC_WORD_MORE, EC_WORD_CUTE, EC_WORD_POKEMON, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_LOOK, EC_WORD_QUITE, EC_WORD_CUTE, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_2}
    },
    [FRONTIER_TRAINER_CORDELL] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_M,
        .trainerName = _("קורדל"),
        .speechBefore = {EC_WORD_A, EC_WORD_BATTLE, EC_WORD_IS, EC_WORD_DECIDED, EC_WORD_ON, EC_WORD_SPIRIT},
        .speechWin = {EC_WORD_CAN_T, EC_WORD_YOU, EC_WORD_ACCEPT, EC_WORD_THAT, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_WORD_BE, EC_WORD_ON, EC_WORD_MY, EC_WORD_WAY},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_BREEDER_M_1}
    },
    [FRONTIER_TRAINER_JAZLYN] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_F,
        .trainerName = _("ג'זלין"),
        .speechBefore = {EC_WORD_IS, EC_WORD_YOUR, EC_WORD_POKEDEX, EC_WORD_REALLY, EC_WORD_AWESOME, EC_WORD_QUES},
        .speechWin = {EC_WORD_OH_YEAH, EC_WORD_WOW, EC_WORD_YOUR, EC_WORD_POKEDEX, EC_WORD_IS, EC_WORD_SUPER},
        .speechLose = {EC_WORD_AN, EC_WORD_AVANT_GARDE, EC_WORD_POKEDEX, EC_WORD_WOULD, EC_WORD_BE, EC_WORD_AWESOME},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_BREEDER_F_1}
    },
    [FRONTIER_TRAINER_ZACHERY] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("זאקרי"),
        .speechBefore = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_MY, EC_WORD_OWN, EC_WORD_PLACE, EC_WORD_YEEHAW_EXCL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_AN, EC_WORD_EXCITING, EC_WORD_TIME, EC_WORD_FOR, EC_WORD_ME},
        .speechLose = {EC_WORD_YOU, EC_WORD_CAN_T, EC_WORD_FLATTEN, EC_WORD_MY, EC_WORD_HAPPINESS, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_2}
    },
    [FRONTIER_TRAINER_JOHAN] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("יוהן"),
        .speechBefore = {EC_WORD_WINTER, EC_WORD_WILL, EC_WORD_SOON, EC_WORD_BE, EC_WORD_HERE, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MY, EC_WORD_ALLOWANCE, EC_WORD_COULD, EC_WORD_USE, EC_WORD_A, EC_MOVE2(HELPING_HAND)},
        .speechLose = {EC_WORD_I, EC_WORD_ALWAYS, EC_WORD_USE, EC_WORD_MY, EC_WORD_ALLOWANCE, EC_WORD_UP},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_2_NO_DUGTRIO}
    },
    [FRONTIER_TRAINER_SHEA] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("שיה"),
        .speechBefore = {EC_WORD_DO, EC_WORD_YOU, EC_WORD_BATTLE, EC_WORD_WITH, EC_WORD_BEAUTY, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_BATTLE, EC_WORD_IN, EC_WORD_AN, EC_WORD_UGLY, EC_WORD_WAY},
        .speechLose = {EC_WORD_WHAT, EC_WORD_IS, EC_WORD_BEAUTY, EC_WORD_TO, EC_WORD_YOU, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_2}
    },
    [FRONTIER_TRAINER_KAILA] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("קיילה"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_THIRSTY, EC_WORD_RIGHT, EC_WORD_NOW, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_I, EC_WORD_COULD, EC_WORD_USE, EC_WORD_A, EC_WORD_COLD, EC_WORD_DRINK},
        .speechLose = {EC_WORD_THAT, EC_WORD_LOSS, EC_WORD_IS, EC_WORD_HARD, EC_WORD_TO, EC_MOVE2(SWALLOW)},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_2}
    },
    [FRONTIER_TRAINER_ISIAH] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_M,
        .trainerName = _("ישעיהו"),
        .speechBefore = {EC_WORD_I, EC_WORD_PRETEND, EC_WORD_TO, EC_WORD_STUDY, EC_WORD_A_LOT, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_MOVE2(TRICK), EC_WORD_MOTHER, EC_WORD_FOR, EC_WORD_MY, EC_WORD_ALLOWANCE},
        .speechLose = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_WANT, EC_WORD_TO, EC_WORD_STUDY, EC_WORD_MORE},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_2}
    },
    [FRONTIER_TRAINER_GARRETT] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_M,
        .trainerName = _("גארט"),
        .speechBefore = {EC_WORD_I, EC_WORD_ENJOY, EC_WORD_COMICS, EC_WORD_AND, EC_WORD_THIS, EC_WORD_GAME},
        .speechWin = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_THIS, EC_WORD_MUSIC, EC_WORD_IDOL, EC_WORD_TOO},
        .speechLose = {EC_WORD_BUT, EC_WORD_I, EC_WORD_HAVE, EC_WORD_TO, EC_WORD_STUDY, EC_WORD_MORE},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_2}
    },
    [FRONTIER_TRAINER_HAYLIE] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_F,
        .trainerName = _("היילי"),
        .speechBefore = {EC_WORD_I, EC_WORD_WORRY, EC_WORD_TOO, EC_WORD_MUCH, EC_WORD_TO, EC_WORD_SLEEP},
        .speechWin = {EC_WORD_A, EC_WORD_WIN, EC_WORD_GIVES, EC_WORD_ME, EC_WORD_A, EC_MOVE2(CALM_MIND)},
        .speechLose = {EC_WORD_MY, EC_WORD_INSOMNIA, EC_WORD_WILL, EC_WORD_GET, EC_WORD_BAD, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_2}
    },
    [FRONTIER_TRAINER_MEGAN] = {
        .facilityClass = FACILITY_CLASS_SCHOOL_KID_F,
        .trainerName = _("מייגן"),
        .speechBefore = {EC_WORD_I, EC_WORD_BELIEVE, EC_WORD_IN, EC_WORD_AN, EC_MOVE(AROMATHERAPY), EC_WORD_BATH},
        .speechWin = {EC_WORD_I, EC_WORD_WANT, EC_WORD_A, EC_WORD_HEALTHY, EC_WORD_CLEAR_BODY, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_IF, EC_WORD_ONLY, EC_MOVE(AROMATHERAPY), EC_WORD_WERE, EC_WORD_LESS, EC_WORD_EXPENSIVE},
        .monSet = (const u16[]){FRONTIER_MONS_SCHOOL_KID_2}
    },
    [FRONTIER_TRAINER_ISSAC] = {
        .facilityClass = FACILITY_CLASS_RICH_BOY,
        .trainerName = _("יצחק"),
        .speechBefore = {EC_WORD_MY, EC_WORD_HOBBY, EC_WORD_QUES, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_ANY, EC_WORD_KIND, EC_WORD_OF, EC_MOVE2(WATER_SPORT)},
        .speechLose = {EC_WORD_I, EC_WORD_DISLIKE, EC_WORD_ANY, EC_WORD_KIND, EC_WORD_OF, EC_MOVE2(MUD_SPORT)},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_2}
    },
    [FRONTIER_TRAINER_QUINTON] = {
        .facilityClass = FACILITY_CLASS_RICH_BOY,
        .trainerName = _("קווינטן"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_SAD, EC_WORD_CAUSE, EC_WORD_I_AM, EC_WORD_TOO_WEAK, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_YOU, EC_WORD_AREN_T, EC_WORD_TOO_STRONG, EC_WORD_FOR, EC_WORD_ME, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_HEY, EC_WORD_WHAT, EC_WORD_DID, EC_WORD_I, EC_WORD_DO, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_2}
    },
    [FRONTIER_TRAINER_SALMA] = {
        .facilityClass = FACILITY_CLASS_LADY,
        .trainerName = _("סלמה"),
        .speechBefore = {EC_WORD_YOU_VE, EC_WORD_GOT, EC_WORD_YOUR, EC_WORD_HUSTLE, EC_WORD_ON, EC_WORD_EXCL},
        .speechWin = {EC_WORD_I, EC_WORD_WIN, EC_WORD_YOU, EC_WORD_HUSTLE, EC_WORD_ON, EC_WORD_OUT},
        .speechLose = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_GET, EC_WORD_HOW, EC_WORD_I, EC_WORD_LOST},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_2}
    },
    [FRONTIER_TRAINER_ANSLEY] = {
        .facilityClass = FACILITY_CLASS_LADY,
        .trainerName = _("אנסלי"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_BORED, EC_WORD_ELLIPSIS, EC_WORD_DANCE, EC_WORD_FOR, EC_WORD_ME},
        .speechWin = {EC_WORD_YOU_VE, EC_WORD_BORED, EC_WORD_ME, EC_WORD_SOME, EC_WORD_MORE, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_TAKE, EC_WORD_YOUR, EC_MOVE2(FRUSTRATION), EC_WORD_SOME, EC_WORD_OTHER, EC_WORD_PLACE},
        .monSet = (const u16[]){FRONTIER_MONS_RICH_BOY_LADY_2}
    },
    [FRONTIER_TRAINER_HOLDEN] = {
        .facilityClass = FACILITY_CLASS_BUG_CATCHER,
        .trainerName = _("הולדן"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_COMMEMORATE, EC_WORD_MY, EC_WORD_COOLNESS, EC_WORD_IN, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_TOO_WEAK, EC_WORD_FOR, EC_WORD_ANY, EC_WORD_PRAISE, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOUR, EC_WORD_BATTLE, EC_WORD_SENSE, EC_WORD_IS, EC_WORD_AMUSING, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_CATCHER_2}
    },
    [FRONTIER_TRAINER_LUCA] = {
        .facilityClass = FACILITY_CLASS_BUG_CATCHER,
        .trainerName = _("לוקה"),
        .speechBefore = {EC_WORD_WE, EC_WORD_WILL, EC_WORD_HAVE, EC_WORD_A, EC_WORD_COOL, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_I, EC_WORD_WON, EC_WORD_IN, EC_WORD_A, EC_WORD_COOL, EC_WORD_WAY},
        .speechLose = {EC_WORD_HELLO, EC_WORD_QUES, EC_WORD_I_AM, EC_WORD_JUST, EC_WORD_A, EC_WORD_KID},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_CATCHER_2}
    },
    [FRONTIER_TRAINER_JAMISON] = {
        .facilityClass = FACILITY_CLASS_NINJA_BOY,
        .trainerName = _("ג'יימסן"),
        .speechBefore = {EC_WORD_MY, EC_MOVE2(SECRET_POWER), EC_WORD_IS, EC_WORD_OVERWHELMING, EC_WORD_TO, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_DID, EC_WORD_YOU, EC_WORD_SEE, EC_WORD_THAT, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_WORD_USE, EC_MOVE(SMOKESCREEN), EC_WORD_TO, EC_WORD_ESCAPE},
        .monSet = (const u16[]){FRONTIER_MONS_NINJA_BOY_2}
    },
    [FRONTIER_TRAINER_GUNNAR] = {
        .facilityClass = FACILITY_CLASS_NINJA_BOY,
        .trainerName = _("גונאר"),
        .speechBefore = {EC_WORD_I, EC_MOVE(CUT), EC_WORD_DOWN, EC_WORD_EVERY, EC_WORD_OPPONENT, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_DON_T, EC_MOVE(GRUDGE), EC_WORD_ME, EC_WORD_FOR, EC_WORD_YOUR, EC_WORD_LOSS},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_LOSE, EC_WORD_THAT, EC_MOVE(SCARY_FACE), EC_WORD_OF, EC_WORD_YOURS},
        .monSet = (const u16[]){FRONTIER_MONS_NINJA_BOY_2}
    },
    [FRONTIER_TRAINER_CRAIG] = {
        .facilityClass = FACILITY_CLASS_TUBER_M,
        .trainerName = _("קרייג"),
        .speechBefore = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_WAIT, EC_WORD_FOR, EC_WORD_MY, EC_WORD_TRAIN},
        .speechWin = {EC_WORD_MY, EC_WORD_TRAIN, EC_WORD_ISN_T, EC_WORD_HERE, EC_WORD_YET, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_HERE_IT_IS, EC_WORD_MY, EC_WORD_TRAIN, EC_WORD_SEE_YA, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_2}
    },
    [FRONTIER_TRAINER_PIERCE] = {
        .facilityClass = FACILITY_CLASS_TUBER_M,
        .trainerName = _("פירס"),
        .speechBefore = {EC_WORD_THERE, EC_WORD_WAS, EC_WORD_A, EC_MOVE2(HEAT_WAVE), EC_WORD_LAST, EC_WORD_WEEK},
        .speechWin = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_TAKE, EC_WORD_A, EC_MOVE2(HEAT_WAVE), EC_EMPTY_WORD},
        .speechLose = {EC_WORD_DIDN_T, EC_WORD_IT, EC_MOVE(HAIL), EC_WORD_TOO, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_2}
    },
    [FRONTIER_TRAINER_REGINA] = {
        .facilityClass = FACILITY_CLASS_TUBER_F,
        .trainerName = _("רג'ינה"),
        .speechBefore = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_TO, EC_WORD_PLAY, EC_WORD_IN, EC_WORD_WATER},
        .speechWin = {EC_WORD_I, EC_WORD_REFUSE, EC_WORD_TO, EC_WORD_COME, EC_WORD_OUT, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_NOT, EC_WORD_MUCH, EC_WORD_GOOD, EC_WORD_IN, EC_WORD_WATER},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_2}
    },
    [FRONTIER_TRAINER_ALISON] = {
        .facilityClass = FACILITY_CLASS_TUBER_F,
        .trainerName = _("אליסון"),
        .speechBefore = {EC_WORD_THIS, EC_WORD_KINDERGARTEN, EC_WORD_MAGAZINE, EC_WORD_IS, EC_WORD_TOO, EC_WORD_MUCH},
        .speechWin = {EC_WORD_HOW, EC_WORD_TO, EC_WORD_BUG, EC_WORD_YOUR, EC_WORD_TEACHER, EC_WORD_QUES},
        .speechLose = {EC_WORD_ENJOY, EC_WORD_A, EC_WORD_TASTY, EC_WORD_SCHOOL, EC_WORD_DIET, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_TUBER_2}
    },
    [FRONTIER_TRAINER_HANK] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("הנק"),
        .speechBefore = {EC_WORD_THERE, EC_WORD_IS, EC_WORD_A, EC_WORD_BUG, EC_WORD_EVENT, EC_WORD_SOON},
        .speechWin = {EC_WORD_IT_S, EC_WORD_A, EC_WORD_BUG, EC_WORD_FASHION, EC_WORD_SHOW, EC_WORD_EXCL},
        .speechLose = {EC_WORD_DON_T, EC_WORD_YOU, EC_WORD_LIKE, EC_WORD_BUG, EC_WORD_POKEMON, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_3}
    },
    [FRONTIER_TRAINER_EARL] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("ארל"),
        .speechBefore = {EC_WORD_THE, EC_WORD_INVINCIBLE, EC_WORD_BUG, EC_WORD_TRAINER, EC_WORD_IS, EC_WORD_HERE},
        .speechWin = {EC_WORD_THE, EC_WORD_INVINCIBLE, EC_WORD_BUG, EC_WORD_TRAINER, EC_WORD_AM, EC_WORD_I},
        .speechLose = {EC_WORD_SEE, EC_WORD_HOW, EC_WORD_FAST, EC_WORD_I, EC_WORD_RUN_AWAY, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_3}
    },
    [FRONTIER_TRAINER_RAMIRO] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("רמירו"),
        .speechBefore = {EC_WORD_I, EC_WORD_WENT, EC_WORD_TO, EC_WORD_A, EC_WORD_FISHING, EC_WORD_SCHOOL},
        .speechWin = {EC_WORD_SERIOUSLY, EC_WORD_I_AM, EC_WORD_IN, EC_WORD_THE, EC_WORD_FISHING, EC_WORD_HALL_OF_FAME},
        .speechLose = {EC_WORD_I, EC_WORD_WANT, EC_WORD_TO, EC_WORD_GO, EC_WORD_BACK, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_2}
    },
    [FRONTIER_TRAINER_HUNTER] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("הנטר"),
        .speechBefore = {EC_WORD_SHOW, EC_WORD_ME, EC_WORD_A, EC_WORD_TOTALLY, EC_WORD_COOL, EC_MOVE(CROSS_CHOP)},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_TOO_WEAK, EC_WORD_TO, EC_WORD_DO, EC_WORD_A, EC_MOVE(CROSS_CHOP)},
        .speechLose = {EC_WORD_WAS, EC_WORD_IT, EC_WORD_A, EC_WORD_MISTAKE, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_2}
    },
    [FRONTIER_TRAINER_AIDEN] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("איידן"),
        .speechBefore = {EC_WORD_MY, EC_WORD_WORK, EC_WORD_IS, EC_WORD_MAKING, EC_WORD_ME, EC_WORD_HEALTHY},
        .speechWin = {EC_WORD_YOU, EC_WORD_SEE, EC_WORD_QUES, EC_WORD_I_AM, EC_WORD_HEALTHY, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_MORE, EC_WORD_HEALTHY, EC_WORD_THAN, EC_WORD_I_AM, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_3}
    },
    [FRONTIER_TRAINER_XAVIER] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("קסבייר"),
        .speechBefore = {EC_WORD_HEY_THERE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_LOOK, EC_WORD_LOOK, EC_WORD_EXCL_EXCL},
        .speechWin = {EC_WORD_GOOD_BYE, EC_WORD_AND, EC_WORD_THANK_YOU, EC_WORD_THAT_WAS, EC_WORD_FUNNY, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WOWEE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_NO, EC_WORD_NO, EC_WORD_EXCL_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_3}
    },
    [FRONTIER_TRAINER_CLINTON] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("קלינטון"),
        .speechBefore = {EC_WORD_WANT, EC_WORD_TO, EC_WORD_SEE, EC_WORD_MY, EC_MOVE(HYPNOSIS), EC_WORD_QUES},
        .speechWin = {EC_WORD_YOUR, EC_MOVE2(FURY_SWIPES), EC_WORD_YOUR, EC_MOVE(STRENGTH), EC_WORD_YOUNG, EC_WORD_TRAINER},
        .speechLose = {EC_WORD_TCH, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_TOO_WEAK, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_COLLECTOR_2}
    },
    [FRONTIER_TRAINER_JESSE] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("ג'סי"),
        .speechBefore = {EC_WORD_THIS, EC_WORD_BATTLE, EC_WORD_IS, EC_WORD_FOR, EC_WORD_MY, EC_WORD_MOTHER},
        .speechWin = {EC_WORD_MOTHER, EC_WORD_WILL, EC_WORD_BE, EC_WORD_HAPPY, EC_WORD_FOR, EC_WORD_ME},
        .speechLose = {EC_WORD_I, EC_WORD_WANT, EC_WORD_MY, EC_WORD_MOTHER, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_COLLECTOR_2}
    },
    [FRONTIER_TRAINER_EDUARDO] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("אדוארדו"),
        .speechBefore = {EC_WORD_OUR, EC_WORD_MUSIC, EC_WORD_WILL, EC_WORD_PLAY, EC_WORD_ALL, EC_WORD_NIGHT},
        .speechWin = {EC_WORD_NIGHTTIME, EC_WORD_IS, EC_WORD_WHEN, EC_WORD_I, EC_WORD_PLAY, EC_WORD_BEST},
        .speechLose = {EC_WORD_LET_S, EC_WORD_PARTY, EC_WORD_UNTIL, EC_WORD_THE, EC_MOVE(MORNING_SUN), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_2}
    },
    [FRONTIER_TRAINER_HAL] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("הל"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_TRENDY, EC_WORD_AREN_T, EC_WORD_I, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_HIP_AND, EC_WORD_HAPPENING, EC_WORD_OH_YEAH, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_ALWAYS, EC_WORD_TRENDY, EC_WORD_THANK_YOU, EC_WORD_VERY, EC_WORD_MUCH},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_2}
    },
    [FRONTIER_TRAINER_GAGE] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("גייג'"),
        .speechBefore = {EC_WORD_HERE_IT_IS, EC_WORD_A, EC_WORD_FLYING, EC_WORD_TYPE, EC_WORD_HIDDEN, EC_WORD_MOVE},
        .speechWin = {EC_WORD_IT_S, EC_WORD_A, EC_WORD_FLYING, EC_WORD_TYPE, EC_WORD_VICTORY, EC_WORD_EXCL},
        .speechLose = {EC_WORD_IF_I_LOSE, EC_WORD_I, EC_WORD_JUST, EC_MOVE(FLY), EC_WORD_AWAY, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_2}
    },
    [FRONTIER_TRAINER_ARNOLD] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("ארנולד"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_WEIRD, EC_WORD_FROM, EC_WORD_A, EC_WORD_DREAM},
        .speechWin = {EC_WORD_YOUR, EC_MOVE(SCARY_FACE), EC_WORD_WAS, EC_WORD_IN, EC_WORD_MY, EC_WORD_DREAM},
        .speechLose = {EC_WORD_MY, EC_WORD_INCREDIBLE, EC_WORD_DREAM, EC_WORD_WAS, EC_WORD_SO, EC_WORD_WEIRD},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_2}
    },
    [FRONTIER_TRAINER_JARRETT] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("ג'ארט"),
        .speechBefore = {EC_WORD_COME_ON, EC_WORD_LET_S, EC_WORD_DANCE, EC_WORD_LIKE, EC_WORD_IT_S, EC_WORD_YESTERDAY},
        .speechWin = {EC_WORD_YOU, EC_WORD_LIKE, EC_WORD_HOW, EC_WORD_I, EC_WORD_DANCE, EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU, EC_WORD_DON_T, EC_WORD_APPRECIATE, EC_WORD_HOW, EC_WORD_I, EC_WORD_DANCE},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_2}
    },
    [FRONTIER_TRAINER_GARETT] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("גארט"),
        .speechBefore = {EC_WORD_MY, EC_WORD_GIRL, EC_WORD_GIVES, EC_WORD_ME, EC_WORD_A_LITTLE, EC_MOVE2(SWEET_KISS)},
        .speechWin = {EC_WORD_MY, EC_WORD_GIRL, EC_WORD_FRIEND, EC_WORD_IS, EC_WORD_MY, EC_WORD_TREASURE},
        .speechLose = {EC_WORD_A, EC_WORD_TREASURE, EC_WORD_ISN_T, EC_WORD_ALWAYS, EC_WORD_ABOUT, EC_WORD_MONEY},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_2}
    },
    [FRONTIER_TRAINER_EMANUEL] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("עמנואל"),
        .speechBefore = {EC_WORD_SMARTNESS, EC_WORD_ALONE, EC_WORD_WON_T, EC_WORD_MAKE, EC_WORD_YOU, EC_WORD_WIN},
        .speechWin = {EC_WORD_I_AM, EC_WORD_NOT_VERY, EC_WORD_SMART, EC_WORD_BUT, EC_WORD_I, EC_WORD_WON},
        .speechLose = {EC_WORD_HOW, EC_WORD_DID, EC_WORD_YOU, EC_MOVE2(FAKE_OUT), EC_WORD_ME, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_2}
    },
    [FRONTIER_TRAINER_GUSTAVO] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("גוסטבו"),
        .speechBefore = {EC_MOVE(CHARGE), EC_WORD_EXCL, EC_EMPTY_WORD, EC_MOVE(CHARGE), EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_SURRENDER, EC_WORD_QUES, EC_EMPTY_WORD, EC_WORD_SO, EC_WORD_SOON, EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU, EC_WORD_CAN_T, EC_WORD_MAKE, EC_WORD_ME, EC_WORD_SURRENDER, EC_WORD_YET},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_2}
    },
    [FRONTIER_TRAINER_KAMERON] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("קמרון"),
        .speechBefore = {EC_WORD_TAKE_THAT, EC_WORD_EXCL, EC_WORD_IT_S, EC_WORD_MY, EC_WORD_FIERY, EC_MOVE2(TRICK)},
        .speechWin = {EC_WORD_DID, EC_WORD_MY, EC_WORD_FIERY, EC_MOVE2(TRICK), EC_MOVE(ASTONISH), EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU, EC_WORD_DIDN_T, EC_WORD_FALL, EC_WORD_FOR, EC_WORD_MY, EC_MOVE2(TRICK)},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_2}
    },
    [FRONTIER_TRAINER_ALFREDO] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("אלפרדו"),
        .speechBefore = {EC_WORD_A, EC_WORD_FIERY, EC_WORD_GOURMET, EC_WORD_AM, EC_WORD_I, EC_WORD_EXCL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_A, EC_WORD_TASTY, EC_WORD_GOURMET, EC_WORD_VICTORY, EC_WORD_EXCL},
        .speechLose = {EC_WORD_WHAT, EC_WORD_A, EC_WORD_DISASTER, EC_WORD_THAT_WAS, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_2}
    },
    [FRONTIER_TRAINER_RUBEN] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("ראובן"),
        .speechBefore = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_WAIT, EC_WORD_TO, EC_WORD_GET, EC_WORD_GOING},
        .speechWin = {EC_WORD_GET, EC_WORD_GOING, EC_WORD_EXCL, EC_WORD_THIS, EC_WORD_IS, EC_WORD_GOOD_BYE},
        .speechLose = {EC_WORD_I_VE, EC_WORD_GOT, EC_WORD_TO, EC_WORD_GET, EC_WORD_GOING, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_GENTLEMAN_2}
    },
    [FRONTIER_TRAINER_LAMAR] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("למאר"),
        .speechBefore = {EC_WORD_A, EC_MOVE2(PRESENT), EC_WORD_FOR, EC_WORD_ME, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MMM, EC_WORD_THIS, EC_WORD_IS, EC_WORD_QUITE, EC_WORD_TASTY, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_OH, EC_WORD_IT_S, EC_WORD_A, EC_WORD_GAME, EC_WORD_IS_IT_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_GENTLEMAN_2}
    },
    [FRONTIER_TRAINER_JAXON] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("ג'קסון"),
        .speechBefore = {EC_WORD_A, EC_WORD_SHELL_ARMOR, EC_WORD_IS, EC_WORD_WHAT, EC_WORD_I, EC_WORD_WANT},
        .speechWin = {EC_WORD_MY, EC_WORD_FATHER, EC_WORD_AND, EC_WORD_MOTHER, EC_WORD_WON_T, EC_WORD_ACCEPT},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_I, EC_WORD_NEED, EC_WORD_A, EC_WORD_SHELL_ARMOR, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_3}
    },
    [FRONTIER_TRAINER_LOGAN] = {
        .facilityClass = FACILITY_CLASS_YOUNGSTER,
        .trainerName = _("לוגן"),
        .speechBefore = {EC_WORD_IF_I_LOSE, EC_WORD_I, EC_WORD_WILL, EC_WORD_STUDY, EC_WORD_FOR, EC_WORD_SCHOOL},
        .speechWin = {EC_WORD_ME, EC_WORD_STUDY, EC_WORD_QUES, EC_WORD_NOT_VERY, EC_WORD_LIKELY_TO, EC_WORD_SEE},
        .speechLose = {EC_WORD_NO, EC_WORD_THANKS, EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_TO, EC_WORD_SLEEP},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_3}
    },
    [FRONTIER_TRAINER_EMILEE] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("אמילי"),
        .speechBefore = {EC_WORD_IS, EC_WORD_THIS, EC_WORD_KIND, EC_WORD_OF, EC_WORD_BATTLE, EC_WORD_OK_QUES},
        .speechWin = {EC_WORD_LET_S, EC_WORD_GO, EC_WORD_FOR, EC_WORD_AN, EC_MOVE(ICY_WIND), EC_MOVE2(SURF)},
        .speechLose = {EC_WORD_HOW, EC_WORD_ABOUT, EC_WORD_A, EC_MOVE(ROCK_SLIDE), EC_WORD_SHOW, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_3}
    },
    [FRONTIER_TRAINER_JOSIE] = {
        .facilityClass = FACILITY_CLASS_LASS,
        .trainerName = _("ג'וזי"),
        .speechBefore = {EC_WORD_A, EC_WORD_POKEMON, EC_WORD_FASHION, EC_WORD_CONTEST, EC_WORD_IS, EC_WORD_PRETTY},
        .speechWin = {EC_WORD_I, EC_WORD_REALLY, EC_WORD_LIKE, EC_WORD_MODE, EC_WORD_FASHION, EC_WORD_THINGS},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_TOTALLY, EC_WORD_LACKING, EC_WORD_IN, EC_WORD_FASHION, EC_WORD_SENSE},
        .monSet = (const u16[]){FRONTIER_MONS_YOUNGSTER_LASS_3}
    },
    [FRONTIER_TRAINER_ARMANDO] = {
        .facilityClass = FACILITY_CLASS_CAMPER,
        .trainerName = _("ארמנדו"),
        .speechBefore = {EC_WORD_I, EC_WORD_NEED, EC_WORD_MORE, EC_WORD_GRASS, EC_WORD_TYPE, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_TRADE, EC_WORD_ME, EC_WORD_A, EC_WORD_GRASS, EC_WORD_POKEMON, EC_WORD_PLEASE},
        .speechLose = {EC_WORD_THERE, EC_WORD_AREN_T, EC_WORD_ENOUGH, EC_WORD_GRASS, EC_WORD_TYPE, EC_WORD_POKEMON},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_2}
    },
    [FRONTIER_TRAINER_SKYLER] = {
        .facilityClass = FACILITY_CLASS_CAMPER,
        .trainerName = _("סקיילר"),
        .speechBefore = {EC_MOVE2(INGRAIN), EC_WORD_IS, EC_WORD_MY, EC_WORD_CHOICE, EC_WORD_BATTLE, EC_WORD_MOVE},
        .speechWin = {EC_WORD_YOU, EC_WORD_CAN_T, EC_WORD_MOVE, EC_WORD_ME, EC_WORD_NOW, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU, EC_MOVE(CUT), EC_WORD_ME, EC_WORD_DOWN, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_2}
    },
    [FRONTIER_TRAINER_RUTH] = {
        .facilityClass = FACILITY_CLASS_PICNICKER,
        .trainerName = _("רות"),
        .speechBefore = {EC_WORD_I, EC_WORD_WANT, EC_WORD_TO, EC_WORD_ENJOY, EC_WORD_THIS, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_MUCH, EC_WORD_TOO, EC_WORD_EASY, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_STOP, EC_WORD_I, EC_WORD_DON_T, EC_WORD_ENJOY, EC_WORD_THIS},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_2}
    },
    [FRONTIER_TRAINER_MELODY] = {
        .facilityClass = FACILITY_CLASS_PICNICKER,
        .trainerName = _("מלודי"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(WISH), EC_WORD_SUNDAY, EC_WORD_IS, EC_WORD_A, EC_MOVE2(SUNNY_DAY)},
        .speechWin = {EC_WORD_SUNDAY, EC_WORD_SEEMS, EC_WORD_FOREVER, EC_WORD_TO, EC_WORD_COME, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_THE, EC_WORD_FORECAST, EC_WORD_SAYS, EC_WORD_IT, EC_WORD_WILL, EC_MOVE(HAIL)},
        .monSet = (const u16[]){FRONTIER_MONS_CAMPER_PICNICKER_2}
    },
    [FRONTIER_TRAINER_PEDRO] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_M,
        .trainerName = _("פדרו"),
        .speechBefore = {EC_WORD_A, EC_WORD_SWIFT_SWIM, EC_WORD_WILL, EC_WORD_DO, EC_WORD_YOU, EC_WORD_GOOD},
        .speechWin = {EC_WORD_THAT_S, EC_WORD_HOW, EC_WORD_I, EC_WORD_SINK, EC_WORD_AN, EC_WORD_OPPONENT},
        .speechLose = {EC_WORD_UH_OH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_A, EC_MOVE(WHIRLPOOL), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_M_2}
    },
    [FRONTIER_TRAINER_ERICK] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_M,
        .trainerName = _("אריק"),
        .speechBefore = {EC_WORD_I, EC_WORD_WILL, EC_MOVE2(TACKLE), EC_WORD_YOU, EC_WORD_DOWN, EC_WORD_EXCL},
        .speechWin = {EC_WORD_DON_T, EC_WORD_YOU, EC_WORD_RUN_AWAY, EC_WORD_YOU, EC_WORD_LOSER, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_DIDN_T, EC_WORD_THINK, EC_WORD_YOU, EC_WORD_WOULD, EC_MOVE(COUNTER)},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_M_2}
    },
    [FRONTIER_TRAINER_ELAINE] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_F,
        .trainerName = _("איליין"),
        .speechBefore = {EC_WORD_MY, EC_WORD_HEROINE, EC_WORD_ADVENTURE, EC_WORD_ISN_T, EC_WORD_GOING, EC_WORD_WELL},
        .speechWin = {EC_WORD_THANK_YOU, EC_WORD_EXCL, EC_WORD_THAT_S, EC_WORD_WHAT, EC_WORD_I, EC_WORD_NEED},
        .speechLose = {EC_WORD_I, EC_WORD_KNOW, EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_A, EC_WORD_HEROINE},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_F_2}
    },
    [FRONTIER_TRAINER_JOYCE] = {
        .facilityClass = FACILITY_CLASS_SWIMMER_F,
        .trainerName = _("ג'ויס"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_MAKE, EC_WORD_ME, EC_WORD_GO, EC_WORD_AHAHA, EC_WORD_EXCL},
        .speechWin = {EC_WORD_LALALA, EC_WORD_NO, EC_WORD_LOSING, EC_WORD_FOR, EC_WORD_ME, EC_WORD_EXCL},
        .speechLose = {EC_WORD_LALALA, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_WORD_HUH_QUES, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMER_F_2}
    },
    [FRONTIER_TRAINER_TODD] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("טוד"),
        .speechBefore = {EC_WORD_YOU_RE, EC_WORD_A, EC_WORD_LIGHTNINGROD, EC_WORD_FOR, EC_WORD_MY, EC_WORD_POWER},
        .speechWin = {EC_WORD_THAT_S, EC_WORD_ALL, EC_WORD_YOU, EC_WORD_COULD, EC_MOVE(ABSORB), EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU, EC_MOVE2(REFLECT), EC_WORD_MY, EC_WORD_POWER, EC_WORD_BACK, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_3}
    },
    [FRONTIER_TRAINER_GAVIN] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_M,
        .trainerName = _("גאווין"),
        .speechBefore = {EC_WORD_I, EC_WORD_WILL, EC_MOVE(BIDE), EC_WORD_MY, EC_WORD_TIME, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_IT_S, EC_WORD_OVER, EC_WORD_SO, EC_WORD_SOON, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_MY, EC_WORD_MISTAKE, EC_WORD_WAS, EC_WORD_TOO, EC_WORD_EXPENSIVE, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_3}
    },
    [FRONTIER_TRAINER_MALORY] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("מלורי"),
        .speechBefore = {EC_WORD_PROMISE, EC_WORD_TO, EC_WORD_SHOW, EC_WORD_ME, EC_WORD_CUTE, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_GIGGLE, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_WORD_THANK_YOU, EC_WORD_SO, EC_WORD_MUCH},
        .speechLose = {EC_WORD_TCH, EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_AREN_T, EC_WORD_VERY, EC_WORD_NICE},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_3}
    },
    [FRONTIER_TRAINER_ESTHER] = {
        .facilityClass = FACILITY_CLASS_POKEFAN_F,
        .trainerName = _("אסתר"),
        .speechBefore = {EC_WORD_I, EC_WORD_WANT, EC_WORD_A, EC_WORD_NICE, EC_MOVE2(PRESENT), EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_PLEASE, EC_WORD_GET, EC_WORD_ME, EC_WORD_A, EC_WORD_POKEMON, EC_WORD_GAME},
        .speechLose = {EC_WORD_MESSAGE, EC_WORD_CARDS, EC_WORD_MAKE, EC_WORD_A, EC_WORD_WEAK, EC_MOVE2(PRESENT)},
        .monSet = (const u16[]){FRONTIER_MONS_POKEFAN_3}
    },
    [FRONTIER_TRAINER_OSCAR] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_M,
        .trainerName = _("אוסקר"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_SEE, EC_WORD_YOUR, EC_WORD_POWER, EC_WORD_IN, EC_WORD_FULL},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_NOT, EC_WORD_YOUR, EC_WORD_FULL, EC_WORD_POWER, EC_WORD_EXCL},
        .speechLose = {EC_WORD_NOT, EC_WORD_FUNNY, EC_WORD_ELLIPSIS, EC_WORD_YOU_RE, EC_WORD_TOO_STRONG, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_BREEDER_2}
    },
    [FRONTIER_TRAINER_WILSON] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_M,
        .trainerName = _("וילסון"),
        .speechBefore = {EC_WORD_WORK, EC_WORD_IS, EC_WORD_MAKING, EC_WORD_ME, EC_WORD_AN, EC_WORD_EARLY_BIRD},
        .speechWin = {EC_WORD_ALL, EC_WORD_WORK, EC_WORD_AND, EC_WORD_NO, EC_WORD_PLAY, EC_WORD_ELLIPSIS},
        .speechLose = {EC_MOVE(ENDURE), EC_WORD_IS, EC_WORD_ALL, EC_WORD_I, EC_WORD_CAN, EC_WORD_DO},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_BREEDER_2}
    },
    [FRONTIER_TRAINER_CLARE] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_F,
        .trainerName = _("קלייר"),
        .speechBefore = {EC_WORD_YAY, EC_WORD_EXCL, EC_WORD_A, EC_WORD_TOUGH, EC_WORD_TRAINER, EC_WORD_EXCL},
        .speechWin = {EC_WORD_AWW, EC_WORD_EXCL, EC_WORD_A, EC_WORD_WIMPY, EC_WORD_TRAINER, EC_WORD_EXCL},
        .speechLose = {EC_WORD_COOL, EC_WORD_EXCL, EC_WORD_A, EC_WORD_GENIUS, EC_WORD_TRAINER, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_BREEDER_2}
    },
    [FRONTIER_TRAINER_TESS] = {
        .facilityClass = FACILITY_CLASS_PKMN_BREEDER_F,
        .trainerName = _("טס"),
        .speechBefore = {EC_WORD_WANT, EC_WORD_SOME, EC_POKEMON(GULPIN), EC_WORD_DESIGN, EC_WORD_SWEETS, EC_WORD_QUES},
        .speechWin = {EC_WORD_THEY_RE, EC_WORD_A, EC_WORD_SECRET, EC_WORD_POKEMON, EC_WORD_GOURMET, EC_WORD_ITEM},
        .speechLose = {EC_WORD_THEY_RE, EC_WORD_TASTY, EC_WORD_EXCL, EC_WORD_REFRESHING, EC_WORD_TOO, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_PKMN_BREEDER_2}
    },
    [FRONTIER_TRAINER_LEON] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("ליאון"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_BETTER, EC_WORD_THAN, EC_WORD_ANY, EC_WORD_OTHER, EC_WORD_TRAINER},
        .speechWin = {EC_WORD_I, EC_WORD_DID, EC_WORD_IT, EC_MOVE2(JUMP_KICK), EC_WORD_FOR, EC_WORD_JOY},
        .speechLose = {EC_WORD_BACK, EC_WORD_HOME, EC_WORD_I, EC_WORD_WILL, EC_WORD_GO, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_M_2A}
    },
    [FRONTIER_TRAINER_ALONZO] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("אלונזו"),
        .speechBefore = {EC_WORD_I_VE, EC_WORD_NOT, EC_WORD_LOST, EC_WORD_ONCE, EC_WORD_YET, EC_WORD_EXCL},
        .speechWin = {EC_WORD_YOUR, EC_WORD_SAD, EC_WORD_LOOK, EC_WORD_BECOMES, EC_WORD_YOU, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_BELIEVE, EC_WORD_THIS, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_M_2B}
    },
    [FRONTIER_TRAINER_VINCE] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("וינס"),
        .speechBefore = {EC_WORD_THE, EC_WORD_TOP, EC_WORD_TRAINER, EC_WORD_THAT_S, EC_WORD_ME, EC_WORD_EXCL},
        .speechWin = {EC_WORD_THE, EC_WORD_TOP, EC_WORD_RANK, EC_WORD_BELONGS_TO, EC_WORD_ME, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_WORD_APPEAL, EC_WORD_THIS, EC_MOVE(OUTRAGE), EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_2C(LATIOS)}
    },
    [FRONTIER_TRAINER_BRYON] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_M,
        .trainerName = _("בריאן"),
        .speechBefore = {EC_WORD_MY, EC_MOVE2(BARRAGE), EC_WORD_WILL, EC_MOVE2(SLAM), EC_WORD_YOU, EC_WORD_EXCL},
        .speechWin = {EC_WORD_YOU, EC_WORD_DIDN_T, EC_WORD_COUNT_ON, EC_WORD_ANY, EC_WORD_LESS, EC_WORD_QUES},
        .speechLose = {EC_WORD_I, EC_WORD_JUST, EC_WORD_DON_T, EC_WORD_GET, EC_WORD_IT, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_2D(LATIOS)}
    },
    [FRONTIER_TRAINER_AVA] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("אווה"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_A, EC_WORD_TREASURE, EC_WORD_OF, EC_WORD_THIS, EC_WORD_WORLD},
        .speechWin = {EC_WORD_MY, EC_WORD_WORLD, EC_WORD_IS, EC_WORD_FULL, EC_WORD_OF, EC_WORD_WONDER},
        .speechLose = {EC_WORD_WHY, EC_WORD_ARE, EC_WORD_YOU, EC_WORD_SO, EC_WORD_TERRIBLE, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_F_2A}
    },
    [FRONTIER_TRAINER_MIRIAM] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("מרים"),
        .speechBefore = {EC_WORD_OH, EC_WORD_A, EC_WORD_TRAINER, EC_WORD_WITH, EC_WORD_A, EC_MOVE(SCARY_FACE)},
        .speechWin = {EC_WORD_AHAHA, EC_WORD_YOU, EC_WORD_ONLY, EC_WORD_LOOK, EC_WORD_SCARY, EC_WORD_EXCL},
        .speechLose = {EC_WORD_AIYEEH, EC_WORD_EXCL, EC_WORD_YOU, EC_WORD_REALLY, EC_WORD_ARE, EC_WORD_SCARY},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_F_2B}
    },
    [FRONTIER_TRAINER_CARRIE] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("קארי"),
        .speechBefore = {EC_WORD_I, EC_WORD_WILL, EC_WORD_SHOW, EC_WORD_YOU, EC_WORD_GUTSY, EC_WORD_EXCL},
        .speechWin = {EC_WORD_IT_S, EC_WORD_ALL, EC_WORD_ABOUT, EC_WORD_GUTS, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_OH, EC_WORD_NO, EC_WORD_ELLIPSIS, EC_MOVE(SELF_DESTRUCT), EC_WORD_MODE, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_2C(LATIAS)}
    },
    [FRONTIER_TRAINER_GILLIAN2] = {
        .facilityClass = FACILITY_CLASS_COOLTRAINER_F,
        .trainerName = _("ג'יליאן"),
        .speechBefore = {EC_WORD_I, EC_WORD_SEEK, EC_WORD_A, EC_WORD_TRULY, EC_WORD_GREAT, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_I, EC_WORD_NEED, EC_WORD_A_LOT, EC_WORD_BETTER, EC_WORD_BATTLE, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_THAT_WAS, EC_WORD_A_LITTLE, EC_WORD_TOO, EC_WORD_MUCH, EC_WORD_TO, EC_WORD_TAKE},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_2D(LATIAS)}
    },
    [FRONTIER_TRAINER_TYLER] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_M,
        .trainerName = _("טיילר"),
        .speechBefore = {EC_WORD_YO, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_LET_S, EC_WORD_GO, EC_WORD_EXCL_EXCL},
        .speechWin = {EC_WORD_YO, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_WON, EC_WORD_YO},
        .speechLose = {EC_WORD_YO, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_LOST, EC_WORD_YO},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_A}
    },
    [FRONTIER_TRAINER_CHAZ] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_M,
        .trainerName = _("צ'אז"),
        .speechBefore = {EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_HAVE, EC_WORD_TOO, EC_WORD_MUCH, EC_WORD_POWER},
        .speechWin = {EC_WORD_THEY, EC_WORD_HAVE, EC_WORD_MORE, EC_WORD_POWER, EC_WORD_NOW, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YEAH, EC_MOVE2(TAKE_DOWN), EC_WORD_THEIR, EC_WORD_POWER, EC_WORD_A_TINY_BIT, EC_WORD_PLEASE},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_B}
    },
    [FRONTIER_TRAINER_NELSON] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_M,
        .trainerName = _("נלסון"),
        .speechBefore = {EC_WORD_WELL_THEN, EC_WORD_WILL, EC_WORD_THIS, EC_WORD_POKEMON, EC_WORD_WORK, EC_WORD_QUES},
        .speechWin = {EC_WORD_I, EC_WORD_SEE, EC_WORD_THAT, EC_WORD_IT, EC_WORD_WAS, EC_WORD_TOO_STRONG},
        .speechLose = {EC_WORD_IT, EC_WORD_DIDN_T, EC_WORD_MATCH_UP, EC_WORD_WELL, EC_WORD_I, EC_WORD_THINK},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_2D(LATIOS)}
    },
    [FRONTIER_TRAINER_SHANIA] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_F,
        .trainerName = _("שאנייה"),
        .speechBefore = {EC_WORD_ALL, EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_ABSOLUTELY, EC_WORD_ADORE, EC_WORD_ME},
        .speechWin = {EC_WORD_HAPPINESS, EC_WORD_IS, EC_WORD_A, EC_WORD_POKEMON, EC_WORD_WITH, EC_WORD_CUTE_CHARM},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_SO, EC_WORD_MEAN, EC_WORD_TO, EC_WORD_CUTE, EC_WORD_POKEMON},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_C}
    },
    [FRONTIER_TRAINER_STELLA] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_F,
        .trainerName = _("סטלה"),
        .speechBefore = {EC_WORD_I, EC_WORD_WANT, EC_WORD_TO, EC_WORD_SEE, EC_WORD_YOUR, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_WELL, EC_WORD_AREN_T, EC_WORD_THEY, EC_WORD_BORING, EC_WORD_QUES, EC_WORD_AHAHA},
        .speechLose = {EC_WORD_YOUR, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_SOMETHING, EC_WORD_ELSE, EC_WORD_ALL_RIGHT},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_D}
    },
    [FRONTIER_TRAINER_DORINE] = {
        .facilityClass = FACILITY_CLASS_PKMN_RANGER_F,
        .trainerName = _("דורין"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_YOUNG, EC_WORD_AND, EC_WORD_STRONG, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_SEE, EC_WORD_QUES, EC_WORD_AREN_T, EC_WORD_I, EC_WORD_GOOD, EC_WORD_QUES},
        .speechLose = {EC_WORD_THIS, EC_WORD_ISN_T, EC_WORD_WORKING, EC_WORD_OUT, EC_WORD_AT, EC_WORD_ALL},
        .monSet = (const u16[]){FRONTIER_MONS_COOLTRAINER_2D(LATIAS)}
    },
    [FRONTIER_TRAINER_MADDOX] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("מדוקס"),
        .speechBefore = {EC_WORD_DRAGON, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_MY, EC_WORD_NO_1, EC_WORD_CHOICE},
        .speechWin = {EC_WORD_IT_S, EC_WORD_NO, EC_WORD_SECRET, EC_WORD_DRAGON, EC_WORD_POKEMON, EC_WORD_WIN},
        .speechLose = {EC_WORD_DRAGON, EC_WORD_POKEMON, EC_WORD_SHOULD, EC_WORD_NOT, EC_WORD_LOSE, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_2}
    },
    [FRONTIER_TRAINER_DAVIN] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("דאווין"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_HEAR, EC_WORD_YOU, EC_MOVE2(ROAR), EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WROOOAAR_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_VICTORY, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WROOOAAR_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_WHY, EC_WORD_QUES_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_2}
    },
    [FRONTIER_TRAINER_TREVON] = {
        .facilityClass = FACILITY_CLASS_DRAGON_TAMER,
        .trainerName = _("טרבון"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_LIVING, EC_WORD_ONLY, EC_WORD_WITH, EC_WORD_DRAGON, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_THE, EC_WORD_WAY, EC_WORD_I_AM, EC_WORD_LIVING, EC_WORD_IS, EC_WORD_PERFECT},
        .speechLose = {EC_WORD_YOU_VE, EC_WORD_DESTROYED, EC_WORD_THE, EC_WORD_WAY, EC_WORD_I_AM, EC_WORD_LIVING},
        .monSet = (const u16[]){FRONTIER_MONS_DRAGON_TAMER_2}
    },
    [FRONTIER_TRAINER_MATEO] = {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("מטאו"),
        .speechBefore = {EC_WORD_THIS, EC_WORD_SHOULD, EC_WORD_BE, EC_WORD_OVER, EC_WORD_SOON, EC_WORD_ENOUGH},
        .speechWin = {EC_WORD_WELL, EC_WORD_THAT, EC_WORD_DIDN_T, EC_WORD_TAKE, EC_WORD_VERY, EC_WORD_MUCH},
        .speechLose = {EC_WORD_I, EC_WORD_CAN_T, EC_WORD_LOSE, EC_WORD_SO, EC_WORD_SOON, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_2A}
    },
    [FRONTIER_TRAINER_BRET] = {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("ברט"),
        .speechBefore = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_ROCK_SOLID, EC_WORD_POKEMON, EC_WORD_THE, EC_WORD_BEST},
        .speechWin = {EC_WORD_TOUGHNESS, EC_WORD_IS, EC_WORD_THE, EC_WORD_WAY, EC_WORD_TO, EC_WORD_GO},
        .speechLose = {EC_WORD_I, EC_WORD_ALSO, EC_WORD_HAVE, EC_WORD_A, EC_WORD_PLUSH_DOLL, EC_WORD_COLLECTION},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_2B}
    },
    [FRONTIER_TRAINER_RAUL] = {
        .facilityClass = FACILITY_CLASS_BLACK_BELT,
        .trainerName = _("ראול"),
        .speechBefore = {EC_WORD_I, EC_WORD_REJECT, EC_WORD_EVERY, EC_WORD_WEAK, EC_WORD_TRAINER, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_HUMPH, EC_WORD_EXCL, EC_WORD_ANOTHER, EC_WORD_WEAK, EC_WORD_TRAINER, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_THERE, EC_WORD_IS, EC_WORD_NOTHING, EC_WORD_WEAK, EC_WORD_ABOUT, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_2C}
    },
    [FRONTIER_TRAINER_KAY] = {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("קיי"),
        .speechBefore = {EC_WORD_AND, EC_WORD_YET, EC_WORD_ANOTHER, EC_WORD_BATTLE, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_WON, EC_WORD_BUT, EC_WORD_I_AM, EC_WORD_TIRED, EC_WORD_ELLIPSIS},
        .speechLose = {EC_WORD_GOOD, EC_WORD_IT_S, EC_WORD_OVER, EC_WORD_AT, EC_WORD_LAST, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_BATTLE_GIRL_2A}
    },
    [FRONTIER_TRAINER_ELENA] = {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("אלנה"),
        .speechBefore = {EC_WORD_A, EC_WORD_BATTLE, EC_WORD_GIRL, EC_WORD_THAT_S, EC_WORD_ME, EC_WORD_EXCL},
        .speechWin = {EC_WORD_ISN_T, EC_WORD_A, EC_WORD_BATTLE, EC_WORD_GIRL, EC_WORD_AWESOME, EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU, EC_WORD_DISLIKE, EC_WORD_A, EC_WORD_BATTLE, EC_WORD_GIRL, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_2B}
    },
    [FRONTIER_TRAINER_ALANA] = {
        .facilityClass = FACILITY_CLASS_BATTLE_GIRL,
        .trainerName = _("אלאנה"),
        .speechBefore = {EC_WORD_EAT, EC_WORD_MY, EC_WORD_INVINCIBLE, EC_WORD_ATTACK, EC_WORD_YOU, EC_WORD_EXCL},
        .speechWin = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_MUCH, EC_WORD_TO, EC_WORD_LEARN, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_SO, EC_WORD_MUCH, EC_WORD_FOR, EC_WORD_MY, EC_WORD_INVINCIBLE, EC_WORD_ATTACK},
        .monSet = (const u16[]){FRONTIER_MONS_BLACK_BELT_BATTLE_GIRL_2C}
    },
    [FRONTIER_TRAINER_ALEXAS] = {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("אלכסס"),
        .speechBefore = {EC_WORD_GOOD, EC_WORD_TO, EC_WORD_MEET_YOU, EC_WORD_YOUNG, EC_WORD_TRAINER, EC_WORD_EXCL},
        .speechWin = {EC_WORD_WAHAHAHA, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_GIVE, EC_WORD_IT, EC_WORD_UP},
        .speechLose = {EC_WORD_YOU, EC_WORD_ARE, EC_WORD_A, EC_WORD_STRONG, EC_WORD_TRAINER, EC_WORD_KID},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_2A(TYRANITAR)}
    },
    [FRONTIER_TRAINER_WESTON] = {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("ווסטון"),
        .speechBefore = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_PLAY, EC_WORD_DOWN, EC_WORD_ALL_RIGHT, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU_RE, EC_WORD_FAR, EC_WORD_TOO, EC_WORD_EASY, EC_WORD_TO, EC_WORD_ATTACK},
        .speechLose = {EC_WORD_WELL, EC_WORD_WELL, EC_WORD_ELLIPSIS, EC_WORD_I, EC_WORD_SURRENDER, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_2B(LATIOS)}
    },
    [FRONTIER_TRAINER_JASPER] = {
        .facilityClass = FACILITY_CLASS_EXPERT_M,
        .trainerName = _("ג'ספר"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_OLD, EC_WORD_I_AM, EC_WORD_SKILLED, EC_WORD_EXCL},
        .speechWin = {EC_WORD_SKILLED, EC_WORD_THAT_S, EC_WORD_WHAT, EC_WORD_I_AM, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I_AM, EC_WORD_SHOCKED, EC_WORD_EXCL, EC_WORD_DOWN, EC_WORD_I, EC_WORD_GO},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_2C(TYRANITAR)}
    },
    [FRONTIER_TRAINER_NADIA] = {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("נדיה"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_CAN_T, EC_WORD_BEAT, EC_WORD_ME, EC_WORD_DOWN, EC_WORD_EXCL},
        .speechWin = {EC_WORD_HAH, EC_WORD_EXCL, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_BEAT, EC_WORD_YOU},
        .speechLose = {EC_WORD_I_AM, EC_MOVE2(BEAT_UP), EC_WORD_AND, EC_WORD_DOWNCAST, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_2A(DRAGONITE)}
    },
    [FRONTIER_TRAINER_MIRANDA] = {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("מירנדה"),
        .speechBefore = {EC_WORD_WELL, EC_WORD_WELL, EC_EMPTY_WORD, EC_WORD_LET_S, EC_WORD_START, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WHAT, EC_WORD_QUES, EC_WORD_DONE, EC_WORD_SO, EC_WORD_SOON, EC_WORD_QUES},
        .speechLose = {EC_WORD_WELL, EC_WORD_I, EC_WORD_SEE, EC_WORD_THAT, EC_WORD_I_AM, EC_WORD_TOO_WEAK},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_2B(LATIAS)}
    },
    [FRONTIER_TRAINER_EMMA] = {
        .facilityClass = FACILITY_CLASS_EXPERT_F,
        .trainerName = _("אמה"),
        .speechBefore = {EC_WORD_I_VE, EC_WORD_BEEN, EC_WORD_HEARING, EC_WORD_ABOUT, EC_WORD_YOU, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_THINK, EC_WORD_I_VE, EC_WORD_MISHEARD, EC_WORD_THINGS, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WHAT, EC_WORD_I_VE, EC_WORD_BEEN, EC_WORD_HEARING, EC_WORD_IS, EC_WORD_RIGHT},
        .monSet = (const u16[]){FRONTIER_MONS_EXPERT_2C(DRAGONITE)}
    },
    [FRONTIER_TRAINER_ROLANDO] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("רולנדו"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_A, EC_WORD_SUPER, EC_WORD_POKEMON, EC_WORD_HERO, EC_WORD_EXCL},
        .speechWin = {EC_WORD_WAS, EC_WORD_THAT, EC_WORD_ENOUGH, EC_WORD_FOR, EC_WORD_YOU, EC_WORD_QUES},
        .speechLose = {EC_WORD_YOU, EC_WORD_SHOULD, EC_WORD_NOT, EC_WORD_BEAT, EC_WORD_A, EC_WORD_HERO},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_2(LATIOS, ARTICUNO, ZAPDOS, MOLTRES)}
    },
    [FRONTIER_TRAINER_STANLY] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("סטנלי"),
        .speechBefore = {EC_WORD_THIS, EC_WORD_SHOULD, EC_WORD_BE, EC_WORD_AN, EC_WORD_EASY, EC_WORD_MATCH},
        .speechWin = {EC_WORD_IT, EC_WORD_REALLY, EC_WORD_WAS, EC_WORD_EASY, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_ARE, EC_WORD_YOU, EC_WORD_HAPPY, EC_WORD_NOW, EC_WORD_QUES, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_2(LATIOS, RAIKOU, ENTEI, SUICUNE)}
    },
    [FRONTIER_TRAINER_DARIO] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_M,
        .trainerName = _("דריו"),
        .speechBefore = {EC_WORD_MY, EC_MOVE2(FORESIGHT), EC_WORD_SAYS, EC_WORD_I, EC_WORD_WILL, EC_WORD_WIN},
        .speechWin = {EC_WORD_MY, EC_MOVE2(FORESIGHT), EC_WORD_HAS, EC_WORD_BEEN, EC_WORD_PERFECT, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_DIDN_T, EC_WORD_SEE, EC_WORD_THIS, EC_MOVE(REVERSAL), EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_2(LATIOS, REGIROCK, REGICE, REGISTEEL)}
    },
    [FRONTIER_TRAINER_KARLEE] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("קרלי"),
        .speechBefore = {EC_WORD_SOMETHING, EC_WORD_GOOD, EC_WORD_WILL, EC_WORD_COME, EC_WORD_OF, EC_WORD_THIS},
        .speechWin = {EC_WORD_YOU, EC_WORD_SEE, EC_WORD_QUES, EC_WORD_FANTASTIC, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_THAT, EC_WORD_SOMETHING, EC_WORD_GOOD, EC_WORD_WENT, EC_WORD_TO, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_2(LATIAS, ARTICUNO, ZAPDOS, MOLTRES)}
    },
    [FRONTIER_TRAINER_JAYLIN] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("ג'יילין"),
        .speechBefore = {EC_WORD_EVERY, EC_WORD_TRAINER, EC_WORD_HAS, EC_WORD_BEEN, EC_WORD_TOO_WEAK, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_IT_S, EC_WORD_MAKING, EC_WORD_ME, EC_MOVE(YAWN), EC_WORD_THAT, EC_WORD_BATTLE},
        .speechLose = {EC_WORD_I, EC_WORD_SLEPT, EC_WORD_AND, EC_WORD_SO, EC_WORD_I, EC_WORD_LOST},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_2(LATIAS, RAIKOU, ENTEI, SUICUNE)}
    },
    [FRONTIER_TRAINER_INGRID] = {
        .facilityClass = FACILITY_CLASS_PSYCHIC_F,
        .trainerName = _("אינגריד"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_A, EC_WORD_VERY, EC_WORD_MEAN, EC_WORD_TRAINER},
        .speechWin = {EC_WORD_WASN_T, EC_WORD_THAT, EC_WORD_A, EC_WORD_GOOD, EC_WORD_MATCH, EC_WORD_QUES},
        .speechLose = {EC_WORD_I, EC_WORD_LOST, EC_WORD_CAUSE, EC_WORD_YOU_RE, EC_WORD_MEAN, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_PSYCHIC_2(LATIAS, REGIROCK, REGICE, REGISTEEL)}
    },
    [FRONTIER_TRAINER_DELILAH] = {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("דלילה"),
        .speechBefore = {EC_WORD_DON_T, EC_MOVE(GRUDGE), EC_WORD_ME, EC_WORD_IF_I_WIN, EC_WORD_OK_QUES, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I_AM, EC_WORD_SORRY, EC_WORD_TO, EC_WORD_SEE, EC_WORD_YOU, EC_WORD_ANGRY},
        .speechLose = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_A, EC_MOVE(GRUDGE), EC_WORD_WITH, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_HEX_MANIAC_2A}
    },
    [FRONTIER_TRAINER_CARLY] = {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("קרלי"),
        .speechBefore = {EC_WORD_I, EC_WORD_WILL, EC_WORD_SCATTER, EC_WORD_SOME, EC_MOVE2(POISON_POWDER), EC_WORD_ABOUT},
        .speechWin = {EC_WORD_IT_S, EC_WORD_SCARY, EC_WORD_HOW, EC_WORD_MY, EC_WORD_STRATEGY, EC_WORD_WORKS},
        .speechLose = {EC_WORD_I, EC_WORD_DISLIKE, EC_WORD_YOU, EC_WORD_AND, EC_WORD_YOUR, EC_WORD_POKEMON},
        .monSet = (const u16[]){FRONTIER_MONS_HEX_MANIAC_2B}
    },
    [FRONTIER_TRAINER_LEXIE] = {
        .facilityClass = FACILITY_CLASS_HEX_MANIAC,
        .trainerName = _("לקסי"),
        .speechBefore = {EC_WORD_WANT, EC_WORD_TO, EC_WORD_SEE, EC_WORD_SCARY, EC_WORD_POKEMON, EC_WORD_QUES},
        .speechWin = {EC_WORD_WASN_T, EC_WORD_THAT, EC_WORD_SCARY, EC_WORD_EH_QUES, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_MORE, EC_WORD_SCARY, EC_WORD_THAN, EC_WORD_MY, EC_WORD_POKEMON},
        .monSet = (const u16[]){FRONTIER_MONS_HEX_MANIAC_2C}
    },
    [FRONTIER_TRAINER_MILLER] = {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("מילר"),
        .speechBefore = {EC_WORD_HELLO, EC_WORD_QUES, EC_EMPTY_WORD, EC_WORD_HELLO, EC_WORD_QUES_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_HELLO, EC_WORD_MOTHER, EC_WORD_EXCL, EC_WORD_I, EC_WORD_WON, EC_WORD_EXCL},
        .speechLose = {EC_WORD_MY, EC_WORD_PHONE, EC_WORD_ISN_T, EC_WORD_WORKING, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_POKEMANIAC_2A}
    },
    [FRONTIER_TRAINER_MARV] = {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("מארב"),
        .speechBefore = {EC_WORD_YOU, EC_WORD_CAN, EC_WORD_LOSE, EC_WORD_YOUR, EC_MOVE(SWAGGER), EC_WORD_NOW},
        .speechWin = {EC_WORD_THERE, EC_WORD_IS, EC_WORD_NO, EC_MOVE(SWAGGER), EC_WORD_LEFT, EC_WORD_EH_QUES},
        .speechLose = {EC_WORD_GO, EC_WORD_ON, EC_MOVE(SWAGGER), EC_WORD_ALL, EC_WORD_YOU, EC_WORD_WANT},
        .monSet = (const u16[]){FRONTIER_MONS_POKEMANIAC_2B}
    },
    [FRONTIER_TRAINER_LAYTON] = {
        .facilityClass = FACILITY_CLASS_POKEMANIAC,
        .trainerName = _("לייטון"),
        .speechBefore = {EC_WORD_I, EC_WORD_KNOW, EC_WORD_I_AM, EC_WORD_TOTALLY, EC_WORD_COOL, EC_WORD_EXCL},
        .speechWin = {EC_WORD_YOU, EC_WORD_CAN, EC_WORD_LOOK, EC_WORD_UP, EC_WORD_TO, EC_WORD_ME},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_COOL, EC_WORD_EXCL, EC_WORD_NO, EC_WORD_REALLY, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_POKEMANIAC_2C}
    },
    [FRONTIER_TRAINER_BROOKS] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("ברוקס"),
        .speechBefore = {EC_WORD_THIS, EC_WORD_IS, EC_WORD_A, EC_WORD_HIGH, EC_WORD_LEVEL, EC_WORD_BATTLE},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_HIGH, EC_WORD_LEVEL, EC_WORD_AND, EC_WORD_EXCITING, EC_WORD_TOO},
        .speechLose = {EC_WORD_YOU_RE, EC_WORD_TOO, EC_WORD_HIGH, EC_WORD_IN, EC_WORD_LEVEL, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_A}
    },
    [FRONTIER_TRAINER_GREGORY] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("גרגורי"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_THAT, EC_WORD_OLD, EC_WORD_YET, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WHO, EC_WORD_SAYS, EC_WORD_I_AM, EC_WORD_TOO, EC_WORD_OLD, EC_WORD_QUES},
        .speechLose = {EC_WORD_PLEASE, EC_WORD_I_AM, EC_WORD_REALLY, EC_WORD_NOT, EC_WORD_THAT, EC_WORD_OLD},
        .monSet = (const u16[]){FRONTIER_MONS_GENTLEMAN_3A}
    },
    [FRONTIER_TRAINER_REESE] = {
        .facilityClass = FACILITY_CLASS_GENTLEMAN,
        .trainerName = _("ריס"),
        .speechBefore = {EC_WORD_I_VE, EC_WORD_A, EC_WORD_COUPLE, EC_WORD_THINGS, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_DON_T, EC_WORD_DIET, EC_WORD_PLAY, EC_WORD_SPORTS, EC_WORD_INSTEAD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_INSTEAD, EC_WORD_OF, EC_WORD_TELEVISION, EC_WORD_GET, EC_WORD_A, EC_WORD_BOOK},
        .monSet = (const u16[]){FRONTIER_MONS_GENTLEMAN_3B}
    },
    [FRONTIER_TRAINER_MASON] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_M,
        .trainerName = _("מייסון"),
        .speechBefore = {EC_WORD_PLEASE, EC_WORD_DON_T, EC_WORD_MAKE, EC_WORD_THIS, EC_WORD_SCARY, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THANK_YOU, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_WORD_I_AM, EC_WORD_HAPPY, EC_WORD_NOW},
        .speechLose = {EC_WORD_I_AM, EC_WORD_DISAPPOINTED, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_A}
    },
    [FRONTIER_TRAINER_TOBY] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_M,
        .trainerName = _("טובי"),
        .speechBefore = {EC_WORD_LISTEN, EC_WORD_UP, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_ALWAYS, EC_WORD_WIN},
        .speechWin = {EC_WORD_I_AM, EC_WORD_A, EC_WORD_GENIUS, EC_WORD_OR, EC_WORD_WHAT, EC_WORD_QUES},
        .speechLose = {EC_WORD_I, EC_WORD_CAN, EC_WORD_BEAT, EC_WORD_YOU, EC_WORD_AT, EC_WORD_SMARTNESS},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_B}
    },
    [FRONTIER_TRAINER_DOROTHY] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_F,
        .trainerName = _("דורותי"),
        .speechBefore = {EC_WORD_THE, EC_WORD_SPORTS, EC_WORD_WORLD, EC_WORD_SHOULD, EC_WORD_ACCEPT, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_THANK_YOU, EC_WORD_EXCL, EC_WORD_THAT, EC_WORD_WIN, EC_WORD_WAS, EC_WORD_REFRESHING},
        .speechLose = {EC_WORD_THANK_YOU, EC_WORD_EXCL, EC_WORD_THAT, EC_WORD_LOSS, EC_WORD_WAS, EC_WORD_REFRESHING},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_C}
    },
    [FRONTIER_TRAINER_PIPER] = {
        .facilityClass = FACILITY_CLASS_RUNNING_TRIATHLETE_F,
        .trainerName = _("פייפר"),
        .speechBefore = {EC_WORD_COME_ON, EC_WORD_YOU, EC_WORD_NEED, EC_WORD_A, EC_WORD_SPEED_BOOST, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_NEED, EC_WORD_TO, EC_WORD_SHOW, EC_WORD_MORE, EC_WORD_GUTS},
        .speechLose = {EC_WORD_OH, EC_WORD_YOU, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_D}
    },
    [FRONTIER_TRAINER_FINN] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
        .trainerName = _("פין"),
        .speechBefore = {EC_WORD_NOT, EC_WORD_ANOTHER, EC_WORD_TRAINER, EC_WORD_BATTLE, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WON_T, EC_WORD_THIS, EC_WORD_EVER, EC_WORD_END, EC_WORD_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_FINALLY, EC_WORD_GET, EC_WORD_TO, EC_MOVE2(REST), EC_WORD_A_LITTLE},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_M_3}
    },
    [FRONTIER_TRAINER_SAMIR] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_M,
        .trainerName = _("סמיר"),
        .speechBefore = {EC_WORD_I, EC_MOVE2(DIVE), EC_WORD_BELOW, EC_WORD_THE, EC_MOVE2(SURF), EC_WORD_EXCL},
        .speechWin = {EC_WORD_YAHOO, EC_WORD_TAKE, EC_WORD_A, EC_MOVE2(DIVE), EC_WORD_YOU, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_TO, EC_WORD_SINK, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_M_3}
    },
    [FRONTIER_TRAINER_FIONA] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
        .trainerName = _("פיונה"),
        .speechBefore = {EC_WORD_DID, EC_WORD_YOU, EC_WORD_LIMBER, EC_WORD_UP, EC_WORD_BEFORE, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_NEED, EC_WORD_TO, EC_WORD_BE, EC_WORD_MORE, EC_WORD_READY},
        .speechLose = {EC_WORD_BEING, EC_WORD_LIMBER, EC_WORD_DIDN_T, EC_WORD_WORK, EC_WORD_FOR, EC_WORD_ME},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_F_3}
    },
    [FRONTIER_TRAINER_GLORIA] = {
        .facilityClass = FACILITY_CLASS_SWIMMING_TRIATHLETE_F,
        .trainerName = _("גלוריה"),
        .speechBefore = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_TO, EC_WORD_ATTACK, EC_WORD_WITH, EC_WORD_SUCTION_CUPS},
        .speechWin = {EC_WORD_GIGGLE, EC_WORD_ELLIPSIS, EC_WORD_IT_S, EC_WORD_OVER, EC_WORD_FOR, EC_WORD_YOU},
        .speechLose = {EC_WORD_I, EC_WORD_DON_T, EC_WORD_GET, EC_WORD_HOW, EC_WORD_SUCTION_CUPS, EC_WORD_WORK},
        .monSet = (const u16[]){FRONTIER_MONS_SWIMMING_TRIATHLETE_F_3}
    },
    [FRONTIER_TRAINER_NICO] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_M,
        .trainerName = _("ניקו"),
        .speechBefore = {EC_WORD_LIKE, EC_WORD_A, EC_MOVE(SONIC_BOOM), EC_WORD_I_VE_ARRIVED, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_SORRY, EC_WORD_TO, EC_WORD_MAKE, EC_WORD_YOU, EC_WORD_SO, EC_WORD_DOWNCAST},
        .speechLose = {EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_WITH, EC_WORD_A, EC_MOVE2(SUPERSONIC), EC_WORD_SPEED_BOOST},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_A}
    },
    [FRONTIER_TRAINER_JEREMY] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_M,
        .trainerName = _("ג'רמי"),
        .speechBefore = {EC_WORD_A, EC_WORD_POKEMON, EC_WORD_MASTER, EC_WORD_THAT_S, EC_WORD_MY, EC_WORD_DREAM},
        .speechWin = {EC_WORD_MY, EC_WORD_DREAM, EC_WORD_ISN_T, EC_WORD_FAR, EC_WORD_OFF, EC_WORD_EXCL},
        .speechLose = {EC_WORD_WHAT, EC_WORD_I, EC_WORD_DREAM, EC_WORD_ISN_T, EC_WORD_HAPPENING, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_B}
    },
    [FRONTIER_TRAINER_CAITLIN] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_F,
        .trainerName = _("קייטלין"),
        .speechBefore = {EC_WORD_DON_T, EC_WORD_YOU, EC_WORD_THINK, EC_WORD_I_AM, EC_WORD_CUTE, EC_WORD_QUES},
        .speechWin = {EC_WORD_THERE, EC_WORD_IS, EC_WORD_MORE, EC_WORD_TO_ME, EC_WORD_THAN, EC_WORD_CUTENESS},
        .speechLose = {EC_WORD_MY, EC_WORD_CUTE_CHARM, EC_WORD_DOESN_T, EC_MOVE2(ATTRACT), EC_WORD_YOU, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_C}
    },
    [FRONTIER_TRAINER_REENA] = {
        .facilityClass = FACILITY_CLASS_CYCLING_TRIATHLETE_F,
        .trainerName = _("רינה"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_ALWAYS, EC_WORD_HAPPY, EC_WORD_HAPPY, EC_WORD_HAPPY, EC_WORD_EXCL},
        .speechWin = {EC_WORD_OH, EC_WORD_YAY, EC_WORD_EXCL, EC_WORD_YAHOO, EC_WORD_FOR, EC_WORD_ME},
        .speechLose = {EC_WORD_YAHOO, EC_WORD_EXCL, EC_WORD_I_AM, EC_WORD_HAPPY, EC_WORD_FOR, EC_WORD_YOU},
        .monSet = (const u16[]){FRONTIER_MONS_GENERAL_D}
    },
    [FRONTIER_TRAINER_AVERY] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("אייברי"),
        .speechBefore = {EC_WORD_I_VE, EC_WORD_GOT, EC_WORD_A_LOT, EC_WORD_OF, EC_WORD_BUG, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_MY, EC_WORD_BUG, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_ALL, EC_WORD_UNBELIEVABLE},
        .speechLose = {EC_WORD_MY, EC_WORD_BUG, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_ALL, EC_WORD_UPSIDE_DOWN},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_4}
    },
    [FRONTIER_TRAINER_LIAM] = {
        .facilityClass = FACILITY_CLASS_BUG_MANIAC,
        .trainerName = _("ליאם"),
        .speechBefore = {EC_WORD_WE, EC_WORD_REALLY, EC_WORD_DISLIKE, EC_WORD_FIRE, EC_WORD_AND, EC_WORD_FLYING},
        .speechWin = {EC_WORD_BUG, EC_WORD_POKEMON, EC_WORD_AREN_T, EC_WORD_BAD, EC_WORD_HEY_QUES, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU, EC_WORD_KNOW, EC_WORD_WHAT, EC_WORD_WE, EC_WORD_DISLIKE, EC_WORD_HEY_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_BUG_MANIAC_4}
    },
    [FRONTIER_TRAINER_THEO] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("תיאו"),
        .speechBefore = {EC_WORD_FISHING, EC_WORD_IS, EC_WORD_MY, EC_WORD_CHOICE, EC_WORD_IN, EC_WORD_LIFE},
        .speechWin = {EC_WORD_WATER, EC_WORD_POKEMON, EC_MOVE2(ATTRACT), EC_WORD_ME, EC_WORD_WITHOUT, EC_WORD_END},
        .speechLose = {EC_WORD_DON_T, EC_WORD_COUNT_ON, EC_WORD_THAT, EC_WORD_HAPPENING, EC_WORD_ANOTHER, EC_WORD_TIME},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_3}
    },
    [FRONTIER_TRAINER_BAILEY] = {
        .facilityClass = FACILITY_CLASS_FISHERMAN,
        .trainerName = _("ביילי"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_AN, EC_WORD_ADULT, EC_WORD_I, EC_WORD_BATTLE, EC_WORD_EASY},
        .speechWin = {EC_WORD_I_AM, EC_WORD_AN, EC_WORD_ADULT, EC_WORD_I, EC_MOVE2(SWALLOW), EC_WORD_JOY},
        .speechLose = {EC_WORD_I_AM, EC_WORD_AN, EC_WORD_ADULT, EC_WORD_I, EC_MOVE2(SWALLOW), EC_MOVE2(FRUSTRATION)},
        .monSet = (const u16[]){FRONTIER_MONS_FISHERMAN_3}
    },
    [FRONTIER_TRAINER_HUGO] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("הוגו"),
        .speechBefore = {EC_WORD_I, EC_WORD_TRY, EC_WORD_THE, EC_WORD_BEST, EC_WORD_I, EC_WORD_CAN},
        .speechWin = {EC_WORD_I, EC_WORD_CAN_WIN, EC_WORD_IF, EC_WORD_I, EC_WORD_TRY, EC_WORD_ENOUGH},
        .speechLose = {EC_WORD_I, EC_WORD_DID, EC_WORD_TRY, EC_WORD_DIDN_T, EC_WORD_I, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_4}
    },
    [FRONTIER_TRAINER_BRYCE] = {
        .facilityClass = FACILITY_CLASS_RUIN_MANIAC,
        .trainerName = _("ברייס"),
        .speechBefore = {EC_WORD_I_WAS, EC_WORD_ON, EC_WORD_VACATION, EC_WORD_UNTIL, EC_WORD_ONLY, EC_WORD_YESTERDAY},
        .speechWin = {EC_WORD_I, EC_WORD_HAVEN_T, EC_WORD_LOST, EC_WORD_MY, EC_WORD_SKILL, EC_WORD_YET},
        .speechLose = {EC_WORD_THAT_S, EC_WORD_IT, EC_WORD_ELLIPSIS, EC_WORD_I, EC_WORD_NEED, EC_WORD_SLEEP},
        .monSet = (const u16[]){FRONTIER_MONS_RUIN_MANIAC_4}
    },
    [FRONTIER_TRAINER_GIDEON] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("גדעון"),
        .speechBefore = {EC_WORD_WHAT_S_UP_QUES, EC_WORD_YOU, EC_WORD_THINK, EC_WORD_I_AM, EC_WORD_SCARY, EC_WORD_QUES},
        .speechWin = {EC_WORD_I_AM, EC_WORD_COOL, EC_WORD_BUT, EC_WORD_NOT, EC_WORD_SCARY, EC_WORD_EXCL},
        .speechLose = {EC_WORD_LOOK, EC_WORD_AT, EC_WORD_MY, EC_WORD_FABULOUS, EC_WORD_FASHION, EC_WORD_SENSE},
        .monSet = (const u16[]){FRONTIER_MONS_COLLECTOR_3}
    },
    [FRONTIER_TRAINER_TRISTON] = {
        .facilityClass = FACILITY_CLASS_COLLECTOR,
        .trainerName = _("טריסטן"),
        .speechBefore = {EC_WORD_I, EC_WORD_WOULD, EC_WORD_RATHER, EC_WORD_LOOK, EC_WORD_AT, EC_WORD_POKEMON},
        .speechWin = {EC_WORD_HUH_QUES, EC_WORD_YOU, EC_WORD_MEAN, EC_WORD_I, EC_WORD_WON, EC_WORD_QUES_EXCL},
        .speechLose = {EC_WORD_SEE, EC_WORD_QUES, EC_EMPTY_WORD, EC_WORD_I, EC_WORD_ALWAYS, EC_WORD_LOSE},
        .monSet = (const u16[]){FRONTIER_MONS_COLLECTOR_3}
    },
    [FRONTIER_TRAINER_CHARLES] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("צ'רלס"),
        .speechBefore = {EC_WORD_IT_S, EC_WORD_HOPELESS, EC_WORD_TO, EC_MOVE2(STRUGGLE), EC_WORD_WITH, EC_WORD_ME},
        .speechWin = {EC_MOVE(SUBMISSION), EC_WORD_WAS, EC_WORD_YOUR, EC_WORD_ONLY, EC_WORD_CHOICE, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I_AM, EC_WORD_GOING, EC_WORD_DOWN, EC_WORD_DOWN, EC_WORD_DOWN, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_3A}
    },
    [FRONTIER_TRAINER_RAYMOND] = {
        .facilityClass = FACILITY_CLASS_GUITARIST,
        .trainerName = _("ריימונד"),
        .speechBefore = {EC_WORD_WANT, EC_WORD_TO, EC_WORD_HEAR, EC_WORD_MY, EC_WORD_SONG, EC_WORD_QUES},
        .speechWin = {EC_WORD_SATISFIED, EC_WORD_THAT_S, EC_WORD_WHAT, EC_WORD_I_AM, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_SATISFIED, EC_WORD_IS, EC_WORD_WHAT, EC_WORD_I, EC_WORD_CAN_T, EC_WORD_BE},
        .monSet = (const u16[]){FRONTIER_MONS_GUITARIST_3B}
    },
    [FRONTIER_TRAINER_DIRK] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("דירק"),
        .speechBefore = {EC_WORD_FLYING, EC_WORD_POKEMON, EC_WORD_ARE, EC_WORD_ABOVE, EC_WORD_THE, EC_MOVE2(REST)},
        .speechWin = {EC_WORD_YOU, EC_WORD_CAN_T_WIN, EC_WORD_EXCL, EC_WORD_FLYING, EC_WORD_POKEMON, EC_WORD_RULE},
        .speechLose = {EC_WORD_AREN_T, EC_WORD_THERE, EC_WORD_MORE, EC_WORD_FLYING, EC_WORD_POKEMON, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_3}
    },
    [FRONTIER_TRAINER_HAROLD] = {
        .facilityClass = FACILITY_CLASS_BIRD_KEEPER,
        .trainerName = _("הרולד"),
        .speechBefore = {EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_APPEAL, EC_WORD_TO, EC_WORD_YOU, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_DO, EC_WORD_LIKE, EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_QUES},
        .speechLose = {EC_WORD_SO, EC_WORD_YOU, EC_WORD_DISLIKE, EC_WORD_MY, EC_WORD_POKEMON, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_BIRD_KEEPER_3}
    },
    [FRONTIER_TRAINER_OMAR] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("עומר"),
        .speechBefore = {EC_WORD_LET_ME_WIN, EC_WORD_IN, EC_MOVE(RETURN), EC_WORD_FOR, EC_WORD_A, EC_MOVE2(PRESENT)},
        .speechWin = {EC_WORD_HERE, EC_WORD_YOU, EC_WORD_ARE, EC_WORD_SOME, EC_MOVE2(TOXIC), EC_WORD_SWEETS},
        .speechLose = {EC_WORD_YOUR, EC_MOVE2(PRESENT), EC_WORD_QUES, EC_WORD_WHAT, EC_WORD_FOR, EC_WORD_QUES_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_3}
    },
    [FRONTIER_TRAINER_PETER] = {
        .facilityClass = FACILITY_CLASS_SAILOR,
        .trainerName = _("פיטר"),
        .speechBefore = {EC_WORD_I, EC_WORD_BRAG, EC_WORD_ABOUT, EC_WORD_MY, EC_WORD_HAPPINESS, EC_WORD_OK_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_TO, EC_WORD_LISTEN, EC_WORD_TO_ME, EC_WORD_BRAG},
        .speechLose = {EC_WORD_I_AM, EC_WORD_DISAPPOINTED, EC_WORD_YOU, EC_WORD_WON_T, EC_WORD_LISTEN, EC_WORD_TO_ME},
        .monSet = (const u16[]){FRONTIER_MONS_SAILOR_3}
    },
    [FRONTIER_TRAINER_DEV] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("דב"),
        .speechBefore = {EC_WORD_COME_ON, EC_WORD_LET_S, EC_WORD_GET, EC_WORD_A, EC_WORD_MOVE, EC_WORD_ON},
        .speechWin = {EC_WORD_I, EC_WORD_GET, EC_WORD_TO, EC_WORD_NAP, EC_WORD_AFTER, EC_WORD_THAT},
        .speechLose = {EC_WORD_I, EC_WORD_NEED, EC_WORD_TO, EC_WORD_NAP, EC_WORD_AFTER, EC_WORD_THAT},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_3}
    },
    [FRONTIER_TRAINER_COREY] = {
        .facilityClass = FACILITY_CLASS_HIKER,
        .trainerName = _("קורי"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_TEACH, EC_WORD_YOU, EC_WORD_HOW, EC_WORD_TOUGH, EC_WORD_I_AM},
        .speechWin = {EC_WORD_LOOK, EC_WORD_AT, EC_WORD_ME, EC_WORD_MAKE, EC_WORD_A, EC_MOVE(BRICK_BREAK)},
        .speechLose = {EC_WORD_MY, EC_MOVE2(FRUSTRATION), EC_WORD_IS, EC_WORD_CLOSE, EC_WORD_TO, EC_MOVE2(ERUPTION)},
        .monSet = (const u16[]){FRONTIER_MONS_HIKER_3}
    },
    [FRONTIER_TRAINER_ANDRE] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("אנדרה"),
        .speechBefore = {EC_WORD_NOW, EC_WORD_THIS, EC_WORD_IS, EC_WORD_A, EC_WORD_PERFECT, EC_WORD_FLAME_BODY},
        .speechWin = {EC_WORD_LOOK, EC_WORD_AT, EC_WORD_MY, EC_WORD_FIERY, EC_WORD_DANCE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOU, EC_WORD_WANT, EC_WORD_AN, EC_MOVE2(EXPLOSION), EC_WORD_HERE, EC_WORD_QUES},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_3}
    },
    [FRONTIER_TRAINER_FERRIS] = {
        .facilityClass = FACILITY_CLASS_KINDLER,
        .trainerName = _("פריס"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_NO_1, EC_WORD_IN, EC_WORD_THE, EC_WORD_OLD, EC_WORD_CLASS},
        .speechWin = {EC_WORD_NO_1, EC_WORD_THAT_S, EC_WORD_WHAT, EC_WORD_I_AM, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I_AM, EC_WORD_NOT, EC_WORD_NO_1, EC_WORD_ANY, EC_WORD_MORE, EC_WORD_ELLIPSIS},
        .monSet = (const u16[]){FRONTIER_MONS_KINDLER_3}
    },
    [FRONTIER_TRAINER_ALIVIA] = {
        .facilityClass = FACILITY_CLASS_PARASOL_LADY,
        .trainerName = _("אליביה"),
        .speechBefore = {EC_WORD_I_AM, EC_WORD_FEELING, EC_WORD_GIDDY, EC_WORD_SO, EC_WORD_SHOULD, EC_WORD_YOU},
        .speechWin = {EC_WORD_IT, EC_WORD_WAS, EC_WORD_ALL, EC_WORD_TOGETHER, EC_WORD_TOO, EC_WORD_EASY},
        .speechLose = {EC_WORD_I, EC_WORD_WILL, EC_WORD_GIDDY, EC_WORD_UP, EC_WORD_AND, EC_WORD_AWAY},
        .monSet = (const u16[]){FRONTIER_MONS_PARASOL_LADY_3}
    },
    [FRONTIER_TRAINER_PAIGE] = {
        .facilityClass = FACILITY_CLASS_PARASOL_LADY,
        .trainerName = _("פייג'"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_ENJOY, EC_WORD_OUR, EC_WORD_BATTLE, EC_WORD_TOGETHER, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THAT_S_IT_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_THANK_YOU, EC_WORD_VERY, EC_WORD_MUCH},
        .speechLose = {EC_WORD_THAT_S_IT_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_WORD_DO, EC_WORD_GO, EC_WORD_ON},
        .monSet = (const u16[]){FRONTIER_MONS_PARASOL_LADY_3}
    },
    [FRONTIER_TRAINER_ANYA] = {
        .facilityClass = FACILITY_CLASS_BEAUTY,
        .trainerName = _("אניה"),
        .speechBefore = {EC_WORD_I, EC_WORD_DISLIKE, EC_WORD_OH, EC_WORD_SO, EC_WORD_PRETTY, EC_WORD_FASHION},
        .speechWin = {EC_WORD_FASHION, EC_WORD_SHOULD, EC_WORD_MATCH, EC_WORD_THE, EC_WORD_PERSON, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_PRETTY, EC_WORD_COULD, EC_WORD_BE, EC_WORD_GOOD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_EEVEELUTIONS}
    },
    [FRONTIER_TRAINER_DAWN] = {
        .facilityClass = FACILITY_CLASS_BEAUTY,
        .trainerName = _("דון"),
        .speechBefore = {EC_WORD_I, EC_WORD_GO, EC_WORD_ALL, EC_WORD_OUT, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_DON_T, EC_WORD_BE, EC_WORD_A, EC_WORD_BABY, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOU, EC_WORD_WON, EC_WORD_EXCL, EC_WORD_MOVE, EC_WORD_ON, EC_WORD_EXCL},
        .monSet = (const u16[]){FRONTIER_MONS_BEAUTY_2}
    },
    [FRONTIER_TRAINER_ABBY] = {
        .facilityClass = FACILITY_CLASS_AROMA_LADY,
        .trainerName = _("אבי"),
        .speechBefore = {EC_WORD_I, EC_WORD_LIKE, EC_WORD_A, EC_WORD_TRAINER, EC_WORD_THAT_S, EC_WORD_REFRESHING},
        .speechWin = {EC_WORD_VICTORY, EC_WORD_HAS, EC_WORD_A, EC_MOVE(SWEET_SCENT), EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WHAT, EC_WORD_AN, EC_WORD_AWFUL, EC_WORD_STENCH, EC_WORD_EXCL, EC_EMPTY_WORD},
        .monSet = (const u16[]){FRONTIER_MONS_AROMA_LADY_3}
    },
    [FRONTIER_TRAINER_GRETEL] = {
        .facilityClass = FACILITY_CLASS_AROMA_LADY,
        .trainerName = _("גרטל"),
        .speechBefore = {EC_WORD_I, EC_WORD_CAUSE, EC_MOVE(OUTRAGE), EC_WORD_AS, EC_WORD_A, EC_WORD_TRAINER},
        .speechWin = {EC_WORD_IT_S, EC_WORD_ONLY, EC_WORD_NATURAL, EC_WORD_SEE_YA, EC_WORD_BYE_BYE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_IT_S, EC_WORD_HARD, EC_WORD_TO, EC_WORD_BELIEVE, EC_WORD_BUT, EC_WORD_CONGRATS},
        .monSet = (const u16[]){FRONTIER_MONS_AROMA_LADY_3}
    },
    [FRONTIER_TRAINER_LEADER_BROCK_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_BROCK_HNS,
        .trainerName = _("ברוק"),
        .speechBefore = {EC_WORD_I, EC_WORD_WILL, EC_WORD_ROCK, EC_WORD_YOUR, EC_WORD_WORLD, EC_WORD_EXCL},
        .speechWin = {EC_WORD_IT, EC_WORD_IS, EC_WORD_WHAT, EC_WORD_IT, EC_WORD_IS, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_IT, EC_WORD_IS, EC_WORD_WHAT, EC_WORD_IT, EC_WORD_IS, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS},
        .monSet = gBattleFrontierTrainerMons_Brock
    },
    [FRONTIER_TRAINER_LEADER_CHUCK_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_CHUCK_HNS,
        .trainerName = _("צ'אק"),
        .speechBefore = {EC_WORD_HEY_THERE, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_WHAT, EC_WORD_AN, EC_WORD_EASY, EC_WORD_FIGHT, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WHAT, EC_WORD_A, EC_WORD_TERRIBLE, EC_WORD_FIGHT, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Chuck
    },
    [FRONTIER_TRAINER_LEADER_LT_SURGE_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_LT_SURGE_HNS,
        .trainerName = _("סרג'"),
        .speechBefore = {EC_WORD_TODAY, EC_WORD_FORECAST, EC_WORD_IS, EC_WORD_ELECTRIC, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_TODAY, EC_WORD_I, EC_WORD_WIN, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_CANCEL, EC_WORD_TODAY, EC_WORD_FORECAST, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_LtSurge
    },
    [FRONTIER_TRAINER_LEADER_BLAINE_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_BLAINE_HNS,
        .trainerName = _("בליין"),
        .speechBefore = {EC_WORD_MY, EC_WORD_TRUMP_CARD, EC_WORD_IS, EC_WORD_DROUGHT, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MY, EC_WORD_FIRE, EC_WORD_TRUMP_CARD, EC_WORD_WORKS, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_MY, EC_WORD_FIRE, EC_WORD_TRUMP_CARD, EC_WORD_DOESN_T, EC_WORD_WORK, EC_WORD_EXCL},
        .monSet = gBattleFrontierTrainerMons_Blaine
    },
    [FRONTIER_TRAINER_LEADER_WHITNEY_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_WHITNEY_HNS,
        .trainerName = _("ויטני"),
        .speechBefore = {EC_WORD_HI, EC_WORD_SON, EC_WORD_ELLIPSIS, EC_WORD_LET_S, EC_WORD_FIGHT, EC_WORD_EXCL},
        .speechWin = {EC_WORD_AHAHA, EC_WORD_EXCL, EC_WORD_IT_S, EC_WORD_OKAY, EC_WORD_ELLIPSIS, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_YOUR, EC_WORD_MOTHER, EC_WORD_WILL, EC_WORD_BE, EC_WORD_HAPPY, EC_WORD_EXCL},
        .monSet = gBattleFrontierTrainerMons_Whitney
    },
    [FRONTIER_TRAINER_LEADER_FALKNER_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_FALKNER_HNS,
        .trainerName = _("פלקנר"),
        .speechBefore = {EC_WORD_GO, EC_WORD_FLYING, EC_WORD_FRIEND, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_MY, EC_WORD_FLYING, EC_WORD_SKILL, EC_WORD_HAS, EC_WORD_NO_MATCH, EC_WORD_EXCL},
        .speechLose = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_BEEN, EC_WORD_DESTROYED, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Falkner
    },
    [FRONTIER_TRAINER_LEADER_SABRINA_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_SABRINA_HNS,
        .trainerName = _("סברינה"),
        .speechBefore = {EC_WORD_GET, EC_WORD_READY, EC_WORD_TO_ME, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THAT_S, EC_WORD_TOO, EC_WORD_EASY, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_WHOAH, EC_WORD_EXCL, EC_WORD_I_VE, EC_WORD_BEEN, EC_WORD_DEFEATED, EC_WORD_EXCL},
        .monSet = gBattleFrontierTrainerMons_Sabrina
    },
    [FRONTIER_TRAINER_LEADER_JANINE_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_JANINE_HNS,
        .trainerName = _("ג'אנין"),
        .speechBefore = {EC_WORD_I, EC_WORD_AM, EC_WORD_STRONG, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THAT_WAS, EC_WORD_HARD, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_SIGH, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Janine
    },
    [FRONTIER_TRAINER_LEADER_MISTY_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_MISTY_HNS,
        .trainerName = _("מיסטי"),
        .speechBefore = {EC_WORD_WATER, EC_WORD_TYPE, EC_WORD_IS, EC_WORD_THE, EC_WORD_BEST, EC_WORD_ELLIPSIS},
        .speechWin = {EC_WORD_OH, EC_WORD_MY, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_AHAHA, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS, EC_WORD_WHAT, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Misty
    },
    [FRONTIER_TRAINER_LEADER_BUGSY_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_BUGSY_HNS,
        .trainerName = _("באגסי"),
        .speechBefore = {EC_WORD_BUG, EC_WORD_POWER, EC_WORD_IS, EC_WORD_INCREDIBLE, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_NOT, EC_WORD_BAD, EC_WORD_EXCL, EC_WORD_FOR, EC_WORD_ME, EC_WORD_EXCL},
        .speechLose = {EC_WORD_WHAT, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS, EC_WORD_YOU, EC_WORD_WERE, EC_WORD_BETTER, EC_WORD_ELLIPSIS},
        .monSet = gBattleFrontierTrainerMons_Bugsy
    },
    [FRONTIER_TRAINER_LEADER_JASMINE_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_JASMINE_HNS,
        .trainerName = _("ג'סמין"),
        .speechBefore = {EC_WORD_STEEL, EC_WORD_POWER, EC_WORD_IS, EC_WORD_INCREDIBLE, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_THERE, EC_WORD_WE, EC_WORD_GO, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_SORRY, EC_WORD_ELLIPSIS_ELLIPSIS_ELLIPSIS, EC_WORD_I, EC_WORD_WASN_T, EC_WORD_ENOUGH, EC_WORD_ELLIPSIS},
        .monSet = gBattleFrontierTrainerMons_Jasmine
    },
    [FRONTIER_TRAINER_LEADER_RED_HNS] = {
        .facilityClass = FACILITY_CLASS_RED,
        .trainerName = _("רד"),
        .speechBefore = {EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Red
    },
    [FRONTIER_TRAINER_LEADER_LEAF_HNS] = {
        .facilityClass = FACILITY_CLASS_LEAF,
        .trainerName = _("ליף"),
        .speechBefore = {EC_WORD_LET_S, EC_WORD_BATTLE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_WON, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_GOOD, EC_WORD_BATTLE, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Leaf
    },
    [FRONTIER_TRAINER_LEADER_BLUE_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_BLUE_HNS,
        .trainerName = _("בלו"),
        .speechBefore = {EC_WORD_HI, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_OH, EC_WORD_WHAT, EC_WORD_QUES_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_NEXT, EC_WORD_TIME, EC_WORD_WILL, EC_WORD_BE, EC_WORD_THE, EC_WORD_TIME},
        .monSet = gBattleFrontierTrainerMons_Blue
    },
    [FRONTIER_TRAINER_LEADER_ERIKA_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_ERIKA_HNS,
        .trainerName = _("אריקה"),
        .speechBefore = {EC_WORD_DO, EC_WORD_YOU, EC_WORD_LIKE, EC_WORD_MY, EC_WORD_POKEBLOCK, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOUR, EC_WORD_PARTY, EC_WORD_IS, EC_WORD_TOO, EC_WORD_SIMPLE, EC_WORD_EXCL},
        .speechLose = {EC_WORD_YOUR, EC_WORD_PARTY, EC_WORD_IS, EC_WORD_TOO, EC_WORD_STRONG, EC_WORD_EXCL},
        .monSet = gBattleFrontierTrainerMons_Erika
    },
    [FRONTIER_TRAINER_LEADER_PRYCE_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_PRYCE_HNS,
        .trainerName = _("פרייס"),
        .speechBefore = {EC_WORD_ICE, EC_WORD_IS, EC_WORD_HOT, EC_WORD_OR, EC_WORD_COLD, EC_WORD_QUES},
        .speechWin = {EC_WORD_YOU, EC_WORD_HAVE, EC_WORD_BEEN, EC_WORD_DEFEATED, EC_WORD_IN, EC_WORD_COLD},
        .speechLose = {EC_WORD_ICE, EC_WORD_IS, EC_WORD_COLD, EC_WORD_AND, EC_WORD_YOU, EC_WORD_TOO},
        .monSet = gBattleFrontierTrainerMons_Pryce
    },
    [FRONTIER_TRAINER_LEADER_MORTY_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_MORTY_HNS,
        .trainerName = _("מורטי"),
        .speechBefore = {EC_WORD_DON_T, EC_WORD_TALK, EC_WORD_JUST, EC_WORD_BATTLE, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_BYE_BYE, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_KTHX_BYE, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Morty
    },
    [FRONTIER_TRAINER_LEADER_CLAIR_HNS] = {
        .facilityClass = FACILITY_CLASS_LEADER_CLAIR_HNS,
        .trainerName = _("קלייר"),
        .speechBefore = {EC_WORD_MY, EC_WORD_HOBBY, EC_WORD_ARE, EC_WORD_DRAGON, EC_WORD_POKEMON, EC_WORD_EXCL},
        .speechWin = {EC_WORD_DRAGON, EC_WORD_POWER, EC_WORD_EXCL, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_DRAGON, EC_WORD_DESTROYED, EC_WORD_DRAGON, EC_WORD_DESTROYED, EC_WORD_EXCL_EXCL, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Clair
    },
    [FRONTIER_TRAINER_CHAMPION_LANCE_HNS] = {
        .facilityClass = FACILITY_CLASS_CHAMPION_LANCE_HNS,
        .trainerName = _("לאנס"),
        .speechBefore = {EC_WORD_I, EC_WORD_HAVE, EC_WORD_TO, EC_WORD_WIN, EC_WORD_EXCL, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_I, EC_WORD_WON, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_I, EC_WORD_LOST, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Lance
    },
    [FRONTIER_TRAINER_CHAMPION_STEVEN_HNS] = {
        .facilityClass = FACILITY_CLASS_CHAMPION_STEVEN_HNS,
        .trainerName = _("סטיבן"),
        .speechBefore = {EC_WORD_ROCK, EC_WORD_ARE, EC_WORD_COOL, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechWin = {EC_WORD_STEEL, EC_WORD_IS, EC_WORD_BETTER, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .speechLose = {EC_WORD_AWFUL, EC_WORD_ELLIPSIS, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD, EC_EMPTY_WORD},
        .monSet = gBattleFrontierTrainerMons_Steven
    }
};
