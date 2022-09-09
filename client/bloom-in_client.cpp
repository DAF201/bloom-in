#include <iostream>
#include <thread>
#include <winsock.h>
#include <string>
#include <fstream>
#include <map>
#define CONFIG_FILE "./config.config"
#pragma comment(lib, "ws2_32.lib")
using namespace std;

class blooming_connection
{
    static const char *head;

    char recv_buffer[65535];
    char send_buffer[65535];

    bool socket_status;

    thread thread_recv;
    SOCKET sock;
    SOCKADDR_IN socket_config;
    WSADATA wsaData;

    void blooming_start()
    {
        send(sock, head, strlen(head), 0);
    }

    void sock_send()
    {
        while (socket_status)
        {
        }
    }

    void sock_recv()
    {
        recv(sock, recv_buffer, 100, 0);
        cout << recv_buffer << endl;
    }

    void blooming_end()
    {
        send(sock, "exit", strlen(head), 0);
    }

public:
    blooming_connection(string IP, int port)
    {
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        sock = socket(AF_INET, SOCK_STREAM, 0);
        memset(&socket_config, 0, sizeof(socket_config));
        socket_config.sin_family = AF_INET;
        socket_config.sin_addr.s_addr = inet_addr(IP.c_str());
        socket_config.sin_port = htons(port);

        connect(sock, (SOCKADDR *)&socket_config, sizeof(SOCKADDR));
        blooming_start();
        
        thread_recv = thread(&blooming_connection::sock_recv, this);
        thread_recv.join();

        blooming_end();
    }
};

const char *blooming_connection::head = "bloom-in protocol V0.0.1 <t>test<t> <i>test_machine_1<i> BLOOM_IN";

int main()
{
    blooming_connection *sock = new blooming_connection("50.17.163.77", 4215);

    return 0;
}
