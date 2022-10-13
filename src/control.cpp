#include "../include/header/control.h"

/**
* @brief Construct a new Control object.
* Default Constructor
* By defauly we have the following values : 
* t0 = 0 ; t1 = 1 ; N = 2
* data = 0
* Interpolator linear with constant extension left and right
*/
Control::Control() {
    this->t0 = 0.; 
    this->t1 = 1.; 
    this->N  = 2; 

    this->time = VectorXd(this->N); 
    this->data = VectorXd(this->N);

    this->construct_discrete_time();
    this->default_data(); 
}

/**
 * @brief Destroy the Control:: Control object
 * 
 */
Control::~Control() {}

std::ostream & operator<<(std::ostream & os, const Control & c) {
    for (int i = 0; i < c.N; i++) {
        os << c.time[i] << "\t"; 
        os << c.data[i] << std::endl; 
    }
    return os; 
}

void Control::construct_discrete_time() {
    assert(this->t0 < this->t1); 
    assert(this->N >= 2); 

    double dt = (this->t1-this->t0) / (1.*this->N - 1); 
    for (int i = 0; i < this->N; i++) {
        this->time(i) = this->t0 + i * dt;
    }

    assert(this->time(0) == this->t0); 
    //assert(this->time[this->time->get_dim()] == this->t1); 
}

void Control::default_data() {
    for (int i = 0; i < this->N; i++) {
        this->data(i) = 0.;
    }
}