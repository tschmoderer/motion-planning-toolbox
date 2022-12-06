# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QGridLayout,
    QComboBox,
    QLabel,
)

from ....config import (
    UI_METHODS_ODE,
    UI_METHODS_INTERPOLATION,
)

class MethodsFormLayout(QGridLayout):
    def __init__(self) -> None:
        super().__init__()

        self.__ode_method = QComboBox()
        self.__ode_method.addItems(UI_METHODS_ODE)

        self.addWidget(QLabel("ODE integration"), 0, 0)
        self.addWidget(self.__ode_method, 0, 1)

        self.__interp_method = QComboBox()
        self.__interp_method.addItems(UI_METHODS_INTERPOLATION)

        self.addWidget(QLabel("Interpolation"), 1, 0)
        self.addWidget(self.__interp_method, 1, 1)

    def getValues(self): 
        data = {}
        data["ode"] = {
            "method": UI_METHODS_ODE[self.__ode_method.currentIndex()],
            "parameters": {}
        }
        data["interpolation"] = {
            "method": UI_METHODS_INTERPOLATION[self.__interp_method.currentIndex()],
            "parameters": {}
        }
        return data 