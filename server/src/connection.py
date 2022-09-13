from concurrent.futures import thread
import socket
import threading
import re
import hashlib
import os
import sys
from time import sleep, time
from config import *


class Header_Syntax_Error(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class Command_Syntax_Error(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class sub_connection():
    CMD_POOL: dict
    CMD_POOL = {}

    def __init__(self, sock: socket.socket, addr: str) -> None:

        self.socket: socket.socket
        self.ip: str
        self.recv: threading.Thread
        self.send: threading.Thread

        self.recv_buffer: str

        self.socket = sock
        self.ip = addr

        self.__connection_recv: function
        self.__connection_send: function
        self.__connection_close: function

        if not self.__connection__init():
            sys.exit()

        self.__connection_recv()
        self.__connection_send()

    def __connection__init(self) -> bool:
        try:
            self.socket.settimeout(3)
            self.head = self.socket.recv(1024)
            if re.match(HEADER, self.head) == None:
                print(self.head)
                raise Header_Syntax_Error("invaild protocol syntax")
            self.socket.settimeout(None)
            return True

        except Header_Syntax_Error as HSE:
            print(HSE)
            self.__connection_close()
            return False

        except TimeoutError as TOE:
            print(TOE)
            self.__connection_close()
            return False

        except Exception as E:
            print(E)
            self.__connection_close()
            return False

    def __connection_close(self):
        self.socket.send(b"close"+b'\0')
        self.socket.close()

    def __connection_recv(self):
        print('start recv')
        recv_t = threading.Thread(target=self.recv)
        recv_t.start()

    def __connection_send(self):
        print('start send')
        send_t = threading.Thread(target=self.send)
        send_t.start()

    def recv(self):
        try:
            while 1:
                self.recv_buffer = self.socket.recv(65535)
                print(self.recv_buffer)
                if re.match(COMMAND, self.recv_buffer) == None:
                    raise Command_Syntax_Error("invaild protocol syntax")
        except:
            self.socket.send(b"invaild syntax, connection closing")
            self.socket.close()
            return

    def send(self):
        while 1:
            pass
