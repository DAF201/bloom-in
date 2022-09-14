#include "b64++.hpp"

vector<byte_data> read_binary_file(const char *filename)
{
    streampos fileSize;
    ifstream file(filename, ios::binary);
    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);
    vector<byte_data> fileData(fileSize);
    file.read((char *)&fileData[0], fileSize);
    return fileData;
}
