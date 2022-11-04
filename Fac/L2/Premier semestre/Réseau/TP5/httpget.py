#!/usr/bin/python3
import socket
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = sys.argv[1]
port = 80

request = "GET / HTTP/1.1\r\n"  \
    "Host: " + host + "\r\n"    \
    "Connection: close\r\n\r\n"

request = request.encode("utf-8")

s.connect((host, port))
s.sendall(request)

data = s.recv(1024)
print(data)

s.close()
