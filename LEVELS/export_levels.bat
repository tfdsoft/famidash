@echo off

setlocal EnableDelayedExpansion
cd "%~dp0"
set n=0
SET all_levels= ^
    stereomadness ^
    leveleasy ^
    supercycles ^
    clutterfunk2 ^
    pgclubstep ^
    eon ^
    cataclysm ^


echo Exporting everything %all_levels%
python export_levels.py --folder "%ownpath%LEVEL DATA" %all_levels%

echo Export finished.
pause
