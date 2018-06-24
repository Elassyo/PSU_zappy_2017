#!/bin/python3

import socket
import sys

from map import Map
from player import Player
from team import Team
from item import Item
from cmd import cmds

def usage():
    print("USAGE : ./client ip port")
    exit (84)

def client(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((ip, port))
    data = s.recv(1024)
    s.send("GRAPHIC\n".encode('ascii'))
    board = Map()
    while (1):
        data = s.recv(4096)
        data = data.decode('utf-8').split("\n")
        for line in data:
            c = line.split(" ")
            for cmd in cmds:
                if c[0] == cmd[0]:
                    cmd[1](c, board)
                    break
    s.close()

    
def main(ac, av):
    if (ac == 3):
        client(av[1], int(av[2]))
    else:
        usage()


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
