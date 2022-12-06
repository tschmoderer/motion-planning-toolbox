# -*- coding: utf-8 -*-

from .timesteps import TimeSteps

class Controls(): 
    def __init__(self, data): 
        self.timesteps = TimeSteps(data["timesteps"])
