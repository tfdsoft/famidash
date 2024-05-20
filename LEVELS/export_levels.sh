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
            test\
            test2\
            test3\
            test4\
            "

echo Exporting everything ${all_levels}
python3 export_levels.py --folder "LEVEL DATA" ${all_levels}

echo Export finished.

