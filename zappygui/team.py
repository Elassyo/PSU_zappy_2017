class Team:

    def __init__(self, name):
        self.name = name
        self.players = []
        return

    def add_player(self, player):
        self.players.append(player)
        return

    def get_player_by_id(self, id):
        for player in self.players:
            if player.id == id:
                return player
        return None
