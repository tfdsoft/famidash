#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

n=0
all_levels="stereomadness backontrack polargeist dryout baseafterbase cantletgo jumper timemachine cycles xstep clutterfunk theoryofeverything electroman clubstep electrodynamix hexagonforce blastprocessing toe2 retray sonar thechallenge leveleasy dreamer kappaclysm revolution lostinthewoods bloodbathbutno aprettyeasylevel thelightningroad nightmare demonpark deathmoon decode supercycles problematic firetemple foresttemple eon pgclubstep stalemate bloodbath cataclysm luckydraw test4 "

echo Exporting everything ${all_levels}
python3 ${SCRIPT_DIR}/export_levels.py --folder "${SCRIPT_DIR}/LEVEL DATA" ${all_levels}

echo Export finished.

