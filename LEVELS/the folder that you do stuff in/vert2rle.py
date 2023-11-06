#!/usr/bin/python3

# written by Doug Fraker 2018, modified by skiskissue gd 2023
# this program takes csv output from CSV_verticalifier
# and turns it into a C style RLE data array that can be included


import sys
import csv
import os


filename = sys.argv[1]
newname = filename[0:-5] + ".fdstage"
newname2 = os.path.basename(filename)
newname2 = newname2[0:-5]

with open(filename, 'r') as oldfile:
  reader = csv.reader(oldfile)
  your_list = list(reader)

newfile = open(newname, 'w')  # warning, this may overwrite old file !!!!!!!!!!!!!!!!!!!!!


newfile.write("const unsigned char " + newname2 + "[]={")
for i in range(0, len(your_list[0])):
	if (i == 0):
		value = your_list[0][i]
		run = 1
	else:
		current_value = your_list[0][i]
		if (current_value == value) and (run < 255):
			run += 1 
		else:
			newfile.write(str(value) + ",")
			newfile.write(str(run) + ",")
			value = current_value
			run = 1
newfile.write(str(value) + ",")
newfile.write(str(run) + ",")
# delete that last comma, back it up	
z = newfile.tell()
newfile.seek(z)
newfile.write("};")


# newfile.write("\nconst unsigned char * const " + newname2 + "_list[]={\n")	
# for h in range(0, loops-1):
# 	if(h == loops):
# 		newfile.write(newname2 + "_" + str(h))
# 	else:
# 		newfile.write(newname2 + "_" + str(h) + ",")
	
# newfile.write("\n};\n\n")	
	
print("Done.")
oldfile.close
newfile.close
