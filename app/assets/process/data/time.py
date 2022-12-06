# -*- coding: utf-8 -*-

class Times: 
    def __init__(self, data): 
        self.__start = data["start"]
        self.__end   = data["end"]
    
    def printHeader(self, file): 
        file.write("#define EXP_START_TIME " + str(self.__start) + "\n")
        file.write("#define EXP_END_TIME " + str(self.__end) + "\n")

    def toDict(self): 
        return {"start": self.__start, "end": self.__end}