# -*- coding: utf-8 -*-

class TimeSteps: 
    def __init__(self, data): 
        self.method = data["method"]
        self.has_data = False
        if self.method == "data": 
            self.val = data["data"]
            self.nbT = len(self.val)
            self.has_data = True
        elif self.method == "linspace": 
            self.nbT = data["linspace"]["nbT"]

    def printHeader(self, file, type): 
        file.write("#define EXP_DISCRETISATION_" + type.upper() + " " + str(self.nbT) + "\n")
        file.write("#define EXP_TIMESTEPS_METHODS_" + type.upper() + "_" + self.method.upper() + "\n")
        if self.has_data: 
            file.write("#define EXP_TIMESTEPS_DATA_" + type.upper() + " " + self.data + "\n") 

    def toDict(self): 
        data = {
            "method": self.method
        }

        if self.has_data: 
            data["data"] = self.val

        if self.method == "linspace": 
            data["linspace"] = {"nbT": self.nbT}
        
        return data