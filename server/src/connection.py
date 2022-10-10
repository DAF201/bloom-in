import socket
import threading
import re
import sys
import time
from typing import final
from config import *
import inspect
import base64
# invaild connection header


class Header_Syntax_Error(Exception):
    '''the connection request does not provide a vaild header protocol'''

    def __init__(self, *args: object) -> None:
        super().__init__(*args)

# invaild protocol


class Command_Syntax_Error(Exception):
    '''the \'client\' does not provide an vaild command protocol while connecting'''

    def __init__(self, *args: object) -> None:
        super().__init__(*args)

# connection closed by client


class Remote_connection_closed(Exception):
    '''the connection was cut remotely'''

    def __init__(self, *args: object) -> None:
        super().__init__(*args)

# connection body


class sub_connection():
    '''a socket connection, should have two sub threads to recieve command from client and to send command to client'''

    # init, sock: socket body, addr: ip address
    def __init__(self, sock: socket.socket, addr: str) -> None:

        # data type declearation
        self.socket: socket.socket  # socket body
        self.ip: str  # ip address
        self.id: str  # id
        self.recv: threading.Thread  # recieve thread
        self.send: threading.Thread  # send thread
        self.__connection__init: function  # connection init
        self.__connection_recv: function  # recieve thread starter
        self.__connection_send: function  # send thread starter
        self.__connection_close: function  # close connection
        self.recv_buffer: str  # reciever buffer

        self.socket = sock
        self.ip = addr

        # check header
        if not self.__connection__init():
            # failed, kill this connection thread(socket closed in except)
            sys.exit()

        # success
        self.socket.send(base64.b64encode(
            b'welcome, wish you find your bloom here'))

        # start recv and send
        self.__connection_recv()
        self.__connection_send()

    def __connection__init(self) -> bool:
        '''check client header protocol'''

        try:
            # 3 s to send header after connection made
            self.socket.settimeout(3)

            # recv header
            self.head = self.socket.recv(1024)

            # protcol matching
            if re.match(HEADER, self.head) == None:
                # failed
                if config["debug"]:
                    print(self.head)
                raise Header_Syntax_Error("invaild protocol syntax")

            self.id = self.extractor(self.head, b'<id>')
            self.id = self.head[self.id[0]: self.id[1]]

            self.channel = self.extractor(self.head, b'<channel>')
            self.channel = self.head[self.channel[0]: self.channel[1]]

            # success, remove timeout
            self.socket.settimeout(None)

            # header check success
            return True

        # protocol error
        except Header_Syntax_Error as HSE:
            print(HSE)
            self.__connection_close()
            return False

        # timeout
        except TimeoutError as TOE:
            print(TOE)
            self.__connection_close()
            return False

        # other
        except Exception as E:
            print(E)
            self.__connection_close()
            return False

    # close the connection
    def __connection_close(self) -> None:
        '''close connection from server'''

        if config["debug"]:
            print('exit from: ', inspect.stack()[1][3])

        # try send close command to 'client
        self.socket.send(b"close"+b'\0')
        # close socket
        self.socket.close()

        # try force close
        try:
            self.socket.shutdown(socket.SHUT_RDWR)
        except:
            pass
        finally:
            del self

    def __connection_recv(self) -> None:
        '''start recv thread'''

        if config["debug"]:
            print('start recv')
        recv_t = threading.Thread(target=self.recv)
        recv_t.start()

    def __connection_send(self) -> None:
        '''start send thread'''

        if config["debug"]:
            print('start send')
        send_t = threading.Thread(target=self.send)
        send_t.start()

    def recv(self) -> None:
        '''recv data and analysis

        channel: where to fetch command
        id: command sender id
        target: command reciver id
        data: sender's command/data
        '''
        try:
            while 1:
                # regular expression max match capicity is 65535, and I don't need pass super large file anyway
                self.recv_buffer = self.socket.recv(65535)

                if config["debug"]:
                    print(self.recv_buffer)

                # if not exit command
                if self.extractor(self.recv_buffer, b'<exit>') == [0, 0]:

                    # take data out from raw data
                    extracted_data = self.extract_data(EXTRACTOR_SYNTAX)

                    target = self.recv_buffer[extracted_data[0]
                                              [0]: extracted_data[0][1]]

                    data = self.recv_buffer[extracted_data[1]
                                            [0]: extracted_data[1][1]]

                    # if config["debug"]:
                    #     print(self.channel, self.id, target, data)

                    # empty package, treate as conection closed
                    if data == b'':
                        raise Command_Syntax_Error("invaild protocol syntax")

                    # append to pool, expire time, target, sender id, data, socket body
                    COMMAND_POOL.append(
                        (int(time.time())+60, target, self.id, data, self.socket))

                # is exit command
                if re.match(EXIT, self.recv_buffer) != None:
                    raise Remote_connection_closed(
                        "connection closed by remote")

                # invaild syntax
                if re.match(COMMAND, self.recv_buffer) == None:
                    raise Command_Syntax_Error("invaild protocol syntax")

        except Command_Syntax_Error as CSE:
            print(CSE)
            try:
                self.__connection_close()
            except:
                pass
            finally:
                return

        except Remote_connection_closed as RCC:
            print(RCC)
            try:
                self.__connection_close()
            except:
                pass
            finally:
                return
        except Exception as E:
            print(E)
            try:
                self.__connection_close()
            except:
                pass
            finally:
                return

    def send(self) -> None:
        '''Get command out of pool and send to client'''
        while 1:
            try:
                for command in COMMAND_POOL:
                    if command[1] == self.id:
                        self.socket.send(command[3]+b'\0')
                        COMMAND_POOL.remove(command)
                    time.sleep(1)
            except Exception as e:

                if config['debug']:
                    print(e)

                try:
                    self.__connection_close()
                except:
                    pass
                finally:
                    return

    def extractor(self, source: str, pattern: str) -> list:
        '''get data out from raw data, return list of starting position and ending position

        retrun [0,0] if no found
        '''
        try:
            # string.find
            start = source.find(pattern)
            end = source.find(pattern, start+len(pattern))
            if start == -1 or end == -1:
                return [0, 0]
            return [start+len(pattern), end]
        except Exception as e:
            print(e)
            return [0, 0]

    def extract_data(self, extractor_syntax) -> list:
        '''extract wanted data'''
        result = []
        for key in extractor_syntax:
            data = self.extractor(self.recv_buffer, key)
            result.append(data)
        return result

    def __del__(self):
        print('connection destructing')


def deactivator() -> None:
    '''deactive the expired command, each command will last 60s at most'''
    while(1):
        try:
            for command_index in range(len(COMMAND_POOL)):
                if COMMAND_POOL[command_index][0] < time.time():
                    COMMAND_POOL.pop(command_index)
                    # if config["debug"]:
                    #     print("size of command pool: "+str(len(COMMAND_POOL)))
                    #     print(COMMAND_POOL)
            # if config["debug"]:
            #     print("-----------------------------------------------")
            time.sleep(1)
        except Exception as e:
            print(e)
