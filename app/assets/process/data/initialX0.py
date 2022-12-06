# -*- coding: utf-8 -*-

class InitialX0: 
    def __init__(self, data): 
        self.__x0 = data
        self.nbX0 = len(self.__x0)
    
    def printHeader(self, file): 
        file.write("#define EXP_NB_X0 " + str(self.nbX0) + "\n")
        file.write("#define EXP_X0S ")
        for i in range(self.nbX0): 
            for j in range(len(self.__x0[i])):
                file.write(str(self.__x0[i][j]))
                if (j < len(self.__x0[i])-1) or (i < self.nbX0 - 1): 
                    file.write(", ")
        file.write(";\n")
    
    def toDict(self): 
        return self.__x0
