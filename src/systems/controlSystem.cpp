#include "../../include/header/systems/controlSystem.h"

/* CONSTRUCTORS */
ControlSystem::ControlSystem(STATE_VECTOR_DIM_T s_dim, CNTRL_VECTOR_DIM_T c_dim) : DynamicalSystem(s_dim) {
    this->M = c_dim;
    this->u = NULL; 
}

ControlSystem::ControlSystem(STATE_VECTOR_DIM_T s_dim, CNTRL_VECTOR_DIM_T c_dim, Time_t t0, Time_t t1, StateVector x0) : DynamicalSystem(s_dim, t0, t1, x0) {
    this->M = c_dim;
    this->u = NULL; 
}

ControlSystem::ControlSystem(
    STATE_VECTOR_DIM_T s_dim, 
    CNTRL_VECTOR_DIM_T c_dim, 
    Time_t t0, 
    Time_t t1, 
    StateVector x0,
    control_func_t f) : DynamicalSystem(s_dim, t0, t1, x0) {

    this->M = c_dim;
    this->u = NULL; 
    this->dynamic_func = f;
}

ControlSystem::ControlSystem(
    STATE_VECTOR_DIM_T s_dim, 
    CNTRL_VECTOR_DIM_T c_dim, 
    Time_t t0, 
    Time_t t1, 
    StateVector x0,
    control_func_t f, 
    control_func_dx_t dfdx) : DynamicalSystem(s_dim, t0, t1, x0) {

    this->M = c_dim;
    this->u = NULL; 
    this->dynamic_func = f;
    this->dynamic_func_derivative_x = dfdx;
}

ControlSystem::ControlSystem(
    STATE_VECTOR_DIM_T s_dim, 
    CNTRL_VECTOR_DIM_T c_dim, 
    Time_t t0, 
    Time_t t1, 
    StateVector x0,
    control_func_t f, 
    control_func_dx_t dfdx, 
    control_func_du_t dfdu) : DynamicalSystem(s_dim, t0, t1, x0) {

    this->M = c_dim;
    this->u = NULL; 
    this->dynamic_func = f;
    this->dynamic_func_derivative_x = dfdx;
    this->dynamic_func_derivative_u = dfdu;
}

/*ControlSystem::ControlSystem(
    STATE_VECTOR_DIM_T s_dim, CNTRL_VECTOR_DIM_T c_dim, 
    Time_t t0, Time_t t1, 
    StateVector x0, 
    control_func_t f, 
    control_func_dx_t dfdx, 
    control_func_du_t dfdu,
    uint16_t discret_ctrl, 
    interpolation_method_t im, 
    extend_t el, extend_t er, 
    uint16_t integr_nb_points) : DynamicalSystem(s_dim, t0, t1, x0) 
{
    this->M = c_dim; 
    this->u = new Controls(c_dim, t0, t1, discret_ctrl, im, el, er, integr_nb_points);
    this->dynamic_func = f;
    this->dynamic_func_derivative_x = dfdx;
    this->dynamic_func_derivative_u = dfdu;
}*/

/* DESTRUCTORS */
ControlSystem::~ControlSystem() {
    if (this->u != NULL) {
        delete this->u;
    }
}

/* ACCESSORS */
Controls * ControlSystem::ctrls() const {
    return this->u; 
}

void ControlSystem::set_controls(const Controls * cs) {
    assert(cs->get_nb_cntrl() == this->M); 
    if (this->u != NULL) {
        delete this->u;
    }
    this->u = new Controls(*cs); 
}

void ControlSystem::set_dynamics(control_func_t func) {
    this->dynamic_func = func;
}    

void ControlSystem::set_dynamics_derivative_x(control_func_dx_t df_dx) {
    this->dynamic_func_derivative_x = df_dx;
}

void ControlSystem::set_dynamics_derivative_u(control_func_du_t df_du) {
    this->dynamic_func_derivative_u = df_du;
}

/* METHODS */
StateVector ControlSystem::eval_dynamics(Time_t t, StateVector x) const {
    return this->dynamic_func(t, x, this->u);
}

/* PRIVATE METHODS */
