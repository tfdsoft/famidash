@echo off
set /P "level=Enter level name (for example, if XX_.csv, just enter XX): "

echo Exporting %level%_SP.csv
CSV2C_SP.py %level%_SP.csv

@REM echo Exporting %level%_.csv
@REM CSV_verticalifier.py %level%_.csv

@REM echo Exporting %level%_.vert
@REM vert2rle.py %level%_.vert

echo Exporting %level%_.csv
vert2rle.py %level%_.csv

echo Export finished.
pause
exit
