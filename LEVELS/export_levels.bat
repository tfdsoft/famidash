@echo off

setlocal EnableDelayedExpansion
cd "%~dp0"

echo Exporting everything specified in metadata.json5
python export_wrapper.py "%*"

echo Export finished.
pause
