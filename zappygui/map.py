class Map:

    def __init__(self):
        self.w = 0
        self.h = 0
        self.teams = []
        self.tiles = []
        return

    def getPlayerByID(self, id):
        for team in self.teams:
            for player in team.teams:
                if player.id == id:
                    return player
        return None

    def setSize(self, w, h):
        self.w = w
        self.h = h
        self.tiles = []
        for x in range(w):
            line = []
            for y in range(h):
                line.append([0] * 7)
            self.tiles.append(line)
