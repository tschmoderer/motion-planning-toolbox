import numpy as np
from datavizscripts.plotWindow import *
import os 

dir_path = os.path.dirname(os.path.realpath(__file__))

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
f = plt.figure()
pw.addPlot("Control", f)
pw.show()