# -*- coding: utf-8 -*-

from .timesteps import TimeSteps
from .initialX0 import InitialX0

class Trajectory: 
    def __init__(self, data): 
        self.timesteps = TimeSteps(data["timesteps"])
        self.x0        = InitialX0(data["x0"])

    def printHeader(self, file): 
        self.timesteps.printHeader(file, "traj")
        self.x0.printHeader(file)

    def toDict(self): 
        data = {
            "timesteps": self.timesteps.toDict(),
            "x0": self.x0.toDict()
        }
        return data