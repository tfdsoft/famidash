del /Q TMP\*.*
bin\winmake.exe
copy .\build\famidash.nes ".\Famidash - The Album.nes"
copy .\build\famidash.dbg ".\Famidash - The Album.dbg"
pause