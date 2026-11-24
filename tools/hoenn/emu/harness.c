// Minimal headless mGBA harness: run a ROM with a scripted input sequence.
// Commands (one per line, from stdin):
//   load <save.sav>        load battery save file (before first frame)
//   wait N                  run N frames, no keys
//   press KEYS [N]          hold KEYS (A,B,L,R,START,SELECT,UP,DOWN,LEFT,RIGHT joined by +) for N frames (default 4), then release 4 frames
//   mash KEYS COUNT GAP     press KEYS COUNT times, GAP idle frames between
//   shot FILE.png           screenshot
//   pc                      print PC/LR/SP
//   r32 ADDR                print 32-bit word
//   w8 ADDR VAL / w16 / w32 write memory
//   savestate FILE / loadstate FILE
#include <mgba/core/core.h>
#include <mgba/core/log.h>
#include <mgba/core/serialize.h>
#include <mgba/internal/arm/arm.h>
#include <mgba-util/vfs.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void nolog(struct mLogger* l, int c, enum mLogLevel lv, const char* f, va_list a) { (void)l;(void)c;(void)lv;(void)f;(void)a; }
static struct mLogger quiet = { .log = nolog };

static int keymask(const char* s) {
    int m = 0; char buf[128]; strncpy(buf, s, 127); buf[127]=0;
    for (char* t = strtok(buf, "+"); t; t = strtok(NULL, "+")) {
        if (!strcmp(t,"A")) m|=1<<0; else if (!strcmp(t,"B")) m|=1<<1; else if (!strcmp(t,"SELECT")) m|=1<<2;
        else if (!strcmp(t,"START")) m|=1<<3; else if (!strcmp(t,"RIGHT")) m|=1<<4; else if (!strcmp(t,"LEFT")) m|=1<<5;
        else if (!strcmp(t,"UP")) m|=1<<6; else if (!strcmp(t,"DOWN")) m|=1<<7; else if (!strcmp(t,"R")) m|=1<<8; else if (!strcmp(t,"L")) m|=1<<9;
    }
    return m;
}
static void frames(struct mCore* c, int n, int keys) { c->setKeys(c, keys); for (int i=0;i<n;i++) c->runFrame(c); c->setKeys(c, 0); }
static void shot(struct mCore* c, color_t* buf, const char* f) {
    unsigned w,h; c->desiredVideoDimensions(c,&w,&h);
    FILE* fp=fopen(f,"wb"); png_structp p=png_create_write_struct(PNG_LIBPNG_VER_STRING,0,0,0); png_infop i=png_create_info_struct(p);
    png_init_io(p,fp); png_set_IHDR(p,i,w,h,8,PNG_COLOR_TYPE_RGB,0,0,0); png_write_info(p,i);
    unsigned char* row=malloc(w*3);
    for (unsigned y=0;y<h;y++){ for(unsigned x=0;x<w;x++){ uint32_t px=buf[y*256+x]; row[x*3]=px&0xFF; row[x*3+1]=(px>>8)&0xFF; row[x*3+2]=(px>>16)&0xFF;} png_write_row(p,row);}
    png_write_end(p,0); png_destroy_write_struct(&p,&i); fclose(fp); free(row);
}
int main(int argc, char** argv) {
    if (argc<2){fprintf(stderr,"usage: harness ROM < script\n");return 2;}
    mLogSetDefaultLogger(&quiet);
    struct mCore* c = mCoreFind(argv[1]); if(!c){fprintf(stderr,"no core\n");return 1;}
    c->init(c); mCoreInitConfig(c,NULL);
    color_t* buf = malloc(256*256*sizeof(color_t)); c->setVideoBuffer(c,buf,256);
    mCoreLoadFile(c, argv[1]);
    char line[512]; int started=0;
    while (fgets(line,sizeof line,stdin)) {
        char cmd[32]={0}, a[256]={0}, b[64]={0}, d[64]={0};
        int n = sscanf(line,"%31s %255s %63s %63s",cmd,a,b,d); if(n<1||cmd[0]=='#') continue;
        if (!strcmp(cmd,"load")) { struct VFile* vf=VFileOpen(a,O_CREAT|O_RDWR); c->loadSave(c,vf); continue; }
        if (!started){ c->reset(c); started=1; }
        if (!strcmp(cmd,"wait")) frames(c, atoi(a), 0);
        else if (!strcmp(cmd,"press")) { frames(c, n>=3?atoi(b):4, keymask(a)); frames(c,4,0); }
        else if (!strcmp(cmd,"mash")) { int cnt=atoi(b), gap=n>=4?atoi(d):20; for(int k=0;k<cnt;k++){frames(c,4,keymask(a)); frames(c,gap,0);} }
        else if (!strcmp(cmd,"shot")) shot(c,buf,a);
        else if (!strcmp(cmd,"pc")) { struct ARMCore* cpu=c->cpu; printf("PC=%08x LR=%08x SP=%08x\n",cpu->gprs[15],cpu->gprs[14],cpu->gprs[13]); }
        else if (!strcmp(cmd,"r32")) { uint32_t ad=strtoul(a,0,16); printf("%08x: %08x\n",ad,c->rawRead32(c,ad,-1)); }
        else if (!strcmp(cmd,"r16")) { uint32_t ad=strtoul(a,0,16); printf("%08x: %04x\n",ad,c->rawRead16(c,ad,-1)); }
        else if (!strcmp(cmd,"r8")) { uint32_t ad=strtoul(a,0,16); printf("%08x: %02x\n",ad,c->rawRead8(c,ad,-1)); }
        else if (!strcmp(cmd,"w8")) c->rawWrite8(c,strtoul(a,0,16),-1,strtoul(b,0,0));
        else if (!strcmp(cmd,"w16")) c->rawWrite16(c,strtoul(a,0,16),-1,strtoul(b,0,0));
        else if (!strcmp(cmd,"w32")) c->rawWrite32(c,strtoul(a,0,16),-1,strtoul(b,0,0));
        else if (!strcmp(cmd,"savestate")) { struct VFile* vf=VFileOpen(a,O_CREAT|O_TRUNC|O_RDWR); mCoreSaveStateNamed(c,vf,SAVESTATE_ALL); vf->close(vf); }
        else if (!strcmp(cmd,"loadstate")) { struct VFile* vf=VFileOpen(a,O_RDONLY); mCoreLoadStateNamed(c,vf,SAVESTATE_ALL); vf->close(vf); }
        fflush(stdout);
    }
    c->deinit(c); return 0;
}
