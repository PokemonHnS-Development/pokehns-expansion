#if I_USE_EVO_HELD_ITEMS_FROM_BAG == TRUE
    #define EVO_HELD_ITEM_TYPE ITEM_USE_PARTY_MENU
    #define EVO_HELD_ITEM_FIELD_FUNC ItemUseOutOfBattle_EvolutionStone
#else
    #define EVO_HELD_ITEM_TYPE ITEM_USE_BAG_MENU
    #define EVO_HELD_ITEM_FIELD_FUNC ItemUseOutOfBattle_CannotUse
#endif

#define GEM_BOOST_PARAM ((I_GEM_BOOST_POWER >= GEN_6) ? 30 : 50)
#define TYPE_BOOST_PARAM ((I_TYPE_BOOST_POWER >= GEN_4) ? 20 : 10) // For non Pokémon-specific type-boosting held items.
#define POWER_ITEM_BOOST ((I_POWER_ITEM_BOOST >= GEN_7) ? 8 : 4)

#define X_ITEM_STAGES ((B_X_ITEMS_BUFF >= GEN_7) ? 2 : 1)

#define TREASURE_FACTOR ((I_SELL_VALUE_FRACTION >= GEN_9) ? 2 : 1)

#define ITEM_NAME(str) COMPOUND_STRING_SIZE_LIMIT(str, ITEM_NAME_LENGTH)
#define ITEM_PLURAL_NAME(str) COMPOUND_STRING_SIZE_LIMIT(str, ITEM_NAME_PLURAL_LENGTH)

// Shared Item Description entries

static const u8 sFullHealDesc[]       = _("Heals all the\n"
                                          "status problems of\n"
                                          "one Pokémon.");

static const u8 sPokeDollDesc[]       = _("Use to flee from\n"
                                          "any battle with\n"
                                          "a wild Pokémon.");

static const u8 sMaxReviveDesc[]      = _("Revives a fainted\n"
                                          "Pokémon with all\n"
                                          "its HP.");

static const u8 sHealthFeatherDesc[]  = _("An item that raises\n"
                                          "the base HP of\n"
                                          "a Pokémon.");

static const u8 sMuscleFeatherDesc[]  = _("An item that raises\n"
                                          "the base Attack of\n"
                                          "a Pokémon.");

static const u8 sResistFeatherDesc[]  = _("An item that raises\n"
                                          "the base Defense\n"
                                          "of a Pokémon.");

static const u8 sGeniusFeatherDesc[]  = _("An item that raises\n"
                                          "the base Sp. Atk.\n"
                                          "of a Pokémon.");

static const u8 sCleverFeatherDesc[]  = _("An item that raises\n"
                                          "the base Sp. Def.\n"
                                          "of a Pokémon.");

static const u8 sSwiftFeatherDesc[]   = _("An item that raises\n"
                                          "the base Speed of\n"
                                          "a Pokémon.");

static const u8 sBigMushroomDesc[]    = _("A rare mushroom\n"
                                          "that would sell at a\n"
                                          "high price.");

static const u8 sShardsDesc[]         = _("A shard from an\n"
                                          "ancient item. Can\n"
                                          "be sold cheaply.");

static const u8 sRootFossilDesc[]     = _("A fossil of an\n"
                                          "ancient, seafloor-\n"
                                          "dwelling Pokémon.");

static const u8 sFossilizedFishDesc[] = _("A fossil of an\n"
                                          "ancient, sea-\n"
                                          "dwelling Pokémon.");

static const u8 sBeadMailDesc[]       = _("Mail featuring a\n"
                                          "sketch of the\n"
                                          "holding Pokémon.");

static const u8 sEvolutionStoneDesc[] = _("Makes certain\n"
                                          "species of Pokémon\n"
                                          "evolve.");

static const u8 sNectarDesc[]         = _("Flower nectar that\n"
                                          "changes the form\n"
                                          "of certain Pokémon.");

static const u8 sCharizarditeDesc[]   = _("This stone enables\n"
                                          "Charizard to Mega\n"
                                          "Evolve in battle.");

static const u8 sMewtwoniteDesc[]     = _("This stone enables\n"
                                          "Mewtwo to Mega\n"
                                          "Evolve in battle.");

static const u8 sRaichuniteDesc[]     = _("This stone enables\n"
                                          "Raichu to Mega\n"
                                          "Evolve in battle.");

static const u8 sAbsoliteDesc[]       = _("This stone enables\n"
                                          "Absol to Mega\n"
                                          "Evolve in battle.");

static const u8 sGarchompiteDesc[]    = _("This stone enables\n"
                                          "Garchomp to Mega\n"
                                          "Evolve in battle.");

static const u8 sLucarioniteDesc[]    = _("This stone enables\n"
                                          "Lucario to Mega\n"
                                          "Evolve in battle.");

static const u8 sSeaIncenseDesc[]     = _("A hold item that\n"
                                          "slightly boosts\n"
                                          "Water-type moves.");

static const u8 sOddIncenseDesc[]     = _("A hold item that\n"
                                          "boosts Psychic-\n"
                                          "type moves.");

static const u8 sRockIncenseDesc[]    = _("A hold item that\n"
                                          "raises the power of\n"
                                          "Rock-type moves.");

static const u8 sFullIncenseDesc[]    = _("A held item that\n"
                                          "makes the holder\n"
                                          "move slower.");

static const u8 sRoseIncenseDesc[]    = _("A hold item that\n"
                                          "raises the power of\n"
                                          "Grass-type moves.");

static const u8 sLuckIncenseDesc[]    = _("Doubles money in\n"
                                          "battle if the\n"
                                          "holder takes part.");

static const u8 sPureIncenseDesc[]    = _("A hold item that\n"
                                          "helps repel wild\n"
                                          "Pokémon.");

static const u8 sKingsRockDesc[]      = _("A hold item that\n"
                                          "may cause flinching\n"
                                          "when the foe is hit.");

static const u8 sFigyBerryDesc[]      = _("A hold item that\n"
                                          "restores HP but\n"
                                          "may confuse.");

const u8 gQuestionMarksItemName[] = _("????????");

static const u8 sQuestionMarksDesc[]  = _("?????");

static const u8 sKeyToRoomDesc[]      = _("A key that opens a\n"
                                          "door inside the\n"
                                          "Abandoned Ship.");

static const u8 sTeraShardDesc[]      = _("These shards may\n"
                                          "form when a Tera\n"
                                          "Pokémon faints.");

static const u8 sGenericMulchDesc[]   = _("A fertilizer that\n"
                                          "is unsuitable for\n"
                                          "local soil.");

const struct ItemInfo gItemsInfo[] =
{
    [ITEM_NONE] =
    {
        .name = gQuestionMarksItemName,
        .price = 0,
        .description = sQuestionMarksDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_UNCATEGORIZED,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

// Poké Balls

    [ITEM_STRANGE_BALL] =
    {
        .name = ITEM_NAME("STRANGE BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An unusual Ball\n"
            "warped through\n"
            "space and time."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_STRANGE,
        .iconPic = gItemIcon_StrangeBall,
        .iconPalette = gItemIconPalette_StrangeBall,
    },

    [ITEM_POKE_BALL] =
    {
        .name = ITEM_NAME("POKé BALL"),
        .price = 200,
        .description = COMPOUND_STRING(
            "A tool used for\n"
            "catching wild\n"
            "Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_POKE,
        .iconPic = gItemIcon_PokeBall,
        .iconPalette = gItemIconPalette_PokeBall,
    },

    [ITEM_GREAT_BALL] =
    {
        .name = ITEM_NAME("GREAT BALL"),
        .price = 600,
        .description = COMPOUND_STRING(
            "A good Ball with a\n"
            "higher catch rate\n"
            "than a Poké Ball."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_GREAT,
        .iconPic = gItemIcon_GreatBall,
        .iconPalette = gItemIconPalette_GreatBall,
    },

    [ITEM_ULTRA_BALL] =
    {
        .name = ITEM_NAME("ULTRA BALL"),
        .price = (I_PRICE >= GEN_7) ? 800 : 1200,
        .description = COMPOUND_STRING(
            "A better Ball with\n"
            "a higher catch rate\n"
            "than a Great Ball."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_ULTRA,
        .iconPic = gItemIcon_UltraBall,
        .iconPalette = gItemIconPalette_UltraBall,
    },

    [ITEM_MASTER_BALL] =
    {
        .name = ITEM_NAME("MASTER BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The best Ball that\n"
            "catches a Pokémon\n"
            "without fail."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_MASTER,
        .iconPic = gItemIcon_MasterBall,
        .iconPalette = gItemIconPalette_MasterBall,
    },

    [ITEM_PREMIER_BALL] =
    {
        .name = ITEM_NAME("PREMIER BALL"),
        .price = (I_PRICE >= GEN_7) ? 20 : 200,
        .description = COMPOUND_STRING(
            "A rare Ball made\n"
            "in commemoration\n"
            "of some event."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_PREMIER,
        .iconPic = gItemIcon_PremierBall,
        .iconPalette = gItemIconPalette_PremierBall,
    },

    [ITEM_HEAL_BALL] =
    {
        .name = ITEM_NAME("HEAL BALL"),
        .price = 300,
        .description = COMPOUND_STRING(
            "A remedial Ball\n"
            "that restores\n"
            "caught Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_HEAL,
        .iconPic = gItemIcon_HealBall,
        .iconPalette = gItemIconPalette_HealBall,
    },

    [ITEM_NET_BALL] =
    {
        .name = ITEM_NAME("NET BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "well on Water- and\n"
            "Bug-type Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_NET,
        .iconPic = gItemIcon_NetBall,
        .iconPalette = gItemIconPalette_NetBall,
    },

    [ITEM_NEST_BALL] =
    {
        .name = ITEM_NAME("NEST BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "better on weaker\n"
            "Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_NEST,
        .iconPic = gItemIcon_NestBall,
        .iconPalette = gItemIconPalette_NestBall,
    },

    [ITEM_DIVE_BALL] =
    {
        .name = ITEM_NAME("DIVE BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "better on Pokémon\n"
            "on the ocean floor."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_DIVE,
        .iconPic = gItemIcon_DiveBall,
        .iconPalette = gItemIconPalette_DiveBall,
    },

    [ITEM_DUSK_BALL] =
    {
        .name = ITEM_NAME("DUSK BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "Works well if\n"
            "used in a\n"
            "dark place."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_DUSK,
        .iconPic = gItemIcon_DuskBall,
        .iconPalette = gItemIconPalette_DuskBall,
    },

    [ITEM_TIMER_BALL] =
    {
        .name = ITEM_NAME("TIMER BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A Ball that gains\n"
            "power in battles\n"
            "taking many turns."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_TIMER,
        .iconPic = gItemIcon_TimerBall,
        .iconPalette = gItemIconPalette_RepeatBall,
    },

    [ITEM_QUICK_BALL] =
    {
        .name = ITEM_NAME("QUICK BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "Works well if\n"
            "used on the\n"
            "first turn."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_QUICK,
        .iconPic = gItemIcon_QuickBall,
        .iconPalette = gItemIconPalette_QuickBall,
    },

    [ITEM_REPEAT_BALL] =
    {
        .name = ITEM_NAME("REPEAT BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "better on Pokémon\n"
            "caught before."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_REPEAT,
        .iconPic = gItemIcon_RepeatBall,
        .iconPalette = gItemIconPalette_RepeatBall,
    },

    [ITEM_LUXURY_BALL] =
    {
        .name = ITEM_NAME("LUXURY BALL"),
        .price = (I_PRICE >= GEN_8) ? 3000 : 1000,
        .description = COMPOUND_STRING(
            "A cozy Ball that\n"
            "makes Pokémon\n"
            "more friendly."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LUXURY,
        .iconPic = gItemIcon_LuxuryBall,
        .iconPalette = gItemIconPalette_LuxuryBall,
    },

    [ITEM_LEVEL_BALL] =
    {
        .name = ITEM_NAME("LEVEL BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "well on lower\n"
            "level Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LEVEL,
        .iconPic = gItemIcon_LevelBall,
        .iconPalette = gItemIconPalette_LevelBall,
    },

    [ITEM_LURE_BALL] =
    {
        .name = ITEM_NAME("LURE BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "well on fished\n"
            "up Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LURE,
        .iconPic = gItemIcon_LureBall,
        .iconPalette = gItemIconPalette_LureBall,
    },

    [ITEM_MOON_BALL] =
    {
        .name = ITEM_NAME("MOON BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "A Ball that works\n"
            "well on Moon\n"
            "Stone users."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_MOON,
        .iconPic = gItemIcon_MoonBall,
        .iconPalette = gItemIconPalette_MoonBall,
    },

    [ITEM_FRIEND_BALL] =
    {
        .name = ITEM_NAME("FRIEND BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "A Ball that makes\n"
            "a Pokémon friendly\n"
            "when caught."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_FRIEND,
        .iconPic = gItemIcon_FriendBall,
        .iconPalette = gItemIconPalette_FriendBall,
    },

    [ITEM_LOVE_BALL] =
    {
        .name = ITEM_NAME("LOVE BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "Works well on\n"
            "Pokémon of the\n"
            "opposite gender."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_LOVE,
        .iconPic = gItemIcon_LoveBall,
        .iconPalette = gItemIconPalette_LoveBall,
    },

    [ITEM_FAST_BALL] =
    {
        .name = ITEM_NAME("FAST BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "Works well on\n"
            "very fast\n"
            "Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_FAST,
        .iconPic = gItemIcon_FastBall,
        .iconPalette = gItemIconPalette_FastBall,
    },

    [ITEM_HEAVY_BALL] =
    {
        .name = ITEM_NAME("HEAVY BALL"),
        .price = (I_PRICE >= GEN_7) ? 0 : 300,
        .description = COMPOUND_STRING(
            "Works well on\n"
            "very heavy\n"
            "Pokémon."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_HEAVY,
        .iconPic = gItemIcon_HeavyBall,
        .iconPalette = gItemIconPalette_HeavyBall,
    },

    [ITEM_DREAM_BALL] =
    {
        .name = ITEM_NAME("DREAM BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
        #if B_DREAM_BALL_MODIFIER >= GEN_8
            "A Ball that works\n"
            "well on sleeping\n"
            "Pokémon."),
        #else
            "A Poké Ball used in\n"
            "the Entree Forest."),
        #endif
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_DREAM,
        .iconPic = gItemIcon_DreamBall,
        .iconPalette = gItemIconPalette_DreamBall,
    },

    [ITEM_SAFARI_BALL] =
    {
        .name = ITEM_NAME("SAFARI BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A special Ball that\n"
            "is used only in the\n"
            "Safari Zone."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_SAFARI,
        .iconPic = gItemIcon_SafariBall,
        .iconPalette = gItemIconPalette_SafariBall,
    },

    [ITEM_SPORT_BALL] =
    {
        .name = ITEM_NAME("SPORT BALL"),
        .price = (I_PRICE <= GEN_3 || I_PRICE >= GEN_9) ? 0 : 300,
        .description = COMPOUND_STRING(
            "A special Ball\n"
            "used in the Bug-\n"
            "Catching Contest."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_SPORT,
        .iconPic = gItemIcon_SportBall,
        .iconPalette = gItemIconPalette_SportBall,
    },

    [ITEM_PARK_BALL] =
    {
        .name = ITEM_NAME("PARK BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A special Ball for\n"
            "the Pal Park."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_PARK,
        .iconPic = gItemIcon_ParkBall,
        .iconPalette = gItemIconPalette_ParkBall,
    },

    [ITEM_BEAST_BALL] =
    {
        .name = ITEM_NAME("BEAST BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A Ball designed to\n"
            "catch Ultra Beasts."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_BEAST,
        .iconPic = gItemIcon_BeastBall,
        .iconPalette = gItemIconPalette_BeastBall,
    },

    [ITEM_CHERISH_BALL] =
    {
        .name = ITEM_NAME("CHERISH BALL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A rare Ball made\n"
            "in commemoration\n"
            "of some event."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .battleUsage = EFFECT_ITEM_THROW_BALL,
        .secondaryId = BALL_CHERISH,
        .iconPic = gItemIcon_CherishBall,
        .iconPalette = gItemIconPalette_CherishBall,
    },

// Medicine

    [ITEM_POTION] =
    {
        .name = ITEM_NAME("POTION"),
        .price = (I_PRICE >= GEN_7) ? 200 : 300,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
            "20 points."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Potion,
        .flingPower = 30,
        .iconPic = gItemIcon_Potion,
        .iconPalette = gItemIconPalette_Potion,
    },

    [ITEM_SUPER_POTION] =
    {
        .name = ITEM_NAME("SUPER POTION"),
        .price = 700,
        .holdEffectParam = 60,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "60 points."),
        #else
            "50 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SuperPotion,
        .flingPower = 30,
        .iconPic = gItemIcon_Potion,
        .iconPalette = gItemIconPalette_SuperPotion,
    },

    [ITEM_HYPER_POTION] =
    {
        .name = ITEM_NAME("HYPER POTION"),
        .price = (I_PRICE >= GEN_2 && I_PRICE <= GEN_6) ? 1200 : 1500,
        .holdEffectParam = 120,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "120 points."),
        #else
            "200 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_HyperPotion,
        .flingPower = 30,
        .iconPic = gItemIcon_Potion,
        .iconPalette = gItemIconPalette_HyperPotion,
    },

    [ITEM_MAX_POTION] =
    {
        .name = ITEM_NAME("MAX POTION"),
        .price = 2500,
        .holdEffectParam = 255,
        .description = COMPOUND_STRING(
            "Fully restores the\n"
            "HP of a Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_MaxPotion,
        .flingPower = 30,
        .iconPic = gItemIcon_LargePotion,
        .iconPalette = gItemIconPalette_MaxPotion,
    },

    [ITEM_FULL_RESTORE] =
    {
        .name = ITEM_NAME("FULL RESTORE"),
        .price = 3000,
        .holdEffectParam = 255,
        .description = COMPOUND_STRING(
            "Fully restores the\n"
            "HP and status of a\n"
            "Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_HEAL_AND_CURE_STATUS,
        .effect = gItemEffect_FullRestore,
        .flingPower = 30,
        .iconPic = gItemIcon_LargePotion,
        .iconPalette = gItemIconPalette_FullRestore,
    },

    [ITEM_REVIVE] =
    {
        .name = ITEM_NAME("REVIVE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 1500,
        .description = COMPOUND_STRING(
            "Revives a fainted\n"
            "Pokémon with half\n"
            "its HP."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_Revive,
        .flingPower = 30,
        .iconPic = gItemIcon_Revive,
        .iconPalette = gItemIconPalette_Revive,
    },

    [ITEM_MAX_REVIVE] =
    {
        .name = ITEM_NAME("MAX REVIVE"),
        .price = 4000,
        .description = sMaxReviveDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_MaxRevive,
        .flingPower = 30,
        .iconPic = gItemIcon_MaxRevive,
        .iconPalette = gItemIconPalette_Revive,
    },

    [ITEM_FRESH_WATER] =
    {
        .name = ITEM_NAME("FRESH WATER"),
        .price = 200,
        .holdEffectParam = 30,
        .description = COMPOUND_STRING(
            "A mineral water\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 30 points."),
        #else
            "by 50 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_FreshWater,
        .flingPower = 30,
        .iconPic = gItemIcon_FreshWater,
        .iconPalette = gItemIconPalette_FreshWater,
    },

    [ITEM_SODA_POP] =
    {
        .name = ITEM_NAME("SODA POP"),
        .price = 300,
        .holdEffectParam = 50,
        .description = COMPOUND_STRING(
            "A fizzy soda drink\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 50 points."),
        #else
            "by 60 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SodaPop,
        .flingPower = 30,
        .iconPic = gItemIcon_SodaPop,
        .iconPalette = gItemIconPalette_SodaPop,
    },

    [ITEM_LEMONADE] =
    {
        .name = ITEM_NAME("LEMONADE"),
        .price = (I_PRICE >= GEN_7) ? 400 : 350,
        .holdEffectParam = 70,
        .description = COMPOUND_STRING(
            "A very sweet drink\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 70 points."),
        #else
            "by 80 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Lemonade,
        .flingPower = 30,
        .iconPic = gItemIcon_Lemonade,
        .iconPalette = gItemIconPalette_Lemonade,
    },

    [ITEM_MOOMOO_MILK] =
    {
        .name = ITEM_NAME("MOOMOO MILK"),
        .price = (I_PRICE >= GEN_7) ? 600 : 500,
        .holdEffectParam = 100,
        .description = COMPOUND_STRING(
            "A nutritious milk\n"
            "that restores HP\n"
            "by 100 points."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_MoomooMilk,
        .flingPower = 30,
        .iconPic = gItemIcon_MoomooMilk,
        .iconPalette = gItemIconPalette_MoomooMilk,
    },

    [ITEM_ENERGY_POWDER] =
    {
        .name = ITEM_NAME("ENERGY POWDER"),
        .price = 500,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 60 points."),
        #else
            "by 50 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_EnergyPowder,
        .flingPower = 30,
        .iconPic = gItemIcon_Powder,
        .iconPalette = gItemIconPalette_EnergyPowder,
    },

    [ITEM_ENERGY_ROOT] =
    {
        .name = ITEM_NAME("ENERGY ROOT"),
        .price = (I_PRICE >= GEN_7) ? 1200 : 800,
        .description = COMPOUND_STRING(
            "A bitter root\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 120 points."),
        #else
            "by 200 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_EnergyRoot,
        .flingPower = 30,
        .iconPic = gItemIcon_EnergyRoot,
        .iconPalette = gItemIconPalette_EnergyRoot,
    },

    [ITEM_HEAL_POWDER] =
    {
        .name = ITEM_NAME("HEAL POWDER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 450,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that heals all\n"
            "status problems."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_HealPowder,
        .flingPower = 30,
        .iconPic = gItemIcon_Powder,
        .iconPalette = gItemIconPalette_HealPowder,
    },

    [ITEM_REVIVAL_HERB] =
    {
        .name = ITEM_NAME("REVIVAL HERB"),
        .price = 2800,
        .description = COMPOUND_STRING(
            "A very bitter herb\n"
            "that revives a\n"
            "fainted Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_RevivalHerb,
        .flingPower = 30,
        .iconPic = gItemIcon_RevivalHerb,
        .iconPalette = gItemIconPalette_RevivalHerb,
    },

    [ITEM_ANTIDOTE] =
    {
        .name = ITEM_NAME("ANTIDOTE"),
        .price = (I_PRICE >= GEN_7) ? 200 : 100,
        .description = COMPOUND_STRING(
            "Heals a poisoned\n"
            "Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Antidote,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_Antidote,
    },

    [ITEM_PARALYZE_HEAL] =
    {
        .name = ITEM_NAME("PARALYZE HEAL"),
        .price = (I_PRICE == GEN_7) ? 300 : 200,
        .description = COMPOUND_STRING(
            "Heals a paralyzed\n"
            "Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_ParalyzeHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_ParalyzeHeal,
    },

    [ITEM_BURN_HEAL] =
    {
        .name = ITEM_NAME("BURN HEAL"),
    #if I_PRICE >= GEN_8
        .price = 200,
    #elif I_PRICE == GEN_7
        .price = 300,
    #else
        .price = 250,
    #endif
        .description = COMPOUND_STRING(
            "Heals Pokémon\n"
            "of a burn."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_BurnHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_BurnHeal,
    },

    [ITEM_ICE_HEAL] =
    {
        .name = ITEM_NAME("ICE HEAL"),
    #if I_PRICE >= GEN_8
        .price = 200,
    #elif I_PRICE == GEN_7
        .price = 100,
    #else
        .price = 250,
    #endif
        .description = COMPOUND_STRING(
            "Defrosts a frozen\n"
            "Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_IceHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_IceHeal,
    },

    [ITEM_AWAKENING] =
    {
        .name = ITEM_NAME("AWAKENING"),
    #if (I_PRICE >= GEN_8 || I_PRICE == GEN_1)
        .price = 200,
    #elif I_PRICE == GEN_7
        .price = 100,
    #else
        .price = 250,
    #endif
        .description = COMPOUND_STRING(
            "Awakens a sleeping\n"
            "Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Awakening,
        .flingPower = 30,
        .iconPic = gItemIcon_StatusHeal,
        .iconPalette = gItemIconPalette_Awakening,
    },

    [ITEM_FULL_HEAL] =
    {
        .name = ITEM_NAME("FULL HEAL"),
        .price = (I_PRICE >= GEN_7) ? 400 : 600,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_FullHeal,
        .iconPalette = gItemIconPalette_FullHeal,
    },

    [ITEM_ETHER] =
    {
        .name = ITEM_NAME("ETHER"),
        .price = (I_PRICE >= GEN_2) ? 1200 : 1,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "Restores the PP\n"
            "of a selected move\n"
            "by 10."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU_MOVES,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_Ether,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_Ether,
    },

    [ITEM_MAX_ETHER] =
    {
        .name = ITEM_NAME("MAX ETHER"),
        .price = (I_PRICE >= GEN_2) ? 2000 : 1,
        .holdEffectParam = 255,
        .description = COMPOUND_STRING(
            "Fully restores the\n"
            "PP of a selected\n"
            "move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU_MOVES,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_MaxEther,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_MaxEther,
    },

    [ITEM_ELIXIR] =
    {
        .name = ITEM_NAME("ELIXIR"),
        .price = (I_PRICE >= GEN_2) ? 3000 : 1,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "Restores the PP\n"
            "of all moves by 10."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_Elixir,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_Elixir,
    },

    [ITEM_MAX_ELIXIR] =
    {
        .name = ITEM_NAME("MAX ELIXIR"),
        .price = (I_PRICE >= GEN_2) ? 4500 : 1,
        .holdEffectParam = 255,
        .description = COMPOUND_STRING(
            "Fully restores the\n"
            "PP of a Pokémon's\n"
            "moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PP_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_MaxElixir,
        .flingPower = 30,
        .iconPic = gItemIcon_Ether,
        .iconPalette = gItemIconPalette_MaxElixir,
    },

    [ITEM_BERRY_JUICE] =
    {
        .name = ITEM_NAME("BERRY JUICE"),
        .price = 100,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A 100% pure juice\n"
            "that restores HP\n"
            "by 20 points."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Potion,
        .flingPower = 30,
        .iconPic = gItemIcon_BerryJuice,
        .iconPalette = gItemIconPalette_BerryJuice,
    },

    [ITEM_SACRED_ASH] =
    {
        .name = ITEM_NAME("SACRED ASH"),
        .pluralName = ITEM_PLURAL_NAME("Sacred Ashes"),
        .price = (I_PRICE >= GEN_7) ? 50000 : 200,
        .description = COMPOUND_STRING(
            "Fully revives and\n"
            "restores all\n"
            "fainted Pokémon."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_SacredAsh,
        .effect = gItemEffect_SacredAsh,
        .flingPower = 30,
        .iconPic = gItemIcon_DittoPowder,
        .iconPalette = gItemIconPalette_SacredAsh,
    },

    [ITEM_SWEET_HEART] =
    {
        .name = ITEM_NAME("SWEET HEART"),
        .price = (I_PRICE >= GEN_7) ? 3000 : 100,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A sweet chocolate\n"
            "that restores HP\n"
            "by 20 points."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Potion,
        .flingPower = 30,
        .iconPic = gItemIcon_SweetHeart,
        .iconPalette = gItemIconPalette_SweetHeart,
    },

    [ITEM_MAX_HONEY] =
    {
        .name = ITEM_NAME("MAX HONEY"),
        .pluralName = ITEM_PLURAL_NAME("Max Honey"),
        .price = 8000,
        .description = sMaxReviveDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_REVIVE,
        .effect = gItemEffect_MaxRevive,
        .flingPower = 30,
        .iconPic = gItemIcon_MaxHoney,
        .iconPalette = gItemIconPalette_MaxHoney,
    },

// Regional Specialties

    [ITEM_PEWTER_CRUNCHIES] =
    {
        .name = ITEM_NAME("PEWTER CRUNCHIES"),
        .pluralName = ITEM_PLURAL_NAME("Pewter Crunchies"),
        .price = 250,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_PewterCrunchies,
        .iconPalette = gItemIconPalette_PewterCrunchies,
    },

    [ITEM_RAGE_CANDY_BAR] =
    {
        .name = ITEM_NAME("RAGE CANDY BAR"),
        .price = (I_PRICE >= GEN_7) ? 350 : 300,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_RageCandyBar,
        .iconPalette = gItemIconPalette_RageCandyBar,
    },

    [ITEM_LAVA_COOKIE] =
    {
        .name = ITEM_NAME("LAVA COOKIE"),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = COMPOUND_STRING(
            "A local specialty\n"
            "that heals all\n"
            "status problems."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_LavaCookie,
        .iconPalette = gItemIconPalette_LavaCookieAndLetter,
    },

    [ITEM_OLD_GATEAU] =
    {
        .name = ITEM_NAME("OLD GATEAU"),
        .pluralName = ITEM_PLURAL_NAME("Old Gateaux"),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_OldGateau,
        .iconPalette = gItemIconPalette_OldGateau,
    },

    [ITEM_CASTELIACONE] =
    {
        .name = ITEM_NAME("CASTELIACONE"),
        .price = (I_PRICE >= GEN_7) ? 350 : 100,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_Casteliacone,
        .iconPalette = gItemIconPalette_Casteliacone,
    },

    [ITEM_LUMIOSE_GALETTE] =
    {
        .name = ITEM_NAME("LUMIOSE GALETTE"),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_LumioseGalette,
        .iconPalette = gItemIconPalette_LumioseGalette,
    },

    [ITEM_SHALOUR_SABLE] =
    {
        .name = ITEM_NAME("SHALOUR SABLE"),
        .price = (I_PRICE >= GEN_7) ? 350 : 200,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_ShalourSable,
        .iconPalette = gItemIconPalette_ShalourSable,
    },

    [ITEM_BIG_MALASADA] =
    {
        .name = ITEM_NAME("BIG MALASADA"),
        .price = 350,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_BigMalasada,
        .iconPalette = gItemIconPalette_BigMalasada,
    },

// Vitamins

    [ITEM_HP_UP] =
    {
        .name = ITEM_NAME("HP UP"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the base HP\n"
            "of one Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_HPUp,
        .flingPower = 30,
        .iconPic = gItemIcon_HPUp,
        .iconPalette = gItemIconPalette_HPUp,
    },

    [ITEM_PROTEIN] =
    {
        .name = ITEM_NAME("PROTEIN"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the base\n"
            "Attack stat of one\n"
            "Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Protein,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Protein,
    },

    [ITEM_IRON] =
    {
        .name = ITEM_NAME("IRON"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the base\n"
            "Defense stat of\n"
            "one Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Iron,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Iron,
    },

    [ITEM_CALCIUM] =
    {
        .name = ITEM_NAME("CALCIUM"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the base\n"
            "Sp. Atk stat of one\n"
            "Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Calcium,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Calcium,
    },

    [ITEM_ZINC] =
    {
        .name = ITEM_NAME("ZINC"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the base\n"
            "Sp. Def stat of one\n"
            "Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Zinc,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Zinc,
    },

    [ITEM_CARBOS] =
    {
        .name = ITEM_NAME("CARBOS"),
        .pluralName = ITEM_PLURAL_NAME("Carbos"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the base\n"
            "Speed stat of one\n"
            "Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_Carbos,
        .flingPower = 30,
        .iconPic = gItemIcon_Vitamin,
        .iconPalette = gItemIconPalette_Carbos,
    },

    [ITEM_PP_UP] =
    {
        .name = ITEM_NAME("PP UP"),
    #if I_PRICE >= GEN_7
        .price = 10000,
    #elif I_PRICE >= GEN_2
        .price = 9800,
    #else
        .price = 1,
    #endif
        .description = COMPOUND_STRING(
            "Raises the maximum\n"
            "PP of a selected\n"
            "move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .effect = gItemEffect_PPUp,
        .flingPower = 30,
        .iconPic = gItemIcon_PPUp,
        .iconPalette = gItemIconPalette_PPUp,
    },

    [ITEM_PP_MAX] =
    {
        .name = ITEM_NAME("PP MAX"),
        .pluralName = ITEM_PLURAL_NAME("PP Maxes"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 9800,
        .description = COMPOUND_STRING(
            "Raises the PP of a\n"
            "move to its maximum\n"
            "points."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_DRINK,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PPUp,
        .effect = gItemEffect_PPMax,
        .flingPower = 30,
        .iconPic = gItemIcon_PPMax,
        .iconPalette = gItemIconPalette_PPMax,
    },

// EV Feathers

    [ITEM_HEALTH_FEATHER] =
    {
        .name = ITEM_NAME("HEALTH FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = sHealthFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_HpFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_HealthFeather,
    },

    [ITEM_MUSCLE_FEATHER] =
    {
        .name = ITEM_NAME("MUSCLE FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = sMuscleFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_AtkFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_MuscleFeather,
    },

    [ITEM_RESIST_FEATHER] =
    {
        .name = ITEM_NAME("RESIST FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = sResistFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_DefFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_ResistFeather,
    },

    [ITEM_GENIUS_FEATHER] =
    {
        .name = ITEM_NAME("GENIUS FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = sGeniusFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpatkFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_GeniusFeather,
    },

    [ITEM_CLEVER_FEATHER] =
    {
        .name = ITEM_NAME("CLEVER FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = sCleverFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpdefFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_CleverFeather,
    },

    [ITEM_SWIFT_FEATHER] =
    {
        .name = ITEM_NAME("SWIFT FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 300 : 3000,
        .description = sSwiftFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_FEATHER,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpeedFeather,
        .flingPower = 20,
        .iconPic = gItemIcon_EVFeather,
        .iconPalette = gItemIconPalette_SwiftFeather,
    },

// Ability Modifiers

    [ITEM_ABILITY_CAPSULE] =
    {
        .name = ITEM_NAME("ABILITY CAPSULE"),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 10000,
    #else
        .price = 1000,
    #endif
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Switches a Poké-\n"
            "mon's ability."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_AbilityCapsule,
        .iconPic = gItemIcon_AbilityCapsule,
        .iconPalette = gItemIconPalette_AbilityCapsule,
    },

    [ITEM_ABILITY_PATCH] =
    {
        .name = ITEM_NAME("ABILITY PATCH"),
        .pluralName = ITEM_PLURAL_NAME("Ability Patches"),
        .price = (I_PRICE >= GEN_9) ? 250000 : 20,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Turns the ability\n"
            "of a Pokémon into\n"
            "a rare ability."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_AbilityPatch,
        .iconPic = gItemIcon_AbilityPatch,
        .iconPalette = gItemIconPalette_AbilityPatch,
    },

// Mints

    [ITEM_LONELY_MINT] =
    {
        .name = ITEM_NAME("LONELY MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Attack, but\n"
            "reduces Defense."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_LONELY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_ADAMANT_MINT] =
    {
        .name = ITEM_NAME("ADAMANT MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Attack, but\n"
            "reduces Sp. Atk."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_ADAMANT,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_NAUGHTY_MINT] =
    {
        .name = ITEM_NAME("NAUGHTY MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Attack, but\n"
            "reduces Sp. Def."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_NAUGHTY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_BRAVE_MINT] =
    {
        .name = ITEM_NAME("BRAVE MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Attack, but\n"
            "reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_BRAVE,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_RedMint,
    },

    [ITEM_BOLD_MINT] =
    {
        .name = ITEM_NAME("BOLD MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Defense, but\n"
            "reduces Attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_BOLD,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_IMPISH_MINT] =
    {
        .name = ITEM_NAME("IMPISH MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Defense, but\n"
            "reduces Sp. Atk."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_IMPISH,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_LAX_MINT] =
    {
        .name = ITEM_NAME("LAX MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Defense, but\n"
            "reduces Sp. Def."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_LAX,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_RELAXED_MINT] =
    {
        .name = ITEM_NAME("RELAXED MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Defense, but\n"
            "reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_RELAXED,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_BlueMint,
    },

    [ITEM_MODEST_MINT] =
    {
        .name = ITEM_NAME("MODEST MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Atk, but\n"
            "reduces Attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_MODEST,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_MILD_MINT] =
    {
        .name = ITEM_NAME("MILD MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Atk, but\n"
            "reduces Defense."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_MILD,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_RASH_MINT] =
    {
        .name = ITEM_NAME("RASH MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Atk, but\n"
            "reduces Sp. Def."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_RASH,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_QUIET_MINT] =
    {
        .name = ITEM_NAME("QUIET MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Atk, but\n"
            "reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_QUIET,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_LightBlueMint,
    },

    [ITEM_CALM_MINT] =
    {
        .name = ITEM_NAME("CALM MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Def, but\n"
            "reduces Attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_CALM,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_GENTLE_MINT] =
    {
        .name = ITEM_NAME("GENTLE MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Def, but\n"
            "reduces Defense."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_GENTLE,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_CAREFUL_MINT] =
    {
        .name = ITEM_NAME("CAREFUL MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Def, but\n"
            "reduces Sp. Atk."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_CAREFUL,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_SASSY_MINT] =
    {
        .name = ITEM_NAME("SASSY MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Sp. Def, but\n"
            "reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_SASSY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_PinkMint,
    },

    [ITEM_TIMID_MINT] =
    {
        .name = ITEM_NAME("TIMID MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Speed, but\n"
            "reduces Attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_TIMID,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_HASTY_MINT] =
    {
        .name = ITEM_NAME("HASTY MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Speed, but\n"
            "reduces Defense."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_HASTY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_JOLLY_MINT] =
    {
        .name = ITEM_NAME("JOLLY MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Speed, but\n"
            "reduces Sp. Atk."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_JOLLY,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_NAIVE_MINT] =
    {
        .name = ITEM_NAME("NAIVE MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "ups Speed, but\n"
            "reduces Sp. Def."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_NAIVE,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_GreenMint,
    },

    [ITEM_SERIOUS_MINT] =
    {
        .name = ITEM_NAME("SERIOUS MINT"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 20,
        .description = COMPOUND_STRING(
            "Can be smelled. It\n"
            "makes each stat\n"
            "grow equally."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NATURE_MINT,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Mint,
        .secondaryId = NATURE_SERIOUS,
        .flingPower = 10,
        .iconPic = gItemIcon_Mint,
        .iconPalette = gItemIconPalette_YellowMint,
    },

// Candy

    [ITEM_RARE_CANDY] =
    {
        .name = ITEM_NAME("RARE CANDY"),
        .pluralName = ITEM_PLURAL_NAME("Rare Candies"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 4800,
        .description = COMPOUND_STRING(
            "Raises the level\n"
            "of a Pokémon by\n"
            "one."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_RareCandy,
        .iconPalette = gItemIconPalette_RareCandy,
    },

    [ITEM_EXP_CANDY_XS] =
    {
        .name = ITEM_NAME("EXP. CANDY XS"),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies XS"),
        .price = 20,
        .holdEffectParam = EXP_100,
        .description = COMPOUND_STRING(
            "Gives a very small\n"
            "amount of Exp. to\n"
            "a single Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyXS,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_S] =
    {
        .name = ITEM_NAME("EXP. CANDY S"),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies S"),
        .price = 240,
        .holdEffectParam = EXP_800,
        .description = COMPOUND_STRING(
            "Gives a small\n"
            "amount of Exp. to\n"
            "a single Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyS,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_M] =
    {
        .name = ITEM_NAME("EXP. CANDY M"),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies M"),
        .price = 1000,
        .holdEffectParam = EXP_3000,
        .description = COMPOUND_STRING(
            "Gives a moderate\n"
            "amount of Exp. to\n"
            "a single Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyM,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_L] =
    {
        .name = ITEM_NAME("EXP. CANDY L"),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies L"),
        .price = 3000,
        .holdEffectParam = EXP_10000,
        .description = COMPOUND_STRING(
            "Gives a large\n"
            "amount of Exp. to\n"
            "a single Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyL,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_EXP_CANDY_XL] =
    {
        .name = ITEM_NAME("EXP. CANDY XL"),
        .pluralName = ITEM_PLURAL_NAME("Exp. Candies XL"),
        .price = 10000,
        .holdEffectParam = EXP_30000,
        .description = COMPOUND_STRING(
            "Gives a very large\n"
            "amount of Exp. to\n"
            "a single Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RareCandy,
        .effect = gItemEffect_RareCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpCandyXL,
        .iconPalette = gItemIconPalette_ExpCandies,
    },

    [ITEM_DYNAMAX_CANDY] =
    {
        .name = ITEM_NAME("DYNAMAX CANDY"),
        .pluralName = ITEM_PLURAL_NAME("Dynamax Candies"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Raises the Dynamax\n"
            "Level of a single\n"
            "Pokémon by one."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_LEVEL_UP_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_DynamaxCandy,
        .flingPower = 30,
        .iconPic = gItemIcon_DynamaxCandy,
        .iconPalette = gItemIconPalette_DynamaxCandy,
    },

// Medicinal Flutes

    [ITEM_BLUE_FLUTE] =
    {
        .name = ITEM_NAME("BLUE FLUTE"),
        .price = (I_PRICE >= GEN_7) ? 20 : 100,
        .description = COMPOUND_STRING(
            "A glass flute that\n"
            "awakens sleeping\n"
            "Pokémon."),
        .notConsumed = TRUE,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Awakening,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_BlueFlute,
    },

    [ITEM_YELLOW_FLUTE] =
    {
        .name = ITEM_NAME("YELLOW FLUTE"),
        .price = (I_PRICE >= GEN_7) ? 20 : 300,
        .description = COMPOUND_STRING(
            "A glass flute that\n"
            "snaps Pokémon\n"
            "out of confusion."),
        .notConsumed = TRUE,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_YellowFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_YellowFlute,
    },

    [ITEM_RED_FLUTE] =
    {
        .name = ITEM_NAME("RED FLUTE"),
        .price = (I_PRICE >= GEN_7) ? 20 : 200,
        .description = COMPOUND_STRING(
            "A glass flute that\n"
            "snaps Pokémon\n"
            "out of attraction."),
        .notConsumed = TRUE,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_RedFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_RedFlute,
    },

// Encounter-modifying Flutes

    [ITEM_BLACK_FLUTE] =
    {
        .name = ITEM_NAME("BLACK FLUTE"),
        .price = (I_PRICE >= GEN_7) ? 20 : 400,
        .holdEffectParam = 50,
        .description = COMPOUND_STRING(
            "A glass flute that\n"
            "keeps away wild\n"
            "Pokémon."),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_BlackFlute,
    },

    [ITEM_WHITE_FLUTE] =
    {
        .name = ITEM_NAME("WHITE FLUTE"),
        .price = (I_PRICE >= GEN_7) ? 20 : 500,
        .holdEffectParam = 150,
        .description = COMPOUND_STRING(
            "A glass flute that\n"
            "lures wild Pokémon."),
        .notConsumed = TRUE,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FLUTE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_BlackWhiteFlute,
        .flingPower = 30,
        .iconPic = gItemIcon_Flute,
        .iconPalette = gItemIconPalette_WhiteFlute,
    },

// Encounter Modifiers

    [ITEM_REPEL] =
    {
        .name = ITEM_NAME("REPEL"),
        .price = (I_PRICE >= GEN_7) ? 400 : 350,
        .holdEffectParam = 100,
        .description = COMPOUND_STRING(
            "Repels weak wild\n"
            "Pokémon for 100\n"
            "steps."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
        .iconPic = gItemIcon_Repel,
        .iconPalette = gItemIconPalette_Repel,
    },

    [ITEM_SUPER_REPEL] =
    {
        .name = ITEM_NAME("SUPER REPEL"),
        .price = (I_PRICE >= GEN_7) ? 700 : 500,
        .holdEffectParam = 200,
        .description = COMPOUND_STRING(
            "Repels weak wild\n"
            "Pokémon for 200\n"
            "steps."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
        .iconPic = gItemIcon_Repel,
        .iconPalette = gItemIconPalette_SuperRepel,
    },

    [ITEM_MAX_REPEL] =
    {
        .name = ITEM_NAME("MAX REPEL"),
        .price = (I_PRICE >= GEN_7) ? 900 : 700,
        .holdEffectParam = 250,
        .description = COMPOUND_STRING(
            "Repels weak wild\n"
            "Pokémon for 250\n"
            "steps."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Repel,
        .flingPower = 30,
        .iconPic = gItemIcon_Repel,
        .iconPalette = gItemIconPalette_MaxRepel,
    },

    [ITEM_LURE] =
    {
        .name = ITEM_NAME("LURE"),
        .price = 400,
        .holdEffectParam = 100,
        .description = COMPOUND_STRING(
            "Makes Pokémon more\n"
            "likely to appear\n"
            "for 100 steps."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Lure,
        .secondaryId = 0,
        .flingPower = 30,
        .iconPic = gItemIcon_Lure,
        .iconPalette = gItemIconPalette_Lure,
    },

    [ITEM_SUPER_LURE] =
    {
        .name = ITEM_NAME("SUPER LURE"),
        .price = 700,
        .holdEffectParam = 200,
        .description = COMPOUND_STRING(
            "Makes Pokémon more\n"
            "likely to appear\n"
            "for 200 steps."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Lure,
        .secondaryId = 0,
        .flingPower = 30,
        .iconPic = gItemIcon_Lure,
        .iconPalette = gItemIconPalette_SuperLure,
    },

    [ITEM_MAX_LURE] =
    {
        .name = ITEM_NAME("MAX LURE"),
        .price = 900,
        .holdEffectParam = 250,
        .description = COMPOUND_STRING(
            "Makes Pokémon more\n"
            "likely to appear\n"
            "for 250 steps."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Lure,
        .secondaryId = 0,
        .flingPower = 30,
        .iconPic = gItemIcon_Lure,
        .iconPalette = gItemIconPalette_MaxLure,
    },

    [ITEM_ESCAPE_ROPE] =
    {
        .name = ITEM_NAME("ESCAPE ROPE"),
        .description = COMPOUND_STRING(
            "Use to escape\n"
            "instantly from a\n"
            "cave or a dungeon."),
    #if I_KEY_ESCAPE_ROPE >= GEN_8
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #else
        .price = (I_PRICE >= GEN_7) ? 1000 : 550,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FIELD_USE,
    #endif
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_EscapeRope,
        .flingPower = 30,
        .iconPic = gItemIcon_EscapeRope,
        .iconPalette = gItemIconPalette_EscapeRope,
    },

// X Items

    [ITEM_X_ATTACK] =
    {
        .name = ITEM_NAME("X ATTACK"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 500,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises stat\n"
            "Attack during\n"
            "one battle."),
        #else
            "Raises the stat\n"
            "Attack during one\n"
            "battle."),
        #endif
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XAttack,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XAttack,
    },

    [ITEM_X_DEFENSE] =
    {
        .name = ITEM_NAME("X DEFENSE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 550,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises stat\n"
            "Defense during\n"
            "one battle."),
        #else
            "Raises the stat\n"
            "Defense during one\n"
            "battle."),
        #endif
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XDefense,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XDefend,
    },

    [ITEM_X_SP_ATK] =
    {
        .name = ITEM_NAME("X SP. ATK"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 350,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises stat\n"
            "Sp. Atk during\n"
            "one battle."),
        #else
            "Raises the stat\n"
            "Sp. Atk during one\n"
            "battle."),
        #endif
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XSpecialAttack,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XSpecial,
    },

    [ITEM_X_SP_DEF] =
    {
        .name = ITEM_NAME("X SP. DEF"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 350,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises stat\n"
            "Sp. Def during\n"
            "one battle."),
        #else
            "Raises the stat\n"
            "Sp. Def during one\n"
            "battle."),
        #endif
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XSpecialDefense,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XSpecialDefense,
    },

    [ITEM_X_SPEED] =
    {
        .name = ITEM_NAME("X SPEED"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 350,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises stat\n"
            "Speed during\n"
            "one battle."),
        #else
            "Raises the stat\n"
            "Speed during one\n"
            "battle."),
        #endif
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XSpeed,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XSpeed,
    },

    [ITEM_X_ACCURACY] =
    {
        .name = ITEM_NAME("X ACCURACY"),
        .pluralName = ITEM_PLURAL_NAME("X Accuracies"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 950,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises move\n"
            "accuracy during\n"
            "one battle."),
        #else
            "Raises accuracy\n"
            "of attack moves\n"
            "during one battle."),
        #endif
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_STAT,
        .effect = gItemEffect_XAccuracy,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_XAccuracy,
    },

    [ITEM_DIRE_HIT] =
    {
        .name = ITEM_NAME("DIRE HIT"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 650,
        .description = COMPOUND_STRING(
            "Raises the\n"
            "critical-hit ratio\n"
            "during one battle."),
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_SET_FOCUS_ENERGY,
        .effect = gItemEffect_DireHit,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_DireHit,
    },

    [ITEM_GUARD_SPEC] =
    {
        .name = ITEM_NAME("GUARD SPEC."),
        .pluralName = ITEM_PLURAL_NAME("Guard Specs."),
        .price = (I_PRICE >= GEN_7) ? 1500 : 700,
        .description = COMPOUND_STRING(
            "Prevents stat\n"
            "reduction when\n"
            "used in battle."),
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_X_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_SET_MIST,
        .effect = gItemEffect_GuardSpec,
        .flingPower = 30,
        .iconPic = gItemIcon_BattleStatItem,
        .iconPalette = gItemIconPalette_GuardSpec,
    },

    [ITEM_POKE_DOLL] =
    {
        .name = ITEM_NAME("POKé DOLL"),
    #if I_PRICE >= GEN_8
        .price = 300,
    #elif I_PRICE == GEN_7
        .price = 100,
    #else
        .price = 1000,
    #endif
        .description = sPokeDollDesc,
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_ESCAPE,
        .flingPower = 30,
        .iconPic = gItemIcon_PokeDoll,
        .iconPalette = gItemIconPalette_PokeDoll,
    },

    [ITEM_FLUFFY_TAIL] =
    {
        .name = ITEM_NAME("FLUFFY TAIL"),
        .price = (I_PRICE >= GEN_7) ? 100 : 1000,
        .description = sPokeDollDesc,
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_ESCAPE,
        .flingPower = 30,
        .iconPic = gItemIcon_FluffyTail,
        .iconPalette = gItemIconPalette_FluffyTail,
    },

    [ITEM_POKE_TOY] =
    {
        .name = ITEM_NAME("POKé TOY"),
        .price = (I_PRICE >= GEN_7) ? 100 : 1000,
        .description = sPokeDollDesc,
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_ESCAPE,
        .flingPower = 30,
        .iconPic = gItemIcon_PokeToy,
        .iconPalette = gItemIconPalette_PokeToy,
    },

    [ITEM_MAX_MUSHROOMS] =
    {
        .name = ITEM_NAME("MAX MUSHROOMS"),
        .pluralName = ITEM_PLURAL_NAME("Max Mushrooms"),
        .price = 8000,
        .description = COMPOUND_STRING(
            "Raises every stat\n"
            "during one battle\n"
            "by one stage."),
        .pocket = POCKET_BATTLE_ITEMS,
        .sortType = ITEM_TYPE_BATTLE_ITEM,
        .type = B_X_ITEMS_CROSSUSE ? ITEM_USE_BATTLER : ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_INCREASE_ALL_STATS,
        .flingPower = 30,
        .iconPic = gItemIcon_MaxMushrooms,
        .iconPalette = gItemIconPalette_MaxMushrooms,
    },

// Treasures

    [ITEM_BOTTLE_CAP] =
    {
        .name = ITEM_NAME("BOTTLE CAP"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 5000,
        .description = COMPOUND_STRING(
            "A beautiful bottle\n"
            "cap that gives off\n"
            "a silver gleam."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BottleCap,
        .iconPalette = gItemIconPalette_BottleCap,
    },

    [ITEM_GOLD_BOTTLE_CAP] =
    {
        .name = ITEM_NAME("GOLD BOTTLE CAP"),
        .price = (I_PRICE >= GEN_9) ? 60000 : 10000,
        .description = COMPOUND_STRING(
            "A beautiful bottle\n"
            "cap that gives off\n"
            "a golden gleam."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BottleCap,
        .iconPalette = gItemIconPalette_GoldBottleCap,
    },

    [ITEM_NUGGET] =
    {
        .name = ITEM_NAME("NUGGET"),
        .price = 10000 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A nugget of pure\n"
            "gold. Can be sold at\n"
            "a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Nugget,
        .iconPalette = gItemIconPalette_Nugget,
    },

    [ITEM_BIG_NUGGET] =
    {
        .name = ITEM_NAME("BIG NUGGET"),
    #if I_PRICE >= GEN_7
        .price = 40000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_6
        .price = 20000,
    #else
        .price = 0,
    #endif
        .description = COMPOUND_STRING(
            "A big nugget made\n"
            "of gold, sellable\n"
            "at a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = B_UPDATED_MOVE_DATA >= GEN_8 ? 130 : 80,
        .iconPic = gItemIcon_BigNugget,
        .iconPalette = gItemIconPalette_BigNugget,
    },

    [ITEM_TINY_MUSHROOM] =
    {
        .name = ITEM_NAME("TINY MUSHROOM"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A plain mushroom\n"
            "that would sell\n"
            "at a cheap price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_TinyMushroom,
        .iconPalette = gItemIconPalette_Mushroom,
    },

    [ITEM_BIG_MUSHROOM] =
    {
        .name = ITEM_NAME("BIG MUSHROOM"),
        .price = 5000 * TREASURE_FACTOR,
        .description = sBigMushroomDesc,
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BigMushroom,
        .iconPalette = gItemIconPalette_Mushroom,
    },

    [ITEM_BALM_MUSHROOM] =
    {
        .name = ITEM_NAME("BALM MUSHROOM"),
    #if I_PRICE >= GEN_7
        .price = 15000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_6
        .price = 12500,
    #else
        .price = 0,
    #endif
        .description = sBigMushroomDesc,
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BalmMushroom,
        .iconPalette = gItemIconPalette_BalmMushroom,
    },

    [ITEM_PEARL] =
    {
        .name = ITEM_NAME("PEARL"),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR: 1400,
        .description = COMPOUND_STRING(
            "A pretty pearl\n"
            "that would sell at a\n"
            "cheap price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Pearl,
        .iconPalette = gItemIconPalette_Pearl,
    },

    [ITEM_BIG_PEARL] =
    {
        .name = ITEM_NAME("BIG PEARL"),
        .price = (I_PRICE >= GEN_7) ? 8000 * TREASURE_FACTOR: 7500,
        .description = COMPOUND_STRING(
            "A lovely large pearl\n"
            "that would sell at a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BigPearl,
        .iconPalette = gItemIconPalette_Pearl,
    },

    [ITEM_PEARL_STRING] =
    {
        .name = ITEM_NAME("PEARL STRING"),
    #if I_PRICE >= GEN_8
        .price = 20000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_7
        .price = 30000,
    #elif I_PRICE == GEN_6
        .price = 15000,
    #else
        .price = 0,
    #endif
        .description = COMPOUND_STRING(
            "Very large pearls\n"
            "that would sell at a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_PearlString,
        .iconPalette = gItemIconPalette_PearlString,
    },

    [ITEM_STARDUST] =
    {
        .name = ITEM_NAME("STARDUST"),
        .price = (I_PRICE >= GEN_7) ? 3000 * TREASURE_FACTOR: 2000,
        .description = COMPOUND_STRING(
            "Beautiful red sand.\n"
            "Can be sold at a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Sand,
        .iconPalette = gItemIconPalette_Star,
    },

    [ITEM_STAR_PIECE] =
    {
        .name = ITEM_NAME("STAR PIECE"),
        .price = (I_PRICE >= GEN_7) ? 12000 * TREASURE_FACTOR: 9800,
        .description = COMPOUND_STRING(
            "A red gem shard.\n"
            "It would sell for a\n"
            "very high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_StarPiece,
        .iconPalette = gItemIconPalette_Star,
    },

    [ITEM_COMET_SHARD] =
    {
        .name = ITEM_NAME("COMET SHARD"),
    #if I_PRICE >= GEN_8
        .price = 25000 * TREASURE_FACTOR,
    #elif I_PRICE == GEN_7
        .price = 60000,
    #elif I_PRICE == GEN_6
        .price = 30000,
    #else
        .price = 0,
    #endif
        .description = COMPOUND_STRING(
            "A comet's shard.\n"
            "It would sell for a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_StarPiece,
        .iconPalette = gItemIconPalette_CometShard,
    },

    [ITEM_SHOAL_SALT] =
    {
        .name = ITEM_NAME("SHOAL SALT"),
        .price = 20,
        .description = COMPOUND_STRING(
            "Salt obtained from\n"
            "deep inside the\n"
            "Shoal Cave."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Powder,
        .iconPalette = gItemIconPalette_ShoalSalt,
    },

    [ITEM_SHOAL_SHELL] =
    {
        .name = ITEM_NAME("SHOAL SHELL"),
        .price = 20,
        .description = COMPOUND_STRING(
            "A seashell found\n"
            "deep inside the\n"
            "Shoal Cave."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ShoalShell,
        .iconPalette = gItemIconPalette_Shell,
    },

    [ITEM_RED_SHARD] =
    {
        .name = ITEM_NAME("RED SHARD"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = sShardsDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_RedShard,
    },

    [ITEM_BLUE_SHARD] =
    {
        .name = ITEM_NAME("BLUE SHARD"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = sShardsDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_BlueShard,
    },

    [ITEM_YELLOW_SHARD] =
    {
        .name = ITEM_NAME("YELLOW SHARD"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = sShardsDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_YellowShard,
    },

    [ITEM_GREEN_SHARD] =
    {
        .name = ITEM_NAME("GREEN SHARD"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .description = sShardsDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Shard,
        .iconPalette = gItemIconPalette_GreenShard,
    },

    [ITEM_HEART_SCALE] =
    {
        .name = ITEM_NAME("HEART SCALE"),
        .price = 100,
        .description = COMPOUND_STRING(
            "A lovely scale.\n"
            "It is coveted by\n"
            "collectors."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_HeartScale,
        .iconPalette = gItemIconPalette_HeartScale,
    },

    [ITEM_HONEY] =
    {
        .name = ITEM_NAME("HONEY"),
        .pluralName = ITEM_PLURAL_NAME("Honey"),
    #if I_PRICE >= GEN_8
        .price = 900,
    #elif I_PRICE == GEN_7
        .price = 300,
    #else
        .price = 100,
    #endif
        .description = COMPOUND_STRING(
            "Sweet honey that\n"
            "attracts wild\n"
            "Pokémon when used."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Honey,
        .flingPower = 30,
        .iconPic = gItemIcon_Honey,
        .iconPalette = gItemIconPalette_Honey,
    },

    [ITEM_RARE_BONE] =
    {
        .name = ITEM_NAME("RARE BONE"),
        .price = (I_PRICE >= GEN_7) ? 5000 * TREASURE_FACTOR: 10000,
        .description = COMPOUND_STRING(
            "A very rare bone.\n"
            "It can be sold at\n"
            "a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_Bone,
        .iconPalette = gItemIconPalette_Bone,
    },

    [ITEM_ODD_KEYSTONE] =
    {
        .name = ITEM_NAME("ODD KEYSTONE"),
        .price = 2100,
        .description = COMPOUND_STRING(
            "Voices can be heard\n"
            "from this odd stone\n"
            "occasionally."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_OddKeystone,
        .iconPalette = gItemIconPalette_OddKeystone,
    },

    [ITEM_PRETTY_FEATHER] =
    {
        .name = ITEM_NAME("PRETTY FEATHER"),
        .price = (I_PRICE >= GEN_7) ? 1000 * TREASURE_FACTOR: 200,
        .description = COMPOUND_STRING(
            "A beautiful yet\n"
            "plain feather that\n"
            "does nothing."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 20,
        .iconPic = gItemIcon_PrettyFeather,
        .iconPalette = gItemIconPalette_PrettyFeather,
    },

    [ITEM_RELIC_COPPER] =
    {
        .name = ITEM_NAME("RELIC COPPER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A copper coin used\n"
            "long ago. It sells\n"
            "at a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCoin,
        .iconPalette = gItemIconPalette_RelicCopper,
    },

    [ITEM_RELIC_SILVER] =
    {
        .name = ITEM_NAME("RELIC SILVER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A silver coin used\n"
            "long ago. It sells\n"
            "at a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCoin,
        .iconPalette = gItemIconPalette_RelicSilver,
    },

    [ITEM_RELIC_GOLD] =
    {
        .name = ITEM_NAME("RELIC GOLD"),
        .price = (I_PRICE >= GEN_6) ? 60000 : 0,
        .description = COMPOUND_STRING(
            "A gold coin used\n"
            "long ago. It sells\n"
            "at a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCoin,
        .iconPalette = gItemIconPalette_RelicGold,
    },

    [ITEM_RELIC_VASE] =
    {
        .name = ITEM_NAME("RELIC VASE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A vase made long\n"
            "ago. It sells at\n"
            "a high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicVase,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_RELIC_BAND] =
    {
        .name = ITEM_NAME("RELIC BAND"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An old bracelet.\n"
            "It sells at a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicBand,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_RELIC_STATUE] =
    {
        .name = ITEM_NAME("RELIC STATUE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An old statue.\n"
            "It sells at a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicStatue,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_RELIC_CROWN] =
    {
        .name = ITEM_NAME("RELIC CROWN"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An old crown.\n"
            "It sells at a\n"
            "high price."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_RelicCrown,
        .iconPalette = gItemIconPalette_Relics,
    },

    [ITEM_STRANGE_SOUVENIR] =
    {
        .name = ITEM_NAME("STRANGE SOUVENIR"),
        .price = (I_PRICE >= GEN_7) ? 3000 : 10,
        .description = COMPOUND_STRING(
            "An ornament that\n"
            "depicts a Pokémon\n"
            "from Alola."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_RELIC,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_StrangeSouvenir,
        .iconPalette = gItemIconPalette_StrangeSouvenir,
    },

// Fossils

    [ITEM_HELIX_FOSSIL] =
    {
        .name = ITEM_NAME("HELIX FOSSIL"),
        .description = COMPOUND_STRING(
            "A piece of an\n"
            "ancient marine\n"
            "Pokémon's seashell."),
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_HelixFossil,
        .iconPalette = gItemIconPalette_KantoFossil,
    },

    [ITEM_DOME_FOSSIL] =
    {
        .name = ITEM_NAME("DOME FOSSIL"),
        .description = COMPOUND_STRING(
            "A piece of an\n"
            "ancient marine\n"
            "Pokémon's shell."),
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_DomeFossil,
        .iconPalette = gItemIconPalette_KantoFossil,
    },

    [ITEM_OLD_AMBER] =
    {
        .name = ITEM_NAME("OLD AMBER"),
        .description = COMPOUND_STRING(
            "A stone containing\n"
            "the genes of an\n"
            "ancient Pokémon."),
    #if I_KEY_FOSSILS >= GEN_4
        .price = 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_OldAmber,
        .iconPalette = gItemIconPalette_OldAmber,
    },

    [ITEM_ROOT_FOSSIL] =
    {
        .name = ITEM_NAME("ROOT FOSSIL"),
        .description = sRootFossilDesc,
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_RootFossil,
        .iconPalette = gItemIconPalette_HoennFossil,
    },

    [ITEM_CLAW_FOSSIL] =
    {
        .name = ITEM_NAME("CLAW FOSSIL"),
        .description = sRootFossilDesc,
    #if I_KEY_FOSSILS >= GEN_4
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
    #else
        .price = 0,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
    #endif
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_ClawFossil,
        .iconPalette = gItemIconPalette_HoennFossil,
    },

    [ITEM_ARMOR_FOSSIL] =
    {
        .name = ITEM_NAME("ARMOR FOSSIL"),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = COMPOUND_STRING(
            "A piece of a\n"
            "prehistoric Poké-\n"
            "mon's head."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_ArmorFossil,
        .iconPalette = gItemIconPalette_ArmorFossil,
    },

    [ITEM_SKULL_FOSSIL] =
    {
        .name = ITEM_NAME("SKULL FOSSIL"),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = COMPOUND_STRING(
            "A piece of a\n"
            "prehistoric Poké-\n"
            "mon's collar."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_SkullFossil,
        .iconPalette = gItemIconPalette_SkullFossil,
    },

    [ITEM_COVER_FOSSIL] =
    {
        .name = ITEM_NAME("COVER FOSSIL"),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = COMPOUND_STRING(
            "A piece of a\n"
            "prehistoric Poké-\n"
            "mon's back."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_CoverFossil,
        .iconPalette = gItemIconPalette_CoverFossil,
    },

    [ITEM_PLUME_FOSSIL] =
    {
        .name = ITEM_NAME("PLUME FOSSIL"),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = COMPOUND_STRING(
            "A piece of a\n"
            "prehistoric Poké-\n"
            "mon's wing."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_PlumeFossil,
        .iconPalette = gItemIconPalette_PlumeFossil,
    },

    [ITEM_JAW_FOSSIL] =
    {
        .name = ITEM_NAME("JAW FOSSIL"),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = COMPOUND_STRING(
            "A piece of a\n"
            "prehistoric Poké-\n"
            "mon's large jaw."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_JawFossil,
        .iconPalette = gItemIconPalette_JawFossil,
    },

    [ITEM_SAIL_FOSSIL] =
    {
        .name = ITEM_NAME("SAIL FOSSIL"),
        .price = (I_PRICE >= GEN_7) ? 7000: 1000,
        .description = COMPOUND_STRING(
            "A piece of a\n"
            "prehistoric Poké-\n"
            "mon's skin sail."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_SailFossil,
        .iconPalette = gItemIconPalette_SailFossil,
    },

    [ITEM_FOSSILIZED_BIRD] =
    {
        .name = ITEM_NAME("FOSSILIZED BIRD"),
        .price = 5000,
        .description = COMPOUND_STRING(
            "A fossil of an\n"
            "ancient, sky-\n"
            "soaring Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedBird,
        .iconPalette = gItemIconPalette_FossilizedBird,
    },

    [ITEM_FOSSILIZED_FISH] =
    {
        .name = ITEM_NAME("FOSSILIZED FISH"),
        .pluralName = ITEM_PLURAL_NAME("Fossilized Fish"),
        .price = 5000,
        .description = sFossilizedFishDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedFish,
        .iconPalette = gItemIconPalette_FossilizedFish,
    },

    [ITEM_FOSSILIZED_DRAKE] =
    {
        .name = ITEM_NAME("FOSSILIZED DRAKE"),
        .price = 5000,
        .description = COMPOUND_STRING(
            "A fossil of an\n"
            "ancient, land-\n"
            "roaming Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedDrake,
        .iconPalette = gItemIconPalette_FossilizedDrake,
    },

    [ITEM_FOSSILIZED_DINO] =
    {
        .name = ITEM_NAME("FOSSILIZED DINO"),
        .price = 5000,
        .description = sFossilizedFishDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_FOSSIL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_FossilizedDino,
        .iconPalette = gItemIconPalette_FossilizedDino,
    },

// Mulch

    [ITEM_GROWTH_MULCH] =
    {
        .name = ITEM_NAME("GROWTH MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Growth Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "accelerates the\n"
            "growth of Berries."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_GROWTH_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_GrowthMulch,
    },

    [ITEM_DAMP_MULCH] =
    {
        .name = ITEM_NAME("DAMP MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Damp Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "decelerates the\n"
            "growth of Berries."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_DAMP_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_DampMulch,
    },

    [ITEM_STABLE_MULCH] =
    {
        .name = ITEM_NAME("STABLE MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Stable Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "ups the life time\n"
            "of Berry trees."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_STABLE_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_StableMulch,
        .iconPalette = gItemIconPalette_StableMulch,
    },

    [ITEM_GOOEY_MULCH] =
    {
        .name = ITEM_NAME("GOOEY MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Gooey Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "makes more Berries\n"
            "regrow after fall."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_GOOEY_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_GooeyMulch,
    },

    [ITEM_RICH_MULCH] =
    {
        .name = ITEM_NAME("RICH MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Rich Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "ups the number of\n"
            "Berries harvested."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_RICH_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_RichMulch,
    },

    [ITEM_SURPRISE_MULCH] =
    {
        .name = ITEM_NAME("SURPRISE MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Surprise Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "ups the chance of\n"
            "Berry mutations."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_SURPRISE_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_SurpriseMulch,
    },

    [ITEM_BOOST_MULCH] =
    {
        .name = ITEM_NAME("BOOST MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Boost Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "ups the dry speed\n"
            "of soft soil."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_BOOST_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_BoostMulch,
    },

    [ITEM_AMAZE_MULCH] =
    {
        .name = ITEM_NAME("AMAZE MULCH"),
        .pluralName = ITEM_PLURAL_NAME("Amaze Mulch"),
        .price = 200,
    #if OW_BERRY_MULCH_USAGE == TRUE
        .description = COMPOUND_STRING(
            "A fertilizer Rich\n"
            "Surprising and\n"
            "Boosting as well."),
    #else
        .description = sGenericMulchDesc,
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = ITEM_TO_MULCH(ITEM_AMAZE_MULCH),
        .flingPower = 30,
        .iconPic = gItemIcon_Mulch,
        .iconPalette = gItemIconPalette_AmazeMulch,
    },

// Apricorns
    #if (I_PRICE >= GEN_8 || I_PRICE <= GEN_2)
        #define APRICORN_PRICE 200
    #elif I_PRICE >= GEN_5
        #define APRICORN_PRICE 20
    #else
        #define APRICORN_PRICE 0
    #endif

    [ITEM_RED_APRICORN] =
    {
        .name = ITEM_NAME("RED APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A red apricorn.\n"
            "It assails your\n"
            "nostrils."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_RedApricorn,
    },

    [ITEM_BLUE_APRICORN] =
    {
        .name = ITEM_NAME("BLUE APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A blue apricorn.\n"
            "It smells a bit\n"
            "like grass."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_BlueApricorn,
    },

    [ITEM_YELLOW_APRICORN] =
    {
        .name = ITEM_NAME("YELLOW APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A yellow apricorn.\n"
            "It has an invigor-\n"
            "ating scent."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_YellowApricorn,
    },

    [ITEM_GREEN_APRICORN] =
    {
        .name = ITEM_NAME("GREEN APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A green apricorn.\n"
            "It has a strange,\n"
            "aromatic scent."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_GreenApricorn,
    },

    [ITEM_PINK_APRICORN] =
    {
        .name = ITEM_NAME("PINK APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A pink apricorn.\n"
            "It has a nice,\n"
            "sweet scent."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_PinkApricorn,
    },

    [ITEM_WHITE_APRICORN] =
    {
        .name = ITEM_NAME("WHITE APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A white apricorn.\n"
            "It doesn't smell\n"
            "like anything."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_WhiteApricorn,
    },

    [ITEM_BLACK_APRICORN] =
    {
        .name = ITEM_NAME("BLACK APRICORN"),
        .price = APRICORN_PRICE,
        .description = COMPOUND_STRING(
            "A black apricorn.\n"
            "It has an inde-\n"
            "scribable scent."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GROWTH,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Apricorn,
        .iconPalette = gItemIconPalette_BlackApricorn,
    },

    [ITEM_WISHING_PIECE] =
    {
        .name = ITEM_NAME("WISHING PIECE"),
        .price = 20,
        .description = COMPOUND_STRING(
            "Throw into a\n"
            "{PKMN} Den to attract\n"
            "Dynamax Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .flingPower = 50,
        .iconPic = gItemIcon_WishingPiece,
        .iconPalette = gItemIconPalette_WishingPiece,
    },

    [ITEM_GALARICA_TWIG] =
    {
        .name = ITEM_NAME("GALARICA TWIG"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A twig from a tree\n"
            "in Galar called\n"
            "Galarica."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_GalaricaTwig,
        .iconPalette = gItemIconPalette_GalaricaItem,
    },

    [ITEM_ARMORITE_ORE] =
    {
        .name = ITEM_NAME("ARMORITE ORE"),
        .pluralName = ITEM_PLURAL_NAME("Armorite Ore"),
        .price = 20,
        .description = COMPOUND_STRING(
            "A rare ore. Can be\n"
            "found in the Isle\n"
            "of Armor at Galar."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ArmoriteOre,
        .iconPalette = gItemIconPalette_ArmoriteOre,
    },

    [ITEM_DYNITE_ORE] =
    {
        .name = ITEM_NAME("DYNITE ORE"),
        .pluralName = ITEM_PLURAL_NAME("Dynite Ore"),
        .price = 20,
        .description = COMPOUND_STRING(
            "A mysterious ore.\n"
            "It can be found in\n"
            "Galar's Max Lair."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_DyniteOre,
        .iconPalette = gItemIconPalette_DyniteOre,
    },

// Mail

    [ITEM_ORANGE_MAIL] =
    {
        .name = ITEM_NAME("ORANGE MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Orange Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Zigzagoon-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_ORANGE_MAIL),
        .iconPic = gItemIcon_OrangeMail,
        .iconPalette = gItemIconPalette_OrangeMail,
    },

    [ITEM_HARBOR_MAIL] =
    {
        .name = ITEM_NAME("HARBOR MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Harbor Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Wingull-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_HARBOR_MAIL),
        .iconPic = gItemIcon_HarborMail,
        .iconPalette = gItemIconPalette_HarborMail,
    },

    [ITEM_GLITTER_MAIL] =
    {
        .name = ITEM_NAME("GLITTER MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Glitter Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Pikachu-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_GLITTER_MAIL),
        .iconPic = gItemIcon_GlitterMail,
        .iconPalette = gItemIconPalette_GlitterMail,
    },

    [ITEM_MECH_MAIL] =
    {
        .name = ITEM_NAME("MECH MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Mech Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Magnemite-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_MECH_MAIL),
        .iconPic = gItemIcon_MechMail,
        .iconPalette = gItemIconPalette_MechMail,
    },

    [ITEM_WOOD_MAIL] =
    {
        .name = ITEM_NAME("WOOD MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Wood Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Slakoth-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_WOOD_MAIL),
        .iconPic = gItemIcon_WoodMail,
        .iconPalette = gItemIconPalette_WoodMail,
    },

    [ITEM_WAVE_MAIL] =
    {
        .name = ITEM_NAME("WAVE MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Wave Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Wailmer-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_WAVE_MAIL),
        .iconPic = gItemIcon_WaveMail,
        .iconPalette = gItemIconPalette_WaveMail,
    },

    [ITEM_BEAD_MAIL] =
    {
        .name = ITEM_NAME("BEAD MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Bead Mail"),
        .price = 50,
        .description = sBeadMailDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_BEAD_MAIL),
        .iconPic = gItemIcon_BeadMail,
        .iconPalette = gItemIconPalette_BeadMail,
    },

    [ITEM_SHADOW_MAIL] =
    {
        .name = ITEM_NAME("SHADOW MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Shadow Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Duskull-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_SHADOW_MAIL),
        .iconPic = gItemIcon_ShadowMail,
        .iconPalette = gItemIconPalette_ShadowMail,
    },

    [ITEM_TROPIC_MAIL] =
    {
        .name = ITEM_NAME("TROPIC MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Tropic Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A Bellossom-print\n"
            "Mail to be held by\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_TROPIC_MAIL),
        .iconPic = gItemIcon_TropicMail,
        .iconPalette = gItemIconPalette_TropicMail,
    },

    [ITEM_DREAM_MAIL] =
    {
        .name = ITEM_NAME("DREAM MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Dream Mail"),
        .price = 50,
        .description = sBeadMailDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_DREAM_MAIL),
        .iconPic = gItemIcon_DreamMail,
        .iconPalette = gItemIconPalette_DreamMail,
    },

    [ITEM_FAB_MAIL] =
    {
        .name = ITEM_NAME("FAB MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Fab Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "A gorgeous-print\n"
            "Mail to be held\n"
            "by a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_FAB_MAIL),
        .iconPic = gItemIcon_FabMail,
        .iconPalette = gItemIconPalette_FabMail,
    },

    [ITEM_RETRO_MAIL] =
    {
        .name = ITEM_NAME("RETRO MAIL"),
        .pluralName = ITEM_PLURAL_NAME("Retro Mail"),
        .price = 50,
        .description = COMPOUND_STRING(
            "Mail featuring the\n"
            "drawings of three\n"
            "Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MAIL,
        .type = ITEM_USE_MAIL,
        .fieldUseFunc = ItemUseOutOfBattle_Mail,
        .secondaryId = ITEM_TO_MAIL(ITEM_RETRO_MAIL),
        .iconPic = gItemIcon_RetroMail,
        .iconPalette = gItemIconPalette_RetroMail,
    },

// Evolution Items

    [ITEM_FIRE_STONE] =
    {
        .name = ITEM_NAME("FIRE STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_FireStone,
        .iconPalette = gItemIconPalette_FireStone,
    },

    [ITEM_WATER_STONE] =
    {
        .name = ITEM_NAME("WATER STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_WaterStone,
        .iconPalette = gItemIconPalette_WaterStone,
    },

    [ITEM_THUNDER_STONE] =
    {
        .name = ITEM_NAME("THUNDER STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_ThunderStone,
        .iconPalette = gItemIconPalette_ThunderStone,
    },

    [ITEM_LEAF_STONE] =
    {
        .name = ITEM_NAME("LEAF STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_LeafStone,
        .iconPalette = gItemIconPalette_LeafStone,
    },

    [ITEM_ICE_STONE] =
    {
        .name = ITEM_NAME("ICE STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_IceStone,
        .iconPalette = gItemIconPalette_IceStone,
    },

    [ITEM_SUN_STONE] =
    {
        .name = ITEM_NAME("SUN STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_SunStone,
        .iconPalette = gItemIconPalette_SunStone,
    },

    [ITEM_MOON_STONE] =
    {
        .name = ITEM_NAME("MOON STONE"),
    #if I_PRICE >= GEN_7
        .price = 3000,
    #elif I_PRICE >= GEN_4
        .price = 2100,
    #elif I_PRICE == GEN_3
        .price = 0,
    #else
        .price = 10000,
    #endif
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_MoonStone,
        .iconPalette = gItemIconPalette_MoonStone,
    },

    [ITEM_SHINY_STONE] =
    {
        .name = ITEM_NAME("SHINY STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_ShinyStone,
        .iconPalette = gItemIconPalette_ShinyStone,
    },

    [ITEM_DUSK_STONE] =
    {
        .name = ITEM_NAME("DUSK STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_DuskStone,
        .iconPalette = gItemIconPalette_DuskStone,
    },

    [ITEM_DAWN_STONE] =
    {
        .name = ITEM_NAME("DAWN STONE"),
        .price = 10000,
        .description = sEvolutionStoneDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_STONE,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_DawnStone,
        .iconPalette = gItemIconPalette_DawnStone,
    },

    [ITEM_SWEET_APPLE] =
    {
        .name = ITEM_NAME("SWEET APPLE"),
        .price = 2200,
        .description = COMPOUND_STRING(
            "A very sweet apple\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_SweetApple,
        .iconPalette = gItemIconPalette_SweetApple,
    },

    [ITEM_TART_APPLE] =
    {
        .name = ITEM_NAME("TART APPLE"),
        .price = 2200,
        .description = COMPOUND_STRING(
            "A very tart apple\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_TartApple,
        .iconPalette = gItemIconPalette_TartApple,
    },

    [ITEM_CRACKED_POT] =
    {
        .name = ITEM_NAME("CRACKED POT"),
        .price = 1600,
        .description = COMPOUND_STRING(
            "A cracked teapot\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_CrackedPot,
        .iconPalette = gItemIconPalette_Pot,
    },

    [ITEM_CHIPPED_POT] =
    {
        .name = ITEM_NAME("CHIPPED POT"),
        .price = 38000,
        .description = COMPOUND_STRING(
            "A chipped teapot\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_ChippedPot,
        .iconPalette = gItemIconPalette_Pot,
    },

    [ITEM_GALARICA_CUFF] =
    {
        .name = ITEM_NAME("GALARICA CUFF"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A cuff from Galar\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_GalaricaCuff,
        .iconPalette = gItemIconPalette_GalaricaItem,
    },

    [ITEM_GALARICA_WREATH] =
    {
        .name = ITEM_NAME("GALARICA WREATH"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A wreath made in\n"
            "Galar. Makes some\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_GalaricaWreath,
        .iconPalette = gItemIconPalette_GalaricaItem,
    },

    [ITEM_DRAGON_SCALE] =
    {
        .name = ITEM_NAME("DRAGON SCALE"),
        .price = 20000,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A strange scale\n"
            "held by Dragon-\n"
            "type Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_DragonScale,
        .iconPalette = gItemIconPalette_DragonScale,
    },

    [ITEM_UPGRADE] =
    {
        .name = ITEM_NAME("UPGRADE"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A peculiar box made\n"
            "by Silph Co."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_Upgrade,
        .iconPalette = gItemIconPalette_Upgrade,
    },

    [ITEM_PROTECTOR] =
    {
        .name = ITEM_NAME("PROTECTOR"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "Loved by a certain\n"
            "Pokémon. It's stiff\n"
            "and heavy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Protector,
        .iconPalette = gItemIconPalette_Protector,
    },

    [ITEM_ELECTIRIZER] =
    {
        .name = ITEM_NAME("ELECTIRIZER"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "Loved by a certain\n"
            "Pokémon. It's full\n"
            "of electric energy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Electirizer,
        .iconPalette = gItemIconPalette_Electirizer,
    },

    [ITEM_MAGMARIZER] =
    {
        .name = ITEM_NAME("MAGMARIZER"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "Loved by a certain\n"
            "Pokémon. It's full\n"
            "of magma energy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Magmarizer,
        .iconPalette = gItemIconPalette_Magmarizer,
    },

    [ITEM_DUBIOUS_DISC] =
    {
        .name = ITEM_NAME("DUBIOUS DISC"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A clear device\n"
            "overflowing with\n"
            "dubious data."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 50,
        .iconPic = gItemIcon_DubiousDisc,
        .iconPalette = gItemIconPalette_DubiousDisc,
    },

    [ITEM_REAPER_CLOTH] =
    {
        .name = ITEM_NAME("REAPER CLOTH"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "Loved by a certain\n"
            "Pokémon. Imbued\n"
            "with spirit energy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 10,
        .iconPic = gItemIcon_ReaperCloth,
        .iconPalette = gItemIconPalette_ReaperCloth,
    },

    [ITEM_PRISM_SCALE] =
    {
        .name = ITEM_NAME("PRISM SCALE"),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 2000,
    #else
        .price = 20000,
    #endif
        .description = COMPOUND_STRING(
            "A mysterious scale\n"
            "that evolves a\n"
            "certain Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_PrismScale,
        .iconPalette = gItemIconPalette_PrismScale,
    },

    [ITEM_WHIPPED_DREAM] =
    {
        .name = ITEM_NAME("WHIPPED DREAM"),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = COMPOUND_STRING(
            "A soft and sweet\n"
            "treat loved by\n"
            "a certain Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_WhippedDream,
        .iconPalette = gItemIconPalette_WhippedDream,
    },

    [ITEM_SACHET] =
    {
        .name = ITEM_NAME("SACHET"),
        .price = (I_PRICE >= GEN_7) ? 2000 * TREASURE_FACTOR : 2100,
        .description = COMPOUND_STRING(
            "A sachet of strong\n"
            "perfumes, loved by\n"
            "a certain Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_Sachet,
        .iconPalette = gItemIconPalette_Sachet,
    },

    [ITEM_OVAL_STONE] =
    {
        .name = ITEM_NAME("OVAL STONE"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "Peculiar stone\n"
            "that evolves a\n"
            "certain Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_OvalStone,
        .iconPalette = gItemIconPalette_OvalStone,
    },

    [ITEM_STRAWBERRY_SWEET] =
    {
        .name = ITEM_NAME("STRAWBERRY SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "Strawberry-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_StrawberrySweet,
        .iconPalette = gItemIconPalette_StrawberrySweet,
    },

    [ITEM_LOVE_SWEET] =
    {
        .name = ITEM_NAME("LOVE SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A heart-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LoveSweet,
        .iconPalette = gItemIconPalette_LoveSweet,
    },

    [ITEM_BERRY_SWEET] =
    {
        .name = ITEM_NAME("BERRY SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A berry-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BerrySweet,
        .iconPalette = gItemIconPalette_BerrySweet,
    },

    [ITEM_CLOVER_SWEET] =
    {
        .name = ITEM_NAME("CLOVER SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A clover-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CloverSweet,
        .iconPalette = gItemIconPalette_CloverSweet,
    },

    [ITEM_FLOWER_SWEET] =
    {
        .name = ITEM_NAME("FLOWER SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A flower-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FlowerSweet,
        .iconPalette = gItemIconPalette_FlowerSweet,
    },

    [ITEM_STAR_SWEET] =
    {
        .name = ITEM_NAME("STAR SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A star-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_StarSweet,
        .iconPalette = gItemIconPalette_StarSweet,
    },

    [ITEM_RIBBON_SWEET] =
    {
        .name = ITEM_NAME("RIBBON SWEET"),
        .price = 500 * TREASURE_FACTOR,
        .description = COMPOUND_STRING(
            "A ribbon-shaped\n"
            "sweet loved by\n"
            "Milcery."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RibbonSweet,
        .iconPalette = gItemIconPalette_RibbonSweet,
    },

    [ITEM_EVERSTONE] =
    {
        .name = ITEM_NAME("EVERSTONE"),
        .price = (I_PRICE >= GEN_7) ? 3000 : 200,
        .holdEffect = HOLD_EFFECT_PREVENT_EVOLVE,
        .description = COMPOUND_STRING(
            "A wondrous hold\n"
            "item that prevents\n"
            "evolution."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Everstone,
        .iconPalette = gItemIconPalette_Everstone,
    },

// Nectars

    [ITEM_RED_NECTAR] =
    {
        .name = ITEM_NAME("RED NECTAR"),
        .price = 300,
        .holdEffectParam = 0,
        .description = sNectarDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_RedNectar,
    },

    [ITEM_YELLOW_NECTAR] =
    {
        .name = ITEM_NAME("YELLOW NECTAR"),
        .price = 300,
        .holdEffectParam = 0,
        .description = sNectarDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_YellowNectar,
    },

    [ITEM_PINK_NECTAR] =
    {
        .name = ITEM_NAME("PINK NECTAR"),
        .price = 300,
        .holdEffectParam = 0,
        .description = sNectarDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_PinkNectar,
    },

    [ITEM_PURPLE_NECTAR] =
    {
        .name = ITEM_NAME("PURPLE NECTAR"),
        .price = 300,
        .holdEffectParam = 0,
        .description = sNectarDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_NECTAR,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange_ConsumedOnUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Nectar,
        .iconPalette = gItemIconPalette_PurpleNectar,
    },

// Plates

    [ITEM_FLAME_PLATE] =
    {
        .name = ITEM_NAME("FLAME PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Fire-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_FlamePlate,
    },

    [ITEM_SPLASH_PLATE] =
    {
        .name = ITEM_NAME("SPLASH PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Water-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_SplashPlate,
    },

    [ITEM_ZAP_PLATE] =
    {
        .name = ITEM_NAME("ZAP PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of Elec-\n"
            "tric-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_ZapPlate,
    },

    [ITEM_MEADOW_PLATE] =
    {
        .name = ITEM_NAME("MEADOW PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Grass-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_MeadowPlate,
    },

    [ITEM_ICICLE_PLATE] =
    {
        .name = ITEM_NAME("ICICLE PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Ice-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_IciclePlate,
    },

    [ITEM_FIST_PLATE] =
    {
        .name = ITEM_NAME("FIST PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of Fight-\n"
            "ing-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_FistPlate,
    },

    [ITEM_TOXIC_PLATE] =
    {
        .name = ITEM_NAME("TOXIC PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Poison-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_ToxicPlate,
    },

    [ITEM_EARTH_PLATE] =
    {
        .name = ITEM_NAME("EARTH PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Ground-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_EarthPlate,
    },

    [ITEM_SKY_PLATE] =
    {
        .name = ITEM_NAME("SKY PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Flying-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_SkyPlate,
    },

    [ITEM_MIND_PLATE] =
    {
        .name = ITEM_NAME("MIND PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of Psy\n"
            "chic-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_MindPlate,
    },

    [ITEM_INSECT_PLATE] =
    {
        .name = ITEM_NAME("INSECT PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Bug-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_InsectPlate,
    },

    [ITEM_STONE_PLATE] =
    {
        .name = ITEM_NAME("STONE PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Rock-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_StonePlate,
    },

    [ITEM_SPOOKY_PLATE] =
    {
        .name = ITEM_NAME("SPOOKY PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Ghost-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_SpookyPlate,
    },

    [ITEM_DRACO_PLATE] =
    {
        .name = ITEM_NAME("DRACO PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Dragon-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_DracoPlate,
    },

    [ITEM_DREAD_PLATE] =
    {
        .name = ITEM_NAME("DREAD PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Dark-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_DreadPlate,
    },

    [ITEM_IRON_PLATE] =
    {
        .name = ITEM_NAME("IRON PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Steel-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_IronPlate,
    },

    [ITEM_PIXIE_PLATE] =
    {
        .name = ITEM_NAME("PIXIE PLATE"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_PLATE,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A tablet that ups\n"
            "the power of\n"
            "Fairy-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_PLATE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 90,
        .iconPic = gItemIcon_Plate,
        .iconPalette = gItemIconPalette_PixiePlate,
    },

// Drives

    [ITEM_DOUSE_DRIVE] =
    {
        .name = ITEM_NAME("DOUSE DRIVE"),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = COMPOUND_STRING(
            "Changes Genesect's\n"
            "Techno Blast to\n"
            "Water-type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_DouseDrive,
    },

    [ITEM_SHOCK_DRIVE] =
    {
        .name = ITEM_NAME("SHOCK DRIVE"),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = COMPOUND_STRING(
            "Changes Genesect's\n"
            "Techno Blast to\n"
            "Electric-type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_ShockDrive,
    },

    [ITEM_BURN_DRIVE] =
    {
        .name = ITEM_NAME("BURN DRIVE"),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = COMPOUND_STRING(
            "Changes Genesect's\n"
            "Techno Blast to\n"
            "Fire-type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_BurnDrive,
    },

    [ITEM_CHILL_DRIVE] =
    {
        .name = ITEM_NAME("CHILL DRIVE"),
        .price = (I_PRICE >= GEN_7) ? 0 : 1000,
        .holdEffect = HOLD_EFFECT_DRIVE,
        .description = COMPOUND_STRING(
            "Changes Genesect's\n"
            "Techno Blast to\n"
            "Ice-type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_DRIVE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 70,
        .iconPic = gItemIcon_Drive,
        .iconPalette = gItemIconPalette_ChillDrive,
    },

// Memories

    [ITEM_FIRE_MEMORY] =
    {
        .name = ITEM_NAME("FIRE MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Fire Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Fire\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 50,
        .iconPic = gItemIcon_FireMemory,
        .iconPalette = gItemIconPalette_FireMemory,
    },

    [ITEM_WATER_MEMORY] =
    {
        .name = ITEM_NAME("WATER MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Water Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Water\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 50,
        .iconPic = gItemIcon_WaterMemory,
        .iconPalette = gItemIconPalette_WaterMemory,
    },

    [ITEM_ELECTRIC_MEMORY] =
    {
        .name = ITEM_NAME("ELECTRIC MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Electric Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Electric\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 50,
        .iconPic = gItemIcon_ElectricMemory,
        .iconPalette = gItemIconPalette_ElectricMemory,
    },

    [ITEM_GRASS_MEMORY] =
    {
        .name = ITEM_NAME("GRASS MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Grass Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Grass\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 50,
        .iconPic = gItemIcon_GrassMemory,
        .iconPalette = gItemIconPalette_GrassMemory,
    },

    [ITEM_ICE_MEMORY] =
    {
        .name = ITEM_NAME("ICE MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Ice Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Ice\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 50,
        .iconPic = gItemIcon_IceMemory,
        .iconPalette = gItemIconPalette_IceMemory,
    },

    [ITEM_FIGHTING_MEMORY] =
    {
        .name = ITEM_NAME("FIGHTING MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Fighting Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Disc with Fighting\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 50,
        .iconPic = gItemIcon_FightingMemory,
        .iconPalette = gItemIconPalette_FightingMemory,
    },

    [ITEM_POISON_MEMORY] =
    {
        .name = ITEM_NAME("POISON MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Poison Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Poison\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 50,
        .iconPic = gItemIcon_PoisonMemory,
        .iconPalette = gItemIconPalette_PoisonMemory,
    },

    [ITEM_GROUND_MEMORY] =
    {
        .name = ITEM_NAME("GROUND MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Ground Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Ground\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 50,
        .iconPic = gItemIcon_GroundMemory,
        .iconPalette = gItemIconPalette_GroundMemory,
    },

    [ITEM_FLYING_MEMORY] =
    {
        .name = ITEM_NAME("FLYING MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Flying Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Flying\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 50,
        .iconPic = gItemIcon_FlyingMemory,
        .iconPalette = gItemIconPalette_FlyingMemory,
    },

    [ITEM_PSYCHIC_MEMORY] =
    {
        .name = ITEM_NAME("PSYCHIC MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Psychic Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Psychic\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 50,
        .iconPic = gItemIcon_PsychicMemory,
        .iconPalette = gItemIconPalette_PsychicMemory,
    },

    [ITEM_BUG_MEMORY] =
    {
        .name = ITEM_NAME("BUG MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Bug Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Bug\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 50,
        .iconPic = gItemIcon_BugMemory,
        .iconPalette = gItemIconPalette_BugMemory,
    },

    [ITEM_ROCK_MEMORY] =
    {
        .name = ITEM_NAME("ROCK MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Rock Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Rock\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 50,
        .iconPic = gItemIcon_RockMemory,
        .iconPalette = gItemIconPalette_RockMemory,
    },

    [ITEM_GHOST_MEMORY] =
    {
        .name = ITEM_NAME("GHOST MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Ghost Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Ghost\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 50,
        .iconPic = gItemIcon_GhostMemory,
        .iconPalette = gItemIconPalette_GhostMemory,
    },

    [ITEM_DRAGON_MEMORY] =
    {
        .name = ITEM_NAME("DRAGON MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Dragon Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Dragon\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 50,
        .iconPic = gItemIcon_DragonMemory,
        .iconPalette = gItemIconPalette_DragonMemory,
    },

    [ITEM_DARK_MEMORY] =
    {
        .name = ITEM_NAME("DARK MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Dark Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Dark\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 50,
        .iconPic = gItemIcon_DarkMemory,
        .iconPalette = gItemIconPalette_DarkMemory,
    },

    [ITEM_STEEL_MEMORY] =
    {
        .name = ITEM_NAME("STEEL MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Steel Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Steel\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .flingPower = 50,
        .iconPic = gItemIcon_SteelMemory,
        .iconPalette = gItemIconPalette_SteelMemory,
    },

    [ITEM_FAIRY_MEMORY] =
    {
        .name = ITEM_NAME("FAIRY MEMORY"),
        .pluralName = ITEM_PLURAL_NAME("Fairy Memories"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_MEMORY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "A disc with Fairy\n"
            "type data. It swaps\n"
            "Silvally's type."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEMORY,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 50,
        .iconPic = gItemIcon_FairyMemory,
        .iconPalette = gItemIconPalette_FairyMemory,
    },

    [ITEM_RUSTED_SWORD] =
    {
        .name = ITEM_NAME("RUSTED SWORD"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A rusty sword. A\n"
            "hero used it to\n"
            "halt a disaster."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RustedSword,
        .iconPalette = gItemIconPalette_RustedWeapons,
    },

    [ITEM_RUSTED_SHIELD] =
    {
        .name = ITEM_NAME("RUSTED SHIELD"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A rusty shield. A\n"
            "hero used it to\n"
            "halt a disaster."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RustedShield,
        .iconPalette = gItemIconPalette_RustedWeapons,
    },

// Colored Orbs

    [ITEM_RED_ORB] =
    {
        .name = ITEM_NAME("RED ORB"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_PRIMAL_ORB,
        .description = COMPOUND_STRING(
            "A red, glowing orb\n"
            "said to contain an\n"
            "ancient power."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RedOrb,
        .iconPalette = gItemIconPalette_RedOrb,
    },

    [ITEM_BLUE_ORB] =
    {
        .name = ITEM_NAME("BLUE ORB"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_PRIMAL_ORB,
        .description = COMPOUND_STRING(
            "A blue, glowing orb\n"
            "said to contain an\n"
            "ancient power."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BlueOrb,
        .iconPalette = gItemIconPalette_BlueOrb,
    },

// Mega Stones

    [ITEM_VENUSAURITE] =
    {
        .name = ITEM_NAME("VENUSAURITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Venusaur to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Venusaurite,
        .iconPalette = gItemIconPalette_Venusaurite,
    },

    [ITEM_CHARIZARDITE_X] =
    {
        .name = ITEM_NAME("CHARIZARDITE X"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sCharizarditeDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_CharizarditeX,
        .iconPalette = gItemIconPalette_CharizarditeX,
    },

    [ITEM_CHARIZARDITE_Y] =
    {
        .name = ITEM_NAME("CHARIZARDITE Y"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sCharizarditeDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_CharizarditeY,
        .iconPalette = gItemIconPalette_CharizarditeY,
    },

    [ITEM_BLASTOISINITE] =
    {
        .name = ITEM_NAME("BLASTOISINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Blastoise to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Blastoisinite,
        .iconPalette = gItemIconPalette_Blastoisinite,
    },

    [ITEM_BEEDRILLITE] =
    {
        .name = ITEM_NAME("BEEDRILLITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Beedrill to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Beedrillite,
        .iconPalette = gItemIconPalette_Beedrillite,
    },

    [ITEM_PIDGEOTITE] =
    {
        .name = ITEM_NAME("PIDGEOTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Pidgeot to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Pidgeotite,
        .iconPalette = gItemIconPalette_Pidgeotite,
    },

    [ITEM_ALAKAZITE] =
    {
        .name = ITEM_NAME("ALAKAZITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Alakazam to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Alakazite,
        .iconPalette = gItemIconPalette_Alakazite,
    },

    [ITEM_SLOWBRONITE] =
    {
        .name = ITEM_NAME("SLOWBRONITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Slowbro to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Slowbronite,
        .iconPalette = gItemIconPalette_Slowbronite,
    },

    [ITEM_GENGARITE] =
    {
        .name = ITEM_NAME("GENGARITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Gengar to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Gengarite,
        .iconPalette = gItemIconPalette_Gengarite,
    },

    [ITEM_KANGASKHANITE] =
    {
        .name = ITEM_NAME("KANGASKHANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Kangaskhan to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Kangaskhanite,
        .iconPalette = gItemIconPalette_Kangaskhanite,
    },

    [ITEM_PINSIRITE] =
    {
        .name = ITEM_NAME("PINSIRITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Pinsir to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Pinsirite,
        .iconPalette = gItemIconPalette_Pinsirite,
    },

    [ITEM_GYARADOSITE] =
    {
        .name = ITEM_NAME("GYARADOSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Gyarados to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Gyaradosite,
        .iconPalette = gItemIconPalette_Gyaradosite,
    },

    [ITEM_AERODACTYLITE] =
    {
        .name = ITEM_NAME("AERODACTYLITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Aerodactyl to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Aerodactylite,
        .iconPalette = gItemIconPalette_Aerodactylite,
    },

    [ITEM_MEWTWONITE_X] =
    {
        .name = ITEM_NAME("MEWTWONITE X"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMewtwoniteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_MewtwoniteX,
        .iconPalette = gItemIconPalette_MewtwoniteX,
    },

    [ITEM_MEWTWONITE_Y] =
    {
        .name = ITEM_NAME("MEWTWONITE Y"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sMewtwoniteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_MewtwoniteY,
        .iconPalette = gItemIconPalette_MewtwoniteY,
    },

    [ITEM_AMPHAROSITE] =
    {
        .name = ITEM_NAME("AMPHAROSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Ampharos to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Ampharosite,
        .iconPalette = gItemIconPalette_Ampharosite,
    },

    [ITEM_STEELIXITE] =
    {
        .name = ITEM_NAME("STEELIXITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Steelix to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Steelixite,
        .iconPalette = gItemIconPalette_Steelixite,
    },

    [ITEM_SCIZORITE] =
    {
        .name = ITEM_NAME("SCIZORITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Scizor to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scizorite,
        .iconPalette = gItemIconPalette_Scizorite,
    },

    [ITEM_HERACRONITE] =
    {
        .name = ITEM_NAME("HERACRONITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Heracross to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Heracronite,
        .iconPalette = gItemIconPalette_Heracronite,
    },

    [ITEM_HOUNDOOMINITE] =
    {
        .name = ITEM_NAME("HOUNDOOMINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Houndoom to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Houndoominite,
        .iconPalette = gItemIconPalette_Houndoominite,
    },

    [ITEM_TYRANITARITE] =
    {
        .name = ITEM_NAME("TYRANITARITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Tyranitar to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Tyranitarite,
        .iconPalette = gItemIconPalette_Tyranitarite,
    },

    [ITEM_SCEPTILITE] =
    {
        .name = ITEM_NAME("SCEPTILITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Sceptile to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Sceptilite,
        .iconPalette = gItemIconPalette_Sceptilite,
    },

    [ITEM_BLAZIKENITE] =
    {
        .name = ITEM_NAME("BLAZIKENITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Blaziken to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Blazikenite,
        .iconPalette = gItemIconPalette_Blazikenite,
    },

    [ITEM_SWAMPERTITE] =
    {
        .name = ITEM_NAME("SWAMPERTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Swampert to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Swampertite,
        .iconPalette = gItemIconPalette_Swampertite,
    },

    [ITEM_GARDEVOIRITE] =
    {
        .name = ITEM_NAME("GARDEVOIRITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Gardevoir to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Gardevoirite,
        .iconPalette = gItemIconPalette_Gardevoirite,
    },

    [ITEM_SABLENITE] =
    {
        .name = ITEM_NAME("SABLENITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Sableye to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Sablenite,
        .iconPalette = gItemIconPalette_Sablenite,
    },

    [ITEM_MAWILITE] =
    {
        .name = ITEM_NAME("MAWILITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Mawile to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Mawilite,
        .iconPalette = gItemIconPalette_Mawilite,
    },

    [ITEM_AGGRONITE] =
    {
        .name = ITEM_NAME("AGGRONITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Aggron to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Aggronite,
        .iconPalette = gItemIconPalette_Aggronite,
    },

    [ITEM_MEDICHAMITE] =
    {
        .name = ITEM_NAME("MEDICHAMITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Medicham to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Medichamite,
        .iconPalette = gItemIconPalette_Medichamite,
    },

    [ITEM_MANECTITE] =
    {
        .name = ITEM_NAME("MANECTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Manectric to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Manectite,
        .iconPalette = gItemIconPalette_Manectite,
    },

    [ITEM_SHARPEDONITE] =
    {
        .name = ITEM_NAME("SHARPEDONITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Sharpedo to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Sharpedonite,
        .iconPalette = gItemIconPalette_Sharpedonite,
    },

    [ITEM_CAMERUPTITE] =
    {
        .name = ITEM_NAME("CAMERUPTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Camerupt to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Cameruptite,
        .iconPalette = gItemIconPalette_Cameruptite,
    },

    [ITEM_ALTARIANITE] =
    {
        .name = ITEM_NAME("ALTARIANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Altaria to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Altarianite,
        .iconPalette = gItemIconPalette_Altarianite,
    },

    [ITEM_BANETTITE] =
    {
        .name = ITEM_NAME("BANETTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Banette to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Banettite,
        .iconPalette = gItemIconPalette_Banettite,
    },

    [ITEM_ABSOLITE] =
    {
        .name = ITEM_NAME("ABSOLITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAbsoliteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Absolite,
        .iconPalette = gItemIconPalette_Absolite,
    },

    [ITEM_GLALITITE] =
    {
        .name = ITEM_NAME("GLALITITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Glalie to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Glalitite,
        .iconPalette = gItemIconPalette_Glalitite,
    },

    [ITEM_SALAMENCITE] =
    {
        .name = ITEM_NAME("SALAMENCITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Salamence to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Salamencite,
        .iconPalette = gItemIconPalette_Salamencite,
    },

    [ITEM_METAGROSSITE] =
    {
        .name = ITEM_NAME("METAGROSSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Metagross to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Metagrossite,
        .iconPalette = gItemIconPalette_Metagrossite,
    },

    [ITEM_LATIASITE] =
    {
        .name = ITEM_NAME("LATIASITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Latias to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Latiasite,
        .iconPalette = gItemIconPalette_Latiasite,
    },

    [ITEM_LATIOSITE] =
    {
        .name = ITEM_NAME("LATIOSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Latios to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Latiosite,
        .iconPalette = gItemIconPalette_Latiosite,
    },

    [ITEM_LOPUNNITE] =
    {
        .name = ITEM_NAME("LOPUNNITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Lopunny to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Lopunnite,
        .iconPalette = gItemIconPalette_Lopunnite,
    },

    [ITEM_GARCHOMPITE] =
    {
        .name = ITEM_NAME("GARCHOMPITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGarchompiteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Garchompite,
        .iconPalette = gItemIconPalette_Garchompite,
    },

    [ITEM_LUCARIONITE] =
    {
        .name = ITEM_NAME("LUCARIONITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sLucarioniteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Lucarionite,
        .iconPalette = gItemIconPalette_Lucarionite,
    },

    [ITEM_ABOMASITE] =
    {
        .name = ITEM_NAME("ABOMASITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Abomasnow to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Abomasite,
        .iconPalette = gItemIconPalette_Abomasite,
    },

    [ITEM_GALLADITE] =
    {
        .name = ITEM_NAME("GALLADITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Gallade to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Galladite,
        .iconPalette = gItemIconPalette_Galladite,
    },

    [ITEM_AUDINITE] =
    {
        .name = ITEM_NAME("AUDINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Audino to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Audinite,
        .iconPalette = gItemIconPalette_Audinite,
    },

    [ITEM_DIANCITE] =
    {
        .name = ITEM_NAME("DIANCITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Diancie to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Diancite,
        .iconPalette = gItemIconPalette_Diancite,
    },

    [ITEM_CLEFABLITE] =
    {
        .name = ITEM_NAME("CLEFABLITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Clefable to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Clefablite,
        .iconPalette = gItemIconPalette_Clefablite,
    },

    [ITEM_VICTREEBELITE] =
    {
        .name = ITEM_NAME("VICTREEBELITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Victreebel to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Victreebelite,
        .iconPalette = gItemIconPalette_Victreebelite,
    },

    [ITEM_STARMINITE] =
    {
        .name = ITEM_NAME("STARMINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Starmie to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Starminite,
        .iconPalette = gItemIconPalette_Starminite,
    },

    [ITEM_DRAGONINITE] =
    {
        .name = ITEM_NAME("DRAGONINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Dragonite to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Dragoninite,
        .iconPalette = gItemIconPalette_Dragoninite,
    },

    [ITEM_MEGANIUMITE] =
    {
        .name = ITEM_NAME("MEGANIUMITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Meganium to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Meganiumite,
        .iconPalette = gItemIconPalette_Meganiumite,
    },

    [ITEM_FERALIGITE] =
    {
        .name = ITEM_NAME("FERALIGITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Feraligatr to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Feraligite,
        .iconPalette = gItemIconPalette_Feraligite,
    },

    [ITEM_SKARMORITE] =
    {
        .name = ITEM_NAME("SKARMORITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Skarmory to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Skarmorite,
        .iconPalette = gItemIconPalette_Skarmorite,
    },

    [ITEM_FROSLASSITE] =
    {
        .name = ITEM_NAME("FROSLASSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Froslass to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Froslassite,
        .iconPalette = gItemIconPalette_Froslassite,
    },

    [ITEM_EMBOARITE] =
    {
        .name = ITEM_NAME("EMBOARITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Emboar to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Emboarite,
        .iconPalette = gItemIconPalette_Emboarite,
    },

    [ITEM_EXCADRITE] =
    {
        .name = ITEM_NAME("EXCADRITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Excadrill to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Excadrite,
        .iconPalette = gItemIconPalette_Excadrite,
    },

    [ITEM_SCOLIPITE] =
    {
        .name = ITEM_NAME("SCOLIPITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Scolipede to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scolipite,
        .iconPalette = gItemIconPalette_Scolipite,
    },

    [ITEM_SCRAFTINITE] =
    {
        .name = ITEM_NAME("SCRAFTINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Scrafty to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scraftinite,
        .iconPalette = gItemIconPalette_Scraftinite,
    },

    [ITEM_EELEKTROSSITE] =
    {
        .name = ITEM_NAME("EELEKTROSSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Eelektross to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Eelektrossite,
        .iconPalette = gItemIconPalette_Eelektrossite,
    },

    [ITEM_CHANDELURITE] =
    {
        .name = ITEM_NAME("CHANDELURITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Chandelure to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Chandelurite,
        .iconPalette = gItemIconPalette_Chandelurite,
    },

    [ITEM_CHESNAUGHTITE] =
    {
        .name = ITEM_NAME("CHESNAUGHTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Chesnaught to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Chesnaughtite,
        .iconPalette = gItemIconPalette_Chesnaughtite,
    },

    [ITEM_DELPHOXITE] =
    {
        .name = ITEM_NAME("DELPHOXITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Delphox to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Delphoxite,
        .iconPalette = gItemIconPalette_Delphoxite,
    },

    [ITEM_GRENINJITE] =
    {
        .name = ITEM_NAME("GRENINJITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Greninja to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Greninjite,
        .iconPalette = gItemIconPalette_Greninjite,
    },

    [ITEM_PYROARITE] =
    {
        .name = ITEM_NAME("PYROARITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Pyroar to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Pyroarite,
        .iconPalette = gItemIconPalette_Pyroarite,
    },

    [ITEM_FLOETTITE] =
    {
        .name = ITEM_NAME("FLOETTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Floette to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Floettite,
        .iconPalette = gItemIconPalette_Floettite,
    },

    [ITEM_MALAMARITE] =
    {
        .name = ITEM_NAME("MALAMARITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Malamar to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Malamarite,
        .iconPalette = gItemIconPalette_Malamarite,
    },

    [ITEM_BARBARACITE] =
    {
        .name = ITEM_NAME("BARBARACITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Barbaracle to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Barbaracite,
        .iconPalette = gItemIconPalette_Barbaracite,
    },

    [ITEM_DRAGALGITE] =
    {
        .name = ITEM_NAME("DRAGALGITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Dragalge to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Dragalgite,
        .iconPalette = gItemIconPalette_Dragalgite,
    },

    [ITEM_HAWLUCHANITE] =
    {
        .name = ITEM_NAME("HAWLUCHANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Hawlucha to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Hawluchanite,
        .iconPalette = gItemIconPalette_Hawluchanite,
    },

    [ITEM_ZYGARDITE] =
    {
        .name = ITEM_NAME("ZYGARDITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Zygarde to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Zygardite,
        .iconPalette = gItemIconPalette_Zygardite,
    },

    [ITEM_DRAMPANITE] =
    {
        .name = ITEM_NAME("DRAMPANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Drampa to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Drampanite,
        .iconPalette = gItemIconPalette_Drampanite,
    },

    [ITEM_FALINKSITE] =
    {
        .name = ITEM_NAME("FALINKSITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Falinks to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Falinksite,
        .iconPalette = gItemIconPalette_Falinksite,
    },

    [ITEM_HEATRANITE] =
    {
        .name = ITEM_NAME("HEATRANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Heatran to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Heatranite,
        .iconPalette = gItemIconPalette_Heatranite,
    },

    [ITEM_DARKRANITE] =
    {
        .name = ITEM_NAME("DARKRANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Darkrai to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Darkranite,
        .iconPalette = gItemIconPalette_Darkranite,
    },

    [ITEM_ZERAORITE] =
    {
        .name = ITEM_NAME("ZERAORITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Zeraora to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Zeraorite,
        .iconPalette = gItemIconPalette_Zeraorite,
    },

    [ITEM_RAICHUNITE_X] =
    {
        .name = ITEM_NAME("RAICHUNITE X"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sRaichuniteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_RaichuniteX,
        .iconPalette = gItemIconPalette_RaichuniteX,
    },

    [ITEM_RAICHUNITE_Y] =
    {
        .name = ITEM_NAME("RAICHUNITE Y"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sRaichuniteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_RaichuniteY,
        .iconPalette = gItemIconPalette_RaichuniteY,
    },

    [ITEM_CHIMECHITE] =
    {
        .name = ITEM_NAME("CHIMECHITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Chimecho to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Chimechite,
        .iconPalette = gItemIconPalette_Chimechite,
    },

    [ITEM_ABSOLITE_Z] =
    {
        .name = ITEM_NAME("ABSOLITE Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sAbsoliteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_AbsoliteZ,
        .iconPalette = gItemIconPalette_AbsoliteZ,
    },

    [ITEM_STARAPTITE] =
    {
        .name = ITEM_NAME("STARAPTITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Staraptor to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Staraptite,
        .iconPalette = gItemIconPalette_Staraptite,
    },

    [ITEM_GARCHOMPITE_Z] =
    {
        .name = ITEM_NAME("GARCHOMPITE Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sGarchompiteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_GarchompiteZ,
        .iconPalette = gItemIconPalette_GarchompiteZ,
    },

    [ITEM_LUCARIONITE_Z] =
    {
        .name = ITEM_NAME("LUCARIONITE Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = sLucarioniteDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_LucarioniteZ,
        .iconPalette = gItemIconPalette_LucarioniteZ,
    },

    [ITEM_GOLURKITE] =
    {
        .name = ITEM_NAME("GOLURKITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Golurk to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Golurkite,
        .iconPalette = gItemIconPalette_Golurkite,
    },

    [ITEM_MEOWSTICITE] =
    {
        .name = ITEM_NAME("MEOWSTICITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Meowstic to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Meowsticite,
        .iconPalette = gItemIconPalette_Meowsticite,
    },

    [ITEM_CRABOMINITE] =
    {
        .name = ITEM_NAME("CRABOMINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Crabominable to\n"
            "Mega in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Crabominite,
        .iconPalette = gItemIconPalette_Crabominite,
    },

    [ITEM_GOLISOPITE] =
    {
        .name = ITEM_NAME("GOLISOPITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Golisopod to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Golisopite,
        .iconPalette = gItemIconPalette_Golisopite,
    },

    [ITEM_MAGEARNITE] =
    {
        .name = ITEM_NAME("MAGEARNITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Magearna to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Magearnite,
        .iconPalette = gItemIconPalette_Magearnite,
    },

    [ITEM_SCOVILLAINITE] =
    {
        .name = ITEM_NAME("SCOVILLAINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Scovillain to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Scovillainite,
        .iconPalette = gItemIconPalette_Scovillainite,
    },

    [ITEM_BAXCALIBRITE] =
    {
        .name = ITEM_NAME("BAXCALIBRITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Baxcalibur to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Baxcalibrite,
        .iconPalette = gItemIconPalette_Baxcalibrite,
    },

    [ITEM_TATSUGIRINITE] =
    {
        .name = ITEM_NAME("TATSUGIRINITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Tatsugiri to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Tatsugirinite,
        .iconPalette = gItemIconPalette_Tatsugirinite,
    },

    [ITEM_GLIMMORANITE] =
    {
        .name = ITEM_NAME("GLIMMORANITE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_MEGA_STONE,
        .description = COMPOUND_STRING(
            "This stone enables\n"
            "Glimmora to Mega\n"
            "Evolve in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_MEGA_STONE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_Glimmoranite,
        .iconPalette = gItemIconPalette_Glimmoranite,
    },

// GB Player
    [ITEM_GB_PLAYER] =
    {
        .name = ITEM_NAME("GB PLAYER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A device that plays\n"
            "music from the old\n"
            "Pokémon games."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_GBPlayer,
        .importance = 1,
        .iconPic = gItemIcon_GBPlayer,
        .iconPalette = gItemIconPalette_GBPlayer,
    },

// Gems
    #if I_PRICE >= GEN_9
        #define GEM_PRICE 15000
    #elif I_PRICE >= GEN_7
        #define GEM_PRICE 4000
    #else
        #define GEM_PRICE 200
    #endif

    [ITEM_NORMAL_GEM] =
    {
        .name = ITEM_NAME("NORMAL GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Normal\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_NormalGem,
    },

    [ITEM_FIRE_GEM] =
    {
        .name = ITEM_NAME("FIRE GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Fire\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FireGem,
    },

    [ITEM_WATER_GEM] =
    {
        .name = ITEM_NAME("WATER GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Water\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_WaterGem,
    },

    [ITEM_ELECTRIC_GEM] =
    {
        .name = ITEM_NAME("ELECTRIC GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Electric\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_ElectricGem,
    },

    [ITEM_GRASS_GEM] =
    {
        .name = ITEM_NAME("GRASS GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Grass\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_GrassGem,
    },

    [ITEM_ICE_GEM] =
    {
        .name = ITEM_NAME("ICE GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Ice\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_IceGem,
    },

    [ITEM_FIGHTING_GEM] =
    {
        .name = ITEM_NAME("FIGHTING GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Fighting\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FightingGem,
    },

    [ITEM_POISON_GEM] =
    {
        .name = ITEM_NAME("POISON GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Poison\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_PoisonGem,
    },

    [ITEM_GROUND_GEM] =
    {
        .name = ITEM_NAME("GROUND GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Ground\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_GroundGem,
    },

    [ITEM_FLYING_GEM] =
    {
        .name = ITEM_NAME("FLYING GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Flying\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FlyingGem,
    },

    [ITEM_PSYCHIC_GEM] =
    {
        .name = ITEM_NAME("PSYCHIC GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Psychic\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_PsychicGem,
    },

    [ITEM_BUG_GEM] =
    {
        .name = ITEM_NAME("BUG GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Bug\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_BugGem,
    },

    [ITEM_ROCK_GEM] =
    {
        .name = ITEM_NAME("ROCK GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Rock\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_RockGem,
    },

    [ITEM_GHOST_GEM] =
    {
        .name = ITEM_NAME("GHOST GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Ghost\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_GhostGem,
    },

    [ITEM_DRAGON_GEM] =
    {
        .name = ITEM_NAME("DRAGON GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Dragon\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_DragonGem,
    },

    [ITEM_DARK_GEM] =
    {
        .name = ITEM_NAME("DARK GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Dark\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_DarkGem,
    },

    [ITEM_STEEL_GEM] =
    {
        .name = ITEM_NAME("STEEL GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Steel\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_SteelGem,
    },

    [ITEM_FAIRY_GEM] =
    {
        .name = ITEM_NAME("FAIRY GEM"),
        .price = GEM_PRICE,
        .holdEffect = HOLD_EFFECT_GEMS,
        .holdEffectParam = GEM_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of Fairy\n"
            "Type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_GEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .iconPic = gItemIcon_TypeGem,
        .iconPalette = gItemIconPalette_FairyGem,
    },

// Z-Crystals

    [ITEM_NORMALIUM_Z] =
    {
        .name = ITEM_NAME("NORMALIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Normal-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
        .iconPic = gItemIcon_NormaliumZ,
        .iconPalette = gItemIconPalette_NormaliumZ,
    },

    [ITEM_FIRIUM_Z] =
    {
        .name = ITEM_NAME("FIRIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Fire-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .iconPic = gItemIcon_FiriumZ,
        .iconPalette = gItemIconPalette_FiriumZ,
    },

    [ITEM_WATERIUM_Z] =
    {
        .name = ITEM_NAME("WATERIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Water-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .iconPic = gItemIcon_WateriumZ,
        .iconPalette = gItemIconPalette_WateriumZ,
    },

    [ITEM_ELECTRIUM_Z] =
    {
        .name = ITEM_NAME("ELECTRIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Electric-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .iconPic = gItemIcon_ElectriumZ,
        .iconPalette = gItemIconPalette_ElectriumZ,
    },

    [ITEM_GRASSIUM_Z] =
    {
        .name = ITEM_NAME("GRASSIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Grass-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .iconPic = gItemIcon_GrassiumZ,
        .iconPalette = gItemIconPalette_GrassiumZ,
    },

    [ITEM_ICIUM_Z] =
    {
        .name = ITEM_NAME("ICIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Ice-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .iconPic = gItemIcon_IciumZ,
        .iconPalette = gItemIconPalette_IciumZ,
    },

    [ITEM_FIGHTINIUM_Z] =
    {
        .name = ITEM_NAME("FIGHTINIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Fighting-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .iconPic = gItemIcon_FightiniumZ,
        .iconPalette = gItemIconPalette_FightiniumZ,
    },

    [ITEM_POISONIUM_Z] =
    {
        .name = ITEM_NAME("POISONIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Poison-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .iconPic = gItemIcon_PoisoniumZ,
        .iconPalette = gItemIconPalette_PoisoniumZ,
    },

    [ITEM_GROUNDIUM_Z] =
    {
        .name = ITEM_NAME("GROUNDIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Ground-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .iconPic = gItemIcon_GroundiumZ,
        .iconPalette = gItemIconPalette_GroundiumZ,
    },

    [ITEM_FLYINIUM_Z] =
    {
        .name = ITEM_NAME("FLYINIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Flying-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .iconPic = gItemIcon_FlyiniumZ,
        .iconPalette = gItemIconPalette_FlyiniumZ,
    },

    [ITEM_PSYCHIUM_Z] =
    {
        .name = ITEM_NAME("PSYCHIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Psychic-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .iconPic = gItemIcon_PsychiumZ,
        .iconPalette = gItemIconPalette_PsychiumZ,
    },

    [ITEM_BUGINIUM_Z] =
    {
        .name = ITEM_NAME("BUGINIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Bug-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .iconPic = gItemIcon_BuginiumZ,
        .iconPalette = gItemIconPalette_BuginiumZ,
    },

    [ITEM_ROCKIUM_Z] =
    {
        .name = ITEM_NAME("ROCKIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Rock-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .iconPic = gItemIcon_RockiumZ,
        .iconPalette = gItemIconPalette_RockiumZ,
    },

    [ITEM_GHOSTIUM_Z] =
    {
        .name = ITEM_NAME("GHOSTIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Ghost-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .iconPic = gItemIcon_GhostiumZ,
        .iconPalette = gItemIconPalette_GhostiumZ,
    },

    [ITEM_DRAGONIUM_Z] =
    {
        .name = ITEM_NAME("DRAGONIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Dragon-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .iconPic = gItemIcon_DragoniumZ,
        .iconPalette = gItemIconPalette_DragoniumZ,
    },

    [ITEM_DARKINIUM_Z] =
    {
        .name = ITEM_NAME("DARKINIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Dark-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .iconPic = gItemIcon_DarkiniumZ,
        .iconPalette = gItemIconPalette_DarkiniumZ,
    },

    [ITEM_STEELIUM_Z] =
    {
        .name = ITEM_NAME("STEELIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Steel-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_STEEL,
        .iconPic = gItemIcon_SteeliumZ,
        .iconPalette = gItemIconPalette_SteeliumZ,
    },

    [ITEM_FAIRIUM_Z] =
    {
        .name = ITEM_NAME("FAIRIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Fairy-\n"
            "type moves into\n"
            "Z-Moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .iconPic = gItemIcon_FairiumZ,
        .iconPalette = gItemIconPalette_FairiumZ,
    },

    [ITEM_PIKANIUM_Z] =
    {
        .name = ITEM_NAME("PIKANIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Pikachu's\n"
            "Volt Tackle\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_PikaniumZ,
        .iconPalette = gItemIconPalette_PikaniumZ,
    },

    [ITEM_EEVIUM_Z] =
    {
        .name = ITEM_NAME("EEVIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Eevee's\n"
            "Last Resort\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_EeviumZ,
        .iconPalette = gItemIconPalette_EeviumZ,
    },

    [ITEM_SNORLIUM_Z] =
    {
        .name = ITEM_NAME("SNORLIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Snorlax's\n"
            "Giga Impact\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_SnorliumZ,
        .iconPalette = gItemIconPalette_SnorliumZ,
    },

    [ITEM_MEWNIUM_Z] =
    {
        .name = ITEM_NAME("MEWNIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Mew's\n"
            "Psychic into\n"
            "a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_MewniumZ,
        .iconPalette = gItemIconPalette_MewniumZ,
    },

    [ITEM_DECIDIUM_Z] =
    {
        .name = ITEM_NAME("DECIDIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Decidu-\n"
            "eye's Spirit Sha-\n"
            "ckle into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_DecidiumZ,
        .iconPalette = gItemIconPalette_DecidiumZ,
    },

    [ITEM_INCINIUM_Z] =
    {
        .name = ITEM_NAME("INCINIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Incine-\n"
            "roar's Darkest La-\n"
            "riat into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_InciniumZ,
        .iconPalette = gItemIconPalette_InciniumZ,
    },

    [ITEM_PRIMARIUM_Z] =
    {
        .name = ITEM_NAME("PRIMARIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Primarina's\n"
            "Sparkling Aria\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_PrimariumZ,
        .iconPalette = gItemIconPalette_PrimariumZ,
    },

    [ITEM_LYCANIUM_Z] =
    {
        .name = ITEM_NAME("LYCANIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Lycanroc's\n"
            "Stone Edge\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_LycaniumZ,
        .iconPalette = gItemIconPalette_LycaniumZ,
    },

    [ITEM_MIMIKIUM_Z] =
    {
        .name = ITEM_NAME("MIMIKIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Mimikyu's\n"
            "Play Rough\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_MimikiumZ,
        .iconPalette = gItemIconPalette_MimikiumZ,
    },

    [ITEM_KOMMONIUM_Z] =
    {
        .name = ITEM_NAME("KOMMONIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Kommo-o's\n"
            "Clanging Scales\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_KommoniumZ,
        .iconPalette = gItemIconPalette_KommoniumZ,
    },

    [ITEM_TAPUNIUM_Z] =
    {
        .name = ITEM_NAME("TAPUNIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade the tapus'\n"
            "Nature's Madness\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  //signature z move
        .iconPic = gItemIcon_TapuniumZ,
        .iconPalette = gItemIconPalette_TapuniumZ,
    },

    [ITEM_SOLGANIUM_Z] =
    {
        .name = ITEM_NAME("SOLGANIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Solgaleo's\n"
            "Sunsteel Strike\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_SolganiumZ,
        .iconPalette = gItemIconPalette_SolganiumZ,
    },

    [ITEM_LUNALIUM_Z] =
    {
        .name = ITEM_NAME("LUNALIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Lunala's\n"
            "Moongeist Beam\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_LunaliumZ,
        .iconPalette = gItemIconPalette_LunaliumZ,
    },

    [ITEM_MARSHADIUM_Z] =
    {
        .name = ITEM_NAME("MARSHADIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Marsha-\n"
            "dow's Spectral Thi-\n"
            "ef into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_MarshadiumZ,
        .iconPalette = gItemIconPalette_MarshadiumZ,
    },

    [ITEM_ALORAICHIUM_Z] =
    {
        .name = ITEM_NAME("ALORAICHIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Alolan\n"
            "Raichu's Thunder-\n"
            "bolt into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_AloraichiumZ,
        .iconPalette = gItemIconPalette_AloraichiumZ,
    },

    [ITEM_PIKASHUNIUM_Z] =
    {
        .name = ITEM_NAME("PIKASHUNIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "Upgrade Pikachu w/\n"
            "a cap's Thunderbolt\n"
            "into a Z-Move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255,  // signature z move
        .iconPic = gItemIcon_PikashuniumZ,
        .iconPalette = gItemIconPalette_PikashuniumZ,
    },

    [ITEM_ULTRANECROZIUM_Z] =
    {
        .name = ITEM_NAME("ULTRANECROZIUM Z"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_Z_CRYSTAL,
        .description = COMPOUND_STRING(
            "A crystal to turn\n"
            "fused Necrozma\n"
            "into a new form."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_Z_CRYSTAL,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 255, //signature z move
        .iconPic = gItemIcon_UltranecroziumZ,
        .iconPalette = gItemIconPalette_UltranecroziumZ,
    },

// Species-specific Held Items

    [ITEM_LIGHT_BALL] =
    {
        .name = ITEM_NAME("LIGHT BALL"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 100,
        .holdEffect = HOLD_EFFECT_LIGHT_BALL,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the Atk and\n"
            "Sp. Atk of Pikachu."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LightBall,
        .iconPalette = gItemIconPalette_LightBall,
    },

    [ITEM_LEEK] =
    {
        .name = ITEM_NAME("LEEK"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 200,
        .holdEffect = HOLD_EFFECT_LEEK,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Farfetch'd's\n"
            "critical-hit ratio."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_Leek,
        .iconPalette = gItemIconPalette_Leek,
    },

    [ITEM_THICK_CLUB] =
    {
        .name = ITEM_NAME("THICK CLUB"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 500,
        .holdEffect = HOLD_EFFECT_THICK_CLUB,
        .description = COMPOUND_STRING(
            "A hold item that \n"
            "raises Cubone or\n"
            "Marowak's Attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
        .iconPic = gItemIcon_Bone,
        .iconPalette = gItemIconPalette_Bone,
    },

    [ITEM_LUCKY_PUNCH] =
    {
        .name = ITEM_NAME("LUCKY PUNCH"),
        .pluralName = ITEM_PLURAL_NAME("Lucky Punches"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 10,
        .holdEffect = HOLD_EFFECT_LUCKY_PUNCH,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Chansey's\n"
            "critical-hit rate."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
        .iconPic = gItemIcon_LuckyPunch,
        .iconPalette = gItemIconPalette_LuckyPunch,
    },

    [ITEM_METAL_POWDER] =
    {
        .name = ITEM_NAME("METAL POWDER"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 10,
        .holdEffect = HOLD_EFFECT_METAL_POWDER,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Ditto's\n"
            "Defense."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DittoPowder,
        .iconPalette = gItemIconPalette_MetalPowder,
    },

    [ITEM_QUICK_POWDER] =
    {
        .name = ITEM_NAME("QUICK POWDER"),
        .price = (I_PRICE >= GEN_7) ? 1000 : 10,
        .holdEffect = HOLD_EFFECT_QUICK_POWDER,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the Speed\n"
            "of Ditto."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DittoPowder,
        .iconPalette = gItemIconPalette_QuickPowder,
    },

    [ITEM_DEEP_SEA_SCALE] =
    {
        .name = ITEM_NAME("DEEP SEA SCALE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 200,
        .holdEffect = HOLD_EFFECT_DEEP_SEA_SCALE,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the Sp. Def\n"
            "of Clamperl."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_DeepSeaScale,
        .iconPalette = gItemIconPalette_DeepSeaScale,
    },

    [ITEM_DEEP_SEA_TOOTH] =
    {
        .name = ITEM_NAME("DEEP SEA TOOTH"),
        .pluralName = ITEM_PLURAL_NAME("Deep Sea Teeth"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 200,
        .holdEffect = HOLD_EFFECT_DEEP_SEA_TOOTH,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the Sp. Atk\n"
            "of Clamperl."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 90,
        .iconPic = gItemIcon_DeepSeaTooth,
        .iconPalette = gItemIconPalette_DeepSeaTooth,
    },

    [ITEM_SOUL_DEW] =
    {
        .name = ITEM_NAME("SOUL DEW"),
        .price = (I_PRICE >= GEN_7) ? 0 : 200,
        .holdEffect = HOLD_EFFECT_SOUL_DEW,
        .holdEffectParam = B_SOUL_DEW_BOOST >= GEN_7 ? 20 : 50,
        .description = COMPOUND_STRING(
        #if B_SOUL_DEW_BOOST >= GEN_7
            "Powers up Latios' &\n"
            "Latias' Psychic and\n"
            "Dragon-type moves."),
        #else
            "Hold item: raises\n"
            "Sp. Atk & Sp. Def of\n"
            "Latios & Latias."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_SoulDew,
        .iconPalette = gItemIconPalette_SoulDew,
    },

    [ITEM_ADAMANT_ORB] =
    {
        .name = ITEM_NAME("ADAMANT ORB"),
        .price = (I_PRICE >= GEN_7) ? 0 : 10000,
        .holdEffect = HOLD_EFFECT_ADAMANT_ORB,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Powers up Dialga's\n"
            "Dragon and Steel-\n"
            "type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_AdamantOrb,
        .iconPalette = gItemIconPalette_AdamantOrb,
    },

    [ITEM_LUSTROUS_ORB] =
    {
        .name = ITEM_NAME("LUSTROUS ORB"),
        .price = (I_PRICE >= GEN_7) ? 0 : 10000,
        .holdEffect = HOLD_EFFECT_LUSTROUS_ORB,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Powers up Palkia's\n"
            "Dragon and Water-\n"
            "type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_LustrousOrb,
        .iconPalette = gItemIconPalette_LustrousOrb,
    },

    [ITEM_GRISEOUS_ORB] =
    {
        .name = ITEM_NAME("GRISEOUS ORB"),
        .price = (I_PRICE >= GEN_7) ? 0 : 10000,
        .holdEffect = HOLD_EFFECT_GRISEOUS_ORB,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Boosts Giratina's\n"
            "Dragon and Ghost-\n"
            "type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_GriseousOrb,
        .iconPalette = gItemIconPalette_GriseousOrb,
    },

// Incenses

    [ITEM_SEA_INCENSE] =
    {
        .name = ITEM_NAME("SEA INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = I_TYPE_BOOST_POWER >= GEN_4 ? 20 : 5,
        .description = sSeaIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 10,
        .iconPic = gItemIcon_SeaIncense,
        .iconPalette = gItemIconPalette_SeaIncense,
    },

    [ITEM_LAX_INCENSE] =
    {
        .name = ITEM_NAME("LAX INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 5000 : 9600,
        .holdEffect = HOLD_EFFECT_EVASION_UP,
    #if I_LAX_INCENSE_BOOST >= GEN_4
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "lowers the\n"
            "foe's accuracy."),
    #else
        .holdEffectParam = 5,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "slightly lowers the\n"
            "foe's accuracy."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LaxIncense,
        .iconPalette = gItemIconPalette_LaxIncense,
    },

    [ITEM_ODD_INCENSE] =
    {
        .name = ITEM_NAME("ODD INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = sOddIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 10,
        .iconPic = gItemIcon_OddIncense,
        .iconPalette = gItemIconPalette_OddIncense,
    },

    [ITEM_ROCK_INCENSE] =
    {
        .name = ITEM_NAME("ROCK INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = sRockIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 10,
        .iconPic = gItemIcon_RockIncense,
        .iconPalette = gItemIconPalette_RockIncense,
    },

    [ITEM_FULL_INCENSE] =
    {
        .name = ITEM_NAME("FULL INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 5000 : 9600,
        .holdEffect = HOLD_EFFECT_LAGGING_TAIL,
        .holdEffectParam = 5,
        .description = sFullIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FullIncense,
        .iconPalette = gItemIconPalette_FullIncense,
    },

    [ITEM_WAVE_INCENSE] =
    {
        .name = ITEM_NAME("WAVE INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = sSeaIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 10,
        .iconPic = gItemIcon_WaveIncense,
        .iconPalette = gItemIconPalette_WaveIncense,
    },

    [ITEM_ROSE_INCENSE] =
    {
        .name = ITEM_NAME("ROSE INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 2000 : 9600,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = 20,
        .description = sRoseIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 10,
        .iconPic = gItemIcon_RoseIncense,
        .iconPalette = gItemIconPalette_RoseIncense,
    },

    [ITEM_LUCK_INCENSE] =
    {
        .name = ITEM_NAME("LUCK INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 11000 : 9600,
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .description = sLuckIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LuckIncense,
        .iconPalette = gItemIconPalette_LuckIncense,
    },

    [ITEM_PURE_INCENSE] =
    {
        .name = ITEM_NAME("PURE INCENSE"),
        .price = (I_PRICE >= GEN_7) ? 6000 : 9600,
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = sPureIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_INCENSE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PureIncense,
        .iconPalette = gItemIconPalette_PureIncense,
    },

// Contest Scarves

    [ITEM_RED_SCARF] =
    {
        .name = ITEM_NAME("RED SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Red Scarves"),
        .price = 100,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Cool in\n"
            "Contests."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_RedScarf,
    },

    [ITEM_BLUE_SCARF] =
    {
        .name = ITEM_NAME("BLUE SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Blue Scarves"),
        .price = 100,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Beauty in\n"
            "Contests."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_BlueScarf,
    },

    [ITEM_PINK_SCARF] =
    {
        .name = ITEM_NAME("PINK SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Pink Scarves"),
        .price = 100,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Cute in\n"
            "Contests."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_PinkScarf,
    },

    [ITEM_GREEN_SCARF] =
    {
        .name = ITEM_NAME("GREEN SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Green Scarves"),
        .price = 100,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Smart in\n"
            "Contests."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_GreenScarf,
    },

    [ITEM_YELLOW_SCARF] =
    {
        .name = ITEM_NAME("YELLOW SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Yellow Scarves"),
        .price = 100,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Tough in\n"
            "Contests."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_CONTEST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Scarf,
        .iconPalette = gItemIconPalette_YellowScarf,
    },

// EV Gain Modifiers

    [ITEM_MACHO_BRACE] =
    {
        .name = ITEM_NAME("MACHO BRACE"),
        .price = 3000,
        .holdEffect = HOLD_EFFECT_MACHO_BRACE,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "promotes growth,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_MachoBrace,
        .iconPalette = gItemIconPalette_MachoBrace,
    },

    [ITEM_POWER_WEIGHT] =
    {
        .name = ITEM_NAME("POWER WEIGHT"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "promotes HP gain,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_HP,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerWeight,
        .iconPalette = gItemIconPalette_PowerWeight,
    },

    [ITEM_POWER_BRACER] =
    {
        .name = ITEM_NAME("POWER BRACER"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "promotes Atk gain,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_ATK,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerBracer,
        .iconPalette = gItemIconPalette_PowerBracer,
    },

    [ITEM_POWER_BELT] =
    {
        .name = ITEM_NAME("POWER BELT"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "promotes Def gain,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_DEF,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerBelt,
        .iconPalette = gItemIconPalette_PowerBelt,
    },

    [ITEM_POWER_LENS] =
    {
        .name = ITEM_NAME("POWER LENS"),
        .pluralName = ITEM_PLURAL_NAME("Power Lenses"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = COMPOUND_STRING(
            "Hold item that pro-\n"
            "motes Sp. Atk gain,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPATK,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerLens,
        .iconPalette = gItemIconPalette_PowerLens,
    },

    [ITEM_POWER_BAND] =
    {
        .name = ITEM_NAME("POWER BAND"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = COMPOUND_STRING(
            "Hold item that pro-\n"
            "motes Sp. Def gain,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPDEF,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerBand,
        .iconPalette = gItemIconPalette_PowerBand,
    },

    [ITEM_POWER_ANKLET] =
    {
        .name = ITEM_NAME("POWER ANKLET"),
        .price = (I_PRICE >= GEN_9) ? 10000 : 3000,
        .holdEffect = HOLD_EFFECT_POWER_ITEM,
        .holdEffectParam = POWER_ITEM_BOOST,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "promotes Spd gain,\n"
            "but reduces Speed."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EV_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = STAT_SPEED,
        .flingPower = 70,
        .iconPic = gItemIcon_PowerAnklet,
        .iconPalette = gItemIconPalette_PowerAnklet,
    },

// Type-boosting Held Items
    #if I_PRICE >= GEN_9
        #define TYPE_BOOSTING_PRICE 3000
    #elif I_PRICE >= GEN_7
        #define TYPE_BOOSTING_PRICE 1000
    #else
        #define TYPE_BOOSTING_PRICE 100
    #endif

    [ITEM_SILK_SCARF] =
    {
        .name = ITEM_NAME("SILK SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Silk Scarves"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Normal-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_NORMAL,
        .flingPower = 10,
        .iconPic = gItemIcon_SilkScarf,
        .iconPalette = gItemIconPalette_SilkScarf,
    },

    [ITEM_CHARCOAL] =
    {
        .name = ITEM_NAME("CHARCOAL"),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 1000,
    #else
        .price = 9800,
    #endif
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Fire-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIRE,
        .flingPower = 30,
        .iconPic = gItemIcon_Charcoal,
        .iconPalette = gItemIconPalette_Charcoal,
    },

    [ITEM_MYSTIC_WATER] =
    {
        .name = ITEM_NAME("MYSTIC WATER"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Water-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_WATER,
        .flingPower = 30,
        .iconPic = gItemIcon_MysticWater,
        .iconPalette = gItemIconPalette_MysticWater,
    },

    [ITEM_MAGNET] =
    {
        .name = ITEM_NAME("MAGNET"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "boosts Electric-\n"
            "type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ELECTRIC,
        .flingPower = 30,
        .iconPic = gItemIcon_Magnet,
        .iconPalette = gItemIconPalette_Magnet,
    },

    [ITEM_MIRACLE_SEED] =
    {
        .name = ITEM_NAME("MIRACLE SEED"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = sRoseIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GRASS,
        .flingPower = 30,
        .iconPic = gItemIcon_MiracleSeed,
        .iconPalette = gItemIconPalette_MiracleSeed,
    },

    [ITEM_NEVER_MELT_ICE] =
    {
        .name = ITEM_NAME("NEVER-MELT ICE"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Ice-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ICE,
        .flingPower = 30,
        .iconPic = gItemIcon_NeverMeltIce,
        .iconPalette = gItemIconPalette_NeverMeltIce,
    },

    [ITEM_BLACK_BELT] =
    {
        .name = ITEM_NAME("BLACK BELT"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "boosts Fighting-\n"
            "type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FIGHTING,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackBelt,
        .iconPalette = gItemIconPalette_BlackTypeEnhancingItem,
    },

    [ITEM_POISON_BARB] =
    {
        .name = ITEM_NAME("POISON BARB"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Poison-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_POISON,
        .flingPower = 70,
        .iconPic = gItemIcon_PoisonBarb,
        .iconPalette = gItemIconPalette_PoisonBarb,
    },

    [ITEM_SOFT_SAND] =
    {
        .name = ITEM_NAME("SOFT SAND"),
        .pluralName = ITEM_PLURAL_NAME("Soft Sand"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Ground-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GROUND,
        .flingPower = 10,
        .iconPic = gItemIcon_Sand,
        .iconPalette = gItemIconPalette_SoftSand,
    },

    [ITEM_SHARP_BEAK] =
    {
        .name = ITEM_NAME("SHARP BEAK"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Flying-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FLYING,
        .flingPower = 50,
        .iconPic = gItemIcon_SharpBeak,
        .iconPalette = gItemIconPalette_SharpBeak,
    },

    [ITEM_TWISTED_SPOON] =
    {
        .name = ITEM_NAME("TWISTED SPOON"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = sOddIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_PSYCHIC,
        .flingPower = 30,
        .iconPic = gItemIcon_TwistedSpoon,
        .iconPalette = gItemIconPalette_TwistedSpoon,
    },

    [ITEM_SILVER_POWDER] =
    {
        .name = ITEM_NAME("SILVER POWDER"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Bug-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_BUG,
        .flingPower = 10,
        .iconPic = gItemIcon_SilverPowder,
        .iconPalette = gItemIconPalette_SilverPowder,
    },

    [ITEM_HARD_STONE] =
    {
        .name = ITEM_NAME("HARD STONE"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = sRockIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_ROCK,
        .flingPower = 100,
        .iconPic = gItemIcon_HardStone,
        .iconPalette = gItemIconPalette_HardStone,
    },

    [ITEM_SPELL_TAG] =
    {
        .name = ITEM_NAME("SPELL TAG"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Ghost-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_GHOST,
        .flingPower = 30,
        .iconPic = gItemIcon_SpellTag,
        .iconPalette = gItemIconPalette_SpellTag,
    },

    [ITEM_DRAGON_FANG] =
    {
        .name = ITEM_NAME("DRAGON FANG"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Dragon-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DRAGON,
        .flingPower = 70,
        .iconPic = gItemIcon_DragonFang,
        .iconPalette = gItemIconPalette_DragonFang,
    },

    [ITEM_BLACK_GLASSES] =
    {
        .name = ITEM_NAME("BLACK GLASSES"),
        .pluralName = ITEM_PLURAL_NAME("Black Glasses"),
        .price = TYPE_BOOSTING_PRICE,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Dark-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_DARK,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackGlasses,
        .iconPalette = gItemIconPalette_BlackTypeEnhancingItem,
    },

    [ITEM_METAL_COAT] =
    {
        .name = ITEM_NAME("METAL COAT"),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 2000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Steel-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .secondaryId = TYPE_STEEL,
        .flingPower = 30,
        .iconPic = gItemIcon_MetalCoat,
        .iconPalette = gItemIconPalette_MetalCoat,
    },

// Choice Items

    [ITEM_CHOICE_BAND] =
    {
        .name = ITEM_NAME("CHOICE BAND"),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_CHOICE_BAND,
        .description = COMPOUND_STRING(
            "Boosts Attack, but\n"
            "allows the use of\n"
            "only one move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChoiceBand,
        .iconPalette = gItemIconPalette_ChoiceBand,
    },

    [ITEM_CHOICE_SPECS] =
    {
        .name = ITEM_NAME("CHOICE SPECS"),
        .pluralName = ITEM_PLURAL_NAME("Choice Specs"),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_CHOICE_SPECS,
        .description = COMPOUND_STRING(
            "Boosts Sp. Atk, but\n"
            "allows the use of\n"
            "only one move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChoiceSpecs,
        .iconPalette = gItemIconPalette_ChoiceSpecs,
    },

    [ITEM_CHOICE_SCARF] =
    {
        .name = ITEM_NAME("CHOICE SCARF"),
        .pluralName = ITEM_PLURAL_NAME("Choice Scarves"),
    #if I_PRICE >= GEN_9
        .price = 100000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_CHOICE_SCARF,
        .description = COMPOUND_STRING(
            "Boosts Speed, but\n"
            "allows the use of\n"
            "only one move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChoiceScarf,
        .iconPalette = gItemIconPalette_ChoiceScarf,
    },

// Status Orbs

    [ITEM_FLAME_ORB] =
    {
        .name = ITEM_NAME("FLAME ORB"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FLAME_ORB,
        .description = COMPOUND_STRING(
            "A bizarre orb that\n"
            "inflicts a burn on\n"
            "holder in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_FlameOrb,
        .iconPalette = gItemIconPalette_FlameOrb,
    },

    [ITEM_TOXIC_ORB] =
    {
        .name = ITEM_NAME("TOXIC ORB"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_TOXIC_ORB,
        .description = COMPOUND_STRING(
            "A bizarre orb that\n"
            "badly poisons the\n"
            "holder in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ToxicOrb,
        .iconPalette = gItemIconPalette_ToxicOrb,
    },

// Weather Rocks

    [ITEM_DAMP_ROCK] =
    {
        .name = ITEM_NAME("DAMP ROCK"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_DAMP_ROCK,
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of Rain Dance if\n"
            "used by the holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_DampRock,
        .iconPalette = gItemIconPalette_DampRock,
    },

    [ITEM_HEAT_ROCK] =
    {
        .name = ITEM_NAME("HEAT ROCK"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_HEAT_ROCK,
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of Sunny Day if\n"
            "used by the holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_HeatRock,
        .iconPalette = gItemIconPalette_HeatRock,
    },

    [ITEM_SMOOTH_ROCK] =
    {
        .name = ITEM_NAME("SMOOTH ROCK"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_SMOOTH_ROCK,
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of Sandstorm if\n"
            "used by the holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SmoothRock,
        .iconPalette = gItemIconPalette_SmoothRock,
    },

    [ITEM_ICY_ROCK] =
    {
        .name = ITEM_NAME("ICY ROCK"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ICY_ROCK,
    #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_HAIL
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of the move Hail\n"
            "used by the holder."),
    #elif B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of Snowscape if\n"
            "used by the holder."),
    #else
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of cold weathers\n"
            "used by the holder."),
    #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
        .iconPic = gItemIcon_IcyRock,
        .iconPalette = gItemIconPalette_IcyRock,
    },

// Terrain Seeds

    [ITEM_ELECTRIC_SEED] =
    {
        .name = ITEM_NAME("ELECTRIC SEED"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_ELECTRIC_TERRAIN,
        .description = COMPOUND_STRING(
            "Boosts Defense on\n"
            "Electric Terrain,\n"
            "but only one time."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_ElectricSeed,
    },

    [ITEM_PSYCHIC_SEED] =
    {
        .name = ITEM_NAME("PSYCHIC SEED"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_PSYCHIC_TERRAIN,
        .description = COMPOUND_STRING(
            "Boosts Sp. Def. on\n"
            "Psychic Terrain,\n"
            "but only one time."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_PsychicSeed,
    },

    [ITEM_MISTY_SEED] =
    {
        .name = ITEM_NAME("MISTY SEED"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_MISTY_TERRAIN,
        .description = COMPOUND_STRING(
            "Boosts Sp. Def. on\n"
            "Misty Terrain,\n"
            "but only one time."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_MistySeed,
    },

    [ITEM_GRASSY_SEED] =
    {
        .name = ITEM_NAME("GRASSY SEED"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_SEED,
        .holdEffectParam = HOLD_EFFECT_PARAM_GRASSY_TERRAIN,
        .description = COMPOUND_STRING(
            "Boosts Defense on\n"
            "Grassy Terrain,\n"
            "but only one time."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TerrainSeed,
        .iconPalette = gItemIconPalette_GrassySeed,
    },

// Type-activated Stat Modifiers

    [ITEM_ABSORB_BULB] =
    {
        .name = ITEM_NAME("ABSORB BULB"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ABSORB_BULB,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Raises Sp. Atk if\n"
            "the holder is hit by\n"
            "a Water-type move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AbsorbBulb,
        .iconPalette = gItemIconPalette_AbsorbBulb,
    },

    [ITEM_CELL_BATTERY] =
    {
        .name = ITEM_NAME("CELL BATTERY"),
        .pluralName = ITEM_PLURAL_NAME("Cell Batteries"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_CELL_BATTERY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Raises Attack if\n"
            "the holder is hit by\n"
            "an Electric move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_CellBattery,
        .iconPalette = gItemIconPalette_CellBattery,
    },

    [ITEM_LUMINOUS_MOSS] =
    {
        .name = ITEM_NAME("LUMINOUS MOSS"),
        .pluralName = ITEM_PLURAL_NAME("Luminous Moss"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 1000,
    #endif
        .holdEffect = HOLD_EFFECT_LUMINOUS_MOSS,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Raises Sp. Def if\n"
            "the holder is hit by\n"
            "a Water-type move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LuminousMoss,
        .iconPalette = gItemIconPalette_LuminousMoss,
    },

    [ITEM_SNOWBALL] =
    {
        .name = ITEM_NAME("SNOWBALL"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_SNOWBALL,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Raises Atk if its\n"
            "holder is hit by an\n"
            "Ice-type move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Snowball,
        .iconPalette = gItemIconPalette_Snowball,
    },

// Misc. Held Items

    [ITEM_BRIGHT_POWDER] =
    {
        .name = ITEM_NAME("BRIGHT POWDER"),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 10,
    #endif
        .holdEffect = HOLD_EFFECT_EVASION_UP,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "casts a glare to\n"
            "reduce accuracy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BrightPowder,
        .iconPalette = gItemIconPalette_BrightPowder,
    },

    [ITEM_WHITE_HERB] =
    {
        .name = ITEM_NAME("WHITE HERB"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_WHITE_HERB,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "restores any\n"
            "lowered stat."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_InBattleHerb,
        .iconPalette = gItemIconPalette_WhiteHerb,
    },

    [ITEM_EXP_SHARE] =
    {
        .name = ITEM_NAME("EXP. SHARE"),
        .holdEffect = HOLD_EFFECT_EXP_SHARE,
    #if I_EXP_SHARE_ITEM >= GEN_6
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "This device gives\n"
            "exp. to other\n"
            "party members."),
        .pocket = POCKET_KEY_ITEMS,
    #else
        .price = (I_PRICE == GEN_1) ? 1 : 3000,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "gets Exp. points\n"
            "from battles."),
        .pocket = POCKET_ITEMS,
    #endif
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_ExpShare,
        .flingPower = 30,
        .iconPic = gItemIcon_ExpShare,
        .iconPalette = gItemIconPalette_ExpShare,
    },

    [ITEM_QUICK_CLAW] =
    {
        .name = ITEM_NAME("QUICK CLAW"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_QUICK_CLAW,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "occasionally allows\n"
            "the first strike."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_QuickClaw,
        .iconPalette = gItemIconPalette_QuickClaw,
    },

    [ITEM_SOOTHE_BELL] =
    {
        .name = ITEM_NAME("SOOTHE BELL"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_FRIENDSHIP_UP,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "calms spirits and\n"
            "fosters friendship."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SootheBell,
        .iconPalette = gItemIconPalette_SootheBell,
    },

    [ITEM_MENTAL_HERB] =
    {
        .name = ITEM_NAME("MENTAL HERB"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_MENTAL_HERB,
        .description = COMPOUND_STRING(
        #if B_MENTAL_HERB >= GEN_5
            "Snaps Pokémon out\n"
            "of move-binding\n"
            "effects."),
        #else
            "A hold item that\n"
            "snaps Pokémon out\n"
            "of infatuation."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_InBattleHerb,
        .iconPalette = gItemIconPalette_MentalHerb,
    },

    [ITEM_KINGS_ROCK] =
    {
        .name = ITEM_NAME("KING'S ROCK"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 5000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .description = sKingsRockDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_KingsRock,
        .iconPalette = gItemIconPalette_KingsRock,
    },

    [ITEM_AMULET_COIN] =
    {
        .name = ITEM_NAME("AMULET COIN"),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 10000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_DOUBLE_PRIZE,
        .description = sLuckIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AmuletCoin,
        .iconPalette = gItemIconPalette_AmuletCoin,
    },

    [ITEM_CLEANSE_TAG] =
    {
        .name = ITEM_NAME("CLEANSE TAG"),
        .price = (I_PRICE >= GEN_7) ? 5000 : 200,
        .holdEffect = HOLD_EFFECT_REPEL,
        .description = sPureIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_CleanseTag,
        .iconPalette = gItemIconPalette_CleanseTag,
    },

    [ITEM_SMOKE_BALL] =
    {
        .name = ITEM_NAME("SMOKE BALL"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_CAN_ALWAYS_RUN,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "assures fleeing\n"
            "from wild Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_SmokeBall,
        .iconPalette = gItemIconPalette_SmokeBall,
    },

    [ITEM_FOCUS_BAND] =
    {
        .name = ITEM_NAME("FOCUS BAND"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FOCUS_BAND,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "occasionally\n"
            "prevents fainting."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FocusBand,
        .iconPalette = gItemIconPalette_FocusBand,
    },

    [ITEM_LUCKY_EGG] =
    {
        .name = ITEM_NAME("LUCKY EGG"),
        .price = (I_PRICE >= GEN_7) ? 10000 : 200,
        .holdEffect = HOLD_EFFECT_LUCKY_EGG,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "boosts Exp. points\n"
            "earned in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LuckyEgg,
        .iconPalette = gItemIconPalette_LuckyEgg,
    },

    [ITEM_SCOPE_LENS] =
    {
        .name = ITEM_NAME("SCOPE LENS"),
        .pluralName = ITEM_PLURAL_NAME("Scope Lenses"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "improves the\n"
            "critical-hit rate."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ScopeLens,
        .iconPalette = gItemIconPalette_ScopeLens,
    },

    [ITEM_LEFTOVERS] =
    {
        .name = ITEM_NAME("LEFTOVERS"),
        .pluralName = ITEM_PLURAL_NAME("Leftovers"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LEFTOVERS,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "gradually restores\n"
            "HP in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_Leftovers,
        .iconPalette = gItemIconPalette_Leftovers,
    },

    [ITEM_SHELL_BELL] =
    {
        .name = ITEM_NAME("SHELL BELL"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_SHELL_BELL,
        .holdEffectParam = 8,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "restores HP upon\n"
            "striking the foe."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ShellBell,
        .iconPalette = gItemIconPalette_Shell,
    },

    [ITEM_WIDE_LENS] =
    {
        .name = ITEM_NAME("WIDE LENS"),
        .pluralName = ITEM_PLURAL_NAME("Wide Lenses"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_WIDE_LENS,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A magnifying lens\n"
            "that boosts the\n"
            "accuracy of moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WideLens,
        .iconPalette = gItemIconPalette_WideLens,
    },

    [ITEM_MUSCLE_BAND] =
    {
        .name = ITEM_NAME("MUSCLE BAND"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_MUSCLE_BAND,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A headband that\n"
            "boosts the power\n"
            "of physical moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MuscleBand,
        .iconPalette = gItemIconPalette_MuscleBand,
    },

    [ITEM_WISE_GLASSES] =
    {
        .name = ITEM_NAME("WISE GLASSES"),
        .pluralName = ITEM_PLURAL_NAME("Wise Glasses"),
    #if I_PRICE >= GEN_9
        .price = 8000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_WISE_GLASSES,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A pair of glasses\n"
            "that ups the power\n"
            "of special moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WiseGlasses,
        .iconPalette = gItemIconPalette_WiseGlasses,
    },

    [ITEM_EXPERT_BELT] =
    {
        .name = ITEM_NAME("EXPERT BELT"),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_EXPERT_BELT,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A belt that boosts\n"
            "the power of super\n"
            "effective moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ExpertBelt,
        .iconPalette = gItemIconPalette_ExpertBelt,
    },

    [ITEM_LIGHT_CLAY] =
    {
        .name = ITEM_NAME("LIGHT CLAY"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LIGHT_CLAY,
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of barrier moves\n"
            "used by the holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LightClay,
        .iconPalette = gItemIconPalette_LightClay,
    },

    [ITEM_LIFE_ORB] =
    {
        .name = ITEM_NAME("LIFE ORB"),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LIFE_ORB,
        .description = COMPOUND_STRING(
            "Boosts move power\n"
            "but holder loses HP\n"
            "with each attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LifeOrb,
        .iconPalette = gItemIconPalette_LifeOrb,
    },

    [ITEM_POWER_HERB] =
    {
        .name = ITEM_NAME("POWER HERB"),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_POWER_HERB,
        .description = COMPOUND_STRING(
            "Allows immediate\n"
            "use of a move that\n"
            "charges first."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PowerHerb,
        .iconPalette = gItemIconPalette_PowerHerb,
    },

    [ITEM_FOCUS_SASH] =
    {
        .name = ITEM_NAME("FOCUS SASH"),
        .pluralName = ITEM_PLURAL_NAME("Focus Sashes"),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FOCUS_SASH,
        .description = COMPOUND_STRING(
            "If the holder has\n"
            "full HP, it endures\n"
            "KO hits with 1 HP."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FocusSash,
        .iconPalette = gItemIconPalette_FocusSash,
    },

    [ITEM_ZOOM_LENS] =
    {
        .name = ITEM_NAME("ZOOM LENS"),
        .pluralName = ITEM_PLURAL_NAME("Zoom Lenses"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ZOOM_LENS,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "If the holder moves\n"
            "after the foe, it'll\n"
            "boost accuracy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ZoomLens,
        .iconPalette = gItemIconPalette_ZoomLens,
    },

    [ITEM_METRONOME] =
    {
        .name = ITEM_NAME("METRONOME"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_METRONOME,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A held item that\n"
            "boosts a move used\n"
            "consecutively."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_Metronome,
        .iconPalette = gItemIconPalette_Metronome,
    },

    [ITEM_IRON_BALL] =
    {
        .name = ITEM_NAME("IRON BALL"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_IRON_BALL,
        .description = COMPOUND_STRING(
            "Cuts Speed and\n"
            "becomes vulnerable\n"
            "to Ground moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 130,
        .iconPic = gItemIcon_IronBall,
        .iconPalette = gItemIconPalette_IronBall,
    },

    [ITEM_LAGGING_TAIL] =
    {
        .name = ITEM_NAME("LAGGING TAIL"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_LAGGING_TAIL,
        .description = sFullIncenseDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LaggingTail,
        .iconPalette = gItemIconPalette_LaggingTail,
    },

    [ITEM_DESTINY_KNOT] =
    {
        .name = ITEM_NAME("DESTINY KNOT"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_DESTINY_KNOT,
        .description = COMPOUND_STRING(
            "If the holder falls\n"
            "in love, the foe\n"
            "does too."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DestinyKnot,
        .iconPalette = gItemIconPalette_DestinyKnot,
    },

    [ITEM_BLACK_SLUDGE] =
    {
        .name = ITEM_NAME("BLACK SLUDGE"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_BLACK_SLUDGE,
        .description = COMPOUND_STRING(
            "Restores HP for\n"
            "Poison-types.\n"
            "Damages all others."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackSludge,
        .iconPalette = gItemIconPalette_BlackSludge,
    },

    [ITEM_GRIP_CLAW] =
    {
        .name = ITEM_NAME("GRIP CLAW"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_GRIP_CLAW,
        .description = COMPOUND_STRING(
            "A held item that\n"
            "extends binding\n"
            "moves like Wrap."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 90,
        .iconPic = gItemIcon_GripClaw,
        .iconPalette = gItemIconPalette_GripClaw,
    },

    [ITEM_STICKY_BARB] =
    {
        .name = ITEM_NAME("STICKY BARB"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_STICKY_BARB,
        .description = COMPOUND_STRING(
            "Damages the holder\n"
            "each turn. May\n"
            "latch on to foes."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_StickyBarb,
        .iconPalette = gItemIconPalette_StickyBarb,
    },

    [ITEM_SHED_SHELL] =
    {
        .name = ITEM_NAME("SHED SHELL"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 100,
    #endif
        .holdEffect = HOLD_EFFECT_SHED_SHELL,
        .description = COMPOUND_STRING(
            "Allows the holder\n"
            "to switch out\n"
            "without fail."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ShedShell,
        .iconPalette = gItemIconPalette_ShedShell,
    },

    [ITEM_BIG_ROOT] =
    {
        .name = ITEM_NAME("BIG ROOT"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_BIG_ROOT,
        .holdEffectParam = 30,
        .description = COMPOUND_STRING(
            "A held item that\n"
            "ups the power of\n"
            "HP-stealing moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BigRoot,
        .iconPalette = gItemIconPalette_BigRoot,
    },

    [ITEM_RAZOR_CLAW] =
    {
        .name = ITEM_NAME("RAZOR CLAW"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 5000,
    #else
        .price = 2100,
    #endif
        .holdEffect = HOLD_EFFECT_SCOPE_LENS,
        .description = COMPOUND_STRING(
            "A hooked claw that\n"
            "ups the holder's\n"
            "critical-hit ratio."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_RazorClaw,
        .iconPalette = gItemIconPalette_RazorClaw,
    },

    [ITEM_RAZOR_FANG] =
    {
        .name = ITEM_NAME("RAZOR FANG"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 5000,
    #else
        .price = 2100,
    #endif
        .holdEffect = HOLD_EFFECT_FLINCH,
        .holdEffectParam = 10,
        .description = sKingsRockDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = EVO_HELD_ITEM_TYPE,
        .fieldUseFunc = EVO_HELD_ITEM_FIELD_FUNC,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_RazorFang,
        .iconPalette = gItemIconPalette_RazorFang,
    },

    [ITEM_EVIOLITE] =
    {
        .name = ITEM_NAME("EVIOLITE"),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_EVIOLITE,
        .holdEffectParam = 50,
        .description = COMPOUND_STRING(
            "Raises the Def and\n"
            "Sp. Def of Pokémon\n"
            "that can evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 40,
        .iconPic = gItemIcon_Eviolite,
        .iconPalette = gItemIconPalette_Eviolite,
    },

    [ITEM_FLOAT_STONE] =
    {
        .name = ITEM_NAME("FLOAT STONE"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_FLOAT_STONE,
        .description = COMPOUND_STRING(
            "It's so light that\n"
            "when held, it halves\n"
            "a Pokémon's weight."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_FloatStone,
        .iconPalette = gItemIconPalette_FloatStone,
    },

    [ITEM_ROCKY_HELMET] =
    {
        .name = ITEM_NAME("ROCKY HELMET"),
    #if I_PRICE >= GEN_9
        .price = 50000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_ROCKY_HELMET,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Hurts the foe if\n"
            "they touch its\n"
            "holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_RockyHelmet,
        .iconPalette = gItemIconPalette_RockyHelmet,
    },

    [ITEM_AIR_BALLOON] =
    {
        .name = ITEM_NAME("AIR BALLOON"),
    #if I_PRICE >= GEN_9
        .price = 15000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_AIR_BALLOON,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Makes the holder\n"
            "float but bursts\n"
            "if hit by an attack."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_AirBalloon,
        .iconPalette = gItemIconPalette_AirBalloon,
    },

    [ITEM_RED_CARD] =
    {
        .name = ITEM_NAME("RED CARD"),
    #if I_PRICE >= GEN_9
        .price = 3000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_RED_CARD,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Switches out the\n"
            "foe if they hit the\n"
            "holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RedCard,
        .iconPalette = gItemIconPalette_RedCard,
    },

    [ITEM_RING_TARGET] =
    {
        .name = ITEM_NAME("RING TARGET"),
    #if I_PRICE >= GEN_9
        .price = 10000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_RING_TARGET,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Moves that usually\n"
            "have no effect will\n"
            "hit the holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RingTarget,
        .iconPalette = gItemIconPalette_RingTarget,
    },

    [ITEM_BINDING_BAND] =
    {
        .name = ITEM_NAME("BINDING BAND"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_BINDING_BAND,
        .description = COMPOUND_STRING(
            "Increases the\n"
            "power of binding\n"
            "moves when held."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BindingBand,
        .iconPalette = gItemIconPalette_BindingBand,
    },

    [ITEM_EJECT_BUTTON] =
    {
        .name = ITEM_NAME("EJECT BUTTON"),
    #if I_PRICE >= GEN_9
        .price = 30000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 200,
    #endif
        .holdEffect = HOLD_EFFECT_EJECT_BUTTON,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "Switches out the\n"
            "user if they're hit\n"
            "by the foe."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_EjectButton,
        .iconPalette = gItemIconPalette_EjectButton,
    },

    [ITEM_WEAKNESS_POLICY] =
    {
        .name = ITEM_NAME("WEAKNESS POLICY"),
        .pluralName = ITEM_PLURAL_NAME("Weakness Policies"),
        .price = (I_PRICE >= GEN_9) ? 50000 : 1000,
        .holdEffect = HOLD_EFFECT_WEAKNESS_POLICY,
        .holdEffectParam = 0,
        .description = COMPOUND_STRING(
            "If hit by a super-\n"
            "effective move,\n"
            "ups Atk and Sp. Atk."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_WeaknessPolicy,
        .iconPalette = gItemIconPalette_WeaknessPolicy,
    },

    [ITEM_ASSAULT_VEST] =
    {
        .name = ITEM_NAME("ASSAULT VEST"),
        .price = (I_PRICE >= GEN_9) ? 50000 : 1000,
        .holdEffect = HOLD_EFFECT_ASSAULT_VEST,
        .holdEffectParam = 50,
        .description = COMPOUND_STRING(
            "Raises Sp. Def but\n"
            "prevents the use\n"
            "of status moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_AssaultVest,
        .iconPalette = gItemIconPalette_AssaultVest,
    },

    [ITEM_SAFETY_GOGGLES] =
    {
        .name = ITEM_NAME("SAFETY GOGGLES"),
        .pluralName = ITEM_PLURAL_NAME("Safety Goggles"),
    #if I_PRICE >= GEN_9
        .price = 20000,
    #elif I_PRICE >= GEN_7
        .price = 4000,
    #else
        .price = 1000,
    #endif
        .holdEffect = HOLD_EFFECT_SAFETY_GOGGLES,
        .description = COMPOUND_STRING(
            "Protect from\n"
            "weather damage and\n"
            "powder moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_SafetyGoggles,
        .iconPalette = gItemIconPalette_SafetyGoggles,
    },

    [ITEM_ADRENALINE_ORB] =
    {
        .name = ITEM_NAME("ADRENALINE ORB"),
    #if I_PRICE >= GEN_9
        .price = 5000,
    #elif I_PRICE == GEN_8
        .price = 4000,
    #else
        .price = 300,
    #endif
        .holdEffect = HOLD_EFFECT_ADRENALINE_ORB,
        .description = COMPOUND_STRING(
            "This orb boosts\n"
            "Speed if the holder\n"
            "is intimidated."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AdrenalineOrb,
        .iconPalette = gItemIconPalette_AdrenalineOrb,
    },

    [ITEM_TERRAIN_EXTENDER] =
    {
        .name = ITEM_NAME("TERRAIN EXTENDER"),
        .price = (I_PRICE >= GEN_9) ? 15000 : 4000,
        .holdEffect = HOLD_EFFECT_TERRAIN_EXTENDER,
        .description = COMPOUND_STRING(
            "Extends the length\n"
            "of the active\n"
            "battle terrain."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_TerrainExtender,
        .iconPalette = gItemIconPalette_TerrainExtender,
    },

    [ITEM_PROTECTIVE_PADS] =
    {
        .name = ITEM_NAME("PROTECTIVE PADS"),
        .pluralName = ITEM_PLURAL_NAME("Protective Pads"),
        .price = (I_PRICE >= GEN_9) ? 15000 : 4000,
        .holdEffect = HOLD_EFFECT_PROTECTIVE_PADS,
        .description = COMPOUND_STRING(
            "Guard the holder\n"
            "from contact move\n"
            "effects."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ProtectivePads,
        .iconPalette = gItemIconPalette_ProtectivePads,
    },

    [ITEM_THROAT_SPRAY] =
    {
        .name = ITEM_NAME("THROAT SPRAY"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_THROAT_SPRAY,
        .description = COMPOUND_STRING(
            "Raises Sp. Atk. if\n"
            "the holder uses a\n"
            "sound-based move."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ThroatSpray,
        .iconPalette = gItemIconPalette_ThroatSpray,
    },

    [ITEM_EJECT_PACK] =
    {
        .name = ITEM_NAME("EJECT PACK"),
        .price = (I_PRICE >= GEN_9) ? 30000 : 4000,
        .holdEffect = HOLD_EFFECT_EJECT_PACK,
        .description = COMPOUND_STRING(
            "Forces the user to\n"
            "switch if its stats\n"
            "are lowered."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 50,
        .iconPic = gItemIcon_EjectPack,
        .iconPalette = gItemIconPalette_EjectPack,
    },

    [ITEM_HEAVY_DUTY_BOOTS] =
    {
        .name = ITEM_NAME("HEAVY-DUTY BOOTS"),
        .pluralName = ITEM_PLURAL_NAME("Heavy-Duty Boots"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_HEAVY_DUTY_BOOTS,
        .description = COMPOUND_STRING(
            "Boots that prevent\n"
            "effects of traps\n"
            "set in the field."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_HeavyDutyBoots,
        .iconPalette = gItemIconPalette_HeavyDutyBoots,
    },

    [ITEM_BLUNDER_POLICY] =
    {
        .name = ITEM_NAME("BLUNDER POLICY"),
        .pluralName = ITEM_PLURAL_NAME("Blunder Policies"),
        .price = (I_PRICE >= GEN_9) ? 30000 : 4000,
        .holdEffect = HOLD_EFFECT_BLUNDER_POLICY,
        .description = COMPOUND_STRING(
            "Raises Speed if\n"
            "the user misses\n"
            "due to Accuracy."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 80,
        .iconPic = gItemIcon_BlunderPolicy,
        .iconPalette = gItemIconPalette_BlunderPolicy,
    },

    [ITEM_ROOM_SERVICE] =
    {
        .name = ITEM_NAME("ROOM SERVICE"),
        .price = (I_PRICE >= GEN_9) ? 20000 : 4000,
        .holdEffect = HOLD_EFFECT_ROOM_SERVICE,
        .description = COMPOUND_STRING(
            "Lowers Speed if\n"
            "Trick Room is\n"
            "active."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 100,
        .iconPic = gItemIcon_RoomService,
        .iconPalette = gItemIconPalette_RoomService,
    },

    [ITEM_UTILITY_UMBRELLA] =
    {
        .name = ITEM_NAME("UTILITY UMBRELLA"),
        .price = (I_PRICE >= GEN_9) ? 15000 : 4000,
        .holdEffect = HOLD_EFFECT_UTILITY_UMBRELLA,
        .description = COMPOUND_STRING(
            "An umbrella that\n"
            "protects from\n"
            "weather effects."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_UtilityUmbrella,
        .iconPalette = gItemIconPalette_UtilityUmbrella,
    },

// Berries

    [ITEM_CHERI_BERRY] =
    {
        .name = ITEM_NAME("CHERI BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Cheri Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_PAR,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "heals paralysis\n"
            "in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_ParalyzeHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_CheriBerry,
        .iconPalette = gItemIconPalette_CheriBerry,
    },

    [ITEM_CHESTO_BERRY] =
    {
        .name = ITEM_NAME("CHESTO BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Chesto Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_SLP,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "awakens Pokémon\n"
            "in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Awakening,
        .flingPower = 10,
        .iconPic = gItemIcon_ChestoBerry,
        .iconPalette = gItemIconPalette_ChestoBerry,
    },

    [ITEM_PECHA_BERRY] =
    {
        .name = ITEM_NAME("PECHA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Pecha Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_PSN,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "heals poisoning\n"
            "in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_Antidote,
        .flingPower = 10,
        .iconPic = gItemIcon_PechaBerry,
        .iconPalette = gItemIconPalette_PechaBerry,
    },

    [ITEM_RAWST_BERRY] =
    {
        .name = ITEM_NAME("RAWST BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Rawst Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_BRN,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "heals a burn in\n"
            "battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_BurnHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_RawstBerry,
        .iconPalette = gItemIconPalette_RawstBerry,
    },

    [ITEM_ASPEAR_BERRY] =
    {
        .name = ITEM_NAME("ASPEAR BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Aspear Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_FRZ,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "defrosts Pokémon\n"
            "in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_IceHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_AspearBerry,
        .iconPalette = gItemIconPalette_AspearBerry,
    },

    [ITEM_LEPPA_BERRY] =
    {
        .name = ITEM_NAME("LEPPA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Leppa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESTORE_PP,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "restores 10 PP in\n"
            "battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU_MOVES,
        .fieldUseFunc = ItemUseOutOfBattle_PPRecovery,
        .battleUsage = EFFECT_ITEM_RESTORE_PP,
        .effect = gItemEffect_LeppaBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_LeppaBerry,
        .iconPalette = gItemIconPalette_LeppaBerry,
    },

    [ITEM_ORAN_BERRY] =
    {
        .name = ITEM_NAME("ORAN BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Oran Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 10,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "restores 10 HP in\n"
            "battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_OranBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_OranBerry,
        .iconPalette = gItemIconPalette_OranBerry,
    },

    [ITEM_PERSIM_BERRY] =
    {
        .name = ITEM_NAME("PERSIM BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Persim Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_CONFUSION,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "heals confusion\n"
            "in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_PersimBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_PersimBerry,
        .iconPalette = gItemIconPalette_PersimBerry,
    },

    [ITEM_LUM_BERRY] =
    {
        .name = ITEM_NAME("LUM BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Lum Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CURE_STATUS,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "heals any status\n"
            "problem in battle."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 10,
        .iconPic = gItemIcon_LumBerry,
        .iconPalette = gItemIconPalette_LumBerry,
    },

    [ITEM_SITRUS_BERRY] =
    {
        .name = ITEM_NAME("SITRUS BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Sitrus Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
    #if I_SITRUS_BERRY_HEAL >= GEN_4
        .holdEffect = HOLD_EFFECT_RESTORE_PCT_HP,
        .holdEffectParam = 25,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "restores the user's\n"
            "HP a little."),
    #else
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "restores 30 HP in\n"
            "battle."),
    #endif
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SitrusBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_SitrusBerry,
        .iconPalette = gItemIconPalette_SitrusBerry,
    },

    [ITEM_FIGY_BERRY] =
    {
        .name = ITEM_NAME("FIGY BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Figy Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_SPICY,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sFigyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_FigyBerry,
        .iconPalette = gItemIconPalette_FigyBerry,
    },

    [ITEM_WIKI_BERRY] =
    {
        .name = ITEM_NAME("WIKI BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Wiki Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_DRY,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sFigyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WikiBerry,
        .iconPalette = gItemIconPalette_WikiBerry,
    },

    [ITEM_MAGO_BERRY] =
    {
        .name = ITEM_NAME("MAGO BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Mago Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_SWEET,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sFigyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MagoBerry,
        .iconPalette = gItemIconPalette_MagoBerry,
    },

    [ITEM_AGUAV_BERRY] =
    {
        .name = ITEM_NAME("AGUAV BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Aguav Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_BITTER,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sFigyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_AguavBerry,
        .iconPalette = gItemIconPalette_AguavBerry,
    },

    [ITEM_IAPAPA_BERRY] =
    {
        .name = ITEM_NAME("IAPAPA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Iapapa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CONFUSE_SOUR,
        .holdEffectParam = CONFUSE_BERRY_HEAL_FRACTION,
        .description = sFigyBerryDesc,
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_IapapaBerry,
        .iconPalette = gItemIconPalette_IapapaBerry,
    },

    [ITEM_RAZZ_BERRY] =
    {
        .name = ITEM_NAME("RAZZ BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Razz Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Razz."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RazzBerry,
        .iconPalette = gItemIconPalette_RazzBerry,
    },

    [ITEM_BLUK_BERRY] =
    {
        .name = ITEM_NAME("BLUK BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Bluk Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Bluk."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BlukBerry,
        .iconPalette = gItemIconPalette_BlukBerry,
    },

    [ITEM_NANAB_BERRY] =
    {
        .name = ITEM_NAME("NANAB BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Nanab Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Nanab."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_NanabBerry,
        .iconPalette = gItemIconPalette_NanabBerry,
    },

    [ITEM_WEPEAR_BERRY] =
    {
        .name = ITEM_NAME("WEPEAR BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Wepear Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Wepear."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WepearBerry,
        .iconPalette = gItemIconPalette_WepearBerry,
    },

    [ITEM_PINAP_BERRY] =
    {
        .name = ITEM_NAME("PINAP BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Pinap Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Pinap."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PinapBerry,
        .iconPalette = gItemIconPalette_PinapBerry,
    },

    [ITEM_POMEG_BERRY] =
    {
        .name = ITEM_NAME("POMEG BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Pomeg Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "Makes a Pokémon\n"
            "friendly but lowers\n"
            "base HP."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_PomegBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_PomegBerry,
        .iconPalette = gItemIconPalette_PomegBerry,
    },

    [ITEM_KELPSY_BERRY] =
    {
        .name = ITEM_NAME("KELPSY BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Kelpsy Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Attack."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_KelpsyBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_KelpsyBerry,
        .iconPalette = gItemIconPalette_KelpsyBerry,
    },

    [ITEM_QUALOT_BERRY] =
    {
        .name = ITEM_NAME("QUALOT BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Qualot Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Defense."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_QualotBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_QualotBerry,
        .iconPalette = gItemIconPalette_QualotBerry,
    },

    [ITEM_HONDEW_BERRY] =
    {
        .name = ITEM_NAME("HONDEW BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Hondew Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Sp. Atk."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_HondewBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_HondewBerry,
        .iconPalette = gItemIconPalette_HondewBerry,
    },

    [ITEM_GREPA_BERRY] =
    {
        .name = ITEM_NAME("GREPA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Grepa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Sp. Def."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_GrepaBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_GrepaBerry,
        .iconPalette = gItemIconPalette_GrepaBerry,
    },

    [ITEM_TAMATO_BERRY] =
    {
        .name = ITEM_NAME("TAMATO BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Tamato Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "Makes a Pokémon\n"
            "friendly but lowers\n"
            "base Speed."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ReduceEV,
        .effect = gItemEffect_TamatoBerry,
        .flingPower = 10,
        .iconPic = gItemIcon_TamatoBerry,
        .iconPalette = gItemIconPalette_TamatoBerry,
    },

    [ITEM_CORNN_BERRY] =
    {
        .name = ITEM_NAME("CORNN BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Cornn Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Cornn."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CornnBerry,
        .iconPalette = gItemIconPalette_CornnBerry,
    },

    [ITEM_MAGOST_BERRY] =
    {
        .name = ITEM_NAME("MAGOST BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Magost Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Magost."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MagostBerry,
        .iconPalette = gItemIconPalette_MagostBerry,
    },

    [ITEM_RABUTA_BERRY] =
    {
        .name = ITEM_NAME("RABUTA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Rabuta Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Rabuta."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RabutaBerry,
        .iconPalette = gItemIconPalette_RabutaBerry,
    },

    [ITEM_NOMEL_BERRY] =
    {
        .name = ITEM_NAME("NOMEL BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Nomel Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Nomel."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_NomelBerry,
        .iconPalette = gItemIconPalette_NomelBerry,
    },

    [ITEM_SPELON_BERRY] =
    {
        .name = ITEM_NAME("SPELON BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Spelon Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Spelon."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SpelonBerry,
        .iconPalette = gItemIconPalette_SpelonBerry,
    },

    [ITEM_PAMTRE_BERRY] =
    {
        .name = ITEM_NAME("PAMTRE BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Pamtre Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Pamtre."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PamtreBerry,
        .iconPalette = gItemIconPalette_PamtreBerry,
    },

    [ITEM_WATMEL_BERRY] =
    {
        .name = ITEM_NAME("WATMEL BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Watmel Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Watmel."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WatmelBerry,
        .iconPalette = gItemIconPalette_WatmelBerry,
    },

    [ITEM_DURIN_BERRY] =
    {
        .name = ITEM_NAME("DURIN BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Durin Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Durin."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_DurinBerry,
        .iconPalette = gItemIconPalette_DurinBerry,
    },

    [ITEM_BELUE_BERRY] =
    {
        .name = ITEM_NAME("BELUE BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Belue Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow Belue."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BelueBerry,
        .iconPalette = gItemIconPalette_BelueBerry,
    },

    [ITEM_CHILAN_BERRY] =
    {
        .name = ITEM_NAME("CHILAN BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Chilan Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_NORMAL,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Normal\n"
            "move."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChilanBerry,
        .iconPalette = gItemIconPalette_ChilanBerry,
    },

    [ITEM_OCCA_BERRY] =
    {
        .name = ITEM_NAME("OCCA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Occa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FIRE,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Fire\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_OccaBerry,
        .iconPalette = gItemIconPalette_OccaBerry,
    },

    [ITEM_PASSHO_BERRY] =
    {
        .name = ITEM_NAME("PASSHO BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Passho Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_WATER,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Water\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PasshoBerry,
        .iconPalette = gItemIconPalette_PasshoBerry,
    },

    [ITEM_WACAN_BERRY] =
    {
        .name = ITEM_NAME("WACAN BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Wacan Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ELECTRIC,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Electric\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_WacanBerry,
        .iconPalette = gItemIconPalette_WacanBerry,
    },

    [ITEM_RINDO_BERRY] =
    {
        .name = ITEM_NAME("RINDO BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Rindo Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GRASS,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Grass\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RindoBerry,
        .iconPalette = gItemIconPalette_RindoBerry,
    },

    [ITEM_YACHE_BERRY] =
    {
        .name = ITEM_NAME("YACHE BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Yache Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ICE,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Ice\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_YacheBerry,
        .iconPalette = gItemIconPalette_YacheBerry,
    },

    [ITEM_CHOPLE_BERRY] =
    {
        .name = ITEM_NAME("CHOPLE BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Chople Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FIGHTING,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Fighting\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChopleBerry,
        .iconPalette = gItemIconPalette_ChopleBerry,
    },

    [ITEM_KEBIA_BERRY] =
    {
        .name = ITEM_NAME("KEBIA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Kebia Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_POISON,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Poison\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_KebiaBerry,
        .iconPalette = gItemIconPalette_KebiaBerry,
    },

    [ITEM_SHUCA_BERRY] =
    {
        .name = ITEM_NAME("SHUCA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Shuca Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GROUND,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Ground\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ShucaBerry,
        .iconPalette = gItemIconPalette_ShucaBerry,
    },

    [ITEM_COBA_BERRY] =
    {
        .name = ITEM_NAME("COBA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Coba Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FLYING,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Flying\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CobaBerry,
        .iconPalette = gItemIconPalette_CobaBerry,
    },

    [ITEM_PAYAPA_BERRY] =
    {
        .name = ITEM_NAME("PAYAPA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Payapa Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_PSYCHIC,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Psychic\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PayapaBerry,
        .iconPalette = gItemIconPalette_PayapaBerry,
    },

    [ITEM_TANGA_BERRY] =
    {
        .name = ITEM_NAME("TANGA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Tanga Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_BUG,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Bug\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_TangaBerry,
        .iconPalette = gItemIconPalette_TangaBerry,
    },

    [ITEM_CHARTI_BERRY] =
    {
        .name = ITEM_NAME("CHARTI BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Charti Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_ROCK,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Rock\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ChartiBerry,
        .iconPalette = gItemIconPalette_ChartiBerry,
    },

    [ITEM_KASIB_BERRY] =
    {
        .name = ITEM_NAME("KASIB BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Kasib Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_GHOST,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Ghost\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_KasibBerry,
        .iconPalette = gItemIconPalette_KasibBerry,
    },

    [ITEM_HABAN_BERRY] =
    {
        .name = ITEM_NAME("HABAN BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Haban Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_DRAGON,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Dragon\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_HabanBerry,
        .iconPalette = gItemIconPalette_HabanBerry,
    },

    [ITEM_COLBUR_BERRY] =
    {
        .name = ITEM_NAME("COLBUR BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Colbur Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_DARK,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Dark\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ColburBerry,
        .iconPalette = gItemIconPalette_ColburBerry,
    },

    [ITEM_BABIRI_BERRY] =
    {
        .name = ITEM_NAME("BABIRI BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Babiri Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_STEEL,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Steel\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BabiriBerry,
        .iconPalette = gItemIconPalette_BabiriBerry,
    },

    [ITEM_ROSELI_BERRY] =
    {
        .name = ITEM_NAME("ROSELI BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Roseli Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RESIST_BERRY,
        .holdEffectParam = TYPE_FAIRY,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "weakens a Fairy\n"
            "move if weak to it."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RoseliBerry,
        .iconPalette = gItemIconPalette_RoseliBerry,
    },

    [ITEM_LIECHI_BERRY] =
    {
        .name = ITEM_NAME("LIECHI BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Liechi Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_ATTACK_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Attack in\n"
            "a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LiechiBerry,
        .iconPalette = gItemIconPalette_LiechiBerry,
    },

    [ITEM_GANLON_BERRY] =
    {
        .name = ITEM_NAME("GANLON BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Ganlon Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Defense in\n"
            "a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_GanlonBerry,
        .iconPalette = gItemIconPalette_GanlonBerry,
    },

    [ITEM_SALAC_BERRY] =
    {
        .name = ITEM_NAME("SALAC BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Salac Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_SPEED_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Speed in\n"
            "a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_SalacBerry,
        .iconPalette = gItemIconPalette_SalacBerry,
    },

    [ITEM_PETAYA_BERRY] =
    {
        .name = ITEM_NAME("PETAYA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Petaya Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_SP_ATTACK_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Sp. Atk in\n"
            "a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_PetayaBerry,
        .iconPalette = gItemIconPalette_PetayaBerry,
    },

    [ITEM_APICOT_BERRY] =
    {
        .name = ITEM_NAME("APICOT BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Apicot Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_SP_DEFENSE_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises Sp. Def in\n"
            "a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_ApicotBerry,
        .iconPalette = gItemIconPalette_ApicotBerry,
    },

    [ITEM_LANSAT_BERRY] =
    {
        .name = ITEM_NAME("LANSAT BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Lansat Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CRITICAL_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "ups the critical-\n"
            "hit rate in a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_LansatBerry,
        .iconPalette = gItemIconPalette_LansatBerry,
    },

    [ITEM_STARF_BERRY] =
    {
        .name = ITEM_NAME("STARF BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Starf Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_RANDOM_STAT_UP,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "sharply boosts a\n"
            "stat in a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_StarfBerry,
        .iconPalette = gItemIconPalette_StarfBerry,
    },

    [ITEM_ENIGMA_BERRY] =
    {
        .name = ITEM_NAME("ENIGMA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Enigma Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_ENIGMA_BERRY,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "heals from super\n"
            "effective moves."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_EnigmaBerry,
        .iconPalette = gItemIconPalette_EnigmaBerry,
    },

    [ITEM_MICLE_BERRY] =
    {
        .name = ITEM_NAME("MICLE BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Micle Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_MICLE_BERRY,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "When held, it ups\n"
            "the Accuracy of a\n"
            "move in a pinch."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MicleBerry,
        .iconPalette = gItemIconPalette_MicleBerry,
    },

    [ITEM_CUSTAP_BERRY] =
    {
        .name = ITEM_NAME("CUSTAP BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Custap Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_CUSTAP_BERRY,
        .holdEffectParam = 4,
        .description = COMPOUND_STRING(
            "It allows a Pokémon\n"
            "in a pinch to move\n"
            "first just once."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_CustapBerry,
        .iconPalette = gItemIconPalette_CustapBerry,
    },

    [ITEM_JABOCA_BERRY] =
    {
        .name = ITEM_NAME("JABOCA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Jaboca Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_JABOCA_BERRY,
        .description = COMPOUND_STRING(
            "If hit by a physical\n"
            "move, it will hurt\n"
            "the attacker a bit."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_JabocaBerry,
        .iconPalette = gItemIconPalette_JabocaBerry,
    },

    [ITEM_ROWAP_BERRY] =
    {
        .name = ITEM_NAME("ROWAP BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Rowap Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_ROWAP_BERRY,
        .description = COMPOUND_STRING(
            "If hit by a special\n"
            "move, it will hurt\n"
            "the attacker a bit."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_RowapBerry,
        .iconPalette = gItemIconPalette_RowapBerry,
    },

    [ITEM_KEE_BERRY] =
    {
        .name = ITEM_NAME("KEE BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Kee Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_KEE_BERRY,
        .description = COMPOUND_STRING(
            "If hit by a physical\n"
            "move, it raises the\n"
            "Defense a bit."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_KeeBerry,
        .iconPalette = gItemIconPalette_KeeBerry,
    },

    [ITEM_MARANGA_BERRY] =
    {
        .name = ITEM_NAME("MARANGA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Maranga Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .holdEffect = HOLD_EFFECT_MARANGA_BERRY,
        .description = COMPOUND_STRING(
            "If hit by a special\n"
            "move, it raises the\n"
            "Sp. Def. a bit."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_MarangaBerry,
        .iconPalette = gItemIconPalette_MarangaBerry,
    },

    [ITEM_ENIGMA_BERRY_E_READER] =
    {
        .name = ITEM_NAME("ENIGMA BERRY"),
        .pluralName = ITEM_PLURAL_NAME("Enigma Berries"),
        .price = (I_BERRY_PRICE >= GEN_8) ? 80 : 20,
        .description = COMPOUND_STRING(
            "{POKEBLOCK} ingredient.\n"
            "Plant in loamy soil\n"
            "to grow a mystery."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU, // Type handled by ItemUseOutOfBattle_EnigmaBerry
        .fieldUseFunc = ItemUseOutOfBattle_EnigmaBerry,
        .battleUsage = EFFECT_ITEM_ENIGMA_BERRY_EREADER,
        .flingPower = 10,
        .iconPic = gItemIcon_EnigmaBerry,
        .iconPalette = gItemIconPalette_EnigmaBerry,
    },

// TMs/HMs. They don't have a set flingPower, as that's handled by GetFlingPowerFromItemId.

    [ITEM_TM_FOCUS_PUNCH] =
    {
        .name = ITEM_NAME("TM01"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Powerful, but makes\n"
            "the user flinch if\n"
            "hit by the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_DRAGON_CLAW] =
    {
        .name = ITEM_NAME("TM02"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Hooks and slashes\n"
            "the foe with long,\n"
            "sharp claws."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_WATER_PULSE] =
    {
        .name = ITEM_NAME("TM03"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Generates an\n"
            "ultrasonic wave\n"
            "that may confuse."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_CALM_MIND] =
    {
        .name = ITEM_NAME("TM04"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Raises Sp. Atk and\n"
            "Sp. Def by focusing\n"
            "the mind."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ROAR] =
    {
        .name = ITEM_NAME("TM05"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A savage roar that\n"
            "makes the foe flee \n"
            "to end the battle."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_TOXIC] =
    {
        .name = ITEM_NAME("TM06"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Poisons the foe\n"
            "with a toxin that\n"
            "gradually worsens."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_HAIL] =
    {
        .name = ITEM_NAME("TM07"),
        .price = 3000,
    #if B_PREFERRED_ICE_WEATHER == B_ICE_WEATHER_SNOW
        .description = COMPOUND_STRING(
            "Raises the Defense\n"
            "of Ice type {PKMN}\n"
            "for 5 turns."),
    #else
        .description = COMPOUND_STRING(
            "Creates a hailstorm\n"
            "that damages all\n"
            "types except Ice."),
    #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BULK_UP] =
    {
        .name = ITEM_NAME("TM08"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Bulks up the body\n"
            "to boost both\n"
            "Attack & Defense."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BULLET_SEED] =
    {
        .name = ITEM_NAME("TM09"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Shoots 2 to 5 seeds\n"
            "in a row to strike\n"
            "the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_HIDDEN_POWER] =
    {
        .name = ITEM_NAME("TM10"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "The attack power\n"
            "varies among\n"
            "different Pokémon."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SUNNY_DAY] =
    {
        .name = ITEM_NAME("TM11"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "Raises the power of\n"
            "Fire-type moves\n"
            "for 5 turns."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_TAUNT] =
    {
        .name = ITEM_NAME("TM12"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Enrages the foe so\n"
            "it can only use\n"
            "attack moves."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ICE_BEAM] =
    {
        .name = ITEM_NAME("TM13"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Fires an icy cold\n"
            "beam that may\n"
        #if B_USE_FROSTBITE == TRUE
            "inflict frostbite."),
        #else
            "freeze the foe."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BLIZZARD] =
    {
        .name = ITEM_NAME("TM14"),
        .price = 5500,
        .description = COMPOUND_STRING(
        #if B_USE_FROSTBITE == TRUE
            "A snow-and-wind\n"
            "attack that may\n"
            "inflict frostbite."),
        #else
            "A brutal snow-and-\n"
            "wind attack that\n"
            "may freeze the foe."),
        #endif
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_HYPER_BEAM] =
    {
        .name = ITEM_NAME("TM15"),
        .price = 7500,
        .description = COMPOUND_STRING(
            "Powerful, but needs\n"
            "recharging the\n"
            "next turn."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_LIGHT_SCREEN] =
    {
        .name = ITEM_NAME("TM16"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Creates a wall of\n"
            "light that lowers\n"
            "Sp. Atk damage."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_PROTECT] =
    {
        .name = ITEM_NAME("TM17"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Negates all damage,\n"
            "but may fail if used\n"
            "in succession."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_RAIN_DANCE] =
    {
        .name = ITEM_NAME("TM18"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "Raises the power of\n"
            "Water-type moves\n"
            "for 5 turns."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_GIGA_DRAIN] =
    {
        .name = ITEM_NAME("TM19"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Recovers half the\n"
            "HP of the damage \n"
            "this move inflicts."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SAFEGUARD] =
    {
        .name = ITEM_NAME("TM20"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Prevents status\n"
            "abnormality with a\n"
            "mystical power."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FRUSTRATION] =
    {
        .name = ITEM_NAME("TM21"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "The less the user\n"
            "likes you, the more\n"
            "powerful this move."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SOLAR_BEAM] =
    {
        .name = ITEM_NAME("TM22"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Absorbs sunlight in\n"
            "the 1st turn, then\n"
            "attacks next turn."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_IRON_TAIL] =
    {
        .name = ITEM_NAME("TM23"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Slams the foe with\n"
            "a hard tail. It may\n"
            "lower Defense."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_THUNDERBOLT] =
    {
        .name = ITEM_NAME("TM24"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A powerful electric\n"
            "attack that may\n"
            "cause paralysis."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_THUNDER] =
    {
        .name = ITEM_NAME("TM25"),
        .price = 5500,
        .description = COMPOUND_STRING(
            "Strikes the foe\n"
            "with a thunderbolt.\n"
            "It may paralyze."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_EARTHQUAKE] =
    {
        .name = ITEM_NAME("TM26"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Causes a quake\n"
            "that has no effect\n"
            "on flying foes."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_RETURN] =
    {
        .name = ITEM_NAME("TM27"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "The more the user\n"
            "likes you, the more\n"
            "powerful this move."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_DIG] =
    {
        .name = ITEM_NAME("TM28"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "Digs underground\n"
            "the 1st turn, then\n"
            "strikes next turn."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_PSYCHIC] =
    {
        .name = ITEM_NAME("TM29"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "A powerful psychic\n"
            "attack that may\n"
            "lower Sp. Def."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SHADOW_BALL] =
    {
        .name = ITEM_NAME("TM30"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Hurls a dark lump\n"
            "at the foe. It may\n"
            "lower Sp. Def."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_BRICK_BREAK] =
    {
        .name = ITEM_NAME("TM31"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Destroys barriers\n"
            "like Light Screen\n"
            "and causes damage."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_DOUBLE_TEAM] =
    {
        .name = ITEM_NAME("TM32"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "Creates illusory\n"
            "copies to enhance\n"
            "elusiveness."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_REFLECT] =
    {
        .name = ITEM_NAME("TM33"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Creates a wall of\n"
            "light that weakens\n"
            "physical attacks."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SHOCK_WAVE] =
    {
        .name = ITEM_NAME("TM34"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Zaps the foe with a\n"
            "jolt of electricity\n"
            "that never misses."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FLAMETHROWER] =
    {
        .name = ITEM_NAME("TM35"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Looses a stream of\n"
            "fire that may burn\n"
            "the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SLUDGE_BOMB] =
    {
        .name = ITEM_NAME("TM36"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "Hurls sludge at the\n"
            "foe. It may poison\n"
            "the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SANDSTORM] =
    {
        .name = ITEM_NAME("TM37"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "Causes a sandstorm\n"
            "that hits the foe\n"
            "over several turns."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FIRE_BLAST] =
    {
        .name = ITEM_NAME("TM38"),
        .price = 5500,
        .description = COMPOUND_STRING(
            "A powerful fire\n"
            "attack that may\n"
            "burn the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ROCK_TOMB] =
    {
        .name = ITEM_NAME("TM39"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Stops the foe from\n"
            "moving with rocks.\n"
            "May lower Speed."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_AERIAL_ACE] =
    {
        .name = ITEM_NAME("TM40"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "An extremely fast\n"
            "attack that can't\n"
            "be avoided."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_TORMENT] =
    {
        .name = ITEM_NAME("TM41"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Prevents the foe\n"
            "from using the same\n"
            "move in a row."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_FACADE] =
    {
        .name = ITEM_NAME("TM42"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Raises Attack when\n"
            "poisoned, burned,\n"
            "or paralyzed."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SECRET_POWER] =
    {
        .name = ITEM_NAME("TM43"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Adds an effect to\n"
            "attack depending\n"
            "on the location."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_REST] =
    {
        .name = ITEM_NAME("TM44"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "The user sleeps for\n"
            "2 turns to restore\n"
            "health and status."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_ATTRACT] =
    {
        .name = ITEM_NAME("TM45"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Makes it tough to\n"
            "attack a foe of the\n"
            "opposite gender."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_THIEF] =
    {
        .name = ITEM_NAME("TM46"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "While attacking,\n"
            "it may steal the\n"
            "foe's held item."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_STEEL_WING] =
    {
        .name = ITEM_NAME("TM47"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Spreads hard-\n"
            "edged wings and\n"
            "slams into the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SKILL_SWAP] =
    {
        .name = ITEM_NAME("TM48"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Switches abilities\n"
            "with the foe on the\n"
            "turn this is used."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_SNATCH] =
    {
        .name = ITEM_NAME("TM49"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Steals the effects\n"
            "of the move the foe\n"
            "is trying to use."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM_OVERHEAT] =
    {
        .name = ITEM_NAME("TM50"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Enables full-power\n"
            "attack, but sharply\n"
            "lowers Sp. Atk."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM51] = // Roost
    {
        .name = ITEM_NAME("TM51"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Restores the user's\n"
            "HP by half of its\n"
            "max HP."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM52] = // Focus Blast
    {
        .name = ITEM_NAME("TM52"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Attacks at full power.\n"
            "May lower the foe's\n"
            "Sp. Def."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM53] = // Energy Ball
    {
        .name = ITEM_NAME("TM53"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Draws power from\n"
            "nature to attack.\n"
            "May lower Sp. Def."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM54] = // False Swipe
    {
        .name = ITEM_NAME("TM54"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "An attack that leaves\n"
            "the foe with at\n"
            "least 1 HP."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM55] = // Brine
    {
        .name = ITEM_NAME("TM55"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Does double damage\n"
            "to foes with half\n"
            "HP or less."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM56] = // Fling
    {
        .name = ITEM_NAME("TM56"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "The effectiveness\n"
            "varies with the\n"
            "held item."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM57] = // Charge Beam
    {
        .name = ITEM_NAME("TM57"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Fires a beam of\n"
            "electricity. May\n"
            "raise Sp. Atk."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM58] = // Endure
    {
        .name = ITEM_NAME("TM58"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Endures any attack\n"
            "for 1 turn, leaving\n"
            "at least 1 HP."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM59] = // Dragon Pulse
    {
        .name = ITEM_NAME("TM59"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Generates a shock\n"
            "wave to damage\n"
            "the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM60] = // Drain Punch
    {
        .name = ITEM_NAME("TM60"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "An attack that\n"
            "absorbs half the\n"
            "damage inflicted."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM61] = // Will-O-Wisp
    {
        .name = ITEM_NAME("TM61"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Inflicts a burn on\n"
            "the foe with\n"
            "intense fire."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM62] = // Silver Wind
    {
        .name = ITEM_NAME("TM62"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A powdery attack\n"
            "that may raise\n"
            "all abilities."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM63] = // Embargo
    {
        .name = ITEM_NAME("TM63"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Prevents the foe\n"
            "from using any\n"
            "items."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM64] = // Explosion
    {
        .name = ITEM_NAME("TM64"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Inflicts severe\n"
            "damage but makes\n"
            "the user faint."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM65] = // Shadow Claw
    {
        .name = ITEM_NAME("TM65"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Strikes with a\n"
            "shadow claw. High\n"
            "critical-hit ratio."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM66] = // Payback
    {
        .name = ITEM_NAME("TM66"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "An attack that gains\n"
            "power if the user\n"
            "moves last."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM67] = // Recycle
    {
        .name = ITEM_NAME("TM67"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Recycles a used item\n"
            "for one more use."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM68] = // Giga Impact
    {
        .name = ITEM_NAME("TM68"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Powerful, but leaves\n"
            "the user immobile\n"
            "the next turn."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM69] = // Rock Polish
    {
        .name = ITEM_NAME("TM69"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Polishes the body\n"
            "to sharply raise\n"
            "Speed."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM70] = // Flash
    {
        .name = ITEM_NAME("TM70"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Looses a powerful\n"
            "blast of light that\n"
            "cuts accuracy."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM71] = // Stone Edge
    {
        .name = ITEM_NAME("TM71"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Stabs the foe with\n"
            "stones. High\n"
            "critical-hit ratio."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM72] = // Avalanche
    {
        .name = ITEM_NAME("TM72"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "An attack that moves\n"
            "last and gains power\n"
            "if hit."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM73] = // Thunder Wave
    {
        .name = ITEM_NAME("TM73"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A weak jolt of\n"
            "electricity that\n"
            "paralyzes the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM74] = // Gyro Ball
    {
        .name = ITEM_NAME("TM74"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A high-speed spin\n"
            "that does more damage\n"
            "to faster foes."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM75] = // Swords Dance
    {
        .name = ITEM_NAME("TM75"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A fighting dance\n"
            "that sharply raises\n"
            "Attack."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM76] = // Stealth Rock
    {
        .name = ITEM_NAME("TM76"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Sets floating stones\n"
            "that hurt a foe\n"
            "switching in."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM77] = // Psych Up
    {
        .name = ITEM_NAME("TM77"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Copies the foe's\n"
            "stat changes and\n"
            "gives to the user."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM78] = // Captivate
    {
        .name = ITEM_NAME("TM78"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Makes the opposite\n"
            "gender sharply cut\n"
            "its Sp. Atk."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM79] = // Dark Pulse
    {
        .name = ITEM_NAME("TM79"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Attacks with a\n"
            "horrible aura. May\n"
            "cause flinching."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM80] = // Rock Slide
    {
        .name = ITEM_NAME("TM80"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Large boulders are\n"
            "hurled. May cause\n"
            "flinching."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM81] = // X-Scissor
    {
        .name = ITEM_NAME("TM81"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Slashes the foe with\n"
            "crossed scythes,\n"
            "claws, etc."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM82] = // Sleep Talk
    {
        .name = ITEM_NAME("TM82"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Uses an available\n"
            "move randomly while\n"
            "asleep."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM83] = // Natural Gift
    {
        .name = ITEM_NAME("TM83"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "The effectiveness\n"
            "varies with the\n"
            "held Berry."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM84] = // Poison Jab
    {
        .name = ITEM_NAME("TM84"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A stabbing attack\n"
            "that may poison\n"
            "the foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM85] = // Dream Eater
    {
        .name = ITEM_NAME("TM85"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Takes one half the\n"
            "damage inflicted on\n"
            "a sleeping foe."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM86] = // Grass Knot
    {
        .name = ITEM_NAME("TM86"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A snare attack that\n"
            "does more damage to\n"
            "heavier foes."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM87] = // Swagger
    {
        .name = ITEM_NAME("TM87"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Confuses the foe,\n"
            "but also sharply\n"
            "raises its Attack."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM88] = // Pluck
    {
        .name = ITEM_NAME("TM88"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Eats the foe's held\n"
            "Berry, gaining its\n"
            "effect."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM89] = // U-turn
    {
        .name = ITEM_NAME("TM89"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Does damage then\n"
            "switches out the\n"
            "user."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM90] = // Substitute
    {
        .name = ITEM_NAME("TM90"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Creates a decoy\n"
            "using 1/4 of the\n"
            "user's maximum HP."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM91] = // Flash Cannon
    {
        .name = ITEM_NAME("TM91"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Releases a blast of\n"
            "light that may lower\n"
            "Sp. Def."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM92] = // Trick Room
    {
        .name = ITEM_NAME("TM92"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Slower Pokémon get\n"
            "to move first for\n"
            "5 turns."),
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM93] =
    {
        .name = ITEM_NAME("TM93"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM94] =
    {
        .name = ITEM_NAME("TM94"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM95] =
    {
        .name = ITEM_NAME("TM95"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM96] =
    {
        .name = ITEM_NAME("TM96"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM97] =
    {
        .name = ITEM_NAME("TM97"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM98] =
    {
        .name = ITEM_NAME("TM98"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM99] =
    {
        .name = ITEM_NAME("TM99"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_TM100] =
    {
        .name = ITEM_NAME("TM100"),
        .price = 3000,
        .description = sQuestionMarksDesc, // Todo
        .importance = I_REUSABLE_TMS,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_CUT] =
    {
        .name = ITEM_NAME("HM01"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Attacks the foe\n"
            "with sharp blades\n"
            "or claws."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_FLY] =
    {
        .name = ITEM_NAME("HM02"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Flies up on the\n"
            "first turn, then\n"
            "attacks next turn."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_SURF] =
    {
        .name = ITEM_NAME("HM03"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Creates a huge\n"
            "wave, then crashes\n"
            "it down on the foe."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_STRENGTH] =
    {
        .name = ITEM_NAME("HM04"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Builds enormous\n"
            "power, then slams\n"
            "the foe."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

#if IS_HNS
    [ITEM_HM_WHIRLPOOL] =
    {
        .name = ITEM_NAME("HM05"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Traps the foe in a\n"
            "violent swirling\n"
            "whirlpool."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },
#else
    [ITEM_HM_FLASH] =
    {
        .name = ITEM_NAME("HM05"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Looses a powerful\n"
            "blast of light that\n"
            "reduces accuracy."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },
#endif

    [ITEM_HM_ROCK_SMASH] =
    {
        .name = ITEM_NAME("HM06"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A rock-crushingly\n"
            "tough attack that\n"
            "may lower Defense."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

    [ITEM_HM_WATERFALL] =
    {
        .name = ITEM_NAME("HM07"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Attacks the foe\n"
            "with enough power\n"
            "to climb waterfalls."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },

#if IS_HNS
    [ITEM_HM_ROCK_CLIMB] =
    {
        .name = ITEM_NAME("HM08"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An all-out charge\n"
            "attack that may\n"
            "confuse the foe."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },
#else
    [ITEM_HM_DIVE] =
    {
        .name = ITEM_NAME("HM08"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Dives underwater\n"
            "the 1st turn, then\n"
            "attacks next turn."),
        .importance = 1,
        .pocket = POCKET_TM_HM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TMHM,
    },
#endif


// Charms

    [ITEM_OVAL_CHARM] =
    {
        .name = ITEM_NAME("OVAL CHARM"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "Raises the chance\n"
            "of finding eggs\n"
            "at the daycare."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_OvalCharm,
        .iconPalette = gItemIconPalette_OvalCharm,
    },

    [ITEM_SHINY_CHARM] =
    {
        .name = ITEM_NAME("SHINY CHARM"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A charm that will\n"
            "raise the chance\n"
            "of Shiny Pokémon."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ShinyCharm,
        .iconPalette = gItemIconPalette_ShinyCharm,
    },

    [ITEM_CATCHING_CHARM] =
    {
        .name = ITEM_NAME("CATCHING CHARM"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A charm that raises\n"
            "the chance of\n"
            "Critical Captures."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_CatchingCharm,
        .iconPalette = gItemIconPalette_CatchingCharm,
    },

    [ITEM_EXP_CHARM] =
    {
        .name = ITEM_NAME("EXP. CHARM"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A charm that raises\n"
            "the amount of Exp.\n"
            "earned in battle."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ExpCharm,
        .iconPalette = gItemIconPalette_ExpCharm,
    },

// Form-changing Key Items

    [ITEM_ROTOM_CATALOG] =
    {
        .name = ITEM_NAME("ROTOM CATALOG"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A catalog full of\n"
            "devices liked by\n"
            "Rotom."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_RotomCatalog,
        .iconPic = gItemIcon_RotomCatalog,
        .iconPalette = gItemIconPalette_RotomCatalog,
    },

    [ITEM_GRACIDEA] =
    {
        .name = ITEM_NAME("GRACIDEA"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "Bouquets made with\n"
            "it are offered as a\n"
            "token of gratitude."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_Gracidea,
        .iconPalette = gItemIconPalette_Gracidea,
    },

    [ITEM_REVEAL_GLASS] =
    {
        .name = ITEM_NAME("REVEAL GLASS"),
        .pluralName = ITEM_PLURAL_NAME("Reveal Glasses"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "This glass returns\n"
            "a Pokémon back to\n"
            "its original form."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_RevealGlass,
        .iconPalette = gItemIconPalette_RevealGlass,
    },

    [ITEM_DNA_SPLICERS] =
    {
        .name = ITEM_NAME("DNA SPLICERS"),
        .pluralName = ITEM_PLURAL_NAME("DNA Splicers"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "Splicer that fuses\n"
            "Kyurem and a\n"
            "certain Pokémon."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_DNASplicers,
        .iconPalette = gItemIconPalette_DNASplicers,
    },

    [ITEM_ZYGARDE_CUBE] =
    {
        .name = ITEM_NAME("ZYGARDE CUBE"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "An item to store\n"
            "Zygarde Cores and\n"
            "Cells."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ZygardeCube,
        .iconPic = gItemIcon_ZygardeCube,
        .iconPalette = gItemIconPalette_ZygardeCube,
    },

    [ITEM_PRISON_BOTTLE] =
    {
        .name = ITEM_NAME("PRISON BOTTLE"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A bottle used to\n"
            "seal a certain\n"
            "Pokémon long ago."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_PrisonBottle,
        .iconPalette = gItemIconPalette_PrisonBottle,
    },

    [ITEM_N_SOLARIZER] =
    {
        .name = ITEM_NAME("N-SOLARIZER"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A device to fuse\n"
            "and split Necrozma\n"
            "using a Solgaleo."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_NecrozmaFuser,
        .iconPalette = gItemIconPalette_NSolarizer,
    },

    [ITEM_N_LUNARIZER] =
    {
        .name = ITEM_NAME("N-LUNARIZER"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A device to fuse\n"
            "and split Necrozma\n"
            "using a Lunala."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_NecrozmaFuser,
        .iconPalette = gItemIconPalette_NLunarizer,
    },

    [ITEM_REINS_OF_UNITY] =
    {
        .name = ITEM_NAME("REINS OF UNITY"),
        .pluralName = ITEM_PLURAL_NAME("Reins of Unity"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "Reins that unite\n"
            "Calyrex with its\n"
            "beloved steed."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Fusion,
        .iconPic = gItemIcon_ReinsOfUnity,
        .iconPalette = gItemIconPalette_ReinsOfUnity,
    },

// Battle Mechanic Key Items

    [ITEM_MEGA_RING] =
    {
        .name = ITEM_NAME("MEGA RING"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "Enables {PKMN} holding\n"
            "their Mega Stone to\n"
            "Mega Evolve."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MegaRing,
        .iconPalette = gItemIconPalette_MegaRing,
    },

    [ITEM_Z_POWER_RING] =
    {
        .name = ITEM_NAME("Z-POWER RING"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A strange ring\n"
            "that enables\n"
            "Z-Move usage."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ZPowerRing,
        .iconPalette = gItemIconPalette_ZPowerRing,
    },

    [ITEM_DYNAMAX_BAND] =
    {
        .name = ITEM_NAME("DYNAMAX BAND"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A band carrying a\n"
            "Wishing Star that\n"
            "allows Dynamaxing."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_DynamaxBand,
        .iconPalette = gItemIconPalette_DynamaxBand,
    },

// Misc. Key Items

    [ITEM_BICYCLE] =
    {
        .name = ITEM_NAME("BIKE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A folding bicycle\n"
            "that is faster than\n"
            "the Running Shoes."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = STANDARD_BIKE,
        .iconPic = gItemIcon_Bicycle,
        .iconPalette = gItemIconPalette_Bicycle,
    },

    [ITEM_MACH_BIKE] =
    {
        .name = ITEM_NAME("MACH BIKE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A folding bicycle\n"
            "that doubles your\n"
            "speed or better."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = MACH_BIKE,
        .iconPic = gItemIcon_MachBike,
        .iconPalette = gItemIconPalette_MachBike,
    },

    [ITEM_ACRO_BIKE] =
    {
        .name = ITEM_NAME("ACRO BIKE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A folding bicycle\n"
            "capable of jumps\n"
            "and wheelies."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Bike,
        .secondaryId = ACRO_BIKE,
        .iconPic = gItemIcon_AcroBike,
        .iconPalette = gItemIconPalette_AcroBike,
    },

    [ITEM_OLD_ROD] =
    {
        .name = ITEM_NAME("OLD ROD"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Use by any body of\n"
            "water to fish for\n"
            "wild Pokémon."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = OLD_ROD,
        .iconPic = gItemIcon_OldRod,
        .iconPalette = gItemIconPalette_OldRod,
    },

    [ITEM_GOOD_ROD] =
    {
        .name = ITEM_NAME("GOOD ROD"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A decent fishing\n"
            "rod for catching\n"
            "wild Pokémon."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = GOOD_ROD,
        .iconPic = gItemIcon_GoodRod,
        .iconPalette = gItemIconPalette_GoodRod,
    },

    [ITEM_SUPER_ROD] =
    {
        .name = ITEM_NAME("SUPER ROD"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The best fishing\n"
            "rod for catching\n"
            "wild Pokémon."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Rod,
        .secondaryId = SUPER_ROD,
        .iconPic = gItemIcon_SuperRod,
        .iconPalette = gItemIconPalette_SuperRod,
    },

    [ITEM_DOWSING_MACHINE] =
    {
        .name = ITEM_NAME("DOWSING MACHINE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A device that\n"
            "signals an invisible\n"
            "item by sound."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_Itemfinder,
        .iconPic = gItemIcon_DowsingMachine,
        .iconPalette = gItemIconPalette_DowsingMachine,
    },

    [ITEM_TOWN_MAP] =
    {
        .name = ITEM_NAME("TOWN MAP"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Can be viewed\n"
            "anytime. Shows your\n"
            "present location."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_TownMap,
        .iconPic = gItemIcon_TownMap,
        .iconPalette = gItemIconPalette_TownMap,
    },

    [ITEM_VS_SEEKER] =
    {
        .name = ITEM_NAME("VS. SEEKER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A rechargeable unit\n"
            "that flags battle-\n"
            "ready Trainers."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
    #if I_VS_SEEKER_CHARGING != 0
        .fieldUseFunc = FieldUseFunc_VsSeeker,
    #else
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    #endif
        .iconPic = gItemIcon_VsSeeker,
        .iconPalette = gItemIconPalette_VsSeeker,
    },

    [ITEM_TM_CASE] =
    {
        .name = ITEM_NAME("TM CASE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A convenient case\n"
            "that holds TMs and\n"
            "HMs."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TMCase,
        .iconPalette = gItemIconPalette_TMCase,
    },

    [ITEM_BERRY_POUCH] =
    {
        .name = ITEM_NAME("BERRY POUCH"),
        .pluralName = ITEM_PLURAL_NAME("Berry Pouches"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A convenient\n"
            "container that\n"
            "holds Berries."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BerryPouch,
        .iconPalette = gItemIconPalette_BerryPouch,
    },

    [ITEM_POKEMON_BOX_LINK] =
    {
        .name = ITEM_NAME("{PKMN} BOX LINK"),
        .price = 0,
        .description = COMPOUND_STRING(
            "This device grants\n"
            "access to the {PKMN}\n"
            "Storage System."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_PokemonBoxLink,
        .iconPic = gItemIcon_PokemonBoxLink,
        .iconPalette = gItemIconPalette_PokemonBoxLink,
    },

    [ITEM_COIN_CASE] =
    {
        .name = ITEM_NAME("COIN CASE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A case that holds\n"
            "up to 9,999 Coins."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CoinCase,
        .iconPic = gItemIcon_CoinCase,
        .iconPalette = gItemIconPalette_CoinCase,
    },

    [ITEM_POWDER_JAR] =
    {
        .name = ITEM_NAME("POWDER JAR"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Stores Berry\n"
            "Powder made using\n"
            "a Berry Crusher."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PowderJar,
        .iconPic = gItemIcon_PowderJar,
        .iconPalette = gItemIconPalette_PowderJar,
    },

    [ITEM_WAILMER_PAIL] =
    {
        .name = ITEM_NAME("WAILMER PAIL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A tool used for\n"
            "watering Berries\n"
            "and plants."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_WailmerPail,
        .iconPic = gItemIcon_WailmerPail,
        .iconPalette = gItemIconPalette_WailmerPail,
    },

    [ITEM_POKE_RADAR] =
    {
        .name = ITEM_NAME("POKé RADAR"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A tool used to\n"
            "search out Pokémon\n"
            "hiding in grass."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse, // Todo
        .iconPic = gItemIcon_PokeRadar,
        .iconPalette = gItemIconPalette_PokeRadar,
    },

    [ITEM_POKEBLOCK_CASE] =
    {
        .name = ITEM_NAME("{POKEBLOCK} CASE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A case for holding\n"
            "{POKEBLOCK}s made with\n"
            "a Berry Blender."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PBLOCK_CASE,
        .fieldUseFunc = ItemUseOutOfBattle_PokeblockCase,
        .iconPic = gItemIcon_PokeblockCase,
        .iconPalette = gItemIconPalette_PokeblockCase,
    },

    [ITEM_SOOT_SACK] =
    {
        .name = ITEM_NAME("SOOT SACK"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A sack used to\n"
            "gather and hold\n"
            "volcanic ash."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SootSack,
        .iconPalette = gItemIconPalette_SootSack,
    },

    [ITEM_POKE_FLUTE] =
    {
        .name = ITEM_NAME("POKé FLUTE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A sweet-sounding\n"
            "flute that awakens\n"
            "Pokémon."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_PokeFlute,
        .battleUsage = EFFECT_ITEM_USE_POKE_FLUTE,
        .iconPic = gItemIcon_PokeFlute,
        .iconPalette = gItemIconPalette_PokeFlute,
    },

    [ITEM_FAME_CHECKER] =
    {
        .name = ITEM_NAME("FAME CHECKER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Stores information\n"
            "on famous people\n"
            "for instant recall."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_FameChecker,
        .iconPalette = gItemIconPalette_FameChecker,
    },

    [ITEM_TEACHY_TV] =
    {
        .name = ITEM_NAME("TEACHY TV"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A TV set tuned to\n"
            "an advice program\n"
            "for Trainers."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeachyTV,
        .iconPalette = gItemIconPalette_TeachyTV,
    },

// Story Key Items

    [ITEM_SS_TICKET] =
    {
        .name = ITEM_NAME("S.S. TICKET"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The ticket required\n"
            "for sailing on a\n"
            "ferry."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SSTicket,
        .iconPalette = gItemIconPalette_SSTicket,
    },

    [ITEM_EON_TICKET] =
    {
        .name = ITEM_NAME("EON TICKET"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The ticket for a\n"
            "ferry to a distant\n"
            "southern island."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = 1,
        .iconPic = gItemIcon_EonTicket,
        .iconPalette = gItemIconPalette_EonTicket,
    },

    [ITEM_MYSTIC_TICKET] =
    {
        .name = ITEM_NAME("MYSTIC TICKET"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A ticket required\n"
            "to board the ship\n"
            "to Navel Rock."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MysticTicket,
        .iconPalette = gItemIconPalette_MysticTicket,
    },

    [ITEM_AURORA_TICKET] =
    {
        .name = ITEM_NAME("AURORA TICKET"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A ticket required\n"
            "to board the ship\n"
            "to Birth Island."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_AuroraTicket,
        .iconPalette = gItemIconPalette_AuroraTicket,
    },

    [ITEM_OLD_SEA_MAP] =
    {
        .name = ITEM_NAME("OLD SEA MAP"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A faded sea chart\n"
            "that shows the way\n"
            "to a certain island."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_OldSeaMap,
        .iconPalette = gItemIconPalette_OldSeaMap,
    },

    [ITEM_LETTER] =
    {
        .name = ITEM_NAME("LETTER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A letter to Steven\n"
            "from the President\n"
            "of the Devon Corp."),
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Letter,
        .iconPalette = gItemIconPalette_LavaCookieAndLetter,
    },

    [ITEM_DEVON_PARTS] =
    {
        .name = ITEM_NAME("DEVON PARTS"),
        .pluralName = ITEM_PLURAL_NAME("Devon Parts"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A package that\n"
            "contains Devon's\n"
            "machine parts."),
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_DevonParts,
        .iconPalette = gItemIconPalette_DevonParts,
    },

    [ITEM_GO_GOGGLES] =
    {
        .name = ITEM_NAME("GO-GOGGLES"),
        .pluralName = ITEM_PLURAL_NAME("Go-Goggles"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Nifty goggles that\n"
            "protect eyes from\n"
            "desert sandstorms."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GoGoggles,
        .iconPalette = gItemIconPalette_GoGoggles,
    },

    [ITEM_DEVON_SCOPE] =
    {
        .name = ITEM_NAME("DEVON SCOPE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A device by Devon\n"
            "that signals any\n"
            "unseeable Pokémon."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_DevonScope,
        .iconPalette = gItemIconPalette_DevonScope,
    },

    [ITEM_BASEMENT_KEY] =
    {
        .name = ITEM_NAME("BASEMENT KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The key for New\n"
            "Mauville beneath\n"
            "Mauville City."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BasementKey,
        .iconPalette = gItemIconPalette_OldKey,
    },

    [ITEM_SCANNER] =
    {
        .name = ITEM_NAME("SCANNER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A device found\n"
            "inside the\n"
            "Abandoned Ship."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Scanner,
        .iconPalette = gItemIconPalette_Scanner,
    },

    [ITEM_STORAGE_KEY] =
    {
        .name = ITEM_NAME("STORAGE KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The key to the\n"
            "storage inside the\n"
            "Abandoned Ship."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_StorageKey,
        .iconPalette = gItemIconPalette_OldKey,
    },

    [ITEM_KEY_TO_ROOM_1] =
    {
        .name = ITEM_NAME("KEY TO ROOM 1"),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 1"),
        .price = 0,
        .description = sKeyToRoomDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom1,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_KEY_TO_ROOM_2] =
    {
        .name = ITEM_NAME("KEY TO ROOM 2"),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 2"),
        .price = 0,
        .description = sKeyToRoomDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom2,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_KEY_TO_ROOM_4] =
    {
        .name = ITEM_NAME("KEY TO ROOM 4"),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 4"),
        .price = 0,
        .description = sKeyToRoomDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom4,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_KEY_TO_ROOM_6] =
    {
        .name = ITEM_NAME("KEY TO ROOM 6"),
        .pluralName = ITEM_PLURAL_NAME("Keys to Room 6"),
        .price = 0,
        .description = sKeyToRoomDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_KeyToRoom6,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_METEORITE] =
    {
        .name = ITEM_NAME("METEORITE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A meteorite found\n"
            "at Meteor Falls."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_FormChange,
        .iconPic = gItemIcon_Meteorite,
        .iconPalette = gItemIconPalette_Meteorite,
    },

    [ITEM_MAGMA_EMBLEM] =
    {
        .name = ITEM_NAME("MAGMA EMBLEM"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A medal-like item in\n"
            "the same shape as\n"
            "Team Magma's mark."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MagmaEmblem,
        .iconPalette = gItemIconPalette_MagmaEmblem,
    },

    [ITEM_CONTEST_PASS] =
    {
        .name = ITEM_NAME("CONTEST PASS"),
        .pluralName = ITEM_PLURAL_NAME("Contest Passes"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The pass required\n"
            "for entering\n"
            "Pokémon Contests."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ContestPass,
        .iconPalette = gItemIconPalette_ContestPass,
    },

    [ITEM_PARCEL] =
    {
        .name = ITEM_NAME("PARCEL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A parcel for Prof.\n"
            "Oak from a Pokémon\n"
            "Mart's clerk."),
        .importance = 2,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Parcel,
        .iconPalette = gItemIconPalette_Parcel,
    },

    [ITEM_SECRET_KEY] =
    {
        .name = ITEM_NAME("SECRET KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "The key to the\n"
            "Cinnabar Island\n"
            "Gym's entrance."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SecretKey,
        .iconPalette = gItemIconPalette_SecretKey,
    },

    [ITEM_BIKE_VOUCHER] =
    {
        .name = ITEM_NAME("BIKE VOUCHER"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A voucher for\n"
            "obtaining a bicycle\n"
            "from the Bike Shop."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_BikeVoucher,
        .iconPalette = gItemIconPalette_BikeVoucher,
    },

    [ITEM_GOLD_TEETH] =
    {
        .name = ITEM_NAME("GOLD TEETH"),
        .pluralName = ITEM_PLURAL_NAME("Gold Teeth"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Gold dentures lost\n"
            "by the Safari\n"
            "Zone's Warden."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GoldTeeth,
        .iconPalette = gItemIconPalette_GoldTeeth,
    },

    [ITEM_CARD_KEY] =
    {
        .name = ITEM_NAME("CARD KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A card-type door\n"
            "key used in Silph\n"
            "Co's office."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_CardKey,
        .iconPalette = gItemIconPalette_CardKey,
    },

    [ITEM_LIFT_KEY] =
    {
        .name = ITEM_NAME("LIFT KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An elevator key\n"
            "used in Team\n"
            "Rocket's Hideout."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_LiftKey,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_SILPH_SCOPE] =
    {
        .name = ITEM_NAME("SILPH SCOPE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Silph Co's scope\n"
            "makes unseeable\n"
            "POKéMON visible."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SilphScope,
        .iconPalette = gItemIconPalette_SilphScope,
    },

    [ITEM_TRI_PASS] =
    {
        .name = ITEM_NAME("TRI-PASS"),
        .pluralName = ITEM_PLURAL_NAME("Tri-Passes"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A pass for ferries\n"
            "between One, Two,\n"
            "and Three Island."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TriPass,
        .iconPalette = gItemIconPalette_TriPass,
    },

    [ITEM_RAINBOW_PASS] =
    {
        .name = ITEM_NAME("RAINBOW PASS"),
        .pluralName = ITEM_PLURAL_NAME("Rainbow Passes"),
        .price = 0,
        .description = COMPOUND_STRING(
            "For ferries serving\n"
            "Vermilion and the\n"
            "Sevii Islands."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RainbowPass,
        .iconPalette = gItemIconPalette_RainbowPass,
    },

    [ITEM_TEA] =
    {
        .name = ITEM_NAME("TEA"),
        .pluralName = ITEM_PLURAL_NAME("Tea"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A thirst-quenching\n"
            "tea prepared by an\n"
            "old lady."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Tea,
        .iconPalette = gItemIconPalette_Tea,
    },

    [ITEM_RUBY] =
    {
        .name = ITEM_NAME("RUBY"),
        .pluralName = ITEM_PLURAL_NAME("Rubies"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An exquisite, red-\n"
            "glowing gem that\n"
            "symbolizes passion."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Gem,
        .iconPalette = gItemIconPalette_Ruby,
    },

    [ITEM_SAPPHIRE] =
    {
        .name = ITEM_NAME("SAPPHIRE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A brilliant blue gem\n"
            "that symbolizes\n"
            "honesty."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Gem,
        .iconPalette = gItemIconPalette_Sapphire,
    },

    [ITEM_ABILITY_SHIELD] =
    {
        .name = ITEM_NAME("ABILITY SHIELD"),
        .price = 20000,
        .holdEffect = HOLD_EFFECT_ABILITY_SHIELD,
        .description = COMPOUND_STRING(
            "Ability changes are\n"
            "prevented for this\n"
            "items's holder."),
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_AbilityShield,
        .iconPalette = gItemIconPalette_AbilityShield,
    },

// GEN 9 ITEMS

    [ITEM_CLEAR_AMULET] =
    {
        .name = ITEM_NAME("CLEAR AMULET"),
        .price = 30000,
        .holdEffect = HOLD_EFFECT_CLEAR_AMULET,
        .description = COMPOUND_STRING(
            "Stat lowering is\n"
            "prevented for this\n"
            "items's holder."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_ClearAmulet,
        .iconPalette = gItemIconPalette_ClearAmulet,
    },

    [ITEM_PUNCHING_GLOVE] =
    {
        .name = ITEM_NAME("PUNCHING GLOVE"),
        .price = 15000,
        .holdEffect = HOLD_EFFECT_PUNCHING_GLOVE,
        .description = COMPOUND_STRING(
            "Powers up punching\n"
            "moves and removes\n"
            "their contact."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_PunchingGlove,
        .iconPalette = gItemIconPalette_PunchingGlove,
    },

    [ITEM_COVERT_CLOAK] =
    {
        .name = ITEM_NAME("COVERT CLOAK"),
        .price = 20000,
        .holdEffect = HOLD_EFFECT_COVERT_CLOAK,
        .description = COMPOUND_STRING(
            "Protects holder\n"
            "from additional\n"
            "effects of moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_CovertCloak,
        .iconPalette = gItemIconPalette_CovertCloak,
    },

    [ITEM_LOADED_DICE] =
    {
        .name = ITEM_NAME("LOADED DICE"),
        .pluralName = ITEM_PLURAL_NAME("Loaded Dice"),
        .price = 20000,
        .holdEffect = HOLD_EFFECT_LOADED_DICE,
        .description = COMPOUND_STRING(
            "Rolls high numbers.\n"
            "Multihit strikes\n"
            "hit more times."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_LoadedDice,
        .iconPalette = gItemIconPalette_LoadedDice,
    },

    [ITEM_AUSPICIOUS_ARMOR] =
    {
        .name = ITEM_NAME("AUSPICIOUS ARMOR"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Armor inhabited by\n"
            "auspicious wishes.\n"
            "Causes evolution."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_AuspiciousArmor,
        .iconPalette = gItemIconPalette_AuspiciousArmor,
    },

    [ITEM_BOOSTER_ENERGY] =
    {
        .name = ITEM_NAME("BOOSTER ENERGY"),
        .pluralName = ITEM_PLURAL_NAME("Booster Energies"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_BOOSTER_ENERGY,
        .description = COMPOUND_STRING(
            "Encapsuled energy\n"
            "ups Pokémon with\n"
            "certain Abilities."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BoosterEnergy,
        .iconPalette = gItemIconPalette_BoosterEnergy,
    },

    [ITEM_BIG_BAMBOO_SHOOT] =
    {
        .name = ITEM_NAME("BIG BAMBOO SHOOT"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A large and rare\n"
            "bamboo shoot. Best\n"
            "sold to gourmands."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_BigBambooShoot,
        .iconPalette = gItemIconPalette_BigBambooShoot,
    },

    [ITEM_GIMMIGHOUL_COIN] =
    {
        .name = ITEM_NAME("GIMMIGHOUL COIN"),
        .price = 400,
        .description = COMPOUND_STRING(
            "Gimmighoul hoard\n"
            "and treasure these\n"
            "curious coins."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GimmighoulCoin,
        .iconPalette = gItemIconPalette_GimmighoulCoin,
    },

    [ITEM_LEADERS_CREST] =
    {
        .name = ITEM_NAME("LEADER'S CREST"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "A shard of an old\n"
            "blade of some sort.\n"
            "Held by Bisharp."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_LeadersCrest,
        .iconPalette = gItemIconPalette_LeadersCrest,
    },

    [ITEM_MALICIOUS_ARMOR] =
    {
        .name = ITEM_NAME("MALICIOUS ARMOR"),
        .price = 3000,
        .description = COMPOUND_STRING(
            "Armor inhabited by\n"
            "malicious will.\n"
            "Causes evolution."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_MaliciousArmor,
        .iconPalette = gItemIconPalette_MaliciousArmor,
    },

    [ITEM_MIRROR_HERB] =
    {
        .name = ITEM_NAME("MIRROR HERB"),
        .price = 30000,
        .holdEffect = HOLD_EFFECT_MIRROR_HERB,
        .description = COMPOUND_STRING(
            "Mirrors an enemy's\n"
            "stat increases\n"
            "but only once."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_MirrorHerb,
        .iconPalette = gItemIconPalette_MirrorHerb,
    },

    [ITEM_SCROLL_OF_DARKNESS] =
    {
        .name = ITEM_NAME("SCROLL OF DARKNESS"),
        .pluralName = ITEM_PLURAL_NAME("Scrolls of Darkness"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A peculiar scroll\n"
            "with secrets of\n"
            "the dark path."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .iconPic = gItemIcon_ScrollOfDarkness,
        .iconPalette = gItemIconPalette_ScrollOfDarkness,
    },

    [ITEM_SCROLL_OF_WATERS] =
    {
        .name = ITEM_NAME("SCROLL OF WATERS"),
        .pluralName = ITEM_PLURAL_NAME("Scrolls of Waters"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A peculiar scroll\n"
            "with secrets of\n"
            "the water path."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .iconPic = gItemIcon_ScrollOfWaters,
        .iconPalette = gItemIconPalette_ScrollOfWaters,
    },

    [ITEM_TERA_ORB] =
    {
        .name = ITEM_NAME("TERA ORB"),
        .price = 0,
        .description = COMPOUND_STRING(
            "Energy charges can\n"
            "be used to cause\n"
            "Terastallization."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraOrb,
        .iconPalette = gItemIconPalette_TeraOrb,
    },

    [ITEM_TINY_BAMBOO_SHOOT] =
    {
        .name = ITEM_NAME("TINY BAMBOO SHOOT"),
        .price = 750,
        .description = COMPOUND_STRING(
            "A small and rare\n"
            "bamboo shoot. Best\n"
            "sold to gourmands."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 30,
        .iconPic = gItemIcon_TinyBambooShoot,
        .iconPalette = gItemIconPalette_TinyBambooShoot,
    },

    [ITEM_BUG_TERA_SHARD] =
    {
        .name = ITEM_NAME("BUG TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_BugTeraShard,
    },

    [ITEM_DARK_TERA_SHARD] =
    {
        .name = ITEM_NAME("DARK TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_DarkTeraShard,
    },

    [ITEM_DRAGON_TERA_SHARD] =
    {
        .name = ITEM_NAME("DRAGON TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_DragonTeraShard,
    },

    [ITEM_ELECTRIC_TERA_SHARD] =
    {
        .name = ITEM_NAME("ELECTRIC TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_ElectricTeraShard,
    },

    [ITEM_FAIRY_TERA_SHARD] =
    {
        .name = ITEM_NAME("FAIRY TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FairyTeraShard,
    },

    [ITEM_FIGHTING_TERA_SHARD] =
    {
        .name = ITEM_NAME("FIGHTING TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FightingTeraShard,
    },

    [ITEM_FIRE_TERA_SHARD] =
    {
        .name = ITEM_NAME("FIRE TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FireTeraShard,
    },

    [ITEM_FLYING_TERA_SHARD] =
    {
        .name = ITEM_NAME("FLYING TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_FlyingTeraShard,
    },

    [ITEM_GHOST_TERA_SHARD] =
    {
        .name = ITEM_NAME("GHOST TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_GhostTeraShard,
    },

    [ITEM_GRASS_TERA_SHARD] =
    {
        .name = ITEM_NAME("GRASS TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_GrassTeraShard,
    },

    [ITEM_GROUND_TERA_SHARD] =
    {
        .name = ITEM_NAME("GROUND TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_GroundTeraShard,
    },

    [ITEM_ICE_TERA_SHARD] =
    {
        .name = ITEM_NAME("ICE TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_IceTeraShard,
    },

    [ITEM_NORMAL_TERA_SHARD] =
    {
        .name = ITEM_NAME("NORMAL TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_NormalTeraShard,
    },

    [ITEM_POISON_TERA_SHARD] =
    {
        .name = ITEM_NAME("POISON TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_PoisonTeraShard,
    },

    [ITEM_PSYCHIC_TERA_SHARD] =
    {
        .name = ITEM_NAME("PSYCHIC TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_PsychicTeraShard,
    },

    [ITEM_ROCK_TERA_SHARD] =
    {
        .name = ITEM_NAME("ROCK TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_RockTeraShard,
    },

    [ITEM_STEEL_TERA_SHARD] =
    {
        .name = ITEM_NAME("STEEL TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_SteelTeraShard,
    },

    [ITEM_WATER_TERA_SHARD] =
    {
        .name = ITEM_NAME("WATER TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TeraShard,
        .iconPalette = gItemIconPalette_WaterTeraShard,
    },

    [ITEM_ADAMANT_CRYSTAL] =
    {
        .name = ITEM_NAME("ADAMANT CRYSTAL"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_ADAMANT_ORB,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A large, glowing gem\n"
            "that lets Dialga\n"
            "change form."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_AdamantCrystal,
        .iconPalette = gItemIconPalette_AdamantCrystal,
    },

    [ITEM_GRISEOUS_CORE] =
    {
        .name = ITEM_NAME("GRISEOUS CORE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_GRISEOUS_ORB,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A large, glowing gem\n"
            "that lets Giratina\n"
            "change form."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_GriseousCore,
        .iconPalette = gItemIconPalette_GriseousCore,
    },

    [ITEM_LUSTROUS_GLOBE] =
    {
        .name = ITEM_NAME("LUSTROUS GLOBE"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_LUSTROUS_ORB,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "A large, glowing gem\n"
            "that lets Palkia\n"
            "change form."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 60,
        .iconPic = gItemIcon_LustrousGlobe,
        .iconPalette = gItemIconPalette_LustrousGlobe,
    },

    [ITEM_BLACK_AUGURITE] =
    {
        .name = ITEM_NAME("BLACK AUGURITE"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A black stone that\n"
            "makes some Pokémon\n"
            "evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_BlackAugurite,
        .iconPalette = gItemIconPalette_BlackAugurite,
    },

    [ITEM_LINKING_CORD] =
    {
        .name = ITEM_NAME("LINKING CORD"),
        .price = 8000,
        .description = COMPOUND_STRING(
            "A mysterious string\n"
            "that makes some\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_LinkingCord,
        .iconPalette = gItemIconPalette_LinkingCord,
    },

    [ITEM_PEAT_BLOCK] =
    {
        .name = ITEM_NAME("PEAT BLOCK"),
        .price = 20000,
        .description = COMPOUND_STRING(
            "A block of material\n"
            "that makes some\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_PeatBlock,
        .iconPalette = gItemIconPalette_PeatBlock,
    },

    [ITEM_BERSERK_GENE] =
    {
        .name = ITEM_NAME("BERSERK GENE"),
        .price = 20,
        .holdEffect = HOLD_EFFECT_BERSERK_GENE,
        .description = COMPOUND_STRING(
            "Sharply boosts\n"
            "Attack, but causes\n"
            "lasting confusion."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .flingPower = 10,
        .iconPic = gItemIcon_BerserkGene,
        .iconPalette = gItemIconPalette_BerserkGene,
    },

    [ITEM_FAIRY_FEATHER] =
    {
        .name = ITEM_NAME("FAIRY FEATHER"),
        .price = 1000,
        .holdEffect = HOLD_EFFECT_TYPE_POWER,
        .holdEffectParam = TYPE_BOOST_PARAM,
        .description = COMPOUND_STRING(
            "A hold item that\n"
            "raises the power of\n"
            "Fairy-type moves."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TYPE_BOOST_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .secondaryId = TYPE_FAIRY,
        .flingPower = 10,
        .iconPic = gItemIcon_FairyFeather,
        .iconPalette = gItemIconPalette_FairyFeather,
    },

    [ITEM_SYRUPY_APPLE] =
    {
        .name = ITEM_NAME("SYRUPY APPLE"),
        .price = 2200,
        .description = COMPOUND_STRING(
            "A very syrupy apple\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 30,
        .iconPic = gItemIcon_SyrupyApple,
        .iconPalette = gItemIconPalette_SyrupyApple,
    },

    [ITEM_UNREMARKABLE_TEACUP] =
    {
        .name = ITEM_NAME("UNREMARKABLE TEACUP"),
        .price = 1600,
        .description = COMPOUND_STRING(
            "A cracked teacup\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_UnremarkableTeacup,
        .iconPalette = gItemIconPalette_UnremarkableTeacup,
    },

    [ITEM_MASTERPIECE_TEACUP] =
    {
        .name = ITEM_NAME("MASTERPIECE TEACUP"),
        .price = 38000,
        .description = COMPOUND_STRING(
            "A chipped teacup\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .flingPower = 80,
        .iconPic = gItemIcon_MasterpieceTeacup,
        .iconPalette = gItemIconPalette_MasterpieceTeacup,
    },

    [ITEM_CORNERSTONE_MASK] =
    {
        .name = ITEM_NAME("CORNERSTONE MASK"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_OGERPON_MASK,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Allows Ogerpon to\n"
            "wield the Rock-\n"
            "type in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_CornerstoneMask,
        .iconPalette = gItemIconPalette_CornerstoneMask,
    },

    [ITEM_WELLSPRING_MASK] =
    {
        .name = ITEM_NAME("WELLSPRING MASK"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_OGERPON_MASK,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Allows Ogerpon to\n"
            "wield the Water-\n"
            "type in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_WellspringMask,
        .iconPalette = gItemIconPalette_WellspringMask,
    },

    [ITEM_HEARTHFLAME_MASK] =
    {
        .name = ITEM_NAME("HEARTHFLAME MASK"),
        .price = 0,
        .holdEffect = HOLD_EFFECT_OGERPON_MASK,
        .holdEffectParam = 20,
        .description = COMPOUND_STRING(
            "Allows Ogerpon to\n"
            "wield the Fire-\n"
            "type in battle."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_SPECIAL_HELD_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_HearthflameMask,
        .iconPalette = gItemIconPalette_HearthflameMask,
    },

    [ITEM_HEALTH_MOCHI] =
    {
        .name = ITEM_NAME("HEALTH MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Health Mochi"),
        .price = 500,
        .description = sHealthFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_HpMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_HealthMochi,
    },

    [ITEM_MUSCLE_MOCHI] =
    {
        .name = ITEM_NAME("MUSCLE MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Muscle Mochi"),
        .price = 500,
        .description = sMuscleFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_AtkMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_MuscleMochi,
    },

    [ITEM_RESIST_MOCHI] =
    {
        .name = ITEM_NAME("RESIST MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Resist Mochi"),
        .price = 500,
        .description = sResistFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_DefMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_ResistMochi,
    },

    [ITEM_GENIUS_MOCHI] =
    {
        .name = ITEM_NAME("GENIUS MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Genius Mochi"),
        .price = 500,
        .description = sGeniusFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpatkMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_GeniusMochi,
    },

    [ITEM_CLEVER_MOCHI] =
    {
        .name = ITEM_NAME("CLEVER MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Clever Mochi"),
        .price = 500,
        .description = sCleverFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpdefMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_CleverMochi,
    },

    [ITEM_SWIFT_MOCHI] =
    {
        .name = ITEM_NAME("SWIFT MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Swift Mochi"),
        .price = 500,
        .description = sSwiftFeatherDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .effect = gItemEffect_SpeedMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_SwiftMochi,
    },

    [ITEM_FRESH_START_MOCHI] =
    {
        .name = ITEM_NAME("FRESH-START MOCHI"),
        .pluralName = ITEM_PLURAL_NAME("Fresh-Start Mochi"),
        .price = 300,
        .description = COMPOUND_STRING(
            "An item that resets\n"
            "all base points of\n"
            "a Pokémon."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_STAT_BOOST_MOCHI,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_ResetEVs,
        .effect = gItemEffect_ResetMochi,
        .flingPower = 30,
        .iconPic = gItemIcon_Mochi,
        .iconPalette = gItemIconPalette_FreshStartMochi,
    },

    [ITEM_GLIMMERING_CHARM] =
    {
        .name = ITEM_NAME("GLIMMERING CHARM"),
        .price = 0,
        .importance = 1,
        .description = COMPOUND_STRING(
            "A charm that will\n"
            "raise the shards\n"
            "from Tera Raids."),
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GlimmeringCharm,
        .iconPalette = gItemIconPalette_GlimmeringCharm,
    },

    [ITEM_METAL_ALLOY] =
    {
        .name = ITEM_NAME("METAL ALLOY"),
        .price = 6000,
        .description = COMPOUND_STRING(
            "A peculiar metal\n"
            "that makes certain\n"
            "Pokémon evolve."),
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_EVOLUTION_ITEM,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_EvolutionStone,
        .effect = gItemEffect_EvoItem,
        .iconPic = gItemIcon_MetalAlloy,
        .iconPalette = gItemIconPalette_MetalAlloy,
    },

    [ITEM_STELLAR_TERA_SHARD] =
    {
        .name = ITEM_NAME("STELLAR TERA SHARD"),
        .price = 0,
        .description = sTeraShardDesc,
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_TERA_SHARD,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_StellarTeraShard,
        .iconPalette = gItemIconPalette_StellarTeraShard,
    },

    [ITEM_JUBILIFE_MUFFIN] =
    {
        .name = ITEM_NAME("JUBILIFE MUFFIN"),
        .price = 250,
        .description = sFullHealDesc,
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_STATUS_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_CURE_STATUS,
        .effect = gItemEffect_FullHeal,
        .flingPower = 30,
        .iconPic = gItemIcon_JubilifeMuffin,
        .iconPalette = gItemIconPalette_JubilifeMuffin,
    },

    [ITEM_REMEDY] =
    {
        .name = ITEM_NAME("REMEDY"),
        .pluralName = ITEM_PLURAL_NAME("Remedies"),
        .price = 150,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
            "by 20 points."),
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_Remedy,
        .flingPower = 30,
        .iconPic = gItemIcon_Remedy,
        .iconPalette = gItemIconPalette_Remedy,
    },

    [ITEM_FINE_REMEDY] =
    {
        .name = ITEM_NAME("FINE REMEDY"),
        .pluralName = ITEM_PLURAL_NAME("Fine Remedies"),
        .price = 150,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 60 points."),
        #else
            "by 50 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_FineRemedy,
        .flingPower = 30,
        .iconPic = gItemIcon_FineRemedy,
        .iconPalette = gItemIconPalette_FineRemedy,
    },

    [ITEM_SUPERB_REMEDY] =
    {
        .name = ITEM_NAME("SUPERB REMEDY"),
        .pluralName = ITEM_PLURAL_NAME("Superb Remedies"),
        .price = 750,
        .description = COMPOUND_STRING(
            "A bitter powder\n"
            "that restores HP\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "by 120 points."),
        #else
            "by 200 points."),
        #endif
        .pocket = POCKET_MEDICINE,
        .sortType = ITEM_TYPE_HEALTH_RECOVERY,
        .type = ITEM_USE_PARTY_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_Medicine,
        .battleUsage = EFFECT_ITEM_RESTORE_HP,
        .effect = gItemEffect_SuperbRemedy,
        .flingPower = 30,
        .iconPic = gItemIcon_SuperbRemedy,
        .iconPalette = gItemIconPalette_SuperbRemedy,
    },

    [ITEM_AUX_EVASION] =
    {
        .name = ITEM_NAME("AUX EVASION"),
        .price = 800,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "evasiveness during\n"
            "one battle."),
        #else
            "Raises evasiveness\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxBottle,
        .iconPalette = gItemIconPalette_AuxEvasion,
    },

    [ITEM_AUX_GUARD] =
    {
        .name = ITEM_NAME("AUX GUARD"),
        .price = 400,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "defenses during\n"
            "one battle."),
        #else
            "Raises defenses\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxBottle,
        .iconPalette = gItemIconPalette_AuxGuard,
    },

    [ITEM_AUX_POWER] =
    {
        .name = ITEM_NAME("AUX POWER"),
        .price = 400,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "offenses during\n"
            "one battle."),
        #else
            "Raises offenses\n"
            "during one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxBottle,
        .iconPalette = gItemIconPalette_AuxPower,
    },

    [ITEM_AUX_POWERGUARD] =
    {
        .name = ITEM_NAME("AUX POWERGUARD"),
        .price = 1200,
        .holdEffectParam = X_ITEM_STAGES,
        .description = COMPOUND_STRING(
        #if B_X_ITEMS_BUFF >= GEN_7
            "Sharply raises\n"
            "offense & defense\n"
            "during one battle."),
        #else
            "Raises offense\n"
            "and defense during\n"
            "one battle."),
        #endif
        .pocket = POCKET_ITEMS,
        .sortType = ITEM_TYPE_AUX_ITEM,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_AuxPowerguard,
        .iconPalette = gItemIconPalette_AuxPowerguard,
    },

    [ITEM_CHOICE_DUMPLING] =
    {
        .name = ITEM_NAME("CHOICE DUMPLING"),
        .price = 1200,
        .description = sQuestionMarksDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_ChoiceDumpling,
        .iconPalette = gItemIconPalette_ChoiceDumpling,
    },

    [ITEM_SWAP_SNACK] =
    {
        .name = ITEM_NAME("SWAP SNACK"),
        .price = 1200,
        .description = sQuestionMarksDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_SwapSnack,
        .iconPalette = gItemIconPalette_SwapSnack,
    },

    [ITEM_TWICE_SPICED_RADISH] =
    {
        .name = ITEM_NAME("TWICE-SPICED RADISH"),
        .pluralName = ITEM_PLURAL_NAME("Twice-Spiced Radishes"),
        .price = 1600,
        .description = sQuestionMarksDesc,
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        //.effect = currently missing
        .iconPic = gItemIcon_TwiceSpicedRadish,
        .iconPalette = gItemIconPalette_TwiceSpicedRadish,
    },

    [ITEM_POKESHI_DOLL] =
    {
        .name = ITEM_NAME("POKéSHI DOLL"),
        .price = 2000,
        .description = COMPOUND_STRING(
            "A wooden toy\n"
            "resembling a Poké-\n"
            "mon. Can be sold."),
        .pocket = POCKET_TREASURES,
        .sortType = ITEM_TYPE_SELLABLE,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_PokeshiDoll,
        .iconPalette = gItemIconPalette_PokeshiDoll,
    },

// HnS Items

    [ITEM_GS_BALL] =
    {
        .name = ITEM_NAME("GS BALL"),
        .price = 1000,
        .description = COMPOUND_STRING(
            "A strange Poké Ball\n"
            "with a gold and\n"
            "silver design."),
        .pocket = POCKET_POKE_BALLS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_GSBall,
        .iconPalette = gItemIconPalette_GSBall,
    },

    [ITEM_FERTILIZER] =
    {
        .name = ITEM_NAME("GROWTH MULCH"),
        .price = 2500,
        .description = COMPOUND_STRING(
            "A fertilizer that\n"
            "accelerates the\n"
            "growth of Berries."),
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

    [ITEM_EXP_SHARE_SMALL] =
    {
        .name = ITEM_NAME("EXP. SHARE S"),
        .price = 6000,
        .holdEffect = HOLD_EFFECT_EXP_SHARE,
        .description = COMPOUND_STRING(
            "A held item that\n"
            "gets Exp. Points\n"
            "from battles."),
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

    [ITEM_HEALING_HEART] =
    {
        .name = ITEM_NAME("HEALING HEART"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A heart that heals\n"
            "your party when\n"
            "used in the field."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_HealingHeart,
        .iconPalette = gItemIconPalette_HealingHeart,
    },

    [ITEM_INFINITE_REPEL] =
    {
        .name = ITEM_NAME("INFIN. REPEL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An item that repels\n"
            "weak Pokémon\n"
            "permanently."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

    [ITEM_INFINITE_RARE_CANDIES] =
    {
        .name = ITEM_NAME("RARECANDY BOX"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A box of Rare Candy\n"
            "that never runs\n"
            "out."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_InfiniteRareCandies,
        .iconPic = gItemIcon_RareCandy,
        .iconPalette = gItemIconPalette_RareCandy,
    },

    [ITEM_CLEAR_BELL] =
    {
        .name = ITEM_NAME("CLEAR BELL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A bell that makes a\n"
            "clear, pure sound.\n"
            "It calms Pokémon."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_ClearBell,
        .iconPalette = gItemIconPalette_ClearBell,
    },

    [ITEM_LOST_ITEM] =
    {
        .name = ITEM_NAME("LOST ITEM"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An item lost by a\n"
            "girl in Saffron\n"
            "City."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_LostItem,
        .iconPalette = gItemIconPalette_LostItem,
    },

    [ITEM_MACHINE_PART] =
    {
        .name = ITEM_NAME("MACHINE PART"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A part needed to\n"
            "repair the Power\n"
            "Plant generator."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MachinePart,
        .iconPalette = gItemIconPalette_MachinePart,
    },

    [ITEM_MYSTERY_EGG] =
    {
        .name = ITEM_NAME("MYSTERY EGG"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An Egg obtained\n"
            "from Mr. Pokémon.\n"
            "Give it to Elm."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_MysteryEgg,
        .iconPalette = gItemIconPalette_MysteryEgg,
    },

    [ITEM_PASS] =
    {
        .name = ITEM_NAME("PASS"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A pass for the\n"
            "Magnet Train between\n"
            "Goldenrod and Saffron."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_HnsPass,
        .iconPalette = gItemIconPalette_HnsPass,
    },

    [ITEM_RAINBOW_WING] =
    {
        .name = ITEM_NAME("RAINBOW WING"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A mystical feather\n"
            "of rainbow colors.\n"
            "It is sacred."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RainbowWing,
        .iconPalette = gItemIconPalette_RainbowWing,
    },

    [ITEM_RED_SCALE] =
    {
        .name = ITEM_NAME("RED SCALE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A scale from the\n"
            "red Gyarados at\n"
            "the Lake of Rage."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_RedScale,
        .iconPalette = gItemIconPalette_RedScale,
    },

    [ITEM_SECRET_POTION] =
    {
        .name = ITEM_NAME("SECRETPOTION"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A secret medicine\n"
            "made in Cianwood\n"
            "City pharmacy."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SecretPotion,
        .iconPalette = gItemIconPalette_SecretPotion,
    },

    [ITEM_SILVER_WING] =
    {
        .name = ITEM_NAME("SILVER WING"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A mystical silver\n"
            "feather. It is said\n"
            "to summon Lugia."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_SilverWing,
        .iconPalette = gItemIconPalette_SilverWing,
    },

    [ITEM_TIDAL_BELL] =
    {
        .name = ITEM_NAME("TIDAL BELL"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A bell that produces\n"
            "an echoing sound\n"
            "that calls Lugia."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_TidalBell,
        .iconPalette = gItemIconPalette_TidalBell,
    },

    [ITEM_RADIO] =
    {
        .name = ITEM_NAME("RADIO"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A portable radio\n"
            "that picks up\n"
            "various channels."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Radio,
        .iconPalette = gItemIconPalette_Radio,
    },

    [ITEM_SQUIRT_BOTTLE] =
    {
        .name = ITEM_NAME("SQUIRTBOTTLE"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A bottle for\n"
            "watering plants\n"
            "and Sudowoodo."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_FIELD,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

    [ITEM_ROOM_1_KEY] =
    {
        .name = ITEM_NAME("RM. 1 KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A key to a room\n"
            "in the Underground\n"
            "Warehouse."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Room1Key,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_ROOM_2_KEY] =
    {
        .name = ITEM_NAME("RM. 2 KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A key to a room\n"
            "in the Underground\n"
            "Warehouse."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Room2Key,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_ROOM_4_KEY] =
    {
        .name = ITEM_NAME("RM. 4 KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A key to a room\n"
            "in the Underground\n"
            "Warehouse."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Room4Key,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_ROOM_6_KEY] =
    {
        .name = ITEM_NAME("RM. 6 KEY"),
        .price = 0,
        .description = COMPOUND_STRING(
            "A key to a room\n"
            "in the Underground\n"
            "Warehouse."),
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_Room6Key,
        .iconPalette = gItemIconPalette_Key,
    },

    [ITEM_UNUSED_BERRY_1] =
    {
        .name = ITEM_NAME("SITRUS BERRY"),
        .price = 20,
        .holdEffect = HOLD_EFFECT_RESTORE_HP,
        .holdEffectParam = 30,
        .description = COMPOUND_STRING(
            "A hold item. Restores\n"
            "the holder's HP by\n"
            "30 points."),
        .pocket = POCKET_BERRIES,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

    [ITEM_UNUSED_BERRY_2] =
    {
        .name = ITEM_NAME("????????"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An unused item\n"
            "placeholder."),
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },

    [ITEM_UNUSED_BERRY_3] =
    {
        .name = ITEM_NAME("????????"),
        .price = 0,
        .description = COMPOUND_STRING(
            "An unused item\n"
            "placeholder."),
        .pocket = POCKET_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
        .iconPic = gItemIcon_QuestionMark,
        .iconPalette = gItemIconPalette_QuestionMark,
    },
};

#undef ITEM_NAME
#undef ITEM_PLURAL_NAME
