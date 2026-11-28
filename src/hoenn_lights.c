// Hoenn & Seek 2.0 (part 25a): follow-the-lights.
//
// A glowing Pokémon object waits at the start of a path. When the player comes
// within `near` tiles of it (in any direction), it drifts on to the next stop
// along a fixed route while the player keeps control. At the last stop the
// path's end script runs. If the player strays more than `lost` tiles from the
// light once it has moved, the lights "scatter": the light goes back to the
// start and a short script says so.
//
// Paths live in data/hoenn/light_paths.json; tools/hoenn/gen_hoenn_lights.py
// finds each route on the map's layout and writes src/data/hoenn_light_paths.h.
// The Night Dive on Underwater Route 124 (part 25a) is the first path; the
// Lanturn lights on Route 41 (part 32, the Lugia chain) are the second.
//
// State:
// - The path's stage var (a VAR_TEMP_*, so it resets on every map load, like
//   the object itself) holds the index of the stop the light is at or heading
//   to. The light's position is taken from that stop, never from the object:
//   an object that leaves the screen is removed and later respawned from its
//   template, so the template's coords are moved with each drift too.
// - A drift is a task that walks the object one tile at a time. If the object
//   goes off screen or a battle resets the tasks mid-drift, nothing is lost:
//   the var and the template already say where the light ended up.
// - Whether the light is out at all is its object's flag (the map's
//   OnTransition decides it), so this code never needs to know the time.
//
// Hook: HoennLightsOnStep() runs on every player step from
// TryStartStepCountScript (src/field_control_avatar.c).
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "overworld.h"
#include "script.h"
#include "task.h"
#include "hoenn.h"
#include "constants/event_object_movement.h"
#include "constants/map_groups.h"
#include "constants/map_event_ids.h"
#include "constants/vars.h"

#if IS_HNS
#include "constants/hoenn_events.h"

struct HoennLightStop
{
    u16 routeIdx; // steps along the route from the start to this stop
    u8 x, y;      // map coords (no MAP_OFFSET)
};

struct HoennLightPath
{
    u16 map;      // MAP_* (group << 8 | num)
    u8 localId;   // the light object
    const u8 *route;               // one DIR_* per step, start to end
    const struct HoennLightStop *stops;
    u8 stopCount;
    u8 near;      // the light moves on when the player is this close
    u8 lost;      // the lights scatter when the player is farther than this
    u16 stageVar; // current stop index
    const u8 *endScript;
};

extern const u8 HoennSeek_EventScript_LightsScatter[];

#include "data/hoenn_light_paths.h"

#define tPath     data[0]
#define tRouteIdx data[1]
#define tRouteEnd data[2]

static const struct HoennLightPath *GetPathHere(u32 *index)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHoennLightPaths); i++)
    {
        if (gSaveBlock1Ptr->location.mapGroup == (sHoennLightPaths[i].map >> 8)
         && gSaveBlock1Ptr->location.mapNum == (sHoennLightPaths[i].map & 0xFF))
        {
            *index = i;
            return &sHoennLightPaths[i];
        }
    }
    return NULL;
}

// The light is out when its object exists in the map and its flag is clear.
static bool32 IsLightOut(const struct HoennLightPath *path)
{
    const struct ObjectEventTemplate *template = GetObjectEventTemplateByLocalIdAndMap(path->localId,
        gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);

    return template != NULL && !FlagGet(template->flagId);
}

static void Task_HoennLightDrift(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    const struct HoennLightPath *path = &sHoennLightPaths[tPath];
    u32 here;
    u8 objId;
    struct ObjectEvent *obj;

    // Left the map, or the light went off screen: the template already holds
    // the stop it was heading to, so it reappears there.
    if (GetPathHere(&here) != path
     || TryGetObjectEventIdByLocalIdAndMap(path->localId, gSaveBlock1Ptr->location.mapNum,
                                           gSaveBlock1Ptr->location.mapGroup, &objId))
    {
        DestroyTask(taskId);
        return;
    }
    obj = &gObjectEvents[objId];
    if (ObjectEventIsMovementOverridden(obj) && !ObjectEventClearHeldMovementIfFinished(obj))
        return; // still walking the last tile
    if (tRouteIdx >= tRouteEnd)
    {
        DestroyTask(taskId);
        return;
    }
    // Walks don't check collision, so a light whose route crosses the player
    // drifts through them for one tile. It's a light; that's fine.
    ObjectEventSetHeldMovement(obj, GetWalkNormalMovementAction(path->route[tRouteIdx++]));
}

static bool32 IsDrifting(void)
{
    return FuncIsActiveTask(Task_HoennLightDrift);
}

static u32 Distance(s16 x, s16 y, const struct HoennLightStop *stop)
{
    s32 dx = x - stop->x, dy = y - stop->y;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    return dx > dy ? dx : dy;
}

// Returns TRUE when it started a script (the end of the path, or the scatter).
bool32 HoennLightsOnStep(void)
{
    u32 index, stage, dist;
    s16 x, y;
    u8 taskId;
    const struct HoennLightPath *path = GetPathHere(&index);

    if (path == NULL || IsDrifting() || !IsLightOut(path))
        return FALSE;

    PlayerGetDestCoords(&x, &y);
    x -= MAP_OFFSET;
    y -= MAP_OFFSET;
    stage = VarGet(path->stageVar);
    if (stage >= path->stopCount)
        stage = 0;
    dist = Distance(x, y, &path->stops[stage]);

    if (dist <= path->near)
    {
        if (stage == path->stopCount - 1u)
        {
            gSpecialVar_0x8005 = path->localId;
            ScriptContext_SetupScript(path->endScript);
            return TRUE;
        }
        // Drift on to the next stop. The var and the template move first, so a
        // drift that's cut short still ends with the light at its stop.
        VarSet(path->stageVar, stage + 1);
        SetObjEventTemplateCoords(path->localId, path->stops[stage + 1].x, path->stops[stage + 1].y);
        taskId = CreateTask(Task_HoennLightDrift, 80);
        gTasks[taskId].tPath = index;
        gTasks[taskId].tRouteIdx = path->stops[stage].routeIdx;
        gTasks[taskId].tRouteEnd = path->stops[stage + 1].routeIdx;
        return FALSE;
    }

    if (stage > 0 && dist > path->lost)
    {
        // A wrong turn: back to the start. The script only tells the player.
        VarSet(path->stageVar, 0);
        SetObjEventTemplateCoords(path->localId, path->stops[0].x, path->stops[0].y);
        TryMoveObjectEventToMapCoords(path->localId, gSaveBlock1Ptr->location.mapNum,
                                      gSaveBlock1Ptr->location.mapGroup, path->stops[0].x, path->stops[0].y);
        gSpecialVar_0x8005 = path->localId;
        ScriptContext_SetupScript(HoennSeek_EventScript_LightsScatter);
        return TRUE;
    }
    return FALSE;
}

#endif // IS_HNS
