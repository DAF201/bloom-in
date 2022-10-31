#ifndef CURL_H
#define CURL_H
#include <string>
#include "file++.h"
#include <iostream>
#include "execute.h"
#include <stdio.h>
using namespace std;

// example:
// #include "./src/libs/curl.h"
// using namespace std;
// int main()
// {
//     vector<string> params;
//     params.push_back("file_name=test.txt");
//     _get("http://50.17.163.77:5232/download", params, 1, "./downloads/file.txt"); //download file
//     _post("http://50.17.163.77:5232/upload", params, 1, "test.txt"); //upload file
// }

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

string _post(string url, vector<string> params = {}, bool upload = 0, string upload_file_path = "")
{
    try
    {
        string cmd;
        if (!upload)
        {
            string str_params = "";
            for (int i = 0; i < params.size(); i++)
            {
                str_params += (params[i] + "&");
            }
            cmd = "curl.exe -X POST \"" + url + "?" + str_params;
            if (cmd.back() == '&' || cmd.back() == '?')
            {
                cmd.pop_back();
            }
            cout << cmd << endl;
            return __execute(cmd);
        }
        else
        {
            if (!file_exist(upload_file_path.c_str()))
            {
                printf("file does not exist\n");
                return "Failed";
            }
            string str_params = "";
            for (int i = 0; i < params.size(); i++)
            {
                str_params += (params[i] + "&");
            }
            cmd = "curl.exe -X POST \"" + url + "?" + str_params;
            if (cmd.back() == '&' || cmd.back() == '?')
            {
                cmd.pop_back();
            }
            cmd = cmd + "\"" + " -F " + "\"file=@" + upload_file_path + "\"";
            return __execute(cmd);
        }
    }
    catch (...)
    {
        return "Failed";
    }
}

// upload
// curl.exe -X POST 'http://50.17.163.77:5232/upload?file_name=test.txt&file_size=1000' -F 'file=@test.txt'

// download
// curl.exe -o C:\Users\daf20\Downloads\test.txt 'http://50.17.163.77:5232/download?file_name=test.txt'

#endif
