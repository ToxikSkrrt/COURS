#!/usr/bin/python3

import socket
import select

def decodeCommand(strarg):
    tmp = strarg.split(' ', 1)
    cmd = tmp[0]
    args = tmp[1]
    return cmd, args

sServ = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
sServ.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
l = [sServ]

sServ.bind(("", 7777))

sServ.listen(1)

while True:
    sl, tmp1, tmp2 = select.select(l, [], [])
    for s in sl:
        if s != sServ:
            data = s.recv(1024)
            if data == b'\n' or data == b'':
                l.remove(s)
                s.close()
                break
            data = data.decode('utf-8')
            try:
                cmd, args = decodeCommand(data)
            except:
                cmd = None
            if cmd == 'MSG':
                args = args.encode('utf-8')
                for stest in l:
                    if stest != sServ and stest != s:
                        stest.sendall(args)
            #else if cmd == 
            print(data)
        else:
            s2, addr = s.accept()
            l.append(s2)