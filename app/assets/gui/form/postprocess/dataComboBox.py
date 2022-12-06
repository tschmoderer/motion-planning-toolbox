# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QComboBox, 
)

class DataComboBox(QComboBox):    
    def __init__(self, sdim : int) -> None:
        super().__init__()
        self.make_data(sdim)

    def make_data(self, sdim : int): 
        data = ["Time"]
        for i in range(sdim): 
            data.append("x" + str(i))

        self.addItems(data)

    def update(self, sdim : int): 
        self.clear()
        self.make_data(sdim)