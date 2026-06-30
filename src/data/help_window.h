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
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: 1/3"),
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
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: 3/3"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "bonus content: SINJOH.\n"
                                "It is NOT required for story\n"
                                "progress, and it is NOT required\n"
                                "for POKéDEX completion.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_ALOLA_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: 2/3"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "bonus content: ALOLA ISLES.\n"
                                "It is NOT required for story\n"
                                "progress, and it is NOT required\n"
                                "for NATIONAL POKéDEX completion.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    // Add more entries
};
