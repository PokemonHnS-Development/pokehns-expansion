#ifndef GUARD_HELP_WINDOW_H
#define GUARD_HELP_WINDOW_H

#include "global.h"
#include "script.h"
#include "text.h"
#include "constants/help_window.h"

struct HelpWindow
{
    const u8 *header;
    const u8 *desc;
    u8 headerFont;
    u8 descFont;
};

extern const struct HelpWindow gHelpWindowInfo[];

void ShowHelpInfoWindow(struct ScriptContext *ctx);
void HideHelpInfoWindow(void);

#endif //GUARD_HELP_WINDOW_H
