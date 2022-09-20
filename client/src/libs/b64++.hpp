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
        return base64_encode(string(source));
    }

    file_stream.close();

    return Base64::encodeFromFile(source);
}

void b64_de(string b64_data, string file_path)
{
    return Base64::decodeToFile(file_path, b64_data);
}

string b64_de(string b64_data)
{
    return base64_decode(b64_data);
}