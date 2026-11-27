// Hoenn & Seek (2.0 part 30a): the lost Kangaskhan baby's overworld sprite, used
// for it as your follower and for its map objects in the Fuchsia Safari Zone
// (see HoennIsKangaBabyGfx in src/hoenn_lane_b.c). Included from
// src/event_object_movement.c, after the follower graphics, for the shared
// animation, OAM and subsprite tables. The six 32x32 frames (down, down, up, up,
// side, side, like every follower sheet) are stacked in one 32-pixel-wide
// column, so the default .png -> .4bpp rule gives the frame-by-frame tile order;
// tools/hoenn/draw_kanga_baby.py has the pixel art. Colours are indices into
// Kangaskhan's overworld palette, which the baby borrows.
static const u32 sHoennKangaBabyPic[] = INCBIN_COMP("graphics/hoenn/kanga_baby/overworld.4bpp");

static const struct SpriteFrameImage sPicTable_HoennKangaBaby[] = {
    overworld_ascending_frames(sHoennKangaBabyPic, 4, 4),
};

static const struct ObjectEventGraphicsInfo sHoennKangaBabyGraphicsInfo = {
    .tileTag = TAG_NONE,
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
    .size = 512,
    .width = 32,
    .height = 32,
    .paletteSlot = PALSLOT_NPC_1,
    .shadowSize = SHADOW_SIZE_S,
    .inanimate = FALSE,
    .compressed = OW_GFX_COMPRESS,
    .tracks = TRACKS_FOOT,
    .oam = &gObjectEventBaseOam_32x32,
    .subspriteTables = sOamTables_32x32,
    .anims = sAnimTable_Following,
    .images = sPicTable_HoennKangaBaby,
};
