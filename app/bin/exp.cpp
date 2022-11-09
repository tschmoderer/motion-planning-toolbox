/// @todo put the include in a better way
#include "exp.hpp"
#include "../../include/header/controltlbx.h"

StateVector_t dyn(double t, StateVector_t x) {
    StateVector_t dxdt(EXP_STATE_DIM);
    
    EXP_DYNAMICS_F
    
    return dxdt;
}

MatrixXd dyn_dx(double t, StateVector_t x) {
    MatrixXd dxdt_dx(EXP_STATE_DIM, EXP_STATE_DIM);
    
    EXP_DYNAMICS_dFdX

    return dxdt_dx;
}

int main(int argc, char **argv) {
    hello_world_control_tlbx();

    StateVector_t x0s(EXP_NB_X0*EXP_STATE_DIM); x0s << EXP_X0S;

    StateVector_t x0(EXP_STATE_DIM); 
    #ifdef EXP_TYPE_DYNAMICAL 
        DynamicalSystem sys(EXP_STATE_DIM, EXP_START_TIME, EXP_END_TIME, x0, dyn, dyn_dx);
    #else 
        #ifdef EXP_TYPE_CONTROL

        #endif
    #endif
    ODEInt odeint(&sys, EXP_METHODS_ODE_INT, EXP_DISCRETISATION_TRAJ);
    Trajectory traj;

    for (int i = 0; i < EXP_NB_X0; i++) {
        x0 << x0s(Eigen::seq(i*EXP_STATE_DIM, (i+1)*EXP_STATE_DIM-1));
        sys.set_x0(x0);
        
        traj = odeint.integrate();

        if (EXP_OUTPUT_CLI) {
            cout << "Initial condition " << i+1 << " / " <<  EXP_NB_X0 << endl;
            cout << traj << endl << endl;
        }

        if (EXP_OUTPUT_FILE) {
            string current_dir = argv[0];
            current_dir = current_dir.substr(0, current_dir.find_last_of('/'));
            string dir = current_dir + "/../" + EXP_OUTPUT_FILE_DIR + EXP_NAME + "/" + EXP_OUTPUT_FILE_SUBDIR ;
            OutputHelper(traj, dir + EXP_OUTPUT_FILE_FNAME).format(CSVFormat).save(i+1);
        }
    }

    return 0;   
}