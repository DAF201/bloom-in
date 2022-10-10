import socket
import threading
import connection as connection

# TCP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((connection.config["ip"], connection.config["port"]))
s.listen(2)

# deactive expired command
command_pool_manager = threading.Thread(target=connection.deactivator)
command_pool_manager.start()


def new_con():
    sock, addr = s.accept()
    sub_connection = threading.Thread(
        target=connection.sub_connection, args=(sock, addr))
    sub_connection.start()
    sub_connection.join()

# receive connection
while True:
    new_con()
    # sub_connection.join()
