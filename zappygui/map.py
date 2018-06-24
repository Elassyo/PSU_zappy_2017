class Map:

    def __init__(self):
        self.teams = []
        self.items = []
        return

    def get_player_by_id(self, id):
        for team in self.teams:
            for player in team.teams:
                if player.id == id:
                    return player
        return None
