#include <iostream>
#include <thread>
#include <winsock.h>
#include <string>
#include <fstream>
#include ".\libs\b64++.hpp"

#define CONFIG_FILE "./config.config"
#pragma comment(lib, "ws2_32.lib")
using namespace std;

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
        send(sock, head.c_str(), strlen(head.c_str()), 0);
    }

    void sock_send()
    {
        string buffer;
        string command;
        while (true)
        {
            getline(cin, buffer);

            if (0 == buffer.compare("exit") || 0 == sock_statu)
            {
                blooming_end();
                sock_statu = 0;
                std::exit(-1);
            }
            command = "bloom-in c <channel>" + channel + "<channel><id>" + local_id + "<id><data>" + buffer + "<data>BLOOM_IN";
            send(sock, command.c_str(), strlen(command.c_str()), 0);
        }
    }

    void sock_recv()
    {
        while (true)
        {
            recv(sock, recv_buffer, 65535, 0);
            if (0 == strcmp(recv_buffer, "close") || 0 == sock_statu || NULL != strstr(recv_buffer, local_id.c_str()) || 0 == strcmp(recv_buffer, "\0"))
            {
                blooming_end();
                sock_statu = 0;
                printf("connection closed\n");
                std::exit(-1);
            }
            printf(recv_buffer);
            printf("\n");
        }
    }

    void blooming_end()
    {
        send(sock, exit.c_str(), strlen(exit.c_str()), 0);
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
    if (argc > 1 && 0 == strcmp(argv[1], "--debug"))
    {
        cout << config.token + " " + config.id + " " + config.IP + " " + config.protocol_version << " " << config.port
             << endl;
    }

    blooming_connection *sock = new blooming_connection(config);
    return 0;
}
