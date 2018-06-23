#!/bin/python3

class Team:

    def __init__(self, name):
        self.name = name
        self.players = []
        return

    def add_player(self, player):
        self.players.append(player)
        return

    def get_player_by_id(self, ID):
        for player in self.players:
            if player.ID == ID:
                return player
        return None
