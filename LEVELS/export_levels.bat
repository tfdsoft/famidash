@echo off

setlocal EnableDelayedExpansion
cd "%~dp0"
set n=0
SET all_levels= ^
    stereomadness ^
    sonar ^
    leveleasy ^
    ninox ^
    lookatthislevel ^
    subzero ^
    pyrophoric ^
    subtleoddities ^
    highlife ^
    supercycles ^
    clutterfunk2 ^
    speedracer ^
    pgclubstep ^
	hell ^
    eon ^
    stalemate ^
    bloodbath ^
    cataclysm ^
    aftermath ^
    aftercatabath ^
    slaughterhouse ^
    test4 ^


echo Exporting everything %all_levels%
python export_levels.py --folder "%ownpath%LEVEL DATA" %all_levels%

echo Export finished.
pause
