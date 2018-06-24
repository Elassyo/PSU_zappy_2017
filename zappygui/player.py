class Player:

    def __init__(self, id, x, y, orientation):
        self.id = id
        self.x = x
        self.y = y
        self.orientation = orientation
        self.incantation = False
        self.inventory = [0, 0, 0, 0, 0, 0, 0]
        return
