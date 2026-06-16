#ifndef GUARD_SHOP_H
#define GUARD_SHOP_H

extern struct ItemSlot gMartPurchaseHistory[3];

void CreatePokemartMenu(const u16 *itemsForSale);
void CreateDecorationShop1Menu(const u16 *itemsForSale);
void CreateDecorationShop2Menu(const u16 *itemsForSale);
void CB2_ExitSellMenu(void);

void CreateBPVitaminShop(void);
void CreateBPHoldItemShop(void);
void CreateBPDecorShop1(void);
void CreateBPDecorShop2(void);
void CreateBPPokeBallShop(void);
void CreateKurtBallShop(void);

#endif // GUARD_SHOP_H
