//Converts 8bit wav to 7bit and adds 1
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cout << "Usage: " << argv[0] << " input.wav";
        return 0;
    }
    ifstream input_file(argv[1], ios::binary);
    string output_filename = argv[1];
    output_filename = output_filename.substr(0, output_filename.rfind(".wav"));
    output_filename += ".pcm";
    ofstream output_file(output_filename, ios::binary);

    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input_file), {});
    for (unsigned char &byte : buffer) {
        byte = 1 + byte/2;
        if(byte == 0x80) byte = 0x7F;
    }

    output_file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

    input_file.close();
    output_file.close();

    cout << "PCM completed." << endl;
    return 0;
}
