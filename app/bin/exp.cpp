/// @todo put the include in a better way
#include "exp.hpp"
#include "../../include/header/controltlbx.h"

#ifdef EXP_TYPE_DYNAMICAL 
StateVector_t dyn(double t, StateVector_t x) {
    StateVector_t dxdt(EXP_STATE_DIM);
    dxdt = StateVector_t::Zero(EXP_STATE_DIM);
    
    EXP_DYNAMICS_F
    
    return dxdt;
}

MatrixXd dyn_dx(double t, StateVector_t x) {
    MatrixXd dxdt_dx(EXP_STATE_DIM, EXP_STATE_DIM);
    dxdt_dx = MatrixXd::Zero(EXP_STATE_DIM, EXP_STATE_DIM);
    
    EXP_DYNAMICS_dFdX

    return dxdt_dx;
}
#else 
#ifdef EXP_TYPE_CONTROL
StateVector_t dyn(double t, StateVector_t x, Controls & u) {
    StateVector_t dxdt(EXP_STATE_DIM);
    VectorXd cntr(EXP_NB_CNTRL);
    cntrl = u(t); 

    EXP_DYNAMICS_F
    
    return dxdt;
}

MatrixXd dyn_dx(double t, StateVector_t x, Controls & u) {
    MatrixXd dxdt_dx(EXP_STATE_DIM, EXP_STATE_DIM);
    dxdt_dx = MatrixXd::Zero(EXP_STATE_DIM, EXP_STATE_DIM);
    VectorXd cntr(EXP_NB_CNTRL);
    cntrl = u(t); 

    EXP_DYNAMICS_dFdX

    return dxdt_dx;
}

MatrixXd dyn_du(double t, StateVector_t x, Controls & u) {
    MatrixXd dxdt_du(EXP_STATE_DIM, EXP_NB_CNTRL);
    dxdt_du = MatrixXd::Zero(EXP_STATE_DIM, EXP_NB_CNTRL);
    VectorXd cntr(EXP_NB_CNTRL);
    cntrl = u(t); 

    EXP_DYNAMICS_dFdU

    return dxdt_du;
}

#endif
#endif

int main(int argc, char **argv) {
    hello_world_control_tlbx();

    StateVector_t x0s(EXP_NB_X0*EXP_STATE_DIM); x0s << EXP_X0S;

    StateVector_t x0(EXP_STATE_DIM); 
    #ifdef EXP_TYPE_DYNAMICAL 
        DynamicalSystem sys(EXP_STATE_DIM, EXP_START_TIME, EXP_END_TIME, x0, dyn, dyn_dx);
    #else 
        #ifdef EXP_TYPE_CONTROL
        ControlSystem sys(EXP_STATE_DIM, EXP_NB_CNTRL, 
                            EXP_START_TIME, EXP_END_TIME, 
                            x0, 
                            dyn, dyn_dx, dyn_du
                        );
        #endif
    #endif
    ODEInt odeint(&sys, EXP_METHODS_ODE_INT, EXP_DISCRETISATION_TRAJ);
    Trajectory traj;

    for (int i = 0; i < EXP_NB_X0; i++) {
        x0 << x0s(Eigen::seq(i*EXP_STATE_DIM, (i+1)*EXP_STATE_DIM-1));
        sys.set_x0(x0);
        
        traj = odeint.integrate();

        if (EXP_OUTPUT_TRAJ_CLI) {
            cout << "Initial condition " << i+1 << " / " <<  EXP_NB_X0 << endl;
            cout << traj << endl << endl;
        }

        if (EXP_OUTPUT_TRAJ_FILE) {
            string current_dir = argv[0];
            current_dir = current_dir.substr(0, current_dir.find_last_of('/'));
            string dir = current_dir + "/../" + EXP_OUTPUT_TRAJ_FILE_DIR + EXP_NAME + "/" + EXP_OUTPUT_TRAJ_FILE_SUBDIR ;
            OutputHelper(traj, dir + EXP_OUTPUT_TRAJ_FILE_FNAME, dir + EXP_OUTPUT_TRAJ_FILE_TIME_FNAME).format(CSVFormat).save(i+1);
        }
    }

    return 0;   
}