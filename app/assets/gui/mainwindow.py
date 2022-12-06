# -*- coding: utf-8 -*-

import os

from PyQt6 import QtGui
from PyQt6.QtCore import QSize
from PyQt6.QtWidgets import (
    QMainWindow,
    QWidget, 
)

from .menus import Menu
from .toolbar import ToolBar
from .mainLayout import MainLayout
from .statusbar import StatusBar

from ..config import (
    GUI_VERSION,
    UI_WIDTH, 
    UI_HEIGHT
)

from ..config import (
    BUILD_DIR,
    BIN_DIR
)

from ..process.experience import Experience

class MainWindow(QMainWindow):
    def __init__(self, basedir = None, parent = None):
        super().__init__(parent)
        self.__basedir = basedir
        self.createUI()
        self.eventHandler()

    def createUI(self): 
        self.setWindowTitle("Control ToolBox GUI - " + str(GUI_VERSION))

        # Size and center
        self.setMinimumSize(QSize(UI_WIDTH//2, UI_HEIGHT//2))

        qr = self.frameGeometry()
        cp = QtGui.QGuiApplication.primaryScreen().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

        # Create Menus
        self.__createMenu()

        # Create ToolBar
        self.__createToolBar()

        # Create Layout
        self.__createLayout()

        self.__mainWidget = QWidget()
        self.__mainWidget.setLayout(self.__layout)
        self.setCentralWidget(self.__mainWidget)

        # Create Bottom bar 
        self.__createStatusBar()

    def __createMenu(self):
        self.__menu = Menu(parent = self)
        
    def __createToolBar(self): 
        self.__toolbar = ToolBar(parent = self)
        self.addToolBar(self.__toolbar)

    def __createLayout(self): 
        self.__layout = MainLayout(basedir = self.__basedir)

    def __createStatusBar(self): 
        self.__statusBar = StatusBar(parent = self)
        self.setStatusBar(self.__statusBar)

    def eventHandler(self): 
        self.__toolbar.runActionTriggered.connect(self.__runExp)

    def __runExp(self): 
        data = []
        data.append(
            self.__layout.getValues()
        )
        data[0]["run"] = True
        data[0]["outputs"] = {
            "cli": False, 
            "file": True,
            "where": "./results/"
        }
        print(data)

        exp = Experience(data[0])
        header = os.path.join(self.__basedir, "bin", "exp.hpp")
        exp.printHeader(header)
        compile = os.path.join(BUILD_DIR, 'app', 'bin', 'Makefile')
        os.system("make -s -f " + compile + " exp")   
        os.system(BIN_DIR + "exp")
