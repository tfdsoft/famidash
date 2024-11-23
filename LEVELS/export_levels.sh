#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

n=0
all_levels="
            stereomadness\
            backontrack\
            polargeist\
            dryout\
            baseafterbase\
            cantletgo\
            jumper\
            timemachine\
            cycles\
            xstep\
            clutterfunk\
            theoryofeverything\
            electroman\
	    clubstep\
	    hexagonforce\
	    toe2\
	    thechallenge\
            leveleasy\	    
            thelightningroad\
	    nightmare\
	    demonpark\
	    decode\
            eon\
	    luckydraw\
            test2\
            test3\
            test4\
            "

echo Exporting everything ${all_levels}
python3 ${SCRIPT_DIR}/export_levels.py --folder "${SCRIPT_DIR}/LEVEL DATA" ${all_levels}

echo Export finished.

