bin\winmake.exe all

copy .\build\main\famidash.nes .\famidash.nes
copy .\build\main\famidash.dbg .\famidash.dbg

copy .\build\vs-sys\famidash.nes ".\famidash vs.nes"
copy .\build\vs-sys\famidash.dbg ".\famidash vs.dbg"

copy .\build\b-sides\famidash.nes ".\Famidash B Sides.nes"
copy .\build\b-sides\famidash.dbg ".\Famidash B Sides.dbg"

copy .\build\c-sides\famidash.nes ".\Famidash C Sides.nes"
copy .\build\c-sides\famidash.dbg ".\Famidash C Sides.dbg"

copy .\build\z-sides\famidash.nes ".\Famidash - The Album.nes"
copy .\build\z-sides\famidash.dbg ".\Famidash - The Album.dbg"
pause