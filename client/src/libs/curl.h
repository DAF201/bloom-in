#ifndef CURL_H
#define CURL_H
#include <string>
#include "file++.h"
#include <iostream>
#include "execute.h"
#include <stdio.h>
using namespace std;

string _get(string url, vector<string> params = {}, bool download = 0, string download_path = "../download/file.file")
{
    try
    {
        string cmd;
        if (!download)
        {
            string str_params = "";
            for (int i = 0; i < params.size(); i++)
            {
                str_params += (params[i] + "&");
            }
            cmd = "curl.exe -o curl_feedback.html \"" + url + "?" + str_params;
            if (cmd.back() == '&' || cmd.back() == '?')
            {
                cmd.pop_back();
            }
            cmd += "\"";
            __execute(cmd);
            string res = read_text_file("curl_feedback.html");
            remove("curl_feedback.html");
            return res;
        }
        else
        {
            string str_params = "";
            for (int i = 0; i < params.size(); i++)
            {
                str_params += (params[i] + "&");
            }
            cmd = "curl.exe -o " + download_path + " \"" + url + "?" + str_params;
            if (cmd.back() == '&' || cmd.back() == '?')
            {
                cmd.pop_back();
            }
            cmd += "\"";
            __execute(cmd);
            return download_path;
        }
    }
    catch (...)
    {
        return "Failed";
    }
}

string _post(string url, vector<string> params = {}, bool upload = 0)
{
}

// upload
// curl.exe -X POST 'http://50.17.163.77:5232/upload?file_name=test.txt&file_size=1000' -F 'file=@test.txt'

// download
// curl.exe -o C:\Users\daf20\Downloads\test.txt 'http://50.17.163.77:5232/download?file_name=test.txt'
#endif