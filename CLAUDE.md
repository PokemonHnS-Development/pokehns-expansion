# Hoenn & Seek: notes for Claude sessions

A fork of Heart & Soul (HnS) 2.0.6 (pokeemerald-expansion 1.15.2) that adds Hoenn as an open, post-Emerald region. Design decisions, the audit and the 20-part roadmap live in the claude.ai Project "Pokemon":
- `claude/hns-hoenn-roadmap.md`
- `claude/hns-hoenn-design-decisions.md`
- `claude/hns-2.0.6-hoenn-audit.md`
- `claude/hns-hoenn-prestart-checklist.md`

Read the roadmap entry for the part you're working on before starting.

## Build
- `make hns RELEASE=1 -j$(nproc)` produces `pokehns-release.gba`. **Never use plain `make` or `make release`.** Those build the Emerald target, which is broken upstream (`FLAG_RECEIVED_TOGEPI_EGG`).
- Patch: `tools/hoenn/build_patch.sh <emerald-U.gba>` produces `dist/*.ups`. It verifies the base ROM sha1 and round-trips the patch.
- `tools/hoenn/build_patch.sh --debug <rom>` builds without RELEASE=1 (keeps the HnS debug menu for warping) and produces `dist/*-debug.ups`.
- Baselines for 2.0.6 with arm-none-eabi-gcc 13.2:
  - Release build: ROM 31,310,548 B (2,191 KB free), EWRAM 94.62%.
  - Non-release build: ~31.71 MB used (~1.76 MB free).
  - The official `pokemonHnS_v2.0.6.ups` output uses 31,707,732 B, which matches a non-release build. Our builds are not byte-identical to official (compiler differs).
  - Budget content against the release figure, but keep the debug build under 32 MB too, since testing uses it.
  - Report the ROM delta after any content change.

## How the codebase is organized
- One tree builds Emerald, FRLG and HnS. Each map/layout's `game_version` field (`emerald` / `frlg` / `hns`) decides whether `tools/mapjson` compiles it into a build. Hoenn maps are tagged `emerald` and are currently excluded from HnS.
- Each layout's `layout_version` selects the primary tileset size at runtime: HnS 640 tiles/7 palettes, Emerald 512/6. Hoenn layouts must stay `emerald`.
- C code switches on `IS_HNS` / `IS_FRLG` at build time (570 uses across 127 files). Hoenn needs some Emerald behavior at runtime, so convert those switches to region checks where needed. Don't flip them globally.
- HnS flags live in `include/constants/flags_hns.h`. The Emerald flag names used by Hoenn scripts are `#define`d to `0` there, so they compile silently but do nothing. Flags must stay below the `ENGINE_FLAGS_START` pin (0x960) unless the pin is raised and `SAVE_VERSION` bumped. Old-save compatibility is **not** a goal.

## Conventions
- **Touch upstream HnS files as little as possible**, so future HnS fixes merge cleanly. Put new code and data in new `hoenn`-named files (`tools/hoenn/`, `src/hoenn_*.c`, `data/maps/*_hoenn/`, etc.) and keep edits to shared files to small hooks.
- Work on a `part-NN-<slug>` branch off `hoenn` and open a PR into `hoenn`. Don't commit to `master` (it mirrors upstream).
- Never commit ROMs, base ROMs or patches. `baserom/` and `dist/` are git-ignored.
- The project owner tests in mGBA. Every part should end with a building ROM and a patch.
