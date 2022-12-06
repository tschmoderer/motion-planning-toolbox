# -*- coding: utf-8 -*-

import os
from PyQt6.QtCore import Qt, QSize
from PyQt6.QtWidgets import  (
    QDialog, 
    QLabel, 
    QVBoxLayout, 
    QScrollArea
)

dir_path = os.path.dirname(os.path.realpath(__file__))

class HelpDialog(QDialog): 
    def __init__(self, title = None, sw = 700, sh = 400):
        super().__init__()
        self.setWindowTitle(title)
        self.setFixedSize(QSize(sw, sh))

        self.layout = QVBoxLayout()

        self._msg = QLabel()
        self._msg.setAlignment(Qt.AlignmentFlag.AlignLeft | Qt.AlignmentFlag.AlignTop)
        self._msg.setMargin(10)

        scroll = QScrollArea()
        scroll.setVerticalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOn)
        scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarPolicy.ScrollBarAlwaysOff)
        scroll.setWidgetResizable(True)
        scroll.setWidget(self._msg)

        self.layout.addWidget(scroll)
        self.setLayout(self.layout)

class LicenseDialog(HelpDialog):
    def __init__(self):
        super().__init__(title = "License")

        with open(os.path.join(dir_path, "ressources", "LICENSE"), "r") as f: 
            self._msg.setText(f.read())

class ContribDialog(HelpDialog):
    def __init__(self):
        super().__init__(title = "Contributors")

        with open(os.path.join(dir_path, "ressources", "CONTRIBUTORS"), "r") as f: 
            self._msg.setText(f.read())
       