#!/bin/bash
# both.sh [HE EN] < script : send the same lines to the Hebrew and English sessions at once
# (default he3 / en3); prints both outputs, Hebrew first.
R=../hns-tools/scratch/screens/r2_battle_frontier_pass_bp_and_remaining_facilities
H=${1:-he3}; E=${2:-en3}
T=$(mktemp); cat > $T
$R/tools/s $H < $T > $T.he 2>&1 &
$R/tools/s $E < $T > $T.en 2>&1 &
wait
echo "=== $H"; cat $T.he; echo "=== $E"; cat $T.en
rm -f $T $T.he $T.en
