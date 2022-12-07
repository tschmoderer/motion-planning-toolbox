# -*- coding: utf-8 -*-

import os, json
from .cleanJsonc import remove_comments
from .log import telllogger

def load_experiment_data(filename : os.path = None, logger = None) -> dict: 
    if filename is None: 
        return None
    
    telllogger(logger, "Open configuration file :" + filename)
    with open(filename, 'r') as jsonfile:
        jsondata = ''.join(line for line in jsonfile)
    
    telllogger(logger, "Load json data from configuration file.")
    data = json.loads(remove_comments(jsondata))

    return data