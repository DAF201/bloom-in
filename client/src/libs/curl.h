#ifndef CURL_H
#define CURL_H
#include <string>
#include "file++.h"
#include <iostream>
#include "execute.h"
using namespace std;

string _get(string url, vector<string> params, bool download = 0, string path = "../download/file.file")
{
    string cmd;
    if (!download)
    {
        string str_params = "";
        for (int i = 0; i < params.size(); i++)
        {
            str_params += (params[i] + "&");
        }
        cmd = "curl.exe " + url + "?" + str_params;
        cmd.pop_back();
        cout << cmd << endl;
    }
    else
    {
    }
}

// upload
// curl.exe -X POST 'http://50.17.163.77:5232/upload?file_name=test.txt&file_size=1000' -F 'file=@test.txt'

// download
// curl.exe -o C:\Users\daf20\Downloads\test.txt 'http://50.17.163.77:5232/download?file_name=test.txt'
#endif