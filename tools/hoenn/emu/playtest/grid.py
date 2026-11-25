# grid.py OUT COLS file:label ...
import sys
from PIL import Image, ImageDraw
out,cols=sys.argv[1],int(sys.argv[2]); items=[a.split(':',1) for a in sys.argv[3:]]
S=2; w,h=240*S,160*S; lh=28
g=Image.new('RGB',(w*cols,(h+lh)*((len(items)+cols-1)//cols)),'white'); d=ImageDraw.Draw(g)
for i,(f,l) in enumerate(items):
    x,y=(i%cols)*w,(i//cols)*(h+lh)
    g.paste(Image.open(f).convert('RGB').resize((w,h),Image.NEAREST),(x,y+lh))
    d.text((x+6,y+6),f"{i+1}. {l}",fill='black')
g.save(out)
