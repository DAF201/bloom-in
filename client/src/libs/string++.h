#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>
#include <type_traits>
#include <iostream>
using namespace std;

// for all string thing I may need in the future

typedef vector<string> str_vec;

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

// int is sub
bool is_sub(int &main_source, int &sub_source)
{
    string main_source_str = to_string(main_source);
    string sub_source_str = to_string(sub_source);

    cout << main_source_str << " " << sub_source_str << endl;

    if (NULL != strstr(main_source_str.c_str(), sub_source_str.c_str()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// string is sub
template <typename T>
bool is_sub(T &main_source, T &sub_source)
{
    if (is_same_v<T, string>)
    {
        if (NULL != strstr(main_source.c_str(), sub_source.c_str()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// cstring is sub
template <typename T>
bool is_sub(T &&main_source, T &&sub_source)
{

    if (is_same_v<T, const char *>)
    {
        if (NULL != strstr(main_source, sub_source))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// string then cstring is sub
template <typename T1, typename T2>
bool is_sub(T1 &main_source, T2 &&sub_source)
{
    if (is_same_v<T1, string> && is_same_v<T2, const char *>)
    {
        if (NULL != strstr(main_source.c_str(), sub_source))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

template <typename T1, typename T2>
bool is_sub(T1 &&main_source, T2 &sub_source)
{
    if (is_same_v<T1, const char *> && is_same_v<T2, string>)
    {
        if (NULL != strstr(main_source, sub_source.c_str()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}