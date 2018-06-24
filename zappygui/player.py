class Player:

    def __init__(self, id, x, y, orientation, level, team):
        self.id = id
        self.level = level
        self.team = team
        self.inventory = [0, 0, 0, 0, 0, 0, 0]
        self.setPosition(x, y, orientation)
        self.broadcast = None
        self.broadcast_timer = 0

    def setPosition(self, x, y, orientation):
        self.x = x
        self.y = y
        self.orientation = orientation
        self.incantation = False
