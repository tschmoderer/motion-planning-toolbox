# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import QLineEdit

class TrajX0Val(QLineEdit): 
    def __init__(self, idx = None): 
        super().__init__()

        self.setToolTip("Enter coordinate of starting point for trajectories.\nEx:1, 8/3, sqrt(2)")
        self.setPlaceholderText(str(idx))

    def getValue(self): 
        return self.text()