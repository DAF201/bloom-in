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

typedef char byte_data;

vector<byte_data> read_binary_file(const char *filename);

template <typename T>
string b64encode(T &source)
{
    string encoded_data = "";
    if (NULL != strstr(typeid(source).name(), "basic_string"))
    {

        cout << "is string" << endl;
        return encoded_data;
    }

    if (NULL != strstr(typeid(source).name(), "basic_fstream"))
    {
        cout << "is file stream" << endl;
        return encoded_data;
    }
}