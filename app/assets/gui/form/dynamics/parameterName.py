# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import QLineEdit

class ParameterName(QLineEdit): 
    def __init__(self, parent = None) -> None:
        super().__init__(parent)

        self.setPlaceholderText("Name")
        self.setMaxLength(5)
        self.setInputMask("A" * 5)
        self.setToolTip("""Choose a name for your parameter.\nParameters are resolved as C++ macro expansions.\nChoose a name that is unique.""")
