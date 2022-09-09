import socket
import threading
import connection as connection


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((connection.config["ip"], connection.config["port"]))
s.listen(2)

while True:
    sock, addr = s.accept()
    sub_connect = threading.Thread(
        target=connection.new_connection, args=(sock, addr))
    sub_connect.start()
    sub_connect.join()
