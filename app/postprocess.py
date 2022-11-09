#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from assets.datavizscripts.plotWindow import *
from assets.postprocess import *
import os 
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))

if len(sys.argv) < 2:
    raise Exception("You should provide the .json file used to generate your experiment(s)")
else:
    if not os.path.isfile(sys.argv[1]):
        raise Exception("The provided argument is not a file or cannot be located.")

data = loadData.load_json_data(sys.argv[1])
checkData.check_data(data)

for k in range(len(data["experiences"])):
    cur_dat = data["experiences"][k]
    print("Experience #" + str(k+1) + " will be postprocessed")
    print("An experiment about a dynamical system named " + data["experiences"][k]["name"] + " is being processed.")
    print(str(len(cur_dat["postprocess"]["plots"])) + " plot(s) will be generated.\n")
    
    results = loadData.load_np_data(dir_path, cur_dat)
    output.do(dir_path, plotParam.plots_parameters(cur_dat, results))



"""
pw = plotWindow()
## PROCESS A TRAJECTORY
traj = np.loadtxt(dir_path + "/exp_0/trajectory.dat", dtype='d', delimiter=',')
r,c  = traj.shape
time = traj[:, 0]

nb_tabs    = (c-1) // 4
plt_remain = (c-1) % 4
if (plt_remain > 0): 
    nb_tabs = nb_tabs + 1

for tab in range(1, nb_tabs+1):
    if (tab < nb_tabs): 
        f, axs = plt.subplots(2 , 2, sharex=True)
        for idx in range(1, 5):
            axs[idx-1].plot(time, traj[:, 4*(tab-1)+idx])
            axs[idx-1].set_xlabel("Time")
            axs[idx-1].set_ylabel("Coordinate $x_"+str(4*(tab-1)+idx)+"$")
    else:
        f, axs = plt.subplots(1 , plt_remain, sharex=True)
        for idx in range(1, plt_remain+1):
            axs[idx-1].plot(time, traj[:, 4*(tab-1)+idx])
            axs[idx-1].set_xlabel("Time")
            axs[idx-1].set_ylabel("Coordinate $x_"+str(4*(tab-1)+idx)+"$")
    f.suptitle('Trajectory of the system -- ' + str(tab) + " / " + str(nb_tabs))
    pw.addPlot("Trajectory " + str(tab) + " / " + str(nb_tabs), f)

## PROCESS A CONTROL
cntrl = np.loadtxt(dir_path + "/exp_0/control.dat", dtype='d', delimiter=',')
r,c  = cntrl.shape
time = cntrl[:, 0]

nb_tabs    = (c-1) // 4
plt_remain = (c-1) % 4
if (plt_remain > 0): 
    nb_tabs = nb_tabs + 1

for tab in range(1, nb_tabs+1):
    if (tab < nb_tabs): 
        f, axs = plt.subplots(2 , 2, sharex=True)
        for idx in range(1, 5):
            axs[idx-1].plot(time, cntrl[:, 4*(tab-1)+idx])
            axs[idx-1].set_xlabel("Time")
            axs[idx-1].set_ylabel("Control $u_"+str(4*(tab-1)+idx)+"$")
    else:
        f, axs = plt.subplots(1 , plt_remain, sharex=True)
        for idx in range(1, plt_remain+1):
            axs[idx-1].plot(time, cntrl[:, 4*(tab-1)+idx])
            axs[idx-1].set_xlabel("Time")
            axs[idx-1].set_ylabel("Control $u_"+str(4*(tab-1)+idx)+"$")
    f.suptitle('Control of the system -- ' + str(tab) + " / " + str(nb_tabs))
    pw.addPlot("Control " + str(tab) + " / " + str(nb_tabs), f)

## Show figure
pw.show()
"""