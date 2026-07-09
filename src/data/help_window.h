// Add entries here
// These entries are example entries which you can replace, but they exist to get you started.
// Remember to modify include/constants/help_window.h to include identifiers so they can be used in event scripts.
const struct HelpWindow gHelpWindowInfo[] =
{
    [HELP_DEMO_WINDOW] =
    {
        .header = COMPOUND_STRING("Information: Help Windows"),
        .desc = COMPOUND_STRING("This is a help window. You can put\n"
                                "lots of text on the screen that\n"
                                "players won't read!\n\nIsn't that great!"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 4, 5},
    },
    [HELP_TRADE_WINDOW] =
    {
        .header = COMPOUND_STRING("WARNING: COMPATIBILITY"),
        .desc = COMPOUND_STRING("Attempting to link with a game\n"
                                "that is not Heart & Soul may result\n"
                                "in permanent damage to your save file.\n"
                                "Only continue if you are linking with\n"
                                "a copy of Heart & Soul that is on the\n"
                                "same version as your current copy."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 4, 5},
    },
    [HELP_TELEPORTER_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: MACHINE"),
        .desc = COMPOUND_STRING("This machine can PERMANENTLY change\n"
                                "POKéMON into their GALARIAN forms.\n"
                                "GALARIAN forms are NOT required\n"
                                "for story progression or\n"
                                "NATIONAL POKéDEX completion.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_SINJOH_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: SINJOH"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "bonus content: SINJOH.\n"
                                "It is NOT required for story\n"
                                "or NATIONAL POKéDEX completion.\n"
                                "\n"
                                "It's just a bonus. If you want it."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_ALOLA_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: ISLES"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "bonus content: ISLES.\n"
                                "It is NOT required for story\n"
                                "or NATIONAL POKéDEX completion.\n"
                                "\n"
                                "It's just a bonus. If you want it."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE1_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON ABILITIES"),
        .desc = COMPOUND_STRING("PICHU's ability is STATIC.\n"
                                "CLEFFA's ability is CUTE CHARM.\n"
                                "IGGLYBUFF's ability is CUTE CHARM.\n"
                                "TYROGUE's ability is GUTS.\n"
                                "SMOOCHUM's ability is OBLIVIOUS.\n"
                                "ELEKID's ability is STATIC.\n"
                                "MAGBY's ability is FLAME BODY."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE2_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON TYPES"),
        .desc = COMPOUND_STRING("PICHU is ELECTRIC type.\n"
                                "CLEFFA is NORMAL type.\n"
                                "IGGLYBUFF is NORMAL type.\n"
                                "TYROGUE is FIGHTING type.\n"
                                "SMOOCHUM is ICE type.\n"
                                "ELEKID is ELECTRIC type.\n"
                                "MAGBY is FIRE type."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE3_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON CRIES"),
        .desc = COMPOUND_STRING("PICHU says WAAAH.\n"
                                "CLEFFA says EEK.\n"
                                "IGGLYBUFF says LALALA.\n"
                                "TYROGUE says HIYAH.\n"
                                "SMOOCHUM says EHEHE.\n"
                                "ELEKID says OI, OI, OI.\n"
                                "MAGBY says TCH."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE4_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON ACTIONS"),
        .desc = COMPOUND_STRING("PICHU likes to PLAY all day.\n"
                                "CLEFFA LOOKS at the moon.\n"
                                "IGGLYBUFF puts them to SLEEP.\n"
                                "TYROGUE TRAINS constantly.\n"
                                "SMOOCHUM likes to SHOW off.\n"
                                "ELEKID STORES up charge.\n"
                                "MAGBY often ANGERS."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    // Add more entries
};
