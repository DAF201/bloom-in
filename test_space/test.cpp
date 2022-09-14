#include <typeinfo>
#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

int main()
{
    base64_encoding(1);
    return 0;
}

template <typename type>
string base64_encoding(type const &source)
{
    if (regex_match(typeid(source).name(), regex("i")))
        cout << "is int" << endl;
}