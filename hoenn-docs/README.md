# Hoenn & Seek: start here

Hoenn & Seek is Bryan's fork of Pokémon Heart & Soul (HnS) 2.0.6 that adds Hoenn as an open, post-Emerald region. **1.0 is done** (tag `1.0`, commit `c0c62f19`). **2.0 is being built**, one small part per sitting.

These docs live in the repo so any Claude session, on any account, sees the same version. **The repo is the source of truth**: update these files in the same PR as the code they describe.

## The docs
| File | What it's for |
|---|---|
| `README.md` (this file) | How to start a session and how Bryan likes to work |
| `2.0-roadmap.md` | **The build order and status.** Find the next part here |
| `2.0-plan.md` | Every 2.0 design decision, the repo check results and a master to-do list |
| `playtest-checklist.md` | Things the emulator couldn't test, for Bryan's real playthrough. Add to it at the end of every part |
| `lanes/` | **Two builder lanes + a reviewer (Nov 27):** the rules (`README.md`) and each lane's status. Read it before claiming a part |
| `2.0-ideas-proposal.md` | Bryan's Nov 27 ideas (rival, gym leaders, swarms, species cut, …): answers, Bryan's decisions and the Phase H plan (parts 41–69). **Nothing built yet** |
| `review-notes.md` | Open items from Bryan's reviews (placement, look, unapproved choices) to adjust later. Mark them done when a part fixes one |
| `../CLAUDE.md` | The technical memory: build commands, every subsystem's notes, conventions, ROM size table |

Older 1.0 background (design decisions, teams, the Aqua/Magma quests, world details, the original audit, Claude's 1.0 playtest log) is in Bryan's first claude.ai Project, "Pokemon". Everything a 2.0 part needs from it is already in `CLAUDE.md` and `2.0-plan.md`.

## Starting a session
1. **Repo:** clone `itsbliusclues-collab/hoenn-and-seek` and check out `hoenn` (on a shallow clone: `git fetch --depth 1 origin hoenn && git checkout -b hoenn origin/hoenn`).
2. **Check for an open PR** (`gh api repos/itsbliusclues-collab/hoenn-and-seek/pulls`) and your lane file in `lanes/`. Since Nov 27, "next" means: start your lane's next part. The reviewer merges PRs; builders don't.
3. **Toolchain** (a fresh cloud session has none): `apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi libpng-dev libmgba-dev` (gcc 13.2.1, the same as every earlier build), then `make -j$(nproc) tools`.
4. **Build:** `make hns -j$(nproc)` (debug, with the warp menu) and `make hns RELEASE=1 -j$(nproc)`. Never plain `make`. A cold build takes ~5–10 minutes; run it in the background.
5. **Base ROM:** `baserom/emerald.gba` (Pokémon Emerald, US; sha1 `f3ae0881…`) is not in git and must never be committed. It's only needed for the `.ups` patches; ask Bryan to attach it. `tools/hoenn/build_patch.sh --debug` then makes the debug patch.
6. **Emulator:** `tools/hoenn/emu/setup.sh` builds the headless mGBA harness in `~/emu`; `tools/hoenn/emu/pt.py` drives it (warp, talk, fight, read text, poke flags). See `CLAUDE.md` → Conventions → Emulator tests.
7. **Git limits in cloud sessions:** branch pushes and PRs (via `gh api`, not GraphQL) work; tag pushes don't, so Bryan makes tags on GitHub.

## Every part ends with
- a release and a debug build, and the ROM size row in `CLAUDE.md`
- the debug `.ups` patch sent to Bryan (if he attached the base ROM)
- emulator tests, with screenshots sent to him as a labeled grid
- an edge-case pass for every event (wrong time/day/weather, coming back after, caught vs. knocked out vs. ran, full party and boxes, save and reload mid-chain, every text box read)
- `CLAUDE.md` notes, the part's status in `2.0-roadmap.md`, untested items in `playtest-checklist.md`
- a PR into `hoenn` from a `v2-NN-<slug>` branch (fixes to 1.0: `v1.1-<slug>`). Never commit to `master`; no force pushes

## How Bryan likes to work
- **Quality over speed.** It's a hobby with no deadline. He'd rather a part take longer and be done well. Don't cut scope or testing to save time.
- **Readable code, documented in the code.** Explain what a file is for and why it's built that way at the top; comment the non-obvious parts. It should be fun to read.
- **Direct answers and pushback, not flattery.** If something in the plan is wrong or a better option exists, say so.
- **Summaries with headings and bullets**, kept short; no repeated lists.
- **He tests in mGBA** on a debug patch, often from his phone.
- **Approval first** for scene text in story-heavy scenes (starters, legendary chains, cameos) and for any new art.
- **Phone rule:** every new quest, area or battle gets a Brendan/May contact line or an event call, and every line says who told the caller.
- **Touch upstream HnS files as little as possible:** new code in `hoenn`-named files; small hooks in shared files. Data-driven where it fits: JSON in `data/hoenn/` plus a generator in `tools/hoenn/`.
- **No Megas.**

## Working from three Claude accounts (since Nov 27)
Aidan runs **two builders and a reviewer**, each on its own Claude account. They share nothing except GitHub, so the rules are in **`lanes/README.md`**; read it before starting anything. In short:
- Each builder owns a **lane** (A or B) of parts, maps and ID ranges; status per lane in `lanes/lane-a.md` and `lanes/lane-b.md`. If you don't know which lane you are, ask Aidan.
- Work on **one part at a time** in your lane. Open the PR as a draft, merge `hoenn` into your branch (no rebase, no force push), run `tools/hoenn/regen_all.sh`, rebuild, then mark it ready.
- **The reviewer merges**, one PR at a time. Builders never merge their own PRs. Aidan's "next" means "start your lane's next part".
- Never keep decisions only in a chat: put them in `2.0-plan.md`, your lane file or the part's roadmap row in the PR.
