const struct Item gItemsInfo[] =
{
    [ITEM_POTION] =
    {
        .name = ITEM_NAME("POTION"),
        .price = 300,
        .description = COMPOUND_STRING(
            "Restores the HP of\n"
            "a Pokémon by\n"
            "20 points."),
        .pocket = POCKET_MEDICINE,
    },
};
