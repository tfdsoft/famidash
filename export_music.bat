@echo off
cd ".\src\sniperengine"
del /Q TMP
mkdir TMP
cd ".\music"
@echo on
py export_wrapper.py