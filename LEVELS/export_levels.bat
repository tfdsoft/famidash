@echo off

setlocal EnableDelayedExpansion
set n=0
SET all_levels= ^
    stereomadness ^
    backontrack ^
    polargeist ^
    dryout ^
    baseafterbase ^
    cantletgo ^
    jumper ^
    timemachine ^
    cycles ^
    xstep ^
    clutterfunk ^
    theoryofeverything ^
    test ^
    test2 ^
    test3 ^
    test4 ^


echo Exporting everything %all_levels%
export_levels.py --folder "the folder that you do stuff in" %all_levels%

echo Export finished.
pause
exit
