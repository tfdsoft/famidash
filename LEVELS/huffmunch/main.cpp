// Huffmunch
// Brad Smith, 2019
// https://github.com/bbbradsmith/huffmunch

#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

const int VERSION_MAJOR = 1;
const int VERSION_MINOR = 5;

#include "huffmunch.h"

bool verbose = false;
unsigned int header_width = 2;

int huffmunch_file(const char* file_in, const char* file_out)
{
	unsigned char* buffer_in = NULL;
	unsigned char* buffer_out = NULL;
	unsigned int size_in = 0;
	unsigned int size_out = 0;

	FILE* f = fopen(file_in, "rb");
	if (f == NULL)
	{
		printf("error: file %s not found\n", file_in);
		return -1;
	}
	fseek(f,0,SEEK_END);
	size_in = ftell(f);
	size_out = size_in + 1024;
	fseek(f,0,SEEK_SET);

	buffer_in = (unsigned char*)malloc((size_in * 2) + 1024);
	buffer_out = buffer_in + size_in;

	if (buffer_in == NULL)
	{
		fclose(f);
		printf("error: out of memory\n");
		return -1;
	}
	fread(buffer_in,1,size_in,f);
	fclose(f);
	printf("%6d bytes read from %s\n", size_in, file_in);

	int result = huffmunch_compress(buffer_in, size_in, buffer_out, size_out, NULL, 0);
	if (result != HUFFMUNCH_OK)
	{
		printf("error: compression error %d: %s\n", result, huffmunch_error_description(result));
		return result;
	}
	printf("%6d bytes compressed: %6.2f%%\n", size_out, (100.0 * size_out)/size_in);
	// note: including the 6-byte header table in the compression size,
	//       because it's needed by the implementation for convenience,
	//       even though there is only 1 entry in the output.

	f = fopen(file_out, "wb");
	if (f == NULL)
	{
		free(buffer_in);
		printf("error: unable to open output file %s\n", file_out);
		return -1;
	}
	fwrite(buffer_out,1,size_out,f);
	fclose(f);
	printf("%6d bytes written to %s\n", size_out, file_out);
	free(buffer_in);

	return 0;
}

// helper function for huffmunch_list
int write_bank_file(
	unsigned int current_bank,
	const char* out_prefix,
	const char* out_ext,
	const unsigned char* bank_data,
	const unsigned int data_size,
	const unsigned int bank_start,
	const unsigned int bank_end)
{
	char bank_file[1024];
	if (snprintf(bank_file, sizeof(bank_file)-1, "%s%04d%s", out_prefix, current_bank, out_ext) < 0)
	{
		printf("internal error: unable to create bank filename\n");
		return -1;
	}

	FILE *fb = fopen(bank_file, "wb");
	if (fb == NULL)
	{
		printf("error: unable to open bank output file %s\n",bank_file);
		return -1;
	}
	if (bank_data && data_size) fwrite(bank_data,1,data_size,fb);
	fclose(fb);

	char line[1024];
	snprintf(line, sizeof(line), "%s: %d - %d (%d bytes)\n", bank_file, bank_start, bank_end, data_size);
	printf(line);
	return 0;
}


int huffmunch_list(const char* list_file, const char* out_file)
{
	using namespace std;

	struct Entry {
		int line_number;
		int start;
		int end;
		string path;
		unsigned int size;
	};

	unsigned int bank_size;
	unsigned int bank_max;
	vector<Entry> entries;
	vector<unsigned char> data;
	vector<unsigned int> splits;

	// parse list file

	char line[1024];
	FILE *fl = fopen(list_file, "rt");
	if (fl == NULL)
	{
		printf("error: list file %s not found\n", list_file);
		return -1;
	}
	if (!fgets(line,sizeof(line),fl))
	{
		printf("error: empty list file\n");
		fclose(fl);
		return -1;
	}
	char* next;
	errno = 0;
	bank_max = strtoul(line, &next, 0);
	if (errno)
	{
		printf("error: unable to read bank count from list file line 1\n");
		fclose(fl);
		return -1;
	}
	errno = 0;
	bank_size = strtoul(next, &next, 0);
	if (errno)
	{
		printf("error: unable to read bank size from list file line 1\n");
		fclose(fl);
		return -1;
	}
	int line_number = 1;
	while (fgets(line,sizeof(line),fl))
	{
		++line_number;

		// trim trailing whitespace (includes newline)
		int i = strlen(line) - 1;
		while (i > 0 && isspace(line[i]))
		{
			line[i] = 0;
			--i;
		}
		if (line[0] == 0) continue; // blank lines skipped

		errno = 0;
		int start = strtol(line, &next, 0);
		if (errno)
		{
			printf("error: unable to read start position on list file line %d\n",line_number);
			fclose(fl);
			return -1;
		}

		errno = 0;
		int end = strtol(next, &next, 0);
		if (errno)
		{
			printf("error: unable to read end position on list file line %d\n",line_number);
			fclose(fl);
			return -1;
		}

		while (isspace(*next)) ++next; // trim leading whitespace

		Entry e;
		e.line_number = line_number;
		e.start = start;
		e.end = end;
		e.path = string(next);
		entries.push_back(e);
	}
	fclose(fl);
	printf("%d entries read from %s\n", entries.size(), list_file);
	printf("bank size: %d\n", bank_size);

	// allow "unlimited" banks
	const unsigned int BANKS_UNLIMITED = 1<<16;
	if (bank_max < 1) bank_max = BANKS_UNLIMITED;

	// collect data

	for (unsigned int i=0; i<entries.size(); ++i)
	{
		Entry& e = entries[i];
		splits.push_back(data.size());

		// This is relative to the CWD,
		// but it would be nice if it was relative to the list file instead,
		// with the option of using an absolute path.
		const char* path = e.path.c_str();
		FILE* fb = fopen(path, "rb");
		if (fb == NULL)
		{
			printf("error: source file %s not found\n",path);
			return -1;
		}
		fseek(fb,0,SEEK_END);
		long fb_size = ftell(fb);

		int start = (e.start < 0) ? 0 : e.start;
		int end = (e.end < 0) ? fb_size : e.end;
		if (start < 0 || end > fb_size)
		{
			printf("error: source start and end (%d, %d) out of range for file %s\n",e.start,e.end,path);
			fclose(fb);
			return -1;
		}
		fseek(fb,e.start,SEEK_SET);
		for (int i=start; i<end; ++i) data.push_back(fgetc(fb));
		fclose(fb);

		unsigned int entry_size = end - start;
		if (end < start) entry_size = 0;
		if(verbose) printf("%4d: %5d bytes read from %s (%d,%d)\n", i, entry_size, path, e.start, e.end);
		e.size = entry_size;
	}
	printf("%d bytes read from %d source entries\n", data.size(), entries.size());
	assert(entries.size() == splits.size());

	// compress and output banks

	const char* out_ext = strrchr(out_file, '.');
	if (out_ext == NULL) out_ext = out_file + strlen(out_file);
	string out_prefix = string(out_file, out_ext-out_file);

	vector<unsigned char> bank;
	vector<unsigned int> bank_splits;
	vector<string> bank_stat;
	bank.resize(bank_size);

	unsigned int total_used = 0;
	unsigned int total_unused = 0;
	unsigned int last_used = 0;
	unsigned int last_unused = 0;

	unsigned int bank_start = 0;
	while (bank_start < entries.size())
	{
		if (bank_splits.size() >= bank_max)
		{
			printf("error: out of banks at entry %d/%d\n", bank_start,entries.size());
			return -1;
		}

		// find a split point for the current bank, starting at bank_start
		unsigned int bank_end_min = bank_start+1; // must store at least 1 entry
		unsigned int bank_end_max = entries.size(); // might include all entries
		unsigned int bank_end = bank_end_max; // best guess so far
		if (bank_max == 1) // single bank has to store everything
		{
			bank_end_min = bank_end_max;
		}
		else // otherwise try to make a good first guess
		{
			// assuming we can fit roughly (banksize x 2) with 50% compression,
			// use x2 input as a starting estimate
			unsigned int target = bank_size * 2;
			unsigned int accum = header_width;
			for (bank_end = bank_start; bank_end < bank_end_max; ++bank_end)
			{
				accum += (2 * header_width) + entries[bank_end].size;
				if (accum >= target) break;
			}
			if (bank_end < bank_end_min) bank_end = bank_end_min;
		}

		// iterative search to find a bank split that fits
		unsigned int result_size;
		while (true)
		{
			unsigned int data_start = splits[bank_start];
			unsigned int data_end = data.size();
			if (bank_end < splits.size()) data_end = splits[bank_end];

			assert(bank_end <= bank_end_max);
			assert(bank_end >= bank_end_min);

			vector <unsigned int> temp_splits;
			for (unsigned int i=bank_start; i<bank_end; ++i)
				temp_splits.push_back(splits[i] - data_start);

			result_size = bank_size;
			int result = huffmunch_compress(
				data.data() + data_start,
				data_end - data_start,
				bank.data(), result_size,
				temp_splits.data(), temp_splits.size());
			if (verbose) printf("Try bank %2d: %3d - %3d (%d bytes)\n",bank_splits.size(),bank_start,bank_end,result_size);

			// successfully found a split for this bank (fits in bank, and has reached our known upper-bound)
			if ((bank_end == bank_end_max) && result == HUFFMUNCH_OK) break;

			if (result == HUFFMUNCH_OUTPUT_OVERFLOW) // too big
			{
				// too much for bank, binary search smaller if possible
				if (bank_end <= bank_end_min) // nothing left to try, fail
				{
					printf("error: can't fit entry %d at bank %d. %d compressed bytes > %d\n",
						bank_start, bank_splits.size(), result_size, bank_size);
					return -1;
				}
				bank_end_max = bank_end - 1; // max has to be at least 1 smaller
			}
			else if (result == HUFFMUNCH_OK) // fits, but more might be possible
			{
				bank_end_min = bank_end; // found a new valid min
			}
			else // failure
			{
				printf("error: compression error %d: %s\n", result, huffmunch_error_description(result));
				return result;
			}

			// choose next guess based on current compression ratio
			unsigned int target = bank_size * (data_end - data_start) / result_size;
			unsigned int accum = header_width;
			unsigned int bank_end_next = bank_start;
			for (; bank_end_next <= bank_end_max; ++bank_end_next)
			{
				accum += (2 * header_width) + entries[bank_end_next].size;
				if (accum >= target) break;
			}
			if (bank_end_next < bank_end_min) bank_end_next = bank_end_min;
			if (bank_end_next > bank_end_max) bank_end_next = bank_end_max;
			if (bank_end_next == bank_end) bank_end_next += 1; // in this case, bank_end == bank_end_min, don't need to retry it
			bank_end = bank_end_next;
		}

		// success: write the bank
		int result = write_bank_file(
			bank_splits.size(),
			out_prefix.c_str(), out_ext,
			bank.data(), result_size,
			bank_start, bank_end);
		if (result) return result;

		bank_splits.push_back(bank_end);
		total_used += result_size;
		total_unused += (bank_size - result_size);
		assert(bank_end > bank_start);
		assert(bank_end <= entries.size());
		bank_start = bank_end;
	}

	// if number of banks is explicit, always generate them all
	while (bank_max != BANKS_UNLIMITED && bank_splits.size() < bank_max)
	{
		int result = write_bank_file(
			bank_splits.size(),
			out_prefix.c_str(), out_ext,
			NULL, 0,
			entries.size(), entries.size());
		if (result) return result;
		bank_splits.push_back(entries.size());
		total_unused += bank_size;
	}
	printf("%d banks output\n", bank_splits.size());

	// output bank split table

	FILE *fo = fopen(out_file, "wb");
	if (fo == NULL)
	{
		printf("error: unable to open bank table output file %s\n",out_file);
		return -1;
	}
	for (unsigned int v: bank_splits)
	{
		for (unsigned int i=0; i<header_width; ++i)
		{
			fputc(v & 0xFF,fo);
			v >>= 8;
		}
		if (v != 0)
		{
			printf("error: entry count exceeds representable size by header width.\n");
			fclose(fo);
			return -1;
		}
	}
	fclose(fo);
	printf("bank end table written to %s\n", out_file);

	unsigned int total_size = total_used + total_unused;
	unsigned int total_compressed = total_used - (header_width * 2 * entries.size());
	// note: excluding the location + size table from compression statistics,
	//       as this is information external to the data, which would still be needed if it as uncompressed.
	//       The 2-byte per-bank entry count is included, since it's functional information needed by the implementation.

	printf("%7d bytes input\n", data.size());
	printf("%7d bytes compressed: %6.2f%%\n", total_compressed, (100.0 * total_compressed) / data.size());
	printf("%7d bytes to banks:   %6.2f%% full\n", total_used, (100.0 * total_used) / total_size);
	printf("%7d bytes unused in %d banks (%d bytes each)\n", total_unused, bank_splits.size(), bank_size);

	return 0;
}

int print_usage()
{
	printf(
		"usage:\n"
		"    huffmunch -B in.bin out.hfm\n"
		"        Compress a single file.\n"
		"    huffmunch -L in.lst out.hfm\n"
		"        Compress a set of files together from a list file.\n"
		"\n"
		"optional arguments:\n"
		"    -V\n"
		"        Verbose output.\n"
		"    -S (width)\n"
		"        Wider search is slower, but marginally increases compression, default 3 (range: 2-16).\n"
		"    -X (cutoff)\n"
		"        Number of missed attempts before halting compression, default 100, 0 unlimited.\n"
		"    -H (width)\n"
		"        Bytes per integer entry in output header, default 2.\n"
		#if HUFFMUNCH_DEBUG
		"    -D[T/B]\n"
		"        Debug output. (-DT text, -DB binary, -D auto)\n"
		#endif
		"\n");
	printf(
		"List files are a simple text format:\n"
		"    Line 1: (banks) (size)\n"
		"        banks (int) - maximum number of banks to split output into\n"
		"                      use 0 for unlimited banks\n"
		"                      use 1 if multiple banks are not needed (faster)\n"
		"        size (int) - how many bytes allowed in each bank\n"
		"    Lines 2+: (start) (end) (file)\n"
		"        start (int) - first byte to read from file\n"
		"        end (int) - last byte to read from file + 1\n"
		"                    use -1 to read the whole file\n"
		"        file - name of file extends to end of line\n"
		"    The input sources will be compressed together and packed into banks.\n"
		"    Integers can be decimal, hexadecimal (0x prefix), or octal (0 prefix).\n"
		"    Example output:\n"
		"        out.hfm - a table of %d-byte (-H) integers giving the end index of each bank\n"
		"        out0000.hfm - the first bank\n"
		"        out0001.hfm - the second bank\n"
		"\n", header_width);
	printf("huffmunch version %d.%d\n",
		VERSION_MAJOR, VERSION_MINOR);
	return -1;
}

int main(int argc, const char** argv)
{
	const char* outfile = NULL;
	const char* infile = NULL;
	int mode = -1;
	const int MODE_BIN = 0;
	const int MODE_LIST = 1;

	huffmunch_configure(HUFFMUNCH_HEADER_WIDTH, header_width); // just to ensure it matches print_usage()

	bool valid_args = true;
	for (int i=1; i<argc; ++i)
	{
		const char* arg = argv[i];
		if (arg[0] == '-')
		{
			switch (arg[1])
			{
			case 'v':
			case 'V':
				if (strlen(arg) > 2) valid_args = false;
				verbose   = true;
				break;
			case 'd':
			case 'D':
				huffmunch_debug(HUFFMUNCH_DEBUG_FULL);
				switch (arg[2])
				{
				case 't':
				case 'T':
					huffmunch_debug(HUFFMUNCH_DEBUG_FULL,1);
					break;
				case 'b':
				case 'B':
					huffmunch_debug(HUFFMUNCH_DEBUG_FULL,0);
					break;
				case 0:
					break;
				default:
					valid_args = false;
					break;
				}
				break;
			case 'b':
			case 'B':
				if (strlen(arg) > 2) valid_args = false;
				if ((i+1) >= argc) { valid_args = false; break; }
				mode = MODE_BIN;
				infile = argv[i+1]; ++i;
				break;
			case 'l':
			case 'L':
				if (strlen(arg) > 2) valid_args = false;
				if ((i+1) >= argc) { valid_args = false; break; }
				mode = MODE_LIST;
				infile = argv[i+1]; ++i;
				break;
			case 's':
			case 'S':
				if (strlen(arg) > 2) valid_args = false;
				if ((i+1) >= argc) { valid_args = false; break; }
				huffmunch_configure(HUFFMUNCH_SEARCH_WIDTH, strtoul(argv[i+1],NULL,0)); ++i;
				break;
			case 'x':
			case 'X':
				if (strlen(arg) > 2) valid_args = false;
				if ((i+1) >= argc) { valid_args = false; break; }
				huffmunch_configure(HUFFMUNCH_SEARCH_CUTOFF, strtoul(argv[i+1],NULL,0)); ++i;
				break;
			case 'h':
			case 'H':
				if (strlen(arg) > 2) valid_args = false;
				if ((i+1) >= argc) { valid_args = false; break; }
				huffmunch_configure(HUFFMUNCH_HEADER_WIDTH, strtoul(argv[i+1],NULL,0)); ++i;
				break;
			default:
				valid_args = false;
				break;
			}
			if (!valid_args) break;
		}
		else
		{
			if (outfile == NULL) 
			{
				outfile = arg;
			}
			else
			{
				valid_args = false;
				break;
			}
		}
	}
	if (!valid_args || infile == NULL || outfile == NULL)
	{
		return print_usage();
	}

	if (mode == MODE_BIN)
	{
		return huffmunch_file(infile,outfile);
	}
	else if (mode == MODE_LIST)
	{
		return huffmunch_list(infile,outfile);
	}

	return print_usage();
}

// end of file
