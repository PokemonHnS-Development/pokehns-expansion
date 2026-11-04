// Minimal libretro frontend: loads a core .dylib, runs a key script, dumps frames.
// usage: lrrun <core.dylib> <rom.gba> <outdir> [save.sav]   (script on stdin)
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define ENV_SET_PIXEL_FORMAT 10
#define ENV_GET_SYSTEM_DIR    9
#define ENV_GET_SAVE_DIR     31
#define ENV_GET_CAN_DUPE      3
#define ENV_GET_VARIABLE     15
#define ENV_SET_VARIABLES    16
#define ENV_GET_LOG_IFACE    27
#define ENV_GET_VARIABLE_UPDATE 17
#define ENV_SET_SUPPORT_NO_GAME 18
#define ENV_GET_INPUT_BITMASKS 51
#define ENV_GET_CORE_OPTIONS_VERSION 52
#define ENV_SET_CORE_OPTIONS         53
#define ENV_SET_CORE_OPTIONS_INTL    54
#define ENV_SET_CORE_OPTIONS_V2      67
#define ENV_SET_CORE_OPTIONS_V2_INTL 68
#define PIXFMT_XRGB8888       1
#define MEM_SAVE_RAM          0

struct retro_game_info { const char *path; const void *data; size_t size; const char *meta; };
struct retro_game_geometry { unsigned base_width, base_height, max_width, max_height; float aspect_ratio; };
struct retro_system_timing { double fps, sample_rate; };
struct retro_system_av_info { struct retro_game_geometry geometry; struct retro_system_timing timing; };
struct retro_variable { const char *key, *value; };
// Core options (libretro.h): every option answers GET_VARIABLE with its default, as a frontend with
// no saved settings does. Cores such as SkyEmu read the value without checking it for NULL.
struct retro_core_option_value { const char *value, *label; };
struct retro_core_option_definition { const char *key, *desc, *info; struct retro_core_option_value values[128]; const char *default_value; };
struct retro_core_options_intl { struct retro_core_option_definition *us, *local; };
struct retro_core_option_v2_definition { const char *key, *desc, *desc_categorized, *info, *info_categorized, *category_key;
    struct retro_core_option_value values[128]; const char *default_value; };
struct retro_core_options_v2 { void *categories; struct retro_core_option_v2_definition *definitions; };
struct retro_core_options_v2_intl { struct retro_core_options_v2 *us, *local; };
#define MAX_OPTS 256
static char *g_optkey[MAX_OPTS], *g_optval[MAX_OPTS]; static int g_nopt;
static void opt_set(const char *key, const char *val, size_t vlen) {
    if (!key || !val || g_nopt >= MAX_OPTS) return;
    for (int i = 0; i < g_nopt; i++) if (!strcmp(g_optkey[i], key)) return;
    g_optkey[g_nopt] = strdup(key); g_optval[g_nopt] = strndup(val, vlen); g_nopt++;
}
// The frontend loads the battery through retro_get_memory_data, so a core must keep its save in
// RAM it exposes: Beetle GBA's default ("mednafen") writes its own file and exposes none.
static const char *const g_override[][2] = { { "gba_use_mednafen_save_method", "libretro" } };
static const char *opt_get(const char *key) {
    for (size_t i = 0; key && i < sizeof g_override / sizeof g_override[0]; i++)
        if (!strcmp(g_override[i][0], key)) return g_override[i][1];
    for (int i = 0; key && i < g_nopt; i++) if (!strcmp(g_optkey[i], key)) return g_optval[i];
    return NULL;
}
static const char *opt_default(const char *dflt, const struct retro_core_option_value *values) {
    return dflt ? dflt : values[0].value;
}

static const uint32_t *g_fb; static unsigned g_w,g_h; static size_t g_pitch;
static uint32_t g_keys;
static long g_polls=0, g_hits=0; static unsigned g_lastid=999, g_lastdev=999;
static unsigned g_fmt = 0; // 0=RGB1555 1=XRGB8888 2=RGB565

static void vcb(const void *data, unsigned w, unsigned h, size_t pitch) {
    if (data) { g_fb = data; g_w = w; g_h = h; g_pitch = pitch; }
}
static void acb(int16_t l, int16_t r) { (void)l;(void)r; }
static size_t abcb(const int16_t *d, size_t f) { (void)d; return f; }
static void ipoll(void) {}
#define JOYPAD_MASK 256
static int16_t istate(unsigned port, unsigned dev, unsigned idx, unsigned id) {
    (void)idx;
    if (port != 0) return 0;
    g_polls++; g_lastid=id; g_lastdev=dev;
    if (id == JOYPAD_MASK) { if (g_keys) g_hits++; return (int16_t)(g_keys & 0xFFF); }
    if ((g_keys >> id) & 1) g_hits++;
    return (g_keys >> id) & 1;
}
static void logfn(int lvl, const char *fmt, ...) { (void)lvl;(void)fmt; }
struct retro_log_callback { void (*log)(int, const char*, ...); };

static bool envcb(unsigned cmd, void *data) {
    switch (cmd) {
    case ENV_SET_PIXEL_FORMAT: { g_fmt = *(unsigned*)data; return true; }
    case ENV_GET_SYSTEM_DIR: case ENV_GET_SAVE_DIR: *(const char**)data = "."; return true;
    case ENV_GET_CAN_DUPE: *(bool*)data = true; return true;
    case ENV_GET_LOG_IFACE: ((struct retro_log_callback*)data)->log = logfn; return true;
    case ENV_GET_VARIABLE: { struct retro_variable *v = data; v->value = opt_get(v->key); return v->value != NULL; }
    case ENV_GET_CORE_OPTIONS_VERSION: *(unsigned*)data = 2; return true;
    case ENV_SET_VARIABLES: {   // "Description; first|second|..."; the first is the default
        for (const struct retro_variable *v = data; v && v->key; v++) {
            const char *p = v->value ? strstr(v->value, "; ") : NULL;
            if (p) { p += 2; opt_set(v->key, p, strcspn(p, "|")); }
        }
        return true; }
    case ENV_SET_CORE_OPTIONS: case ENV_SET_CORE_OPTIONS_INTL: {
        const struct retro_core_option_definition *d = cmd == ENV_SET_CORE_OPTIONS ? data
            : ((const struct retro_core_options_intl*)data)->us;
        for (; d && d->key; d++) { const char *x = opt_default(d->default_value, d->values); if (x) opt_set(d->key, x, strlen(x)); }
        return true; }
    case ENV_SET_CORE_OPTIONS_V2: case ENV_SET_CORE_OPTIONS_V2_INTL: {
        const struct retro_core_options_v2 *o = cmd == ENV_SET_CORE_OPTIONS_V2 ? data
            : ((const struct retro_core_options_v2_intl*)data)->us;
        for (const struct retro_core_option_v2_definition *d = o ? o->definitions : NULL; d && d->key; d++) {
            const char *x = opt_default(d->default_value, d->values); if (x) opt_set(d->key, x, strlen(x)); }
        return true; }
    case ENV_GET_VARIABLE_UPDATE: *(bool*)data = false; return true;
    case ENV_GET_INPUT_BITMASKS: return true;
    case ENV_SET_SUPPORT_NO_GAME: return true;
    default: return false;
    }
}
// joypad ids
static uint32_t parseKeys(const char *s) {
    uint32_t k = 0;
    if (strstr(s,"START"))  k |= 1u<<3;
    if (strstr(s,"SELECT")) k |= 1u<<2;
    if (strstr(s,"UP"))     k |= 1u<<4;
    if (strstr(s,"DOWN"))   k |= 1u<<5;
    if (strstr(s,"LEFT"))   k |= 1u<<6;
    if (strstr(s,"RIGHT"))  k |= 1u<<7;
    if (strstr(s,"Lb"))     k |= 1u<<10;
    if (strstr(s,"Rb"))     k |= 1u<<11;
    if (strchr(s,'A') && !strstr(s,"START") && !strstr(s,"SELECT")) k |= 1u<<8;
    if (strchr(s,'B') && !strstr(s,"Lb") && !strstr(s,"Rb")) k |= 1u<<0;
    return k;
}
typedef void (*fn_setenv)(bool(*)(unsigned,void*));
typedef void (*fn_setvid)(void(*)(const void*,unsigned,unsigned,size_t));
typedef void (*fn_setaud)(void(*)(int16_t,int16_t));
typedef void (*fn_setaudb)(size_t(*)(const int16_t*,size_t));
typedef void (*fn_setpoll)(void(*)(void));
typedef void (*fn_setstate)(int16_t(*)(unsigned,unsigned,unsigned,unsigned));
typedef void (*fn_void)(void);
typedef bool (*fn_load)(const struct retro_game_info*);
typedef void (*fn_avinfo)(struct retro_system_av_info*);
typedef void* (*fn_memdata)(unsigned);
typedef size_t (*fn_memsize)(unsigned);
typedef size_t (*fn_szfn)(void);
typedef bool (*fn_unser)(const void*, size_t);
typedef void (*fn_setport)(unsigned,unsigned);

#define SYM(T,n) T n = (T)dlsym(h, #n); if (!n) { fprintf(stderr,"missing %s\n", #n); return 1; }
int main(int argc, char **argv) {
    if (argc < 4) { fprintf(stderr,"usage: lrrun <core> <rom> <outdir> [save]\n"); return 2; }
    void *h = dlopen(argv[1], RTLD_NOW);
    if (!h) { fprintf(stderr,"dlopen: %s\n", dlerror()); return 1; }
    SYM(fn_setenv,   retro_set_environment)
    SYM(fn_setvid,   retro_set_video_refresh)
    SYM(fn_setaud,   retro_set_audio_sample)
    SYM(fn_setaudb,  retro_set_audio_sample_batch)
    SYM(fn_setpoll,  retro_set_input_poll)
    SYM(fn_setstate, retro_set_input_state)
    SYM(fn_void,     retro_init)
    SYM(fn_load,     retro_load_game)
    SYM(fn_avinfo,   retro_get_system_av_info)
    SYM(fn_void,     retro_run)
    SYM(fn_memdata,  retro_get_memory_data)
    SYM(fn_memsize,  retro_get_memory_size)
    SYM(fn_szfn,     retro_serialize_size)
    SYM(fn_unser,    retro_unserialize)
    fn_setport retro_set_controller_port_device = (fn_setport)dlsym(h, "retro_set_controller_port_device");

    retro_set_environment(envcb);
    retro_set_video_refresh(vcb);
    retro_set_audio_sample(acb);
    retro_set_audio_sample_batch(abcb);
    retro_set_input_poll(ipoll);
    retro_set_input_state(istate);
    retro_init();

    FILE *f = fopen(argv[2],"rb");
    if (!f) { fprintf(stderr,"rom open failed\n"); return 1; }
    fseek(f,0,SEEK_END); long sz = ftell(f); fseek(f,0,SEEK_SET);
    void *rom = malloc(sz); if (fread(rom,1,sz,f)!=(size_t)sz) return 1; fclose(f);

    struct retro_game_info gi = { argv[2], rom, (size_t)sz, NULL };
    if (!retro_load_game(&gi)) { fprintf(stderr,"load_game failed\n"); return 1; }
    if (retro_set_controller_port_device) retro_set_controller_port_device(0, 1); // RETRO_DEVICE_JOYPAD
    struct retro_system_av_info av; retro_get_system_av_info(&av);
    fprintf(stderr,"GEOMETRY base=%ux%u max=%ux%u aspect=%.3f fps=%.2f pixfmt=%u\n",
        av.geometry.base_width, av.geometry.base_height,
        av.geometry.max_width, av.geometry.max_height,
        av.geometry.aspect_ratio, av.timing.fps, g_fmt);
    fprintf(stderr,"SERIALIZE size=%zu\n", retro_serialize_size());

    if (argc > 4) {
        void *sram = retro_get_memory_data(MEM_SAVE_RAM);
        size_t ssz = retro_get_memory_size(MEM_SAVE_RAM);
        FILE *s = fopen(argv[4],"rb");
        if (s && sram && ssz) {
            size_t n = fread(sram,1,ssz,s);
            fprintf(stderr,"SAVE loaded %zu of %zu bytes\n", n, ssz);
            fclose(s);
        } else fprintf(stderr,"SAVE skipped (sram=%p size=%zu)\n", sram, ssz);
    }

    char line[1024]; long total = 0;
    while (fgets(line,sizeof line,stdin)) {
        char a[64]={0}, b[768]={0};
        if (sscanf(line,"%63s %767s",a,b) < 1) continue;
        if (!strcmp(a,"shot")) {
            char p[512]; snprintf(p,sizeof p,"%s/%s.raw", argv[3], b[0]?b:"shot");
            FILE *o = fopen(p,"wb"); if (!o) return 1;
            uint32_t w = g_w, hh = g_h;
            fwrite(&w,4,1,o); fwrite(&hh,4,1,o);
            for (unsigned y = 0; y < g_h; y++) {
                const uint8_t *rowb = (const uint8_t*)g_fb + y*g_pitch;
                for (unsigned x = 0; x < g_w; x++) {
                    uint8_t r,gg,bb;
                    if (g_fmt == 1) { uint32_t px = ((const uint32_t*)rowb)[x];
                        r=(px>>16)&0xFF; gg=(px>>8)&0xFF; bb=px&0xFF; }
                    else { uint16_t px = ((const uint16_t*)rowb)[x];
                        if (g_fmt == 2) { r=((px>>11)&0x1F)<<3; gg=((px>>5)&0x3F)<<2; bb=(px&0x1F)<<3; }
                        else            { r=((px>>10)&0x1F)<<3; gg=((px>>5)&0x1F)<<3; bb=(px&0x1F)<<3; }
                        r|=r>>5; gg|=gg>>6; bb|=bb>>5; }
                    uint8_t bgra[4] = { bb, gg, r, 0xFF };
                    fwrite(bgra,1,4,o);
                }
            }
            fclose(o);
            fprintf(stderr,"shot %s @%ld (%ux%u)\n", b, total, g_w, g_h);
            continue;
        }
        if (!strcmp(a,"state")) {
            // A libretro save state is CPU registers plus RAM, with no ROM in
            // it, so it only makes sense against the build it was taken from.
            // Feed it a raw (already RZIP-decompressed) blob.
            FILE *st = fopen(b,"rb");
            if (!st) { fprintf(stderr,"STATE open failed %s\n", b); return 1; }
            fseek(st,0,SEEK_END); long ssz2 = ftell(st); fseek(st,0,SEEK_SET);
            void *buf = malloc(ssz2);
            if (fread(buf,1,ssz2,st) != (size_t)ssz2) return 1;
            fclose(st);
            size_t want = retro_serialize_size();
            bool ok = retro_unserialize(buf, (size_t)ssz2);
            fprintf(stderr,"STATE %s %ld bytes (core wants %zu): %s\n",
                    b, ssz2, want, ok ? "accepted" : "REJECTED");
            free(buf);
            continue;
        }
        long n = atol(a);
        g_keys = b[0] && b[0] != '-' ? parseKeys(b) : 0;
        for (long i = 0; i < n; i++) { retro_run(); total++; }
    }
    fprintf(stderr,"OK %ld frames polls=%ld hits=%ld lastid=%u lastdev=%u\n", total, g_polls, g_hits, g_lastid, g_lastdev);
    return 0;
}
