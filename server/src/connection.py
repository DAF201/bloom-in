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


class sub_connection():
    CMD_POOL: dict
    CMD_POOL = {}

    def __init__(self, sock: socket.socket, addr: str) -> None:

        self.socket: socket.socket
        self.ip: str

        self.socket = sock
        self.ip = addr
        if not self.__connection__init():
            sys.exit()

    def __connection__init(self) -> bool:
        try:
            self.socket.settimeout(3)
            self.head = self.socket.recv(1024)
            if re.match(HEADER, self.head) == None:
                raise Header_Syntax_Error("invaild protocol syntax")
            self.socket.settimeout(None)
            return True

        except Header_Syntax_Error as HSE:
            print(HSE)
            self.__close_connection()
            return False

        except TimeoutError as TOE:
            print(TOE)
            self.__close_connection()
            return False

        except Exception as E:
            print(E)
            self.__close_connection()
            return False

    def __close_connection(self):
        self.socket.send(b"close"+b'\0')
        self.socket.close()
