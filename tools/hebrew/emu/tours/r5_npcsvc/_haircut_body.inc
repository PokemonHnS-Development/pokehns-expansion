# (included) the haircut flow from the tile left of the brother
# --- 1. YES, then B in the party menu
face RIGHT
tap A 4
fieldwatch h1_offer menu 6000
pick 0
fieldwatch h1_which cb2:CB2_UpdatePartyMenu 6000
waittaskx Task_HandleChooseMonInput 900
waitquiet
snap h1_party
tap B 0
fieldwatch h1_declined free 6000

# --- 2. YES, the Egg
face RIGHT
tap A 4
fieldwatch h2_offer menu 6000
pick 0
fieldwatch h2_which cb2:CB2_UpdatePartyMenu 6000
waittaskx Task_HandleChooseMonInput 900
waitquiet
seek 8 @gPartyMenu+9@ 1 DOWN
tap A 0
fieldwatch h2_egg free 6000

# --- 3. ¥100: not enough
setmoney 100
face RIGHT
tap A 4
fieldwatch h3_offer menu 6000
pick 0
fieldwatch h3_which cb2:CB2_UpdatePartyMenu 6000
waittaskx Task_HandleChooseMonInput 900
waitquiet
tap A 0
fieldwatch h3_nomoney free 6000

# --- 4. ¥10000: the cut
setmoney 10000
face RIGHT
tap A 4
fieldwatch h4_offer menu 6000
pick 0
fieldwatch h4_which cb2:CB2_UpdatePartyMenu 6000
waittaskx Task_HandleChooseMonInput 900
waitquiet
tap A 0
fieldwatch h4_cut free 12000 20

# --- 5. once a day
face RIGHT
tap A 4
fieldwatch h5_again free 6000

# --- 6. NO (flag cleared again; no release: last)
ev clearflag FLAG_DAILY_HAIRCUT1_RECEIVED; clearflag FLAG_DAILY_HAIRCUT2_RECEIVED; end
face RIGHT
tap A 4
fieldwatch h6_offer menu 6000
pick 1
pages h6_no 4
