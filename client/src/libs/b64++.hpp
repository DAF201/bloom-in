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

template <typename resource>
string b64_en(resource &source, int source_type)
{
    if (0 == source_type)
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

    if (1 == source_type)
    {
    }
}