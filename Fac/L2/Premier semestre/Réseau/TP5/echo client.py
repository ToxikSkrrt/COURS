#!/usr/bin/python3

import sys
import socket

s = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)

s.connect(("", 7777))

while True:
    line = sys.stdin.readline()
    if line == '\n':
        break
    print(line)

s.close()