# -*- coding: utf-8 -*-

from PyQt6.QtWidgets import (
    QFormLayout,
    QLabel,
    QLineEdit
)

class DynamicFuncForm(QFormLayout): 
    def __init__(self) -> None:
        super().__init__()

        # default is 1 
        lbl = QLabel("dxdt(0) = ")
        wid = QLineEdit()
        wid.setToolTip("Enter component of dynamics (C++ code).")
        self.addRow(lbl, wid)

    def update(self, sdim = 1): 
        nb_row = self.rowCount()
        # if more rows than current dim
        # delete rows from [sdim+1, to nb_rows]
        if nb_row > sdim: 
            for i in reversed(range(sdim, nb_row)): 
                print("delete row " + str(i))
                self.removeRow(i)
        
        # if less rows then add some
        if nb_row < sdim: 
            for i in range(nb_row, sdim): 
                print("add row "+ str(i+1))
                lbl = QLabel("dxdt(" + str(i) + ") = ")
                wid = QLineEdit()
                wid.setToolTip("Enter component of dynamics (C++ code).")
                self.addRow(lbl, wid)

    def getValues(self): 
        data   = []
        nb_row = self.rowCount()
        for i in range(nb_row): 
            #txt = "dxdt[" + str(i) + "] = " 
            txt = self.itemAt(i, QFormLayout.LabelRole).widget().text()
            txt += self.itemAt(i, QFormLayout.FieldRole).widget().text()
            txt += ";"
            data.append(txt)
        return data 