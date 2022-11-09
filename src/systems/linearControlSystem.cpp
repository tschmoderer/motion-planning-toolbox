#include "../../include/header/systems/linearControlSystem.h"

/* CONSTRUCTORS */

LinearControlSystem::LinearControlSystem(uint16_t s_dim, uint16_t c_dim) : ControlSystem(s_dim, c_dim) {
}

LinearControlSystem::LinearControlSystem(uint16_t s_dim, uint16_t c_dim, Time_t t0, Time_t t1, StateVector_t x0) : ControlSystem(s_dim, c_dim, t0, t1, x0) {
} 

/* DESTRUCTOR */
LinearControlSystem::~LinearControlSystem() {}

/* ACCESSORS */
void LinearControlSystem::set_dynamics_derivative_x(std::function<MatrixXd(Time_t )> a) {
    this->A_ = a;
}

void LinearControlSystem::set_dynamics_derivative_u(std::function<MatrixXd(Time_t )> b) {
    this->B_ = b;
}

/* METHODS */
StateVector_t LinearControlSystem::eval_dynamics(Time_t t, StateVector_t x) const {
    assert(this->A_);
    assert(this->B_);
    return this->A_(t) * x + this->B_(t) * (*this->u)(t);
}
