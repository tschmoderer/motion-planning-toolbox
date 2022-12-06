#include "../../include/header/odeint/odeint.h"

/* CONSTRUCTORS */
ODEInt::ODEInt(DynamicalSystem * asys, odeint_method_t odeintmeth, TimeVector tsteps) {
    assert(tsteps(0) == asys->get_t0());
    this->sys = asys;
    this->ode_meth = odeintmeth;
    this->tspan = tsteps;
}

ODEInt::ODEInt(const ODEInt & oi) {
    this->sys = oi.sys;
    this->ode_meth = oi.ode_meth;
    this->tspan = oi.tspan;
}

/* DESTRCTORS */
ODEInt::~ODEInt() {}

/* ACCESSORS */
/*
void ODEInt::update_integration_method(odeint_method_t new_meth) {
    this->ode_meth = new_meth;
}

void ODEInt::update_discretisation_length(STATE_VECTOR_DIM_T new_step) {
    this->T = new_step;
}*/

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
    TimeVector tspan = this->tspan;
    StateMatrix res(tspan.size(), this->sys->get_x0().size()); 
    StateVector state(this->sys->get_x0()); 
    Time_t dt = 0.; 

    for (int j = 0; j < this->sys->get_x0().size(); j++) {
        res(0, j) = state(j);
    }

    for (int i = 1; i < tspan.size(); i++) {
        dt = tspan(i) - tspan(i-1); 
        state = this->sys->eval_dynamics(tspan(i), state);
        for (int j = 0; j < this->sys->get_x0().size(); j++) {
            res(i, j) = res(i-1, j) + dt * state(j);
            state(j)  = res(i, j);
        }
    }

    return Trajectory(tspan, res); 
}

Trajectory ODEInt::rk4() const {
    TimeVector tspan = this->tspan;
    StateMatrix res(tspan.size(), this->sys->get_x0().size()); 
    StateVector k1(this->sys->get_x0().size()), k2(this->sys->get_x0().size()), k3(this->sys->get_x0().size()), k4(this->sys->get_x0().size());
    StateVector state(this->sys->get_x0()); 
    Time_t dt = 0.; 

    for (int j = 0; j < this->sys->get_x0().size(); j++) {
        res(0, j) = state(j);
    }

    for (int i = 1; i < tspan.size(); i++) {
        dt = tspan(i) - tspan(i-1); 

        k1 = this->sys->eval_dynamics(tspan(i), state);
        k2 = this->sys->eval_dynamics(tspan(i) + dt/2., state + k1*dt/2.);
        k3 = this->sys->eval_dynamics(tspan(i) + dt/2., state + k2*dt/2.);
        k4 = this->sys->eval_dynamics(tspan(i) + dt, state + dt*k3);

        for (int j = 0; j < this->sys->get_x0().size(); j++) {
            res(i, j) = res(i-1, j) + dt * (k1(j) + 2*k2(j)  + 2*k3(j)  + k4(j) ) / 6.;
            state(j)  = res(i, j);
        }
    }

    return Trajectory(tspan, res); 
}