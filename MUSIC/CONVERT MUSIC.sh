rm music.dmc
rm music.s
rm sfx.s

wine ./text2data.exe -ca65 music.txt
wine ./text2data.exe -ca65 sfx.txt
