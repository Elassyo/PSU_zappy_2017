#!/bin/python3

class Player:
    
    def __init__(self, ID, x, y, orientation):
        self.ID = ID
        self.x = x
        self.y = y
        self.orientation = orientation
        self.incantation = False
        self.inventory = [0, 0, 0, 0, 0, 0, 0]
        return
