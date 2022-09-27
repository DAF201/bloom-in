import socket
import threading
import re
import sys
import time
from config import *


class Header_Syntax_Error(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class Command_Syntax_Error(Exception):
    def __init__(self, *args: object) -> None:
        super().__init__(*args)


class Remote_connection_closed(Exception):
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

    def __connection_close(self) -> None:
        self.socket.send(b"close"+b'\0')
        self.socket.close()

    def __connection_recv(self) -> None:
        print('start recv')
        recv_t = threading.Thread(target=self.recv)
        recv_t.start()

    def __connection_send(self) -> None:
        print('start send')
        send_t = threading.Thread(target=self.send)
        send_t.start()

    def recv(self) -> None:
        try:
            while 1:
                self.recv_buffer = self.socket.recv(65535)

                print(self.recv_buffer)
                if self.extractor(self.recv_buffer, b'<exit>') == [0, 0]:
                    self.channel = self.extractor(
                        self.recv_buffer, b'<channel>')
                    self.id = self.extractor(self.recv_buffer, b'<id>')
                    target = self.extractor(self.recv_buffer, b'<target>')
                    data = self.extractor(self.recv_buffer, b'<data>')

                    print(self.recv_buffer[self.channel[0]:self.channel[1]])
                    print(self.recv_buffer[self.id[0]:self.id[1]])
                    print(self.recv_buffer[target[0]:target[1]])
                    print(self.recv_buffer[data[0]: data[1]])

                if re.match(EXIT, self.recv_buffer) != None:
                    raise Remote_connection_closed(
                        "connection closed by remote")

                if re.match(COMMAND, self.recv_buffer) == None:
                    raise Command_Syntax_Error("invaild protocol syntax")

        except Exception as e:
            print(e)
            self.socket.send(b"invaild syntax, connection closing")
            self.socket.close()
            return

    def send(self):
        while 1:
            pass

    def extractor(self, source: str, pattern: str) -> list:
        try:
            start = source.find(pattern)
            end = source.find(pattern, start+len(pattern))
            if start == -1 or end == -1:
                return [0, 0]
            return [start+len(pattern), end]
        except Exception as e:
            print(e)
            return [0, 0]
