del /Q TMP\*.*
bin\winmake.exe all

copy .\build\main\famidash.nes .\famidash.nes
copy .\build\main\famidash.dbg .\famidash.dbg

copy .\build\vs-sys\famidash.nes .\VS-Famidash.nes
copy .\build\vs-sys\famidash.dbg .\VS-Famidash.dbg

copy .\build\b-sides\famidash.nes .\Famidash B Sides.nes
copy .\build\b-sides\famidash.dbg .\Famidash B Sides.dbg
pause