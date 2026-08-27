#ifndef GUARD_UI_SCREENSHOTS
#define GUARD_UI_SCREENSHOTS

#include "main.h"

void Task_OpenScreenshots(u8 taskId);
void Screenshots_Init(MainCallback callback);
void Screenshots_StartMenuInitCB(void);


enum Screenshots
{
    SCREENSHOT_ALOLA_MAP,
};


#endif // GUARD_UI_MENU_H
