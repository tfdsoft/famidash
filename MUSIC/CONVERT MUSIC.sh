rm music.dmc
rm music.s
rm sfx.s

wine ./text2data.exe -ca65 music.txt
wine ./nsf2data.exe sfx.nsf -ca65
