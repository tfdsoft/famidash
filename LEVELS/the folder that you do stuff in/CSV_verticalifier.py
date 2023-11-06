#!/usr/bin/python3

# written by Doug Fraker 2018, modified by skiskissue gd 2023
# this program takes csv output from Tiled
# and makes it vertical


import sys
import csv
import os


filename = sys.argv[1]
newname = filename[0:-4] + ".vert"
newname2 = os.path.basename(filename)
newname2 = newname2[0:-4]

with open(filename, 'r') as oldfile:
  reader = csv.reader(oldfile)
  your_list = list(reader)

newfile = open(newname, 'w')  # warning, this may overwrite old file !!!!!!!!!!!!!!!!!!!!!


rows = len(your_list)
columns = len(your_list[0])

loops = columns  # force int division
a = 0

j = 0
for h in range(0, loops):
	for i in range (0, rows):
		a = j + h
		newfile.write(your_list[i][a] + ",")
	# delete that last comma, back it up	
	z = newfile.tell()
	newfile.seek(z)
	newfile.write("")
z = newfile.tell()
z = z - 1
newfile.seek(z)
newfile.write(" ")


# newfile.write("\nconst unsigned char * const " + newname2 + "_list[]={\n")	
# for h in range(0, loops):
# 	if(h == loops-1):
# 		newfile.write(newname2 + "_" + str(h))
# 	else:
# 		newfile.write(newname2 + "_" + str(h) + ",")
	
#newfile.write("\n};\n\n")	
	
print("Done.")
oldfile.close
newfile.close
