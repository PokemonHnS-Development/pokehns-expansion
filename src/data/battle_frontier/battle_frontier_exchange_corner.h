struct BPShopEntry
{
    u16 item;
    u16 bpCost;
};

static const struct BPShopEntry sBPVitaminShopEntries[] = {
    { ITEM_PROTEIN, 1 },
    { ITEM_CALCIUM, 1 },
    { ITEM_IRON,    1 },
    { ITEM_ZINC,    1 },
    { ITEM_CARBOS,  1 },
    { ITEM_HP_UP,   1 },
    { ITEM_NONE,    0 },
};

static const struct BPShopEntry sBPHoldItemShopEntries[] = {
    { ITEM_LEFTOVERS,     48 },
    { ITEM_WHITE_HERB,    48 },
    { ITEM_QUICK_CLAW,    48 },
    { ITEM_MENTAL_HERB,   48 },
    { ITEM_BRIGHT_POWDER, 64 },
    { ITEM_CHOICE_BAND,   64 },
    { ITEM_KINGS_ROCK,    64 },
    { ITEM_FOCUS_BAND,    64 },
    { ITEM_SCOPE_LENS,    64 },
    { ITEM_NONE,           0 },
};

static const struct BPShopEntry sBPDecor1ShopEntries[] = {
    { DECOR_TREECKO_DOLL,   48 },
    { DECOR_TORCHIC_DOLL,   48 },
    { DECOR_MUDKIP_DOLL,    48 },
    { DECOR_TOGEPI_DOLL,    48 },
    { DECOR_MEOWTH_DOLL,    48 },
    { DECOR_CLEFAIRY_DOLL,  48 },
    { DECOR_DITTO_DOLL,     48 },
    { DECOR_CYNDAQUIL_DOLL, 80 },
    { DECOR_CHIKORITA_DOLL, 80 },
    { DECOR_TOTODILE_DOLL,  80 },
    { ITEM_NONE,              0 },
};

static const struct BPShopEntry sBPDecor2ShopEntries[] = {
    { DECOR_LAPRAS_DOLL,    128 },
    { DECOR_VENUSAUR_DOLL,  256 },
    { DECOR_CHARIZARD_DOLL, 256 },
    { DECOR_BLASTOISE_DOLL, 256 },
    { ITEM_NONE,              0 },
};

static const struct BPShopEntry sBPPokeBallShopEntries[] = {
    { ITEM_NET_BALL,     1 },
    { ITEM_DIVE_BALL,    1 },
    { ITEM_NEST_BALL,    1 },
    { ITEM_REPEAT_BALL,  1 },
    { ITEM_TIMER_BALL,   1 },
    { ITEM_LUXURY_BALL,  1 },
    { ITEM_NONE,         0 },
};

static const u16 sFrontierExchangeCorner_Decor1[] =
{
    DECOR_KISS_POSTER,
    DECOR_KISS_CUSHION,
    DECOR_SMOOCHUM_DOLL,
    DECOR_TOGEPI_DOLL,
    DECOR_MEOWTH_DOLL,
    DECOR_CLEFAIRY_DOLL,
    DECOR_DITTO_DOLL,
    DECOR_CYNDAQUIL_DOLL,
    DECOR_CHIKORITA_DOLL,
    DECOR_TOTODILE_DOLL,
    ITEM_LIST_END
};

static const u16 sFrontierExchangeCorner_Decor2[] =
{
    DECOR_LAPRAS_DOLL,
    DECOR_SNORLAX_DOLL,
    DECOR_VENUSAUR_DOLL,
    DECOR_CHARIZARD_DOLL,
    DECOR_BLASTOISE_DOLL,
    ITEM_LIST_END
};

static const u16 sFrontierExchangeCorner_Vitamins[] =
{
    ITEM_PROTEIN,
    ITEM_CALCIUM,
    ITEM_IRON,
    ITEM_ZINC,
    ITEM_CARBOS,
    ITEM_HP_UP,
    ITEM_LIST_END
};

static const u16 sFrontierExchangeCorner_HoldItems[] =
{
    ITEM_LEFTOVERS,
    ITEM_WHITE_HERB,
    ITEM_QUICK_CLAW,
    ITEM_MENTAL_HERB,
    ITEM_BRIGHT_POWDER,
    ITEM_CHOICE_BAND,
    ITEM_KINGS_ROCK,
    ITEM_FOCUS_BAND,
    ITEM_SCOPE_LENS,
    ITEM_LIST_END
};

static const u8 *const sFrontierExchangeCorner_Decor1Descriptions[] =
{
    BattleFrontier_ExchangeServiceCorner_Text_KissPosterDesc,
    BattleFrontier_ExchangeServiceCorner_Text_KissCushionDesc,
    BattleFrontier_ExchangeServiceCorner_Text_SmoochumDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_TogepiDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_MeowthDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_ClefairyDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_DittoDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_CyndaquilDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_ChikoritaDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_TotodileDollDesc,
    gText_Exit,
};

static const u8 *const sFrontierExchangeCorner_Decor2Descriptions[] =
{
    BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc,
    BattleFrontier_ExchangeServiceCorner_Text_LargeDollDesc,
    gText_Exit
};

static const u8 *const sFrontierExchangeCorner_VitaminsDescriptions[] =
{
    BattleFrontier_ExchangeServiceCorner_Text_ProteinDesc,
    BattleFrontier_ExchangeServiceCorner_Text_CalciumDesc,
    BattleFrontier_ExchangeServiceCorner_Text_IronDesc,
    BattleFrontier_ExchangeServiceCorner_Text_ZincDesc,
    BattleFrontier_ExchangeServiceCorner_Text_CarbosDesc,
    BattleFrontier_ExchangeServiceCorner_Text_HPUpDesc,
    gText_Exit
};

static const u8 *const sFrontierExchangeCorner_HoldItemsDescriptions[] =
{
    BattleFrontier_ExchangeServiceCorner_Text_LeftoversDesc,
    BattleFrontier_ExchangeServiceCorner_Text_WhiteHerbDesc,
    BattleFrontier_ExchangeServiceCorner_Text_QuickClawDesc,
    BattleFrontier_ExchangeServiceCorner_Text_MentalHerbDesc,
    BattleFrontier_ExchangeServiceCorner_Text_BrightpowderDesc,
    BattleFrontier_ExchangeServiceCorner_Text_ChoiceBandDesc,
    BattleFrontier_ExchangeServiceCorner_Text_KingsRockDesc,
    BattleFrontier_ExchangeServiceCorner_Text_FocusBandDesc,
    BattleFrontier_ExchangeServiceCorner_Text_ScopeLensDesc,
    gText_Exit
};
