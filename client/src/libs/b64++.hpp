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

string b64_en(char *source)
{

    fstream file_stream;
    file_stream.open(source);

    if (!file_stream.is_open())
    {
        return "";
    }

    file_stream.close();

    return Base64::encodeFromFile(source);
}