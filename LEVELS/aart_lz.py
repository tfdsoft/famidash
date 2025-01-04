# Original script by AArt1256
# Modified by alexmush

import sys

def chunks(lst, n):
	"""Yield successive n-sized chunks from lst."""
	for i in range(0, len(lst), n):
		yield lst[i:i + n]

def find_subarray(arr, sub_arr):
    sub_len = len(sub_arr)
    for i in range(len(arr) - sub_len + 1):
        if arr[i:i+sub_len] == sub_arr:
            return i
    return -1

def compress(input_data : bytearray):
    LEN_BUFFER = 256
    final = []
    buf = [0]*LEN_BUFFER
    buf_ind = 0
    for data in chunks(input_data, LEN_BUFFER):
        data = list(data)
        data += [0] * (LEN_BUFFER - len(data))
        index = 0
        aux = []
        while index < LEN_BUFFER:
            aux.append(data[index])
            find_ind = find_subarray(buf,aux)
            if find_ind == -1 or index == LEN_BUFFER-1 or (len(aux) > 0x70 and find_ind != -1):
                if len(aux) > 1:
                    find_ind = find_subarray(buf,aux[:-1])
                    final.append(len(aux[:-1]))
                    final.append(find_ind)
                    final.append(data[index])
                    for i in aux[:-1]:
                        buf[buf_ind] = i
                        buf_ind += 1
                        buf_ind %= 256
                    buf[buf_ind] = data[index]
                    buf_ind += 1
                    buf_ind %= 256
                elif len(aux) == 1:
                    final.append(0x80)
                    final.append(data[index])
                    buf[buf_ind] = data[index]
                    buf_ind += 1
                    buf_ind %= 256
                aux = []
            index += 1
        #print(buf==data)
    final.append(0xFF)
    return bytearray(final)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("error: not enough argument given\n")
        print("example arguments:")
        print("python",sys.argv[0],"input.bin lzout.bin")
        sys.exit()

    f = open(sys.argv[1],"rb")
    final = compress(f.read())

    f = open(sys.argv[2],"wb")
    f.write(final)
    f.close()
