#!/usr/bin/env python3
"""Re-wrap a Hebrew string's \\n / \\l line breaks to fit a pixel budget. Moves breaks only.

Usage:
  wrap.py [options] TEXT...        TEXT in source form, as inside .string "..." (\\n \\l \\p {CODES} $)
  wrap.py [options] --stdin        one string per input line
Options:
  --kind KIND       budget from data/budgets.json via audit.py (default overworld_dialogue:
                    FONT_NORMAL, 208 px, 200 px on lines that end in \\l or \\p, 2 lines a page)
  --px N            line budget in px (overrides --kind)
  --prompt-px N     budget for lines that end in \\l or \\p (default: --px - 8 when --px is given)
  --lines N         lines per page (default: from --kind)
  --no-scroll       never use \\l: every break is \\n and a page holds at most --lines lines
                    (descriptions, menus). Kinds other than dialogue/phone/battle text imply it.
  --font NAME       font to measure in (default: from --kind; a kind shown in several windows is
                    checked in each, in the narrowest font of each fit chain, like audit.py errors)
  --fonts-tree DIR  src/fonts.c + charmap.txt to measure with (default: textwidth.py's)
  --subst NAME=SPEC worst-case placeholder override, textwidth.py grammar
  --json            machine-readable output

Rules:
  - \\p page breaks and every word stay where they are; only \\n and \\l are moved. Inside a page the
    words (split at spaces and at the old \\n/\\l) are refilled greedily: each line takes as many words
    as fit its budget. Line k of a page ends in \\n while k < lines-1, after that in \\l (scroll),
    as upstream dialogue does; with --no-scroll every break is \\n.
  - A line that ends in \\l or \\p carries the 8 px down arrow, so it gets --prompt-px.
  - Widths come from textwidth.py (worst-case placeholders: {PLAYER} = 7 widest glyphs, etc.),
    measured with the font active at that point ({FONT_x} switches carry across breaks).
  - Check: the result with every \\n/\\l turned into a space equals the input turned the same way.
Exit status 1 when a word is wider than a line, or a no-scroll page needs more lines than allowed
(that string must be reworded), else 0.
"""
import argparse
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import textwidth as tw  # noqa: E402

SCROLL_KINDS = ('overworld_dialogue', 'phone_call_text', 'sign', 'battle_message', 'battle_trainer_text')
BREAK_RE = re.compile(r'\s*\\[nl]\s*')


class Budget(object):
    """CHECKS: [(font, px, prompt_px)]; a line must fit every one (each window that shows the string)."""

    def __init__(self, checks, lines=2, scroll=True, kind='custom'):
        self.checks, self.lines, self.scroll, self.kind = list(checks), lines, scroll, kind

    def as_dict(self):
        return dict(kind=self.kind, checks=[dict(font=f, px=p, prompt_px=q) for f, p, q in self.checks],
                    lines=self.lines, scroll=self.scroll)


def budget_for_kind(kind, budgets_path=None):
    """Every width check of an audit.py kind (measured in the narrowest font of its fit chain, as
    audit.py judges errors) and the fewest lines among them."""
    import audit
    kinds = audit.build_kinds(budgets_path or audit.BUDGETS)
    if kind not in kinds or not kinds[kind]['checks']:
        raise SystemExit('wrap: kind %s has no width budget (known: %s)' % (
            kind, ', '.join(k for k, v in sorted(kinds.items()) if v['checks'])))
    scroll = kind in SCROLL_KINDS
    checks = []
    for where, fonts, px_warn, px_err, prompt_px, nlines in kinds[kind]['checks']:
        prompt = prompt_px if prompt_px else (px_err - tw.PROMPT_ARROW_PX if scroll else px_err)
        checks.append((fonts[-1], px_err, prompt))
    return Budget(checks, min(c[5] for c in kinds[kind]['checks']), scroll, kind)


def canonical(text):
    return BREAK_RE.sub(' ', text)


def split_pages(text):
    """[(page_text, terminator)] with terminator '\\p', '$' or ''."""
    out, cur, i = [], [], 0
    while i < len(text):
        if text.startswith('\\p', i):
            out.append((''.join(cur), '\\p'))
            cur, i = [], i + 2
            continue
        if text[i] == '{':
            j = text.find('}', i)
            j = len(text) - 1 if j < 0 else j
            cur.append(text[i:j + 1])
            i = j + 1
            continue
        if text[i] == '\\' and i + 1 < len(text):
            cur.append(text[i:i + 2])
            i += 2
            continue
        cur.append(text[i])
        i += 1
    rest = ''.join(cur)
    if rest.endswith('$'):
        out.append((rest[:-1], '$'))
    elif rest or not out:
        out.append((rest, ''))
    return out


def words_of(page):
    """Words of a page: split at spaces and old \\n/\\l (spaces inside {CODES} are kept)."""
    page = BREAK_RE.sub(' ', page)
    words, cur, depth = [], [], 0
    for c in page:
        if c == '{':
            depth += 1
        elif c == '}':
            depth = max(0, depth - 1)
        if c == ' ' and depth == 0:
            words.append(''.join(cur))
            cur = []
        else:
            cur.append(c)
    words.append(''.join(cur))
    return words


class Wrapper(object):
    def __init__(self, model, budget):
        self.model, self.b = model, budget

    def _widths(self, prefix, lines, font):
        """Widths of LINES in FONT, laid out after PREFIX (earlier pages, for the font state)."""
        text = prefix + ''.join(l + '\\n' for l in lines[:-1]) + lines[-1] + '$'
        laid = self.model.lines(text, font)
        return [l.width for l in laid[-len(lines):]]

    def _prompt(self, k, nlines, term):
        """Whether line k of a page of nlines lines carries the down arrow."""
        if k == nlines - 1:
            return term == '\\p'
        return self.b.scroll and k >= self.b.lines - 1

    def _over(self, prefix, lines, k, prompt):
        """[(font, width, cap)] of the checks that line k breaks."""
        out = []
        for font, px, prompt_px in self.b.checks:
            w = self._widths(prefix, lines[:k + 1], font)[-1]
            cap = prompt_px if prompt else px
            if w > cap:
                out.append((font, w, cap))
        return out

    def wrap_page(self, prefix, page, term):
        words = words_of(page)
        lines, problems = [], []
        cur = None
        for w in words:
            if cur is None:
                cur = w
                continue
            trial = cur + ' ' + w
            k = len(lines)
            # judged as if this line were not the page's last; the last line is checked below
            if not self._over(prefix, lines + [trial], k, self.b.scroll and k >= self.b.lines - 1):
                cur = trial
            else:
                lines.append(cur)
                cur = w
        lines.append(cur if cur is not None else '')
        while True:                    # the last line may need the arrow budget: push words down
            k = len(lines) - 1
            if not self._over(prefix, lines, k, self._prompt(k, len(lines), term)):
                break
            ws = words_of(lines[-1])
            if len(ws) < 2:
                break
            lines[-1] = ' '.join(ws[:-1])
            lines.append(ws[-1])
        detail = []
        for k, l in enumerate(lines):
            prompt = self._prompt(k, len(lines), term)
            over = self._over(prefix, lines, k, prompt)
            font, px, prompt_px = self.b.checks[0]
            detail.append(dict(text=l, width=self._widths(prefix, lines[:k + 1], font)[-1],
                               cap=prompt_px if prompt else px, font=font, prompt=prompt))
            for f, w, cap in over:
                problems.append('line "%s" is %d px > %d px in %s and cannot be split further' % (l, w, cap, f))
        if not self.b.scroll and len(lines) > self.b.lines:
            problems.append('page needs %d lines, the window has %d: reword' % (len(lines), self.b.lines))
        out = ''
        for k, l in enumerate(lines):
            out += l
            if k < len(lines) - 1:
                out += '\\l' if (self.b.scroll and k >= self.b.lines - 1) else '\\n'
        return out, detail, problems

    def wrap(self, text):
        out, prefix, detail, problems = '', '', [], []
        for page, term in split_pages(text):
            wrapped, lines, probs = self.wrap_page(prefix, page, term)
            out += wrapped + term
            detail.append(lines)
            problems += probs
            prefix += wrapped + ('\\p' if term == '\\p' else '')
        if canonical(out) != canonical(text):
            raise AssertionError('wrap changed the words: %r -> %r' % (text, out))
        return out, detail, problems


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('text', nargs='*')
    ap.add_argument('--stdin', action='store_true')
    ap.add_argument('--kind', default='overworld_dialogue')
    ap.add_argument('--px', type=int)
    ap.add_argument('--prompt-px', type=int)
    ap.add_argument('--lines', type=int)
    ap.add_argument('--no-scroll', action='store_true')
    ap.add_argument('--font')
    ap.add_argument('--fonts-tree', default=tw.FONTS_TREE)
    ap.add_argument('--subst', action='append')
    ap.add_argument('--json', action='store_true')
    a = ap.parse_args(argv)
    font = (a.font if a.font.startswith('FONT_') else 'FONT_' + a.font) if a.font else None
    if a.px:
        prompt = a.prompt_px or (a.px if a.no_scroll else a.px - tw.PROMPT_ARROW_PX)
        b = Budget([(font or 'FONT_NORMAL', a.px, prompt)], a.lines or 2, not a.no_scroll)
    else:
        b = budget_for_kind(a.kind)
        b.lines = a.lines or b.lines
        if a.no_scroll:
            b.scroll = False
        b.checks = [(font or f, px, a.prompt_px or (px if not b.scroll else q)) for f, px, q in b.checks]
    model = tw.TextModel(a.fonts_tree, subst=tw._parse_subst(a.subst))
    texts = [l.rstrip('\n') for l in sys.stdin] if a.stdin else a.text
    if not texts:
        ap.print_usage()
        return 2
    w = Wrapper(model, b)
    results, bad = [], 0
    for t in texts:
        out, detail, problems = w.wrap(t)
        bad += bool(problems)
        results.append(dict(input=t, output=out, changed=out != t, lines=detail, problems=problems))
    if a.json:
        print(json.dumps({'budget': b.as_dict(), 'results': results}, ensure_ascii=False, indent=1))
    else:
        for r in results:
            print(r['output'])
            for p, page in enumerate(r['lines'], 1):
                for l in page:
                    print('   p%d %3d/%d px %s %s' % (p, l['width'], l['cap'], l['font'], l['text']))
            for p in r['problems']:
                print('   ERROR %s' % p)
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
