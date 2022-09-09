#include <iostream>
#include <thread>
#include <winsock.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

bool close_socket = false;
void Send(SOCKET client, char send_buf[]);
void Recv(SOCKET client, char recv_buf[]);

int main()
{
    char send_buf[100];
    char recv_buf[100];

    thread thread_send;
    thread thread_recv;

    SOCKET client;

    SOCKADDR_IN client_addr;

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    client = socket(AF_INET, SOCK_STREAM, 0);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("50.17.163.77");
    client_addr.sin_port = htons(4215);

    connect(client, (SOCKADDR *)&client_addr, sizeof(SOCKADDR));

    const char *head = "bloom-in protocol V0.0.1 <t>test<t> <i>test_machine_1<i> BLOOM_IN";
    send(client, head, strlen(head), 0);

    // thread_send = thread(Send, client, send_buf);
    thread_recv = thread(Recv, client, recv_buf);

    // thread_send.join();
    thread_recv.join();

    closesocket(client);

    WSACleanup();
    return 0;
}

void Send(SOCKET client, char send_buf[])
{
    while (true)
    {
        if (close_socket == 1)
        {
            return;
        }

        cin >> send_buf;

        if (send_buf == "exit")
        {
            close_socket = 1;
        }

        // send(client, send_buf, 100, 0);
    }
}

void Recv(SOCKET client, char recv_buf[])
{

    // while (true)
    // {
        if (close_socket == 1)
        {
            return;
        }
        recv(client, recv_buf, 100, 0);
        cout << recv_buf << endl;
    // }
}