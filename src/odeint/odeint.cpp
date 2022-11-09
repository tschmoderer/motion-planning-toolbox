#include "../../include/header/odeint/odeint.h"

/* CONSTRUCTORS */
ODEInt::ODEInt(DynamicalSystem * asys, odeint_method_t odeintmeth, uint16_t nb_tsteps) {
    assert(nb_tsteps > 1);
    this->sys = asys;
    this->ode_meth = odeintmeth;
    this->T = nb_tsteps;
}

ODEInt::ODEInt(const ODEInt & oi) {
    this->sys = oi.sys;
    this->ode_meth = oi.ode_meth;
    this->T = oi.T;
}

/* DESTRCTORS */
ODEInt::~ODEInt() {}

/* ACCESSORS */
void ODEInt::update_integration_method(odeint_method_t new_meth) {
    this->ode_meth = new_meth;
}

void ODEInt::update_discretisation_length(uint16_t new_step) {
    this->T = new_step;
}

/* METHODS */
Trajectory ODEInt::integrate() const {
    switch (this->ode_meth) {
        case RK4:
            return this->rk4();
            break;
        
        default: // rk1 EULER EXPLICIT
            return this->rk1();
            break;
    }
}

/* PRIVATE METHODS */
Trajectory ODEInt::rk1() const {
    VectorXd tspan = VectorXd::LinSpaced(this->T, this->sys->get_t0(), this->sys->get_t1()); 
    MatrixXd res(tspan.size(), this->sys->get_x0().size()); 
    VectorXd state(this->sys->get_x0()); 
    double dt = 0.; 

    res.row(0) = state;

    for (int i = 1; i < tspan.size(); i++) {
        dt = tspan(i) - tspan(i-1); 
        state = res.row(i-1);
        res.row(i) = state + dt * this->sys->eval_dynamics(tspan(i), state);
    }

    return Trajectory(tspan, res); 
}

Trajectory ODEInt::rk4() const {
    VectorXd tspan = VectorXd::LinSpaced(this->T, this->sys->get_t0(), this->sys->get_t1()); 
    MatrixXd res(tspan.size(), this->sys->get_x0().size()); 
    VectorXd k1(this->sys->get_x0().size()), k2(this->sys->get_x0().size()), k3(this->sys->get_x0().size()), k4(this->sys->get_x0().size());

    VectorXd state(this->sys->get_x0()); 
    double dt = 0.; 

    res.row(0) = state;

    for (int i = 1; i < tspan.size(); i++) {
        dt = tspan(i) - tspan(i-1); 
        state = res.row(i-1);

        k1 = this->sys->eval_dynamics(tspan(i), state);
        k2 = this->sys->eval_dynamics(tspan(i) + dt/2., state + k1*dt/2.);
        k3 = this->sys->eval_dynamics(tspan(i) + dt/2., state + k2*dt/2.);
        k4 = this->sys->eval_dynamics(tspan(i) + dt, state + dt*k3);

        res.row(i) = state + dt * (k1 + 2*k2 +2*k3 + k4) / 6.;
    }

    return Trajectory(tspan, res); 
}