import sys

from .egg import Egg
from .player import Player
from .team import Team

def welcome(client, args):
    client.socket.send(b'GRAPHIC\n')

def cmd_bct(client, args):
    try:
        args = args.split(' ')
        if len(args) != 9:
            raise Exception()
        args = [int(x) for x in args]
        x, y, content = args[0], args[1], args[2:]
        if not (0 <= x < client.map.w and 0 <= y < client.map.h) or \
            any([c < 0 for c in content]):
            raise Exception()
    except Exception:
        print('Invalid BCT message', file=sys.stderr)
        return
    client.map.tiles[x][y] = content

def cmd_ebo(client, args):
    try:
        id = int(args)
        egg = client.map.getEggByID(id)
        if not egg:
            raise Exception()
    except Exception:
        print('Invalid EBO message', file=sys.stderr)
        return

    client.map.eggs.remove(egg)

def cmd_eht(client, args):
    try:
        id = int(args)
        egg = client.map.getEggByID(id)
        if not egg:
            raise Exception()
    except Exception:
        print('Invalid EHT message', file=sys.stderr)
        return

    egg.hatched = True

def cmd_enw(client, args):
    try:
        args = args.split(' ')
        if len(args) != 4:
            raise Exception()
        id, parent_id, x, y = [int(x) for x in args]
        if client.map.getEggByID(id):
            raise Exception()
    except Exception:
        raise
        print('Invalid ENW message', file=sys.stderr)
        return

    client.map.eggs.append(Egg(id, x, y))

def cmd_msz(client, args):
    try:
        args = args.split(' ')
        if len(args) != 2:
            raise Exception()
        w, h = [int(x) for x in args]
        if w <= 0 and h <= 0:
            raise Exception()
    except Exception:
        print('Invalid MSZ message', file=sys.stderr)
        return
    client.map.setSize(w, h)

def cmd_pbc(client, args):
    try:
        args = args.split(' ', 1)
        if len(args) < 2:
            raise Exception()
        id = int(args[0])
        player = client.map.getPlayerByID(id)
        if not player:
            raise Exception()
        msg = args[1]
    except Exception:
        print('Invalid PBC message', file=sys.stderr)
        return

    player.broadcast = msg
    player.broadcast_timer = 60

def cmd_pdi(client, args):
    try:
        id = int(args)
        player = client.map.getPlayerByID(id)
        if not player:
            raise Exception()
    except Exception:
        print('Invalid PDI message', file=sys.stderr)
        return

    player.team.players.remove(player)

def cmd_pic(client, args):
    try:
        args = args.split(' ')
        if len(args) < 4:
            raise Exception()
        x, y, lvl = [int(x) for x in args[:3]]
        ids = [int(x) for x in args[3:]]
        if not (0 <= x < client.map.w and 0 <= y < client.map.h and 1 <= lvl <= 8):
            raise Exception()
        players = [client.map.getPlayerByID(id) for id in ids]
        if not all([player and player.x == x and player.y == y and player.level == lvl for player in players]):
            raise Exception()
    except Exception:
        print('Invalid PIC message', file=sys.stderr)
        return
    for player in players:
        player.incantation = True

def cmd_pie(client, args):
    try:
        args = args.split(' ')
        if len(args) != 3:
            raise Exception()
        x, y, res = [int(x) for x in args]
        if not (0 <= x < client.map.w and 0 <= y < client.map.h and 0 <= res <= 1):
            raise Exception()
    except Exception:
        print('Invalid PIE message', file=sys.stderr)
        return
    for team in client.map.teams:
        for player in team.players:
            if player.x == x and player.y == y:
                player.incantation = False

def cmd_pin(client, args):
    try:
        args = args.split(' ')
        if len(args) != 10:
            raise Exception()
        id, x, y = [int(x) for x in args[:3]]
        inventory = [int(x) for x in args[3:]]
        player = client.map.getPlayerByID(id)
        if not player:
            raise Exception()
        if not (0 <= x < client.map.w and 0 <= y < client.map.h) or \
            any([q < 0 for q in inventory]):
            raise Exception()
    except Exception:
        print('Invalid PIN message', file=sys.stderr)
        return

    player.x = x
    player.y = y
    player.inventory = inventory

def cmd_plv(client, args):
    try:
        args = args.split(' ')
        if len(args) != 2:
            raise Exception()
        id, lvl = [int(x) for x in args]
        player = client.map.getPlayerByID(id)
        if not player:
            raise Exception()
        if not 1 <= lvl <= 8:
            raise Exception()
    except Exception:
        print('Invalid PLV message', file=sys.stderr)
        return

    player.level = lvl

def cmd_pnw(client, args):
    try:
        args = args.split(' ')
        if len(args) != 6:
            raise Exception()
        id, x, y, o, lvl = [int(x) for x in args[:5]]
        if client.map.getPlayerByID(id):
            raise Exception()
        if not (0 <= x < client.map.w and 0 <= y < client.map.h and \
            1 <= o <= 4 and 1 <= lvl <= 8):
            raise Exception()
        team = client.map.getTeamByName(args[5])
        if not team:
            raise Exception()
    except Exception:
        print('Invalid PNW message', file=sys.stderr)
        return

    team.players.append(Player(id, x, y, o, lvl, team))

def cmd_ppo(client, args):
    try:
        args = args.split(' ')
        if len(args) != 4:
            raise Exception()
        id, x, y, o = [int(x) for x in args]
        player = client.map.getPlayerByID(id)
        if not player:
            raise Exception()
        if not (0 <= x < client.map.w and 0 <= y < client.map.h and 1 <= o <= 4):
            raise Exception()
    except Exception:
        print('Invalid PPO message', file=sys.stderr)
        return

    player.setPosition(x, y, o)

def cmd_seg(client, args):
    try:
        if client.win_team:
            raise Exception()
        team = client.map.getTeamByName(args)
        if not team:
            raise Exception()
    except Exception:
        print('Invalid SEG message', file=sys.stderr)
        return
    client.win_team = team

def cmd_sgt(client, args):
    try:
        freq = int(args)
        if freq <= 0:
            raise Exception()
    except Exception:
        print('Invalid SGT message', file=sys.stderr)
        return
    client.freq = freq

def cmd_sst(client, args):
    try:
        freq = int(args)
        if freq <= 0:
            raise Exception()
    except Exception:
        print('Invalid SST message', file=sys.stderr)
        return
    client.freq = freq

def cmd_tna(client, args):
    client.map.teams.append(Team(args))

def cmd_ignore(client, args):
    pass

Cmds = {
    'welcome': welcome,
    'bct': cmd_bct,
    'ebo': cmd_ebo,
    'eht': cmd_eht,
    'enw': cmd_enw,
    'msz': cmd_msz,
    'pbc': cmd_pbc,
    'pdi': cmd_pdi,
    'pdr': cmd_ignore,
    'pex': cmd_ignore,
    'pfk': cmd_ignore,
    'pgt': cmd_ignore,
    'pic': cmd_pic,
    'pie': cmd_pie,
    'pin': cmd_pin,
    'plv': cmd_plv,
    'pnw': cmd_pnw,
    'ppo': cmd_ppo,
    'seg': cmd_seg,
    'sgt': cmd_sgt,
    'sst': cmd_sst,
    'tna': cmd_tna
}
