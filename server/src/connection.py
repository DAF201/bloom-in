import socket
import threading
import re
import hashlib
import os
import sys
from time import sleep, time
from config import *


class HEADER_SYNTAX_ERROR(Exception):
    def __init__(self):
        super().__init__("header syntax error")


class sub_connection():
    CMD_POOL: dict
    CMD_POOL = {}

    def __init__(self, sock: socket.socket, addr: str) -> None:

        self.socket: socket.socket
        self.ip: str
        self.token: str
        self.id: str

        self.socket = sock
        self.ip = addr

        if not self.__connection__init():
            sys.exit()

    def __connection__init(self) -> bool:
        try:
            self.socket.settimeout(3)
            connection_head = self.socket.recv(1024)
            self.socket.settimeout(None)

            if re.match(HEADER, connection_head) == None:
                raise HEADER_SYNTAX_ERROR

            token = re.search(
                b'bloom-in protocol V\d\.\d.\d <t>(.*)<t> <i>\w{0,16}<i> BLOOM_IN$', connection_head)
            self.token = token.group(1) if token else None

            id = re.search(
                b'bloom-in protocol V\d\.\d.\d <t>\w{0,16}<t> <i>(.*)<i> BLOOM_IN$', connection_head)
            self.id = id.group(1) if id else None

            return True
        except HEADER_SYNTAX_ERROR:
            print("header error")
            self.__close_connection()
            return False
        except:
            print("connection init error")
            self.__close_connection()
            return False

    def __close_connection(self):
        self.socket.send(b"close"+b'\0')
        self.socket.close()
