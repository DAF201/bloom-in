#include <iostream>
#include <thread>
#include <winsock.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

bool close_socket_flag = false;
bool __socket_send();
bool __socket_recv();