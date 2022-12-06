# -*- coding: utf-8 -*-

from PyQt6 import QtCore
from PyQt6.QtWidgets import QToolBar
from PyQt6.QtGui import QAction

from .icons import icons

class ToolBar(QToolBar):
    runActionTriggered = QtCore.pyqtSignal()

    def __init__(self, parent = None): 
        super().__init__(parent)
        #self.setObjectName("Main toolbar")

        self.__create()

    def __create(self): 
        self.setMovable(False)
        self.__add_actions()

    def __add_actions(self): 
        check_icon   = icons.IconCheck()
        run_icon     = icons.IconRun() 
        postpro_icon = icons.IconPostProcess()

        btn_check = QAction(check_icon, "check", self)
        btn_check.setStatusTip('Check configuration')
        btn_check.triggered.connect(self.__checkExp)
        self.addAction(btn_check)

        btn_run = QAction(run_icon, "run", self)
        btn_run.setStatusTip("Run exp")
        # btn_run.triggered.connect(self.__startExp)
        btn_run.triggered.connect(lambda: self.runActionTriggered.emit())
        self.addAction(btn_run)
        
        btn_pp = QAction(postpro_icon,"postprocess", self)
        btn_pp.setStatusTip("Postprocess exp")
        btn_pp.triggered.connect(self.__postproExp)
        self.addAction(btn_pp)

    def __checkExp(self):
        pass

    def __startExp(self): 
        print("Start Experiment")

    def __postproExp(self): 
        pass