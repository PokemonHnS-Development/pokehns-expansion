// Hoenn & Seek (2.0 part 13a): data for the decorations in constants/hoenn_decorations.h.
// Included at the end of description.h; HOENN_DECORATION_HEADERS ends gDecorations (header.h)
// and HOENN_DECORATION_ICONS ends gDecorIconTable (icon.h: NULL icons, so the menus draw
// the object sprite, like Emerald's small dolls).

static const u8 DecorDesc_SUDOWOODO_DOLL[] = _(
    "A doll of the\n"
        "POKéMON that\n"
        "poses as a tree.");
static const u16 DecorGfx_SUDOWOODO_DOLL[] = {OBJ_EVENT_GFX_MON_BASE + SPECIES_SUDOWOODO};

static const u8 DecorDesc_SLOWPOKE_DOLL[] = _(
    "A doll of a\n"
        "POKéMON from the\n"
        "SLOWPOKE WELL.");
static const u16 DecorGfx_SLOWPOKE_DOLL[] = {OBJ_EVENT_GFX_MON_BASE + SPECIES_SLOWPOKE};

static const u8 DecorDesc_MAREEP_DOLL[] = _(
    "A fluffy doll.\n"
        "Its wool feels\n"
        "slightly static.");
static const u16 DecorGfx_MAREEP_DOLL[] = {OBJ_EVENT_GFX_MON_BASE + SPECIES_MAREEP};

static const u8 DecorDesc_UNOWN_DOLL[] = _(
    "A doll of a\n"
        "letter from the\n"
        "RUINS OF ALPH.");
static const u16 DecorGfx_UNOWN_DOLL[] = {OBJ_EVENT_GFX_MON_BASE + SPECIES_UNOWN};

static const u8 DecorDesc_VULPIX_DOLL[] = _(
    "A doll of a\n"
        "VULPIX with six\n"
        "curly tails.");
static const u16 DecorGfx_VULPIX_DOLL[] = {OBJ_EVENT_GFX_MON_BASE + SPECIES_VULPIX};

static const u8 DecorDesc_EEVEE_DOLL[] = _(
    "A doll of a\n"
        "POKéMON that can\n"
        "evolve many ways.");
static const u16 DecorGfx_EEVEE_DOLL[] = {OBJ_EVENT_GFX_MON_BASE + SPECIES_EEVEE};

#define HOENN_DECORATION_HEADERS \
    [DECOR_SUDOWOODO_DOLL] = {.id = DECOR_SUDOWOODO_DOLL, .name = _("SUDOWOODO DOLL"), .permission = DECORPERM_SPRITE, \
        .shape = DECORSHAPE_1x1, .category = DECORCAT_DOLL, .price = 6000, \
        .description = DecorDesc_SUDOWOODO_DOLL, .tiles = DecorGfx_SUDOWOODO_DOLL}, \
    [DECOR_SLOWPOKE_DOLL] = {.id = DECOR_SLOWPOKE_DOLL, .name = _("SLOWPOKE DOLL"), .permission = DECORPERM_SPRITE, \
        .shape = DECORSHAPE_1x1, .category = DECORCAT_DOLL, .price = 6000, \
        .description = DecorDesc_SLOWPOKE_DOLL, .tiles = DecorGfx_SLOWPOKE_DOLL}, \
    [DECOR_MAREEP_DOLL] = {.id = DECOR_MAREEP_DOLL, .name = _("MAREEP DOLL"), .permission = DECORPERM_SPRITE, \
        .shape = DECORSHAPE_1x1, .category = DECORCAT_DOLL, .price = 6000, \
        .description = DecorDesc_MAREEP_DOLL, .tiles = DecorGfx_MAREEP_DOLL}, \
    [DECOR_UNOWN_DOLL] = {.id = DECOR_UNOWN_DOLL, .name = _("UNOWN DOLL"), .permission = DECORPERM_SPRITE, \
        .shape = DECORSHAPE_1x1, .category = DECORCAT_DOLL, .price = 6000, \
        .description = DecorDesc_UNOWN_DOLL, .tiles = DecorGfx_UNOWN_DOLL}, \
    [DECOR_VULPIX_DOLL] = {.id = DECOR_VULPIX_DOLL, .name = _("VULPIX DOLL"), .permission = DECORPERM_SPRITE, \
        .shape = DECORSHAPE_1x1, .category = DECORCAT_DOLL, .price = 6000, \
        .description = DecorDesc_VULPIX_DOLL, .tiles = DecorGfx_VULPIX_DOLL}, \
    [DECOR_EEVEE_DOLL] = {.id = DECOR_EEVEE_DOLL, .name = _("EEVEE DOLL"), .permission = DECORPERM_SPRITE, \
        .shape = DECORSHAPE_1x1, .category = DECORCAT_DOLL, .price = 6000, \
        .description = DecorDesc_EEVEE_DOLL, .tiles = DecorGfx_EEVEE_DOLL}, \

#define HOENN_DECORATION_ICONS \
    [DECOR_SUDOWOODO_DOLL] = {NULL, NULL}, \
    [DECOR_SLOWPOKE_DOLL] = {NULL, NULL}, \
    [DECOR_MAREEP_DOLL] = {NULL, NULL}, \
    [DECOR_UNOWN_DOLL] = {NULL, NULL}, \
    [DECOR_VULPIX_DOLL] = {NULL, NULL}, \
    [DECOR_EEVEE_DOLL] = {NULL, NULL}, \
