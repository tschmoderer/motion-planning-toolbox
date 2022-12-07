# -*- coding: utf-8 -*-

import os, sys, argparse, logging

from src.application import AppCLI, AppGUI

from assets.process import experience, loadData
from assets.utils import log

from assets.config import BUILD_DIR, BIN_DIR
from assets.gui.gui import AppGui 

logger  = log.setup_custom_logger('main2', logging.DEBUG)
basedir = os.path.dirname(os.path.realpath(__file__))

def cli(confFile): 
    ## Load configuration file as dict data
    logger.debug("CLI Mode")
    logger.debug("Argument of python script is " + str(confFile))
    if not os.path.isfile(confFile):
        logger.critical("The provided argument is not a file or cannot be located.")
        raise Exception("The provided argument is not a file or cannot be located.")

    logger.info("The configuration file " + str(confFile) + " will be loaded.")
    data = loadData.load_json_data(confFile)

    ## Parse experiment data
    exps = []
    k    = 0
    for d in data["experiences"]: 
        k = k + 1
        logger.info("Load setting for experience # " + str(k))
        exps.append(experience.Experience(d))

    ## Run experiments
    k = 0
    for exp in exps: 
        k = k + 1
        logger.info("Print Header file for exp # " + str(k) + " : " + exp.name)
        exp.printHeader("bin/exp.hpp")

        # Compile cpp program
        logger.info("Compile for exp " + exp.name)
        err = os.system("make -s -f " + BUILD_DIR + "/app/bin/Makefile exp")
        if err: 
            logger.error("There was an error in the compilation of your experiment.")
            quit()
        logger.info("COMPILATION SUCCESSFUL")

        # Run cpp program 
        logger.info("Run exp  # " + str(k) + " : " + exp.name)
        err = os.system(BIN_DIR + "exp")

        logger.info("End exp " + exp.name)

    logger.info("Starting Post processing")

def gui(confFile = None): 
    """
    TODO: implement pass data to gui 
    """
    AppGui(basedir = dir_path, data = None)

def parse(argv : list[str]): 
    desc = "A python command Line Interface for the C++ control ToolBox"
    parser = argparse.ArgumentParser(description = desc)

    parser.add_argument("-g", "--gui", help="GUI Mode", required=False, action='store_true')
    # iscli = not (("--gui" in argv) or ("-g" in argv))
    parser.add_argument("-i", "--input", help="Input configuration file", required=False)

    args = parser.parse_args()

    return args

if __name__ == "__main__":

    args = parse(sys.argv)
    basedir = os.path.dirname(os.path.realpath(__file__))

    if args.gui: 
        app = AppGUI(rootdir = basedir, configurationFileName = args.input)
    else: 
        app = AppCLI(rootdir = basedir, configurationFileName = args.input)

    app.start()
