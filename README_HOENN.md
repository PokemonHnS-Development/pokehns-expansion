# Hoenn & Seek

*Working title.* A fork of [Pokémon Heart & Soul](https://github.com/PokemonHnS-Development/pokehns-expansion) 2.0.6 that adds Hoenn as an open, post-Emerald region. You reach it after the 16 Johto/Kanto badges and must finish it before Red.

> Status: **early development.** Builds are plain Heart & Soul 2.0.6 until the Hoenn parts land.

## The idea
- **Professor Oak gives you a ferry ticket after you beat Blue.** You sail from Vermilion to Slateport.
- **Hoenn is set after Emerald:**
  - No Team Aqua/Magma story; their defeated members hang around instead.
  - Brendan and May fight you in Littleroot as a hard double battle.
  - There's a small Norman event.
- **The 8 gyms and the Hoenn League award trainer card stamps.** Gym levels scale with how many stamps you have, and Wallace is the final stamp. Red unlocks after that.
- **Restored features:** HM09 Dive, contests in Lilycove, secret bases, the Hoenn Safari Zone.
- **Legendaries stay where Heart & Soul already puts them.**

## Playing
Patches go on a **Pokémon - Emerald Version (U)** ROM (sha1 `f3ae088181bf583e55daf962a92bb46f4f1d07b7`). Use your own legally obtained copy. Apply the `.ups` with [Rom Patcher JS](https://www.marcrobledo.com/RomPatcher.js/). Do not share ROMs, only patches.

## Building
Follow [INSTALL.md](INSTALL.md) for the toolchain, then:

```sh
make hns RELEASE=1 -j$(nproc)            # -> pokehns-release.gba
tools/hoenn/build_patch.sh baserom/emerald.gba   # -> dist/hoenn-and-seek-<rev>.ups
```

Note: plain `make` or `make release` builds the *Emerald* target of this codebase, which is broken upstream. Always build the `hns` target.

## Branches
- `master`: untouched upstream Heart & Soul 2.0.6.
- `hoenn`: integration branch for this project.
- `part-NN-*`: one branch per roadmap part, merged into `hoenn` by PR.

## Credits
- All of Heart & Soul: Lil Dill and the [Heart & Soul team and contributors](CREDITS.md).
- [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) and [pret/pokeemerald](https://github.com/pret/pokeemerald).
- Pokémon is © Nintendo / Creatures / GAME FREAK. This is a non-commercial fan project.
