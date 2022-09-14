#include <fstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include "base64.h"
#include "base64_file.h"

using namespace std;

typedef char byte_data;

vector<byte_data> read_binary_file(const char *filename);

template <typename T>
void test(T &source, string name)
{
    cout << name << " : " << typeid(source).name() << endl;
}