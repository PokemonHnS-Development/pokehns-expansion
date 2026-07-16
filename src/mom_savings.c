#include "global.h"
#include "mom_savings.h"
#include "main.h"
#include "item.h"
#include "random.h"
#include "constants/items.h"
#include "constants/decorations.h"
#include "constants/vars.h"
#include "constants/flags.h"
#include "event_data.h"
#include "string_util.h"
#include "strings.h"
#include "script.h"
#include "menu_helpers.h"
#include "money.h"
#include "menu.h"
#include "task.h"
#include "sound.h"
#include "constants/songs.h"
#include "text_window.h"
#include "palette.h"
#include "window.h"
#include "bg.h"
#include "fieldmap.h"
#include "constants/map_types.h"
#include "decoration_inventory.h"
#include "randomizer.h"

extern const u8 EventScript_MomGiftCall_Item[];
extern const u8 EventScript_MomGiftCall_Berry[];
extern const u8 EventScript_MomGiftCall_Decoration[];

#define MAX_PLAYER_MONEY 9999999
#define MOM_GIFT_STARTER_DOLL 0xFFFF


static const struct MomGiftSequential sMomGifts_Sequential[] = {
    {ITEM_SUPER_POTION,      900,    600,   FALSE},
    {ITEM_REPEL,             4000,   270,   FALSE},
    {ITEM_SILK_SCARF,        7000,   600,   FALSE},
    {MOM_GIFT_STARTER_DOLL,  10000,  1000,   TRUE},
    {ITEM_MOON_STONE,        15000,  2100,  FALSE},
    {ITEM_HYPER_POTION,      19000,  1200,  FALSE},
    {ITEM_LEFTOVERS,         30000,  1500,  FALSE},
    {ITEM_CHOICE_BAND,       40000,  100,   FALSE},
    {DECOR_SNORLAX_DOLL,     50000,  22800, TRUE},
    {ITEM_MASTER_BALL,       100000, 50000, FALSE},
};

#define MOM_ITEMS_SEQUENTIAL_COUNT ARRAY_COUNT(sMomGifts_Sequential)

static const u16 sMomGifts_Berries[] = {
    ITEM_PECHA_BERRY,
    ITEM_RAWST_BERRY,
    ITEM_CHERI_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_CHESTO_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_PERSIM_BERRY,
};

#define MOM_BERRIES_COUNT ARRAY_COUNT(sMomGifts_Berries)

static bool8 Mom_CheckSequentialGifts(u32 balance, u16 *purchasedItem);
static bool8 Mom_CheckRandomBerries(u32 newBalance, u32 oldBalance, u16 *purchasedItem);
static void Mom_AddItemToPC(u16 itemId, u16 quantity, bool8 isDecoration);

void InitMomSavings(void)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;
    mom->momsMoney = 0;
    mom->normalGiftFlags = 0;
    mom->isSavingMoney = FALSE;
    mom->isInitialized = TRUE;
}

void Mom_EnsureInitialized(void)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;

    if (mom->isInitialized == TRUE)
        return;

    mom->momsMoney = 0;
    mom->normalGiftFlags = 0;
    mom->isSavingMoney = FALSE;
    mom->isInitialized = TRUE;
}

void Mom_EnableSaving(bool8 enable)
{
    gSaveBlock1Ptr->momSavings.isSavingMoney = enable;
}

bool8 Mom_IsSavingEnabled(void)
{
    return gSaveBlock1Ptr->momSavings.isSavingMoney;
}

u32 Mom_GetBalance(void)
{
    return gSaveBlock1Ptr->momSavings.momsMoney;
}

bool8 Mom_TryDepositMoney(u32 amount)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;
    u32 oldBalance = mom->momsMoney;

    mom->momsMoney += amount;
    if (mom->momsMoney > MOM_MAX_MONEY)
        mom->momsMoney = MOM_MAX_MONEY;

    Mom_CheckForGiftPurchase(mom->momsMoney, oldBalance, FALSE);
    return TRUE;
}

bool8 Mom_AutoDepositFromBattle(u32 amount)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;
    u32 oldBalance = mom->momsMoney;

    mom->momsMoney += amount;
    if (mom->momsMoney > MOM_MAX_MONEY)
        mom->momsMoney = MOM_MAX_MONEY;

    Mom_CheckForGiftPurchase(mom->momsMoney, oldBalance, TRUE);
    return TRUE;
}

bool8 Mom_TryWithdrawMoney(u32 amount)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;

    if (mom->momsMoney < amount)
        return FALSE;

    mom->momsMoney -= amount;
    return TRUE;
}

bool8 Mom_CheckForGiftPurchase(u32 newBalance, u32 oldBalance, bool8 isAutomatic)
{
    u16 purchasedItem = ITEM_NONE;
    u16 quantity = 1;
    bool8 isDecoration = FALSE;

    if (FlagGet(FLAG_MOM_HAS_GIFT))
        return FALSE;

    if (Mom_CheckSequentialGifts(newBalance, &purchasedItem))
    {
        if (purchasedItem == MOM_GIFT_STARTER_DOLL)
        {
            u16 starterChoice = VarGet(VAR_STARTER_MON);
            switch (starterChoice)
            {
                case 0:
                    purchasedItem = DECOR_CHIKORITA_DOLL;
                    break;
                case 1:
                    purchasedItem = DECOR_CYNDAQUIL_DOLL;
                    break;
                case 2:
                    purchasedItem = DECOR_TOTODILE_DOLL;
                    break;
                default:
                    purchasedItem = DECOR_TOGEPI_DOLL;
                    break;
            }
            isDecoration = TRUE;
        }
        else
        {
            for (u32 i = 0; i < MOM_ITEMS_SEQUENTIAL_COUNT; i++)
            {
                if (sMomGifts_Sequential[i].itemId == purchasedItem)
                {
                    isDecoration = sMomGifts_Sequential[i].isDecoration;
                    break;
                }
            }

#if RANDOMIZER_AVAILABLE
            if (!isDecoration && RandomizerFeatureEnabled(RANDOMIZE_FIELD_ITEMS))
                purchasedItem = RandomizeFoundItem(purchasedItem, 0, 0, 0);
#endif
        }

        quantity = 1;
        Mom_AddItemToPC(purchasedItem, quantity, isDecoration);

        VarSet(VAR_MOM_GIFT_ITEM, purchasedItem);
        VarSet(VAR_MOM_GIFT_QUANTITY, isDecoration ? 0 : quantity);
        FlagSet(FLAG_MOM_HAS_GIFT);

        return TRUE;
    }

    if (isAutomatic && Mom_CheckRandomBerries(newBalance, oldBalance, &purchasedItem))
    {
        quantity = MOM_BERRY_QUANTITY;
        Mom_AddItemToPC(purchasedItem, quantity, FALSE);

        VarSet(VAR_MOM_GIFT_ITEM, purchasedItem);
        VarSet(VAR_MOM_GIFT_QUANTITY, quantity);
        FlagSet(FLAG_MOM_HAS_GIFT);

        return TRUE;
    }

    return FALSE;
}

static bool8 Mom_CheckSequentialGifts(u32 balance, u16 *purchasedItem)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;

    for (u32 i = 0; i < MOM_ITEMS_SEQUENTIAL_COUNT; i++)
    {
        if (mom->normalGiftFlags & (1 << i))
            continue;

        if (balance < sMomGifts_Sequential[i].threshold)
            continue;

        mom->normalGiftFlags |= (1 << i);
        mom->momsMoney -= sMomGifts_Sequential[i].cost;
        *purchasedItem = sMomGifts_Sequential[i].itemId;

        return TRUE;
    }

    return FALSE;
}

static bool8 Mom_CheckRandomBerries(u32 newBalance, u32 oldBalance, u16 *purchasedItem)
{
    struct MomSavingsData *mom = &gSaveBlock1Ptr->momSavings;

    u32 newTier = newBalance / MOM_RANDOM_THRESHOLD;
    u32 oldTier = oldBalance / MOM_RANDOM_THRESHOLD;

    if (newTier <= oldTier)
        return FALSE;

    u32 randomIndex = Random() % MOM_BERRIES_COUNT;
    u16 berryId = sMomGifts_Berries[randomIndex];

    mom->momsMoney -= MOM_BERRY_COST;
    *purchasedItem = berryId;

    return TRUE;
}

static bool8 Mom_GiftIsBerry(void)
{
    u16 item = VarGet(VAR_MOM_GIFT_ITEM);
    return (item >= ITEM_CHERI_BERRY && item <= ITEM_ENIGMA_BERRY);
}

static bool8 Mom_GiftIsDecoration(void)
{
    return (VarGet(VAR_MOM_GIFT_QUANTITY) == 0);
}

bool8 Mom_TryTriggerGiftCall(void)
{
    u8 mapType = gMapHeader.mapType;

    if (!FlagGet(FLAG_MOM_HAS_GIFT))
        return FALSE;

    if (mapType != MAP_TYPE_ROUTE && mapType != MAP_TYPE_OCEAN_ROUTE
     && mapType != MAP_TYPE_CITY && mapType != MAP_TYPE_TOWN)
        return FALSE;

    if (Mom_GiftIsDecoration())
        ScriptContext_SetupScript(EventScript_MomGiftCall_Decoration);
    else if (Mom_GiftIsBerry())
        ScriptContext_SetupScript(EventScript_MomGiftCall_Berry);
    else
        ScriptContext_SetupScript(EventScript_MomGiftCall_Item);

    return TRUE;
}

// ===== Money Input UI =====

#define MOM_MAX_INPUT 999999

enum {
    WIN_MOM_MONEY,
    WIN_MOM_INPUT,
    WIN_MOM_MESSAGE,
};

static const struct WindowTemplate sMomInputWindowTemplates[] = {
    [WIN_MOM_MONEY] = {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 10,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x001E,
    },
    [WIN_MOM_INPUT] = {
        .bg = 0,
        .tilemapLeft = 19,
        .tilemapTop = 11,
        .width = 9,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 0x018E,
    },
    [WIN_MOM_MESSAGE] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x01A2,
    },
    DUMMY_WIN_TEMPLATE
};

static u32 sMomInputAmount = 0;
static u32 sMomInputMaxAmount = 0;

#define tIsDeposit      data[0]
#define tWindowMoney    data[1]
#define tWindowInput    data[2]
#define tWindowMessage  data[3]

static void Task_MomInput_ShowMessage(u8 taskId);
static void Task_MomInput_InitAmountDialogue(u8 taskId);
static void Task_MomInput_HandleInput(u8 taskId);
static void MomInput_CleanupWindows(u8 taskId);

static void MomInput_DisplayMessage(u8 taskId, const u8 *text, TaskFunc callback)
{
    s16 *data = gTasks[taskId].data;
    DisplayMessageAndContinueTask(taskId, tWindowMessage, 10, 14, FONT_NORMAL, GetPlayerTextSpeedDelay(), text, callback);
    ScheduleBgCopyTilemapToVram(0);
}

static void MomInput_PrintAmount(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    FillWindowPixelBuffer(tWindowInput, PIXEL_FILL(1));
    PrintMoneyAmount(tWindowInput, 0, 1, sMomInputAmount, 0);
}

static void Task_MomInput_ShowMessage(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    const u8 *text = tIsDeposit ? gText_MomHowMuchDeposit : gText_MomHowMuchWithdraw;
    MomInput_DisplayMessage(taskId, text, Task_MomInput_InitAmountDialogue);
}

static void Task_MomInput_InitAmountDialogue(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    DrawStdFrameWithCustomTileAndPalette(tWindowInput, FALSE, 1, 13);
    MomInput_PrintAmount(taskId);
    ScheduleBgCopyTilemapToVram(0);

    gTasks[taskId].func = Task_MomInput_HandleInput;
}

static void Task_MomInput_HandleInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (AdjustQuantityAccordingToDPadInput_MomVersion(&sMomInputAmount, sMomInputMaxAmount) == TRUE)
    {
        MomInput_PrintAmount(taskId);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        gSpecialVar_0x8000 = sMomInputAmount;

        if (tIsDeposit)
        {
            RemoveMoney(&gSaveBlock1Ptr->money, sMomInputAmount);
            Mom_TryDepositMoney(sMomInputAmount);
        }
        else
        {
            Mom_TryWithdrawMoney(sMomInputAmount);
            AddMoney(&gSaveBlock1Ptr->money, sMomInputAmount);
        }

        MomInput_CleanupWindows(taskId);
        DestroyTask(taskId);
        ScriptContext_Enable();
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        gSpecialVar_0x8000 = 0;

        MomInput_CleanupWindows(taskId);
        DestroyTask(taskId);
        ScriptContext_Enable();
    }
}

static void MomInput_CleanupWindows(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    RemoveMoneyLabelObject();

    ClearStdWindowAndFrameToTransparent(tWindowMoney, FALSE);
    ClearWindowTilemap(tWindowMoney);
    RemoveWindow(tWindowMoney);

    ClearStdWindowAndFrameToTransparent(tWindowInput, FALSE);
    ClearWindowTilemap(tWindowInput);
    RemoveWindow(tWindowInput);

    ClearDialogWindowAndFrameToTransparent(tWindowMessage, FALSE);
    ClearWindowTilemap(tWindowMessage);
    RemoveWindow(tWindowMessage);

    ScheduleBgCopyTilemapToVram(0);
}

static void MomInput_Open(bool8 isDeposit)
{
    u8 taskId = CreateTask(Task_MomInput_ShowMessage, 8);
    s16 *data = gTasks[taskId].data;

    tWindowMoney = AddWindow(&sMomInputWindowTemplates[WIN_MOM_MONEY]);
    tWindowInput = AddWindow(&sMomInputWindowTemplates[WIN_MOM_INPUT]);
    tWindowMessage = AddWindow(&sMomInputWindowTemplates[WIN_MOM_MESSAGE]);

    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(tWindowMoney, 1, BG_PLTT_ID(13));
    LoadMessageBoxGfx(tWindowMoney, 0xA, BG_PLTT_ID(14));
    PutWindowTilemap(tWindowMoney);
    PutWindowTilemap(tWindowMessage);

    tIsDeposit = isDeposit;
    sMomInputAmount = 1;

    if (isDeposit)
        PrintMoneyAmountInMoneyBoxWithBorder(tWindowMoney, 1, 13, GetMoney(&gSaveBlock1Ptr->money));
    else
        PrintMoneyAmountInMoneyBoxWithBorder(tWindowMoney, 1, 13, Mom_GetBalance());

    AddMoneyLabelObject(19, 11);

    if (isDeposit)
    {
        u32 momsRemainingCapacity = MOM_MAX_MONEY - Mom_GetBalance();
        u32 playersAvailableMoney = GetMoney(&gSaveBlock1Ptr->money);
        sMomInputMaxAmount = min(MOM_MAX_INPUT, min(playersAvailableMoney, momsRemainingCapacity));
    }
    else
    {
        u32 playersWalletCapacity = MAX_PLAYER_MONEY - GetMoney(&gSaveBlock1Ptr->money);
        u32 momsAvailableMoney = Mom_GetBalance();
        sMomInputMaxAmount = min(MOM_MAX_INPUT, min(momsAvailableMoney, playersWalletCapacity));
    }

    ScriptContext_Stop();
}

static void Mom_AddItemToPC(u16 itemId, u16 quantity, bool8 isDecoration)
{
    if (isDecoration)
        DecorationAdd(itemId);
    else
        AddPCItem(itemId, quantity);
}

void Special_MomEnableSaving(void)
{
    Mom_EnableSaving(TRUE);
}

void Special_MomDisableSaving(void)
{
    Mom_EnableSaving(FALSE);
}

void Special_MomGetBalance(void)
{
    u32 balance = Mom_GetBalance();
    ConvertIntToDecimalStringN(gStringVar1, balance, STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar2, gText_PokedollarVar1);
    gSpecialVar_Result = balance;
}

void Special_MomDeposit(void)
{
    u32 amount = gSpecialVar_0x8000;
    bool8 success = Mom_TryDepositMoney(amount);
    gSpecialVar_Result = success;
}

void Special_MomWithdraw(void)
{
    u32 amount = gSpecialVar_0x8000;
    bool8 success = Mom_TryWithdrawMoney(amount);
    gSpecialVar_Result = success;
}

void Special_MomIsSavingEnabled(void)
{
    gSpecialVar_Result = Mom_IsSavingEnabled();
}

void Special_MomEnsureInitialized(void)
{
    Mom_EnsureInitialized();
}

void Special_MomOpenDepositInput(void)
{
    MomInput_Open(TRUE);
}

void Special_MomOpenWithdrawInput(void)
{
    MomInput_Open(FALSE);
}

#undef tIsDeposit
#undef tWindowMoney
#undef tWindowInput
#undef tWindowMessage
