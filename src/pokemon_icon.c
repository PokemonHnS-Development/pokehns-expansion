#include "global.h"
#include "data.h"
#include "graphics.h"
#include "mail.h"
#include "palette.h"
#include "pokemon_sprite_visualizer.h"
#include "pokemon_icon.h"
#include "sprite.h"
#include "data.h"
#include "constants/pokemon_icon.h"

#define POKE_ICON_SPECIES_BASE_PAL_TAG (POKE_ICON_BASE_PAL_TAG + 16)
#define POKE_ICON_SPECIES_MAX_PAL_TAG (POKE_ICON_SPECIES_BASE_PAL_TAG + NUM_SPECIES + SPECIES_SHINY_TAG)

#define IS_MON_ICON_TAG(x) (((x) >= POKE_ICON_BASE_PAL_TAG && (x) < POKE_ICON_BASE_PAL_TAG + ARRAY_COUNT(gMonIconPaletteTable)) || \
                            ((x) >= POKE_ICON_SPECIES_BASE_PAL_TAG && (x) < POKE_ICON_SPECIES_MAX_PAL_TAG))

#define INVALID_ICON_SPECIES SPECIES_OLD_UNOWN_J // Oddly specific, used when an icon should be a ?. Any of the 'old unown' would work

struct MonIconSpriteTemplate
{
    const struct OamData *oam;
    const u8 *image;
    const union AnimCmd *const *anims;
    const union AffineAnimCmd *const *affineAnims;
    void (*callback)(struct Sprite *);
    u16 paletteTag;
};

static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *, s16, s16, u8);
static void FreeAndDestroyMonIconSprite_(struct Sprite *sprite);

const struct SpritePalette gMonIconPaletteTable[] =
{
    { gMonIconPalettes[0], POKE_ICON_BASE_PAL_TAG + 0 },
    { gMonIconPalettes[1], POKE_ICON_BASE_PAL_TAG + 1 },
    { gMonIconPalettes[2], POKE_ICON_BASE_PAL_TAG + 2 },
    { gMonIconPalettes[3], POKE_ICON_BASE_PAL_TAG + 3 },
    { gMonIconPalettes[4], POKE_ICON_BASE_PAL_TAG + 4 },
    { gMonIconPalettes[5], POKE_ICON_BASE_PAL_TAG + 5 },
};

static const struct OamData sMonIconOamData =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
};

// fastest to slowest

static const union AnimCmd sAnim_0[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_1[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(1, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_2[] =
{
    ANIMCMD_FRAME(0, 14),
    ANIMCMD_FRAME(1, 14),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_3[] =
{
    ANIMCMD_FRAME(0, 22),
    ANIMCMD_FRAME(1, 22),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sAnim_4[] =
{
    ANIMCMD_FRAME(0, 29),
    ANIMCMD_FRAME(0, 29), // frame 0 is repeated
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sMonIconAnims[] =
{
    sAnim_0,
    sAnim_1,
    sAnim_2,
    sAnim_3,
    sAnim_4,
};

static const union AffineAnimCmd sAffineAnim_0[] =
{
    AFFINEANIMCMD_FRAME(0, 0, 0, 10),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd sAffineAnim_1[] =
{
    AFFINEANIMCMD_FRAME(-2, -2, 0, 122),
    AFFINEANIMCMD_END,
};

static const union AffineAnimCmd *const sMonIconAffineAnims[] =
{
    sAffineAnim_0,
    sAffineAnim_1,
};

static const u16 sSpriteImageSizes[3][4] =
{
    [ST_OAM_SQUARE] =
    {
        [SPRITE_SIZE(8x8)]   =  8 * 8  / 2,
        [SPRITE_SIZE(16x16)] = 16 * 16 / 2,
        [SPRITE_SIZE(32x32)] = 32 * 32 / 2,
        [SPRITE_SIZE(64x64)] = 64 * 64 / 2,
    },
    [ST_OAM_H_RECTANGLE] =
    {
        [SPRITE_SIZE(16x8)]  = 16 * 8  / 2,
        [SPRITE_SIZE(32x8)]  = 32 * 8  / 2,
        [SPRITE_SIZE(32x16)] = 32 * 16 / 2,
        [SPRITE_SIZE(64x32)] = 64 * 32 / 2,
    },
    [ST_OAM_V_RECTANGLE] =
    {
        [SPRITE_SIZE(8x16)]  =  8 * 16 / 2,
        [SPRITE_SIZE(8x32)]  =  8 * 32 / 2,
        [SPRITE_SIZE(16x32)] = 16 * 32 / 2,
        [SPRITE_SIZE(32x64)] = 32 * 64 / 2,
    },
};

const u16 gMonIconPalettesCompressed[][16] =
{
    INCBIN_U16("graphics/pokemon/icon_palettes/pal0.gbapal"),
    INCBIN_U16("graphics/pokemon/icon_palettes/pal1.gbapal"),
    INCBIN_U16("graphics/pokemon/icon_palettes/pal2.gbapal"),
    INCBIN_U16("graphics/pokemon/icon_palettes/pal3.gbapal"),
    INCBIN_U16("graphics/pokemon/icon_palettes/pal4.gbapal"),
    INCBIN_U16("graphics/pokemon/icon_palettes/pal5.gbapal"),
};

const u16 * GetIconPalette(u32 species, bool32 isShiny, bool32 female)
{
#if P_GENDER_DIFFERENCES
    if (gSpeciesInfo[species].iconSpriteFemale != NULL && gSpeciesInfo[species].iconPaletteFemale != NULL && female)
        return (isShiny) ? gSpeciesInfo[species].shinyIconPaletteFemale : gSpeciesInfo[species].iconPaletteFemale;
    else
#endif
    if (gSpeciesInfo[species].iconPalette != NULL)
        return (isShiny) ? gSpeciesInfo[species].shinyIconPalette : gSpeciesInfo[species].iconPalette;
    else
        return gMonIconPalettesCompressed[GetMonIconPaletteIndexFromSpecies(species)];
}

const u32 GetIconPalTag(u32 species, bool32 isShiny)
{
    u32 tag = POKE_ICON_SPECIES_BASE_PAL_TAG;
    if (isShiny)
        tag += NUM_SPECIES;
    tag += species;
    return tag;
}

// Find or allocate a palette slot for a pokemon icon
// Prefers unused slots with tags in the icon range (IS_MON_ICON_TAG),
// but if not found, will allocate a new palette slot
u32 FindFreeIconPaletteSlot(u16 tag) 
{
    u32 i;
    u16 tag2, used;
    // look for an unused mon icon slot
    for (i = 0, used = 0; i < MAX_SPRITES; i++) // compute a bitfield of in-use sprite palettes
        if (gSprites[i].inUse)
            used |= 1 << gSprites[i].oam.paletteNum;
    for (i = 0; i < 16; i++) {
        if (used & (1 << i)) // skip in-use palettes
            continue;
        tag2 = GetSpritePaletteTagByPaletteNum(i);
        if (IS_MON_ICON_TAG(tag2))
            return i;
    }
    // Allocate new slot
    return AllocSpritePalette(tag);
}

// Creates mon icon sprite and overwrites its paletteNum
u8 CreateMonIcon3(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, u8 paletteNum, bool32 isEgg) {
    struct MonIconSpriteTemplate iconTemplate =
    {
        .oam = &sMonIconOamData,
        .image = GetMonIconPtrIsEgg(species, personality, isEgg),
        .anims = sMonIconAnims,
        .affineAnims = sMonIconAffineAnims,
        .callback = callback,
        .paletteTag = TAG_NONE,
    };
    u8 spriteId = CreateMonIconSprite(&iconTemplate, x, y, subpriority);
    struct Sprite *sprite = &gSprites[spriteId];

    UpdateMonIconFrame(sprite);
    sprite->oam.paletteNum = paletteNum;
    return spriteId;
}

// Like CreateMonIcon, but also accepts isShiny
u8 CreateMonIcon2(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, bool32 isShiny, u32 personality, bool32 isEgg)
{
    u32 paletteNum;
    const u16 *palette = GetIconPalette(species, isShiny, IsPersonalityFemale(species, personality));
    u16 tag = GetIconPalTag(species, isShiny);

    if ((paletteNum = IndexOfSpritePaletteTag(tag)) >= 16) 
    {
        if ((paletteNum = FindFreeIconPaletteSlot(tag)) < 16) 
        {
            SetSpritePaletteTagByPaletteNum(paletteNum, tag);
            LoadPalette(palette, paletteNum*16 + 0x100, 32);
        }
    }

    return CreateMonIcon3(species, callback, x, y, subpriority, personality, paletteNum, isEgg);
}

// Compatible with vanilla
u8 CreateMonIcon(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality) 
{
    return CreateMonIconIsEgg(species, callback, x, y, subpriority, personality, FALSE);
}

u8 CreateMonIconIsEgg(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority, u32 personality, bool32 isEgg) 
{
    return CreateMonIcon2(species, callback, x, y, subpriority, FALSE, personality, isEgg);
}

// Load the palette for a pokemon into paletteNum,
// optionally overwrite `sprite`'s paletteNum
void SetMonIconPalette(struct Pokemon *mon, struct Sprite *sprite, u8 paletteNum) 
{
    if (paletteNum >= 16)
        return;
    LoadPalette(GetMonFrontSpritePal(mon), paletteNum*16 + 0x100, 32);
    if (sprite)
        sprite->oam.paletteNum = paletteNum;
}

// Only used with mail and mystery event, which cannot really store a bit for a shiny pokemon,
// so we just load the palette into the proper slot by species
// Used by mail/mystery event/other systems which do not store PIDs;
// we just pass 0 as the personality
u8 CreateMonIconNoPersonality(u16 species, void (*callback)(struct Sprite *), s16 x, s16 y, u8 subpriority)
{
    return CreateMonIcon(species, callback, x, y, subpriority, 0);
}

u16 GetIconSpecies(u16 species, u32 personality)
{
    species = SanitizeSpeciesId(species);
    if (species == SPECIES_UNOWN)
        species = GetUnownSpeciesId(personality);
    return species;
}

u16 GetUnownLetterByPersonality(u32 personality)
{
    if (!personality)
        return 0;
    else
        return GET_UNOWN_LETTER(personality);
}

u16 GetIconSpeciesNoPersonality(u16 species)
{
    species = SanitizeSpeciesId(species);

    if (MailSpeciesToSpecies(species, &species) == SPECIES_UNOWN)
        return species += SPECIES_UNOWN_B; // TODO
    return GetIconSpecies(species, 0);
}

// usage in menu.c is unused
const u8 *GetMonIconPtr(u16 species, u32 personality)
{
    return GetMonIconPtrIsEgg(species, personality, FALSE);
}

const u8 *GetMonIconPtrIsEgg(u16 species, u32 personality, bool32 isEgg)
{
    return GetMonIconTilesIsEgg(GetIconSpecies(species, personality), personality, isEgg);
}

void FreeAndDestroyMonIconSprite(struct Sprite *sprite)
{
    FreeAndDestroyMonIconSprite_(sprite);
}

void LoadMonIconPalettes(void)
{
    u8 i;
    for (i = 0; i < ARRAY_COUNT(gMonIconPaletteTable); i++)
        LoadSpritePalette(&gMonIconPaletteTable[i]);
}

void FreeMonIconPalettes(void)
{
    u32 i;
    u16 tag;
    for (i = 0; i < 16; i++) {
        tag = GetSpritePaletteTagByPaletteNum(i);
        if (IS_MON_ICON_TAG(tag))
            SetSpritePaletteTagByPaletteNum(i, TAG_NONE);
    }
}

void SpriteCB_MonIcon(struct Sprite *sprite)
{
    UpdateMonIconFrame(sprite);
}

const u8 *GetMonIconTiles(u16 species, u32 personality)
{
    return GetMonIconTilesIsEgg(species, personality, FALSE);
}

const u8 *GetMonIconTilesIsEgg(u16 species, u32 personality, bool32 isEgg)
{
    const u8 *iconSprite;

    if (species > NUM_SPECIES)
        species = SPECIES_NONE;

    if (isEgg)
    {
        if (gSpeciesInfo[species].eggId != EGG_ID_NONE)
            iconSprite = gEggDatas[gSpeciesInfo[species].eggId].eggIcon;
        else
            iconSprite = gSpeciesInfo[SPECIES_EGG].iconSprite;
    }
    else
    {
#if P_GENDER_DIFFERENCES
        if (gSpeciesInfo[species].iconSpriteFemale != NULL && IsPersonalityFemale(species, personality))
            iconSprite = gSpeciesInfo[species].iconSpriteFemale;
        else
#endif
        if (gSpeciesInfo[species].iconSprite != NULL)
            iconSprite = gSpeciesInfo[species].iconSprite;
        else
            iconSprite = gSpeciesInfo[SPECIES_NONE].iconSprite;
    }

    return iconSprite;
}

// Loads pokemon icon palettes into the BG palettes, in the PC. Changed to always load an all-white palette.
void TryLoadAllMonIconPalettesAtOffset(u16 offset)
{
    s32 i;
    const struct SpritePalette* monIconPalettePtr;
    if (offset <= BG_PLTT_ID(16 - ARRAY_COUNT(gMonIconPaletteTable)))
    {
        u16 whitePalette[16];
        for (i = 0; i < 16; i++)
          whitePalette[i] = 0xFFFF;
        monIconPalettePtr = gMonIconPaletteTable;
        for(i = ARRAY_COUNT(gMonIconPaletteTable) - 1; i >= 0; i--)
        {
            LoadPalette(&whitePalette[0], offset, PLTT_SIZE_4BPP);
            offset += 16;
            monIconPalettePtr++;
        }
    }
}

u8 GetMonIconPaletteIndexFromSpecies(u16 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex;
}

u8 UpdateMonIconFrame(struct Sprite *sprite)
{
    u8 result = 0;

    if (sprite->animDelayCounter == 0)
    {
        s16 frame = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.imageValue;

        switch (frame)
        {
        case -1:
            break;
        case -2:
            sprite->animCmdIndex = 0;
            break;
        default:
            RequestSpriteCopy(
                // pointer arithmetic is needed to get the correct pointer to perform the sprite copy on.
                // because sprite->images is a struct def, it has to be casted to (u8 *) before any
                // arithmetic can be performed.
                (u8 *)sprite->images + (sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] * frame),
                (u8 *)(OBJ_VRAM0 + sprite->oam.tileNum * TILE_SIZE_4BPP),
                sSpriteImageSizes[sprite->oam.shape][sprite->oam.size]);
            sprite->animDelayCounter = sprite->anims[sprite->animNum][sprite->animCmdIndex].frame.duration & 0xFF;
            sprite->animCmdIndex++;
            result = sprite->animCmdIndex;
            break;
        }
    }
    else
    {
        sprite->animDelayCounter--;
    }
    return result;
}

static u8 CreateMonIconSprite(struct MonIconSpriteTemplate *iconTemplate, s16 x, s16 y, u8 subpriority)
{
    u8 spriteId;

    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[iconTemplate->oam->shape][iconTemplate->oam->size] };

    struct SpriteTemplate spriteTemplate =
    {
        .tileTag = TAG_NONE,
        .paletteTag = iconTemplate->paletteTag,
        .oam = iconTemplate->oam,
        .anims = iconTemplate->anims,
        .images = &image,
        .affineAnims = iconTemplate->affineAnims,
        .callback = iconTemplate->callback,
    };

    spriteId = CreateSprite(&spriteTemplate, x, y, subpriority);
    gSprites[spriteId].animPaused = TRUE;
    gSprites[spriteId].animBeginning = FALSE;
    gSprites[spriteId].images = (const struct SpriteFrameImage *)iconTemplate->image;
    return spriteId;
}

static void FreeAndDestroyMonIconSprite_(struct Sprite *sprite)
{
    struct SpriteFrameImage image = { NULL, sSpriteImageSizes[sprite->oam.shape][sprite->oam.size] };
    sprite->images = &image;
    DestroySprite(sprite);
}

void SetPartyHPBarSprite(struct Sprite *sprite, u8 animNum)
{
    sprite->animNum = animNum;
    sprite->animDelayCounter = 0;
    sprite->animCmdIndex = 0;
}
