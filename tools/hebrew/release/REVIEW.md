# Visual review

Automated checks cannot see overlap, a cursor on the wrong item, mirrored or reordered digits, a
wrong glyph or a wrong translation. Every release candidate therefore gets a review of its
screenshots by several independent reviewers, and every finding then goes to a second reviewer
who tries to refute it. This file is the procedure, the finding format and the two prompts. The
reviewers can be people or AI agents; the prompts are written so either can follow them.

## Inputs

| Input | Made by |
| --- | --- |
| the candidate's tour screenshots | `run_release_tests.sh` (`RC/tests/tours`) |
| the English tour run | `python3 tools/hebrew/emu/hns.py tour "$HNS_EN_ROM" OUT` (69 of the 71 release tours run on English; `naming_player` and `naming_nickname` are Hebrew-only) |
| side-by-side sheets, English left, Hebrew right | `python3 tools/hebrew/pairsheets.py EN_TOURS RC/tests/tours SHEETS --per 6 --scale 2` |
| the frames that changed since the previous candidate | `python3 tools/hebrew/emu/hns.py tourdiff PREV/tests/tours RC/tests/tours` |
| dialogue pages of the labels a change touched | `sweep.py run ... --label NAME --shots all` on the clip ROM |
| the change list | `git log --oneline PREV_COMMIT..RC_COMMIT` |

Split the sheets into batches (one tour family, or one track of a round: battle, menus, dialogue,
Pokédex) and give each batch to its own reviewer. A reviewer sees only its batch and the inputs
above, never another reviewer's findings.

## Lenses

Each reviewer looks at every frame through these lenses (`kind` in `visual_findings.json`):

| Lens | `kind` | Look for |
| --- | --- | --- |
| English left on screen | `english_left` | Latin words where the English frame has a translatable word; names that the glossary has in Hebrew |
| Numbers | `numbers` | digits reversed, a period or unit on the wrong side, a sign or `/` pulled away from its number |
| Clipping and overflow | `clip_or_overflow` | the end of a line in reading order missing (it looks like a typo), text past a frame, a third row in a two-row box |
| Mirroring | `mirroring` | text, cursor or icon on the wrong side; LEFT/RIGHT moving against the picture; a list in the wrong order |
| Overlap | `overlap` | two items in one place; a descender or quote mark on a frame; a cursor over text |
| Glyph | `glyph` | a wrong or blank glyph, a final letter in the middle of a word, a glyph from another font |
| Translation | `translation` | a wrong meaning, wrong gender or number, a wrong name, a voice that does not fit the speaker |
| Other | `other` | anything else that differs from English without a reason |

Two rules apply to every lens:

- A frame that differs from English is a finding only if the difference is not the expected
  effect of right-to-left text (`docs/hebrew_translation.md`). When in doubt, report it.
- Never argue from a downscaled image. Zoom the PNG, read the string from RAM, dump the pixels or
  simulate the pen (`tools/hebrew/textwidth.py`).

## Finding format

A candidate's findings go to `RC/visual_findings.json`, a list of objects. `make_testing_md.py`
writes the visual-review row only when this file exists, with its text from `notes.json`
(`visual_review`).

| Field | What |
| --- | --- |
| `sheet` | the sheet the reviewer saw |
| `shot` | the screenshot name |
| `kind` | one lens from the table above |
| `severity` | `high` (wrong meaning, text lost, a crash), `medium` (visible and misleading), `low` (cosmetic) |
| `what` | what is on screen, compared with English, in plain words |
| `source` | the file and line that print it, and the code that places it |
| `fix` | the smallest fix, and where |

The review rounds keep a longer form for each confirmed finding (for example `<builds>/records`
and `<builds>/archive/rounds`):

| Field | What |
| --- | --- |
| `id` | `<track>-NNN` |
| `track` | the batch the reviewer had |
| `source`, `symbol`, `string_ids` | where the text comes from (file:line, label or table entry, string ids) |
| `lens` | `screen` (layout, glyphs, numbers) or `text` (wording, names, grammar) |
| `severity` | `low`, `medium` or `high` |
| `claim` | one or two sentences: what is wrong |
| `evidence` | measurements, file:line, the frames that show it; anything not seen is marked UNVERIFIED |
| `proposed_fix` | as `fix` above |
| `needs_owner` | true when the fix is a style call or a gameplay change (HANDOFF 7.4) |
| `shot_he`, `shot_en`, `sheet` | the Hebrew and English frames and the sheet |
| `review_reason`, `review_fix` | added by the refuter: why the finding holds, and any change to the fix |

## Refuting

Every finding goes to a second reviewer who did not make it and whose job is to prove it wrong.
The refuter reruns or re-measures instead of re-reading the finding. Each finding gets one
outcome:

| Outcome | Meaning | What happens |
| --- | --- | --- |
| `confirmed` | it holds and needs action | fix it in a new candidate, or list it in `notes.json` `known_issues` |
| `confirmed_expected` | it holds, but it is the expected behaviour (English does the same, or it is the right-to-left layout) | no change; say why in the record |
| `refuted` | it does not hold | dropped, with the reason |

A finding that needs a fix means a new candidate (`rcN+1`), whose changed frames get the same
review. Record the outcome counts in `DECISIONS.md` when a decision changed the screens (see its
"Review of the changed screens").

## Reviewer prompt

> You are reviewing screenshots of the Hebrew translation of Pokémon Heart & Soul 2.0.6. The
> sheets in `SHEETS/` show the English build on the left and the Hebrew build on the right, frame
> by frame. Hebrew is drawn right to left: a mirrored layout is expected, as described in
> `docs/hebrew_translation.md`. The style rules are `translation/hebrew/STYLE.md` and the names are
> in `translation/hebrew/glossary.csv`.
>
> Look at every frame of your batch through each of these lenses: English left on screen, numbers,
> clipping and overflow, mirroring, overlap, glyphs, translation, and anything else that differs
> from English without a reason. Zoom into the PNG before you report a pixel-level problem; never
> argue from a downscaled image. For every problem, find the string or code that prints it (search
> the English text in `../pokehns-heb-engine`, then open the same label in this tree) and measure
> it with `tools/hebrew/textwidth.py` when width is involved.
>
> Return a JSON list. Each finding has `sheet`, `shot`, `kind`, `severity`, `what`, `source` and
> `fix`, as in `tools/hebrew/release/REVIEW.md`. Say only what you saw or measured; mark anything
> else UNVERIFIED. Return an empty list if the batch is clean. Do not change any file.

## Refuter prompt

> You are checking one finding from a screenshot review of the Hebrew translation of Pokémon
> Heart & Soul 2.0.6. Your job is to prove it wrong. The finding is below, with the frames it
> cites.
>
> 1. Open the Hebrew and English frames at full size and check that the frame shows what the
>    finding says.
> 2. Open the cited source and check that it prints that text. Re-measure every number it gives.
> 3. Check whether English 2.0.6 does the same, and whether the difference is the expected effect of
>    right-to-left text (`docs/hebrew_translation.md`), a decision already recorded in
>    `translation/hebrew/DECISIONS.md`, or a known issue in `tools/hebrew/release/notes.json`.
> 4. Check that the proposed fix changes only text, art or right-to-left layout, never gameplay, and
>    that it does not break the same string elsewhere.
>
> Answer with one outcome, `confirmed`, `confirmed_expected` or `refuted`, a `review_reason` with
> the evidence (file:line, measurements, frames), and a `review_fix` when the fix should change.
> Mark anything you could not check UNVERIFIED. Do not change any file.

## History

0.2 had 8 findings confirmed and 8 refuted (`translation/hebrew/DECISIONS.md`, "Review of the
changed screens"). The candidates' review JSON is in `<builds>/records/rcNN/`, the rounds' reports
in `<builds>/archive/rounds/`, and the workflow script that translated the G01 chunks in
`<builds>/archive/rounds/hns-translate-g01.js`. The scripts that ran the earlier reviewers were not
kept; these prompts are written from the rounds' reports.
