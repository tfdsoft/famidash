import sys
import csv


value = 0
run = 0

def main():
    for csv_name in sys.argv[1:]:
        print(f"converting {csv_name}...")

        with open(f"{csv_name}", 'r') as oldfile:
            reader = csv.reader(oldfile)
            your_list = list(reader)

        newfile = open(f"./{(csv_name)[:-4]}.lvl", 'wb')

        width = len(your_list[0])
        height = len(your_list)

        if(height >= 46):
            print(f"err: level {csv_name} is too tall!")
            exit()


        run = 0
        for i in range (0, width):
            for j in range (0, height):
                if (run == 0):
                    value = your_list[j][i]
                    run = 1
                else:
                    current_value = your_list[j][i]
                    if (current_value == value) and (run < 255):
                        run += 1
                    else:
                        newfile.write((int(value)%256).to_bytes())
                        newfile.write((int(run)%256).to_bytes())
                        
                        value = current_value
                        run = 1
            # end of 'for j in range'
        # end of 'for i in range'

        # get the last values
        newfile.write((int(value)%256).to_bytes())
        newfile.write((int(run)%256).to_bytes())

        print("done.")

        oldfile.close
        newfile.close

main()