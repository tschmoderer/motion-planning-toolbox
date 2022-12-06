# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QVBoxLayout, 
    QWidget,
    QTabWidget,
)

from .plotLayout import PlotLayout

class ResultLayout(QVBoxLayout): 
    def __init__(self) -> None: 
        super().__init__()

        self.__tabs = QTabWidget(movable = False, tabsClosable = False)

        self.addWidget(self.__tabs)

        # test
        self.add_plot()

    def add_plot(self): 
        wid  = QWidget()
        plot = PlotLayout()
        wid.setLayout(plot)
        self.__tabs.addTab(wid, plot.getTitle())

    def update(self, xdata, ydata): 
        l = self.__tabs.widget(0).layout()
        l.update_plot(xdata, ydata)
