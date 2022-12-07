# -*- coding: utf-8 -*-

import os, logging, json
from enum import Enum

from .utils import loadConfiguration, log, cleanConfiguration
from .config import (
    LIB_VERSION, 
    LIB_DOCUMENTATION, 
    LIB_CODE_LINK,
    GUI_AUTHOR, 
    GUI_EMAIL, 
    GUI_VERSION, 
)

AppType = Enum('AppType', ['CLI', 'GUI'])

class Application: 
    def __init__(self, rootdir : os.path = None, mode : AppType = AppType.CLI, configurationFileName : os.path = None) -> None:        
        self._logger = log.setup_custom_logger('main', logging.DEBUG)
        self._roodir = rootdir
        self._mode   = mode

        self._welcome()

        """Test configuration file exists"""
        self._confFile = None
        if not configurationFileName is None: 
            if not os.path.exists(os.path.join(self._roodir, configurationFileName)): 
                self._logger.warning("Input file cannot be located. The tested location is " + os.path.join(self._roodir, configurationFileName))
            else: 
                self._logger.debug("Configuration file " + os.path.join(self._roodir, configurationFileName) + " is located.")
                self._confFile = os.path.join(self._roodir, configurationFileName)

        """Try to load json configuration file"""
        self._data = loadConfiguration.load_experiment_data(self._confFile, self._logger)
        self._data = cleanConfiguration.clean_experiment_data(self._data)

        self._data_info()

    def _welcome(self) -> None: 
        self._logger.info("Welcome to Motion Planning Toolbox Interface")
        self._logger.info("Interface version : " + GUI_VERSION)
        self._logger.info("Library version   : " + LIB_VERSION)
        self._logger.info("Code              : " + LIB_CODE_LINK)
        self._logger.info("Documentation     : " + LIB_DOCUMENTATION)
        self._logger.info("Contact           : " + GUI_AUTHOR + " (" + GUI_EMAIL + ")")
        self._logger.info("--")

    def _data_info(self) -> None: 
        if self._data is None: 
            self._logger.info("No data provided or succesfully read. A configuration builder will be displayed.")
            return 
        
        self._logger.info("A configuration file with " + str(len(self._data["experiences"])) + " experiment(s) has been loaded. On start we will run each experiment.")

    def _parse(self) -> None:
        pass

    def check_configuration(self, data) -> bool: 
        pass

    def run_experiment(self, data) -> bool: 
        pass

class AppCLI(Application): 
    def __init__(self, rootdir : os.path = None, configurationFileName : os.path = None) -> None:
        super().__init__(rootdir, AppType.CLI, configurationFileName)
    
    def start(self): 
        pass 

class AppGUI(Application): 
    def __init__(self, rootdir : os.path = None, configurationFileName : os.path = None) -> None:
        super().__init__(rootdir, AppType.GUI, configurationFileName)
    
    def start(self):
        pass
