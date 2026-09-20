// Add entries here
// These entries are example entries which you can replace, but they exist to get you started.
// Remember to modify include/constants/help_window.h to include identifiers so they can be used in event scripts.
const struct HelpWindow gHelpWindowInfo[] =
{
    [HELP_DEMO_WINDOW] =
    {
        .header = COMPOUND_STRING("Information: Help Windows"),
        .desc = COMPOUND_STRING("This is a help window. You can put\n"
                                "mucho texto en pantalla que\n"
                                "¡los jugadores no leerán!\n\n¡No es genial!"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 4, 5},
    },
    [HELP_GAMESTART_WINDOW] =
    {
        .header = COMPOUND_STRING("Information: More Options"),
        .desc = COMPOUND_STRING("The clock can be changed from any\n"
                                "CENTRO POKéMON sin penalización.\n"
                                "Revisa los OBJETOS CLAVE de tu BOLSA\n"
                                "y el MENÚ de OPCIONES para más\n"
                                "formas de personalizar tu juego.\n"
                                "¡Disfruta!"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_TRADE_WINDOW] =
    {
        .header = COMPOUND_STRING("WARNING: COMPATIBILITY"),
        .desc = COMPOUND_STRING("Attempting to link incorrectly may result\n"
                                "daño permanente a tu partida.\n"
                                "Solo conéctate con otro jugador si:\n"
                                "Ambos juegan Heart & Soul.\n"
                                "Ambos tienen la misma versión.\n"
                                "Ambos tienen los mismos ajustes.\n"
                                "NO estás usando el randomizer."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 4, 5},
    },
    [HELP_TELEPORTER_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: TELEPORTER"),
        .desc = COMPOUND_STRING("The TELEPORTER can PERMANENTLY change\n"
                                "POKéMON en sus formas de GALAR.\n"
                                "Las formas de GALAR NO son\n"
                                "necesarias para la historia ni\n"
                                "para completar la POKéDEX NAC.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_SINJOH_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: SINJOH"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "contenido extra: SINJOH.\n"
                                "NO es necesario para la historia\n"
                                "ni para completar la POKéDEX NAC.\n"
                                "\n"
                                "Es solo un extra. Si lo quieres."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_ALOLA_WINDOW] =
    {
        .header = COMPOUND_STRING("OPTIONAL BONUS CONTENT: ISLES"),
        .desc = COMPOUND_STRING("This NPC grants access to optional\n"
                                "contenido extra: ISLAS.\n"
                                "NO es necesario para la historia\n"
                                "ni para completar la POKéDEX NAC.\n"
                                "\n"
                                "Es solo un extra. Si lo quieres."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE1_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON ABILITIES"),
        .desc = COMPOUND_STRING("PICHU's ability is STATIC.\n"
                                "La habilidad de CLEFFA es ATRACTO.\n"
                                "IGGLYBUFF's ability is CUTE CHARM.\n"
                                "TYROGUE's ability is GUTS.\n"
                                "SMOOCHUM's ability is OBLIVIOUS.\n"
                                "ELEKID's ability is STATIC.\n"
                                "MAGBY's ability is FLAME BODY."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE2_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON TYPES"),
        .desc = COMPOUND_STRING("PICHU is ELECTRIC type.\n"
                                "CLEFFA es de tipo NORMAL.\n"
                                "IGGLYBUFF es de tipo NORMAL.\n"
                                "TYROGUE es de tipo LUTAS.\n"
                                "SMOOCHUM es de tipo HIELO.\n"
                                "ELEKID es de tipo ELÉCTRICO.\n"
                                "MAGBY es de tipo FUEGO."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE3_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON CRIES"),
        .desc = COMPOUND_STRING("PICHU says WAAAH.\n"
                                "CLEFFA dice EEK.\n"
                                "IGGLYBUFF dice LALALA.\n"
                                "TYROGUE dice HIYAH.\n"
                                "SMOOCHUM dice EHEHE.\n"
                                "ELEKID dice OI, OI, OI.\n"
                                "MAGBY dice TCH."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE4_WINDOW] =
    {
        .header = COMPOUND_STRING("BABY POKéMON ACTIONS"),
        .desc = COMPOUND_STRING("PICHU likes to PLAY all day.\n"
                                "CLEFFA MIRA la luna.\n"
                                "IGGLYBUFF los DURMió.\n"
                                "TYROGUE ENTRENA sin parar.\n"
                                "A SMOOCHUM le gusta LUCIRSE.\n"
                                "ELEKID ACUMULA carga.\n"
                                "MAGBY se ENOJA a menudo."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_POKEBLOCK_WINDOW] =
    {
        .header = COMPOUND_STRING("FEEDERS: REGULAR POKéBLOCKS"),
        .desc = COMPOUND_STRING("POKéBLOCK colors attract perfect IVs:\n"
                                "ROJ: PS,ATA,VEL   AZU: PS,PAE,VEL\n"
                                "ROSA: ATK,A.ESP,VEL  VERD: PS,DEF,VEL\n"
                                "AMAR: PS,ATK,DEF   MOR: ATK,DEF,VEL\n"
                                "IND: PS,PAE,VEL   BRN: DEF,VEL,VEL\n"
                                "LBL: PAE,VEL,VEL  OLV: ATA,DEF,VEL\n"
                                "GRIS: PS,ATK,A.ESP\n"
                                "Every POKéBLOCK attracts HIDDEN ABILITY."

                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_GOLD_POKEBLOCK_WINDOW] =
    {
        .header = COMPOUND_STRING("FEEDERS: GOLD POKéBLOCKS"),
        .desc = COMPOUND_STRING("GOLD POKéBLOCKS attract POKéMON with\n"
                                "5 IVs perfectos. El sabor decide cuál\n"
                                "IV no es perfecto.\n"
                                "PICANTE: sin A.ESP   SECO: sin ATK\n"
                                "DULCE: sin D.ESP   AMARGO: sin VEL\n"
                                "ÁCIDO: sin PS\n"
                                "Every POKéBLOCK attracts HIDDEN ABILITY."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    // Add more entries
};
