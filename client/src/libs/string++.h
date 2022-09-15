#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <algorithm>
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

// remove space for cstring
void rm_space(char *input)
{
    int size = strlen(input);
    int index = 0;
    char *temp;
    temp = new char[size];
    for (int i = 0; i < size; i++)
    {
        if (' ' != input[i])
        {
            temp[index] = input[i];
            index++;
        }
    }
    temp[index] = '\0';
    strcpy(input, temp);
    delete temp;
}

// string remove space
void rm_space(string *input) // to avoid I totally forget how to use pointer (SO WHY DON'T JUST PASS IN REFERENCE...)
{
    input->erase(remove(input->begin(), input->end(), ' '), input->end());
}

// remove substring from string
void rm_sub(string &main_str, string &sub_str) // here you go, reference
{
    string replacement = "";
    regex target(sub_str);
    main_str = regex_replace(main_str, target, replacement);
}

// char array remove sub
void rm_sub(char *main_str, const char *sub_str)
{
    string str_main(main_str);
    string str_sub(sub_str);

    // lazy
    rm_sub(str_main, str_sub);

    strcpy(main_str, str_main.c_str());
}

// int is sub, for example 1 is a sub of 12 or 11...
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

// just for pratice purpose, and then I realize is will be just easier to use overwrite incase I am not make container or so

//  string is sub
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