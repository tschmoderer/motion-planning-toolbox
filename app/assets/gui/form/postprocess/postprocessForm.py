# -*- coding: utf-8 -*-

from PyQt6 import QtCore

from PyQt6.QtWidgets import (
    QVBoxLayout,
    QHBoxLayout,
    QLabel,
    QComboBox, 
    QGroupBox, 
    QPushButton
)

from .dataComboBox import DataComboBox

from ...icons.icons import IconPlus, IconMinus, IconUpdate, IconPaint

class PostprocessFormLayout(QVBoxLayout):
    updateConfClicked = QtCore.pyqtSignal()
    plotDataClicked   = QtCore.pyqtSignal(object, object)

    def __init__(self) -> None:
        super().__init__()

        self.state_dimension = 1

        btn_update = QPushButton(IconUpdate(), "Update configuration")
        btn_update.clicked.connect(lambda  : self.updateConfClicked.emit())
        self.addWidget(btn_update, alignment = QtCore.Qt.AlignRight | QtCore.Qt.AlignTop)

        self.addStretch(1)
        btn_add = QPushButton(IconPlus(), "Add plot")
        btn_add.clicked.connect(self.add_plot_config)
        self.addWidget(btn_add, alignment=QtCore.Qt.AlignRight)

    def create_select_data(self, sdim): 
        data_selector = DataComboBox(sdim)
        return data_selector

    def add_plot_config(self): 
        row_nb = self.count()
        plt_nb = row_nb - 1
        pos    = row_nb - 2 
        data_selector_x = self.create_select_data(self.state_dimension)
        data_selector_y = self.create_select_data(self.state_dimension)

        plotConf = QGroupBox("Plot configuration")
        layout   = QHBoxLayout()
        layout.addWidget(QLabel("x : "))
        layout.addWidget(data_selector_x)

        layout.addWidget(QLabel("y : "))
        layout.addWidget(data_selector_y)
        plotConf.setLayout(layout)
        layout.addStretch(1)

        btn_plt = QPushButton(IconPaint(), "")
        btn_plt.clicked.connect(lambda : self.make_plot(data_selector_x, data_selector_y))
        layout.addWidget(btn_plt)

        btn_remove = QPushButton(IconMinus(), "")
        btn_remove.clicked.connect(lambda : self.remove_plot_config(plotConf))
        layout.addWidget(btn_remove)

        self.insertWidget(pos, plotConf, alignment = QtCore.Qt.AlignTop)

    def remove_plot_config(self, grpbx): 
        for w in grpbx.children():
            w.deleteLater()

        grpbx.deleteLater()

    def update_data_selectors(self, sdim : int):
        row_nb = self.count()
        for i in range(row_nb): 
            itm = self.itemAt(i)
            if not itm is None: 
                grpbx = itm.widget()
                if not grpbx is None: 
                    for w in grpbx.findChildren(DataComboBox):
                        w.update(sdim)

    def make_plot(self, data_x : DataComboBox, data_y : DataComboBox): 
        x_data = data_x.currentIndex()
        y_data = data_y.currentIndex()

        self.plotDataClicked.emit(x_data, y_data)