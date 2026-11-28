"""Render every battle background in graphics/battle_environment (classic and modern,
with each palette) to one contact sheet: python3 render_battle_bgs.py graphics/battle_environment out.png"""
import struct,sys,os
from PIL import Image
def pal(path):
    d=open(path,'rb').read(); c=[]
    for i in range(0,len(d),2):
        v=d[i]|d[i+1]<<8; c.append(((v&31)*8,(v>>5&31)*8,(v>>10&31)*8))
    return c
def render(folder,palfile=None):
    t=open(folder+'/tiles.4bpp','rb').read()
    m=struct.unpack('<2048H',open(folder+'/map.bin','rb').read()[:4096])
    p=pal(palfile or folder+'/palette.gbapal')
    img=Image.new('RGB',(256,112))
    for ty in range(14):
        for tx in range(32):
            e=m[ty*32+tx]; ti=e&0x3ff; hf=e>>10&1; vf=e>>11&1; pn=(e>>12)-2
            for y in range(8):
                for x in range(8):
                    sx=7-x if hf else x; sy=7-y if vf else y
                    off=ti*32+sy*4+sx//2
                    if off>=len(t): continue
                    b=t[off]; ci=(b>>4) if sx&1 else b&15
                    idx=max(pn,0)*16+ci
                    img.putpixel((tx*8+x,ty*8+y),p[idx] if idx<len(p) else (255,0,255))
    return img.crop((0,0,240,112))
if __name__=='__main__':
    root=sys.argv[1]; out=sys.argv[2]
    from PIL import ImageDraw
    items=[]
    for d in sorted(os.listdir(root)):
        f=os.path.join(root,d)
        if not os.path.exists(f+'/map.bin'): continue
        pals=[f+'/palette.gbapal']+[os.path.join(f,x) for x in sorted(os.listdir(f)) if x.endswith('.gbapal') and x!='palette.gbapal']
        for pf in pals:
            try: items.append((d+('' if pf.endswith('/palette.gbapal') else ':'+os.path.basename(pf)[:-7]),render(f,pf)))
            except Exception as e: print(d,e)
    cols=4; W,H=240,124
    sheet=Image.new('RGB',(cols*W,((len(items)+cols-1)//cols)*H),(30,30,30))
    dr=ImageDraw.Draw(sheet)
    for i,(n,im) in enumerate(items):
        x,y=i%cols*W,i//cols*H; sheet.paste(im,(x,y+12)); dr.text((x+2,y),n,fill=(255,255,255))
    sheet.save(out); print(len(items))
