# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QGridLayout,
    QPushButton, 
    QComboBox,
    QSpinBox,
    QLabel,
)

from .x0Form import TrajX0Val
from ...icons import icons
from ....config import (
    UI_TRAJECTORY_METHODS,
    UI_TRAJECTORY_LINSPACE_MIN,
    UI_TRAJECTORY_LINSPACE_MAX,
)

class TrajectoryFormLayout(QGridLayout):
    def __init__(self) -> None:
        super().__init__()

        self.__methodSelector = QComboBox()
        self.__methodSelector.addItems(UI_TRAJECTORY_METHODS)
        self.__methodSelector.currentIndexChanged.connect(self.__method_selector_changed)

        self.__nbT = QSpinBox()
        self.__nbT.setRange(UI_TRAJECTORY_LINSPACE_MIN, UI_TRAJECTORY_LINSPACE_MAX)
        self.__nbT.valueChanged.connect(self.__nb_timeseps)

        # first row : method
        self.addWidget(QLabel("Method : "), 0, 0)
        self.addWidget(self.__methodSelector, 0, 1)
        self.addWidget(self.__nbT, 0, 2)

        # second row : x0
        plus_icon  = icons.IconPlus() 
        minus_icon = icons.IconPlus() 

        self.__add_x0 = QPushButton(plus_icon, "add")
        self.__add_x0.setToolTip("Add an initial condition")
        self.__add_x0.clicked.connect(self.__btn_add_x0)

        self.__x0s = TrajX0Val(idx = 1)

        self.addWidget(QLabel("X0 : "), 1, 0)
        self.addWidget(self.__x0s, 1, 1)
        #self.addWidget(self.__add_x0, 1, 2)

    def __method_selector_changed(self, i : int): 
        print(i)

    def __nb_timeseps(self, i : int): 
        print(i)

    # TODO
    def __btn_add_x0(self):
        pass

    def update_x0(self, sdim = 1): 
        nb_rows = self.rowCount()
        nb_cols = self.columnCount()
        print("Nb rows : " + str(nb_rows) + " Nb colums : " + str(nb_cols))

        cntX0 = 0
        for i in range(1, nb_cols): 
            if not self.itemAtPosition(1, i) is None: 
                cntX0 = cntX0 + 1

        # if more cols than current dim
        # delete rows from [sdim+1, to nb_rows]
        if cntX0 > sdim: 
            for i in reversed(range(sdim, cntX0)):
                print("Remove x0 label at " + str(i+1))
                widgetToRemove = self.itemAtPosition(1, i+1).widget()
                widgetToRemove.setParent(None)
                widgetToRemove.deleteLater()
                

        # if more cols than current dim
        # ass cols from [col+1, to sdim]
        if cntX0 < sdim: 
            for i in range(cntX0, sdim):
                print("Add label at col : " + str(i+1)) 
                self.addWidget(TrajX0Val(idx = i+1), 1, i+1)
    
    def getValues(self): 
        data = {}
        data ["timesteps"] = {
            "method" : UI_TRAJECTORY_METHODS[self.__methodSelector.currentIndex()].lower() ,
            "linspace" : {
                "nbT" : self.__nbT.value()
            } 
        }
        nb_rows = self.rowCount()
        nb_cols = self.columnCount()
        data["x0"] = []
        x0  = []
        for i in range(1, nb_cols): 
            itm = self.itemAtPosition(1, i)
            if not itm is None: 
                val = itm.widget().text()
                x0.append(val)
        data["x0"].append(x0) 
        return data 