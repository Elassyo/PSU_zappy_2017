class Team:

    def __init__(self, name):
        self.name = name
        self.players = []
        return

    def getPlayerByID(self, id):
        for player in self.players:
            if player.id == id:
                return player
        return None
