# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QGridLayout,
    QPushButton, 
)

from ...icons import icons
from .parameterName  import ParameterName
from .parameterValue import ParameterValue
from .parametersRmv  import BtnRmvParam

class ParameterForm(QGridLayout): 
    def __init__(self) -> None:
        super().__init__()

        plus_icon = icons.IconPlus() 
        minus_icon = icons.IconMinus()

        self.__add_param = QPushButton(plus_icon, "add") #BtnAddParam()
        self.__add_param.setToolTip("Add a parameter")
        self.__add_param.clicked.connect(self.__btn_add_param)

        __rmv_param = BtnRmvParam(layout = self, row = 0)

        # first row
        self.addWidget(ParameterName(), 0, 0)
        self.addWidget(ParameterValue(), 0, 1)
        self.addWidget(self.__add_param, 0, 2)
        self.addWidget(__rmv_param, 0, 3)        
        self.setColumnStretch(4, 1)

    def __btn_add_param(self): 
        row_nb = self.rowCount()

        self.addWidget(ParameterName(),  row_nb, 0)
        self.addWidget(ParameterValue(), row_nb, 1)
        self.addWidget(BtnRmvParam(layout = self, row = row_nb), row_nb, 3)

    def getValues(self): 
        data = {}
        row_nb = self.rowCount()
        for i in range(row_nb): 
            key = self.itemAtPosition(i, 0).widget().text()
            val = self.itemAtPosition(i, 1).widget().text()
            if not key == '':
                data[key] = val
        return data 