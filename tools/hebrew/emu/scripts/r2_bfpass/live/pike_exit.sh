#!/bin/bash
# pike_exit.sh SESSION PREFIX: finish the room's text, walk round the NPC (who stands on the
# carpet below the exit) to the exit at (4,3), back into the three-path room.
../hns-tools/scratch/screens/r2_battle_frontier_pass_bp_and_remaining_facilities/tools/s $1 <<EOT
drivex $2 free 20 6000
go RIGHT 1
go UP 3
go LEFT 1
go UP 2
waitctl 900
loc
EOT
