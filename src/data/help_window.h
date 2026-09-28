// Add entries here
// These entries are example entries which you can replace, but they exist to get you started.
// Remember to modify include/constants/help_window.h to include identifiers so they can be used in event scripts.
const struct HelpWindow gHelpWindowInfo[] =
{
    [HELP_DEMO_WINDOW] =
    {
        .header = COMPOUND_STRING("Información: Ventanas de ayuda"),
        .desc = COMPOUND_STRING("Esta es una ventana de ayuda.\nPuedes poner mucho texto en\npantalla ¡y nadie lo leerá!\n\n¡Qué genial!"),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 4, 5},
    },
    [HELP_GAMESTART_WINDOW] =
    {
        .header = COMPOUND_STRING("Información: Más opciones"),
        .desc = COMPOUND_STRING("El reloj se puede cambiar en\ncualquier CENTRO POKéMON sin\npenalización. Revisa los OBJETOS\nCLAVE de tu BOLSA y el MENÚ de\nOPCIONES para más opciones.\n¡Disfruta!"),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_TRADE_WINDOW] =
    {
        .header = COMPOUND_STRING("AVISO: COMPATIBILIDAD"),
        .desc = COMPOUND_STRING("Un enlace incorrecto puede dañar\ntu partida de forma permanente.\nConéctate solo si:\nAmbos juegan Heart & Soul.\nMisma versión y mismos ajustes.\nNO uses el randomizer."),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 4, 5},
    },
    [HELP_TELEPORTER_WINDOW] =
    {
        .header = COMPOUND_STRING("CONTENIDO EXTRA: TELEPORTADOR"),
        .desc = COMPOUND_STRING("El TELEPORTADOR puede cambiar\n"
                                "PERMANENTEMENTE POKéMON a sus\n"
                                "formas de GALAR. Las formas de\n"
                                "GALAR NO son necesarias para la\n"
                                "para completar la POKéDEX NAC.\n"
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_SINJOH_WINDOW] =
    {
        .header = COMPOUND_STRING("CONTENIDO EXTRA: SINJOH"),
        .desc = COMPOUND_STRING("Este NPC da acceso a contenido\nopcional: SINJOH.\nNO es necesario para la historia\nni para completar la POKéDEX NAC.\n \nEs solo un extra. Si lo quieres."),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_ALOLA_WINDOW] =
    {
        .header = COMPOUND_STRING("CONTENIDO EXTRA: ISLAS"),
        .desc = COMPOUND_STRING("Este NPC da acceso a contenido\nopcional: ISLAS.\nNO es necesario para la historia\nni para completar la POKéDEX NAC.\n \nEs solo un extra. Si lo quieres."),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_NORMAL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE1_WINDOW] =
    {
        .header = COMPOUND_STRING("HABILIDADES POKéMON BEBÉ"),
        .desc = COMPOUND_STRING("La habilidad de PICHU: ELECTRICIDAD.\nLa habilidad de CLEFFA es ATRACTO.\nLa habilidad de IGGLYBUFF es ENCANTO.\nLa habilidad de TYROGUE es AGALLAS.\nLa habilidad de SMOOCHUM es DESPISTE.\nLa habilidad de ELEKID: ELECTRICIDAD.\nLa habilidad de MAGBY: CUERPO LLAMA."),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_DAYCARE2_WINDOW] =
    {
        .header = COMPOUND_STRING("TIPOS DE POKéMON BEBÉ"),
        .desc = COMPOUND_STRING("PICHU es de tipo ELÉCTRICO.\n"
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
        .header = COMPOUND_STRING("GRITOS DE POKéMON BEBÉ"),
        .desc = COMPOUND_STRING("PICHU dice WAAAH.\n"
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
        .header = COMPOUND_STRING("ACCIONES DE POKéMON BEBÉ"),
        .desc = COMPOUND_STRING("A PICHU le gusta JUGAR todo el día.\n"
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
        .header = COMPOUND_STRING("COMEDEROS: POKéBLOCKS NORMALES"),
        .desc = COMPOUND_STRING("Los colores atraen IVs perfectos:\n"
                                "ROJ: PS,ATA,VEL   AZU: PS,A.ESP,VEL\n"
                                "ROSA: ATA,A.ESP,VEL  VERD: PS,DEF,D.ESP\n"
                                "AMAR: PS,ATA,DEF   MOR: ATA,DEF,D.ESP\n"
                                "IND: PS,A.ESP,D.ESP  BRN: DEF,VEL,D.ESP\n"
                                "LBL: A.ESP,VEL,D.ESP  OLV: ATA,DEF,VEL\n"
                                "GRIS: PS,ATA,A.ESP\n"
                                "Cada uno atrae una HABILIDAD OCULTA."

                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    [HELP_GOLD_POKEBLOCK_WINDOW] =
    {
        .header = COMPOUND_STRING("COMEDEROS: POKéBLOCKS ORO"),
        .desc = COMPOUND_STRING("Los POKéBLOCKS ORO atraen POKéMON con\n"
                                "5 IVs perfectos. El sabor decide cuál\n"
                                "IV no es perfecto.\n"
                                "PICANTE: sin A.ESP   SECO: sin ATA\n"
                                "DULCE: sin D.ESP   AMARGO: sin VEL\n"
                                "ÁCIDO: sin PS\n"
                                "Cada uno atrae una HABILIDAD OCULTA."
                            ),
        .headerFont = FONT_NORMAL,
        .descFont = FONT_SMALL,
        .headerColor = {0, 8, 3},
    },
    // Add more entries
};
