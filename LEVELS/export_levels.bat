@echo off

setlocal EnableDelayedExpansion
SET ownpath=%~dp0
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
    decode ^
    test ^
    test2 ^
    test3 ^
    test4 ^
    danger ^


echo Exporting everything %all_levels%
python %ownpath%export_levels.py --folder "%ownpath%LEVEL DATA" %all_levels%

echo Export finished.
pause
