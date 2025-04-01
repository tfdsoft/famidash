@echo off

setlocal EnableDelayedExpansion
cd "%~dp0"

echo Exporting everything specified in metadata.json5
python export_levels.py --folder "%ownpath%LEVEL DATA" --metadata "%ownpath%metadata.json5"

echo Export finished.
pause
