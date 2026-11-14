#ifndef GUARD_CONFIG_TEXT_H
#define GUARD_CONFIG_TEXT_H

// Text settings:
#define AUTO_SCROLL_TEXT             FALSE   // If TRUE, text will automatically scroll to the next line after NUM_FRAMES_AUTO_SCROLL_DELAY. Players can still press A_BUTTON or B_BUTTON to scroll on their own.
#define NUM_FRAMES_AUTO_SCROLL_DELAY 49

// A note on the modifiers: they are roughly multiplicative, so having them set at 1 is vanilla speed. They also are used to calculate frame delays for the speed of the scroll effect and the animated down arrow, so to that end, they are capped at 31 to prevent the text printing from desyncing with A/B button inputs.
// From testing, a value of 18 to 20 is essentially equivalent to instant text.
#define TEXT_SPEED_SLOW_MODIFIER     1       // How fast the SLOW text speed option prints
#define TEXT_SPEED_MEDIUM_MODIFIER   1       // How fast the MID text speed option prints
#define TEXT_SPEED_FAST_MODIFIER     1       // How fast the FAST text speed option prints
#define TEXT_SPEED_INSTANT_MODIFIER  12      // Needed only for the animation delays
#define TEXT_SPEED_INSTANT           FALSE   // Renders all text as fast as it can, basically instant. Overrides FLAG_TEXT_SPEED_INSTANT and in-game player options menu setting.

// Right-to-left (Hebrew) rendering:
// Each window printer keeps upstream's left-to-right logical pen and mirrors every glyph inside its
// window when it is blitted, so all layouts come out mirrored with no per-screen changes. Runs of
// Latin letters and digits are drawn left to right as one block at the run's mirrored position.
#define TEXT_RTL                     TRUE
// Diagnostic build only: record every glyph drawn outside its window (see tools/hebrew/emu).
#ifndef RTL_CLIP_REPORT
#define RTL_CLIP_REPORT              FALSE
#endif
// Diagnostic build only: record the ROM address of every string copied, expanded or printed
// (see tools/hebrew/strcov.py).
#ifndef RTL_STRING_REPORT
#define RTL_STRING_REPORT            FALSE
#endif

// Battle text names a foe's Pokémon as nickname + suffix ("{nickname} הפראי") instead of
// prefix + nickname ("The wild {nickname}"), as Hebrew word order needs. The Pokédex category
// ("פוקימון זרע") and the ability pop-up follow the same switch. It is on exactly when TEXT_RTL
// is, so a build with TEXT_RTL FALSE prints the English prefixes as upstream does.
#define TEXT_NAME_SUFFIX_IN_BATTLE   TEXT_RTL

// Text speed flag:
#define FLAG_TEXT_SPEED_INSTANT      0       // Use this if you want to toggle instant text speed

#endif // GUARD_CONFIG_TEXT_H
