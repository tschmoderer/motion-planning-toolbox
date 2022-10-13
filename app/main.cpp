#include <cstdint>
#include <iostream>

#include "../include/header/controltlbx.h"

using namespace std;

#define STATE_DIM 3
#define CONTROL_DIM 2
/*
Vector f(double t, const State & x, const Controls & u) {
    Vector dxdt(STATE_DIM);
    dxdt[0] = cos(x[2])*u[0](t);
    dxdt[1] = sin(x[2])*u[1](t);
    dxdt[2] = u[2](t);
    return dxdt; 
}

Matrix dfdx(double t, const State & x, const Control & u) {
    Matrix df_dx(STATE_DIM, STATE_DIM);
    return df_dx;
}

Matrix dfdu(double t, const State & x, const Control & u) {
    Matrix df_du(STATE_DIM, CONTROL_DIM);
    return df_du;
}
*/
int main(int argc, char **argv) {
    hello_world_control_tlbx();

    // Put your code here
    //State x0(STATE_DIM);
    //State x1(STATE_DIM);

    double t0 = 0; 
    double t1 = 1;

    Control u0;

    // End code
    return 0;
}