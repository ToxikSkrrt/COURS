#!/usr/bin/python3

import socket

s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(("", 7777))

s.listen(1)

while True:
    s2, addr = s.accept()
    while True:
        data = s2.recv(1500)
        if data == b'\n' or data == b'':
            break
        s2.send(data)
        print(data)

    s2.close()
    s.close()