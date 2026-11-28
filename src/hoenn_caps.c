// Hoenn & Seek 2.0 (part 4a): level caps after the eighth Johto badge.
//
// HnS's challenge setting "LEVEL CAP" (Normal / Hard) caps levels by Johto
// badge (src/caps.c's tables), then jumps straight to 70 at Johto champion
// and removes the cap at Kanto champion. That left Kanto's eight gyms and
// all of Hoenn uncapped or flat. This file takes over once the eighth Johto
// badge is in: caps.c asks HoennGetPostJohtoLevelCap() for the HnS build.
//
// HOW THE CAP IS PICKED
//   Each stage of the game gives a cap, and the player gets the highest cap
//   of every stage they've reached. Taking the highest means the cap never
//   goes down, whatever order things are done in: Oak's ticket comes at 16
//   badges, so Hoenn can be started before the Kanto Elite Four rematch.
//
//   Stage                            Normal cap        Based on
//   8 Johto badges                   56 (caps.c)       Lance 56
//   Johto champion, n Kanto badges   sKantoCaps[n]     the n+1th lowest Kanto
//                                                      leader ace (60 .. 69),
//                                                      then the E4 rematch 70
//   Kanto champion                   70                never lower the cap
//   n Hoenn badges (0-7)             the next Hoenn    gyms scale 68 -> 78 by
//                                    leader's ace,     badge count
//                                    at least 70 + n   (src/hoenn_scaling.c)
//   8 Hoenn badges                   84                E4 76-81, Wallace 84
//   Beat Wallace                     no cap            Brendan & May, Red, ...
//
//   Kanto gyms can be done in any order, so the Kanto cap goes by how many
//   Kanto badges you have and steps through the leaders' aces from lowest to
//   highest. Hoenn gyms scale with your stamp count, so their cap follows
//   the same formula as the next leader's ace (HoennGymAceLevel()).
//
// HARD MODE is the same table minus HOENN_CAP_HARD_GAP (2) levels. Johto's
// own Hard table (in caps.c) is HnS's and unchanged.
//
// Everything after Wallace stays uncapped: Mt. Silver, the Sinjoh story and
// its Lv 70-79 rematch teams all open after Brendan & May (part 16a), which
// comes after Wallace.

#include "global.h"
#include "event_data.h"
#include "hoenn.h"
#include "hoenn_caps.h"
#include "pokemon.h"
#include "constants/hoenn_custom.h"

#if IS_HNS

#define HOENN_CAP_HARD_GAP          2
#define HOENN_CAP_KANTO_CHAMPION    70  // never lower than the Kanto E4 rematch cap
#define HOENN_CAP_HOENN_E4          84  // Wallace's ace

// Johto champion, by number of Kanto badges (0-8). The Kanto leaders' aces in
// trainers_hns.party, lowest first: Lt. Surge 60, Erika 62, Misty 63,
// Janine 64, Brock 66, Sabrina 66, Blaine 67, Blue 69; then the Kanto E4
// rematch (68-69, Lance 70).
static const u8 sKantoCaps[] = { 60, 62, 63, 64, 66, 66, 67, 69, 70 };

// Badges 9-16 are Kanto's in HnS (Brock's is FLAG_BADGE09_GET).
static u32 CountKantoBadges(void)
{
    u32 i, count = 0;

    for (i = FLAG_BADGE09_GET; i <= FLAG_BADGE16_GET; i++)
        if (FlagGet(i))
            count++;
    return count;
}

// The Hoenn cap with n stamps: the next leader's ace (HoennGymAceLevel() is
// that ace for the current stamp count), but always at least 70 + n, so each
// badge raises the cap by one or more.
static u32 HoennBadgeCap(void)
{
    u32 stamps = HoennCountStamps();
    u32 cap;

    if (stamps >= HOENN_GYM_COUNT)
        return HOENN_CAP_HOENN_E4;
    cap = HoennGymAceLevel();
    if (cap < HOENN_CAP_KANTO_CHAMPION + stamps)
        cap = HOENN_CAP_KANTO_CHAMPION + stamps;
    return cap;
}

// Called by GetCurrentLevelCap() (src/caps.c) once the player has all eight
// Johto badges, with the cap the Johto table gives (56, or 54 on Hard).
// hard: TRUE for the Hard setting.
u32 HoennGetPostJohtoLevelCap(u32 johtoCap, bool32 hard)
{
    u32 cap = 0;

    if (FlagGet(FLAG_HOENN_STAMP_WALLACE))
        return MAX_LEVEL;

    if (FlagGet(FLAG_IS_CHAMPION))
        cap = sKantoCaps[CountKantoBadges()];
    if (FlagGet(FLAG_IS_KANTO_CHAMPION) && cap < HOENN_CAP_KANTO_CHAMPION)
        cap = HOENN_CAP_KANTO_CHAMPION;
    // Hoenn counts once you could be there: Kanto champion, or any stamp
    // (Oak's ticket only needs 16 badges).
    if (FlagGet(FLAG_IS_KANTO_CHAMPION) || HoennCountStamps() != 0)
    {
        u32 hoenn = HoennBadgeCap();
        if (cap < hoenn)
            cap = hoenn;
    }

    if (cap == 0)  // eight Johto badges, not champion yet: HnS's table
        return johtoCap;
    if (hard)
        cap -= HOENN_CAP_HARD_GAP;
    // Never below the Johto cap the player already had.
    return cap < johtoCap ? johtoCap : cap;
}

#endif // IS_HNS
