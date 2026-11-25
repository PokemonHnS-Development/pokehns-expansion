# sheet.py OUT COLS files... : small numbered contact sheet (half size) for picking frames
import sys
from PIL import Image, ImageDraw
out,cols=sys.argv[1],int(sys.argv[2]); fs=sys.argv[3:]
W,H=120,80; g=Image.new("RGB",(W*cols,(H+10)*((len(fs)+cols-1)//cols)),"white"); d=ImageDraw.Draw(g)
for i,f in enumerate(fs):
    x,y=(i%cols)*W,(i//cols)*(H+10)
    try: g.paste(Image.open(f).convert("RGB").resize((W,H)),(x,y+10))
    except Exception: pass
    d.text((x+2,y),str(i+1),fill="black")
g.save(out)
