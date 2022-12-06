# -*- coding: utf-8 -*-

class ODEset: 
    def __init__(self, data): 
        self.method = data["method"]

    def printHeader(self, file): 
        file.write("#define EXP_METHODS_ODE_INT " + str(self.method) + "\n")

    def toDict(self): 
        data = {"method": self.method}
        return data