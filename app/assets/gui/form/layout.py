# -*- coding: utf-8 -*-

from PyQt6 import QtCore

from PyQt6.QtWidgets import (
    QFormLayout,
    QGridLayout,
    QVBoxLayout,
    QLabel, 
    QComboBox,
    QSpinBox,
    QDoubleSpinBox,
    QLineEdit,
    QPushButton, 
    QScrollArea,
    QGroupBox
)

from ...config import (
    UI_EXP_TYPES,
    UI_MAX_NAME_LEN,
    UI_MIN_STATE_DIM,
    UI_MAX_STATE_DIM,
    UI_TIME_STEP,
    UI_MIN_TIME,
)

from .general.generalForm import GeneralFormLayout
from .dimensions.dimensionForm import DimensionFormLayout
from .times.timesForm import TimesFormLayout
from .dynamics.dynamicsForm import DynamicsFormLayout
from .trajectory.trajectoryForm import TrajectoryFormLayout
from .methods.methodsForm import MethodsFormLayout

from .outputs.form import OutputsForm

class FormLayout(QVBoxLayout):
    stateDimChanged = QtCore.pyqtSignal(object)

    def __init__(self) -> None:
        super().__init__()

        ## General Info 
        self.__generalGroupBox = QGroupBox("General")
        self.__generalForm = GeneralFormLayout()
        self.__generalGroupBox.setLayout(self.__generalForm)
        self.addWidget(self.__generalGroupBox)

        ## Dimensions 
        self.__dimensionsGroupBox = QGroupBox("Dimensions")
        self.__dimensionsForm = DimensionFormLayout()
        self.__dimensionsGroupBox.setLayout(self.__dimensionsForm)
        self.addWidget(self.__dimensionsGroupBox)

        ## Times
        self.__timesGroupBox = QGroupBox("Times")
        self.__timesForm = TimesFormLayout()
        self.__timesGroupBox.setLayout(self.__timesForm)
        self.addWidget(self.__timesGroupBox)

        ## Dynamics
        self.__dynamicsGroupBox = QGroupBox("Dynamics")
        self.__dynamicsForm = DynamicsFormLayout()
        self.__dynamicsGroupBox.setLayout(self.__dynamicsForm)
        self.addWidget(self.__dynamicsGroupBox)

        ## Trajectories
        self.__trajectoryGroupBox = QGroupBox("Trajectories")
        self.__trajectoryForm = TrajectoryFormLayout()
        self.__trajectoryGroupBox.setLayout(self.__trajectoryForm)
        self.addWidget(self.__trajectoryGroupBox)

        ## Methods
        self.__methodsGroupBox = QGroupBox("Methods")
        self.__methodsForm = MethodsFormLayout()
        self.__methodsGroupBox.setLayout(self.__methodsForm)
        self.addWidget(self.__methodsGroupBox)

        ## Outputs


        self.addStretch(1)

        """self.__stateDim = QSpinBox()
        self.__stateDim.setToolTip("Select the state-space dimension.")
        self.__stateDim.setRange(UI_MIN_STATE_DIM, UI_MAX_STATE_DIM) 
        self.__stateDim.valueChanged.connect(self.state_dim_selector)"""

        self.__dimensionsForm.stateDimChanged.connect(self.state_dim_selector)

    def state_dim_selector(self, i : int): 
        print("State dimension changed : " + str(i))
        self.__dynamicsForm.update_dim(sdim = i)
        self.__trajectoryForm.update_x0(sdim = i)

        self.stateDimChanged.emit(i)

    def getValues(self): 
        data = self.__generalForm.getValues()
        data["dimensions"]   = self.__dimensionsForm.getValues()
        data["times"]        = self.__timesForm.getValues()
        data["dynamics"]     = self.__dynamicsForm.getValues()
        data["trajectories"] = self.__trajectoryForm.getValues()
        data["methods"]      = self.__methodsForm.getValues()

        return data

    def getStateDim(self): 
        return self.__dimensionsForm.getStateDim()