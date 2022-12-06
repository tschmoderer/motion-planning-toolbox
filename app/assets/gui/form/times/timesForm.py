# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QFormLayout,
    QLabel,
    QDoubleSpinBox
)

from ....config import (
    UI_MIN_TIME,
    UI_TIME_STEP
)

class TimesFormLayout(QFormLayout):
    def __init__(self) -> None:
        super().__init__()

        self.__tmin = QDoubleSpinBox()
        self.__tmin.setToolTip("Select the start time.")
        self.__tmin.setMinimum(UI_MIN_TIME)
        self.__tmin.setSingleStep(UI_TIME_STEP)
        self.__tmin.valueChanged.connect(self.tmin_selector)

        self.__tmax = QDoubleSpinBox() 
        self.__tmax.setToolTip("Select the end time.")
        self.__tmax.setValue(self.__tmin.value() + UI_TIME_STEP)
        self.__tmax.setMinimum(self.__tmin.value() + UI_TIME_STEP)  
        self.__tmax.setSingleStep(UI_TIME_STEP)
        self.__tmax.valueChanged.connect(self.tmax_selector)
        
        self.addRow(QLabel('T min'),self.__tmin)
        self.addRow(QLabel('T max'),self.__tmax)
        
    def tmin_selector(self, t0): 
        self.__tmax.setMinimum(t0 + UI_TIME_STEP)
        print("Tmin changed : " + str(t0))

    def tmax_selector(self, t1): 
        self.__tmin.setMaximum(t1 - UI_TIME_STEP)
        print("Tmax changed : " + str(t1))

    def getValues(self): 
        data = {
            "start": self.__tmin.value(), 
            "end"  : self.__tmax.value()
        }
        return data