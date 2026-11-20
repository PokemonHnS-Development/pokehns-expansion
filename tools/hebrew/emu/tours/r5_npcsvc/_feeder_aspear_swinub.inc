# (included) swinub: likes ITEM_ASPEAR_BERRY; talked to from the tile left of it. Every answer
# blows the player back two tiles, so each branch warps back first.
# --- 1. NO: blown back
face RIGHT
tap A 4
fieldwatch sw1_ask menu 6000
pick 1
fieldwatch sw1_no free 6000 15
warpto MAP_ICE_PATH_B3F_HNS 21 21
# --- 2. YES, then B in the bag
face RIGHT
tap A 4
fieldwatch sw2_ask menu 6000
pick 0
fieldwatch sw2_bag cb2:CB2_BagMenuRun 6000
waittaskx Task_BagMenu_HandleInput 900
waitquiet
snap sw2_bag
tap B 0
fieldwatch sw2_cancel free 6000 15
warpto MAP_ICE_PATH_B3F_HNS 21 21
# --- 3. YES, an Oran Berry: disliked
face RIGHT
tap A 4
fieldwatch sw3_ask menu 6000
pick 0
fieldwatch sw3_bag cb2:CB2_BagMenuRun 6000
waittaskx Task_BagMenu_HandleInput 900
bagseek ITEM_ORAN_BERRY
snap sw3_bag_oran
tap A 0
fieldwatch sw3_disliked free 6000 15
warpto MAP_ICE_PATH_B3F_HNS 21 21
# --- 4. YES, the liked berry: the TM
face RIGHT
tap A 4
fieldwatch sw4_ask menu 6000
pick 0
fieldwatch sw4_bag cb2:CB2_BagMenuRun 6000
waittaskx Task_BagMenu_HandleInput 900
bagseek ITEM_ASPEAR_BERRY
snap sw4_bag_liked
tap A 0
fieldwatch sw4_liked free 8000 15
warpto MAP_ICE_PATH_B3F_HNS 21 21
# --- 5. again: straight to the blow-back
face RIGHT
tap A 4
fieldwatch sw5_again free 6000 15
