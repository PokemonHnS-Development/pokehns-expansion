#ifndef GUARD_POKE_RADAR_H
#define GUARD_POKE_RADAR_H

#include "global.h"

#define MON_ICON_TAG 0x4000
#define ENCOUNTER_TYPE_TAG 0x4001
#define CAPTURED_ALL_TAG 0x4002

void OpenPokeRadar(void);
bool32 IsPokeRadarEnabled(void);

#endif //GUARD_POKE_RADAR_H