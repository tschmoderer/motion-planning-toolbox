# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QHBoxLayout, 
    QWidget, 
    QScrollArea, 
    QTabWidget
)

from .form.layout import FormLayout
from .form.postprocess.postprocessForm import PostprocessFormLayout
from .results.resultsLayout import ResultLayout
from .icons.icons import IconGear, IconPostProcess

import numpy as np
import os

class MainLayout(QHBoxLayout): 
    def __init__(self, basedir = None) -> None:
        super().__init__()

        self.__basedir = basedir

        self.__tabs = QTabWidget(movable = False,tabsClosable = False)

        self.__configuration = QScrollArea()
        self.__configuration.setWidgetResizable(True)

        self.__postprocess = QScrollArea()
        self.__postprocess.setWidgetResizable(True)

        self.__leftMainWidget  = QWidget()
        self.__rightMainWidget = QWidget()

        self.__leftLayout  = FormLayout()
        self.__rightLayout = ResultLayout()

        self.__leftMainWidget.setLayout(self.__leftLayout)
        self.__configuration.setWidget(self.__leftMainWidget)

        self.__postprocessMainWidget = QWidget()
        self.__postprocessLayout     = PostprocessFormLayout()
        self.__postprocessMainWidget.setLayout(self.__postprocessLayout)
        self.__postprocess.setWidget(self.__postprocessMainWidget)

        self.__tabs.addTab(self.__configuration, IconGear(), 'Configuration')
        self.__tabs.addTab(self.__postprocess, IconPostProcess(), 'PostProcess')

        self.__rightMainWidget.setLayout(self.__rightLayout)

        self.addWidget(self.__tabs)
        self.addWidget(self.__rightMainWidget)

        self.__leftLayout.stateDimChanged.connect(self.update_state_dim)

        # Handle prostprocessor event
        self.__postprocessLayout.updateConfClicked.connect(self.update_postprocess)
        self.__postprocessLayout.plotDataClicked.connect(self.plotData)

    def getValues(self): 
        data = self.__leftLayout.getValues()
        return data

    def update_postprocess(self): 
        sdim = self.__leftLayout.getStateDim()
        self.update_state_dim(sdim)
    
    def update_state_dim(self, sdim):
        self.__postprocessLayout.state_dimension = sdim
        self.__postprocessLayout.update_data_selectors(sdim)
        print("in main layout , state dim changed" + str(sdim))

    def plotData(self, xd : int, yd : int): 
        if xd == 0:
            fname = os.path.join(self.__basedir, 'results', 'vanderpol','trajectories','1', 'time.dat')
            xdata = np.loadtxt(fname, dtype='d', delimiter=',')
        else: 
            fname = os.path.join(self.__basedir, 'results', 'vanderpol','trajectories','1', 'trajectory.dat')
            xdata = np.loadtxt(fname, dtype='d', delimiter=',')
            xdata = xdata[:, xd-1]

        if yd == 0:
            fname = os.path.join(self.__basedir, 'results', 'vanderpol','trajectories','1', 'time.dat')
            ydata = np.loadtxt(fname, dtype='d', delimiter=',')
        else: 
            fname = os.path.join(self.__basedir, 'results', 'vanderpol','trajectories','1', 'trajectory.dat')
            ydata = np.loadtxt(fname, dtype='d', delimiter=',')
            ydata = xdata[:, yd-1]

        self.__rightLayout.update(xdata, ydata)
        
