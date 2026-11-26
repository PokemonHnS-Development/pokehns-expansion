#ifndef GUARD_HOENN_HINTS_H
#define GUARD_HOENN_HINTS_H

// Hoenn & Seek 2.0 (part 7): NPC hint lines, rumors, field notes and forecasts.
// Code and design: src/hoenn_hints.c. Data: data/hoenn/npc_hints.json.

#if IS_HNS
struct ScriptContext;
// callnatives used by data/scripts/hoenn_hints.inc (generated)
void HoennSeek_NpcHint(struct ScriptContext *ctx);
void HoennSeek_FieldNotesCount(struct ScriptContext *ctx);
void HoennSeek_FieldNotesHint(struct ScriptContext *ctx);
void HoennSeek_Forecast(struct ScriptContext *ctx);
#endif

#endif // GUARD_HOENN_HINTS_H
