#!/usr/bin/env python3
"""Cut the translation work into chunks of units for translators.

  make_chunks.py BATCH [BATCH ...] [--size 150] [--out DIR]     e.g. B10 B20, or 'all'

For each inventory batch (data/inventory.json) it extracts the live units of the batch's files from
the English baseline (HNS_BASELINE: the Hebrew engine with English strings), pre-fills every name field
from the glossary (those units are marked "fixed": translators leave them alone), and writes
  OUT/<BATCH>/<BATCH>_<NN>.json            (OUT: --out, default HNS_UNITS)
each holding {"batch", "chunk", "files", "names": {english: hebrew}, "units": [...]}.
"names" lists the glossary entries whose English appears in the chunk's text, so the translator
uses exactly those spellings.

A run rewrites each batch it names: it first removes that batch's chunk files from an earlier run
(OUT/<BATCH>/<BATCH>_NN.json, _names.json, and the --supplement ones _sNN.json, _snames.json), so
the folder holds this run's chunks only; the sweep reads every file there. It removes no other
file. With 'all' it also warns about a folder of chunk files of a batch the inventory no longer has.
--supplement adds to the files already written and removes nothing.
"""
import argparse, csv, json, os, re, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import units as U
import paths

BASE = paths.BASELINE
INVENTORY = paths.INVENTORY
GLOSSARY = paths.GLOSSARY
SOURCES = paths.GLOSSARY_SOURCES
OUT = paths.UNITS

# Not cut into chunks: the Easy Chat word lists, which are translated in place (each word is one
# short literal, checked by tests/test_easy_chat.py), and the R+START debug menu (src/debug.c),
# which stays English.
SKIP_FILES = ('src/data/easy_chat/', 'src/debug.c')

# Struct fields whose text is a glossary name, by file pattern.
NAME_FIELDS = {
    'speciesName': 'species', 'categoryName': 'category', 'pluralName': 'item_plural',
}


def load_glossary():
    rows = list(csv.DictReader(open(GLOSSARY, encoding='utf-8')))
    by_key = {(r['kind'], r['constant']): r for r in rows}
    by_src = {}
    for r in csv.DictReader(open(SOURCES, encoding='utf-8')):
        for src in r['source'].split(';'):
            src = src.strip()
            if ':' in src:
                f, line = src.rsplit(':', 1)
                if line.isdigit():
                    by_src.setdefault((f, int(line)), []).append((r['kind'], r['constant']))
    return rows, by_key, by_src


def hebrew_of(row):
    return (row.get('proposed_hebrew') or '').strip()


def names_in(text, rows):
    """Glossary entries whose English occurs as a whole word in text. Case-sensitive, because the
    game writes names in capitals (PIKACHU, POKé BALL) and common words would otherwise match."""
    found = {}
    plain = U.TOKEN_RE.sub(' ', text).replace('\\n', ' ').replace('\\l', ' ').replace('\\p', ' ')
    for r in rows:
        en = r['english'].strip()
        if len(en) < 3 or not hebrew_of(r) or r['kind'] in ('category', 'item_plural', 'type_generic'):
            continue
        i = plain.find(en)
        while i >= 0:
            before = plain[i - 1] if i > 0 else ' '
            after = plain[i + len(en)] if i + len(en) < len(plain) else ' '
            # A hit inside a longer capitalised name (PASS in FRONTIER PASS) is not this name.
            prev_word = re.findall(r'[A-Za-z\xe9]+', plain[:i])[-1:] if i else []
            next_word = re.findall(r'[A-Za-z\xe9]+', plain[i + len(en):])[:1]
            in_longer = (before == ' ' and prev_word and prev_word[0].isupper() and len(prev_word[0]) > 1) or \
                        (after == ' ' and next_word and next_word[0].isupper() and len(next_word[0]) > 1)
            if not before.isalnum() and not after.isalnum() and not (en.isupper() and in_longer):
                found[en] = hebrew_of(r)
                break
            i = plain.find(en, i + 1)
    return found


def own_chunk_files(folder, batch):
    """The chunk files of BATCH in FOLDER that this script writes: BATCH_NN.json, BATCH_names.json,
    and with --supplement BATCH_sNN.json and BATCH_snames.json. Nothing else matches."""
    if not os.path.isdir(folder):
        return []
    rx = re.compile(r'^%s_s?(\d+|names)\.json$' % re.escape(batch))
    return sorted(f for f in os.listdir(folder) if rx.match(f) and os.path.isfile(os.path.join(folder, f)))


def remove_old_chunks(out, batch):
    """Removes BATCH's chunk files from an earlier run before a full run writes it again. Returns
    the names removed."""
    folder = os.path.join(out, batch)
    old = own_chunk_files(folder, batch)
    for f in old:
        os.remove(os.path.join(folder, f))
    return old


def foreign_batch_dirs(out, batches):
    """Folders of OUT that hold chunk files of a batch not in BATCHES (OUT/B99/B99_01.json): left
    from an inventory that had that batch."""
    if not os.path.isdir(out):
        return []
    return sorted(d for d in os.listdir(out) if d not in batches and own_chunk_files(os.path.join(out, d), d))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('batches', nargs='+')
    ap.add_argument('--size', type=int, default=150)
    ap.add_argument('--supplement', action='store_true',
                    help='only units missing from the chunk files already written; new files are B##_sNN.json')
    ap.add_argument('--out', default=OUT, help='output folder (default HNS_UNITS)')
    a = ap.parse_args()
    base = paths.need('BASELINE')
    out = a.out
    inv = json.load(open(INVENTORY))
    rows, by_key, by_src = load_glossary()
    batches = sorted({i['batch'] for i in inv if i.get('batch')}) if a.batches == ['all'] else a.batches
    if a.batches == ['all']:
        for d in foreign_batch_dirs(out, batches):
            print('make_chunks: %s holds chunk files of %s, which %s has no longer; the sweep reads '
                  'them too: remove the folder' % (os.path.join(out, d), d, INVENTORY), file=sys.stderr)
    have = set()
    if a.supplement:
        import glob
        for f in glob.glob(os.path.join(out, '*', '*.json')):
            d = json.load(open(f, encoding='utf-8'))
            have.update(u['id'] for u in (d['units'] if isinstance(d, dict) else d))
    for b in batches:
        files = [i['file'] for i in inv if i.get('batch') == b]
        files = [f for f in files if f.endswith(('.inc', '.s', '.c', '.h')) and not any(x in f for x in SKIP_FILES)]
        us = [u for u in U.extract(files, base, False) if u['id'] not in have]
        fixed = 0
        for u in us:
            line = u['context'].get('line')
            hits = by_src.get((u['file'], line), [])
            for kind, const in hits:
                r = by_key.get((kind, const))
                if r and hebrew_of(r) and U.TOKEN_RE.sub('', r['english']).strip().upper() == U.TOKEN_RE.sub('', u['en']).strip().upper():
                    u['he'] = hebrew_of(r)
                    u['fixed'] = '%s %s' % (kind, const)
                    fixed += 1
                    break
        todo = [u for u in us if not u.get('fixed')]
        # The sweep reads every file in the batch folder, so chunk files of an earlier run (labels
        # that may no longer be live) must not stay next to this run's.
        removed = [] if a.supplement else remove_old_chunks(out, b)
        os.makedirs(os.path.join(out, b), exist_ok=True)
        # Fixed (name) units go in their own file, applied without a translator.
        if fixed:
            json.dump([u for u in us if u.get('fixed')], open(os.path.join(out, b, '%s_%snames.json' % (b, 's' if a.supplement else '')), 'w', encoding='utf-8'),
                      ensure_ascii=False, indent=1)
        n = 0
        chunk = []
        def flush():
            nonlocal n, chunk
            if not chunk:
                return
            n += 1
            text = ' '.join(u['en'] for u in chunk)
            tag = ('s%02d' if a.supplement else '%02d') % n
            doc = {'batch': b, 'chunk': '%s_%s' % (b, tag), 'files': sorted({u['file'] for u in chunk}),
                   'names': names_in(text, rows), 'units': chunk}
            json.dump(doc, open(os.path.join(out, b, '%s_%s.json' % (b, tag)), 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
            chunk = []
        prev_file = None
        for u in todo:
            # Keep a file's units together unless the chunk is already full.
            if len(chunk) >= a.size or (prev_file and u['file'] != prev_file and len(chunk) >= a.size * 0.7):
                flush()
            chunk.append(u)
            prev_file = u['file']
        flush()
        print('%s: %d files, %d units (%d names pre-filled), %d chunks' % (b, len(files), len(us), fixed, n))
        stale = sorted(set(removed) - set(own_chunk_files(os.path.join(out, b), b)))
        if stale:
            print('%s: removed %d chunk file(s) of an earlier run that this run does not write: %s'
                  % (b, len(stale), ', '.join(stale)))


if __name__ == '__main__':
    main()
