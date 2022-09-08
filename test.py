import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 1111))
s.listen(2)
sock, addr = s.accept()
print(sock.recv(1024))
sock.close()
