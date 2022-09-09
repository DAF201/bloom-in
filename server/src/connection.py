import socket
import threading
import re
import hashlib
import os
import sys
from time import sleep, time
from config import *


def new_connection(socket: socket.socket, flag: str):

    socket.settimeout(3)
    try:
        connection_head = socket.recv(128)
    except:
        socket.send(b"timeout")
        socket.close()
        sys.exit()
    finally:
        socket.settimeout(None)

    print(connection_head)
    if hashlib.sha512(connection_head).hexdigest() == config["exit_command"]:
        os._exit(0)

    if re.match(HEADER, connection_head) == None:
        sys.exit()

    try:
        token = re.search(
            b'bloom-in protocol V\d\.\d.\d <t>(.*)<t> <i>\w{0,16}<i> BLOOM_IN$', connection_head)
        token = token.group(1) if token else None

        id = re.search(
            b'bloom-in protocol V\d\.\d.\d <t>\w{0,16}<t> <i>(.*)<i> BLOOM_IN$', connection_head)
        id = id.group(1) if id else None
    except:
        socket.close()
        sys.exit()

    print(id)

    socket.send(
        b"Wlecome to bloom-in, current channel: "+token+b", wish you find the one blooming for you, "+id+b'\0')

    reciever = threading.Thread(
        target=connection_receive, args=(socket, token.decode()))
    fetcher = threading.Thread(
        target=connection_fetch, args=(socket, token.decode()))

    reciever.start()
    fetcher.start()


def connection_receive(socket: socket.socket, token: str):
    try:
        while True:
            data = socket.recv(1024)
            if data == b'exit':
                socket.close()
                return
            COMMAND_POOL.append((token, data, time()))
    except:
        socket.close()
        return


def connection_fetch(socket: socket.socket, token: str):
    try:
        while True:
            for command_index in range(len(COMMAND_POOL)):
                if(time()-COMMAND_POOL[command_index][2] > 600):
                    COMMAND_POOL.pop(command_index)

                if COMMAND_POOL[command_index][0] == token:
                    socket.send(COMMAND_POOL[command_index][1])
                    COMMAND_POOL.pop(command_index)
            sleep(1)
    except:
        socket.close()
        return