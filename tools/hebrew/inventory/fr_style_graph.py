# Re-run the French fork's map traversal (translation/AI_HANDOFF.md:222-229 on fr/fr/main):
# warp_events + connections of every map.json, plus warp commands in each map's
# own scripts.inc, from MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS, ignoring flags and
# ignoring whether the destination map is compiled into the hns build.
import json,glob,re,os,collections,sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import invconfig as CFG
SRC=CFG.SRC
maps={}; byname={}
for f in glob.glob(SRC+'/data/maps/*/map.json'):
    d=json.load(open(f)); maps[d['id']]=d; byname[d['name']]=d['id']
edges=collections.defaultdict(set)
for k,d in maps.items():
    for w in d.get('warp_events') or []: edges[k].add(w['dest_map'])
    for c in d.get('connections') or []: edges[k].add(c['map'])
    sp=f"{SRC}/data/maps/{d['name']}/scripts.inc"
    if os.path.exists(sp):
        for line in open(sp,errors='replace'):
            m=re.match(r'\s*(warp\w*|setwarp|setdynamicwarp|setescapewarp|setholewarp|setdivewarp)\s+(MAP_[A-Z0-9_]+)',line)
            if m: edges[k].add(m.group(2))
start='MAP_NEW_BARK_TOWN_PLAYERS_HOUSE_2F_HNS'
seen={start:None}; q=[start]
while q:
    x=q.pop()
    for t in edges[x]:
        if t in maps and t not in seen: seen[t]=x; q.append(t)
a=json.load(open(os.path.join(CFG.OUT,'asm_strings.json')))
inh=[d for k,d in maps.items() if d.get('game_version')!='hns']
def nstr(name):
    return sum(1 for r in a.get(f'data/maps/{name}/scripts.inc',[]) if r['letters'])
reached=[d['name'] for d in inh if d['id'] in seen and nstr(d['name'])>0]
unreached=[d['name'] for d in inh if d['id'] not in seen and nstr(d['name'])>0]
print('maps reached',len(seen),'of',len(maps))
print('inherited with strings: reached',len(reached),sum(nstr(n) for n in reached),'unreached',len(unreached),sum(nstr(n) for n in unreached))
# path for one reached inherited map
def path(m):
    p=[];x=m
    while x: p.append(x); x=seen[x]
    return ' <- '.join(p[:6])
print(path(byname['PetalburgCity']))
json.dump({'reached_inherited':sorted(reached),'unreached_inherited':sorted(unreached),'reached_count':len(seen)},open(os.path.join(CFG.OUT,'fr_style_graph.json'),'w'),indent=0)
