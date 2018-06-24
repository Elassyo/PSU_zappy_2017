Cmds = {
    'welcome': lambda client, args: client.socket.send(b'GRAPHIC\n')
}
