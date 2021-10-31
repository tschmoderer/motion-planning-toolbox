/**
 * @file control.cpp
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Implementation of control class
 * @version 1.0
 * @date 2021-10-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "control.h"

/**
 * @brief Construct a new Control object.
 * Default Constructor
 */
Control::Control() {
    this->m  = 1; 
    this->t0 = 0.; 
    this->t1 = 1.; 
    this->N  = 2; 

    this->construct_discrete_time(); 
    this->default_data(); 
}

Control::Control(uint8_t nb_ctrl, double time_0, double time_1, uint8_t nb_time) {
    this->m  = nb_ctrl; 
    this->t0 = time_0; 
    this->t1 = time_1; 
    this->N  = nb_time; 

    this->construct_discrete_time(); 
    this->default_data(); 
}

Control::~Control() {}

/* OPERATORS */
Vector Control::operator()(double t) const {
    assert(this->t0 <= t); 
    assert(t <= this->t1); 

    Vector res(this->m); 

    /* Test if t is in the discrete points */
    for (int i=0; i<this->N; i++) {
        if (t == this->time(i)) {
            for (int j=0; j < this->m; j++) {
                res(j) = this->data(j,i); 
            }
            return res; 
        }
    }

    uint8_t whereIsT = this->locate_time(t); 

    for (int i = 0; i < this->m; i++) {
        res(i) = this->interp1d(i, t, whereIsT); 
    }

    return res; 

}

void Control::construct_discrete_time() {
    assert(this->t0 < this->t1); 
    assert(this->N >= 2); 

    this->time = Vector(this->N); 

    double dx = (this->t1 - this->t0) / (this->N - 1.); 
    
    for (int i=0; i < this->N; i++) {
        this->time(i) = this->t0 + i*dx;
    }
}

void Control::default_data() {
    this->data = Matrix(m, N); 
    for (int i=0; i<this->m; i++) {
        for (int j=0; j < this->N; j++) {
            this->data(i,j) = 0.;
        }
    }
}

/**
 * @brief Locate the indices where a time t is contained. 
 * FInd the index i such that t \in ]t_i, t_{i+1}[
 * 
 * @param t Time t (must be contained in [t0,t1] must be differnt than all t_i)
 * @return uint8_t (index of the closest discrete time that is inferior to t)
 */
uint8_t Control::locate_time(double t) const {
    uint8_t idx = 0; 
    while (t > this->time(idx)) {
        idx++; 
    }
    return (idx-1);
}

/**
 * @brief Interpolate time t located between t_i and t_{i+1}
 * 
 * @param ctrl_nb the number of the control to interpolate
 * @param t       Interpolation time 
 * @param idx_inf Index of the closest discret time
 * @return double Value of u_i(t)
 */
double Control::interp1d(uint8_t ctrl_nb, double t, uint8_t idx_inf) const {
    if (this->interp_method == INTERP_CONSTANT_LEFT) {
        return this->data(ctrl_nb, idx_inf); 
    }

    if (this->interp_method == INTERP_CONSTANT_RIGHT) {
        return this->data(ctrl_nb, idx_inf+1); 
    }

    if (this->interp_method == INTERP_NEAREST) {
        double mid = (this->time(idx_inf+1) - this->time(idx_inf)) / 2.; 
        if (t <= mid) {
            return this->data(ctrl_nb, idx_inf); 
        } else {
            return this->data(ctrl_nb, idx_inf+1); 
        }
    }

    /* Default: linear interpolation */
    double dx = this->time(idx_inf+1) - this->time(idx_inf); 
    double a = (this->data(ctrl_nb, idx_inf+1) - this->data(ctrl_nb, idx_inf)) / dx; 
    double b = (this->time(idx_inf+1) * this->data(ctrl_nb, idx_inf) - this->time(idx_inf) * this->data(ctrl_nb, idx_inf+1)) / dx;
    return a*t+b; 
}