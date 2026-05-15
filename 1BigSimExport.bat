@echo off
@del /Q TMP\*.*
@cd MUSIC
@call export.bat > ..\buildmusic.log
@cd ..
@call LEVELS\export_levels.bat > buildlevels.log
@call build.bat > build.log