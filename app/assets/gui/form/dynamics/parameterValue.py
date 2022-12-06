# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import QLineEdit

class ParameterValue(QLineEdit): 
    def __init__(self, parent = None) -> None:
        super().__init__(parent)

        self.setPlaceholderText("Value")
        self.setToolTip("""Set a value for your macro.\nEx: 1, 8/3, sqrt(2)...""")