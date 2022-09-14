#include "base64.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "base64.h"
#include "base64_file.h"
using namespace std;

typedef char BYTE;

vector<BYTE> read_binary_file(const char *filename);

template <typename type>
string base64_encoding(type const &source);

template <typename type>
string base64_decoding(type const &source);