#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

n=0
all_levels="stereomadness leveleasy supercycles clutterfunk2 pgclubstep eon cataclysm "

echo Exporting everything ${all_levels}
python3 ${SCRIPT_DIR}/export_levels.py --folder "${SCRIPT_DIR}/LEVEL DATA" ${all_levels}

echo Export finished.

