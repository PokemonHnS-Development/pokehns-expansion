#!/usr/bin/env python3
"""Hoenn & Seek 2.0 (part 38): check Hoenn & Seek's message texts for two things.

1. Width: every line of every .string text in the files given (default: every
   data/scripts/hoenn_*.inc and data/maps/*_hoenn/scripts.inc) is measured with
   FONT_NORMAL's glyph widths (gFontNormalLatinGlyphWidths in src/fonts.c, codes
   from charmap.txt). The field message box is 27 tiles wide (216 px,
   sStandardTextBox_WindowTemplates in src/menu.c), and text starts at x = 0.
   Placeholders count as a typical long value: {PLAYER} 7 capitals, {STR_VAR_n}
   10 capitals, {RIVAL} 7 capitals.
2. One-word last lines: a text box (between \\p breaks or the end) of two or more
   lines whose last line is a single word (CLAUDE.md's "No one-word last lines").
   Lines of only dots or punctuation don't count.

Texts written for other windows (braille, multichoice labels, PokéGear names) are
skipped by label: anything whose label contains Braille, _Name, Label or Choice.

Usage: tools/hoenn/text_audit.py [--max PX] [FILES...]   exit 1 if anything is found
"""
import glob, os, re, sys

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
BOX_PX = 216
SKIP = ("Braille", "_Name", "Label", "Choice")
CAPS_PX = 6  # most capitals in FONT_NORMAL
PLACEHOLDER_PX = {"PLAYER": 7 * CAPS_PX, "RIVAL": 7 * CAPS_PX,
                  "STR_VAR_1": 10 * CAPS_PX, "STR_VAR_2": 10 * CAPS_PX, "STR_VAR_3": 10 * CAPS_PX}


# Placeholders that hold a number in these texts (one or two digits, not a name).
NUMBERS = {("HoennSeek_Text_AlphResearcherFragments", "STR_VAR_3"),
           ("HoennSeek_Text_ShrineHaveSome", "STR_VAR_1")}


def glyph_widths():
    src = open(P("src/fonts.c")).read()
    body = src[src.index("gFontNormalLatinGlyphWidths[] = {"):]
    body = body[body.index("{") + 1:body.index("};")]
    return [int(v) for v in re.findall(r"\d+", body)]


def charmap():
    codes = {}
    for line in open(P("charmap.txt"), encoding="utf-8"):
        m = re.match(r"^'(.+)'\s*=\s*([0-9A-Fa-f]{2})\s*$", line)
        if m:
            ch = m.group(1).replace("\\'", "'")
            codes.setdefault(ch, int(m.group(2), 16))
    return codes


def line_px(line, widths, codes, label=""):
    px, i = 0, 0
    while i < len(line):
        if line[i] == "{":
            j = line.index("}", i)
            name = line[i + 1:j]
            px += 2 * CAPS_PX if (label, name) in NUMBERS else PLACEHOLDER_PX.get(name, 0)
            i = j + 1
            continue
        c = codes.get(line[i])
        px += widths[c] if c is not None and c < len(widths) else 6
        i += 1
    return px


def texts(path):
    """Yields (label, text) for each label followed by .string lines."""
    label, parts = None, []
    for raw in open(path, encoding="utf-8"):
        m = re.match(r"^(\w+):{1,2}\s*$", raw)
        s = re.match(r'^\s*\.string\s+"(.*)"\s*$', raw)
        if m:
            if label and parts:
                yield label, "".join(parts)
            label, parts = m.group(1), []
        elif s and label:
            parts.append(s.group(1))
        elif label and parts and raw.strip() and not raw.lstrip().startswith("@"):
            yield label, "".join(parts)
            label, parts = None, []
    if label and parts:
        yield label, "".join(parts)


def main():
    args = sys.argv[1:]
    limit = BOX_PX
    if args[:1] == ["--max"]:
        limit, args = int(args[1]), args[2:]
    files = args or sorted(glob.glob(P("data/scripts/hoenn_*.inc")) + glob.glob(P("data/maps/*_hoenn/scripts.inc")))
    widths, codes = glyph_widths(), charmap()
    bad = 0
    for f in files:
        for label, text in texts(f):
            if any(k in label for k in SKIP):
                continue
            text = text.replace("$", "")
            for box in text.split("\\p"):
                lines = re.split(r"\\n|\\l", box)
                for ln in lines:
                    w = line_px(ln, widths, codes, label)
                    if w > limit:
                        bad += 1
                        print("%s: %s: %d px: %s" % (os.path.relpath(f, ROOT), label, w, ln))
                last = lines[-1].strip()
                bare = re.sub(r"\{\w+\}", "", last)  # a line that's only a placeholder is deliberate
                if len(lines) > 1 and len(last.split()) == 1 and re.search(r"[A-Za-z0-9]", bare):
                    bad += 1
                    print("%s: %s: one-word last line: %s" % (os.path.relpath(f, ROOT), label, last))
    print("text_audit: %d finding(s) in %d file(s)" % (bad, len(files)))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
