#include <cstdint>
#include <iostream>

#include "../include/header/controltlbx.h"

using namespace std;

#define STATE_DIM 3
#define NB_CNTRL 2

VectorXd f_dubin_car(double t, const VectorXd & x, const Controls & u) {
    VectorXd dxdt(STATE_DIM);
    VectorXd cntr(NB_CNTRL);

    cntr = u(t); 

    dxdt[0] = cos(x[2])*cntr(0);
    dxdt[1] = sin(x[2])*cntr(0);
    dxdt[2] = cntr(1);

    return dxdt; 
}

/*
Matrix dfdx(double t, const State & x, const Control & u) {
    Matrix df_dx(STATE_DIM, STATE_DIM);
    return df_dx;
}

Matrix dfdu(double t, const State & x, const Control & u) {
    Matrix df_du(STATE_DIM, NB_CNTRL);
    return df_du;
}
*/

int main(int argc, char **argv) {
    hello_world_control_tlbx();

    // Put your code here
    constexpr uint16_t N = STATE_DIM; 
    constexpr uint16_t M = NB_CNTRL; 
    constexpr uint16_t H = 17;
    
    constexpr double t0 = 0; 
    constexpr double t1 = 1;
    constexpr uint16_t T = 129;
    VectorXd x0(N); x0 << 0., 0., 0.;

    Interpolator1D * interpol_cntrl = new Interpolator1D(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO); 
    Integrator1D *   integr_cntrl   = new Integrator1D(H);
    ODEInt *         odeintgrator   = new ODEInt(RK4, T);                 

    Controls u(M, t0, t1, H); 
    u.set_interpolation_method(interpol_cntrl);
    u.set_integration_method(integr_cntrl);

    cout << u << endl; 
    cout << u.norm2() << endl;
    cout << u(0.4) << endl << endl; 

    ControlSystem sys(N, M, t0, t1, x0);
    sys.set_controls(&u); 
    sys.set_ode_integrator(odeintgrator); 
    sys.set_dynamics(f_dubin_car);

    cout << "Test dynamics" << endl; 
    cout << sys.get_dynamics(t0, x0) << endl << endl;

    delete interpol_cntrl;
    delete integr_cntrl;
    delete odeintgrator;

    // End code
    return 0;
}