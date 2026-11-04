const struct Item gItemsInfo[] =
{
    [ITEM_SUPER_POTION] =
    {
        .name = ITEM_NAME("שיקוי על"),
        .price = 700,
        .description = COMPOUND_STRING(
            "משקם את הנ”ח\n"
            "של פוקימון\n"
        #if I_HEALTH_RECOVERY >= GEN_7
            "ב-60 נקודות."),
        #else
            "ב-50 נקודות."),
        #endif
        .pocket = POCKET_MEDICINE,
    },
};
