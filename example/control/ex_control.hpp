#ifndef EXP_HPP
#define EXP_HPP

#define EXP_TYPE_CONTROL
#define EXP_TYPE "control"
#define EXP_NAME "dubin"

#define EXP_STATE_DIM 3
#define EXP_CNTRL_DIM 2
#define EXP_START_TIME 0
#define EXP_END_TIME 20
#define EXP_NB_X0 1
#define EXP_X0S 0, 0, M_PI/4;

#define EXP_DYNAMICS_F dxdt(0) = cos(x(2)) * cntrl(0); dxdt(1) = sin(x(2)) * cntrl(0); dxdt(2) = cntrl(1);
#define EXP_DYNAMICS_dFdX dxdt_dx(0,0) = 0; dxdt_dx(0,1) = 0; dxdt_dx(0,2) = -sin(x(2)) * cntrl(0); dxdt_dx(1,0) = 0;                    dxdt_dx(1,1) = 0;                    dxdt_dx(1,2) = cos(x(2)) * cntrl(0);                    dxdt_dx(2,0) = 0;                    dxdt_dx(2,1) = 0;                    dxdt_dx(2,2) = 0;
#define EXP_DYNAMICS_dFdU dxdt_du(0,0) = cos(x(2)); dxdt_du(0,1) = 0; dxdt_du(1,0) = sin(x(2));                    dxdt_du(1,1) = 0;                    dxdt_du(2,0) = 0;                    dxdt_du(2,1) = 1;

#define EXP_DISCRETISATION_TRAJ 513
#define EXP_DISCRETISATION_CNTRL 17

#define EXP_METHODS_ODE_INT RK4

#define EXP_OUTPUT_TRAJ_CLI true
#define EXP_OUTPUT_TRAJ_FILE false
#define EXP_OUTPUT_TRAJ_FILE_DIR "./results/"
#define EXP_OUTPUT_TRAJ_FILE_SUBDIR "data/"
#define EXP_OUTPUT_TRAJ_FILE_FNAME "trajectory.dat"
#define EXP_OUTPUT_TRAJ_FILE_TIME_FNAME "traj-time.dat"

#define EXP_OUTPUT_CNTRL_CLI true
#define EXP_OUTPUT_CNTRL_FILE false
#define EXP_OUTPUT_CNTRL_FILE_DIR "./results/"
#define EXP_OUTPUT_CNTRL_FILE_SUBDIR "data/"
#define EXP_OUTPUT_CNTRL_FILE_FNAME "control.dat"
#define EXP_OUTPUT_CNTRL_FILE_TIME_FNAME "ctrl-time.dat"

#endif