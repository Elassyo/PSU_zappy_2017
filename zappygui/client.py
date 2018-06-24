import socket
import threading

class ClientThread(threading.Thread):

    def __init__(self, client):
        threading.Thread.__init__(self)
        self.client = client

    def run(self):

        while self.client.connected:
            pass


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
