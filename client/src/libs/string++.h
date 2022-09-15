#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>
#include <type_traits>
#include <iostream>
using namespace std;

// for all string thing I may need in the future

/*
definitely, I can make something like

    void str_to_vec(string input_str,str_vec destination){...}

but I just don't want... I don't want to change my code style because I need to temporary use c++ while most of the time I was using script languages like lua js py

Network programming... I assume the network will not be faster than CPU with in 20 years (Now the network is already faster than my USB port which is crazy...)

*/
typedef vector<string> str_vec;

// split string by space and dump to vector
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

// remove space for cstring
char *rm_space(const char *input, int size)
{
    char *temp = nullptr;
    temp = new char[size];
    int temp_index = 0;
    for (int i = 0; i < size; i++)
    {
        if (input[i] != ' ')
        {
            temp[temp_index] = input[i];
            temp_index++;
        }
    }
    return temp;
}

// remove space
string rm_space(string input)
{
    
}

// make a string vector to a string
string strvec_to_str(str_vec input_vec)
{
    string temp = "";
    for (int i = 0; i < input_vec.size(); i++)
    {
        temp = temp + input_vec[i];
    }
    return temp;
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

// cstring then string is sub
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