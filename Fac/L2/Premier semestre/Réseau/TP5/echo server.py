#!/usr/bin/python3

import socket

s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
s2 = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
s.bind(("", 7777))

s.listen(1)

while True:
    s2, addr = s.accept()
    while True:
        data = s2.recv(1500)
        if data == 0:
            break
        s2.send(data)

    s.close()