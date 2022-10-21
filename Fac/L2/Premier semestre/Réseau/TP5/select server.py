#!/usr/bin/python3

import socket
import select

sServ = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
l = [sServ]

sServ.bind(("", 7777))

sServ.listen(1)

while True:
    sl, tmp1, tmp2 = select.select(l, [], [])
    for s in sl:
        if s != sServ:
            data = s.recv(1024)
            s.send(data)
        else:
            s2, addr = s.accept()
            l.append(s2)