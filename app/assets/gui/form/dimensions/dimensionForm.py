# -*- coding: utf-8 -*-

from PyQt6 import QtCore

from PyQt6.QtWidgets import (
    QFormLayout,
    QLabel,
    QSpinBox,
)

from ....config import (
    UI_MIN_STATE_DIM,
    UI_MAX_STATE_DIM,
)

class DimensionFormLayout(QFormLayout):
    stateDimChanged = QtCore.pyqtSignal(object)

    def __init__(self) -> None:
        super().__init__()
        
        self.__stateDim = QSpinBox()
        self.__stateDim.setToolTip("Select the state-space dimension.")
        self.__stateDim.setRange(UI_MIN_STATE_DIM, UI_MAX_STATE_DIM) 
        self.__stateDim.valueChanged.connect(lambda: self.stateDimChanged.emit(self.__stateDim.value()))
        
        self.addRow(QLabel('State Dimension'), self.__stateDim)

    def getValues(self): 
        data = {
           "state_dim" : self.__stateDim.value()
        }
        return data

    def getStateDim(self): 
        return self.__stateDim.value()
        
