# -*- coding: utf-8 -*-

from PyQt6.QtGui import QAction
from .helpdialog import LicenseDialog, ContribDialog

from .icons import icons

class Menu(): 
    def __init__(self, parent) -> None:
        self.__parent  = parent
        self.__menubar = parent.menuBar()
        self.__create()

    def __create(self):
        self.__structure()
        self.__add_actions()
    
    def __structure(self):     
        self.__fileMenu = self.__menubar.addMenu('File')
        self.__editMenu = self.__menubar.addMenu('Edit')
        self.__execMenu = self.__menubar.addMenu('Execute')
        self.__helpMenu = self.__menubar.addMenu('Help')

    def __add_actions(self):
        self.__add_file_actions()
        self.__add_edit_actions()
        self.__add_exec_actions()
        self.__add_help_actions()

    def __add_file_actions(self):
        new_icon = icons.IconNewFile()
        newAction = QAction(new_icon, 'New', self.__parent)        
        newAction.setShortcut('Ctrl+N')
        newAction.setStatusTip('New document')
        newAction.triggered.connect(self.__newCall)

        self.__fileMenu.addAction(newAction)

    def __newCall(self): 
        pass

    def __add_edit_actions(self):
        pass

    def __add_exec_actions(self):
        pass 

    def __add_help_actions(self): 
        apropos = QAction("A propos", self.__parent)
        apropos.triggered.connect(self.__apropostrigger)
        
        license = QAction("License", self.__parent)
        license.triggered.connect(self.__licensetrigger)

        self.__helpMenu.addAction("Help")
        self.__helpMenu.addAction(license)
        self.__helpMenu.addAction(apropos)

    def __licensetrigger(self): 
        lcs = LicenseDialog()
        lcs.exec()

    def __apropostrigger(self): 
        ctrb = ContribDialog()
        ctrb.exec()

