#ifndef FILE_PLUS_PLUS
#define FILE_PLUS_PLUS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "b64++.h"
#define CHUNK_SIZE 1024

using namespace std;
// files

typedef vector<string> file_chunks;

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

file_chunks file_b64_encode(char *file_name)
{
    string file_b64_string = b64_en(file_name);
    file_chunks file_b64_data;

    for (int i = 0; i < file_b64_string.size(); i = i + CHUNK_SIZE)
    {
        file_b64_data.push_back(b64_en((char *)file_b64_string.substr(i, 1024).c_str()));
    }

    cout << file_b64_data.size() << endl;

    return file_b64_data;
}

void file_chunk_decode(file_chunks file_source, string file_name)
{
    string file_b64_string = "";
    for (int i = 0; i < file_source.size(); i++)
    {
        file_b64_string = file_b64_string + b64_de(file_source[i]);
    }

    b64_de(file_b64_string, file_name);
}
#endif