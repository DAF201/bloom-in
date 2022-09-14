#include "base64.h"
#include <iostream>
#include <fstream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
typedef char BYTE;

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
    // std::vector<BYTE> binary_data = readFile("test.png");
    // for (int i = 0; i < binary_data.size(); i++)
    // {
    //     std::cout << binary_data[i];
    // }
    // std::string b64_data = Base64::encodeFromFile("test.png");
    // std::vector<BYTE> file_data = Base64::decode(b64_data);

    // std::fstream test_img;
    // test_img.open("1.png", std::ios::out | std::ios::binary);
    // test_img.write(file_data.data(), file_data.size());
    return 0;
}