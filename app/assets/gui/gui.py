# -*- coding: utf-8 -*-

import os, sys

from PyQt6 import QtGui
from PyQt6.QtWidgets import QApplication

from .mainwindow import MainWindow

class AppGui: 
    def __init__(self, basedir, data = None):
        self.__app = QApplication(sys.argv)
        self.__app.setWindowIcon(QtGui.QIcon(os.path.join(basedir, 'img', 'icons', 'rocket.svg')))
        self.__win = MainWindow(basedir)
        self.__win.show()
        sys.exit(self.__app.exec())