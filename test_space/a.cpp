#include "base64.h"
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
typedef unsigned char BYTE;

std::vector<BYTE> readFile(const char *filename)
{
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<BYTE> fileData(fileSize);
    file.read((char *)&fileData[0], fileSize);
    return fileData;
}

int main()
{
    std::string b64_data = Base64::encodeFromFile("test.png");
    std::cout << b64_data.size() << std::endl;
}