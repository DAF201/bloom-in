#include <map>
#include <string.h>
#include <exception>
#include <time.h>
#include "./libs/string++.h"

using namespace std;

struct command
{
    string *command_content;
    string *command_send_from;
    int *command_send_time;
    string *command_execution_result;

    command(string *command_content, string *command_send_from, int *command_send_time)
    {
        this->command_content = command_content;
        this->command_send_from = command_send_from;
        this->command_send_time = command_send_time;
    }

    string execute()
    {
        FILE *pipe = _popen(this->command_content->c_str(), "r");
        string result = "";
        if (!pipe)
        {
            _pclose(pipe);
            return "Failed";
        }
    }
};