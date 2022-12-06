# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import QLabel, QStatusBar
from datetime import date

class StatusBar(QStatusBar):
    def __init__(self, parent) -> None:
        super().__init__(parent)

        self.__create()
    
    def __create(self): 
        self.__add_copyright()

    def __add_copyright(self): 
        copyRight = QLabel(
            'Copyright © <a href="https://github.com/tschmoderer/motion-planning-toolbox">Control ToolBox</a> 2022 - ' + str(date.today().year))
        copyRight.setOpenExternalLinks(True)
        self.addPermanentWidget(copyRight)