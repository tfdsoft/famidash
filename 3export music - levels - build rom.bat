@echo off
del /Q TMP\*.*
cd MUSIC
call export.bat
cd ..
call LEVELS\export_levels.bat
call build.bat