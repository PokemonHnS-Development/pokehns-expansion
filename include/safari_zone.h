#ifndef GUARD_SAFARI_ZONE_H
#define GUARD_SAFARI_ZONE_H

// Steps allowed in a single Safari Game before "Ding-dong! Time's up!".
// NOTE: the FRLG build shows the step count in the start menu with a 3-digit
// conversion (see ShowSafariBallsWindow), so raising SAFARI_ZONE_STEPS_FRLG
// past 999 also means widening that display.
#define SAFARI_ZONE_STEPS_FRLG 600
#define SAFARI_ZONE_STEPS_HNS  1000
#define SAFARI_ZONE_STEPS      500

extern u8 gNumSafariBalls;
extern u16 gSafariZoneStepCounter;

bool32 GetSafariZoneFlag(void);
void SetSafariZoneFlag(void);
void ResetSafariZoneFlag(void);

void EnterSafariMode(void);
void ExitSafariMode(void);

bool8 SafariZoneTakeStep(void);
void SafariZoneRetirePrompt(void);

void CB2_EndSafariBattle(void);

struct Pokeblock *SafariZoneGetActivePokeblock(void);
void SafariZoneActivatePokeblockFeeder(u8 pkblId);

#endif // GUARD_SAFARI_ZONE_H
