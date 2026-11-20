# (included) pidgeotto: likes ITEM_QUALOT_BERRY; talked to from the tile left of it. Every answer
# blows the player back two tiles, so each branch warps back first.
# --- 1. NO: blown back
face RIGHT
tap A 4
fieldwatch pg1_ask menu 6000
pick 1
fieldwatch pg1_no free 6000 15
warpto MAP_ROUTE14_HNS 4 22
# --- 2. YES, then B in the bag
face RIGHT
tap A 4
fieldwatch pg2_ask menu 6000
pick 0
fieldwatch pg2_bag cb2:CB2_BagMenuRun 6000
waittaskx Task_BagMenu_HandleInput 900
waitquiet
snap pg2_bag
tap B 0
fieldwatch pg2_cancel free 6000 15
warpto MAP_ROUTE14_HNS 4 22
# --- 3. YES, an Oran Berry: disliked
face RIGHT
tap A 4
fieldwatch pg3_ask menu 6000
pick 0
fieldwatch pg3_bag cb2:CB2_BagMenuRun 6000
waittaskx Task_BagMenu_HandleInput 900
bagseek ITEM_ORAN_BERRY
snap pg3_bag_oran
tap A 0
fieldwatch pg3_disliked free 6000 15
warpto MAP_ROUTE14_HNS 4 22
# --- 4. YES, the liked berry: the TM
face RIGHT
tap A 4
fieldwatch pg4_ask menu 6000
pick 0
fieldwatch pg4_bag cb2:CB2_BagMenuRun 6000
waittaskx Task_BagMenu_HandleInput 900
bagseek ITEM_QUALOT_BERRY
snap pg4_bag_liked
tap A 0
fieldwatch pg4_liked free 8000 15
warpto MAP_ROUTE14_HNS 4 22
# --- 5. again: straight to the blow-back
face RIGHT
tap A 4
fieldwatch pg5_again free 6000 15
