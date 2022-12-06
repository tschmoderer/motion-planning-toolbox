/// @todo put the include in a better way
#include "exp.hpp"
#include "../../include/header/controltlbx.h"

StateVector dyn(Time_t t, StateVector x) {
    StateVector dxdt(EXP_STATE_DIM);
    dxdt = StateVector::Zero(EXP_STATE_DIM);
    
    EXP_DYNAMICS_F
    
    return dxdt;
}

#ifdef EXP_DYNAMICS_dFdX
StateMatrix dyn_dx(Time_t t, StateVector x) {
    StateMatrix dxdt_dx(EXP_STATE_DIM, EXP_STATE_DIM);
    dxdt_dx = StateMatrix::Zero(EXP_STATE_DIM, EXP_STATE_DIM);
    
    EXP_DYNAMICS_dFdX

    return dxdt_dx;
}
#endif

int main(int argc, char **argv) {
    hello_world_control_tlbx();

    StateVector x0s(EXP_NB_X0*EXP_STATE_DIM); x0s << EXP_X0S;

    StateVector x0(EXP_STATE_DIM); 
    TimeVector tspan; 

    #ifdef EXP_TIMESTEPS_METHODS_TRAJ_LINSPACE
        tspan =  TimeVector::linspace(EXP_START_TIME, EXP_END_TIME, EXP_DISCRETISATION_TRAJ);
    #elif defined EXP_TIMESTEPS_METHODS_TRAJ_DATA
        Time_t * val = new Time_t[EXP_DISCRETISATION_TRAJ]{EXP_TIMESTEPS_DATA}; 
        tspan = TimeVector(EXP_DISCRETISATION_TRAJ, val);
        delete [] val;
    #endif

    #ifdef EXP_DYNAMICS_dFdX
    DynamicalSystem sys(EXP_STATE_DIM, EXP_START_TIME, EXP_END_TIME, x0, dyn, dyn_dx);
    #else 
    DynamicalSystem sys(EXP_STATE_DIM, EXP_START_TIME, EXP_END_TIME, x0, dyn);
    #endif

    ODEInt odeint(&sys, EXP_METHODS_ODE_INT, tspan);
    Trajectory traj;

    for (int i = 0; i < EXP_NB_X0; i++) {
        cout << "Start : initial condition " << i+1 << " / " <<  EXP_NB_X0 << endl;
        x0 << x0s(Eigen::seq(i*EXP_STATE_DIM, (i+1)*EXP_STATE_DIM-1));
        sys.set_x0(x0);
        
        traj = odeint.integrate();

        OutputHelper oh_traj(traj);   

        #if EXP_OUTPUT_CLI
            cout << oh_traj << endl << endl;
        #endif

        #if EXP_OUTPUT_FILE
            string dir = SOURCE_DIR + string("/") + EXP_OUTPUT_DIR + EXP_NAME + string("/");
            oh_traj.set_out_directory(dir); 
            oh_traj.format(CSVFormat).save(i+1);
        #endif
        
        cout << "End   : initial condition " << i+1 << " / " <<  EXP_NB_X0 << endl;
    }

    return 0;   
}