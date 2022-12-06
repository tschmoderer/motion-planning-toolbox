# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QVBoxLayout, 
    QWidget
)

from .matplotlibCanvas import MplCanvas

class PlotLayout(QVBoxLayout):
    def __init__(self) -> None: 
        super().__init__()

        self.__canvas = MplCanvas(self, width=5, height=4, dpi=100)
        #sc.axes.plot([0,1,2,3,4], [10,1,20,3,40])

        layout = QVBoxLayout()
        layout.addWidget(self.__canvas.toolbar)
        layout.addWidget(self.__canvas)

        # Create a placeholder widget to hold our toolbar and canvas.
        widget = QWidget()
        widget.setLayout(layout)

        self.addWidget(widget)

    def update_plot(self, xdata, ydata):        
        self.__canvas.axes.cla()  # Clear the canvas.
        self.__canvas.axes.plot(xdata, ydata)

        # Trigger the canvas to update and redraw.
        self.__canvas.draw()

    def getTitle(self): 
        return 'TO UPDATE'
