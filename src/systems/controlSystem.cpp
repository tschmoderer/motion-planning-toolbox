#include "../../include/header/systems/controlSystem.h"

/* CONSTRUCTORS */
ControlSystem::ControlSystem(uint16_t s_dim, uint16_t c_dim) : DynamicalSystem(s_dim) {
    this->M = c_dim;
    this->u = NULL; 
}

ControlSystem::ControlSystem(uint16_t s_dim, uint16_t c_dim, Time_t t0, Time_t t1, StateVector_t x0) : DynamicalSystem(s_dim, t0, t1, x0) {
    this->M = c_dim;
    this->u = NULL; 
}

ControlSystem::ControlSystem(
    uint16_t s_dim, 
    uint16_t c_dim, 
    Time_t t0, 
    Time_t t1, 
    StateVector_t x0,
    control_func_t f, 
    control_func_dx_t dfdx, 
    control_func_du_t dfdu) : DynamicalSystem(s_dim, t0, t1, x0) {

    this->M = c_dim;
    this->u = NULL; 
    this->dynamic_func = f;
    this->dynamic_func_derivative_x = dfdx;
    this->dynamic_func_derivative_u = dfdu;
}


ControlSystem::ControlSystem(
    uint16_t s_dim, uint16_t c_dim, 
    Time_t t0, Time_t t1, 
    StateVector_t x0, 
    control_func_t f, 
    control_func_dx_t dfdx, 
    control_func_du_t dfdu,
    uint16_t discret_ctrl, 
    interpolation_method_t im=INTERP_LINEAR, 
    extend_t el=EXTEND_ZERO, extend_t er=EXTEND_ZERO, 
    uint16_t integr_nb_points=0) : DynamicalSystem(s_dim, t0, t1, x0) 
{
    this->M = c_dim; 
    this->u = new Controls(c_dim, t0, t1, discret_ctrl, im, el, er, integr_nb_points);
    this->dynamic_func = f;
    this->dynamic_func_derivative_x = dfdx;
    this->dynamic_func_derivative_u = dfdu;
}

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

void ControlSystem::set_dynamics(std::function<VectorXd(Time_t , StateVector_t , Controls * )> func) {
    this->dynamic_func = func;
}    

void ControlSystem::set_dynamics_derivative_x(std::function<MatrixXd(Time_t , StateVector_t , Controls * )> df_dx) {
    this->dynamic_func_derivative_x = df_dx;
}

void ControlSystem::set_dynamics_derivative_u(std::function<MatrixXd(Time_t , StateVector_t , Controls * )> df_du) {
    this->dynamic_func_derivative_u = df_du;
}

/* METHODS */
StateVector_t ControlSystem::eval_dynamics(Time_t t, StateVector_t x) const {
    return this->dynamic_func(t, x, this->u);
}

/* PRIVATE METHODS */
