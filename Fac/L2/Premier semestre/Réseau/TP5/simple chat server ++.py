#!/usr/bin/python3

import socket
import select

HOST = ''
PORT = 7777

def decodeCommand(strarg):
    tmp = strarg.split(' ', 1)
    cmd = tmp[0]
    try:
        args = tmp[1]
    except:
        args = None
    return cmd, args

sServ = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
sServ.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
l = [sServ]

sServ.bind((HOST, PORT))

sServ.listen(1)

nicknames = {}

print('Welcome to Chat Server !')

while True:
    sl, tmp1, tmp2 = select.select(l, [], [])
    for s in sl:
        if s != sServ:
            data = s.recv(1024)
            if data == b'\n' or data == b'':
                l.remove(s)
                del nicknames[s]
                s.close()
                break
            data = data.decode('utf-8').replace('\n', '')
            cmd, args = decodeCommand(data)

            if cmd == 'MSG' and args != None:
                args = f'[{nicknames[s]}] {args}\n'
                for stest in l:
                    if stest != sServ and stest != s:
                        stest.sendall(args.encode('utf-8'))
            elif cmd == 'NICK' and args != None:
                print(f'client "{nicknames[s]}" => "{args}"')
                nicknames[s] = args
            elif cmd == 'NAMES':
                nl = []
                for i in nicknames.values():
                    nl.append(i)
                for stest in l:
                    if stest != sServ and stest == s:
                        stest.sendall(f'[server] {str(nl)}\n'.encode('utf-8'))
            elif cmd == 'QUIT' and args != None:
                args = f'[{nicknames[s]}] {args}\n'
                for stest in l:
                    if stest != sServ and stest != s:
                        stest.sendall(args.encode('utf-8'))
                print(f'client disconnected "{nicknames[s]}"')
                l.remove(s)
                del nicknames[s]
                s.close()
            elif cmd == 'KILL' and args != None:
                word = args.split(' ', 1)
                for stest in l:
                    if stest != sServ and stest != s and nicknames[stest] == word[0]:
                        stest.sendall(f'[{nicknames[s]}] {word[1]}\n'.encode('utf-8'))
                        l.remove(stest)
                        del nicknames[stest]
                        stest.close()
                print(f'client disconnected "{word[0]}"')
                
            # print(data)
        else:
            s2, addr = s.accept()
            tab = s2.getpeername()
            print(f'client connected : "{tab[0]}:{tab[1]}"')
            nicknames[s2] = f'{tab[0]}:{tab[1]}'
            l.append(s2)