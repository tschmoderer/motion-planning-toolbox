#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import os

def svgFig(fig, dir, param): 
    fname = dir + "/" + param.dir_  + param.name_ + "/" + param.subdir_ + param.filename_
    fdir = os.path.dirname(fname)
    if not os.path.exists(fdir):
        os.makedirs(fdir)
    fig.savefig(fname)
    print("Plot successfully saved in " + fname + ".")


"""
@todo improve this function to handle all cases
"""
def do(cur_dir, lp):
    for idx in range(len(lp)):
        fig, ax = plt.subplots()
        ax.plot(lp[idx].xdata_, lp[idx].ydata_)
        ax.set_title(lp[idx].title_)
        ax.set_xlabel(lp[idx].xlabel_)
        ax.set_ylabel(lp[idx].ylabel_)

        if lp[idx].gui_:
            plt.show()

        if lp[idx].file_:
            svgFig(fig, cur_dir, lp[idx])