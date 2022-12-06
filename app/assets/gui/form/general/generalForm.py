# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QFormLayout,
    QLabel, 
    QComboBox,
    QLineEdit,
)

from ....config import (
    UI_EXP_TYPES,
    UI_MAX_NAME_LEN,
)

class GeneralFormLayout(QFormLayout):
    def __init__(self) -> None:
        super().__init__()

        self.__expType_Selector = QComboBox()
        self.__expType_Selector.setToolTip("Choose your experiment type.")
        self.__expType_Selector.addItems(UI_EXP_TYPES)
        self.__expType_Selector.currentIndexChanged.connect(self.exp_selector_changed)

        self.__namePicker = QLineEdit()
        self.__namePicker.setToolTip("Choose a name for your experiment.\nThe name will be used to save the results.\nA name is a string of characters without spaces.")
        self.__namePicker.setMaxLength(UI_MAX_NAME_LEN)
        self.__namePicker.textChanged.connect(self.name_changed)
        self.__namePicker.setInputMask("A"*UI_MAX_NAME_LEN)

        self.addRow(QLabel('Type'), self.__expType_Selector)
        self.addRow(QLabel('Name'), self.__namePicker)

    def exp_selector_changed(self, i : int): 
        print("Exp type changed : " + UI_EXP_TYPES[i])

    def name_changed(self, s):
        print("Exp name changed : " + s)

    def getValues(self): 
        data = {
            "type": UI_EXP_TYPES[self.__expType_Selector.currentIndex()], 
            "name": self.__namePicker.text(), 
        }
        return data

