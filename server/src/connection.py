import socket
import threading
import re
import hashlib
import os
import sys
from time import sleep, time
from config import *


class sub_connection():
    def __init__(self, socket: socket.socket, addr: str) -> None:
        self.socket = socket
        self.ip = addr
        if not self.__connection__init():
            sys.exit()

    def __connection__init(self) -> bool:
        try:
            self.socket.settimeout(3)
            print(self.socket.recv(1024))
            self.socket.settimeout(None)
            return True
        except:
            print("time out")
            self.socket.send(b"close"+b'\0')
            self.socket.close()
            return False
