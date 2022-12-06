# -*- coding: utf-8 -*-

from .data.dimension import Dimensions 
from .data.time import Times
from .data.trajectory import Trajectory
from .data.dynamic import Dynamics
from .data.methods import Methods
from .data.outputs import Outputs

class Experience: 
    """
        The Experience class stores all the information to configure and run an experiment.
    """
    def __init__(self, data):
        self.type = data["type"]
        self.name = data["name"]
        self.run  = data["run"]

        self.dimensions = Dimensions(data["dimensions"])
        self.times      = Times(data["times"])

        self.dynamics = Dynamics(data["dynamics"])

        self.trajectories = Trajectory(data["trajectories"])

        self.methods = Methods(data["methods"])

        self.outputs = Outputs(data["outputs"])
    
    def printHeader(self, filename):
        f = open(filename, "w")
        f.write("#ifndef EXP_HPP\n")
        f.write("#define EXP_HPP\n\n")

        f.write("#define EXP_TYPE_" + str(self.type).upper() + "\n")
        f.write("#define EXP_TYPE " + self.type + "\n")
        f.write("#define EXP_NAME \"" + self.name + "\"\n\n")

        self.dimensions.printHeader(f)
        f.write("\n")
        self.times.printHeader(f)
        f.write("\n")
        self.dynamics.printHeader(f)
        f.write("\n")
        self.trajectories.printHeader(f)
        f.write("\n")
        self.methods.printHeader(f)
        f.write("\n")
        self.outputs.printHeader(f)

        f.write("\n#endif")
        f.close() 
    
    def toDict(self): 
        data = {
            "type": self.type, 
            "name": self.name,
            "run" : self.run,
            "dimensions": self.dimensions.toDict(), 
            "times": self.times.toDict(), 
            "dynamics": self.dynamics.toDict(),
            "trajectories": self.trajectories.toDict(),
            "methods": self.methods.toDict(), 
            "outputs": self.outputs.toDict(), 
        }
        return data