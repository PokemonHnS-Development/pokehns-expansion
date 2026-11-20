const struct Item gItemsInfo[] =
{
    [ITEM_SUPER_POTION] =
    {
        .name = ITEM_NAME("SUPER POTION"),
        .price = 700,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "60 points."),
        #else
            "50 points."),
        #endif
        .pocket = POCKET_MEDICINE,
    },
};
