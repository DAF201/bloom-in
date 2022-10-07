#include <map>
#include <string.h>
#include <exception>
#include <time.h>
#include "./libs/string++.h"

using namespace std;

const static string command_type[] = {"COMMANDS", "FILE_STREAM", "PRINTING"};

struct command
{
    string *command_type;
    string *command_content;
    string *command_send_from;
    int command_send_time;
    string command_execution_result;

    command(string *command_type, string *command_content, string *command_send_from)
    {
        this->command_type = command_type;
        this->command_content = command_content;
        this->command_send_from = command_send_from;
        this->command_send_time = (int)time(NULL);
    }

    void execute()
    {
        int start_time = (int)time(NULL);
        FILE *pipe = _popen(this->command_content->c_str(), "r");
        char pipe_buffer[128];
        string result = "";

        if (!pipe)
        {
            _pclose(pipe);
            return;
        }
        while (!feof(pipe))
        {
            if (fgets(pipe_buffer, 128, pipe) != NULL)
                result += pipe_buffer;
        }

        _pclose(pipe);
        this->command_execution_result = result;
    }
};