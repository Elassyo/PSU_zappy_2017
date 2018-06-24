import socket
import sys
import threading

from .cmd import Cmds

class ClientThread(threading.Thread):

    def __init__(self, client):
        threading.Thread.__init__(self)
        self.client = client

    def run(self):
        buffer = b''
        while self.client.connected:
            try:
                data = self.client.socket.recv(4096)
                if not data:
                    raise Exception()
            except socket.timeout:
                continue
            except Exception:
                self.client.connected = False
                break
            buffer += data
            while b'\n' in buffer:
                line, buffer = buffer.split(b'\n', 1)
                line = line.decode()
                args = line.split(' ', 1)
                args[0] = args[0].lower()
                if not args[0] in Cmds:
                    print('Received unrecognized message: %s' % args[0],
                        file=sys.stderr)
                else:
                    Cmds[args[0]](self.client, args[1:])


class Client:

    def __init__(self):
        self.connected = False
        self.server = ('', '')

    def setServer(self, server):
        assert(not self.connected)
        self.socket = None
        self.server = tuple(server)

    def connect(self):
        try:
            server = (self.server[0], int(self.server[1]))
            if not 0 < server[1] < 65536:
                raise ValueError()
        except ValueError:
            raise Exception('Invalid port number')

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.settimeout(0.5)
        self.socket.connect(server)
        self.connected = True

        thread = ClientThread(self)
        thread.start()

    def disconnect(self):
        if self.socket:
            self.socket.close()
            self.socket = None
        self.connected = False
        self.reset()

    def reset(self):
        pass
