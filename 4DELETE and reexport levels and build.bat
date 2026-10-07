@echo off
del /Q TMP\*.*
rmdir /s /q LEVELS\include\lvlset_A\exports
rmdir /s /q LEVELS\include\lvlset_B\exports
rmdir /s /q LEVELS\include\lvlset_C\exports
rmdir /s /q LEVELS\include\lvlset_D\exports
rmdir /s /q LEVELS\include\lvlset_E\exports
rmdir /s /q LEVELS\include\lvlset_HUGE\exports
mkdir LEVELS\include\lvlset_A\exports\level
mkdir LEVELS\include\lvlset_A\exports\sprite
mkdir LEVELS\include\lvlset_B\exports\level
mkdir LEVELS\include\lvlset_B\exports\sprite
mkdir LEVELS\include\lvlset_C\exports\level
mkdir LEVELS\include\lvlset_C\exports\sprite
mkdir LEVELS\include\lvlset_D\exports\level
mkdir LEVELS\include\lvlset_D\exports\sprite
mkdir LEVELS\include\lvlset_E\exports\level
mkdir LEVELS\include\lvlset_E\exports\sprite
mkdir LEVELS\include\lvlset_HUGE\exports\level
mkdir LEVELS\include\lvlset_HUGE\exports\sprite
call LEVELS\export_levels.bat
call build.bat