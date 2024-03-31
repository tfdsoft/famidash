@echo off
set /P "level=Enter level name (for example, if XX_.csv, just enter XX): "

echo Exporting %level%_SP.csv
CSV2C_SP.py %level%_SP.csv

echo Exporting %level%_.csv
CSV_verticalifier.py %level%_.csv

echo Exporting %level%_.vert
vert2rle.py %level%_.vert

echo Export finished.
pause
exit
