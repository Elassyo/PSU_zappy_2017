import sys

def welcome(client, args):
    client.socket.send(b'GRAPHIC\n')

def cmd_bct(client, args):
    try:
        args = args.split(' ')
        if len(args) != 9:
            raise Exception()
        print('zz')
        args = [int(arg) for arg in args]
        x, y, content = args[0], args[1], args[2:]
        print(x, y)
        if not (0 <= x < client.map.w and 0 <= y < client.map.h):
             #or            any([c < 0 for c in content]):
            raise Exception()
    except Exception:
        raise
        print('Invalid BCT message', file=sys.stderr)
        return
    client.map.tiles[x][y] = content

def cmd_msz(client, args):
    try:
        args = args.split(' ')
        if len(args) != 2:
            raise Exception()
        w, h = [int(arg) for arg in args]
        if w <= 0 and h <= 0:
            raise Exception()
    except Exception:
        print('Invalid MSZ message', file=sys.stderr)
        return
    client.map.setSize(w, h)

def todo(client, args):
    print(client.map.tiles)

Cmds = {
    'welcome': welcome,
    'bct': cmd_bct,
    'ebo': todo,
    'eht': todo,
    'enw': todo,
    'msz': cmd_msz,
    'pbc': todo,
    'pdi': todo,
    'pdr': todo,
    'pex': todo,
    'pfk': todo,
    'pgt': todo,
    'pic': todo,
    'pie': todo,
    'pin': todo,
    'plv': todo,
    'pnw': todo,
    'ppo': todo,
    'seg': todo,
    'sgt': todo,
    'sst': todo,
    'tna': todo
}
