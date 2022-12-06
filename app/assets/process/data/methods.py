# -*- coding: utf-8 -*-

from .odeset import ODEset

class Methods(): 
    def __init__(self, data):
        self.ode = ODEset(data["ode"])

    def printHeader(self, file): 
        self.ode.printHeader(file)

    def toDict(self): 
        data = {"ode": self.ode.toDict()}
        return data 