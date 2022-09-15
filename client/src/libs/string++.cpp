#include "string++.h"

str_vec str_split_by_space(string input)
{
    string temp = "";
    str_vec result;
    for (int i = 0; i < input.length(); ++i)
    {

        if (input[i] == ' ')
        {
            result.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(input[i]);
        }
    }
    result.push_back(temp);
    return result;
}

bool str_is_in(string main_str, string sub_str)
{
    if (NULL != strstr(main_str.c_str(), sub_str.c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool str_equal(string str_1, string str_2)
{
    if (0 == strcmp(str_1.c_str(), str_2.c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}