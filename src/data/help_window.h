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
        .descFont = FONT_NORMAL
    },
    // Add more entries
};
