#include "../../include/header/odeint/controlSystemInt.h"

/* CONSTRUCTORS */
ControlSystemInt::ControlSystemInt(odeint_method_t odeintmeth, uint16_t nb_tsteps) : ODEInt(odeintmeth, nb_tsteps) {}

ControlSystemInt::ControlSystemInt(const ControlSystemInt & oi) : ODEInt(oi) {}

/* DESTRUCTORS */
ControlSystemInt::~ControlSystemInt() {}

/* METHODS */
Trajectory ControlSystemInt::integrate(double t0, double t1, VectorXd x0, Controls u, std::function<VectorXd(double, VectorXd , Controls )> F) {
    VectorXd tspan = VectorXd::LinSpaced(this->T, t0, t1); 
    switch (this->ode_meth) {
    case RK4:
        return this->rk4(tspan, x0, u, F);
        break;
    
    default: // rk1 EULER EXPLICIT
        return this->rk1(tspan, x0, u, F);
        break;
    }
}

/* PRIVATE METHODS */
Trajectory ControlSystemInt::rk1(VectorXd tspan, VectorXd x0, Controls u, std::function<VectorXd(double, VectorXd, Controls )> F) {
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
        dt        = tspan(i) - tspan(i-1); 
        state     = res(i-1, Eigen::seq(1, Eigen::last));
        new_state = state + dt * F(tspan(i), state, u);

        for (int j = 0; j < x0.size(); j++) {
            res(i, j+1) = new_state(j);
        }
    }

    Trajectory traj(tspan, res(Eigen::all, Eigen::seq(1,Eigen::last)));

    return traj; 
}

Tajectory ControlSystemInt::rk4(VectorXd tspan, VectorXd x0, Controls u, std::function<VectorXd(double, VectorXd, Controls )> F) {
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
        new_state = state + dt * F(tspan(i), state, u);

        for (int j = 0; j < x0.size(); j++) {
            res(i, j+1) = new_state(j);
        }
    }

    Trajectory traj(tspan, res(Eigen::all, Eigen::seq(1,Eigen::last)));

    return traj; 
}