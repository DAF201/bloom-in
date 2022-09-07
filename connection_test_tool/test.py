import socket
import threading
import os
import atexit
import json
from time import sleep


with open(__file__.split(os.path.basename(__file__))[0]+'/config.json', 'r') as config:
    config_data = json.load(config)

HEADER = b'bloom-in protocol %s <t>%s<t> <i>%s<i> BLOOM_IN' % (config_data["protocol_version"].encode(),
                                                               config_data["token"].encode(), config_data["id"].encode())

COMMAND = b'bloom-in \w <t>\w{0,16}<t>(<i>\w{0,16}<i>)?<d>\w{0,65535}<d>\s?BLOOM_IN'
SERVER_COMMAND = b'bloom-in protocol V\d\.\d.\d <a>\w{0,16}<a> <c>\w{0,16}<c> BLOOM_IN'


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((config_data["IP"], config_data["PORT"]))

s.send(HEADER)


def reciving(socket: socket.socket):
    while 1:
        temp_data = socket.recv(65535)
        print(temp_data)


def phrasing(input):
    return input


def sending(socket: socket.socket):
    try:
        while 1:
            user_input = input()
            if user_input == 'exit':
                socket.send(b'exit')
                os._exit(0)
            if user_input == '':
                continue
            socket.send(phrasing(user_input.encode()))
    except:
        pass


def close_connection(socket: socket.socket):
    socket.send(b'exit')
    socket.close()


atexit.register(close_connection, args=(s,))

rec = threading.Thread(target=reciving, args=(s,))
sen = threading.Thread(target=sending, args=(s,))
rec.start()
sen.start()
rec.join()
sen.join()
