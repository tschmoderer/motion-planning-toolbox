# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QFormLayout,
    QLabel,
    QDoubleSpinBox
)

from .parametersForm import ParameterForm
from .dynamicFunctionForm import DynamicFuncForm

from ....config import (
    UI_MIN_TIME,
    UI_TIME_STEP
)

class DynamicsFormLayout(QFormLayout):
    def __init__(self) -> None:
        super().__init__()

        self.__dynamic_params = ParameterForm()
        self.__dynamics = DynamicFuncForm() 
        
        self.addRow(QLabel('Parameters'), self.__dynamic_params)
        self.addRow(QLabel('Function'), self.__dynamics)

    def update_dim(self, sdim : int): 
        self.__dynamics.update(sdim = sdim)

    def getValues(self): 
        data = {
            "parameters": self.__dynamic_params.getValues(), 
            "f": self.__dynamics.getValues()
        }
        return data