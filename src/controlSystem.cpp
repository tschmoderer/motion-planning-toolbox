#include "../include/header/controlSystem.h"

/* CONSTRUCTORS */
ControlSystem::ControlSystem(uint16_t s_dim, uint16_t c_dim) {
    this->N = s_dim;
    this->M = c_dim;

    this->x0 = VectorXd(s_dim); 
    this->t0 = 0.;
    this->t1 = 1.; 

    this->u = NULL; 
    this->integrator = NULL; 
}

ControlSystem::ControlSystem(uint16_t s_dim, uint16_t c_dim, double t0, double t1, VectorXd x0) {
    this->N = s_dim;
    this->M = c_dim;

    this->x0 = x0; 
    this->t0 = t0;
    this->t1 = t1; 

    this->u = NULL; 
    this->integrator = NULL; 
}

/* DESTRUCTORS */
ControlSystem::~ControlSystem() {
    if (this->u != NULL) {
        delete this->u;
    }
    if (this->integrator != NULL) {
        delete this->integrator;
    }
}

/* ACCESSORS */
VectorXd ControlSystem::get_dynamics(double t, VectorXd x) const {
    return this->dynamics(t, x);
}

void ControlSystem::set_x0(VectorXd new_x0) {
    assert(this->N == new_x0.size()); 
    this->x0 = new_x0;
}

void ControlSystem::set_t0(double new_t0) {
    assert(this->t1 > new_t0); 
    this->t0 = new_t0;
}

void ControlSystem::set_t1(double new_t1) {
    assert(this->t0 < new_t1); 
    this->t1 = new_t1;
}

void ControlSystem::set_controls(const Controls * cs) {
    assert(cs->get_nb_cntrl() == this->M); 
    if (this->u != NULL) {
        delete this->u;
    }
    this->u = new Controls(*cs); 
}

void ControlSystem::set_cntrl_system_integrator(const ControlSystemInt * odeint)  {
    if (this->integrator != NULL) {
        delete this->integrator; 
    }
    this->integrator = new ControlSystemInt(*odeint);
}

void ControlSystem::set_dynamics(std::function<VectorXd(double , VectorXd , Controls )> func) {
    this->F = func;
}    

void ControlSystem::set_dynamics_derivative_x(std::function<MatrixXd(double , VectorXd , Controls )> df_dx) {
    this->dFdX = df_dx;
}

void ControlSystem::set_dynamics_derivative_u(std::function<MatrixXd(double , VectorXd , Controls )> df_du) {
    this->dFdU = df_du;
}

/* METHODS */

MatrixXd ControlSystem::trajectory() {
    return this->integrator->integrate(this->t0, this->t1, this->x0, *this->u, this->F);
}

VectorXd ControlSystem::inout() {
    return this->trajectory()(Eigen::last, Eigen::seq(1, Eigen::last));
}

/* PRIVATE METHODS */
VectorXd ControlSystem::dynamics(double t, VectorXd x) const{
    return this->F(t, x, *(this->u));
}