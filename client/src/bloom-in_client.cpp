#include <iostream>
#include <thread>
#include <winsock.h>
#include <string>
#include <fstream>
#include <map>
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
                cout << "UNKNOWN KEY-VALUE: " << buffer << " at line :" << line << endl;
            }
        }
    }
};

class blooming_connection
{
    static const char *head;
    static const char *at_command;
    static const char *broadcast_command;
    static const char *exit;
    char recv_buffer[65535];
    char send_buffer[65535];

    bool socket_status = 1;

    thread thread_recv;
    thread thread_send;
    SOCKET sock;
    SOCKADDR_IN socket_config;
    WSADATA wsaData;

    void blooming_init()
    {
        send(sock, head, strlen(head), 0);
    }

    void sock_send()
    {
        string buffer;
        while (socket_status)
        {
            getline(cin, buffer);

            if (0 == buffer.compare("exit"))
            {
                blooming_end();
            }

            send(sock, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
    }

    void sock_recv()
    {
        recv(sock, recv_buffer, 65535, 0);
        if (0 == strcmp(recv_buffer, "close"))
        {
            cout << "remote connection closed" << endl;
            std::exit(0);
        }
        cout << recv_buffer << endl;
    }

    void blooming_end()
    {
        send(sock, exit, strlen(exit), 0);
        closesocket(sock);
        WSACleanup();
        std::exit(0);
    }

public:
    blooming_connection(config config)
    {
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

const char *blooming_connection::head = "bloom-in protocol V0.0.1 <t>test<t> <i>tmachine1<i> BLOOM_IN";
const char *blooming_connection::at_command = "bloom-in %s <t>%s<t><i>%s<i><d>%s<d>BLOOM_IN";
const char *blooming_connection::broadcast_command = "bloom-in %s <t>%s<t><d>%s<d>BLOOM_IN";
const char *blooming_connection::exit = "exit";

int main()
{
    config config;
    blooming_connection *sock = new blooming_connection(config);
    return 0;
}
