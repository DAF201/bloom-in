#include <fstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <regex>
#include <cstring>
#include "base64.h"
#include "base64_file.h"

using namespace std;

class No_File_Exist : exception
{
public:
    char *what()
    {
        return "No file at given path";
    }
};

template <typename T>
string base64(T &source)
{
    try
    {
        fstream file;
        file.open(source);
        if (!file.is_open())
        {
            throw No_File_Exist;
        }
    }
    catch (...)
    {
        if (is_same_v(T, string))
        {
        }

        if (is_same_v(T, const char *))
        {
        }

        if (is_same_v(T, char *))
        {
        }

        return "";
    }
}