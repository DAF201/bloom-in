#ifndef CURL_H
#define CURL_H
#include <string>
#include <file++.h>
#include <iostream>
using namespace std;
// upload
// curl.exe -X POST 'http://50.17.163.77:5232/upload?file_name=test.txt&file_size=1000' -F 'file=@test.txt'

// download
// curl.exe -o C:\Users\daf20\Downloads\test.txt 'http://50.17.163.77:5232/download?file_name=test.txt'
#endif