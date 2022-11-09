#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import numpy as np

class plotData(): 
    def __init__(self, data, npData, idx):
        """
        attributes: 
        * type_ : type of the experiment
        * name_ : name of the experiment
        * nbX0_ : number of x0 conditions
        * dim_  : dimension of the plot (2 or three)
        * plotType_: plot type: can be scatter, line
        * nb_ : plot for a specific x0 or for all
        * xdata_: data for x 
        * ydata_: data for y 
        * zdata_: data for z (opt)
        *
        * title_: figure title (default: "default title")
        * xlabel_ : x-axis label (default: "default xlabel")
        * ylabel_ : y-axis label (default: "default ylabel")
        * zlabel_ : z-axis label (default: "default zlabel")
        * 
        * gui_: bool to display the plot
        * file_: bool to save the plot
        * filename_: name of the saved figure
        * dir_: where to save the plot
        * subdir_: where to save th plots subfolder
        """
        self.type_ = data["type"]
        self.name_ = data["name"]
        self.nbX0_ = len(data["general"]["x0"])

        plotData = data["postprocess"]["plots"][idx]
        self.plotType_ = plotData["type"]

        if "z" in plotData["data"]:
            self.dim_ = 3
        else: 
            self.dim_ = 2

        self.nb_ = plotData["data"]["nb"]

        # load data
        if self.nb_ == 0: 
            # plot for all x0
            time = npData[0][:,0]

            nbT = len(time)
            nbX = np.shape(npData[0])[1]-1
            nbX0 = self.nbX0_
            coord = np.empty((nbT, nbX, nbX0) ,dtype=np.double)
            for t in range(nbT):
                for i in range(nbX):
                    for k in range(nbX0):
                        coord[t][i][k] = npData[k][t][i+1]
        else: 
            # plot for a specific x0
            time  = npData[self.nb_-1][:,0]
            coord = npData[self.nb_-1][:,1:-1]

        #distribute data in object
        if plotData["data"]["x"] == 0: 
            #self.xdata_ = time
            self.xdata_ = time
        else: 
            # self.xdata_ = x(idx)
            self.xdata_ = coord[:, plotData["data"]["x"]-1]

        if plotData["data"]["y"] == 0: 
            #self.ydata_ = time
            self.ydata_ = time
        else: 
            # self.ydata_ = y(idx)
            self.ydata_ = coord[:, plotData["data"]["y"]-1]

        if self.dim_ == 3: 
            if plotData["data"]["z"] == 0: 
                #self.zdata_ = time
                self.zdata_ = time
            else: 
                # self.zdata_ = z(idx)
                self.zdata_ = coord[:, plotData["data"]["z"]-1]
        
        if "title" in plotData: 
            self.title_ = plotData["title"]
        else:
            self.title_ = "Default Title"

        if "xlabel" in plotData: 
            self.xlabel_ = plotData["xlabel"]
        else:
            self.xlabel_ = "Default xlabel"

        if "ylabel" in plotData: 
            self.ylabel_ = plotData["ylabel"]
        else:
            self.ylabel_ = "Default ylabel"

        if "zlabel" in plotData: 
            self.zlabel_ = plotData["zlabel"]
        else:
            self.zlabel_ = "Default zlabel"   

        if "output" in plotData:
            if 'gui' in plotData["output"]:
                self.gui_ = plotData["output"]["gui"]
            else: 
                self.gui_ = False

            if "file" in plotData["output"]:
                self.file_ = plotData["output"]["file"]["yn"]
            else:
                self.file_ = False
            if self.file_: 
                self.dir_ = plotData["output"]["file"]["dir"]
                self.subdir_ = plotData["output"]["file"]["subdir"]
                self.filename_ = plotData["output"]["file"]["filename"]

        else:
            self.gui_  = False
            self.file_ = False
        
        


"""
return a list of Plotparam object for each plot to be produced
"""
def plots_parameters(data, npdata): 
    lp = []
    for k in range(len(data["postprocess"]["plots"])):
        lp.append(plotData(data, npdata, k))
    return lp