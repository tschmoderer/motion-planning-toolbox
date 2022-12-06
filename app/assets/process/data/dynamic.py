# -*- coding: utf-8 -*-

class Dynamics(): 
    def __init__(self, data): 
        if "parameters" in data: 
            self.parameters = data["parameters"]
        else: 
            self.parameters = {}
        self.f = data["f"]
        self.has_dx = False
        self.has_du = False
        if "dfdx" in data: 
            self.dfdx = data["dfdx"]
            self.has_dx = True
        if "dfdu" in data: 
            self.dfdu = data["dfdu"]
            self.has_du = True

    def printHeader(self, file): 
        for k in self.parameters: 
            file.write("#define " + str(k) + " " + str(self.parameters[k]) + "\n")
        
        file.write("#define EXP_DYNAMICS_F ")
        for i in range(len(self.f)): 
            file.write(str(self.f[i]) + " ")
        file.write("\n")
        
        if self.has_dx: 
            file.write("#define EXP_DYNAMICS_dFdX ")
            for i in range(len(self.dfdx)): 
                file.write(str(self.dfdx[i]) + " ")
            file.write("\n")
        if self.has_du:
            file.write("#define EXP_DYNAMICS_dFdU ")
            for i in range(len(self.dfdu)): 
                file.write(str(self.dfdu[i]) + " ")
            file.write("\n")

    def toDict(self): 
        data = {
            "parameters": self.parameters, 
            "f": self.f
        }
        
        if self.has_dx: 
            data["dfdx"] = self.dfdx
        if self.has_du: 
            data["dfdu"] = self.dfdu

        return data
