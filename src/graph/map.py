#!/bin/python3

class Map:
    
    def __init__(self):
        self.teams = []
        self.items = []
        return

    def get_player_by_id(self, ID):
        for team in self.teams:
            for player in team.teams:
                if player.ID == ID:
                    return player
        return None
