#ifndef FILE_PLUS_PLUS_H
#define FILE_PLUS_PLUS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
// files

bool file_exist(const char *filename)
{
    ifstream file(filename);
    return file.good();
}

unsigned long file_size(const char *filename)
{
    ifstream file(filename);
    return file.tellg();
}

namespace binary_file
{
    // this name "BYTE" comflict with something in std
    typedef char BYTE;

    vector<BYTE> read_binary_file(const char *filename)
    {
        try
        {
            streampos fileSize;
            ifstream file(filename, ios::binary);
            file.seekg(0, ios::end);
            fileSize = file.tellg();
            file.seekg(0, ios::beg);
            vector<BYTE> fileData(fileSize);
            file.read((char *)&fileData[0], fileSize);
            file.close();
            return fileData;
        }
        catch (...)
        {
            vector<BYTE> __NULL_vector;
            __NULL_vector.push_back('\0');
            return __NULL_vector;
        }
    }
}

string read_text_file(const char *filename)
{
    try
    {
        fstream file;
        string buffer;
        string res = "";
        file.open(filename);
        while (!file.eof())
        {
            getline(file, buffer);
            res = res + buffer;
        }
        file.close();
        return res;
    }
    catch (...)
    {
        return "";
    }
}
#endif