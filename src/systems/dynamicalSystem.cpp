#include "../../include/header/systems/dynamicalSystem.h"

/* CONSTRUCTORS */
DynamicalSystem::DynamicalSystem(uint16_t N) {
    this->N = N;
}

DynamicalSystem::DynamicalSystem(uint16_t N, Time_t t0, Time_t t1, StateVector_t x0) {
    this->N = N; 
    this->t0 = t0; 
    this->t1 = t1; 
    this->x0 = x0;
} 

DynamicalSystem::DynamicalSystem(uint16_t N, Time_t t0, Time_t t1, StateVector_t x0, dynamic_func_t F, dynamic_func_dx_t dFdX) {
    this->N = N; 
    this->t0 = t0; 
    this->t1 = t1; 
    this->x0 = x0;
    this->dynamic_func = F; 
    this->dynamic_func_derivative_x = dFdX;
} 

/* DESTRUCTOR */
DynamicalSystem::~DynamicalSystem() {} 

/* ACCESSORS */
Time_t DynamicalSystem::get_t0() const {
    return this->t0;
} 

Time_t DynamicalSystem::get_t1() const {
    return this->t1;
}

StateVector_t DynamicalSystem::get_x0() const {
    return this->x0; 
}

bool DynamicalSystem::func_derivative_x_is_set() const {
    return bool(this->dynamic_func_derivative_x);
}

void DynamicalSystem::set_t0(Time_t new_t0) {
    this->t0 = new_t0; 
} 

void DynamicalSystem::set_t1(Time_t new_t1) {
    this->t1 = new_t1;
}

void DynamicalSystem::set_x0(StateVector_t new_x0) {
    this->x0 = new_x0;
}

void DynamicalSystem::set_dynamics(std::function<VectorXd(Time_t , StateVector_t )> func) {
    this->dynamic_func = func;
}

void DynamicalSystem::set_dynamics_derivative_x(std::function<MatrixXd(Time_t , StateVector_t )> d_func) {
    this->dynamic_func_derivative_x = d_func;
}

/* METHODS */
StateVector_t DynamicalSystem::eval_dynamics(Time_t t, StateVector_t x) const {
    assert(this->dynamic_func);
    return this->dynamic_func(t, x);
}

StateVector_t DynamicalSystem::eval_dynamics_derivative_x(Time_t t, StateVector_t x) const {
    assert(this->dynamic_func_derivative_x);
    return this->dynamic_func_derivative_x(t, x);
}

/* OPERATORS */
