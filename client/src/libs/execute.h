#include <iostream>
#include <string>
#include <conio.h>
#include <stdio.h>

using namespace std;

string __execute(string command)
{

    char pipe_buffer[128];
    string execution_result = "";
    FILE *pipe = _popen(command.c_str(), "r");

    if (is_sub(command, "cmd") || is_sub(command, "powershell"))
    {
        return execution_result;
    }

    if (!pipe)
    {
        return "popen failed!";
    }

    while (!feof(pipe))
    {
        if (fgets(pipe_buffer, 128, pipe) != NULL)
            execution_result += pipe_buffer;
    }

    _pclose(pipe);
    return execution_result;
}