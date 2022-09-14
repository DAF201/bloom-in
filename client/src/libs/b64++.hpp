#include "base64.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "base64.h"
#include "base64_file.h"
using namespace std;

typedef unsigned char BYTE;

vector<BYTE> read_binary_file(const char *filename);