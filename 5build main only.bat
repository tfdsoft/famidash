del /Q TMP\*.*
bin\winmake.exe main

copy .\build\main\famidash.nes .\famidash.nes
copy .\build\main\famidash.dbg .\famidash.dbg

pause