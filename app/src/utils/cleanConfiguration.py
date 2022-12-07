# -*- coding: utf-8 -*-

from .log import telllogger

def remove_not_run_exp(data : dict) -> dict: 
    data["experiences"] = [x for x in data["experiences"] if x["run"]]
    return data

def clean_experiment_data(data : dict, logger = None) -> dict: 
    if data is None: 
        return None 
    
    telllogger(logger, "Remove not runned experiment(s).")
    data = remove_not_run_exp(data)
    return data