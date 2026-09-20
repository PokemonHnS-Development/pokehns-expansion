#ifdef __INTELLISENSE__
const struct SpeciesInfo gSpeciesInfoGen9[] =
{
#endif

#if P_FAMILY_SPRIGATITO
    [SPECIES_SPRIGATITO] =
    {
        .baseHP        = 40,
        .baseAttack    = 61,
        .baseDefense   = 54,
        .baseSpeed     = 65,
        .baseSpAttack  = 45,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 62,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_PROTEAN },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SPRIGATITO"),
        .cryId = CRY_SPRIGATITO,
        .natDexNum = NATIONAL_DEX_SPRIGATITO,
        .categoryName = _("Gato Planta"),
        .height = 4,
        .weight = 41,
        .description = COMPOUND_STRING(
            "El dulce aroma que desprende su\n"
            "hipnotiza a quienes lo rodean. El\n"
            "aroma es más fuerte cuando este\n"
            "Pokémon is in the sun."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sprigatito,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Sprigatito,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sprigatito,
        .shinyPalette = gMonShinyPalette_Sprigatito,
        .iconSprite = gMonIcon_Sprigatito,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 5, SHADOW_SIZE_S)
        FOOTPRINT(Sprigatito)
        OVERWORLD(
            sPicTable_Sprigatito,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Sprigatito,
            gShinyOverworldPalette_Sprigatito
        )
        .levelUpLearnset = sSprigatitoLevelUpLearnset,
        .teachableLearnset = sSprigatitoTeachableLearnset,
        .eggMoveLearnset = sSprigatitoEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_FLORAGATO}),
    },

    [SPECIES_FLORAGATO] =
    {
        .baseHP        = 61,
        .baseAttack    = 80,
        .baseDefense   = 63,
        .baseSpeed     = 83,
        .baseSpAttack  = 60,
        .baseSpDefense = 63,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 45,
        .expYield = 144,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_PROTEAN },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("FLORAGATO"),
        .cryId = CRY_FLORAGATO,
        .natDexNum = NATIONAL_DEX_FLORAGATO,
        .categoryName = _("Gato Planta"),
        .height = 9,
        .weight = 122,
        .description = COMPOUND_STRING(
            "Floragato usa con destreza la liana\n"
            "oculta bajo su pelaje, golpeando\n"
            "el duro capullo contra su\n"
            "opponents."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Floragato,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Floragato,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Floragato,
        .shinyPalette = gMonShinyPalette_Floragato,
        .iconSprite = gMonIcon_Floragato,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 11, SHADOW_SIZE_M)
        FOOTPRINT(Floragato)
        OVERWORLD(
            sPicTable_Floragato,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Floragato,
            gShinyOverworldPalette_Floragato
        )
        .levelUpLearnset = sFloragatoLevelUpLearnset,
        .teachableLearnset = sFloragatoTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_MEOWSCARADA}),
    },

    [SPECIES_MEOWSCARADA] =
    {
        .baseHP        = 76,
        .baseAttack    = 110,
        .baseDefense   = 70,
        .baseSpeed     = 123,
        .baseSpAttack  = 81,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GRASS, TYPE_DARK),
        .catchRate = 45,
        .expYield = 265,
        .evYield_Speed = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_GRASS),
        .abilities = { ABILITY_OVERGROW, ABILITY_NONE, ABILITY_PROTEAN },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("MEOWSCARADA"),
        .cryId = CRY_MEOWSCARADA,
        .natDexNum = NATIONAL_DEX_MEOWSCARADA,
        .categoryName = _("Mago"),
        .height = 15,
        .weight = 312,
        .description = COMPOUND_STRING(
            "Este POKéMON usa el reflejo de\n"
            "forro de piel en su capa para\n"
            "camuflar el tallo de su flor, y\n"
            "illusion that the flower is floating."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Meowscarada,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Meowscarada,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Meowscarada,
        .shinyPalette = gMonShinyPalette_Meowscarada,
        .iconSprite = gMonIcon_Meowscarada,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 14, SHADOW_SIZE_S)
        FOOTPRINT(Meowscarada)
        OVERWORLD(
            sPicTable_Meowscarada,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Meowscarada,
            gShinyOverworldPalette_Meowscarada
        )
        .levelUpLearnset = sMeowscaradaLevelUpLearnset,
        .teachableLearnset = sMeowscaradaTeachableLearnset,
    },
#endif //P_FAMILY_SPRIGATITO

#if P_FAMILY_FUECOCO
    [SPECIES_FUECOCO] =
    {
        .baseHP        = 67,
        .baseAttack    = 45,
        .baseDefense   = 59,
        .baseSpeed     = 36,
        .baseSpAttack  = 63,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 62,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_UNAWARE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("FUECOCO"),
        .cryId = CRY_FUECOCO,
        .natDexNum = NATIONAL_DEX_FUECOCO,
        .categoryName = _("Cocodrilo Fuego"),
        .height = 4,
        .weight = 98,
        .description = COMPOUND_STRING(
            "Su saco de fuego es pequeño, por lo\n"
            "que la energía se escapa. Esta\n"
            "sale por la muesca de su cabeza\n"
            "Fuecoco's head and flickers to and fro."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fuecoco,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Fuecoco,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fuecoco,
        .shinyPalette = gMonShinyPalette_Fuecoco,
        .iconSprite = gMonIcon_Fuecoco,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-3, 5, SHADOW_SIZE_S)
        FOOTPRINT(Fuecoco)
        OVERWORLD(
            sPicTable_Fuecoco,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Fuecoco,
            gShinyOverworldPalette_Fuecoco
        )
        .levelUpLearnset = sFuecocoLevelUpLearnset,
        .teachableLearnset = sFuecocoTeachableLearnset,
        .eggMoveLearnset = sFuecocoEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_CROCALOR}),
    },

    [SPECIES_CROCALOR] =
    {
        .baseHP        = 81,
        .baseAttack    = 55,
        .baseDefense   = 78,
        .baseSpeed     = 49,
        .baseSpAttack  = 90,
        .baseSpDefense = 58,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 45,
        .expYield = 144,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_UNAWARE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("CROCALOR"),
        .cryId = CRY_CROCALOR,
        .natDexNum = NATIONAL_DEX_CROCALOR,
        .categoryName = _("Cocodrilo Fuego"),
        .height = 10,
        .weight = 307,
        .description = COMPOUND_STRING(
            "La energía de fuego de Crocalor y\n"
            "su gran vitalidad han creado una\n"
            "bola de fuego en forma de huevo\n"
            "appear on the Pokémon's head."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Crocalor,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Crocalor,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Crocalor,
        .shinyPalette = gMonShinyPalette_Crocalor,
        .iconSprite = gMonIcon_Crocalor,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 8, SHADOW_SIZE_M)
        FOOTPRINT(Crocalor)
        OVERWORLD(
            sPicTable_Crocalor,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Crocalor,
            gShinyOverworldPalette_Crocalor
        )
        .levelUpLearnset = sCrocalorLevelUpLearnset,
        .teachableLearnset = sCrocalorTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_SKELEDIRGE}),
    },

    [SPECIES_SKELEDIRGE] =
    {
        .baseHP        = 104,
        .baseAttack    = 75,
        .baseDefense   = 100,
        .baseSpeed     = 66,
        .baseSpAttack  = 110,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 265,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_BLAZE, ABILITY_NONE, ABILITY_UNAWARE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("SKELEDIRGE"),
        .cryId = CRY_SKELEDIRGE,
        .natDexNum = NATIONAL_DEX_SKELEDIRGE,
        .categoryName = _("Cantante"),
        .height = 16,
        .weight = 3265,
        .description = COMPOUND_STRING(
            "El canto suave de Skeledirge\n"
            "calma el alma de quien lo oye. Es\n"
            "capaz de calcinar a sus enemigos con\n"
            "flames of over 5,400 degrees Fahrenheit."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Skeledirge,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Skeledirge,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Skeledirge,
        .shinyPalette = gMonShinyPalette_Skeledirge,
        .iconSprite = gMonIcon_Skeledirge,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(6, 7, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Skeledirge)
        OVERWORLD(
            sPicTable_Skeledirge,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Skeledirge,
            gShinyOverworldPalette_Skeledirge
        )
        .levelUpLearnset = sSkeledirgeLevelUpLearnset,
        .teachableLearnset = sSkeledirgeTeachableLearnset,
    },
#endif //P_FAMILY_FUECOCO

#if P_FAMILY_QUAXLY
    [SPECIES_QUAXLY] =
    {
        .baseHP        = 55,
        .baseAttack    = 65,
        .baseDefense   = 45,
        .baseSpeed     = 50,
        .baseSpAttack  = 50,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield =  62,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_MOXIE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("QUAXLY"),
        .cryId = CRY_QUAXLY,
        .natDexNum = NATIONAL_DEX_QUAXLY,
        .categoryName = _("Patito"),
        .height = 5,
        .weight = 61,
        .description = COMPOUND_STRING(
            "Sus fuertes patas le permiten nadar\n"
            "incluso en ríos de corriente rápida.\n"
            "Le gusta mantener todo ordenado y es\n"
            "prone to overthinking things."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Quaxly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Quaxly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Quaxly,
        .shinyPalette = gMonShinyPalette_Quaxly,
        .iconSprite = gMonIcon_Quaxly,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, 5, SHADOW_SIZE_S)
        FOOTPRINT(Quaxly)
        OVERWORLD(
            sPicTable_Quaxly,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Quaxly,
            gShinyOverworldPalette_Quaxly
        )
        .levelUpLearnset = sQuaxlyLevelUpLearnset,
        .teachableLearnset = sQuaxlyTeachableLearnset,
        .eggMoveLearnset = sQuaxlyEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_QUAXWELL}),
    },

    [SPECIES_QUAXWELL] =
    {
        .baseHP        = 70,
        .baseAttack    = 85,
        .baseDefense   = 65,
        .baseSpeed     = 65,
        .baseSpAttack  = 65,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 144,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_MOXIE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("QUAXWELL"),
        .cryId = CRY_QUAXWELL,
        .natDexNum = NATIONAL_DEX_QUAXWELL,
        .categoryName = _("Practicando"),
        .height = 12,
        .weight = 215,
        .description = COMPOUND_STRING(
            "El dedicado Quaxwell observa\n"
            "personas y POKéMON de varias\n"
            "regiones e incorpora sus\n"
            "movements into its own dance routines."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Quaxwell,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Quaxwell,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Quaxwell,
        .shinyPalette = gMonShinyPalette_Quaxwell,
        .iconSprite = gMonIcon_Quaxwell,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 10, SHADOW_SIZE_S)
        FOOTPRINT(Quaxwell)
        OVERWORLD(
            sPicTable_Quaxwell,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Quaxwell,
            gShinyOverworldPalette_Quaxwell
        )
        .levelUpLearnset = sQuaxwellLevelUpLearnset,
        .teachableLearnset = sQuaxwellTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_QUAQUAVAL}),
    },

    [SPECIES_QUAQUAVAL] =
    {
        .baseHP        = 85,
        .baseAttack    = 120,
        .baseDefense   = 80,
        .baseSpeed     = 85,
        .baseSpAttack  = 85,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_WATER, TYPE_FIGHTING),
        .catchRate = 45,
        .expYield = 265,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_WATER_1),
        .abilities = { ABILITY_TORRENT, ABILITY_NONE, ABILITY_MOXIE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("QUAQUAVAL"),
        .cryId = CRY_QUAQUAVAL,
        .natDexNum = NATIONAL_DEX_QUAQUAVAL,
        .categoryName = _("Bailarín"),
        .height = 18,
        .weight = 619,
        .description = COMPOUND_STRING(
            "Una patada de Quaquaval puede\n"
            "empujar un camión. Este POKéMON\n"
            "usa sus fuertes patas para bailar\n"
            "striking dances from far-off lands."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Quaquaval,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Quaquaval,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Quaquaval,
        .shinyPalette = gMonShinyPalette_Quaquaval,
        .iconSprite = gMonIcon_Quaquaval,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-7, 13, SHADOW_SIZE_M)
        FOOTPRINT(Quaquaval)
        OVERWORLD(
            sPicTable_Quaquaval,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Quaquaval,
            gShinyOverworldPalette_Quaquaval
        )
        .levelUpLearnset = sQuaquavalLevelUpLearnset,
        .teachableLearnset = sQuaquavalTeachableLearnset,
    },
#endif //P_FAMILY_QUAXLY

#if P_FAMILY_LECHONK
    [SPECIES_LECHONK] =
    {
        .baseHP        = 54,
        .baseAttack    = 45,
        .baseDefense   = 40,
        .baseSpeed     = 35,
        .baseSpAttack  = 35,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 51,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_AROMA_VEIL, ABILITY_GLUTTONY, ABILITY_THICK_FAT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("LECHONK"),
        .cryId = CRY_LECHONK,
        .natDexNum = NATIONAL_DEX_LECHONK,
        .categoryName = _("Hog"),
        .height = 5,
        .weight = 102,
        .description = COMPOUND_STRING(
            "Busca comida todo el día. Tiene\n"
            "un gran olfato, pero no lo usa\n"
            "para nada más que buscar comida\n"
            "than foraging."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Lechonk,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Lechonk,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Lechonk,
        .shinyPalette = gMonShinyPalette_Lechonk,
        .iconSprite = gMonIcon_Lechonk,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(0, 1, SHADOW_SIZE_S)
        FOOTPRINT(Lechonk)
        OVERWORLD(
            sPicTable_Lechonk,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Lechonk,
            gShinyOverworldPalette_Lechonk
        )
        .levelUpLearnset = sLechonkLevelUpLearnset,
        .teachableLearnset = sLechonkTeachableLearnset,
        .eggMoveLearnset = sLechonkEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_OINKOLOGNE_M, CONDITIONS({IF_GENDER, MON_MALE})},
                                {EVO_LEVEL, 18, SPECIES_OINKOLOGNE_F, CONDITIONS({IF_GENDER, MON_FEMALE})}),
    },

    [SPECIES_OINKOLOGNE_M] =
    {
        .baseHP        = 110,
        .baseAttack    = 100,
        .baseDefense   = 75,
        .baseSpeed     = 65,
        .baseSpAttack  = 59,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 100,
        .expYield = 171,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(0),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_LINGERING_AROMA, ABILITY_GLUTTONY, ABILITY_THICK_FAT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("OINKOLOGNE"),
        .cryId = CRY_OINKOLOGNE_M,
        .natDexNum = NATIONAL_DEX_OINKOLOGNE,
        .categoryName = _("Hog"),
        .height = 10,
        .weight = 1200,
        .description = COMPOUND_STRING("Oinkologne presume de su piel\nfina y brillante. Emite un aroma\npor la punta de su cola.\n"),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_OinkologneM,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_OinkologneM,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_OinkologneM,
        .shinyPalette = gMonShinyPalette_OinkologneM,
        .iconSprite = gMonIcon_OinkologneM,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 6, SHADOW_SIZE_M)
        FOOTPRINT(Oinkologne)
        OVERWORLD(
            sPicTable_OinkologneM,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_OinkologneM,
            gShinyOverworldPalette_OinkologneM
        )
        .levelUpLearnset = sOinkologneMLevelUpLearnset,
        .teachableLearnset = sOinkologneTeachableLearnset,
        .formSpeciesIdTable = sOinkologneFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_RANDOM_FORM,
    },

    [SPECIES_OINKOLOGNE_F] =
    {
        .baseHP        = 115,
        .baseAttack    = 90,
        .baseDefense   = 70,
        .baseSpeed     = 65,
        .baseSpAttack  = 59,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 100,
        .expYield = 171,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(100),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_AROMA_VEIL, ABILITY_GLUTTONY, ABILITY_THICK_FAT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("OINKOLOGNE"),
        .cryId = CRY_OINKOLOGNE_F,
        .natDexNum = NATIONAL_DEX_OINKOLOGNE,
        .categoryName = _("Hog"),
        .height = 10,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "Es un POKéMON meticuloso que\n"
            "ama mantener todo ordenado. Se\n"
            "rodea de un aroma floral que\n"
            "soothes the Pokémon around it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_OinkologneF,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_OinkologneF,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_OinkologneF,
        .shinyPalette = gMonShinyPalette_OinkologneF,
        .iconSprite = gMonIcon_OinkologneF,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 6, SHADOW_SIZE_M)
        FOOTPRINT(Oinkologne)
        OVERWORLD(
            sPicTable_OinkologneF,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_OinkologneF,
            gShinyOverworldPalette_OinkologneF
        )
        .levelUpLearnset = sOinkologneFLevelUpLearnset,
        .teachableLearnset = sOinkologneTeachableLearnset,
        .formSpeciesIdTable = sOinkologneFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_FAMILY_LECHONK

#if P_FAMILY_TAROUNTULA
    [SPECIES_TAROUNTULA] =
    {
        .baseHP        = 35,
        .baseAttack    = 41,
        .baseDefense   = 45,
        .baseSpeed     = 20,
        .baseSpAttack  = 29,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 255,
        .expYield = 42,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_INSOMNIA, ABILITY_NONE, ABILITY_STAKEOUT },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("TAROUNTULA"),
        .cryId = CRY_TAROUNTULA,
        .natDexNum = NATIONAL_DEX_TAROUNTULA,
        .categoryName = _("String Ball"),
        .height = 3,
        .weight = 40,
        .description = COMPOUND_STRING(
            "El hilo que segrega por su parte\n"
            "trasera es fuerte como un cable.\n"
            "El secreto de su fuerza es la\n"
            "topic of ongoing research."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tarountula,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tarountula,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tarountula,
        .shinyPalette = gMonShinyPalette_Tarountula,
        .iconSprite = gMonIcon_Tarountula,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 2, SHADOW_SIZE_M)
        FOOTPRINT(Tarountula)
        OVERWORLD(
            sPicTable_Tarountula,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_BUG,
            sAnimTable_Following,
            gOverworldPalette_Tarountula,
            gShinyOverworldPalette_Tarountula
        )
        .levelUpLearnset = sTarountulaLevelUpLearnset,
        .teachableLearnset = sTarountulaTeachableLearnset,
        .eggMoveLearnset = sTarountulaEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 15, SPECIES_SPIDOPS}),
    },

    [SPECIES_SPIDOPS] =
    {
        .baseHP        = 60,
        .baseAttack    = 79,
        .baseDefense   = 92,
        .baseSpeed     = 35,
        .baseSpAttack  = 52,
        .baseSpDefense = 86,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 120,
        .expYield = 141,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_INSOMNIA, ABILITY_NONE, ABILITY_STAKEOUT },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SPIDOPS"),
        .cryId = CRY_SPIDOPS,
        .natDexNum = NATIONAL_DEX_SPIDOPS,
        .categoryName = _("Trampa"),
        .height = 10,
        .weight = 165,
        .description = COMPOUND_STRING(
            "Se aferra a ramas y techos\n"
            "usa sus hilos y se mueve sin\n"
            "hacer ruido. Atrapa a su presa\n"
            "before the prey even notices it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Spidops,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Spidops,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Spidops,
        .shinyPalette = gMonShinyPalette_Spidops,
        .iconSprite = gMonIcon_Spidops,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(6, 8, SHADOW_SIZE_L)
        FOOTPRINT(Spidops)
        OVERWORLD(
            sPicTable_Spidops,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Spidops,
            gShinyOverworldPalette_Spidops
        )
        .levelUpLearnset = sSpidopsLevelUpLearnset,
        .teachableLearnset = sSpidopsTeachableLearnset,
    },
#endif //P_FAMILY_TAROUNTULA

#if P_FAMILY_NYMBLE
    [SPECIES_NYMBLE] =
    {
        .baseHP        = 33,
        .baseAttack    = 46,
        .baseDefense   = 40,
        .baseSpeed     = 45,
        .baseSpAttack  = 21,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 190,
        .expYield = 42,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 20,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SWARM, ABILITY_NONE, ABILITY_TINTED_LENS },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("NYMBLE"),
        .cryId = CRY_NYMBLE,
        .natDexNum = NATIONAL_DEX_NYMBLE,
        .categoryName = _("Saltamontes"),
        .height = 2,
        .weight = 10,
        .description = COMPOUND_STRING(
            "Tiene su tercer par de patas\n"
            "plegado. En apuros, este\n"
            "Pokémon salta más de 9 metros.\n"
            "strength of its legs."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Nymble,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Nymble,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Nymble,
        .shinyPalette = gMonShinyPalette_Nymble,
        .iconSprite = gMonIcon_Nymble,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(1, 3, SHADOW_SIZE_M)
        FOOTPRINT(Nymble)
        OVERWORLD(
            sPicTable_Nymble,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_BUG,
            sAnimTable_Following,
            gOverworldPalette_Nymble,
            gShinyOverworldPalette_Nymble
        )
        .levelUpLearnset = sNymbleLevelUpLearnset,
        .teachableLearnset = sNymbleTeachableLearnset,
        .eggMoveLearnset = sNymbleEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_LOKIX}),
    },

    [SPECIES_LOKIX] =
    {
        .baseHP        = 71,
        .baseAttack    = 102,
        .baseDefense   = 78,
        .baseSpeed     = 92,
        .baseSpAttack  = 52,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_BUG, TYPE_DARK),
        .catchRate = 30,
        .expYield = 158,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SWARM, ABILITY_NONE, ABILITY_TINTED_LENS },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("LOKIX"),
        .cryId = CRY_LOKIX,
        .natDexNum = NATIONAL_DEX_LOKIX,
        .categoryName = _("Saltamontes"),
        .height = 10,
        .weight = 175,
        .description = COMPOUND_STRING(
            "Cuando decide luchar a fondo, se\n"
            "apoya en sus patas plegadas\n"
            "para entrar en Modo Duelo.\n"
            "neutralizes its enemies in short order."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Lokix,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Lokix,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Lokix,
        .shinyPalette = gMonShinyPalette_Lokix,
        .iconSprite = gMonIcon_Lokix,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 11, SHADOW_SIZE_M)
        FOOTPRINT(Lokix)
        OVERWORLD(
            sPicTable_Lokix,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Lokix,
            gShinyOverworldPalette_Lokix
        )
        .levelUpLearnset = sLokixLevelUpLearnset,
        .teachableLearnset = sLokixTeachableLearnset,
    },
#endif //P_FAMILY_NYMBLE

#if P_FAMILY_PAWMI
    [SPECIES_PAWMI] =
    {
        .baseHP        = 45,
        .baseAttack    = 50,
        .baseDefense   = 20,
        .baseSpeed     = 60,
        .baseSpAttack  = 40,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 190,
        .expYield = 48,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_STATIC, ABILITY_NATURAL_CURE, ABILITY_IRON_FIST },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("PAWMI"),
        .cryId = CRY_PAWMI,
        .natDexNum = NATIONAL_DEX_PAWMI,
        .categoryName = _("Ratón"),
        .height = 3,
        .weight = 25,
        .description = COMPOUND_STRING(
            "Las almohadillas de sus patas son\n"
            "órganos eléctricos. Pawmi lanza\n"
            "electricidad de sus patas delanteras\n"
            "standing unsteadily on its hind legs."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Pawmi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pawmi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pawmi,
        .shinyPalette = gMonShinyPalette_Pawmi,
        .iconSprite = gMonIcon_Pawmi,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(1, 4, SHADOW_SIZE_M)
        FOOTPRINT(Pawmi)
            OVERWORLD(
            sPicTable_Pawmi,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Pawmi,
            gShinyOverworldPalette_Pawmi
        )
        .levelUpLearnset = sPawmiLevelUpLearnset,
        .teachableLearnset = sPawmiTeachableLearnset,
        .eggMoveLearnset = sPawmiEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_PAWMO}),
    },

    [SPECIES_PAWMO] =
    {
        .baseHP        = 60,
        .baseAttack    = 75,
        .baseDefense   = 40,
        .baseSpeed     = 85,
        .baseSpAttack  = 50,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIGHTING),
        .catchRate = 80,
        .expYield = 123,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_VOLT_ABSORB, ABILITY_NATURAL_CURE, ABILITY_IRON_FIST },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("PAWMO"),
        .cryId = CRY_PAWMO,
        .natDexNum = NATIONAL_DEX_PAWMO,
        .categoryName = _("Ratón"),
        .height = 4,
        .weight = 65,
        .description = COMPOUND_STRING(
            "Si atacan a su grupo, Pawmo es el\n"
            "primero en saltar al combate y\n"
            "derrotando enemigos con un ataque\n"
            "technique that utilizes electric shocks."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Pawmo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pawmo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pawmo,
        .shinyPalette = gMonShinyPalette_Pawmo,
        .iconSprite = gMonIcon_Pawmo,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-3, 10, SHADOW_SIZE_S)
        FOOTPRINT(Pawmo)
        OVERWORLD(
            sPicTable_Pawmo,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Pawmo,
            gShinyOverworldPalette_Pawmo
        )
        .levelUpLearnset = sPawmoLevelUpLearnset,
        .teachableLearnset = sPawmoTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_PAWMOT, CONDITIONS({IF_MIN_OVERWORLD_STEPS, 1000})}),
    },

    [SPECIES_PAWMOT] =
    {
        .baseHP        = 70,
        .baseAttack    = 115,
        .baseDefense   = 70,
        .baseSpeed     = 105,
        .baseSpAttack  = 70,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FIGHTING),
        .catchRate = 45,
        .expYield = 245,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_VOLT_ABSORB, ABILITY_NATURAL_CURE, ABILITY_IRON_FIST },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("PAWMOT"),
        .cryId = CRY_PAWMOT,
        .natDexNum = NATIONAL_DEX_PAWMOT,
        .categoryName = _("Manos a la obra"),
        .height = 9,
        .weight = 410,
        .description = COMPOUND_STRING(
            "Este POKéMON suele reaccionar\n"
            "lento, pero al entrar en batalla\n"
            "derribará a sus enemigos con\n"
            "lightning-fast movements."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Pawmot,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pawmot,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pawmot,
        .shinyPalette = gMonShinyPalette_Pawmot,
        .iconSprite = gMonIcon_Pawmot,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 11, SHADOW_SIZE_M)
        FOOTPRINT(Pawmot)
        OVERWORLD(
            sPicTable_Pawmot,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Pawmot,
            gShinyOverworldPalette_Pawmot
        )
        .levelUpLearnset = sPawmotLevelUpLearnset,
        .teachableLearnset = sPawmotTeachableLearnset,
    },
#endif //P_FAMILY_PAWMI

#if P_FAMILY_TANDEMAUS
    [SPECIES_TANDEMAUS] =
    {
        .baseHP        = 50,
        .baseAttack    = 50,
        .baseDefense   = 45,
        .baseSpeed     = 75,
        .baseSpAttack  = 40,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 150,
        .expYield = 61,
        .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_PICKUP, ABILITY_OWN_TEMPO },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("TANDEMAUS"),
        .cryId = CRY_TANDEMAUS,
        .natDexNum = NATIONAL_DEX_TANDEMAUS,
        .categoryName = _("Pareja"),
        .height = 3,
        .weight = 18,
        .description = COMPOUND_STRING(
            "Con un gran trabajo en equipo, ellos\n"
            "trozos de cualquier material que\n"
            "de cualquier material que sea útil\n"
            "for a nest, then make off with them."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tandemaus,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tandemaus,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tandemaus,
        .shinyPalette = gMonShinyPalette_Tandemaus,
        .iconSprite = gMonIcon_Tandemaus,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(0, -1, SHADOW_SIZE_M)
        FOOTPRINT(Tandemaus)
        OVERWORLD(
            sPicTable_Tandemaus,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Tandemaus,
            gShinyOverworldPalette_Tandemaus
        )
        .levelUpLearnset = sTandemausLevelUpLearnset,
        .teachableLearnset = sTandemausTeachableLearnset,
        .eggMoveLearnset = sTandemausEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL_BATTLE_ONLY, 25, SPECIES_MAUSHOLD_FOUR, CONDITIONS({IF_PID_MODULO_100_GT, 0})},
                                {EVO_LEVEL_BATTLE_ONLY, 25, SPECIES_MAUSHOLD_THREE, CONDITIONS({IF_PID_MODULO_100_EQ, 0})}),
    },

    [SPECIES_MAUSHOLD_THREE] =
    {
        .baseHP        = 74,
        .baseAttack    = 75,
        .baseDefense   = 70,
        .baseSpeed     = 111,
        .baseSpAttack  = 65,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 75,
        .expYield = 165,
        .evYield_Speed = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_FRIEND_GUARD, ABILITY_CHEEK_POUCH, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("MAUSHOLD"),
        .cryId = CRY_MAUSHOLD_THREE,
        .natDexNum = NATIONAL_DEX_MAUSHOLD,
        .categoryName = _("Familia"),
        .height = 3,
        .weight = 23,
        .description = COMPOUND_STRING(
            "El pequeño acaba de aparecer una\n"
            "familia, pero la relación entre\n"
            "familia, pero la relación entre\n"
            "the three is still unclear."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MausholdThree,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_MausholdThree,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_Maushold,
        .shinyPalette = gMonShinyPalette_Maushold,
        .iconSprite = gMonIcon_MausholdThree,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(4, -1, SHADOW_SIZE_L)
        FOOTPRINT(MausholdThree)
        OVERWORLD(
            sPicTable_MausholdThree,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_MausholdThree,
            gShinyOverworldPalette_MausholdThree
        )
        .levelUpLearnset = sMausholdLevelUpLearnset,
        .teachableLearnset = sMausholdTeachableLearnset,
        .formSpeciesIdTable = sMausholdFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_SPECIAL_FORM,
    },

    [SPECIES_MAUSHOLD_FOUR] =
    {
        .baseHP        = 74,
        .baseAttack    = 75,
        .baseDefense   = 70,
        .baseSpeed     = 111,
        .baseSpAttack  = 65,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 75,
        .expYield = 165,
        .evYield_Speed = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 10,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_FAIRY),
        .abilities = { ABILITY_FRIEND_GUARD, ABILITY_CHEEK_POUCH, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("MAUSHOLD"),
        .cryId = CRY_MAUSHOLD_FOUR,
        .natDexNum = NATIONAL_DEX_MAUSHOLD,
        .categoryName = _("Familia"),
        .height = 3,
        .weight = 28,
        .description = COMPOUND_STRING(
            "La pareja mayor protege a los\n"
            "pequeños en combate. Al luchar\n"
            "rivales fuertes, todo el grupo\n"
            "will join the fight."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MausholdFour,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 15,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_MausholdFour,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_Maushold,
        .shinyPalette = gMonShinyPalette_Maushold,
        .iconSprite = gMonIcon_MausholdFour,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, -1, SHADOW_SIZE_L)
        FOOTPRINT(MausholdFour)
        OVERWORLD(
            sPicTable_MausholdFour,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_MausholdFour,
            gShinyOverworldPalette_MausholdFour
        )
        .levelUpLearnset = sMausholdLevelUpLearnset,
        .teachableLearnset = sMausholdTeachableLearnset,
        .formSpeciesIdTable = sMausholdFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_FAMILY_TANDEMAUS

#if P_FAMILY_FIDOUGH
    [SPECIES_FIDOUGH] =
    {
        .baseHP        = 37,
        .baseAttack    = 55,
        .baseDefense   = 70,
        .baseSpeed     = 65,
        .baseSpAttack  = 30,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_FAIRY),
        .catchRate = 190,
        .expYield = 62,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_OWN_TEMPO, ABILITY_NONE, ABILITY_KLUTZ },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("FIDOUGH"),
        .cryId = CRY_FIDOUGH,
        .natDexNum = NATIONAL_DEX_FIDOUGH,
        .categoryName = _("Puppy"),
        .height = 3,
        .weight = 109,
        .description = COMPOUND_STRING(
            "Este POKéMON es suave y húmedo\n"
            "al tacto. La levadura en el aliento\n"
            "de Fidough induce la fermentación.\n"
            "Pokémon's vicinity."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fidough,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Fidough,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fidough,
        .shinyPalette = gMonShinyPalette_Fidough,
        .iconSprite = gMonIcon_Fidough,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(4, 0, SHADOW_SIZE_S)
        FOOTPRINT(Fidough)
        OVERWORLD(
            sPicTable_Fidough,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Fidough,
            gShinyOverworldPalette_Fidough
        )
        .levelUpLearnset = sFidoughLevelUpLearnset,
        .teachableLearnset = sFidoughTeachableLearnset,
        .eggMoveLearnset = sFidoughEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 26, SPECIES_DACHSBUN}),
    },

    [SPECIES_DACHSBUN] =
    {
        .baseHP        = 57,
        .baseAttack    = 80,
        .baseDefense   = 115,
        .baseSpeed     = 95,
        .baseSpAttack  = 50,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FAIRY),
        .catchRate = 90,
        .expYield = 167,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_WELL_BAKED_BODY, ABILITY_NONE, ABILITY_AROMA_VEIL },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("DACHSBUN"),
        .cryId = CRY_DACHSBUN,
        .natDexNum = NATIONAL_DEX_DACHSBUN,
        .categoryName = _("Dog"),
        .height = 5,
        .weight = 149,
        .description = COMPOUND_STRING(
            "El aroma agradable que emana de\n"
            "su cuerpo ayuda a que el trigo\n"
            "crezca, así que Dachsbun es útil.\n"
            "treasured by farming villages."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dachsbun,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Dachsbun,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dachsbun,
        .shinyPalette = gMonShinyPalette_Dachsbun,
        .iconSprite = gMonIcon_Dachsbun,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-1, 7, SHADOW_SIZE_L)
        FOOTPRINT(Dachsbun)
        OVERWORLD(
            sPicTable_Dachsbun,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Dachsbun,
            gShinyOverworldPalette_Dachsbun
        )
        .levelUpLearnset = sDachsbunLevelUpLearnset,
        .teachableLearnset = sDachsbunTeachableLearnset,
    },
#endif //P_FAMILY_FIDOUGH

#if P_FAMILY_SMOLIV
    [SPECIES_SMOLIV] =
    {
        .baseHP        = 41,
        .baseAttack    = 35,
        .baseDefense   = 45,
        .baseSpeed     = 30,
        .baseSpAttack  = 58,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 52,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_EARLY_BIRD, ABILITY_NONE, ABILITY_HARVEST },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SMOLIV"),
        .cryId = CRY_SMOLIV,
        .natDexNum = NATIONAL_DEX_SMOLIV,
        .categoryName = _("Olivo"),
        .height = 3,
        .weight = 65,
        .description = COMPOUND_STRING(
            "Este POKéMON convierte nutrientes\n"
            "en aceite, que guarda en el fruto\n"
            "de su cabeza. Puede pasar fácilmente\n"
            "week without eating or drinking."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Smoliv,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Smoliv,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Smoliv,
        .shinyPalette = gMonShinyPalette_Smoliv,
        .iconSprite = gMonIcon_Smoliv,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-1, -2, SHADOW_SIZE_S)
        FOOTPRINT(Smoliv)
        OVERWORLD(
            sPicTable_Smoliv,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Smoliv,
            gShinyOverworldPalette_Smoliv
        )
        .levelUpLearnset = sSmolivLevelUpLearnset,
        .teachableLearnset = sSmolivTeachableLearnset,
        .eggMoveLearnset = sSmolivEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_DOLLIV}),
    },

    [SPECIES_DOLLIV] =
    {
        .baseHP        = 52,
        .baseAttack    = 53,
        .baseDefense   = 60,
        .baseSpeed     = 33,
        .baseSpAttack  = 78,
        .baseSpDefense = 78,
        .types = MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 120,
        .expYield = 124,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_EARLY_BIRD, ABILITY_NONE, ABILITY_HARVEST },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("DOLLIV"),
        .cryId = CRY_DOLLIV,
        .natDexNum = NATIONAL_DEX_DOLLIV,
        .categoryName = _("Olivo"),
        .height = 6,
        .weight = 119,
        .description = COMPOUND_STRING(
            "Dolliv comparte su aceite fresco y\n"
            "aromático con otros. Esta especie\n"
            "ha coexistido con humanos desde\n"
            "times long gone."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dolliv,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Dolliv,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dolliv,
        .shinyPalette = gMonShinyPalette_Dolliv,
        .iconSprite = gMonIcon_Dolliv,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(1, 9, SHADOW_SIZE_M)
        FOOTPRINT(Dolliv)
        OVERWORLD(
            sPicTable_Dolliv,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Dolliv,
            gShinyOverworldPalette_Dolliv
        )
        .levelUpLearnset = sDollivLevelUpLearnset,
        .teachableLearnset = sDollivTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_ARBOLIVA}),
    },

    [SPECIES_ARBOLIVA] =
    {
        .baseHP        = 78,
        .baseAttack    = 69,
        .baseDefense   = 90,
        .baseSpeed     = 39,
        .baseSpAttack  = 125,
        .baseSpDefense = 109,
        .types = MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 45,
        .expYield = 255,
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_SEED_SOWER, ABILITY_NONE, ABILITY_HARVEST },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("ARBOLIVA"),
        .cryId = CRY_ARBOLIVA,
        .natDexNum = NATIONAL_DEX_ARBOLIVA,
        .categoryName = _("Olivo"),
        .height = 14,
        .weight = 482,
        .description = COMPOUND_STRING(
            "Este POKéMON ahuyenta enemigos\n"
            "lanzando su aceite aromático con\n"
            "fuerza suficiente para aplastar algo\n"
            "boulder."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Arboliva,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Arboliva,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Arboliva,
        .shinyPalette = gMonShinyPalette_Arboliva,
        .iconSprite = gMonIcon_Arboliva,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 13, SHADOW_SIZE_L)
        FOOTPRINT(Arboliva)
        OVERWORLD(
            sPicTable_Arboliva,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Arboliva,
            gShinyOverworldPalette_Arboliva
        )
        .levelUpLearnset = sArbolivaLevelUpLearnset,
        .teachableLearnset = sArbolivaTeachableLearnset,
    },
#endif //P_FAMILY_SMOLIV

#if P_FAMILY_SQUAWKABILLY
    [SPECIES_SQUAWKABILLY_GREEN] =
    {
        .baseHP        = 82,
        .baseAttack    = 96,
        .baseDefense   = 51,
        .baseSpeed     = 92,
        .baseSpAttack  = 45,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE, ABILITY_GUTS },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SQUAWKABILLY"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Loro"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "Las bandadas de plumas verdes\n"
            "mandan más. Cuando salen\n"
            "a buscar comida por las mañanas y\n"
            "evenings, it gets very noisy."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_SquawkabillyGreen,
        .shinyPalette = gMonShinyPalette_SquawkabillyGreen,
        .iconSprite = gMonIcon_SquawkabillyGreen,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-6, 9, SHADOW_SIZE_M)
        FOOTPRINT(Squawkabilly)
        OVERWORLD(
            sPicTable_SquawkabillyGreen,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_SquawkabillyGreen,
            gShinyOverworldPalette_SquawkabillyGreen
        )
        .levelUpLearnset = sSquawkabillyLevelUpLearnset,
        .teachableLearnset = sSquawkabillyTeachableLearnset,
        .eggMoveLearnset = sSquawkabillyEggMoveLearnset,
        .formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_RANDOM_FORM,
    },

    [SPECIES_SQUAWKABILLY_BLUE] =
    {
        .baseHP        = 82,
        .baseAttack    = 96,
        .baseDefense   = 51,
        .baseSpeed     = 92,
        .baseSpAttack  = 45,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE, ABILITY_GUTS },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("SQUAWKABILLY"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Loro"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "Sus bandadas más grandes pueden\n"
            "tener más de 50 individuos. Ellos\n"
            "vuelan por pueblos y bosques,\n"
            "searching for food and making a racket."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_SquawkabillyBlue,
        .shinyPalette = gMonShinyPalette_SquawkabillyBlue,
        .iconSprite = gMonIcon_SquawkabillyBlue,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-6, 9, SHADOW_SIZE_M)
        FOOTPRINT(Squawkabilly)
        OVERWORLD(
            sPicTable_SquawkabillyBlue,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_SquawkabillyBlue,
            gShinyOverworldPalette_SquawkabillyBlue
        )
        .levelUpLearnset = sSquawkabillyLevelUpLearnset,
        .teachableLearnset = sSquawkabillyTeachableLearnset,
        .eggMoveLearnset = sSquawkabillyEggMoveLearnset,
        .formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },

    [SPECIES_SQUAWKABILLY_YELLOW] =
    {
        .baseHP        = 82,
        .baseAttack    = 96,
        .baseDefense   = 51,
        .baseSpeed     = 92,
        .baseSpAttack  = 45,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE, ABILITY_SHEER_FORCE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("SQUAWKABILLY"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Loro"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING(
            "Estos Squawkabilly son impulsivos,\n"
            "y su estilo de lucha es feroz.\n"
            "Saltarán hasta alcanzar a su\n"
            "foes to engage in close combat."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_SquawkabillyYellow,
        .shinyPalette = gMonShinyPalette_SquawkabillyYellow,
        .iconSprite = gMonIcon_SquawkabillyYellow,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-6, 9, SHADOW_SIZE_M)
        FOOTPRINT(Squawkabilly)
        OVERWORLD(
            sPicTable_SquawkabillyYellow,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_SquawkabillyYellow,
            gShinyOverworldPalette_SquawkabillyYellow
        )
        .levelUpLearnset = sSquawkabillyLevelUpLearnset,
        .teachableLearnset = sSquawkabillyTeachableLearnset,
        .eggMoveLearnset = sSquawkabillyEggMoveLearnset,
        .formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },

    [SPECIES_SQUAWKABILLY_WHITE] =
    {
        .baseHP        = 82,
        .baseAttack    = 96,
        .baseDefense   = 51,
        .baseSpeed     = 92,
        .baseSpAttack  = 45,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FLYING),
        .catchRate = 190,
        .expYield = 146,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_HUSTLE, ABILITY_SHEER_FORCE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("SQUAWKABILLY"),
        .cryId = CRY_SQUAWKABILLY,
        .natDexNum = NATIONAL_DEX_SQUAWKABILLY,
        .categoryName = _("Loro"),
        .height = 6,
        .weight = 24,
        .description = COMPOUND_STRING("Aunque estos Squawkabilly son los\nmenos numerosos, no tienen\nproblemas en pueblos pues se mezclan\ncon los edificios blancos.\n"),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Squawkabilly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_Squawkabilly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_SquawkabillyWhite,
        .shinyPalette = gMonShinyPalette_SquawkabillyWhite,
        .iconSprite = gMonIcon_SquawkabillyWhite,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-6, 9, SHADOW_SIZE_M)
        FOOTPRINT(Squawkabilly)
        OVERWORLD(
            sPicTable_SquawkabillyWhite,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_SquawkabillyWhite,
            gShinyOverworldPalette_SquawkabillyWhite
        )
        .levelUpLearnset = sSquawkabillyLevelUpLearnset,
        .teachableLearnset = sSquawkabillyTeachableLearnset,
        .eggMoveLearnset = sSquawkabillyEggMoveLearnset,
        .formSpeciesIdTable = sSquawkabillyFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_FAMILY_SQUAWKABILLY

#if P_FAMILY_NACLI
    [SPECIES_NACLI] =
    {
        .baseHP        = 55,
        .baseAttack    = 55,
        .baseDefense   = 75,
        .baseSpeed     = 25,
        .baseSpAttack  = 35,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 255,
        .expYield = 56,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_PURIFYING_SALT, ABILITY_STURDY, ABILITY_CLEAR_BODY },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("NACLI"),
        .cryId = CRY_NACLI,
        .natDexNum = NATIONAL_DEX_NACLI,
        .categoryName = _("Sal de roca"),
        .height = 4,
        .weight = 160,
        .description = COMPOUND_STRING(
            "El suelo raspa su cuerpo al\n"
            "viajar, dejando rastros de sal\n"
            "detrás. Crea sal constantemente.\n"
            "and replenished inside Nacli's body."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Nacli,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Nacli,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Nacli,
        .shinyPalette = gMonShinyPalette_Nacli,
        .iconSprite = gMonIcon_Nacli,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-1, 5, SHADOW_SIZE_S)
        FOOTPRINT(Nacli)
        OVERWORLD(
            sPicTable_Nacli,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Nacli,
            gShinyOverworldPalette_Nacli
        )
        .levelUpLearnset = sNacliLevelUpLearnset,
        .teachableLearnset = sNacliTeachableLearnset,
        .eggMoveLearnset = sNacliEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_NACLSTACK}),
    },

    [SPECIES_NACLSTACK] =
    {
        .baseHP        = 60,
        .baseAttack    = 60,
        .baseDefense   = 100,
        .baseSpeed     = 35,
        .baseSpAttack  = 35,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 120,
        .expYield = 124,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_PURIFYING_SALT, ABILITY_STURDY, ABILITY_CLEAR_BODY },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("NACLSTACK"),
        .cryId = CRY_NACLSTACK,
        .natDexNum = NATIONAL_DEX_NACLSTACK,
        .categoryName = _("Sal de roca"),
        .height = 6,
        .weight = 1050,
        .description = COMPOUND_STRING(
            "Comprime sal de roca en su cuerpo\n"
            "y dispara perdigones de sal dura\n"
            "con fuerza suficiente para herir.\n"
            "perforate an iron sheet."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Naclstack,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Naclstack,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Naclstack,
        .shinyPalette = gMonShinyPalette_Naclstack,
        .iconSprite = gMonIcon_Naclstack,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(0, 0, SHADOW_SIZE_L)
        FOOTPRINT(Naclstack)
        OVERWORLD(
            sPicTable_Naclstack,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Naclstack,
            gShinyOverworldPalette_Naclstack
        )
        .levelUpLearnset = sNaclstackLevelUpLearnset,
        .teachableLearnset = sNaclstackTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 38, SPECIES_GARGANACL}),
    },

    [SPECIES_GARGANACL] =
    {
        .baseHP        = 100,
        .baseAttack    = 100,
        .baseDefense   = 130,
        .baseSpeed     = 35,
        .baseSpAttack  = 45,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 45,
        .expYield = 250,
        .evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_PURIFYING_SALT, ABILITY_STURDY, ABILITY_CLEAR_BODY },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("GARGANACL"),
        .cryId = CRY_GARGANACL,
        .natDexNum = NATIONAL_DEX_GARGANACL,
        .categoryName = _("Sal de roca"),
        .height = 23,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "Garganacl frota sus dedos y esparce\n"
            "sal sobre los heridos.\n"
            "Pokémon de sal. Incluso heridas\n"
            "promptly heal afterward."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Garganacl,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Garganacl,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Garganacl,
        .shinyPalette = gMonShinyPalette_Garganacl,
        .iconSprite = gMonIcon_Garganacl,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 13, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Garganacl)
        OVERWORLD(
            sPicTable_Garganacl,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Garganacl,
            gShinyOverworldPalette_Garganacl
        )
        .levelUpLearnset = sGarganaclLevelUpLearnset,
        .teachableLearnset = sGarganaclTeachableLearnset,
    },
#endif //P_FAMILY_NACLI

#if P_FAMILY_CHARCADET
    [SPECIES_CHARCADET] =
    {
        .baseHP        = 40,
        .baseAttack    = 50,
        .baseDefense   = 40,
        .baseSpeed     = 35,
        .baseSpAttack  = 50,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_FIRE),
        .catchRate = 90,
        .expYield = 51,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE, ABILITY_FLAME_BODY },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("CHARCADET"),
        .cryId = CRY_CHARCADET,
        .natDexNum = NATIONAL_DEX_CHARCADET,
        .categoryName = _("Niño Fuego"),
        .height = 6,
        .weight = 105,
        .description = COMPOUND_STRING(
            "Carbón quemado que cobró vida y\n"
            "se volvió un Pokémon. Con un\n"
            "espíritu ardiente, Charcadet\n"
            "battle even tough opponents."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Charcadet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Charcadet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Charcadet,
        .shinyPalette = gMonShinyPalette_Charcadet,
        .iconSprite = gMonIcon_Charcadet,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-1, 5, SHADOW_SIZE_S)
        FOOTPRINT(Charcadet)
        OVERWORLD(
            sPicTable_Charcadet,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Charcadet,
            gShinyOverworldPalette_Charcadet
        )
        .levelUpLearnset = sCharcadetLevelUpLearnset,
        .teachableLearnset = sCharcadetTeachableLearnset,
        .eggMoveLearnset = sCharcadetEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_FIRE_STONE, SPECIES_ARMAROUGE},
                                {EVO_ITEM, ITEM_DUSK_STONE, SPECIES_CERULEDGE},
                                {EVO_ITEM, ITEM_AUSPICIOUS_ARMOR, SPECIES_ARMAROUGE},
                                {EVO_ITEM, ITEM_MALICIOUS_ARMOR, SPECIES_CERULEDGE}),
    },

    [SPECIES_ARMAROUGE] =
    {
        .baseHP        = 85,
        .baseAttack    = 60,
        .baseDefense   = 100,
        .baseSpeed     = 75,
        .baseSpAttack  = 125,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_FIRE, TYPE_PSYCHIC),
        .catchRate = 25,
        .expYield = 263,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 20,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE, ABILITY_WEAK_ARMOR },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("ARMAROUGE"),
        .cryId = CRY_ARMAROUGE,
        .natDexNum = NATIONAL_DEX_ARMAROUGE,
        .categoryName = _("Guerrero Fuego"),
        .height = 15,
        .weight = 850,
        .description = COMPOUND_STRING(
            "Armarouge evolucionó usando una\n"
            "armadura que perteneció a un\n"
            "guerrero distinguido. Este\n"
            "Pokémon is incredibly loyal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Armarouge,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Armarouge,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Armarouge,
        .shinyPalette = gMonShinyPalette_Armarouge,
        .iconSprite = gMonIcon_Armarouge,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 14, SHADOW_SIZE_L)
        FOOTPRINT(Armarouge)
        OVERWORLD(
            sPicTable_Armarouge,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Armarouge,
            gShinyOverworldPalette_Armarouge
        )
        .levelUpLearnset = sArmarougeLevelUpLearnset,
        .teachableLearnset = sArmarougeTeachableLearnset,
    },

    [SPECIES_CERULEDGE] =
    {
        .baseHP        = 75,
        .baseAttack    = 125,
        .baseDefense   = 80,
        .baseSpeed     = 85,
        .baseSpAttack  = 60,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GHOST),
        .catchRate = 25,
        .expYield = 263,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 20,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_NONE, ABILITY_WEAK_ARMOR },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("CERULEDGE"),
        .cryId = CRY_CERULEDGE,
        .natDexNum = NATIONAL_DEX_CERULEDGE,
        .categoryName = _("Hojas de Fuego"),
        .height = 16,
        .weight = 620,
        .description = COMPOUND_STRING(
            "Las hojas de fuego en sus brazos\n"
            "arden con fuerza por el rencor\n"
            "de un espadachín que cayó.\n"
            "before accomplishing their goal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Ceruledge,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Ceruledge,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Ceruledge,
        .shinyPalette = gMonShinyPalette_Ceruledge,
        .iconSprite = gMonIcon_Ceruledge,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(9, 14, SHADOW_SIZE_L)
        FOOTPRINT(Ceruledge)
        OVERWORLD(
            sPicTable_Ceruledge,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Ceruledge,
            gShinyOverworldPalette_Ceruledge
        )
        .levelUpLearnset = sCeruledgeLevelUpLearnset,
        .teachableLearnset = sCeruledgeTeachableLearnset,
    },
#endif //P_FAMILY_CHARCADET

#if P_FAMILY_TADBULB
    [SPECIES_TADBULB] =
    {
        .baseHP        = 61,
        .baseAttack    = 31,
        .baseDefense   = 41,
        .baseSpeed     = 45,
        .baseSpAttack  = 59,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 190,
        .expYield = 54,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_OWN_TEMPO, ABILITY_STATIC, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("TADBULB"),
        .cryId = CRY_TADBULB,
        .natDexNum = NATIONAL_DEX_TADBULB,
        .categoryName = _("EleRenacuajo"),
        .height = 3,
        .weight = 4,
        .description = COMPOUND_STRING(
            "Tadbulb agita su cola para\n"
            "generate electricity. If it senses danger,\n"
            "hará que su cabeza parpadee\n"
            "to alert its allies."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tadbulb,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 12,
        .backPic = gMonBackPic_Tadbulb,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tadbulb,
        .shinyPalette = gMonShinyPalette_Tadbulb,
        .iconSprite = gMonIcon_Tadbulb,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 19, SHADOW_SIZE_S)
        FOOTPRINT(Tadbulb)
        OVERWORLD(
            sPicTable_Tadbulb,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Tadbulb,
            gShinyOverworldPalette_Tadbulb
        )
        .levelUpLearnset = sTadbulbLevelUpLearnset,
        .teachableLearnset = sTadbulbTeachableLearnset,
        .eggMoveLearnset = sTadbulbEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_THUNDER_STONE, SPECIES_BELLIBOLT}),
    },

    [SPECIES_BELLIBOLT] =
    {
        .baseHP        = 109,
        .baseAttack    = 64,
        .baseDefense   = 91,
        .baseSpeed     = 45,
        .baseSpAttack  = 103,
        .baseSpDefense = 83,
        .types = MON_TYPES(TYPE_ELECTRIC),
        .catchRate = 50,
        .expYield = 173,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1),
        .abilities = { ABILITY_ELECTROMORPHOSIS, ABILITY_STATIC, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("BELLIBOLT"),
        .cryId = CRY_BELLIBOLT,
        .natDexNum = NATIONAL_DEX_BELLIBOLT,
        .categoryName = _("EleRana"),
        .height = 12,
        .weight = 1130,
        .description = COMPOUND_STRING(
            "Cuando este POKéMON se expande y\n"
            "contrae su cuerpo, el botón\n"
            "dinamo de su estómago\n"
            "produces a huge amount of electricity."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bellibolt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Bellibolt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Bellibolt,
        .shinyPalette = gMonShinyPalette_Bellibolt,
        .iconSprite = gMonIcon_Bellibolt,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 7, SHADOW_SIZE_M)
        FOOTPRINT(Bellibolt)
        OVERWORLD(
            sPicTable_Bellibolt,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Bellibolt,
            gShinyOverworldPalette_Bellibolt
        )
        .levelUpLearnset = sBelliboltLevelUpLearnset,
        .teachableLearnset = sBelliboltTeachableLearnset,
    },
#endif //P_FAMILY_TADBULB

#if P_FAMILY_WATTREL
    [SPECIES_WATTREL] =
    {
        .baseHP        = 40,
        .baseAttack    = 40,
        .baseDefense   = 35,
        .baseSpeed     = 70,
        .baseSpAttack  = 55,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FLYING),
        .catchRate = 180,
        .expYield = 56,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FLYING),
        .abilities = { ABILITY_WIND_POWER, ABILITY_VOLT_ABSORB, ABILITY_COMPETITIVE },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("WATTREL"),
        .cryId = CRY_WATTREL,
        .natDexNum = NATIONAL_DEX_WATTREL,
        .categoryName = _("Pájaro Tormenta"),
        .height = 4,
        .weight = 36,
        .description = COMPOUND_STRING(
            "Cuando el viento sopla en sus alas,\n"
            "sus huesos generan electricidad.\n"
            "Este POKéMON se zambulle al mar,\n"
            "catching prey by electrocuting them."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Wattrel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Wattrel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Wattrel,
        .shinyPalette = gMonShinyPalette_Wattrel,
        .iconSprite = gMonIcon_Wattrel,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 0, SHADOW_SIZE_S)
        FOOTPRINT(Wattrel)
        OVERWORLD(
            sPicTable_Wattrel,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Wattrel,
            gShinyOverworldPalette_Wattrel
        )
        .levelUpLearnset = sWattrelLevelUpLearnset,
        .teachableLearnset = sWattrelTeachableLearnset,
        .eggMoveLearnset = sWattrelEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_KILOWATTREL}),
    },

    [SPECIES_KILOWATTREL] =
    {
        .baseHP        = 70,
        .baseAttack    = 70,
        .baseDefense   = 60,
        .baseSpeed     = 125,
        .baseSpAttack  = 105,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_FLYING),
        .catchRate = 90,
        .expYield = 172,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FLYING),
        .abilities = { ABILITY_WIND_POWER, ABILITY_VOLT_ABSORB, ABILITY_COMPETITIVE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("KILOWATTREL"),
        .cryId = CRY_KILOWATTREL,
        .natDexNum = NATIONAL_DEX_KILOWATTREL,
        .categoryName = _("Fragata"),
        .height = 14,
        .weight = 386,
        .description = COMPOUND_STRING(
            "Usa su saco gular para guardar la\n"
            "electricidad de sus alas.\n"
            "Casi no hay aceite en sus plumas,\n"
            "so it is a poor swimmer."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Kilowattrel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Kilowattrel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Kilowattrel,
        .shinyPalette = gMonShinyPalette_Kilowattrel,
        .iconSprite = gMonIcon_Kilowattrel,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-6, 6, SHADOW_SIZE_M)
        FOOTPRINT(Kilowattrel)
        OVERWORLD(
            sPicTable_Kilowattrel,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Kilowattrel,
            gShinyOverworldPalette_Kilowattrel
        )
        .levelUpLearnset = sKilowattrelLevelUpLearnset,
        .teachableLearnset = sKilowattrelTeachableLearnset,
    },
#endif //P_FAMILY_WATTREL

#if P_FAMILY_MASCHIFF
    [SPECIES_MASCHIFF] =
    {
        .baseHP        = 60,
        .baseAttack    = 78,
        .baseDefense   = 60,
        .baseSpeed     = 51,
        .baseSpAttack  = 40,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 150,
        .expYield = 68,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_RUN_AWAY, ABILITY_STAKEOUT },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("MASCHIFF"),
        .cryId = CRY_MASCHIFF,
        .natDexNum = NATIONAL_DEX_MASCHIFF,
        .categoryName = _("Travieso"),
        .height = 5,
        .weight = 160,
        .description = COMPOUND_STRING(
            "Su mandíbula y colmillos fuertes\n"
            "son capaces de triturar incluso\n"
            "rocas, y su espesa grasa hace\n"
            "for an excellent defense."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Maschiff,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Maschiff,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Maschiff,
        .shinyPalette = gMonShinyPalette_Maschiff,
        .iconSprite = gMonIcon_Maschiff,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(2, 5, SHADOW_SIZE_L)
        FOOTPRINT(Maschiff)
        OVERWORLD(
            sPicTable_Maschiff,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Maschiff,
            gShinyOverworldPalette_Maschiff
        )
        .levelUpLearnset = sMaschiffLevelUpLearnset,
        .teachableLearnset = sMaschiffTeachableLearnset,
        .eggMoveLearnset = sMaschiffEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_MABOSSTIFF}),
    },

    [SPECIES_MABOSSTIFF] =
    {
        .baseHP        = 80,
        .baseAttack    = 120,
        .baseDefense   = 90,
        .baseSpeed     = 85,
        .baseSpAttack  = 60,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 75,
        .expYield = 177,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_GUARD_DOG, ABILITY_STAKEOUT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("MABOSSTIFF"),
        .cryId = CRY_MABOSSTIFF,
        .natDexNum = NATIONAL_DEX_MABOSSTIFF,
        .categoryName = _("Jefe"),
        .height = 11,
        .weight = 610,
        .description = COMPOUND_STRING(
            "A Mabosstiff le encanta jugar con\n"
            "niños. Aunque es gentil, se ve\n"
            "se ve intimidante cuando\n"
            "protecting its family."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Mabosstiff,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Mabosstiff,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Mabosstiff,
        .shinyPalette = gMonShinyPalette_Mabosstiff,
        .iconSprite = gMonIcon_Mabosstiff,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 5, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Mabosstiff)
        OVERWORLD(
            sPicTable_Mabosstiff,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Mabosstiff,
            gShinyOverworldPalette_Mabosstiff
        )
        .levelUpLearnset = sMabosstiffLevelUpLearnset,
        .teachableLearnset = sMabosstiffTeachableLearnset,
    },
#endif //P_FAMILY_MASCHIFF

#if P_FAMILY_SHROODLE
    [SPECIES_SHROODLE] =
    {
        .baseHP        = 40,
        .baseAttack    = 65,
        .baseDefense   = 35,
        .baseSpeed     = 75,
        .baseSpAttack  = 40,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_POISON, TYPE_NORMAL),
        .catchRate = 190,
        .expYield = 58,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_UNBURDEN, ABILITY_PICKPOCKET, ABILITY_PRANKSTER },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("SHROODLE"),
        .cryId = CRY_SHROODLE,
        .natDexNum = NATIONAL_DEX_SHROODLE,
        .categoryName = _("Ratón Tóxico"),
        .height = 2,
        .weight = 7,
        .description = COMPOUND_STRING(
            "Para alejar enemigos de su\n"
            "territorio, pinta marcas cerca de su\n"
            "nido usando un líquido venenoso que\n"
            "has an acrid odor."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Shroodle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 17,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Shroodle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Shroodle,
        .shinyPalette = gMonShinyPalette_Shroodle,
        .iconSprite = gMonIcon_Shroodle,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(0, -6, SHADOW_SIZE_S)
        FOOTPRINT(Shroodle)
        OVERWORLD(
            sPicTable_Shroodle,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_BUG,
            sAnimTable_Following,
            gOverworldPalette_Shroodle,
            gShinyOverworldPalette_Shroodle
        )
        .levelUpLearnset = sShroodleLevelUpLearnset,
        .teachableLearnset = sShroodleTeachableLearnset,
        .eggMoveLearnset = sShroodleEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 28, SPECIES_GRAFAIAI}),
    },

    [SPECIES_GRAFAIAI] =
    {
        .baseHP        = 63,
        .baseAttack    = 95,
        .baseDefense   = 65,
        .baseSpeed     = 110,
        .baseSpAttack  = 80,
        .baseSpDefense = 72,
        .types = MON_TYPES(TYPE_POISON, TYPE_NORMAL),
        .catchRate = 90,
        .expYield = 170,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_UNBURDEN, ABILITY_POISON_TOUCH, ABILITY_PRANKSTER },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("GRAFAIAI"),
        .cryId = CRY_GRAFAIAI,
        .natDexNum = NATIONAL_DEX_GRAFAIAI,
        .categoryName = _("Mono Tóxico"),
        .height = 7,
        .weight = 272,
        .description = COMPOUND_STRING(
            "Cada Grafaiai pinta su propio\n"
            "patrón individual, y pintará ese\n"
            "mismo patrón una y otra vez\n"
            "throughout its life."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Grafaiai,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Grafaiai,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Grafaiai,
        .shinyPalette = gMonShinyPalette_Grafaiai,
        .iconSprite = gMonIcon_Grafaiai,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 5, SHADOW_SIZE_S)
        FOOTPRINT(Grafaiai)
        OVERWORLD(
            sPicTable_Grafaiai,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Grafaiai,
            gShinyOverworldPalette_Grafaiai
        )
        .levelUpLearnset = sGrafaiaiLevelUpLearnset,
        .teachableLearnset = sGrafaiaiTeachableLearnset,
    },
#endif //P_FAMILY_SHROODLE

#if P_FAMILY_BRAMBLIN
    [SPECIES_BRAMBLIN] =
    {
        .baseHP        = 40,
        .baseAttack    = 65,
        .baseDefense   = 30,
        .baseSpeed     = 60,
        .baseSpAttack  = 45,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 190,
        .expYield = 55,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_WIND_RIDER, ABILITY_NONE, ABILITY_INFILTRATOR },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("BRAMBLIN"),
        .cryId = CRY_BRAMBLIN,
        .natDexNum = NATIONAL_DEX_BRAMBLIN,
        .categoryName = _("Estepicursor"),
        .height = 6,
        .weight = 6,
        .description = COMPOUND_STRING(
            "Un alma que no pudo pasar al\n"
            "más allá fue arrastrada por el viento\n"
            "hasta que se enredó con zarzas\n"
            "grass and became a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bramblin,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Bramblin,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Bramblin,
        .shinyPalette = gMonShinyPalette_Bramblin,
        .iconSprite = gMonIcon_Bramblin,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(2, 0, SHADOW_SIZE_S)
        FOOTPRINT(Bramblin)
        OVERWORLD(
            sPicTable_Bramblin,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Bramblin,
            gShinyOverworldPalette_Bramblin
        )
        .levelUpLearnset = sBramblinLevelUpLearnset,
        .teachableLearnset = sBramblinTeachableLearnset,
        .eggMoveLearnset = sBramblinEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_BRAMBLEGHAST, CONDITIONS({IF_MIN_OVERWORLD_STEPS, 1000})}),
    },

    [SPECIES_BRAMBLEGHAST] =
    {
        .baseHP        = 55,
        .baseAttack    = 115,
        .baseDefense   = 70,
        .baseSpeed     = 90,
        .baseSpAttack  = 80,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 168,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_WIND_RIDER, ABILITY_NONE, ABILITY_INFILTRATOR },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("BRAMBLEGHAST"),
        .cryId = CRY_BRAMBLEGHAST,
        .natDexNum = NATIONAL_DEX_BRAMBLEGHAST,
        .categoryName = _("Estepicursor"),
        .height = 12,
        .weight = 60,
        .description = COMPOUND_STRING(
            "Abre las ramas de su cabeza para\n"
            "envolver a su presa. Una vez que\n"
            "absorbe la energía vital, se va.\n"
            "expels the prey and discards it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Brambleghast,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Brambleghast,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Brambleghast,
        .shinyPalette = gMonShinyPalette_Brambleghast,
        .iconSprite = gMonIcon_Brambleghast,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 6, SHADOW_SIZE_M)
        FOOTPRINT(Brambleghast)
        OVERWORLD(
            sPicTable_Brambleghast,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Brambleghast,
            gShinyOverworldPalette_Brambleghast
        )
        .levelUpLearnset = sBrambleghastLevelUpLearnset,
        .teachableLearnset = sBrambleghastTeachableLearnset,
    },
#endif //P_FAMILY_BRAMBLIN

#if P_FAMILY_TOEDSCOOL
    [SPECIES_TOEDSCOOL] =
    {
        .baseHP        = 40,
        .baseAttack    = 40,
        .baseDefense   = 35,
        .baseSpeed     = 70,
        .baseSpAttack  = 50,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 190,
        .expYield = 67,
        .evYield_SpDefense = 1,
        .itemCommon = ITEM_TINY_MUSHROOM,
        .itemRare = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_MYCELIUM_MIGHT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("TOEDSCOOL"),
        .cryId = CRY_TOEDSCOOL,
        .natDexNum = NATIONAL_DEX_TOEDSCOOL,
        .categoryName = _("Woodear"),
        .height = 9,
        .weight = 330,
        .description = COMPOUND_STRING(
            "Aunque se parece a Tentacool,\n"
            "Toedscool es una especie totalmente\n"
            "distinta. Sus patas son finas, pero\n"
            "can run at a speed of 30 mph."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Toedscool,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Toedscool,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Toedscool,
        .shinyPalette = gMonShinyPalette_Toedscool,
        .iconSprite = gMonIcon_Toedscool,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 10, SHADOW_SIZE_M)
        FOOTPRINT(Toedscool)
        OVERWORLD(
            sPicTable_Toedscool,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Toedscool,
            gShinyOverworldPalette_Toedscool
        )
        .levelUpLearnset = sToedscoolLevelUpLearnset,
        .teachableLearnset = sToedscoolTeachableLearnset,
        .eggMoveLearnset = sToedscoolEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_TOEDSCRUEL}),
    },

    [SPECIES_TOEDSCRUEL] =
    {
        .baseHP        = 80,
        .baseAttack    = 70,
        .baseDefense   = 65,
        .baseSpeed     = 100,
        .baseSpAttack  = 80,
        .baseSpDefense = 120,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 90,
        .expYield = 180,
        .evYield_SpDefense = 2,
        .itemCommon = ITEM_TINY_MUSHROOM,
        .itemRare = ITEM_BIG_MUSHROOM,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_MYCELIUM_MIGHT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("TOEDSCRUEL"),
        .cryId = CRY_TOEDSCRUEL,
        .natDexNum = NATIONAL_DEX_TOEDSCRUEL,
        .categoryName = _("Woodear"),
        .height = 19,
        .weight = 580,
        .description = COMPOUND_STRING(
            "Estos POKéMON se reúnen en grupos\n"
            "y forman colonias en lo profundo de\n"
            "los bosques. Odian que alguien\n"
            "strangers approach."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Toedscruel,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Toedscruel,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Toedscruel,
        .shinyPalette = gMonShinyPalette_Toedscruel,
        .iconSprite = gMonIcon_Toedscruel,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 8, SHADOW_SIZE_L)
        FOOTPRINT(Toedscruel)
        OVERWORLD(
            sPicTable_Toedscruel,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Toedscruel,
            gShinyOverworldPalette_Toedscruel
        )
        .levelUpLearnset = sToedscruelLevelUpLearnset,
        .teachableLearnset = sToedscruelTeachableLearnset,
    },
#endif //P_FAMILY_TOEDSCOOL

#if P_FAMILY_KLAWF
    [SPECIES_KLAWF] =
    {
        .baseHP        = 70,
        .baseAttack    = 100,
        .baseDefense   = 115,
        .baseSpeed     = 75,
        .baseSpAttack  = 35,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 120,
        .expYield = 158,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_ANGER_SHELL, ABILITY_SHELL_ARMOR, ABILITY_REGENERATOR },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("KLAWF"),
        .cryId = CRY_KLAWF,
        .natDexNum = NATIONAL_DEX_KLAWF,
        .categoryName = _("Emboscada"),
        .height = 13,
        .weight = 790,
        .description = COMPOUND_STRING(
            "Klawf cuelga boca abajo de los\n"
            "acantilados esperando presas. Pero\n"
            "no puede estar así mucho tiempo\n"
            "because its blood rushes to its head."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Klawf,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Klawf,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 20,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Klawf,
        .shinyPalette = gMonShinyPalette_Klawf,
        .iconSprite = gMonIcon_Klawf,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 0, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Klawf)
        OVERWORLD(
            sPicTable_Klawf,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Klawf,
            gShinyOverworldPalette_Klawf
        )
        .levelUpLearnset = sKlawfLevelUpLearnset,
        .teachableLearnset = sKlawfTeachableLearnset,
        .eggMoveLearnset = sKlawfEggMoveLearnset,
    },
#endif //P_FAMILY_KLAWF

#if P_FAMILY_CAPSAKID
    [SPECIES_CAPSAKID] =
    {
        .baseHP        = 50,
        .baseAttack    = 62,
        .baseDefense   = 40,
        .baseSpeed     = 50,
        .baseSpAttack  = 62,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 190,
        .expYield = 61,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_INSOMNIA, ABILITY_KLUTZ },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("CAPSAKID"),
        .cryId = CRY_CAPSAKID,
        .natDexNum = NATIONAL_DEX_CAPSAKID,
        .categoryName = _("Pimiento Picante"),
        .height = 3,
        .weight = 30,
        .description = COMPOUND_STRING(
            "Cuanta más luz solar reciba este\n"
            "POKéMON, más químicos picantes\n"
            "produce su cuerpo, y por lo tanto\n"
            "spicier its moves become."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Capsakid,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Capsakid,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Capsakid,
        .shinyPalette = gMonShinyPalette_Capsakid,
        .iconSprite = gMonIcon_Capsakid,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(2, 0, SHADOW_SIZE_S)
        FOOTPRINT(Capsakid)
        OVERWORLD(
            sPicTable_Capsakid,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Capsakid,
            gShinyOverworldPalette_Capsakid
        )
        .levelUpLearnset = sCapsakidLevelUpLearnset,
        .teachableLearnset = sCapsakidTeachableLearnset,
        .eggMoveLearnset = sCapsakidEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_FIRE_STONE, SPECIES_SCOVILLAIN}),
    },

    [SPECIES_SCOVILLAIN] =
    {
        .baseHP        = 65,
        .baseAttack    = 108,
        .baseDefense   = 65,
        .baseSpeed     = 75,
        .baseSpAttack  = 108,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_GRASS, TYPE_FIRE),
        .catchRate = 75,
        .expYield = 170,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_INSOMNIA, ABILITY_MOODY },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SCOVILLAIN"),
        .cryId = CRY_SCOVILLAIN,
        .natDexNum = NATIONAL_DEX_SCOVILLAIN,
        .categoryName = _("Pimiento Picante"),
        .height = 9,
        .weight = 150,
        .description = COMPOUND_STRING(
            "Su cabeza verde se volvió viciosa\n"
            "por los químicos picantes que\n"
            "estimulan su cerebro. Al entrar en\n"
            "rampage, there is no stopping it."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Scovillain,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Scovillain,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Scovillain,
        .shinyPalette = gMonShinyPalette_Scovillain,
        .iconSprite = gMonIcon_Scovillain,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(6, 11, SHADOW_SIZE_M)
        FOOTPRINT(Scovillain)
        OVERWORLD(
            sPicTable_Scovillain,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following_Asym,
            gOverworldPalette_Scovillain,
            gShinyOverworldPalette_Scovillain
        )
        .levelUpLearnset = sScovillainLevelUpLearnset,
        .teachableLearnset = sScovillainTeachableLearnset,
        .formSpeciesIdTable = sScovillainFormSpeciesIdTable,
        .formChangeTable = sScovillainFormChangeTable,
    },

#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_SCOVILLAIN_MEGA] =
    {
        .baseHP        = 65,
        .baseAttack    = 138,
        .baseDefense   = 85,
        .baseSpeed     = 75,
        .baseSpAttack  = 138,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_GRASS, TYPE_FIRE),
        .catchRate = 75,
        .expYield = 170,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_CHLOROPHYLL, ABILITY_INSOMNIA, ABILITY_MOODY },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SCOVILLAIN"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_SCOVILLAIN_MEGA,
    #else
        .cryId = CRY_SCOVILLAIN,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_SCOVILLAIN,
        .categoryName = _("Pimiento Picante"),
        .height = 12,
        .weight = 220,
        .description = COMPOUND_STRING(
            "Megaevolución, aumentó el picante\n"
            "de este POKéMON. Balancea su\n"
            "“necktie” around to wallop its foes."),
        .frontPic = gMonFrontPic_ScovillainMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ScovillainMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 8,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ScovillainMega,
        .shinyPalette = gMonShinyPalette_ScovillainMega,
        .iconSprite = gMonIcon_ScovillainMega,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Scovillain)
        SHADOW(1, 12, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sScovillainLevelUpLearnset,
        .teachableLearnset = sScovillainTeachableLearnset,
        .formSpeciesIdTable = sScovillainFormSpeciesIdTable,
        .formChangeTable = sScovillainFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_CAPSAKID

#if P_FAMILY_RELLOR
    [SPECIES_RELLOR] =
    {
        .baseHP        = 41,
        .baseAttack    = 50,
        .baseDefense   = 60,
        .baseSpeed     = 30,
        .baseSpAttack  = 31,
        .baseSpDefense = 58,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 190,
        .expYield = 54,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_COMPOUND_EYES, ABILITY_NONE, ABILITY_SHED_SKIN },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("RELLOR"),
        .cryId = CRY_RELLOR,
        .natDexNum = NATIONAL_DEX_RELLOR,
        .categoryName = _("Rodando"),
        .height = 2,
        .weight = 10,
        .description = COMPOUND_STRING(
            "Crea una bola de lodo mezclando\n"
            "arena y tierra con energía psíquica.\n"
            "Valora su bola de lodo más que\n"
            "than its own life."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Rellor,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 17,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Rellor,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Rellor,
        .shinyPalette = gMonShinyPalette_Rellor,
        .iconSprite = gMonIcon_Rellor,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(4, -3, SHADOW_SIZE_L)
        FOOTPRINT(Rellor)
        OVERWORLD(
            sPicTable_Rellor,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_BUG,
            sAnimTable_Following,
            gOverworldPalette_Rellor,
            gShinyOverworldPalette_Rellor
        )
        .levelUpLearnset = sRellorLevelUpLearnset,
        .teachableLearnset = sRellorTeachableLearnset,
        .eggMoveLearnset = sRellorEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_RABSCA, CONDITIONS({IF_MIN_OVERWORLD_STEPS, 1000})}),
    },

    [SPECIES_RABSCA] =
    {
        .baseHP        = 75,
        .baseAttack    = 50,
        .baseDefense   = 85,
        .baseSpeed     = 45,
        .baseSpAttack  = 115,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_BUG, TYPE_PSYCHIC),
        .catchRate = 45,
        .expYield = 165,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SYNCHRONIZE, ABILITY_NONE, ABILITY_TELEPATHY },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("RABSCA"),
        .cryId = CRY_RABSCA,
        .natDexNum = NATIONAL_DEX_RABSCA,
        .categoryName = _("Rodando"),
        .height = 3,
        .weight = 35,
        .description = COMPOUND_STRING(
            "El cuerpo que sostiene la BALL\n"
            "apenas se mueve. Por eso, se cree\n"
            "que el cuerpo real de este POKéMON\n"
            "is actually inside the ball."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Rabsca,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Rabsca,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Rabsca,
        .shinyPalette = gMonShinyPalette_Rabsca,
        .iconSprite = gMonIcon_Rabsca,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 14, SHADOW_SIZE_M)
        FOOTPRINT(Rabsca)
        OVERWORLD(
            sPicTable_Rabsca,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Rabsca,
            gShinyOverworldPalette_Rabsca
        )
        .levelUpLearnset = sRabscaLevelUpLearnset,
        .teachableLearnset = sRabscaTeachableLearnset,
    },
#endif //P_FAMILY_RELLOR

#if P_FAMILY_FLITTLE
    [SPECIES_FLITTLE] =
    {
        .baseHP        = 30,
        .baseAttack    = 35,
        .baseDefense   = 30,
        .baseSpeed     = 75,
        .baseSpAttack  = 55,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 120,
        .expYield = 51,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_ANTICIPATION, ABILITY_FRISK, ABILITY_SPEED_BOOST },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("FLITTLE"),
        .cryId = CRY_FLITTLE,
        .natDexNum = NATIONAL_DEX_FLITTLE,
        .categoryName = _("Frill"),
        .height = 2,
        .weight = 15,
        .description = COMPOUND_STRING(
            "Los dedos de Flittle levitan a medio\n"
            "centímetro del suelo debido al\n"
            "poder psíquico que emite desde su\n"
            "frills on the Pokémon's belly."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Flittle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Flittle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Flittle,
        .shinyPalette = gMonShinyPalette_Flittle,
        .iconSprite = gMonIcon_Flittle,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 2, SHADOW_SIZE_S)
        FOOTPRINT(Flittle)
        OVERWORLD(
            sPicTable_Flittle,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Flittle,
            gShinyOverworldPalette_Flittle
        )
        .levelUpLearnset = sFlittleLevelUpLearnset,
        .teachableLearnset = sFlittleTeachableLearnset,
        .eggMoveLearnset = sFlittleEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_ESPATHRA}),
    },

    [SPECIES_ESPATHRA] =
    {
        .baseHP        = 95,
        .baseAttack    = 60,
        .baseDefense   = 60,
        .baseSpeed     = 105,
        .baseSpAttack  = 101,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 60,
        .expYield = 168,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_OPPORTUNIST, ABILITY_FRISK, ABILITY_SPEED_BOOST },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("ESPATHRA"),
        .cryId = CRY_ESPATHRA,
        .natDexNum = NATIONAL_DEX_ESPATHRA,
        .categoryName = _("Ostrich"),
        .height = 19,
        .weight = 900,
        .description = COMPOUND_STRING(
            "Inmoviliza a los rivales al\n"
            "bañarlos en poder psíquico desde su\n"
            "ojos grandes. Pese a su apariencia,\n"
            "has a vicious temperament."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Espathra,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Espathra,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Espathra,
        .shinyPalette = gMonShinyPalette_Espathra,
        .iconSprite = gMonIcon_Espathra,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-5, 10, SHADOW_SIZE_M)
        FOOTPRINT(Espathra)
        OVERWORLD(
            sPicTable_Espathra,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Espathra,
            gShinyOverworldPalette_Espathra
        )
        .levelUpLearnset = sEspathraLevelUpLearnset,
        .teachableLearnset = sEspathraTeachableLearnset,
    },
#endif //P_FAMILY_FLITTLE

#if P_FAMILY_TINKATINK
    [SPECIES_TINKATINK] =
    {
        .baseHP        = 50,
        .baseAttack    = 45,
        .baseDefense   = 45,
        .baseSpeed     = 58,
        .baseSpAttack  = 35,
        .baseSpDefense = 64,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_STEEL),
        .catchRate = 190,
        .expYield = 59,
        .evYield_SpDefense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_OWN_TEMPO, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("TINKATINK"),
        .cryId = CRY_TINKATINK,
        .natDexNum = NATIONAL_DEX_TINKATINK,
        .categoryName = _("Herrero"),
        .height = 4,
        .weight = 89,
        .description = COMPOUND_STRING(
            "Este POKéMON golpea restos de\n"
            "hierro para hacer un martillo. Lo\n"
            "rehace una y otra vez hasta que\n"
            "it's satisfied with the result."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tinkatink,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tinkatink,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tinkatink,
        .shinyPalette = gMonShinyPalette_Tinkatink,
        .iconSprite = gMonIcon_Tinkatink,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-3, 1, SHADOW_SIZE_S)
        FOOTPRINT(Tinkatink)
        OVERWORLD(
            sPicTable_Tinkatink,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following_Asym,
            gOverworldPalette_Tinkatink,
            gShinyOverworldPalette_Tinkatink
        )
        .levelUpLearnset = sTinkatinkLevelUpLearnset,
        .teachableLearnset = sTinkatinkTeachableLearnset,
        .eggMoveLearnset = sTinkatinkEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_TINKATUFF}),
    },

    [SPECIES_TINKATUFF] =
    {
        .baseHP        = 65,
        .baseAttack    = 55,
        .baseDefense   = 55,
        .baseSpeed     = 78,
        .baseSpAttack  = 45,
        .baseSpDefense = 82,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_STEEL),
        .catchRate = 90,
        .expYield = 133,
        .evYield_SpDefense = 2,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_OWN_TEMPO, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("TINKATUFF"),
        .cryId = CRY_TINKATUFF,
        .natDexNum = NATIONAL_DEX_TINKATUFF,
        .categoryName = _("Martillo"),
        .height = 7,
        .weight = 591,
        .description = COMPOUND_STRING(
            "Estos POKéMON viven en montones\n"
            "de chatarra. Prueban la fuerza de\n"
            "sus martillos chocándolos entre sí\n"
            "smashing them together."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tinkatuff,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tinkatuff,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tinkatuff,
        .shinyPalette = gMonShinyPalette_Tinkatuff,
        .iconSprite = gMonIcon_Tinkatuff,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-4, 5, SHADOW_SIZE_L)
        FOOTPRINT(Tinkatuff)
        OVERWORLD(
            sPicTable_Tinkatuff,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following_Asym,
            gOverworldPalette_Tinkatuff,
            gShinyOverworldPalette_Tinkatuff
        )
        .levelUpLearnset = sTinkatuffLevelUpLearnset,
        .teachableLearnset = sTinkatuffTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 38, SPECIES_TINKATON}),
    },

    [SPECIES_TINKATON] =
    {
        .baseHP        = 85,
        .baseAttack    = 75,
        .baseDefense   = 77,
        .baseSpeed     = 94,
        .baseSpAttack  = 70,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_STEEL),
        .catchRate = 45,
        .expYield = 253,
        .evYield_SpDefense = 3,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_OWN_TEMPO, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("TINKATON"),
        .cryId = CRY_TINKATON,
        .natDexNum = NATIONAL_DEX_TINKATON,
        .categoryName = _("Martillo"),
        .height = 7,
        .weight = 1128,
        .description = COMPOUND_STRING(
            "El martillo pesa 100 kilos, pero\n"
            "Tinkaton lo balancea con facilidad\n"
            "Tinkaton mientras roba lo que quiera\n"
            "and carries its plunder back home."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tinkaton,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tinkaton,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tinkaton,
        .shinyPalette = gMonShinyPalette_Tinkaton,
        .iconSprite = gMonIcon_Tinkaton,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-5, 15, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Tinkaton)
        OVERWORLD(
            sPicTable_Tinkaton,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following_Asym,
            gOverworldPalette_Tinkaton,
            gShinyOverworldPalette_Tinkaton
        )
        .levelUpLearnset = sTinkatonLevelUpLearnset,
        .teachableLearnset = sTinkatonTeachableLearnset,
    },
#endif //P_FAMILY_TINKATINK

#if P_FAMILY_WIGLETT
    [SPECIES_WIGLETT] =
    {
        .baseHP        = 10,
        .baseAttack    = 55,
        .baseDefense   = 25,
        .baseSpeed     = 95,
        .baseSpAttack  = 35,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 255,
        .expYield = 49,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_GOOEY, ABILITY_RATTLED, ABILITY_SAND_VEIL },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("WIGLETT"),
        .cryId = CRY_WIGLETT,
        .natDexNum = NATIONAL_DEX_WIGLETT,
        .categoryName = _("Anguila de Jardín"),
        .height = 12,
        .weight = 18,
        .description = COMPOUND_STRING(
            "Este POKéMON puede oler a un\n"
            "de un Veluza a más de 20 metros\n"
            "and will hide itself in the sand."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Wiglett,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Wiglett,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Wiglett,
        .shinyPalette = gMonShinyPalette_Wiglett,
        .iconSprite = gMonIcon_Wiglett,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        NO_SHADOW
        FOOTPRINT(Wiglett)
        OVERWORLD(
            sPicTable_Wiglett,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_Wiglett,
            gShinyOverworldPalette_Wiglett
        )
        .levelUpLearnset = sWiglettLevelUpLearnset,
        .teachableLearnset = sWiglettTeachableLearnset,
        .eggMoveLearnset = sWiglettEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 26, SPECIES_WUGTRIO}),
    },

    [SPECIES_WUGTRIO] =
    {
        .baseHP        = 35,
        .baseAttack    = 100,
        .baseDefense   = 50,
        .baseSpeed     = 120,
        .baseSpAttack  = 50,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 50,
        .expYield = 149,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_GOOEY, ABILITY_RATTLED, ABILITY_SAND_VEIL },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("WUGTRIO"),
        .cryId = CRY_WUGTRIO,
        .natDexNum = NATIONAL_DEX_WUGTRIO,
        .categoryName = _("Anguila de Jardín"),
        .height = 12,
        .weight = 54,
        .description = COMPOUND_STRING(
            "Wugtrio, un POKéMON pez variado,\n"
            "fue considerado alguna vez como un\n"
            "regional form of Dugtrio."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Wugtrio,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Wugtrio,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Wugtrio,
        .shinyPalette = gMonShinyPalette_Wugtrio,
        .iconSprite = gMonIcon_Wugtrio,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        NO_SHADOW
        FOOTPRINT(Wugtrio)
        OVERWORLD(
            sPicTable_Wugtrio,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_Wugtrio,
            gShinyOverworldPalette_Wugtrio
        )
        .levelUpLearnset = sWugtrioLevelUpLearnset,
        .teachableLearnset = sWugtrioTeachableLearnset,
    },
#endif //P_FAMILY_WIGLETT

#if P_FAMILY_BOMBIRDIER
    [SPECIES_BOMBIRDIER] =
    {
        .baseHP        = 70,
        .baseAttack    = 103,
        .baseDefense   = 85,
        .baseSpeed     = 82,
        .baseSpAttack  = 60,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_FLYING, TYPE_DARK),
        .catchRate = 25,
        .expYield = 243,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_BIG_PECKS, ABILITY_KEEN_EYE, ABILITY_ROCKY_PAYLOAD },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("BOMBIRDIER"),
        .cryId = CRY_BOMBIRDIER,
        .natDexNum = NATIONAL_DEX_BOMBIRDIER,
        .categoryName = _("Objeto Soltado"),
        .height = 15,
        .weight = 429,
        .description = COMPOUND_STRING(
            "Bombirdier usa el delantal de su\n"
            "pecho para envolver comida y\n"
            "lleva a su nido. Le gusta\n"
            "dropping things that make loud noises."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bombirdier,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Bombirdier,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Bombirdier,
        .shinyPalette = gMonShinyPalette_Bombirdier,
        .iconSprite = gMonIcon_Bombirdier,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(8, 12, SHADOW_SIZE_M)
        FOOTPRINT(Bombirdier)
        OVERWORLD(
            sPicTable_Bombirdier,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Bombirdier,
            gShinyOverworldPalette_Bombirdier
        )
        .levelUpLearnset = sBombirdierLevelUpLearnset,
        .teachableLearnset = sBombirdierTeachableLearnset,
        .eggMoveLearnset = sBombirdierEggMoveLearnset,
    },
#endif //P_FAMILY_BOMBIRDIER

#if P_FAMILY_FINIZEN
    [SPECIES_FINIZEN] =
    {
        .baseHP        = 70,
        .baseAttack    = 45,
        .baseDefense   = 40,
        .baseSpeed     = 75,
        .baseSpAttack  = 45,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 200,
        .expYield = 63,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_2),
        .abilities = { ABILITY_WATER_VEIL, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("FINIZEN"),
        .cryId = CRY_FINIZEN,
        .natDexNum = NATIONAL_DEX_FINIZEN,
        .categoryName = _("Delfín"),
        .height = 13,
        .weight = 602,
        .description = COMPOUND_STRING("Su anillo de agua es de agua\nmarina con un fluido pegajoso\nque Finizen segrega por su espiráculo.\n"),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Finizen,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Finizen,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Finizen,
        .shinyPalette = gMonShinyPalette_Finizen,
        .iconSprite = gMonIcon_Finizen,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 7, SHADOW_SIZE_S)
        FOOTPRINT(Finizen)
        OVERWORLD(
            sPicTable_Finizen,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Finizen,
            gShinyOverworldPalette_Finizen
        )
        .levelUpLearnset = sFinizenLevelUpLearnset,
        .teachableLearnset = sFinizenTeachableLearnset,
        .eggMoveLearnset = sFinizenEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 38, SPECIES_PALAFIN_ZERO}),
    },

    [SPECIES_PALAFIN_ZERO] =
    {
        .baseHP        = 100,
        .baseAttack    = 70,
        .baseDefense   = 72,
        .baseSpeed     = 100,
        .baseSpAttack  = 53,
        .baseSpDefense = 62,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 160,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_2),
        .abilities = { ABILITY_ZERO_TO_HERO, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("PALAFIN"),
        .cryId = CRY_FINIZEN,
        .natDexNum = NATIONAL_DEX_PALAFIN,
        .categoryName = _("Delfín"),
        .height = 13,
        .weight = 602,
        .description = COMPOUND_STRING(
            "Este POKéMON cambia su aspecto\n"
            "si oye a sus aliados pedir\n"
            "ayuda. Palafin jamás mostrará su\n"
            "anybody its moment of transformation."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PalafinZero,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_PalafinZero,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_PalafinZero,
        .shinyPalette = gMonShinyPalette_PalafinZero,
        .iconSprite = gMonIcon_PalafinZero,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 7, SHADOW_SIZE_S)
        FOOTPRINT(Palafin)
        OVERWORLD(
            sPicTable_PalafinZero,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_PalafinZero,
            gShinyOverworldPalette_PalafinZero
        )
        .levelUpLearnset = sPalafinLevelUpLearnset,
        .teachableLearnset = sPalafinTeachableLearnset,
        .formSpeciesIdTable = sPalafinFormSpeciesIdTable,
        .formChangeTable = sPalafinZeroFormChangeTable,
    },

    [SPECIES_PALAFIN_HERO] =
    {
        .baseHP        = 100,
        .baseAttack    = 160,
        .baseDefense   = 97,
        .baseSpeed     = 100,
        .baseSpAttack  = 106,
        .baseSpDefense = 87,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 45,
        .expYield = 228,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD, EGG_GROUP_WATER_2),
        .abilities = { ABILITY_ZERO_TO_HERO, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("PALAFIN"),
        .cryId = CRY_PALAFIN_HERO,
        .natDexNum = NATIONAL_DEX_PALAFIN,
        .categoryName = _("Héroe"),
        .height = 18,
        .weight = 974,
        .description = COMPOUND_STRING(
            "Los genes antiguos de este POKéMON\n"
            "despertaron. Ahora es tan fuerte\n"
            "que puede levantar fácilmente a un\n"
            "cruise ship with one fin."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PalafinHero,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_PalafinHero,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_PalafinHero,
        .shinyPalette = gMonShinyPalette_PalafinHero,
        .iconSprite = gMonIcon_PalafinHero,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 13, SHADOW_SIZE_M)
        FOOTPRINT(Palafin)
        OVERWORLD(
            sPicTable_PalafinHero,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_PalafinHero,
            gShinyOverworldPalette_PalafinHero
        )
        .levelUpLearnset = sPalafinLevelUpLearnset,
        .teachableLearnset = sPalafinTeachableLearnset,
        .formSpeciesIdTable = sPalafinFormSpeciesIdTable,
        .formChangeTable = sPalafinZeroFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_FAMILY_FINIZEN

#if P_FAMILY_VAROOM
    [SPECIES_VAROOM] =
    {
        .baseHP        = 45,
        .baseAttack    = 70,
        .baseDefense   = 63,
        .baseSpeed     = 47,
        .baseSpAttack  = 30,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_STEEL, TYPE_POISON),
        .catchRate = 190,
        .expYield = 60,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_OVERCOAT, ABILITY_NONE, ABILITY_SLOW_START },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("VAROOM"),
        .cryId = CRY_VAROOM,
        .natDexNum = NATIONAL_DEX_VAROOM,
        .categoryName = _("Monocilindro"),
        .height = 10,
        .weight = 350,
        .description = COMPOUND_STRING(
            "La parte de acero es el cuerpo\n"
            "real de Varoom. Se aferra a las\n"
            "rocas y convierte sus minerales.\n"
            "into energy to fuel its activities."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Varoom,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Varoom,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Varoom,
        .shinyPalette = gMonShinyPalette_Varoom,
        .iconSprite = gMonIcon_Varoom,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 0, SHADOW_SIZE_M)
        FOOTPRINT(Varoom)
        OVERWORLD(
            sPicTable_Varoom,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Varoom,
            gShinyOverworldPalette_Varoom
        )
        .levelUpLearnset = sVaroomLevelUpLearnset,
        .teachableLearnset = sVaroomTeachableLearnset,
        .eggMoveLearnset = sVaroomEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_REVAVROOM}),
    },

    [SPECIES_REVAVROOM] =
    {
        .baseHP        = 80,
        .baseAttack    = 119,
        .baseDefense   = 90,
        .baseSpeed     = 90,
        .baseSpAttack  = 54,
        .baseSpDefense = 67,
        .types = MON_TYPES(TYPE_STEEL, TYPE_POISON),
        .catchRate = 75,
        .expYield = 175,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_OVERCOAT, ABILITY_NONE, ABILITY_FILTER },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("REVAVROOM"),
        .cryId = CRY_REVAVROOM,
        .natDexNum = NATIONAL_DEX_REVAVROOM,
        .categoryName = _("Multicilindro"),
        .height = 18,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "Crea un gas de veneno y minerales\n"
            "de las rocas. Luego los usa.\n"
            "detona el gas de sus cilindros ahora\n"
            "numbering eight-to generate energy."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Revavroom,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Revavroom,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Revavroom,
        .shinyPalette = gMonShinyPalette_Revavroom,
        .iconSprite = gMonIcon_Revavroom,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 7, SHADOW_SIZE_L)
        FOOTPRINT(Revavroom)
        OVERWORLD(
            sPicTable_Revavroom,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Revavroom,
            gShinyOverworldPalette_Revavroom
        )
        .levelUpLearnset = sRevavroomLevelUpLearnset,
        .teachableLearnset = sRevavroomTeachableLearnset,
    },
#endif //P_FAMILY_VAROOM

#if P_FAMILY_CYCLIZAR
    [SPECIES_CYCLIZAR] =
    {
        .baseHP        = 70,
        .baseAttack    = 95,
        .baseDefense   = 65,
        .baseSpeed     = 121,
        .baseSpAttack  = 85,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_NORMAL),
        .catchRate = 190,
        .expYield = 175,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SHED_SKIN, ABILITY_NONE, ABILITY_REGENERATOR },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("CYCLIZAR"),
        .cryId = CRY_CYCLIZAR,
        .natDexNum = NATIONAL_DEX_CYCLIZAR,
        .categoryName = _("Montar"),
        .height = 16,
        .weight = 630,
        .description = COMPOUND_STRING(
            "Puede correr a más de 110 km/h\n"
            "llevando a un humano. El calor del\n"
            "jinete calienta su espalda y lo eleva\n"
            "the Pokémon's spirit."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cyclizar,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cyclizar,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cyclizar,
        .shinyPalette = gMonShinyPalette_Cyclizar,
        .iconSprite = gMonIcon_Cyclizar,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 9, SHADOW_SIZE_M)
        FOOTPRINT(Cyclizar)
        OVERWORLD(
            sPicTable_Cyclizar,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Cyclizar,
            gShinyOverworldPalette_Cyclizar
        )
        .levelUpLearnset = sCyclizarLevelUpLearnset,
        .teachableLearnset = sCyclizarTeachableLearnset,
        .eggMoveLearnset = sCyclizarEggMoveLearnset,
    },
#endif //P_FAMILY_CYCLIZAR

#if P_FAMILY_ORTHWORM
    [SPECIES_ORTHWORM] =
    {
        .baseHP        = 70,
        .baseAttack    = 85,
        .baseDefense   = 145,
        .baseSpeed     = 65,
        .baseSpAttack  = 60,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_STEEL),
        .catchRate = 25,
        .expYield = 240,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_EARTH_EATER, ABILITY_NONE, ABILITY_SAND_VEIL },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("ORTHWORM"),
        .cryId = CRY_ORTHWORM,
        .natDexNum = NATIONAL_DEX_ORTHWORM,
        .categoryName = _("Lombriz de tierra"),
        .height = 25,
        .weight = 3100,
        .description = COMPOUND_STRING(
            "Si lo atacan, este POKéMON\n"
            "usa los zarcillos de su cuerpo como\n"
            "puños y golpea fuerte al rival.\n"
            "storm of punches."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Orthworm,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Orthworm,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Orthworm,
        .shinyPalette = gMonShinyPalette_Orthworm,
        .iconSprite = gMonIcon_Orthworm,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(6, 10, SHADOW_SIZE_L)
        FOOTPRINT(Orthworm)
        OVERWORLD(
            sPicTable_Orthworm,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_Orthworm,
            gShinyOverworldPalette_Orthworm
        )
        .levelUpLearnset = sOrthwormLevelUpLearnset,
        .teachableLearnset = sOrthwormTeachableLearnset,
        .eggMoveLearnset = sOrthwormEggMoveLearnset,
    },
#endif //P_FAMILY_ORTHWORM

#if P_FAMILY_GLIMMET
    [SPECIES_GLIMMET] =
    {
        .baseHP        = 48,
        .baseAttack    = 35,
        .baseDefense   = 42,
        .baseSpeed     = 60,
        .baseSpAttack  = 105,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_ROCK, TYPE_POISON),
        .catchRate = 70,
        .expYield = 70,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_TOXIC_DEBRIS, ABILITY_NONE, ABILITY_CORROSION },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("GLIMMET"),
        .cryId = CRY_GLIMMET,
        .natDexNum = NATIONAL_DEX_GLIMMET,
        .categoryName = _("Ore"),
        .height = 7,
        .weight = 80,
        .description = COMPOUND_STRING(
            "Los cristales minerales tóxicos de\n"
            "Glimmet parecen pétalos de flores.\n"
            "Pokémon esparce polvo venenoso como\n"
            "pollen to protect itself."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Glimmet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 16,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 11,
        .backPic = gMonBackPic_Glimmet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Glimmet,
        .shinyPalette = gMonShinyPalette_Glimmet,
        .iconSprite = gMonIcon_Glimmet,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 6, SHADOW_SIZE_S)
        FOOTPRINT(Glimmet)
        OVERWORLD(
            sPicTable_Glimmet,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Glimmet,
            gShinyOverworldPalette_Glimmet
        )
        .levelUpLearnset = sGlimmetLevelUpLearnset,
        .teachableLearnset = sGlimmetTeachableLearnset,
        .eggMoveLearnset = sGlimmetEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_GLIMMORA}),
    },

    [SPECIES_GLIMMORA] =
    {
        .baseHP        = 83,
        .baseAttack    = 55,
        .baseDefense   = 90,
        .baseSpeed     = 86,
        .baseSpAttack  = 130,
        .baseSpDefense = 81,
        .types = MON_TYPES(TYPE_ROCK, TYPE_POISON),
        .catchRate = 25,
        .expYield = 184,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_TOXIC_DEBRIS, ABILITY_NONE, ABILITY_CORROSION },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("GLIMMORA"),
        .cryId = CRY_GLIMMORA,
        .natDexNum = NATIONAL_DEX_GLIMMORA,
        .categoryName = _("Ore"),
        .height = 15,
        .weight = 450,
        .description = COMPOUND_STRING(
            "Los pétalos de Glimmora están hechos\n"
            "de energía venenosa cristalizada. Se\n"
            "ha vuelto evidente que estos\n"
            "petals resemble Tera Jewels."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Glimmora,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_Glimmora,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Glimmora,
        .shinyPalette = gMonShinyPalette_Glimmora,
        .iconSprite = gMonIcon_Glimmora,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 17, SHADOW_SIZE_M)
        FOOTPRINT(Glimmora)
        OVERWORLD(
            sPicTable_Glimmora,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Glimmora,
            gShinyOverworldPalette_Glimmora
        )
        .levelUpLearnset = sGlimmoraLevelUpLearnset,
        .teachableLearnset = sGlimmoraTeachableLearnset,
        .formSpeciesIdTable = sGlimmoraFormSpeciesIdTable,
        .formChangeTable = sGlimmoraFormChangeTable,
    },

#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_GLIMMORA_MEGA] =
    {
        .baseHP        = 83,
        .baseAttack    = 90,
        .baseDefense   = 105,
        .baseSpeed     = 101,
        .baseSpAttack  = 150,
        .baseSpDefense = 96,
        .types = MON_TYPES(TYPE_ROCK, TYPE_POISON),
        .catchRate = 25,
        .expYield = 184,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 30,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_TOXIC_DEBRIS, ABILITY_NONE, ABILITY_CORROSION },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("GLIMMORA"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_GLIMMORA_MEGA,
    #else
        .cryId = CRY_GLIMMORA,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_GLIMMORA,
        .categoryName = _("Ore"),
        .height = 15,
        .weight = 450,
        .description = COMPOUND_STRING(
            "pétalos de Glimmora, ahora más grandes\n"
            "y separados de su cuerpo, rotan a su\n"
            "alrededor para darle defensa mientras\n"
            "cattering poisonous fragments."),
        .frontPic = gMonFrontPic_GlimmoraMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 7,
        .backPic = gMonBackPic_GlimmoraMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GlimmoraMega,
        .shinyPalette = gMonShinyPalette_GlimmoraMega,
        .iconSprite = gMonIcon_GlimmoraMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Glimmora)
        SHADOW(1, 18, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sGlimmoraLevelUpLearnset,
        .teachableLearnset = sGlimmoraTeachableLearnset,
        .formSpeciesIdTable = sGlimmoraFormSpeciesIdTable,
        .formChangeTable = sGlimmoraFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_GLIMMET

#if P_FAMILY_GREAVARD
    [SPECIES_GREAVARD] =
    {
        .baseHP        = 50,
        .baseAttack    = 61,
        .baseDefense   = 60,
        .baseSpeed     = 34,
        .baseSpAttack  = 30,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 120,
        .expYield = 58,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_PICKUP, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("GREAVARD"),
        .cryId = CRY_GREAVARD,
        .natDexNum = NATIONAL_DEX_GREAVARD,
        .categoryName = _("Perro Fantasma"),
        .height = 6,
        .weight = 350,
        .description = COMPOUND_STRING(
            "A este Pokémon amigable no le gusta\n"
            "estar solo. Dale aunque sea un\n"
            "mínima atención y entonces\n"
            "follow you forever."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Greavard,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Greavard,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Greavard,
        .shinyPalette = gMonShinyPalette_Greavard,
        .iconSprite = gMonIcon_Greavard,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(3, 2, SHADOW_SIZE_M)
        FOOTPRINT(Greavard)
        OVERWORLD(
            sPicTable_Greavard,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Greavard,
            gShinyOverworldPalette_Greavard
        )
        .levelUpLearnset = sGreavardLevelUpLearnset,
        .teachableLearnset = sGreavardTeachableLearnset,
        .eggMoveLearnset = sGreavardEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_HOUNDSTONE, CONDITIONS({IF_TIME, TIME_NIGHT})}),
    },

    [SPECIES_HOUNDSTONE] =
    {
        .baseHP        = 72,
        .baseAttack    = 101,
        .baseDefense   = 100,
        .baseSpeed     = 68,
        .baseSpAttack  = 50,
        .baseSpDefense = 97,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 60,
        .expYield = 171,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_SAND_RUSH, ABILITY_NONE, ABILITY_FLUFFY },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("HOUNDSTONE"),
        .cryId = CRY_HOUNDSTONE,
        .natDexNum = NATIONAL_DEX_HOUNDSTONE,
        .categoryName = _("Perro Fantasma"),
        .height = 20,
        .weight = 150,
        .description = COMPOUND_STRING(
            "Houndstone pasa la mayor parte de su\n"
            "tiempo durmiendo en cementerios. De\n"
            "los POKéMON perro, este es el más\n"
            "loyal to its master."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Houndstone,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Houndstone,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Houndstone,
        .shinyPalette = gMonShinyPalette_Houndstone,
        .iconSprite = gMonIcon_Houndstone,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 6, SHADOW_SIZE_L)
        FOOTPRINT(Houndstone)
        OVERWORLD(
            sPicTable_Houndstone,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Houndstone,
            gShinyOverworldPalette_Houndstone
        )
        .levelUpLearnset = sHoundstoneLevelUpLearnset,
        .teachableLearnset = sHoundstoneTeachableLearnset,
    },
#endif //P_FAMILY_GREAVARD

#if P_FAMILY_FLAMIGO
    [SPECIES_FLAMIGO] =
    {
        .baseHP        = 82,
        .baseAttack    = 115,
        .baseDefense   = 74,
        .baseSpeed     = 90,
        .baseSpAttack  = 75,
        .baseSpDefense = 64,
        .types = MON_TYPES(TYPE_FLYING, TYPE_FIGHTING),
        .catchRate = 100,
        .expYield = 175,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_SCRAPPY, ABILITY_TANGLED_FEET, ABILITY_COSTAR },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("FLAMIGO"),
        .cryId = CRY_FLAMIGO,
        .natDexNum = NATIONAL_DEX_FLAMIGO,
        .categoryName = _("Sincronía"),
        .height = 16,
        .weight = 370,
        .description = COMPOUND_STRING(
            "Gracias a un comportamiento suyo\n"
            "conocido como “sincronización”, un\n"
            "bandada de estos POKéMON puede atacar\n"
            "simultaneously in perfect harmony."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Flamigo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Flamigo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Flamigo,
        .shinyPalette = gMonShinyPalette_Flamigo,
        .iconSprite = gMonIcon_Flamigo,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 12, SHADOW_SIZE_S)
        FOOTPRINT(Flamigo)
        OVERWORLD(
            sPicTable_Flamigo,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Flamigo,
            gShinyOverworldPalette_Flamigo
        )
        .levelUpLearnset = sFlamigoLevelUpLearnset,
        .teachableLearnset = sFlamigoTeachableLearnset,
        .eggMoveLearnset = sFlamigoEggMoveLearnset,
    },
#endif //P_FAMILY_FLAMIGO

#if P_FAMILY_CETODDLE
    [SPECIES_CETODDLE] =
    {
        .baseHP        = 108,
        .baseAttack    = 68,
        .baseDefense   = 45,
        .baseSpeed     = 43,
        .baseSpAttack  = 30,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_ICE),
        .catchRate = 150,
        .expYield = 67,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SNOW_CLOAK, ABILITY_SHEER_FORCE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("CETODDLE"),
        .cryId = CRY_CETODDLE,
        .natDexNum = NATIONAL_DEX_CETODDLE,
        .categoryName = _("Ballena Tierra"),
        .height = 12,
        .weight = 450,
        .description = COMPOUND_STRING(
            "Esta especie dejó el océano y\n"
            "empezó a vivir en tierra hace mucho\n"
            "tiempo. Parece estar muy emparentada\n"
            "to Wailmer."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cetoddle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cetoddle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 16,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cetoddle,
        .shinyPalette = gMonShinyPalette_Cetoddle,
        .iconSprite = gMonIcon_Cetoddle,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 0, SHADOW_SIZE_M)
        FOOTPRINT(Cetoddle)
        OVERWORLD(
            sPicTable_Cetoddle,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Cetoddle,
            gShinyOverworldPalette_Cetoddle
        )
        .levelUpLearnset = sCetoddleLevelUpLearnset,
        .teachableLearnset = sCetoddleTeachableLearnset,
        .eggMoveLearnset = sCetoddleEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_ICE_STONE, SPECIES_CETITAN}),
    },

    [SPECIES_CETITAN] =
    {
        .baseHP        = 170,
        .baseAttack    = 113,
        .baseDefense   = 65,
        .baseSpeed     = 73,
        .baseSpAttack  = 45,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_ICE),
        .catchRate = 50,
        .expYield = 182,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SLUSH_RUSH, ABILITY_SHEER_FORCE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("CETITAN"),
        .cryId = CRY_CETITAN,
        .natDexNum = NATIONAL_DEX_CETITAN,
        .categoryName = _("Ballena Tierra"),
        .height = 45,
        .weight = 7000,
        .description = COMPOUND_STRING(
            "La energía hielo se acumula en el\n"
            "cuerno de su mandíbula superior,\n"
            "alcanzando temperaturas criogénicas\n"
            "freeze its surroundings."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Cetitan,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Cetitan,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Cetitan,
        .shinyPalette = gMonShinyPalette_Cetitan,
        .iconSprite = gMonIcon_Cetitan,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 10, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Cetitan)
        OVERWORLD(
            sPicTable_Cetitan,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Cetitan,
            gShinyOverworldPalette_Cetitan
        )
        .levelUpLearnset = sCetitanLevelUpLearnset,
        .teachableLearnset = sCetitanTeachableLearnset,
    },
#endif //P_FAMILY_CETODDLE

#if P_FAMILY_VELUZA
    [SPECIES_VELUZA] =
    {
        .baseHP        = 90,
        .baseAttack    = 102,
        .baseDefense   = 73,
        .baseSpeed     = 70,
        .baseSpAttack  = 78,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER, TYPE_PSYCHIC),
        .catchRate = 100,
        .expYield = 167,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_MOLD_BREAKER, ABILITY_NONE, ABILITY_SHARPNESS },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("VELUZA"),
        .cryId = CRY_VELUZA,
        .natDexNum = NATIONAL_DEX_VELUZA,
        .categoryName = _("Expulsión"),
        .height = 25,
        .weight = 900,
        .description = COMPOUND_STRING(
            "Veluza tiene una regeneración\n"
            "excelente. Desprende carne de su\n"
            "cuerpo para aumentar su agilidad,\n"
            "then charges at its prey."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Veluza,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 5,
        .backPic = gMonBackPic_Veluza,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Veluza,
        .shinyPalette = gMonShinyPalette_Veluza,
        .iconSprite = gMonIcon_Veluza,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 5, SHADOW_SIZE_M)
        FOOTPRINT(Veluza)
        OVERWORLD(
            sPicTable_Veluza,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Veluza,
            gShinyOverworldPalette_Veluza
        )
        .levelUpLearnset = sVeluzaLevelUpLearnset,
        .teachableLearnset = sVeluzaTeachableLearnset,
        .eggMoveLearnset = sVeluzaEggMoveLearnset,
    },
#endif //P_FAMILY_VELUZA

#if P_FAMILY_DONDOZO
    [SPECIES_DONDOZO] =
    {
        .baseHP        = 150,
        .baseAttack    = 100,
        .baseDefense   = 115,
        .baseSpeed     = 35,
        .baseSpAttack  = 65,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 25,
        .expYield = 265,
        .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_UNAWARE, ABILITY_OBLIVIOUS, ABILITY_WATER_VEIL },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("DONDOZO"),
        .cryId = CRY_DONDOZO,
        .natDexNum = NATIONAL_DEX_DONDOZO,
        .categoryName = _("Bagre Gigante"),
        .height = 120,
        .weight = 2200,
        .description = COMPOUND_STRING(
            "Trata a Tatsugiri como a su jefe\n"
            "y lo sigue con lealtad. Aunque\n"
            "poderoso, Dondozo no parece ser muy\n"
            "smart."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Dondozo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 1,
        .backPic = gMonBackPic_Dondozo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Dondozo,
        .shinyPalette = gMonShinyPalette_Dondozo,
        .iconSprite = gMonIcon_Dondozo,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 8, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Dondozo)
        OVERWORLD(
            sPicTable_Dondozo,
            SIZE_64x64,
            SHADOW_SIZE_L,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Dondozo,
            gShinyOverworldPalette_Dondozo
        )
        .levelUpLearnset = sDondozoLevelUpLearnset,
        .teachableLearnset = sDondozoTeachableLearnset,
        .eggMoveLearnset = sDondozoEggMoveLearnset,
    },
#endif //P_FAMILY_DONDOZO

#if P_FAMILY_TATSUGIRI
    [SPECIES_TATSUGIRI_CURLY] =
    {
        .baseHP        = 68,
        .baseAttack    = 50,
        .baseDefense   = 60,
        .baseSpeed     = 82,
        .baseSpAttack  = 120,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_COMMANDER, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("TATSUGIRI"),
        .cryId = CRY_TATSUGIRI_CURLY,
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimetismo"),
        .height = 3,
        .weight = 80,
        .description = COMPOUND_STRING(
            "Es un pequeño POKéMON dragón. It\n"
            "vive en la boca de Dondozo para\n"
            "protegerse de enemigos en la\n"
            "outside."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TatsugiriCurly,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_TatsugiriCurly,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_TatsugiriCurly,
        .shinyPalette = gMonShinyPalette_TatsugiriCurly,
        .iconSprite = gMonIcon_TatsugiriCurly,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, -1, SHADOW_SIZE_S)
        FOOTPRINT(Tatsugiri)
        OVERWORLD(
            sPicTable_TatsugiriCurly,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_TatsugiriCurly,
            gShinyOverworldPalette_TatsugiriCurly
        )
        .levelUpLearnset = sTatsugiriLevelUpLearnset,
        .teachableLearnset = sTatsugiriTeachableLearnset,
        .eggMoveLearnset = sTatsugiriEggMoveLearnset,
        .formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
        .formChangeTable = sTatsugiriCurlyFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_RANDOM_FORM,
    },

    [SPECIES_TATSUGIRI_DROOPY] =
    {
        .baseHP        = 68,
        .baseAttack    = 50,
        .baseDefense   = 60,
        .baseSpeed     = 82,
        .baseSpAttack  = 120,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_COMMANDER, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("TATSUGIRI"),
        .cryId = CRY_TATSUGIRI_DROOPY,
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimetismo"),
        .height = 3,
        .weight = 80,
        .description = COMPOUND_STRING(
            "Este POKéMON engaña a sus rivales\n"
            "fingiendo estar muerto. Es pequeño y\n"
            "weak, but it uses its smarts to survive."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TatsugiriDroopy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_TatsugiriDroopy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_TatsugiriDroopy,
        .shinyPalette = gMonShinyPalette_TatsugiriDroopy,
        .iconSprite = gMonIcon_TatsugiriDroopy,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, -1, SHADOW_SIZE_S)
        FOOTPRINT(Tatsugiri)
        OVERWORLD(
            sPicTable_TatsugiriDroopy,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_TatsugiriDroopy,
            gShinyOverworldPalette_TatsugiriDroopy
        )
        .levelUpLearnset = sTatsugiriLevelUpLearnset,
        .teachableLearnset = sTatsugiriTeachableLearnset,
        .eggMoveLearnset = sTatsugiriEggMoveLearnset,
        .formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
        .formChangeTable = sTatsugiriDroopyFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },

    [SPECIES_TATSUGIRI_STRETCHY] =
    {
        .baseHP        = 68,
        .baseAttack    = 50,
        .baseDefense   = 60,
        .baseSpeed     = 82,
        .baseSpAttack  = 120,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_COMMANDER, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("TATSUGIRI"),
        .cryId = CRY_TATSUGIRI_STRETCHY,
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimetismo"),
        .height = 3,
        .weight = 80,
        .description = COMPOUND_STRING(
            "Es uno de los POKéMON dragón más\n"
            "inteligentes. Se camufla muy bien.\n"
            "by inflating its throat sac."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TatsugiriStretchy,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 14,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/
        .backPic = gMonBackPic_TatsugiriStretchy,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        /*.backAnimId = BACK_ANIM_NONE,*/
        .palette = gMonPalette_TatsugiriStretchy,
        .shinyPalette = gMonShinyPalette_TatsugiriStretchy,
        .iconSprite = gMonIcon_TatsugiriStretchy,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, -1, SHADOW_SIZE_S)
        FOOTPRINT(Tatsugiri)
        OVERWORLD(
            sPicTable_TatsugiriStretchy,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_TatsugiriStretchy,
            gShinyOverworldPalette_TatsugiriStretchy
        )
        .levelUpLearnset = sTatsugiriLevelUpLearnset,
        .teachableLearnset = sTatsugiriTeachableLearnset,
        .eggMoveLearnset = sTatsugiriEggMoveLearnset,
        .formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
        .formChangeTable = sTatsugiriStretchyFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },

#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_TATSUGIRI_CURLY_MEGA] =
    {
        .baseHP        = 68,
        .baseAttack    = 65,
        .baseDefense   = 90,
        .baseSpeed     = 92,
        .baseSpAttack  = 135,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_STORM_DRAIN, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("TATSUGIRI"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_TATSUGIRI_MEGA,
    #else
        .cryId = CRY_TATSUGIRI_CURLY,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimetismo"),
        .height = 6,
        .weight = 240,
        .description = COMPOUND_STRING(
            "El cerebro de Tatsugiri se ha\n"
            "potenciado con la Megaevolución,\n"
            "siendo ahora más astuto. Crea y\n"
            "copies of itself."),
        .frontPic = gMonFrontPic_TatsugiriCurlyMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TatsugiriCurlyMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TatsugiriMega,
        .shinyPalette = gMonShinyPalette_TatsugiriMega,
        .iconSprite = gMonIcon_TatsugiriCurlyMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Tatsugiri)
        SHADOW(0, 2, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sTatsugiriLevelUpLearnset,
        .teachableLearnset = sTatsugiriTeachableLearnset,
        .eggMoveLearnset = sTatsugiriEggMoveLearnset,
        .formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
        .formChangeTable = sTatsugiriCurlyFormChangeTable,
    },

    [SPECIES_TATSUGIRI_DROOPY_MEGA] =
    {
        .baseHP        = 68,
        .baseAttack    = 65,
        .baseDefense   = 90,
        .baseSpeed     = 92,
        .baseSpAttack  = 135,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_STORM_DRAIN, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("TATSUGIRI"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_TATSUGIRI_MEGA,
    #else
        .cryId = CRY_TATSUGIRI_DROOPY,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimetismo"),
        .height = 6,
        .weight = 240,
        .description = COMPOUND_STRING(
            "Solidifica la energía de la Mega-\n"
            "evolución, acumulándola para\n"
            "lanzarla. Estos proyectiles explotan.\n"
            "on contact."),
        .frontPic = gMonFrontPic_TatsugiriDroopyMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TatsugiriDroopyMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TatsugiriMega,
        .shinyPalette = gMonShinyPalette_TatsugiriMega,
        .iconSprite = gMonIcon_TatsugiriDroopyMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Tatsugiri)
        SHADOW(0, 2, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sTatsugiriLevelUpLearnset,
        .teachableLearnset = sTatsugiriTeachableLearnset,
        .eggMoveLearnset = sTatsugiriEggMoveLearnset,
        .formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
        .formChangeTable = sTatsugiriDroopyFormChangeTable,
    },

    [SPECIES_TATSUGIRI_STRETCHY_MEGA] =
    {
        .baseHP        = 68,
        .baseAttack    = 65,
        .baseDefense   = 90,
        .baseSpeed     = 92,
        .baseSpAttack  = 135,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_WATER),
        .catchRate = 100,
        .expYield = 166,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2),
        .abilities = { ABILITY_STORM_DRAIN, ABILITY_NONE, ABILITY_STORM_DRAIN },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("TATSUGIRI"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_TATSUGIRI_MEGA,
    #else
        .cryId = CRY_TATSUGIRI_STRETCHY,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_TATSUGIRI,
        .categoryName = _("Mimetismo"),
        .height = 6,
        .weight = 240,
        .description = COMPOUND_STRING(
            "Con la energía de la Megaevolución,\n"
            "crea un plato para montar, lo que le\n"
            "permite moverse con total libertad.\n"
            "the air."),
        .frontPic = gMonFrontPic_TatsugiriStretchyMega,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TatsugiriStretchyMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 17,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TatsugiriMega,
        .shinyPalette = gMonShinyPalette_TatsugiriMega,
        .iconSprite = gMonIcon_TatsugiriStretchyMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Tatsugiri)
        SHADOW(0, 2, SHADOW_SIZE_M)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sTatsugiriLevelUpLearnset,
        .teachableLearnset = sTatsugiriTeachableLearnset,
        .eggMoveLearnset = sTatsugiriEggMoveLearnset,
        .formSpeciesIdTable = sTatsugiriFormSpeciesIdTable,
        .formChangeTable = sTatsugiriStretchyFormChangeTable,
    },
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_TATSUGIRI

#if P_FAMILY_GREAT_TUSK
    [SPECIES_GREAT_TUSK] =
    {
        .baseHP        = 115,
        .baseAttack    = 131,
        .baseDefense   = 131,
        .baseSpeed     = 87,
        .baseSpAttack  = 53,
        .baseSpDefense = 53,
        .types = MON_TYPES(TYPE_GROUND, TYPE_FIGHTING),
        .catchRate = 30,
        .expYield = 285,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("GREAT TUSK"),
        .cryId = CRY_GREAT_TUSK,
        .natDexNum = NATIONAL_DEX_GREAT_TUSK,
        .categoryName = _("Paradoja"),
        .height = 22,
        .weight = 3200,
        .description = COMPOUND_STRING(
            "Se han reportado avistamientos de\n"
            "este POKéMON en años recientes. El\n"
            "Great Tusk fue tomado de una criatura\n"
            "listed in a certain book."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GreatTusk,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GreatTusk,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GreatTusk,
        .shinyPalette = gMonShinyPalette_GreatTusk,
        .iconSprite = gMonIcon_GreatTusk,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 13, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(GreatTusk)
        OVERWORLD(
            sPicTable_GreatTusk,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_GreatTusk,
            gShinyOverworldPalette_GreatTusk
        )
        .isParadox = TRUE,
        .levelUpLearnset = sGreatTuskLevelUpLearnset,
        .teachableLearnset = sGreatTuskTeachableLearnset,
    },
#endif //P_FAMILY_GREAT_TUSK

#if P_FAMILY_SCREAM_TAIL
    [SPECIES_SCREAM_TAIL] =
    {
        .baseHP        = 115,
        .baseAttack    = 65,
        .baseDefense   = 99,
        .baseSpeed     = 111,
        .baseSpAttack  = 65,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_PSYCHIC),
        .catchRate = 50,
        .expYield = 285,
        .evYield_HP = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("SCREAM TAIL"),
        .cryId = CRY_SCREAM_TAIL,
        .natDexNum = NATIONAL_DEX_SCREAM_TAIL,
        .categoryName = _("Paradoja"),
        .height = 12,
        .weight = 80,
        .description = COMPOUND_STRING(
            "Solo ha habido un reporte de\n"
            "avistamiento de este POKéMON. Se\n"
            "parece a una criatura misteriosa\n"
            "in an old expedition journal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ScreamTail,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ScreamTail,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ScreamTail,
        .shinyPalette = gMonShinyPalette_ScreamTail,
        .iconSprite = gMonIcon_ScreamTail,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 3, SHADOW_SIZE_L)
        FOOTPRINT(ScreamTail)
        OVERWORLD(
            sPicTable_ScreamTail,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_ScreamTail,
            gShinyOverworldPalette_ScreamTail
        )
        .isParadox = TRUE,
        .levelUpLearnset = sScreamTailLevelUpLearnset,
        .teachableLearnset = sScreamTailTeachableLearnset,
    },
#endif //P_FAMILY_SCREAM_TAIL

#if P_FAMILY_BRUTE_BONNET
    [SPECIES_BRUTE_BONNET] =
    {
        .baseHP        = 111,
        .baseAttack    = 127,
        .baseDefense   = 99,
        .baseSpeed     = 55,
        .baseSpAttack  = 79,
        .baseSpDefense = 99,
        .types = MON_TYPES(TYPE_GRASS, TYPE_DARK),
        .catchRate = 50,
        .expYield = 285,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("BRUTE BONNET"),
        .cryId = CRY_BRUTE_BONNET,
        .natDexNum = NATIONAL_DEX_BRUTE_BONNET,
        .categoryName = _("Paradoja"),
        .height = 12,
        .weight = 210,
        .description = COMPOUND_STRING(
            "Se parece ligeramente a un\n"
            "POKéMON descrito en una revista\n"
            "dudosa como un cruce de dinosaurio\n"
            "and a mushroom."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_BruteBonnet,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_BruteBonnet,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_BruteBonnet,
        .shinyPalette = gMonShinyPalette_BruteBonnet,
        .iconSprite = gMonIcon_BruteBonnet,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 7, SHADOW_SIZE_L)
        FOOTPRINT(BruteBonnet)
        OVERWORLD(
            sPicTable_BruteBonnet,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_BruteBonnet,
            gShinyOverworldPalette_BruteBonnet
        )
        .isParadox = TRUE,
        .levelUpLearnset = sBruteBonnetLevelUpLearnset,
        .teachableLearnset = sBruteBonnetTeachableLearnset,
    },
#endif //P_FAMILY_BRUTE_BONNET

#if P_FAMILY_FLUTTER_MANE
    [SPECIES_FLUTTER_MANE] =
    {
        .baseHP        = 55,
        .baseAttack    = 55,
        .baseDefense   = 55,
        .baseSpeed     = 135,
        .baseSpAttack  = 135,
        .baseSpDefense = 135,
        .types = MON_TYPES(TYPE_GHOST, TYPE_FAIRY),
        .catchRate = 30,
        .expYield = 285,
        .evYield_Speed = 1,
        .evYield_SpAttack = 1,
        .evYield_SpDefense = 1,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("FLUTTER MANE"),
        .cryId = CRY_FLUTTER_MANE,
        .natDexNum = NATIONAL_DEX_FLUTTER_MANE,
        .categoryName = _("Paradoja"),
        .height = 14,
        .weight = 40,
        .description = COMPOUND_STRING(
            "Tiene rasgos similares a un\n"
            "pterosaurio fantasmal que salió en\n"
            "una revista paranormal, pero...\n"
            "have little else in common."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_FlutterMane,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 18,
        .backPic = gMonBackPic_FlutterMane,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_FlutterMane,
        .shinyPalette = gMonShinyPalette_FlutterMane,
        .iconSprite = gMonIcon_FlutterMane,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 20, SHADOW_SIZE_S)
        FOOTPRINT(FlutterMane)
        OVERWORLD(
            sPicTable_FlutterMane,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_FlutterMane,
            gShinyOverworldPalette_FlutterMane
        )
        .isParadox = TRUE,
        .levelUpLearnset = sFlutterManeLevelUpLearnset,
        .teachableLearnset = sFlutterManeTeachableLearnset,
    },
#endif //P_FAMILY_FLUTTER_MANE

#if P_FAMILY_SLITHER_WING
    [SPECIES_SLITHER_WING] =
    {
        .baseHP        = 85,
        .baseAttack    = 135,
        .baseDefense   = 79,
        .baseSpeed     = 81,
        .baseSpAttack  = 85,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_BUG, TYPE_FIGHTING),
        .catchRate = 30,
        .expYield = 285,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("SLITHER WING"),
        .cryId = CRY_SLITHER_WING,
        .natDexNum = NATIONAL_DEX_SLITHER_WING,
        .categoryName = _("Paradoja"),
        .height = 32,
        .weight = 920,
        .description = COMPOUND_STRING(
            "Este misterioso POKéMON tiene\n"
            "similitudes con una criatura de...\n"
            "old book introduced as Slither Wing."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SlitherWing,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_SlitherWing,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_SlitherWing,
        .shinyPalette = gMonShinyPalette_SlitherWing,
        .iconSprite = gMonIcon_SlitherWing,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-5, 13, SHADOW_SIZE_M)
        FOOTPRINT(SlitherWing)
        OVERWORLD(
            sPicTable_SlitherWing,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_SlitherWing,
            gShinyOverworldPalette_SlitherWing
        )
        .isParadox = TRUE,
        .levelUpLearnset = sSlitherWingLevelUpLearnset,
        .teachableLearnset = sSlitherWingTeachableLearnset,
    },
#endif //P_FAMILY_SLITHER_WING

#if P_FAMILY_SANDY_SHOCKS
    [SPECIES_SANDY_SHOCKS] =
    {
        .baseHP        = 85,
        .baseAttack    = 81,
        .baseDefense   = 97,
        .baseSpeed     = 101,
        .baseSpAttack  = 121,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_GROUND),
        .catchRate = 30,
        .expYield = 285,
        .evYield_SpAttack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("SANDY SHOCKS"),
        .cryId = CRY_SANDY_SHOCKS,
        .natDexNum = NATIONAL_DEX_SANDY_SHOCKS,
        .categoryName = _("Paradoja"),
        .height = 23,
        .weight = 600,
        .description = COMPOUND_STRING(
            "Se parece un poco a un Magneton\n"
            "que vivió hace 10,000 años y que\n"
            "apareció en un artículo de una\n"
            "paranormal magazine."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SandyShocks,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_SandyShocks,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_SandyShocks,
        .shinyPalette = gMonShinyPalette_SandyShocks,
        .iconSprite = gMonIcon_SandyShocks,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 13, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(SandyShocks)
        OVERWORLD(
            sPicTable_SandyShocks,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_SandyShocks,
            gShinyOverworldPalette_SandyShocks
        )
        .isParadox = TRUE,
        .levelUpLearnset = sSandyShocksLevelUpLearnset,
        .teachableLearnset = sSandyShocksTeachableLearnset,
    },
#endif //P_FAMILY_SANDY_SHOCKS

#if P_FAMILY_IRON_TREADS
    [SPECIES_IRON_TREADS] =
    {
        .baseHP        = 90,
        .baseAttack    = 112,
        .baseDefense   = 120,
        .baseSpeed     = 106,
        .baseSpAttack  = 72,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GROUND, TYPE_STEEL),
        .catchRate = 30,
        .expYield = 285,
        .evYield_Defense = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("IRON TREADS"),
        .cryId = CRY_IRON_TREADS,
        .natDexNum = NATIONAL_DEX_IRON_TREADS,
        .categoryName = _("Paradoja"),
        .height = 9,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "Se han reportado avistamientos de\n"
            "ocurrió hace poco. Se parece a\n"
            "un objeto misterioso descrito en un\n"
            "old expedition journal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronTreads,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronTreads,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronTreads,
        .shinyPalette = gMonShinyPalette_IronTreads,
        .iconSprite = gMonIcon_IronTreads,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 3, SHADOW_SIZE_L)
        FOOTPRINT(IronTreads)
        OVERWORLD(
            sPicTable_IronTreads,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronTreads,
            gShinyOverworldPalette_IronTreads
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronTreadsLevelUpLearnset,
        .teachableLearnset = sIronTreadsTeachableLearnset,
    },
#endif //P_FAMILY_IRON_TREADS

#if P_FAMILY_IRON_BUNDLE
    [SPECIES_IRON_BUNDLE] =
    {
        .baseHP        = 56,
        .baseAttack    = 80,
        .baseDefense   = 114,
        .baseSpeed     = 136,
        .baseSpAttack  = 124,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_ICE, TYPE_WATER),
        .catchRate = 50,
        .expYield = 285,
        .evYield_Speed = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("IRON BUNDLE"),
        .cryId = CRY_IRON_BUNDLE,
        .natDexNum = NATIONAL_DEX_IRON_BUNDLE,
        .categoryName = _("Paradoja"),
        .height = 6,
        .weight = 110,
        .description = COMPOUND_STRING(
            "Su forma es similar a la de un robot\n"
            "de un artículo de una revista\n"
            "paranormal. Decían que el robot era\n"
            "created by an ancient civilization."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronBundle,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronBundle,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronBundle,
        .shinyPalette = gMonShinyPalette_IronBundle,
        .iconSprite = gMonIcon_IronBundle,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-1, 6, SHADOW_SIZE_M)
        FOOTPRINT(IronBundle)
        OVERWORLD(
            sPicTable_IronBundle,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronBundle,
            gShinyOverworldPalette_IronBundle
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronBundleLevelUpLearnset,
        .teachableLearnset = sIronBundleTeachableLearnset,
    },
#endif //P_FAMILY_IRON_BUNDLE

#if P_FAMILY_IRON_HANDS
    [SPECIES_IRON_HANDS] =
    {
        .baseHP        = 154,
        .baseAttack    = 140,
        .baseDefense   = 108,
        .baseSpeed     = 50,
        .baseSpAttack  = 50,
        .baseSpDefense = 68,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_ELECTRIC),
        .catchRate = 50,
        .expYield = 285,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("IRON HANDS"),
        .cryId = CRY_IRON_HANDS,
        .natDexNum = NATIONAL_DEX_IRON_HANDS,
        .categoryName = _("Paradoja"),
        .height = 18,
        .weight = 3807,
        .description = COMPOUND_STRING(
            "Es muy similar a un cyborg\n"
            "descrito solo en una revista\n"
            "paranormal. Decían que el cyborg era\n"
            "modified form of a certain athlete."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronHands,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronHands,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronHands,
        .shinyPalette = gMonShinyPalette_IronHands,
        .iconSprite = gMonIcon_IronHands,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 8, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(IronHands)
        OVERWORLD(
            sPicTable_IronHands,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronHands,
            gShinyOverworldPalette_IronHands
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronHandsLevelUpLearnset,
        .teachableLearnset = sIronHandsTeachableLearnset,
    },
#endif //P_FAMILY_IRON_HANDS

#if P_FAMILY_IRON_JUGULIS
    [SPECIES_IRON_JUGULIS] =
    {
        .baseHP        = 94,
        .baseAttack    = 80,
        .baseDefense   = 86,
        .baseSpeed     = 108,
        .baseSpAttack  = 122,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_DARK, TYPE_FLYING),
        .catchRate = 30,
        .expYield = 285,
        .evYield_SpAttack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("IRON JUGULIS"),
        .cryId = CRY_IRON_JUGULIS,
        .natDexNum = NATIONAL_DEX_IRON_JUGULIS,
        .categoryName = _("Paradoja"),
        .height = 13,
        .weight = 1110,
        .description = COMPOUND_STRING(
            "Se parece a cierto POKéMON\n"
            "presentado en una revista paranormal,\n"
            "descrito como la cría de un\n"
            "Hydreigon that fell in love with a robot."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronJugulis,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 7,
        .backPic = gMonBackPic_IronJugulis,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronJugulis,
        .shinyPalette = gMonShinyPalette_IronJugulis,
        .iconSprite = gMonIcon_IronJugulis,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 15, SHADOW_SIZE_M)
        FOOTPRINT(IronJugulis)
        OVERWORLD(
            sPicTable_IronJugulis,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_IronJugulis,
            gShinyOverworldPalette_IronJugulis
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronJugulisLevelUpLearnset,
        .teachableLearnset = sIronJugulisTeachableLearnset,
    },
#endif //P_FAMILY_IRON_JUGULIS

#if P_FAMILY_IRON_MOTH
    [SPECIES_IRON_MOTH] =
    {
        .baseHP        = 80,
        .baseAttack    = 70,
        .baseDefense   = 60,
        .baseSpeed     = 110,
        .baseSpAttack  = 140,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_FIRE, TYPE_POISON),
        .catchRate = 30,
        .expYield = 285,
        .evYield_SpAttack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("IRON MOTH"),
        .cryId = CRY_IRON_MOTH,
        .natDexNum = NATIONAL_DEX_IRON_MOTH,
        .categoryName = _("Paradoja"),
        .height = 12,
        .weight = 360,
        .description = COMPOUND_STRING(
            "No hay registros de que esta especie\n"
            "haya sido capturada. Faltan datos,\n"
            "pero sus rasgos coinciden con un\n"
            "object described in an old book."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronMoth,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_IronMoth,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronMoth,
        .shinyPalette = gMonShinyPalette_IronMoth,
        .iconSprite = gMonIcon_IronMoth,
        .iconPalIndex = 3,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-4, 14, SHADOW_SIZE_M)
        FOOTPRINT(IronMoth)
        OVERWORLD(
            sPicTable_IronMoth,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronMoth,
            gShinyOverworldPalette_IronMoth
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronMothLevelUpLearnset,
        .teachableLearnset = sIronMothTeachableLearnset,
    },
#endif //P_FAMILY_IRON_MOTH

#if P_FAMILY_IRON_THORNS
    [SPECIES_IRON_THORNS] =
    {
        .baseHP        = 100,
        .baseAttack    = 134,
        .baseDefense   = 110,
        .baseSpeed     = 72,
        .baseSpAttack  = 70,
        .baseSpDefense = 84,
        .types = MON_TYPES(TYPE_ROCK, TYPE_ELECTRIC),
        .catchRate = 30,
        .expYield = 285,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("IRON THORNS"),
        .cryId = CRY_IRON_THORNS,
        .natDexNum = NATIONAL_DEX_IRON_THORNS,
        .categoryName = _("Paradoja"),
        .height = 16,
        .weight = 3030,
        .description = COMPOUND_STRING(
            "Tiene similitudes con un\n"
            "POKéMON de una revista dudosa\n"
            "como un Tyranitar de hace mil millones\n"
            "years into the future."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronThorns,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronThorns,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronThorns,
        .shinyPalette = gMonShinyPalette_IronThorns,
        .iconSprite = gMonIcon_IronThorns,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-9, 12, SHADOW_SIZE_L)
        FOOTPRINT(IronThorns)
        OVERWORLD(
            sPicTable_IronThorns,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronThorns,
            gShinyOverworldPalette_IronThorns
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronThornsLevelUpLearnset,
        .teachableLearnset = sIronThornsTeachableLearnset,
    },
#endif //P_FAMILY_IRON_THORNS

#if P_FAMILY_FRIGIBAX
    [SPECIES_FRIGIBAX] =
    {
        .baseHP        = 65,
        .baseAttack    = 75,
        .baseDefense   = 45,
        .baseSpeed     = 55,
        .baseSpAttack  = 35,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 45,
        .expYield = 64,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE, ABILITY_ICE_BODY },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("FRIGIBAX"),
        .cryId = CRY_FRIGIBAX,
        .natDexNum = NATIONAL_DEX_FRIGIBAX,
        .categoryName = _("Aleta de Hielo"),
        .height = 5,
        .weight = 170,
        .description = COMPOUND_STRING(
            "Este POKéMON vive en bosques y\n"
            "zonas rocosas. Usa el poder de su\n"
            "aleta dorsal para enfriar su interior\n"
            "nest like a refrigerator."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Frigibax,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Frigibax,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 13,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Frigibax,
        .shinyPalette = gMonShinyPalette_Frigibax,
        .iconSprite = gMonIcon_Frigibax,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(2, -1, SHADOW_SIZE_S)
        FOOTPRINT(Frigibax)
        OVERWORLD(
            sPicTable_Frigibax,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Frigibax,
            gShinyOverworldPalette_Frigibax
        )
        .levelUpLearnset = sFrigibaxLevelUpLearnset,
        .teachableLearnset = sFrigibaxTeachableLearnset,
        .eggMoveLearnset = sFrigibaxEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_ARCTIBAX}),
    },

    [SPECIES_ARCTIBAX] =
    {
        .baseHP        = 90,
        .baseAttack    = 95,
        .baseDefense   = 66,
        .baseSpeed     = 62,
        .baseSpAttack  = 45,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 25,
        .expYield = 148,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE, ABILITY_ICE_BODY },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("ARCTIBAX"),
        .cryId = CRY_ARCTIBAX,
        .natDexNum = NATIONAL_DEX_ARCTIBAX,
        .categoryName = _("Aleta de Hielo"),
        .height = 8,
        .weight = 300,
        .description = COMPOUND_STRING(
            "Arctibax congela el aire a su lado,\n"
            "protege su cara con una máscara de\n"
            "hielo y usa su aleta dorsal como\n"
            "blade of ice."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Arctibax,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Arctibax,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Arctibax,
        .shinyPalette = gMonShinyPalette_Arctibax,
        .iconSprite = gMonIcon_Arctibax,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 8, SHADOW_SIZE_M)
        FOOTPRINT(Arctibax)
        OVERWORLD(
            sPicTable_Arctibax,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Arctibax,
            gShinyOverworldPalette_Arctibax
        )
        .levelUpLearnset = sArctibaxLevelUpLearnset,
        .teachableLearnset = sArctibaxTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 54, SPECIES_BAXCALIBUR}),
    },

    [SPECIES_BAXCALIBUR] =
    {
        .baseHP        = 115,
        .baseAttack    = 145,
        .baseDefense   = 92,
        .baseSpeed     = 87,
        .baseSpAttack  = 75,
        .baseSpDefense = 86,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 10,
        .expYield = 300,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE, ABILITY_ICE_BODY },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("BAXCALIBUR"),
        .cryId = CRY_BAXCALIBUR,
        .natDexNum = NATIONAL_DEX_BAXCALIBUR,
        .categoryName = _("Dragón de Hielo"),
        .height = 21,
        .weight = 2100,
        .description = COMPOUND_STRING(
            "Se lanza al combate girando sobre\n"
            "sí mismo y lanzando aire gélido por\n"
            "la boca. Así es como finaliza\n"
            "opponents off with its dorsal blade."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Baxcalibur,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Baxcalibur,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Baxcalibur,
        .shinyPalette = gMonShinyPalette_Baxcalibur,
        .iconSprite = gMonIcon_Baxcalibur,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 12, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Baxcalibur)
        OVERWORLD(
            sPicTable_Baxcalibur,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Baxcalibur,
            gShinyOverworldPalette_Baxcalibur
        )
        .levelUpLearnset = sBaxcaliburLevelUpLearnset,
        .teachableLearnset = sBaxcaliburTeachableLearnset,
        .formSpeciesIdTable = sBaxcaliburFormSpeciesIdTable,
        .formChangeTable = sBaxcaliburFormChangeTable,
    },

#if P_GEN_9_MEGA_EVOLUTIONS
    [SPECIES_BAXCALIBUR_MEGA] =
    {
        .baseHP        = 115,
        .baseAttack    = 175,
        .baseDefense   = 117,
        .baseSpeed     = 87,
        .baseSpAttack  = 105,
        .baseSpDefense = 101,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 10,
        .expYield = 300,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON, EGG_GROUP_MINERAL),
        .abilities = { ABILITY_THERMAL_EXCHANGE, ABILITY_NONE, ABILITY_ICE_BODY },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("BAXCALIBUR"),
    #if P_MODIFIED_MEGA_CRIES
        .cryId = CRY_BAXCALIBUR_MEGA,
    #else
        .cryId = CRY_BAXCALIBUR,
    #endif // P_MODIFIED_MEGA_CRIES
        .natDexNum = NATIONAL_DEX_BAXCALIBUR,
        .categoryName = _("Dragón de Hielo"),
        .height = 21,
        .weight = 3150,
        .description = COMPOUND_STRING(
            "La hoja dorsal de Baxcalibur ha\n"
            "crecido más por la Megaevolución.\n"
            "Este POKéMON lanza rayos desde la\n"
            "at its solar plexus."),
        .frontPic = gMonFrontPic_BaxcaliburMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_BaxcaliburMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_BaxcaliburMega,
        .shinyPalette = gMonShinyPalette_BaxcaliburMega,
        .iconSprite = gMonIcon_BaxcaliburMega,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(Baxcalibur)
        SHADOW(4, 14, SHADOW_SIZE_L)
        .isMegaEvolution = TRUE,
        .levelUpLearnset = sBaxcaliburLevelUpLearnset,
        .teachableLearnset = sBaxcaliburTeachableLearnset,
        .formSpeciesIdTable = sBaxcaliburFormSpeciesIdTable,
        .formChangeTable = sBaxcaliburFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_GEN_9_MEGA_EVOLUTIONS
#endif //P_FAMILY_FRIGIBAX

#if P_FAMILY_GIMMIGHOUL
    [SPECIES_GIMMIGHOUL_CHEST] =
    {
        .baseHP        = 45,
        .baseAttack    = 30,
        .baseDefense   = 70,
        .baseSpeed     = 10,
        .baseSpAttack  = 75,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 45,
        .expYield = 60,
        .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_RATTLED, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("GIMMIGHOUL"),
        .cryId = CRY_GIMMIGHOUL_CHEST,
        .natDexNum = NATIONAL_DEX_GIMMIGHOUL,
        .categoryName = _("Cofre Moneda"),
        .height = 3,
        .weight = 50,
        .description = COMPOUND_STRING(
            "Vive dentro de un viejo cofre del\n"
            "tesoro. A veces se queda en tiendas\n"
            "porque nadie nota que está ahí.\n"
            "actually a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GimmighoulChest,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GimmighoulChest,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GimmighoulChest,
        .shinyPalette = gMonShinyPalette_GimmighoulChest,
        .iconSprite = gMonIcon_GimmighoulChest,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(0, 7, SHADOW_SIZE_M)
        FOOTPRINT(GimmighoulChest)
        OVERWORLD(
            sPicTable_GimmighoulChest,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_GimmighoulChest,
            gShinyOverworldPalette_GimmighoulChest
        )
        .levelUpLearnset = sGimmighoulLevelUpLearnset,
        .teachableLearnset = sGimmighoulTeachableLearnset,
        .formSpeciesIdTable = sGimmighoulFormSpeciesIdTable,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_GHOLDENGO, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})},
                                {EVO_LEVEL, 0, SPECIES_GHOLDENGO, CONDITIONS({IF_BAG_ITEM_COUNT, ITEM_GIMMIGHOUL_COIN, 999})}),
    },

    [SPECIES_GIMMIGHOUL_ROAMING] =
    {
        .baseHP        = 45,
        .baseAttack    = 30,
        .baseDefense   = 25,
        .baseSpeed     = 80,
        .baseSpAttack  = 75,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 45,
        .expYield = 60,
        .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_RUN_AWAY, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("GIMMIGHOUL"),
        .cryId = CRY_GIMMIGHOUL_ROAMING,
        .natDexNum = NATIONAL_DEX_GIMMIGHOUL,
        .categoryName = _("Cazador Moneda"),
        .height = 1,
        .weight = 1,
        .description = COMPOUND_STRING(
            "Vaga cargando una moneda antigua\n"
            "en su espalda. Sobrevive absorbiendo\n"
            "la energía vital de los humanos.\n"
            "try to pick up its coin."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GimmighoulRoaming,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 17,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GimmighoulRoaming,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GimmighoulRoaming,
        .shinyPalette = gMonShinyPalette_GimmighoulRoaming,
        .iconSprite = gMonIcon_GimmighoulRoaming,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-1, -4, SHADOW_SIZE_S)
        FOOTPRINT(GimmighoulRoaming)
        .levelUpLearnset = sGimmighoulLevelUpLearnset,
        .teachableLearnset = sGimmighoulTeachableLearnset,
        .formSpeciesIdTable = sGimmighoulFormSpeciesIdTable,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_GHOLDENGO, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})},
                                {EVO_LEVEL, 0, SPECIES_GHOLDENGO, CONDITIONS({IF_BAG_ITEM_COUNT, ITEM_GIMMIGHOUL_COIN, 999})}),
    },

    [SPECIES_GHOLDENGO] =
    {
        .baseHP        = 87,
        .baseAttack    = 60,
        .baseDefense   = 95,
        .baseSpeed     = 84,
        .baseSpAttack  = 133,
        .baseSpDefense = 91,
        .types = MON_TYPES(TYPE_STEEL, TYPE_GHOST),
        .catchRate = 45,
        .expYield = 275,
        .evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_GOOD_AS_GOLD, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("GHOLDENGO"),
        .cryId = CRY_GHOLDENGO,
        .natDexNum = NATIONAL_DEX_GHOLDENGO,
        .categoryName = _("Entidad Moneda"),
        .height = 12,
        .weight = 300,
        .description = COMPOUND_STRING(
            "Tiene un cuerpo robusto formado por\n"
            "monedas apiladas. Gholdengo vence a\n"
            "a sus enemigos lanzando monedas\n"
            "at them in quick succession."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Gholdengo,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Gholdengo,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Gholdengo,
        .shinyPalette = gMonShinyPalette_Gholdengo,
        .iconSprite = gMonIcon_Gholdengo,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 13, SHADOW_SIZE_M)
        FOOTPRINT(Gholdengo)
        OVERWORLD(
            sPicTable_Gholdengo,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Gholdengo,
            gShinyOverworldPalette_Gholdengo
        )
        .levelUpLearnset = sGholdengoLevelUpLearnset,
        .teachableLearnset = sGholdengoTeachableLearnset,
    },
#endif //P_FAMILY_GIMMIGHOUL

#if P_FAMILY_WO_CHIEN
    [SPECIES_WO_CHIEN] =
    {
        .baseHP        = 85,
        .baseAttack    = 85,
        .baseDefense   = 100,
        .baseSpeed     = 70,
        .baseSpAttack  = 95,
        .baseSpDefense = 135,
        .types = MON_TYPES(TYPE_DARK, TYPE_GRASS),
        .catchRate = 6,
        .expYield = 285,
        .evYield_SpDefense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TABLETS_OF_RUIN, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("WO-CHIEN"),
        .cryId = CRY_WO_CHIEN,
        .natDexNum = NATIONAL_DEX_WO_CHIEN,
        .categoryName = _("Ruinoso"),
        .height = 15,
        .weight = 742,
        .description = COMPOUND_STRING(
            "El rencor de alguien castigado por\n"
            "escribir los males del rey en tablas\n"
            "tablillas de madera se ha cubierto\n"
            "dead leaves to become a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WoChien,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_WoChien,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_WoChien,
        .shinyPalette = gMonShinyPalette_WoChien,
        .iconSprite = gMonIcon_WoChien,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 11, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(WoChien)
        OVERWORLD(
            sPicTable_WoChien,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_WoChien,
            gShinyOverworldPalette_WoChien
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sWoChienLevelUpLearnset,
        .teachableLearnset = sWoChienTeachableLearnset,
    },
#endif //P_FAMILY_WO_CHIEN

#if P_FAMILY_CHIEN_PAO
    [SPECIES_CHIEN_PAO] =
    {
        .baseHP        = 80,
        .baseAttack    = 120,
        .baseDefense   = 80,
        .baseSpeed     = 135,
        .baseSpAttack  = 90,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_DARK, TYPE_ICE),
        .catchRate = 6,
        .expYield = 285,
        .evYield_Speed = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_SWORD_OF_RUIN, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("CHIEN-PAO"),
        .cryId = CRY_CHIEN_PAO,
        .natDexNum = NATIONAL_DEX_CHIEN_PAO,
        .categoryName = _("Ruinoso"),
        .height = 19,
        .weight = 1522,
        .description = COMPOUND_STRING(
            "Este POKéMON controla 100 toneladas\n"
            "de nieve caída. Juega\n"
            "inocentemente saltando dentro y\n"
            "avalanches it has caused."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ChienPao,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ChienPao,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ChienPao,
        .shinyPalette = gMonShinyPalette_ChienPao,
        .iconSprite = gMonIcon_ChienPao,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-4, 8, SHADOW_SIZE_L)
        FOOTPRINT(ChienPao)
        OVERWORLD(
            sPicTable_ChienPao,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_ChienPao,
            gShinyOverworldPalette_ChienPao
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sChienPaoLevelUpLearnset,
        .teachableLearnset = sChienPaoTeachableLearnset,
    },
#endif //P_FAMILY_CHIEN_PAO

#if P_FAMILY_TING_LU
    [SPECIES_TING_LU] =
    {
        .baseHP        = 155,
        .baseAttack    = 110,
        .baseDefense   = 125,
        .baseSpeed     = 45,
        .baseSpAttack  = 55,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_DARK, TYPE_GROUND),
        .catchRate = 6,
        .expYield = 285,
        .evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_VESSEL_OF_RUIN, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("TING-LU"),
        .cryId = CRY_TING_LU,
        .natDexNum = NATIONAL_DEX_TING_LU,
        .categoryName = _("Ruinoso"),
        .height = 27,
        .weight = 6997,
        .description = COMPOUND_STRING(
            "Baja lentamente su cabeza\n"
            "extremadamente pesada hacia el suelo,\n"
            "abriendo la tierra con su gran\n"
            "fissures that run over 160 feet deep."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_TingLu,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TingLu,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TingLu,
        .shinyPalette = gMonShinyPalette_TingLu,
        .iconSprite = gMonIcon_TingLu,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(12, 13, SHADOW_SIZE_L)
        FOOTPRINT(TingLu)
        OVERWORLD(
            sPicTable_TingLu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_TingLu,
            gShinyOverworldPalette_TingLu
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sTingLuLevelUpLearnset,
        .teachableLearnset = sTingLuTeachableLearnset,
    },
#endif //P_FAMILY_TING_LU

#if P_FAMILY_CHI_YU
    [SPECIES_CHI_YU] =
    {
        .baseHP        = 55,
        .baseAttack    = 80,
        .baseDefense   = 80,
        .baseSpeed     = 100,
        .baseSpAttack  = 135,
        .baseSpDefense = 120,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIRE),
        .catchRate = 6,
        .expYield = 285,
        .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_BEADS_OF_RUIN, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("CHI-YU"),
        .cryId = CRY_CHI_YU,
        .natDexNum = NATIONAL_DEX_CHI_YU,
        .categoryName = _("Ruinoso"),
        .height = 4,
        .weight = 49,
        .description = COMPOUND_STRING(
            "Controla llamas que arden a más de\n"
            "3000 grados Celsius. Nada\n"
            "nada tranquilamente por el mar de lava\n"
            "creates by melting rock and sand."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ChiYu,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 15,
        .backPic = gMonBackPic_ChiYu,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 14,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_ChiYu,
        .shinyPalette = gMonShinyPalette_ChiYu,
        .iconSprite = gMonIcon_ChiYu,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 16, SHADOW_SIZE_S)
        FOOTPRINT(ChiYu)
        OVERWORLD(
            sPicTable_ChiYu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_ChiYu,
            gShinyOverworldPalette_ChiYu
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sChiYuLevelUpLearnset,
        .teachableLearnset = sChiYuTeachableLearnset,
    },
#endif //P_FAMILY_CHI_YU

#if P_FAMILY_ROARING_MOON
    [SPECIES_ROARING_MOON] =
    {
        .baseHP        = 105,
        .baseAttack    = 139,
        .baseDefense   = 71,
        .baseSpeed     = 119,
        .baseSpAttack  = 55,
        .baseSpDefense = 101,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_DARK),
        .catchRate = 10,
        .expYield = 295,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("LUNA ROGADA"),
        .cryId = CRY_ROARING_MOON,
        .natDexNum = NATIONAL_DEX_ROARING_MOON,
        .categoryName = _("Paradoja"),
        .height = 20,
        .weight = 3800,
        .description = COMPOUND_STRING(
            "Según un artículo en un\n"
            "revista dudosa, este POKéMON tiene\n"
            "algún vínculo con la Megaevolución\n"
            "occurs in Hoenn."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_RoaringMoon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_RoaringMoon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_RoaringMoon,
        .shinyPalette = gMonShinyPalette_RoaringMoon,
        .iconSprite = gMonIcon_RoaringMoon,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 9, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(RoaringMoon)
        OVERWORLD(
            sPicTable_RoaringMoon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RoaringMoon,
            gShinyOverworldPalette_RoaringMoon
        )
        .isParadox = TRUE,
        .levelUpLearnset = sRoaringMoonLevelUpLearnset,
        .teachableLearnset = sRoaringMoonTeachableLearnset,
    },
#endif //P_FAMILY_ROARING_MOON

#if P_FAMILY_IRON_VALIANT
    [SPECIES_IRON_VALIANT] =
    {
        .baseHP        = 74,
        .baseAttack    = 130,
        .baseDefense   = 90,
        .baseSpeed     = 116,
        .baseSpAttack  = 120,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_FAIRY, TYPE_FIGHTING),
        .catchRate = 10,
        .expYield = 295,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("IRON VALIANT"),
        .cryId = CRY_IRON_VALIANT,
        .natDexNum = NATIONAL_DEX_IRON_VALIANT,
        .categoryName = _("Paradoja"),
        .height = 14,
        .weight = 350,
        .description = COMPOUND_STRING(
            "Se parece al invento de un científico\n"
            "loco cubierto de metal.\n"
            "paranormal magazine."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronValiant,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronValiant,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronValiant,
        .shinyPalette = gMonShinyPalette_IronValiant,
        .iconSprite = gMonIcon_IronValiant,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 14, SHADOW_SIZE_L)
        FOOTPRINT(IronValiant)
        OVERWORLD(
            sPicTable_IronValiant,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronValiant,
            gShinyOverworldPalette_IronValiant
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronValiantLevelUpLearnset,
        .teachableLearnset = sIronValiantTeachableLearnset,
    },
#endif //P_FAMILY_IRON_VALIANT

#if P_FAMILY_KORAIDON
    [SPECIES_KORAIDON] =
    {
        .baseHP        = 100,
        .baseAttack    = 135,
        .baseDefense   = 115,
        .baseSpeed     = 135,
        .baseSpAttack  = 85,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_DRAGON),
        .catchRate = 3,
        .expYield = 335,
        .evYield_Attack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_ORICHALCUM_PULSE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("KORAIDON"),
        .cryId = CRY_KORAIDON,
        .natDexNum = NATIONAL_DEX_KORAIDON,
        .categoryName = _("Paradoja"),
        .height = 25,
        .weight = 3030,
        .description = COMPOUND_STRING(
            "Se parece a Cyclizar, pero es mucho\n"
            "más robusto y feroz. No se sabe\n"
            "nada sobre su origen.\n"
            "ecology or other features."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Koraidon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Koraidon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Koraidon,
        .shinyPalette = gMonShinyPalette_Koraidon,
        .iconSprite = gMonIcon_Koraidon,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 13, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Koraidon)
        OVERWORLD(
            sPicTable_Koraidon,
            SIZE_64x64,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Koraidon,
            gShinyOverworldPalette_Koraidon
        )
        .isRestrictedLegendary = TRUE,
        .isFrontierBanned = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sKoraidonLevelUpLearnset,
        .teachableLearnset = sKoraidonTeachableLearnset,
    },
#endif //P_FAMILY_KORAIDON

#if P_FAMILY_MIRAIDON
    [SPECIES_MIRAIDON] =
    {
        .baseHP        = 100,
        .baseAttack    = 85,
        .baseDefense   = 100,
        .baseSpeed     = 135,
        .baseSpAttack  = 135,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_DRAGON),
        .catchRate = 3,
        .expYield = 335,
        .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_HADRON_ENGINE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("MIRAIDON"),
        .cryId = CRY_MIRAIDON,
        .natDexNum = NATIONAL_DEX_MIRAIDON,
        .categoryName = _("Paradoja"),
        .height = 35,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "Parece ser la Serpiente de Hierro\n"
            "del Libro Violeta. El\n"
            "Dicen que Iron Serpent convirtió el\n"
            "land to ash with its lightning."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Miraidon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_Miraidon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Miraidon,
        .shinyPalette = gMonShinyPalette_Miraidon,
        .iconSprite = gMonIcon_Miraidon,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 20, SHADOW_SIZE_L)
        FOOTPRINT(Miraidon)
        OVERWORLD(
            sPicTable_Miraidon,
            SIZE_64x64,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Miraidon,
            gShinyOverworldPalette_Miraidon
        )
        .isRestrictedLegendary = TRUE,
        .isFrontierBanned = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sMiraidonLevelUpLearnset,
        .teachableLearnset = sMiraidonTeachableLearnset,
    },
#endif //P_FAMILY_MIRAIDON

#if P_FAMILY_WALKING_WAKE
    [SPECIES_WALKING_WAKE] =
    {
        .baseHP        = 99,
        .baseAttack    = 83,
        .baseDefense   = 91,
        .baseSpeed     = 109,
        .baseSpAttack  = 125,
        .baseSpDefense = 83,
        .types = MON_TYPES(TYPE_WATER, TYPE_DRAGON),
        .catchRate = 5,
        .expYield = 295,
        .evYield_SpAttack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("WALKING WAKE"),
        .cryId = CRY_WALKING_WAKE,
        .natDexNum = NATIONAL_DEX_WALKING_WAKE,
        .categoryName = _("Paradoja"),
        .height = 35,
        .weight = 2800,
        .description = COMPOUND_STRING(
            "Esta fiera criatura está envuelta en\n"
            "misterio. Su nombre viene de un ser\n"
            "monster mentioned in an old journal."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WalkingWake,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_WalkingWake,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_WalkingWake,
        .shinyPalette = gMonShinyPalette_WalkingWake,
        .iconSprite = gMonIcon_WalkingWake,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 13, SHADOW_SIZE_L)
        FOOTPRINT(WalkingWake)
        OVERWORLD(
            sPicTable_WalkingWake,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_WalkingWake,
            gShinyOverworldPalette_WalkingWake
        )
        .isParadox = TRUE,
        .levelUpLearnset = sWalkingWakeLevelUpLearnset,
        .teachableLearnset = sWalkingWakeTeachableLearnset,
    },
#endif //P_FAMILY_WALKING_WAKE

#if P_FAMILY_IRON_LEAVES
    [SPECIES_IRON_LEAVES] =
    {
        .baseHP        = 90,
        .baseAttack    = 130,
        .baseDefense   = 88,
        .baseSpeed     = 104,
        .baseSpAttack  = 70,
        .baseSpDefense = 108,
        .types = MON_TYPES(TYPE_GRASS, TYPE_PSYCHIC),
        .catchRate = 5,
        .expYield = 295,
        .evYield_Attack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("IRON LEAVES"),
        .cryId = CRY_IRON_LEAVES,
        .natDexNum = NATIONAL_DEX_IRON_LEAVES,
        .categoryName = _("Paradoja"),
        .height = 15,
        .weight = 1250,
        .description = COMPOUND_STRING(
            "Según los pocos testigos que existen,\n"
            "usó sus hojas brillantes para cortar\n"
            "to julienne large trees and boulders."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronLeaves,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronLeaves,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronLeaves,
        .shinyPalette = gMonShinyPalette_IronLeaves,
        .iconSprite = gMonIcon_IronLeaves,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 11, SHADOW_SIZE_M)
        FOOTPRINT(IronLeaves)
        OVERWORLD(
            sPicTable_IronLeaves,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronLeaves,
            gShinyOverworldPalette_IronLeaves
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronLeavesLevelUpLearnset,
        .teachableLearnset = sIronLeavesTeachableLearnset,
    },
#endif //P_FAMILY_IRON_LEAVES

#if P_FAMILY_POLTCHAGEIST
    [SPECIES_POLTCHAGEIST_COUNTERFEIT] =
    {
        .baseHP        = 40,
        .baseAttack    = 45,
        .baseDefense   = 45,
        .baseSpeed     = 50,
        .baseSpAttack  = 74,
        .baseSpDefense = 54,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 120,
        .expYield = 62,
        .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE, ABILITY_HEATPROOF },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("POLTCHAGEIST"),
        .cryId = CRY_POLTCHAGEIST,
        .natDexNum = NATIONAL_DEX_POLTCHAGEIST,
        .categoryName = _("Matcha"),
        .height = 1,
        .weight = 11,
        .description = COMPOUND_STRING(
            "Se dice que los pesares de un maestro\n"
            "de té que murió antes de perfeccionar\n"
            "su arte quedaron atrapados en algún\n"
            "matcha and became a Pokémon."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Poltchageist,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Poltchageist,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Poltchageist,
        .shinyPalette = gMonShinyPalette_Poltchageist,
        .iconSprite = gMonIcon_Poltchageist,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 12, SHADOW_SIZE_S)
        FOOTPRINT(Poltchageist)
        OVERWORLD(
            sPicTable_Poltchageist,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Poltchageist,
            gShinyOverworldPalette_Poltchageist
        )
        .levelUpLearnset = sPoltchageistLevelUpLearnset,
        .teachableLearnset = sPoltchageistTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_LEAF_STONE, SPECIES_SINISTCHA_UNREMARKABLE},
                                {EVO_ITEM, ITEM_UNREMARKABLE_TEACUP, SPECIES_SINISTCHA_UNREMARKABLE}),
        .formSpeciesIdTable = sPoltchageistFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_SPECIAL_FORM,
    },

    [SPECIES_POLTCHAGEIST_ARTISAN] =
    {
        .baseHP        = 40,
        .baseAttack    = 45,
        .baseDefense   = 45,
        .baseSpeed     = 50,
        .baseSpAttack  = 74,
        .baseSpDefense = 54,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 120,
        .expYield = 62,
        .evYield_SpAttack = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE, ABILITY_HEATPROOF },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("POLTCHAGEIST"),
        .cryId = CRY_POLTCHAGEIST,
        .natDexNum = NATIONAL_DEX_POLTCHAGEIST,
        .categoryName = _("Matcha"),
        .height = 1,
        .weight = 11,
        .description = COMPOUND_STRING(
            "Vive en un recipiente de té muy\n"
            "caro. Se necesita a un experto\n"
            "para notar que es costoso.\n"
            "tea caddies from the cheap ones."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Poltchageist,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Poltchageist,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Poltchageist,
        .shinyPalette = gMonShinyPalette_Poltchageist,
        .iconSprite = gMonIcon_Poltchageist,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 12, SHADOW_SIZE_S)
        FOOTPRINT(Poltchageist)
        OVERWORLD(
            sPicTable_Poltchageist,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Poltchageist,
            gShinyOverworldPalette_Poltchageist
        )
        .levelUpLearnset = sPoltchageistLevelUpLearnset,
        .teachableLearnset = sPoltchageistTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_SHINY_STONE, SPECIES_SINISTCHA_MASTERPIECE},
                                {EVO_ITEM, ITEM_MASTERPIECE_TEACUP, SPECIES_SINISTCHA_MASTERPIECE}),
        .formSpeciesIdTable = sPoltchageistFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },

    [SPECIES_SINISTCHA_UNREMARKABLE] =
    {
        .baseHP        = 71,
        .baseAttack    = 60,
        .baseDefense   = 106,
        .baseSpeed     = 70,
        .baseSpAttack  = 121,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 60,
        .expYield = 178,
        .evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE, ABILITY_HEATPROOF },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SINISTCHA"),
        .cryId = CRY_SINISTCHA,
        .natDexNum = NATIONAL_DEX_SINISTCHA,
        .categoryName = _("Matcha"),
        .height = 2,
        .weight = 22,
        .description = COMPOUND_STRING(
            "Finge ser té para engañar a la\n"
            "gente y que lo beban, así puede\n"
            "absorber su energía vital.\n"
            "generally unsuccessful."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sinistcha,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Sinistcha,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 1,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sinistcha,
        .shinyPalette = gMonShinyPalette_Sinistcha,
        .iconSprite = gMonIcon_Sinistcha,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 16, SHADOW_SIZE_M)
        FOOTPRINT(Sinistcha)
        OVERWORLD(
            sPicTable_Sinistcha,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Sinistcha,
            gShinyOverworldPalette_Sinistcha
        )
        .levelUpLearnset = sSinistchaLevelUpLearnset,
        .teachableLearnset = sSinistchaTeachableLearnset,
        .formSpeciesIdTable = sSinistchaFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_SPECIAL_FORM,
    },

    [SPECIES_SINISTCHA_MASTERPIECE] =
    {
        .baseHP        = 71,
        .baseAttack    = 60,
        .baseDefense   = 106,
        .baseSpeed     = 70,
        .baseSpAttack  = 121,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_GHOST),
        .catchRate = 60,
        .expYield = 178,
        .evYield_SpAttack = 2,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL, EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_HOSPITALITY, ABILITY_NONE, ABILITY_HEATPROOF },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("SINISTCHA"),
        .cryId = CRY_SINISTCHA,
        .natDexNum = NATIONAL_DEX_SINISTCHA,
        .categoryName = _("Matcha"),
        .height = 2,
        .weight = 22,
        .description = COMPOUND_STRING(
            "Cuanto más bate el batidor de\n"
            "té que tiene en la cabeza, más\n"
            "energía acumula.\n"
            "prepare for battle."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sinistcha,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 10,
        .backPic = gMonBackPic_Sinistcha,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Sinistcha,
        .shinyPalette = gMonShinyPalette_Sinistcha,
        .iconSprite = gMonIcon_Sinistcha,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 16, SHADOW_SIZE_M)
        FOOTPRINT(Sinistcha)
        OVERWORLD(
            sPicTable_Sinistcha,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Sinistcha,
            gShinyOverworldPalette_Sinistcha
        )
        .levelUpLearnset = sSinistchaLevelUpLearnset,
        .teachableLearnset = sSinistchaTeachableLearnset,
        .formSpeciesIdTable = sSinistchaFormSpeciesIdTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_FAMILY_POLTCHAGEIST

#if P_FAMILY_OKIDOGI
    [SPECIES_OKIDOGI] =
    {
        .baseHP        = 88,
        .baseAttack    = 128,
        .baseDefense   = 115,
        .baseSpeed     = 80,
        .baseSpAttack  = 58,
        .baseSpDefense = 86,
        .types = MON_TYPES(TYPE_POISON, TYPE_FIGHTING),
        .catchRate = 3,
        .expYield = 278,
        .evYield_Attack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TOXIC_CHAIN, ABILITY_NONE, ABILITY_GUARD_DOG },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("OKIDOGI"),
        .cryId = CRY_OKIDOGI,
        .natDexNum = NATIONAL_DEX_OKIDOGI,
        .categoryName = _("Retenedor"),
        .height = 18,
        .weight = 920,
        .description = COMPOUND_STRING(
            "Tras estimular todos sus músculos\n"
            "con la cadena tóxica del cuello,\n"
            "Okidogi cambió y se convirtió en\n"
            "a powerful physique."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Okidogi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Okidogi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Okidogi,
        .shinyPalette = gMonShinyPalette_Okidogi,
        .iconSprite = gMonIcon_Okidogi,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 11, SHADOW_SIZE_L)
        FOOTPRINT(Okidogi)
        OVERWORLD(
            sPicTable_Okidogi,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Okidogi,
            gShinyOverworldPalette_Okidogi
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sOkidogiLevelUpLearnset,
        .teachableLearnset = sOkidogiTeachableLearnset,
    },
#endif //P_FAMILY_OKIDOGI

#if P_FAMILY_MUNKIDORI
    [SPECIES_MUNKIDORI] =
    {
        .baseHP        = 88,
        .baseAttack    = 75,
        .baseDefense   = 66,
        .baseSpeed     = 106,
        .baseSpAttack  = 130,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_POISON, TYPE_PSYCHIC),
        .catchRate = 3,
        .expYield = 278,
        .evYield_SpAttack = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TOXIC_CHAIN, ABILITY_NONE, ABILITY_FRISK },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("MUNKIDORI"),
        .cryId = CRY_MUNKIDORI,
        .natDexNum = NATIONAL_DEX_MUNKIDORI,
        .categoryName = _("Retenedor"),
        .height = 10,
        .weight = 122,
        .description = COMPOUND_STRING(
            "La cadena tiene toxinas que\n"
            "mejoran las capacidades. Estimuló\n"
            "el cerebro de Munkidori y creó al\n"
            "Pokémon's psychic powers to bloom."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Munkidori,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Munkidori,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Munkidori,
        .shinyPalette = gMonShinyPalette_Munkidori,
        .iconSprite = gMonIcon_Munkidori,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 8, SHADOW_SIZE_S)
        FOOTPRINT(Munkidori)
        OVERWORLD(
            sPicTable_Munkidori,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Munkidori,
            gShinyOverworldPalette_Munkidori
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sMunkidoriLevelUpLearnset,
        .teachableLearnset = sMunkidoriTeachableLearnset,
    },
#endif //P_FAMILY_MUNKIDORI

#if P_FAMILY_FEZANDIPITI
    [SPECIES_FEZANDIPITI] =
    {
        .baseHP        = 88,
        .baseAttack    = 91,
        .baseDefense   = 82,
        .baseSpeed     = 99,
        .baseSpAttack  = 70,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = 3,
        .expYield = 278,
        .evYield_SpDefense = 3,
        .genderRatio = MON_MALE,
        .eggCycles = 120,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TOXIC_CHAIN, ABILITY_NONE, ABILITY_TECHNICIAN },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("FEZANDIPITI"),
        .cryId = CRY_FEZANDIPITI,
        .natDexNum = NATIONAL_DEX_FEZANDIPITI,
        .categoryName = _("Retenedor"),
        .height = 14,
        .weight = 301,
        .description = COMPOUND_STRING(
            "Fezandipiti debe su belleza y su\n"
            "bella voz a los estimulantes tóxicos\n"
            "de la cadena que envuelve a\n"
            "its body."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fezandipiti,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Fezandipiti,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Fezandipiti,
        .shinyPalette = gMonShinyPalette_Fezandipiti,
        .iconSprite = gMonIcon_Fezandipiti,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 10, SHADOW_SIZE_M)
        FOOTPRINT(Fezandipiti)
        OVERWORLD(
            sPicTable_Fezandipiti,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Fezandipiti,
            gShinyOverworldPalette_Fezandipiti
        )
        .isSubLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sFezandipitiLevelUpLearnset,
        .teachableLearnset = sFezandipitiTeachableLearnset,
    },
#endif //P_FAMILY_FEZANDIPITI

#if P_FAMILY_OGERPON
#define OGERPON_SPECIES_INFO(Form1, Form2, type, ability, color, frontYOffset, iconpalette, isTeraform)    \
    {                                                                                                      \
        .baseHP        = 80,                                                                               \
        .baseAttack    = 120,                                                                              \
        .baseDefense   = 84,                                                                               \
        .baseSpeed     = 110,                                                                              \
        .baseSpAttack  = 60,                                                                               \
        .baseSpDefense = 96,                                                                               \
        .types = MON_TYPES(TYPE_GRASS, type),                                                              \
        .forceTeraType = type,                                                                             \
        .catchRate = 5,                                                                                    \
        .expYield = 275,                                                                                   \
        .evYield_Attack = 3,                                                                               \
        .genderRatio = MON_FEMALE,                                                                         \
        .eggCycles = 10,                                                                                   \
        .friendship = STANDARD_FRIENDSHIP,                                                                 \
        .growthRate = GROWTH_SLOW,                                                                         \
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),                                         \
        .abilities = { ability, ABILITY_NONE },                                                            \
        .bodyColor = color,                                                                                \
        .speciesName = _("OGERPON"),                                                                       \
        .cryId = CRY_OGERPON,                                                                              \
        .natDexNum = NATIONAL_DEX_OGERPON,                                                                 \
        .categoryName = _("Máscara"),                                                                         \
        .height = 12,                                                                                      \
        .weight = 398,                                                                                     \
        .description = gOgerpon##Form1##MaskPokedexText,                                                   \
        .pokemonScale = 356,                                                                               \
        .pokemonOffset = 17,                                                                               \
        .trainerScale = 256,                                                                               \
        .trainerOffset = 0,                                                                                \
        .frontPic = gMonFrontPic_Ogerpon##Form2,                                                           \
        .frontPicSize = MON_COORDS_SIZE(64, 64),                                                           \
        .frontPicYOffset = frontYOffset,                                                                   \
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,                                                  \
        /*.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,*/                                                       \
        .backPic = gMonBackPic_Ogerpon##Form2,                                                             \
        .backPicSize = MON_COORDS_SIZE(64, 64),                                                            \
        .backPicYOffset = 0,                                                                               \
        /*.backAnimId = BACK_ANIM_NONE,*/                                                                  \
        .palette = gMonPalette_Ogerpon##Form2,                                                             \
        .shinyPalette = gMonShinyPalette_Ogerpon##Form2,                                                   \
        .iconSprite = gMonIcon_Ogerpon##Form1,                                                             \
        .iconPalIndex = iconpalette,                                                                       \
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,                                                            \
        SHADOW(3, 12, SHADOW_SIZE_M)                                                                       \
        FOOTPRINT(Ogerpon)                                                                                 \
        OVERWORLD(                                                                                         \
            sPicTable_Ogerpon##Form2,                                                                      \
            SIZE_32x32,                                                                                    \
            SHADOW_SIZE_M,                                                                                 \
            TRACKS_FOOT,                                                                                   \
            sAnimTable_Following,                                                                          \
            gOverworldPalette_Ogerpon##Form2,                                                              \
            gShinyOverworldPalette_Ogerpon##Form2                                                          \
        )                                                                                                  \
        .levelUpLearnset = sOgerponLevelUpLearnset,                                                        \
        .teachableLearnset = sOgerponTeachableLearnset,                                                    \
        .formSpeciesIdTable = sOgerponFormSpeciesIdTable,                                                  \
        .formChangeTable = sOgerpon##Form1##FormChangeTable,                                               \
        .isSubLegendary = TRUE,                                                                            \
        .isTeraForm = isTeraform,                                                                          \
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,                                                      \
        .randomizerMode = (!(isTeraform) && ((type) == TYPE_GRASS))                                        \
        ? MON_RANDOMIZER_NORMAL : MON_RANDOMIZER_INVALID,                                                  \
    }

    [SPECIES_OGERPON_TEAL]             = OGERPON_SPECIES_INFO(Teal,        Teal,            TYPE_GRASS, ABILITY_DEFIANT,                        BODY_COLOR_GREEN, 2, 1, FALSE),
    [SPECIES_OGERPON_WELLSPRING]       = OGERPON_SPECIES_INFO(Wellspring,  Wellspring,      TYPE_WATER, ABILITY_WATER_ABSORB,                   BODY_COLOR_BLUE,  2, 0, FALSE),
    [SPECIES_OGERPON_HEARTHFLAME]      = OGERPON_SPECIES_INFO(Hearthflame, Hearthflame,     TYPE_FIRE,  ABILITY_MOLD_BREAKER,                   BODY_COLOR_RED,   2, 0, FALSE),
    [SPECIES_OGERPON_CORNERSTONE]      = OGERPON_SPECIES_INFO(Cornerstone, Cornerstone,     TYPE_ROCK,  ABILITY_STURDY,                         BODY_COLOR_GRAY,  2, 0, FALSE),
#if P_TERA_FORMS
    [SPECIES_OGERPON_TEAL_TERA]        = OGERPON_SPECIES_INFO(Teal,        TealTera,        TYPE_GRASS, ABILITY_EMBODY_ASPECT_TEAL_MASK,        BODY_COLOR_GREEN, 0, 1, TRUE),
    [SPECIES_OGERPON_WELLSPRING_TERA]  = OGERPON_SPECIES_INFO(Wellspring,  WellspringTera,  TYPE_WATER, ABILITY_EMBODY_ASPECT_WELLSPRING_MASK,  BODY_COLOR_BLUE,  0, 0, TRUE),
    [SPECIES_OGERPON_HEARTHFLAME_TERA] = OGERPON_SPECIES_INFO(Hearthflame, HearthflameTera, TYPE_FIRE,  ABILITY_EMBODY_ASPECT_HEARTHFLAME_MASK, BODY_COLOR_RED,   0, 0, TRUE),
    [SPECIES_OGERPON_CORNERSTONE_TERA] = OGERPON_SPECIES_INFO(Cornerstone, CornerstoneTera, TYPE_ROCK,  ABILITY_EMBODY_ASPECT_CORNERSTONE_MASK, BODY_COLOR_GRAY,  0, 0, TRUE),
#endif //P_TERA_FORMS

#endif //P_FAMILY_OGERPON

#if P_FAMILY_GOUGING_FIRE
    [SPECIES_GOUGING_FIRE] =
    {
        .baseHP        = 105,
        .baseAttack    = 115,
        .baseDefense   = 121,
        .baseSpeed     = 91,
        .baseSpAttack  = 65,
        .baseSpDefense = 93,
        .types = MON_TYPES(TYPE_FIRE, TYPE_DRAGON),
        .catchRate = 10,
        .expYield = 295,
        .evYield_Defense = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("GOUGING FIRE"),
        .cryId = CRY_GOUGING_FIRE,
        .natDexNum = NATIONAL_DEX_GOUGING_FIRE,
        .categoryName = _("Paradoja"),
        .height = 35,
        .weight = 5900,
        .description = COMPOUND_STRING(
            "Hay muy pocos reportes de\n"
            "avistamientos de esta criatura.\n"
            "Un video corto lo muestra enfurecido,\n"
            "and spouting pillars of flame."),
        .pokemonScale = 259,
        .pokemonOffset = 0,
        .trainerScale = 345,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_GougingFire,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_GougingFire,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_GougingFire,
        .shinyPalette = gMonShinyPalette_GougingFire,
        .iconSprite = gMonIcon_GougingFire,
        .iconPalIndex = 5,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 6, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(GougingFire)
        OVERWORLD(
            sPicTable_GougingFire,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_GougingFire,
            gShinyOverworldPalette_GougingFire
        )
        .isParadox = TRUE,
        .levelUpLearnset = sGougingFireLevelUpLearnset,
        .teachableLearnset = sGougingFireTeachableLearnset,
    },
#endif //P_FAMILY_GOUGING_FIRE

#if P_FAMILY_RAGING_BOLT
    [SPECIES_RAGING_BOLT] =
    {
        .baseHP        = 125,
        .baseAttack    = 73,
        .baseDefense   = 91,
        .baseSpeed     = 75,
        .baseSpAttack  = 137,
        .baseSpDefense = 89,
        .types = MON_TYPES(TYPE_ELECTRIC, TYPE_DRAGON),
        .catchRate = 10,
        .expYield = 295,
        .evYield_SpAttack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("RAGING BOLT"),
        .cryId = CRY_RAGING_BOLT,
        .natDexNum = NATIONAL_DEX_RAGING_BOLT,
        .categoryName = _("Paradoja"),
        .height = 52,
        .weight = 4800,
        .description = COMPOUND_STRING(
            "Se parece a un POKéMON que fue\n"
            "tema popular por un tiempo tras\n"
            "una revista paranormal.\n"
            "touted it as Raikou's ancestor."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 345,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_RagingBolt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_RagingBolt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_RagingBolt,
        .shinyPalette = gMonShinyPalette_RagingBolt,
        .iconSprite = gMonIcon_RagingBolt,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 14, SHADOW_SIZE_L)
        FOOTPRINT(RagingBolt)
        OVERWORLD(
            sPicTable_RagingBolt,
            SIZE_64x64,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_RagingBolt,
            gShinyOverworldPalette_RagingBolt
        )
        .isParadox = TRUE,
        .levelUpLearnset = sRagingBoltLevelUpLearnset,
        .teachableLearnset = sRagingBoltTeachableLearnset,
    },
#endif //P_FAMILY_RAGING_BOLT

#if P_FAMILY_IRON_BOULDER
    [SPECIES_IRON_BOULDER] =
    {
        .baseHP        = 90,
        .baseAttack    = 120,
        .baseDefense   = 80,
        .baseSpeed     = 124,
        .baseSpAttack  = 68,
        .baseSpDefense = 108,
        .types = MON_TYPES(TYPE_ROCK, TYPE_PSYCHIC),
        .catchRate = 10,
        .expYield = 295,
        .evYield_Speed = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("IRON BOULDER"),
        .cryId = CRY_IRON_BOULDER,
        .natDexNum = NATIONAL_DEX_IRON_BOULDER,
        .categoryName = _("Paradoja"),
        .height = 15,
        .weight = 1625,
        .description = COMPOUND_STRING(
            "Su nombre viene de un objeto\n"
            "misterioso de un libro antiguo.\n"
            "Its body seems to be metallic."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 336,
        .trainerOffset = 4,
        .frontPic = gMonFrontPic_IronBoulder,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronBoulder,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronBoulder,
        .shinyPalette = gMonShinyPalette_IronBoulder,
        .iconSprite = gMonIcon_IronBoulder,
        .iconPalIndex = 5,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 7, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(IronBoulder)
        OVERWORLD(
            sPicTable_IronBoulder,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronBoulder,
            gShinyOverworldPalette_IronBoulder
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronBoulderLevelUpLearnset,
        .teachableLearnset = sIronBoulderTeachableLearnset,
    },
#endif //P_FAMILY_IRON_BOULDER

#if P_FAMILY_IRON_CROWN
    [SPECIES_IRON_CROWN] =
    {
        .baseHP        = 90,
        .baseAttack    = 72,
        .baseDefense   = 100,
        .baseSpeed     = 98,
        .baseSpAttack  = 122,
        .baseSpDefense = 108,
        .types = MON_TYPES(TYPE_STEEL, TYPE_PSYCHIC),
        .catchRate = 10,
        .expYield = 295,
        .evYield_SpAttack = 3,
        .itemRare = ITEM_BOOSTER_ENERGY,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 50,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("CORONA FÉRREA"),
        .cryId = CRY_IRON_CROWN,
        .natDexNum = NATIONAL_DEX_IRON_CROWN,
        .categoryName = _("Paradoja"),
        .height = 16,
        .weight = 1560,
        .description = COMPOUND_STRING(
            "Se parece a un objeto misterioso\n"
            "que apareció en una revista\n"
            "como un arma de vanguardia\n"
            "shaped like Cobalion."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_IronCrown,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_IronCrown,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 2,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronCrown,
        .shinyPalette = gMonShinyPalette_IronCrown,
        .iconSprite = gMonIcon_IronCrown,
        .iconPalIndex = 3,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 14, SHADOW_SIZE_L)
        FOOTPRINT(IronCrown)
        OVERWORLD(
            sPicTable_IronCrown,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_IronCrown,
            gShinyOverworldPalette_IronCrown
        )
        .isParadox = TRUE,
        .levelUpLearnset = sIronCrownLevelUpLearnset,
        .teachableLearnset = sIronCrownTeachableLearnset,
    },
#endif //P_FAMILY_IRON_CROWN

#if P_FAMILY_TERAPAGOS
    [SPECIES_TERAPAGOS_NORMAL] =
    {
        .baseHP        = 90,
        .baseAttack    = 65,
        .baseDefense   = 85,
        .baseSpeed     = 60,
        .baseSpAttack  = 65,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_NORMAL),
        .forceTeraType = TYPE_STELLAR,
        .catchRate = 255,
        .expYield = 90,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TERA_SHIFT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("TERAPAGOS"),
        .cryId = CRY_TERAPAGOS,
        .natDexNum = NATIONAL_DEX_TERAPAGOS,
        .categoryName = _("Tera"),
        .height = 2,
        .weight = 65,
        .description = COMPOUND_STRING(
            "Terapagos se protege usando su\n"
            "poder para crear cristales duros\n"
            "de energía. Es la fuente de todo\n"
            "of the Terastal phenomenon."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_TerapagosNormal,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TerapagosNormal,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 9,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TerapagosNormal,
        .shinyPalette = gMonShinyPalette_TerapagosNormal,
        .iconSprite = gMonIcon_TerapagosNormal,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, 2, SHADOW_SIZE_M)
        FOOTPRINT(TerapagosNormal)
        OVERWORLD(
            sPicTable_TerapagosNormal,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_TerapagosNormal,
            gShinyOverworldPalette_TerapagosNormal
        )
        .isRestrictedLegendary = TRUE,
        .isFrontierBanned = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sTerapagosLevelUpLearnset,
        .teachableLearnset = sTerapagosTeachableLearnset,
        .formSpeciesIdTable = sTerapagosFormSpeciesIdTable,
        .formChangeTable = sTerapagosFormChangeTable,
    },

    [SPECIES_TERAPAGOS_TERASTAL] =
    {
        .baseHP        = 95,
        .baseAttack    = 95,
        .baseDefense   = 110,
        .baseSpeed     = 85,
        .baseSpAttack  = 105,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_NORMAL),
        .forceTeraType = TYPE_STELLAR,
        .catchRate = 255,
        .expYield = 120,
        .evYield_Defense = 2,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TERA_SHELL, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("TERAPAGOS"),
        .cryId = CRY_TERAPAGOS,
        .natDexNum = NATIONAL_DEX_TERAPAGOS,
        .categoryName = _("Tera"),
        .height = 3,
        .weight = 160,
        .description = COMPOUND_STRING(
            "Su caparazón es energía Teracristal\n"
            "cristalizada. Al recibir un ataque,\n"
            "el caparazón absorbe esa energía\n"
            "and transfers it to Terapagos."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_TerapagosTerastal,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 8,
        .backPic = gMonBackPic_TerapagosTerastal,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 11,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TerapagosTerastal,
        .shinyPalette = gMonShinyPalette_TerapagosTerastal,
        .iconSprite = gMonIcon_TerapagosTerastal,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-4, 8, SHADOW_SIZE_L)
        FOOTPRINT(TerapagosTerastal)
        OVERWORLD(
            sPicTable_TerapagosTerastal,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_TerapagosTerastal,
            gShinyOverworldPalette_TerapagosTerastal
        )
        .isRestrictedLegendary = TRUE,
        .isFrontierBanned = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sTerapagosLevelUpLearnset,
        .teachableLearnset = sTerapagosTeachableLearnset,
        .formSpeciesIdTable = sTerapagosFormSpeciesIdTable,
        .formChangeTable = sTerapagosFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },

    [SPECIES_TERAPAGOS_STELLAR] =
    {
        .baseHP        = 160,
        .baseAttack    = 105,
        .baseDefense   = 110,
        .baseSpeed     = 85,
        .baseSpAttack  = 130,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_NORMAL),
        .forceTeraType = TYPE_STELLAR,
        .catchRate = 255,
        .expYield = 140,
        .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_TERAFORM_ZERO, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("TERAPAGOS"),
        .cryId = CRY_TERAPAGOS,
        .natDexNum = NATIONAL_DEX_TERAPAGOS,
        .categoryName = _("Tera"),
        .height = 17,
        .weight = 770,
        .description = COMPOUND_STRING(
            "Un viejo diario de expedición dice\n"
            "que este Pokémon, enterrado en lo\n"
            "profundo de la tierra, se parece a\n"
            "planet floating in space."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_TerapagosStellar,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_TerapagosStellar,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 0,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_TerapagosStellar,
        .shinyPalette = gMonShinyPalette_TerapagosStellar,
        .iconSprite = gMonIcon_TerapagosStellar,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 12, SHADOW_SIZE_L)
        FOOTPRINT(TerapagosStellar)
        .isRestrictedLegendary = TRUE,
        .isTeraForm = TRUE,
        .isFrontierBanned = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sTerapagosLevelUpLearnset,
        .teachableLearnset = sTerapagosTeachableLearnset,
        .formSpeciesIdTable = sTerapagosFormSpeciesIdTable,
        .formChangeTable = sTerapagosFormChangeTable,
        .randomizerMode = MON_RANDOMIZER_INVALID,
    },
#endif //P_FAMILY_TERAPAGOS

#if P_FAMILY_PECHARUNT
    [SPECIES_PECHARUNT] =
    {
        .baseHP        = 88,
        .baseAttack    = 88,
        .baseDefense   = 160,
        .baseSpeed     = 88,
        .baseSpAttack  = 88,
        .baseSpDefense = 88,
        .types = MON_TYPES(TYPE_POISON, TYPE_GHOST),
        .catchRate = 3,
        .expYield = 300,
        .evYield_Defense = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_POISON_PUPPETEER, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("PECHARUNT"),
        .cryId = CRY_PECHARUNT,
        .natDexNum = NATIONAL_DEX_PECHARUNT,
        .categoryName = _("Subyugación"),
        .height = 3,
        .weight = 3,
        .description = COMPOUND_STRING(
            "Da a otros mochi tóxicos que\n"
            "extraen deseos y capacidades.\n"
            "Quienes comen el mochi caen bajo\n"
            "Pecharunt's control, chained to its will."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 365,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_Pecharunt,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Pecharunt,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 5,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Pecharunt,
        .shinyPalette = gMonShinyPalette_Pecharunt,
        .iconSprite = gMonIcon_Pecharunt,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 1, SHADOW_SIZE_L)
        FOOTPRINT(Pecharunt)
        OVERWORLD(
            sPicTable_Pecharunt,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Pecharunt,
            gShinyOverworldPalette_Pecharunt
        )
        .isMythical = TRUE,
        .isFrontierBanned = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sPecharuntLevelUpLearnset,
        .teachableLearnset = sPecharuntTeachableLearnset,
    },
#endif //P_FAMILY_PECHARUNT

#ifdef __INTELLISENSE__
};
#endif
