#include "../../include/header/odeint/odeint.h"

/* CONSTRUCTORS */
ODEInt::ODEInt(odeint_method_t odeintmeth, uint16_t nb_tsteps) {
    assert(nb_tsteps > 1);
    this->ode_meth = odeintmeth;
    this->T = nb_tsteps;
}

ODEInt::ODEInt(const ODEInt & oi) {
    this->ode_meth = oi.ode_meth;
    this->T = oi.T;
}

/* DESTRCTORS */
ODEInt::~ODEInt() {}

/* METHODS */
MatrixXd ODEInt::ode_int(double t0, double t1, VectorXd x0, std::function<VectorXd(double,VectorXd)> F) {
    VectorXd tspan = VectorXd::LinSpaced(this->T, t0, t1); 
    switch (this->ode_meth) {
    case RK4:
        return this->rk4(tspan, x0, F);
        break;
    
    default: // rk1 EULER EXPLICIT
        return this->rk1(tspan, x0, F);
        break;
    }
} 

/* PRIVATE METHODS */
MatrixXd ODEInt::rk1(VectorXd tspan, VectorXd x0, std::function<VectorXd(double,VectorXd)> F) {
    MatrixXd res(tspan.size(), x0.size()+1); 
    VectorXd state(x0.size()); 
    VectorXd new_state(x0.size()); 
    double dt = 0.; 

    res(0, 0) = tspan(0); 
    for (int j = 0; j < x0.size(); j++) {
        res(0, j+1) = x0(j);
    }

    for (int i = 1; i < tspan.size(); i++) {
        res(i, 0) = tspan(i);
        dt = tspan(i) - tspan(i-1); 
        state     = res(i-1, Eigen::seq(1, Eigen::last));
        new_state = state + dt * F(tspan(i), state);

        for (int j = 0; j < x0.size(); j++) {
            res(i, j+1) = new_state(j);
        }
    }

    return res; 
}

MatrixXd ODEInt::rk4(VectorXd tspan, VectorXd x0, std::function<VectorXd(double,VectorXd)> F) {
    MatrixXd res(tspan.size(), x0.size()+1); 
    VectorXd state(x0.size()); 
    VectorXd new_state(x0.size()); 
    VectorXd k1(x0.size()), k2(x0.size()), k3(x0.size()), k4(x0.size());
    double dt = 0.; 

    res(0, 0) = tspan(0); 
    for (int j = 0; j < x0.size(); j++) {
        res(0, j+1) = x0(j);
    }

    for (int i = 1; i < tspan.size(); i++) {
        res(i, 0) = tspan(i);
        dt = tspan(i) - tspan(i-1); 
        state     = res(i-1, Eigen::seq(1, Eigen::last));

        k1 = F(tspan(i), state);
        k2 = F(tspan(i) + dt/2., state + k1*dt/2.);
        k3 = F(tspan(i) + dt/2., state + k2*dt/2.);
        k4 = F(tspan(i) + dt, state + dt*k3);

        new_state = state + dt * (k1 + 2*k2 +2*k3 + k4) / 6.;

        for (int j = 0; j < x0.size(); j++) {
            res(i, j+1) = new_state(j);
        }
    }


    return res;
}