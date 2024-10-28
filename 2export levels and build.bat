@echo off
del /Q TMP\*.*
call LEVELS\export_levels.bat
call build.bat