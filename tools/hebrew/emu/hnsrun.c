// Headless GBA runner for the Heart & Soul Hebrew harness.
// Boots a ROM with an optional battery save, pins the RTC, steps frames with a
// key mask, writes PNG screenshots, peeks/pokes memory, and reports crashes.
//
// argv: hnsrun <rom> <outdir> [save.sav]
// env:  HNS_RTC=<unix seconds>  fake-epoch RTC start (default 2026-01-01 12:00 UTC)
//       HNS_LOG=1               echo every mGBA log line, not just warnings and game prints
// stdin script, one command per line ('#' starts a comment):
//   <frames> <keys>             hold keys (A B START SELECT UP DOWN LEFT RIGHT Lb Rb, '-' for none)
//   tap <keys> [idle]           hold keys 3 frames, then idle (default 20) frames
//   shot <name>                 write <outdir>/<name>.png (240x160, 1x)
//   read <hexaddr> <len>        hex-dump memory to stderr
//   r32 <hexaddr>               print one word
//   crc <hexaddr> <len>         print the CRC-32 of len bytes and whether they are all equal
//                               ("CRC addr len crc uniform"; cheaper than read for big buffers)
//   w8|w16|w32 <hexaddr> <hexval>
//   wait32 <hexaddr> <hexval> <maxframes> [keys]
//                               run until the word at addr equals val; with keys, tap them every 30 frames
//   pc                          print the CPU's program counter
//   pin <hexaddr> <hexbytes>    rewrite these bytes before every frame until unpinned (max 8 pins,
//                               31 bytes each; e.g. pin the RNG state so battles do not depend on timing)
//   unpin [hexaddr]             drop one pin, or all
//   ss <file> / sl <file>       save / load a savestate (same build only)
//   quit
// Every 60 frames the runner checks that the PC is in BIOS, EWRAM, IWRAM, ROM or a ROM mirror
// (pcIsSane). Anywhere else the game jumped through a bad pointer, and the run stops with "CRASH".
#include <mgba/core/core.h>
#include <mgba/core/config.h>
#include <mgba/core/log.h>
#include <mgba/core/serialize.h>
#include <mgba/core/interface.h>
#include <mgba/internal/arm/arm.h>
#include <mgba/internal/gba/input.h>
#include <mgba-util/vfs.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static int sVerboseLog;
static long sTotal;

static void logCb(struct mLogger* logger, int category, enum mLogLevel level, const char* fmt, va_list args) {
    (void) logger;
    const char* cat = mLogCategoryName(category);
    int isGame = cat && (strstr(cat, "Debug") || strstr(cat, "debug"));
    if (!sVerboseLog && !isGame && level > mLOG_WARN)
        return;
    if (!sVerboseLog && !isGame && cat && strstr(cat, "Audio"))
        return;
    char buf[1024];
    vsnprintf(buf, sizeof buf, fmt, args);
    fprintf(stderr, "LOG[%s/%d] @%ld %s\n", cat ? cat : "?", level, sTotal, buf);
}

static struct mLogger sLogger = { .log = logCb, .filter = NULL };

static uint32_t parseKeys(const char* s) {
    uint32_t k = 0;
    if (!s || !*s || *s == '-') return 0;
    char buf[128];
    snprintf(buf, sizeof buf, "%s", s);
    for (char* t = strtok(buf, "+,"); t; t = strtok(NULL, "+,")) {
        if (!strcmp(t, "A")) k |= 1 << GBA_KEY_A;
        else if (!strcmp(t, "B")) k |= 1 << GBA_KEY_B;
        else if (!strcmp(t, "START")) k |= 1 << GBA_KEY_START;
        else if (!strcmp(t, "SELECT")) k |= 1 << GBA_KEY_SELECT;
        else if (!strcmp(t, "UP")) k |= 1 << GBA_KEY_UP;
        else if (!strcmp(t, "DOWN")) k |= 1 << GBA_KEY_DOWN;
        else if (!strcmp(t, "LEFT")) k |= 1 << GBA_KEY_LEFT;
        else if (!strcmp(t, "RIGHT")) k |= 1 << GBA_KEY_RIGHT;
        else if (!strcmp(t, "Lb") || !strcmp(t, "L")) k |= 1 << GBA_KEY_L;
        else if (!strcmp(t, "Rb") || !strcmp(t, "R")) k |= 1 << GBA_KEY_R;
        else fprintf(stderr, "WARN: unknown key %s\n", t);
    }
    return k;
}

static int writePng(const char* path, const color_t* fb, unsigned w, unsigned h) {
    size_t rowLen = 1 + (size_t) w * 3;
    unsigned char* raw = malloc(rowLen * h);
    for (unsigned y = 0; y < h; y++) {
        unsigned char* row = raw + y * rowLen;
        row[0] = 0;
        for (unsigned x = 0; x < w; x++) {
            uint32_t p = fb[y * w + x];
            row[1 + x * 3 + 0] = p & 0xFF;
            row[1 + x * 3 + 1] = (p >> 8) & 0xFF;
            row[1 + x * 3 + 2] = (p >> 16) & 0xFF;
        }
    }
    uLongf zlen = compressBound(rowLen * h);
    unsigned char* z = malloc(zlen);
    compress2(z, &zlen, raw, rowLen * h, 6);
    FILE* f = fopen(path, "wb");
    if (!f) { free(raw); free(z); return 0; }
    static const unsigned char sig[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};
    fwrite(sig, 1, 8, f);
    unsigned char ihdr[13] = {
        w >> 24, w >> 16, w >> 8, w, h >> 24, h >> 16, h >> 8, h, 8, 2, 0, 0, 0
    };
    struct { const char* t; const unsigned char* d; uint32_t n; } chunks[3] = {
        {"IHDR", ihdr, 13}, {"IDAT", z, (uint32_t) zlen}, {"IEND", NULL, 0}
    };
    for (int i = 0; i < 3; i++) {
        unsigned char len[4] = {chunks[i].n >> 24, chunks[i].n >> 16, chunks[i].n >> 8, chunks[i].n};
        fwrite(len, 1, 4, f);
        fwrite(chunks[i].t, 1, 4, f);
        uLong crc = crc32(0, (const Bytef*) chunks[i].t, 4);
        if (chunks[i].n) {
            fwrite(chunks[i].d, 1, chunks[i].n, f);
            crc = crc32(crc, chunks[i].d, chunks[i].n);
        }
        unsigned char c[4] = {crc >> 24, crc >> 16, crc >> 8, crc};
        fwrite(c, 1, 4, f);
    }
    fclose(f);
    free(raw);
    free(z);
    return 1;
}

static uint32_t getPc(struct mCore* core) {
    struct ARMCore* cpu = core->cpu;
    return (uint32_t) cpu->gprs[ARM_PC];
}

// Regions the game runs code from: BIOS 00, EWRAM 02, IWRAM 03, ROM 08-09 and the ROM's wait-state
// mirrors 0A-0D, where it runs every script command that requests effects (the command table stores
// those as address + ROM_SIZE, data/script_cmd_table.inc). hns.py pc_is_sane accepts the same.
static int pcIsSane(uint32_t pc) {
    uint32_t region = pc >> 24;
    return region == 0x00 || region == 0x02 || region == 0x03 || (region >= 0x08 && region <= 0x0D);
}

static int sCrashed;

#define MAX_PINS 8
static struct { uint32_t addr; int len; uint8_t bytes[32]; } sPins[MAX_PINS];
static int sNumPins;

static void applyPins(struct mCore* core) {
    for (int p = 0; p < sNumPins; p++)
        for (int i = 0; i < sPins[p].len; i++)
            core->busWrite8(core, sPins[p].addr + i, sPins[p].bytes[i]);
}

static void stepFrames(struct mCore* core, long frames, uint32_t keys) {
    for (long i = 0; i < frames && !sCrashed; i++) {
        applyPins(core);
        core->setKeys(core, keys);
        core->runFrame(core);
        sTotal++;
        if ((sTotal % 60) == 0) {
            uint32_t pc = getPc(core);
            if (!pcIsSane(pc)) {
                fprintf(stderr, "CRASH: pc=%08X @%ld\n", pc, sTotal);
                sCrashed = 1;
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) { fprintf(stderr, "usage: hnsrun <rom> <outdir> [save.sav]\n"); return 2; }
    const char* rom = argv[1];
    const char* outdir = argv[2];
    const char* savePath = argc > 3 ? argv[3] : NULL;
    sVerboseLog = getenv("HNS_LOG") != NULL;
    mLogSetDefaultLogger(&sLogger);

    struct mCore* core = mCoreFind(rom);
    if (!core) { fprintf(stderr, "FAIL: mCoreFind\n"); return 1; }
    if (!core->init(core)) { fprintf(stderr, "FAIL: core init\n"); return 1; }
    mCoreInitConfig(core, NULL);

    unsigned w, h;
    core->desiredVideoDimensions(core, &w, &h);
    color_t* fb = calloc(w * h, BYTES_PER_PIXEL);
    core->setVideoBuffer(core, fb, w);

    if (!mCoreLoadFile(core, rom)) { fprintf(stderr, "FAIL: load ROM\n"); return 1; }

    if (savePath) {
        struct VFile* sv = VFileOpen(savePath, O_RDWR | O_CREAT);
        if (!sv) { fprintf(stderr, "FAIL: open save %s\n", savePath); return 1; }
        if (!core->loadSave(core, sv)) { fprintf(stderr, "FAIL: loadSave\n"); return 1; }
        fprintf(stderr, "OK: save attached (%s)\n", savePath);
    }

    const char* rtcEnv = getenv("HNS_RTC");
    core->rtc.override = RTC_FAKE_EPOCH;
    core->rtc.value = (rtcEnv ? atoll(rtcEnv) : 1767268800LL) * 1000LL;

    core->reset(core);
    fprintf(stderr, "OK: booted %ux%u rtc=%lld\n", w, h, (long long) (core->rtc.value / 1000));

    char line[512];
    while (!sCrashed && fgets(line, sizeof line, stdin)) {
        char* hash = strchr(line, '#');
        if (hash) *hash = 0;
        char a[64] = {0}, b[128] = {0}, c[64] = {0}, d[64] = {0}, e[64] = {0};
        int n = sscanf(line, "%63s %127s %63s %63s %63s", a, b, c, d, e);
        if (n < 1) continue;
        if (!strcmp(a, "quit")) break;
        if (!strcmp(a, "shot")) {
            char path[1024];
            snprintf(path, sizeof path, "%s/%s.png", outdir, b[0] ? b : "shot");
            if (!writePng(path, fb, w, h)) { fprintf(stderr, "FAIL: write %s\n", path); return 1; }
            fprintf(stderr, "shot %s @%ld\n", b, sTotal);
            continue;
        }
        if (!strcmp(a, "ss") || !strcmp(a, "sl")) {
            struct VFile* st = VFileOpen(b, !strcmp(a, "ss") ? (O_RDWR | O_CREAT | O_TRUNC) : O_RDONLY);
            if (!st) { fprintf(stderr, "FAIL: state %s %s\n", a, b); return 1; }
            bool ok = !strcmp(a, "ss") ? mCoreSaveStateNamed(core, st, 0) : mCoreLoadStateNamed(core, st, 0);
            st->close(st);
            fprintf(stderr, "STATE %s %s %s\n", a, b, ok ? "ok" : "FAIL");
            continue;
        }
        if (!strcmp(a, "read")) {
            uint32_t addr = (uint32_t) strtoul(b, NULL, 16);
            int len = c[0] ? atoi(c) : 16;
            fprintf(stderr, "MEM %08X:", addr);
            for (int i = 0; i < len; i++) fprintf(stderr, " %02X", core->busRead8(core, addr + i));
            fprintf(stderr, "\n");
            continue;
        }
        if (!strcmp(a, "r32")) {
            uint32_t addr = (uint32_t) strtoul(b, NULL, 16);
            fprintf(stderr, "R32 %08X = %08X\n", addr, core->busRead32(core, addr));
            continue;
        }
        if (!strcmp(a, "crc")) {
            uint32_t addr = (uint32_t) strtoul(b, NULL, 16);
            long len = c[0] ? atol(c) : 0;
            uLong crc = crc32(0L, Z_NULL, 0);
            int uniform = 1;
            uint8_t first = len > 0 ? (uint8_t) core->busRead8(core, addr) : 0;
            for (long i = 0; i < len; i++) {
                uint8_t v = (uint8_t) core->busRead8(core, addr + (uint32_t) i);
                crc = crc32(crc, &v, 1);
                if (v != first) uniform = 0;
            }
            fprintf(stderr, "CRC %08X %ld %08lX %d\n", addr, len, (unsigned long) crc, uniform);
            continue;
        }
        if (!strcmp(a, "pc")) {
            fprintf(stderr, "PC %08X @%ld\n", getPc(core), sTotal);
            continue;
        }
        if (!strcmp(a, "pin")) {
            uint32_t addr = (uint32_t) strtoul(b, NULL, 16);
            int len = (int) strlen(c) / 2;
            int slot = 0;
            while (slot < sNumPins && sPins[slot].addr != addr) slot++;
            if (len < 1 || len > 31 || (strlen(c) & 1) || slot >= MAX_PINS) {
                fprintf(stderr, "WARN: bad pin: %s", line);
                continue;
            }
            for (int i = 0; i < len; i++) {
                char hx[3] = {c[2 * i], c[2 * i + 1], 0};
                sPins[slot].bytes[i] = (uint8_t) strtoul(hx, NULL, 16);
            }
            sPins[slot].addr = addr;
            sPins[slot].len = len;
            if (slot == sNumPins) sNumPins++;
            fprintf(stderr, "PIN %08X %d\n", addr, len);
            continue;
        }
        if (!strcmp(a, "unpin")) {
            uint32_t addr = b[0] ? (uint32_t) strtoul(b, NULL, 16) : 0;
            int keep = 0;
            for (int p = 0; p < sNumPins; p++)
                if (b[0] && sPins[p].addr != addr) sPins[keep++] = sPins[p];
            sNumPins = keep;
            fprintf(stderr, "UNPIN %d left\n", sNumPins);
            continue;
        }
        if (!strcmp(a, "w8") || !strcmp(a, "w16") || !strcmp(a, "w32")) {
            uint32_t addr = (uint32_t) strtoul(b, NULL, 16);
            uint32_t val = (uint32_t) strtoul(c, NULL, 16);
            if (!strcmp(a, "w8")) core->busWrite8(core, addr, val & 0xFF);
            if (!strcmp(a, "w16")) core->busWrite16(core, addr, val & 0xFFFF);
            if (!strcmp(a, "w32")) core->busWrite32(core, addr, val);
            fprintf(stderr, "POKE %s %08X = %X\n", a, addr, val);
            continue;
        }
        if (!strcmp(a, "tap")) {
            uint32_t keys = parseKeys(b);
            long idle = c[0] ? atol(c) : 20;
            stepFrames(core, 3, keys);
            stepFrames(core, idle, 0);
            continue;
        }
        if (!strcmp(a, "wait32")) {
            uint32_t addr = (uint32_t) strtoul(b, NULL, 16);
            uint32_t val = (uint32_t) strtoul(c, NULL, 16);
            long maxf = d[0] ? atol(d) : 600;
            uint32_t keys = e[0] ? parseKeys(e) : 0;
            long waited = 0;
            while (waited < maxf && !sCrashed && core->busRead32(core, addr) != val) {
                if (keys && (waited % 30) < 3)
                    stepFrames(core, 1, keys);
                else
                    stepFrames(core, 1, 0);
                waited++;
            }
            if (core->busRead32(core, addr) == val)
                fprintf(stderr, "WAIT ok %08X after %ld @%ld\n", addr, waited, sTotal);
            else
                fprintf(stderr, "WAIT TIMEOUT %08X=%08X want %08X @%ld\n", addr, core->busRead32(core, addr), val, sTotal);
            continue;
        }
        long frames = atol(a);
        if (frames <= 0 && strcmp(a, "0")) { fprintf(stderr, "WARN: bad line: %s", line); continue; }
        stepFrames(core, frames, parseKeys(b));
    }
    fprintf(stderr, "OK: %ld frames pc=%08X%s\n", sTotal, getPc(core), sCrashed ? " CRASHED" : "");
    core->deinit(core);
    return sCrashed ? 3 : 0;
}
