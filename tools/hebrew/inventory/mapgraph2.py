# Stricter map reachability: a script warp counts only if the script is reached
# from a map that is itself reached (or from live C code, for global scripts).
import json,glob,re,collections,os,sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import invconfig as CFG
SRC=CFG.SRC
maps={}; name2id={}
for f in glob.glob(SRC+'/data/maps/*/map.json'):
    d=json.load(open(f)); maps[d['id']]=d; name2id[d['name']]=d['id']
a=json.load(open(os.path.join(CFG.OUT,'asm_strings.json')))
# per-label MAP refs: parse all script files
lab_maprefs=collections.defaultdict(set); lab_info={}
for f in glob.glob(SRC+'/data/maps/*/scripts.inc')+glob.glob(SRC+'/data/scripts/*.inc')+[SRC+'/data/event_scripts.s']:
    cur=None
    for line in open(f,errors='replace'):
        m=re.match(r'^\s*([A-Za-z_][A-Za-z0-9_]*)::?\s*(@.*)?$',line)
        if m: cur=m.group(1); continue
        if cur:
            for mm in re.findall(r'\bMAP_[A-Z0-9_]+\b',line.split('@')[0]):
                if mm in maps: lab_maprefs[cur].add(mm)
# label -> maps that reach it, and via categories: need every label, not only text labels
# re-derive from extract outputs: asm_parents has all reached labels; by_map only stored for text.
# so recompute by_map for all labels here using a lightweight traversal of source refs
lab_refs=collections.defaultdict(set); order=collections.defaultdict(list)
LABEL=re.compile(r'^\s*([A-Za-z_][A-Za-z0-9_]*)::?\s*(@.*|//.*)?$')
labels=set()
for f in glob.glob(SRC+'/data/maps/*/scripts.inc')+glob.glob(SRC+'/data/scripts/*.inc')+glob.glob(SRC+'/data/text/*.inc')+[SRC+'/data/event_scripts.s']:
    cur=None
    for line in open(f,errors='replace'):
        m=LABEL.match(line)
        if m: cur=m.group(1); labels.add(cur); order[f].append(cur); continue
        if cur and not line.strip().startswith('.string'):
            lab_refs[cur].update(re.findall(r'\b[A-Za-z_][A-Za-z0-9_]*\b',line.split('@')[0]))
reach=set(json.load(open(os.path.join(CFG.OUT,'asm_reach.json')))['release'])
roots=json.load(open(os.path.join(CFG.OUT,'asm_roots.json')))['release']
def trav(start):
    seen=set(); st=list(start)
    while st:
        L=st.pop()
        if L in seen or L not in labels: continue
        seen.add(L)
        st.extend(r for r in lab_refs[L] if r in labels and r not in seen)
    return seen
map_roots=collections.defaultdict(list); code_roots=[]
for L,ow in roots.items():
    for o in ow:
        m=re.match(r'^(.*)_(ObjectEvents|MapBGEvents|MapCoordEvents|MapScripts|MapEvents)$',o or '')
        if m and m.group(1) in name2id: map_roots[name2id[m.group(1)]].append(L)
        elif not re.search(r'(?i)debug',o or ''): code_roots.append(L)
global_targets=set()
for L in trav(code_roots): global_targets|=lab_maprefs[L]
edges=collections.defaultdict(set)
for k,d in maps.items():
    for w in d.get('warp_events') or []: edges[k].add(('warp',w['dest_map']))
    for c in d.get('connections') or []: edges[k].add(('conn',c['map']))
for k in list(maps):
    for L in trav(map_roots.get(k,[])):
        for t in lab_maprefs[L]: edges[k].add(('script',t))
start='MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS'
seen={start:('start',None)}; q=[start]
for t in global_targets:
    if t not in seen: seen[t]=('code-script',None); q.append(t)
import collections as C
dq=C.deque(q)
while dq:
    x=dq.popleft()
    for kind,t in edges[x]:
        if t in maps and t not in seen and maps[t].get('game_version')=='hns':
            seen[t]=(kind,x); dq.append(t)
hns=[k for k,d in maps.items() if d.get('game_version')=='hns']
unr=sorted(k for k in hns if k not in seen)
def nstr(k):
    return sum(1 for r in a.get(f"data/maps/{maps[k]['name']}/scripts.inc",[]) if r['letters'])
print('hns reached',len(hns)-len(unr),'unreached',len(unr))
print([ (k.replace('MAP_','').replace('_HNS',''),nstr(k)) for k in unr])
print('global (code) script targets:',sorted(t.replace('MAP_','') for t in global_targets if t in maps and maps[t].get('game_version')=='hns'))
json.dump({'reached':seen,'unreached':unr,'global_targets':sorted(global_targets)},open(os.path.join(CFG.OUT,'mapgraph2.json'),'w'),indent=0)
