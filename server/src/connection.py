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
        self.__connection__init()

    def __connection__init(self) -> bool:
        try:
            self.socket.settimeout(3)
            print(self.socket.recv(1024))
            self.socket.settimeout(None)
        except:
            print("time out")
            self.socket.close()
