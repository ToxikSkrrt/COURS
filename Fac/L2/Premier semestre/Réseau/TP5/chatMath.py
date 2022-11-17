#!/usr/bin/python3
import socket
import select

HOST = ""
PORT = 7777
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(1)

def cmd_msg (socket,sockets,nicks,message):
        for i in sockets:
            if i != socket:
                request ="[" + str(socket_to_nick(socket,nicks))+ "]" + " " + str(message)
                request = request.replace("\n","")
                request = request + "\n"
                i.sendall(request.encode())            
    
def socket_to_nick(socket,nicks):
    for i in nicks:
        if i==socket:
            return nicks[i]
    
def nick_to_socket(nicks,nick):
    for i in nicks:
        if nicks[i]==nick:
            return i
    
def add_nick(nicks,nick,socket):
    nicks[socket]=nick

def cmd_nick (socket,sockets,nicks,nick):
    for i in sockets :
        if i == socket :
            nicks = add_nick(nicks, nick,socket)

def get_nick(nicks):
    L=()
    for valeur in nicks.values():
        valeur = valeur.replace("\n","")
        valeur = valeur.replace("'","")
        valeur = valeur.replace("`","")
        L=L + (valeur,)
    return L 

def delnick(nicks,socket):
    del nicks[socket]

def cmd_kill(socket,sockets,nicks,kill,dead):
    s3= nick_to_socket(nicks,dead)
    for i in sockets :
        if i != socket :
            request = "[" + str(socket_to_nick(socket,nicks)) + "]" + " " + str(kill)
            request = request.replace("\n","")
            request = request + "\n"
            i.sendall(request.encode())
    print("client disconnected,", dead)
    delnick(nicks,s3)
    s3.close()
    l.remove(s3)
    
l = []  # liste des socket clientes
ni = {}

while True:
    lr, _, _ = select.select(l + [s], [], [])
    for s2 in lr:
        if s2 == s:
            # accepter le nouveau client qui demande Ã  se connecter
            sclient, addr = s2.accept()
            tab=sclient.getpeername()
            print("New connected :", "{}:{}".format(tab[0],tab[1]))
            l = l + [sclient]
        else:
            # traiter les donnÃ©es envoyÃ©es par le client
            data = s2.recv(1500)
            data = data.decode().replace("\n","")
            argu=data.split(" ",1)
            if argu[0] == 'MSG':
                cmd_msg(s2,l,ni,argu[1])
            elif argu[0] == 'NICK':
                cmd_nick(s2,l,ni,argu[1])
            elif argu[0] =='WHO':
                request = "[server]" + " " + str(get_nick(ni))
                request = request.replace("\n","")
                request = request.replace("(","")
                request = request.replace(")","")
                request = request.replace(",","")
                request = request.replace("'","")
                request = request.replace("`","")
                request = request + "\n"
                s2.sendall(request.encode())
            elif argu[0] == 'QUIT':
                for s3 in l :
                    if s3 != s2 :
                        request = "[" + str(socket_to_nick(s2,ni)) + "]" + " " + str(argu[1])
                        request = request.replace("\n","")
                        request = request + "\n"
                        s3.sendall(request.encode())
                print("client disconnected,", socket_to_nick(s2,ni))
                delnick(ni,s2)  
                s2.close()
                l.remove(s2)
                continue
            elif argu[0] == 'KILL':
                word = argu[1]
                argument = word.split(" ",1)
                cmd_kill(s2,l,ni,argument[1],argument[0])
            else:
                print("invalid command")
            print(data)