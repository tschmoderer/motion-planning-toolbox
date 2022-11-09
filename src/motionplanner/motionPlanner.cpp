#include "../../include/header/motionplanner/motionPlanner.h"

/* CONSTRUCTORS */
/*
MotionPlanner::MotionPlanner(
    uint16_t s_dim, 
    uint16_t c_dim, 
    Time_t t0, 
    Time_t t1, 
    StateVector_t x0, 
    StateVector_t x1,
    uint16_t nb_discretisation_ctrl, 
    interpolation_method_t im=INTERP_LINEAR, 
    extend_t el=EXTEND_ZERO, 
    extend_t er=EXTEND_ZERO,
    uint16_t integr_nb_points=0,
    odeint_method_t ode_meth=RK4, 
    uint16_t ode_nb_step=0) {

    this->sys_ = new ControlSystem(
        s_dim, c_dim, t0, t1, x0, nb_discretisation_ctrl, im, el, er, integr_nb_points); 
    this->target_ = x1;
    this->ode_integr = new ODEInt(this->sys_, ode_meth, (ode_nb_step == 0) ? 2*nb_discretisation_ctrl-1 : ode_nb_step);
}
*/

/* DESTRUCTOR */
MotionPlanner::~MotionPlanner() {
    delete this->sys_;
    delete this->ode_integr;
}

/* ACCESSORS */

/* METHODS */
Trajectory MotionPlanner::trajectory() const {
    return this->ode_integr->integrate(); 
}

StateVector_t MotionPlanner::inout() const {
    return this->trajectory().endpoint();
}