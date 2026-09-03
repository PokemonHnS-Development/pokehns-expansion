#ifndef GUARD_CONFIG_POKEDEX_PLUS_HGSS_H
#define GUARD_CONFIG_POKEDEX_PLUS_HGSS_H

#define POKEDEX_PLUS_HGSS                   TRUE // If TRUE, enables the custom HGSS style Pokedex.
#define HGSS_DECAPPED                       FALSE // If TRUE, uses decapped gfx and strings.
#define HGSS_DARK_MODE                      FALSE // If TRUE, enables dark mode.
#define HGSS_HIDE_UNSEEN_EVOLUTION_NAMES    FALSE // If TRUE, hides evolution mon names.
#define HGSS_HIDE_UNOWNED_EVOLUTION_METHODS FALSE // If TRUE, hides evolution methods.
#define HGSS_SORT_TMS_BY_NUM                TRUE // If TRUE, sorts the TMS in HGSS Dex by TM number, rather than alphabetically.
#define HGSS_SHOW_EGG_MOVES_FOR_EVOS        TRUE // If TRUE, shows Egg Moves for evolved Pokémon too.

// For modifying behaviour of the stats screen move list
#define REVERSE_MOVES_DIRECTION             TRUE // If TRUE, Reversed Movement: Up on d-pad increments list, If FALSE, default: Down on d-pad increments list
#define LOOP_MOVES_LIST                     TRUE // If TRUE, Looped List: List continues infinitely, If FALSE, default: List stops at 1 and at max moves

// For modifying whether to use original numbers or summarised values
#define CATCH_RATE_NUMBER                   TRUE // If TRUE, uses numeric catch rate, If FALSE, uses text labels instead
#define FRIENDSHIP_BASE_NUMBER              TRUE // If TRUE, uses numeric base friendship rate, If FALSE, uses emoji instead
#define EGG_CYCLES_NUMBER                   TRUE // If TRUE, uses numeric egg cycles rate, If FALSE, uses egg icons instead

#if IS_HNS
#define SEPARATE_OBTAINABLE_DEX             TRUE
#else
#define SEPARATE_OBTAINABLE_DEX             FALSE
#endif

#endif // GUARD_CONFIG_POKEDEX_PLUS_HGSS_H
