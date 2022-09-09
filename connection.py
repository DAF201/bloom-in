import socket
import threading
import re
import hashlib
import os
import sys
from time import sleep, time

config = {
    "port": 4215,
    "ip": "0.0.0.0",
    "exit_command": "a2dff2049c95fc45de4a6601177db8cdc55d81e8d6506a1771f4d2108854f3a6a81a8ab28f0b3bbc3a46455a4067168773d942de3e502e2d1c22514d976127e8"
}

HEADER = b'bloom-in protocol V\d\.\d.\d <t>\w{0,16}<t> <i>\w{0,16}<i> BLOOM_IN$'

COMMAND = b'bloom-in \w <t>\w{0,16}<t>(<i>\w{0,16}<i>)?<d>\w{0,65535}<d>\s?BLOOM_IN$'

COMMAND_POOL = []


def new_connection(socket: socket.socket, flag: str):

    connection_head = socket.recv(128)
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

    socket.send(b'recieved, token is: ' + token + b' id is: '+id)

    reciever = threading.Thread(
        target=recieve_command, args=(socket, token.decode()))
    fetcher = threading.Thread(
        target=fetch_command, args=(socket, token.decode()))

    reciever.start()
    fetcher.start()


def recieve_command(socket: socket.socket, token: str):
    try:
        while True:
            data = socket.recv(1024)
            if data == b'exit':
                socket.close()
                break
            COMMAND_POOL.append((token, data, time()))
    except:
        socket.close()
        return


def fetch_command(socket: socket, token: str):
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
