#include "../../include/header/systems/dynamicalSystem.h"

/* CONSTRUCTORS */
DynamicalSystem::DynamicalSystem(STATE_VECTOR_DIM_T n) {
    this->N_ = n; 
    this->x0_ = StateVector(n); 
    this->t0_ = 0.; 
    this->t1_ = 1; 
} 

DynamicalSystem::DynamicalSystem(STATE_VECTOR_DIM_T n, Time_t t0, Time_t t1, StateVector x0) {
    this->N_ = n; 
    this->x0_ = x0; 
    this->t0_ = t0; 
    this->t1_ = t1; 
} 

DynamicalSystem::DynamicalSystem(STATE_VECTOR_DIM_T n, Time_t t0, Time_t t1, StateVector x0, dynamic_func_t f) {
    this->N_ = n; 
    this->x0_ = x0; 
    this->t0_ = t0; 
    this->t1_ = t1; 
    this->dynamic_func = f; 
}        

DynamicalSystem::DynamicalSystem(STATE_VECTOR_DIM_T n, Time_t t0, Time_t t1, StateVector x0, dynamic_func_t f, dynamic_func_dx_t fx) {
    this->N_ = n; 
    this->x0_ = x0; 
    this->t0_ = t0; 
    this->t1_ = t1; 
    this->dynamic_func = f; 
    this->dynamic_func_derivative_x = fx;
}        

/* DESTRUCTOR */
DynamicalSystem::~DynamicalSystem() {}

/* ACCESSORS */
Time_t DynamicalSystem::get_t0() const {
    return this->t0_;
}

Time_t DynamicalSystem::get_t1() const {
    return this->t1_;
}

StateVector DynamicalSystem::get_x0() const {
    return this->x0_;
}

bool DynamicalSystem::func_derivative_x_is_set() const {
    return bool(this->dynamic_func_derivative_x);
}

void DynamicalSystem::set_t0(Time_t t0) {
    assert(t0 < this->t1_);
    this->t0_ = t0;
} 

void DynamicalSystem::set_t1(Time_t t1) {
    assert(t1 > this->t0_); 
    this->t1_ = t1;
}

void DynamicalSystem::set_x0(StateVector x0) {
    assert(x0.size() == this->N_);
    this->x0_ = x0;  
} 

void DynamicalSystem::set_dynamics(dynamic_func_t f) {
    this->dynamic_func = f;
}

void DynamicalSystem::set_dynamics_derivative_x(dynamic_func_dx_t fx) {
    this->dynamic_func_derivative_x = fx;
}

/* METHODS */
StateVector DynamicalSystem::eval_dynamics(Time_t t, StateVector x) const {
    assert(this->dynamic_func);
    return this->dynamic_func(t, x);
}

StateMatrix DynamicalSystem::eval_dynamics_derivative_x(Time_t t, StateVector x) const {
    assert(this->dynamic_func_derivative_x);
    return this->dynamic_func_derivative_x(t, x);
} 
