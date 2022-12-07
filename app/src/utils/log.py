#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import logging

class CustomFormatter(logging.Formatter):
    grey = "\x1b[38;20m"
    blue = '\x1b[38;5;39m'
    yellow = "\x1b[33;20m"
    red = "\x1b[31;20m"
    bold_red = "\x1b[31;1m"
    reset = "\x1b[0m"
    format = "%(asctime)s - %(module)s - %(levelname)s - %(message)s" # (%(filename)s:%(lineno)d)"
    datefmt = "%d-%m-%Y %H:%M"

    FORMATS = {
        logging.DEBUG: grey + format + reset,
        logging.INFO: blue + format + reset,
        logging.WARNING: yellow + format + reset,
        logging.ERROR: red + format + reset,
        logging.CRITICAL: bold_red + format + reset
    }

    def format(self, record):
        log_fmt = self.FORMATS.get(record.levelno)
        formatter = logging.Formatter(fmt = log_fmt, datefmt = self.datefmt)
        return formatter.format(record)

def setup_custom_logger(name, level = logging.DEBUG):
    
    handler = logging.StreamHandler()
    handler.setFormatter(CustomFormatter() )

    logger = logging.getLogger(name)
    logger.setLevel(level)
    logger.addHandler(handler)

    return logger

def telllogger(logger : logging.Logger, what : str): 
    if logger is None: 
        return 

    logger.debug(what)