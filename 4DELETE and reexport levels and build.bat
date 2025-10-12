@echo off
del /Q TMP\*.*
rmdir /s /q LEVELS\include\lvlset_A\exports
rmdir /s /q LEVELS\include\lvlset_B\exports
rmdir /s /q LEVELS\include\lvlset_C\exports
rmdir /s /q LEVELS\include\lvlset_HUGE\exports
call LEVELS\export_levels.bat
call build.bat