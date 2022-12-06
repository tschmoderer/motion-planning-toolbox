# -*- coding: utf-8 -*-

class Dimensions: 
    def __init__(self, data): 
        self.__state = data["state_dim"]
        self.has_ctrl = False
        if "ctrl_dim" in data: 
            self.__ctrl  = data["ctrl_dim"]
            self.has_ctrl = True
    
    def printHeader(self, file): 
        file.write("#define EXP_STATE_DIM " + str(self.__state) + "\n")
        if self.has_ctrl: 
            file.write("#define EXP_CNTRL_DIM " + str(self.__ctrl) + "\n")
    
    def toDict(self): 
        data = {"state_dim": self.__state}
        if self.has_ctrl: 
            data["ctrl_dim"] = self.__ctrl
        return data
