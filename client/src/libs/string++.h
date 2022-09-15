#include <vector>
#include <string>
#include <cstring>
#include <typeinfo>
#include <type_traits>

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

template <typename T>
bool is_sub(T &main_source, T &sub_source)
{
    if (is_same<T, int>::value)
    {
        string main_source_str = to_string(main_source);
        string sub_source_str = to_string(sub_source);

        if (0 == strcmp(main_source_str.c_str(), sub_source_str.c_str()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (is_same<T, string>::value)
    {
    }
}