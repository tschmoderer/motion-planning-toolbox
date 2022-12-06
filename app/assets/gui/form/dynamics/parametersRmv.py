# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import QPushButton
from ...icons import icons

class BtnRmvParam(QPushButton): 
    def __init__(self, parent = None, layout = None, row = 0) -> None:
        super().__init__(parent)

        self.__layout = layout
        self.__row    = row

        self.__minus_icon = icons.IconMinus()
        self.setIcon(self.__minus_icon)
        self.setText("remove")
        self.setToolTip("Remove parameter")

        self.clicked.connect(self.__clicked)

    def __clicked(self):
        print("Remove row  " + str(self.__row))
        if self.__row > 0: 
            for i in [1, 0]:
                widgetToRemove = self.__layout.itemAtPosition(self.__row, i).widget()
                widgetToRemove.setParent(None)
                widgetToRemove.deleteLater()
            self.setParent(None)
            self.deleteLater()
        else: 
            w = self.__layout.itemAtPosition(self.__row, 0).widget().setText("")
            self.__layout.itemAtPosition(self.__row, 1).widget().setText("")
