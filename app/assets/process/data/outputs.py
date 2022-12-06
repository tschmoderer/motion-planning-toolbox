# -*- coding: utf-8 -*-

class Outputs: 
    def __init__(self, data):
        self.__cli   = data["cli"]
        self.__file  = data["file"]
        if self.__file: 
            if data["where"][-1] != "/":
                data["where"] = data["where"] + "/"
            self.__where = data["where"]
        """    
        self.hasTraj = False
        self.hasCtrl = False
        if "trajectories" in data: 
            self.traj = OutTraj(data["trajectories"])
            self.hasTraj = True
        if "controls" in data: 
            self.ctrl = OutCtrl(data["controls"])
            self.hasCtrl = True
        """
    
    def printHeader(self, file): 
        file.write("#define EXP_OUTPUT_CLI " + str(self.__cli).lower() + "\n")
        file.write("#define EXP_OUTPUT_FILE " + str(self.__file).lower() + "\n")
        if self.__file:
            file.write("#define EXP_OUTPUT_DIR \"" + self.__where + "\"\n")


    def toDict(self) -> dict: 
        data = {
            "cli": self.__cli,
            "file": self.__file
        }
        if self.__file: 
            data["where"] = self.__where
        return data
