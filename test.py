import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('50.17.163.77', 4215))
s.settimeout(None)
try:
    print(s.recv(1024))
except Exception as e:
    print(e)
