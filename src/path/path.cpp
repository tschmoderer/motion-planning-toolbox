#include "../../include/header/path/path.h"

/* CONSTRUCTOR */
Path::Path(VectorXd x0, VectorXd x1) {
    this->start_p = x0;
    this->end_p   = x1; 
}

/* DESTRUCTOR */
Path::~Path() {}

/* ACCESSORS */
void Path::set_path(std::function<VectorXd(double )> func) {
    this->path = func;
}

void Path::set_derivative_path(std::function<VectorXd(double )> dfunc) {
    this->d_path = dfunc;
}

/* METHODS */
VectorXd Path::evaluate(double s) const {
    assert(s >= this->t0); 
    assert(s <= this->t1);
    if (!this->path) {
        return (this->end_p*(s-this->t0) + this->start_p*(this->t1-s)) / (this->t1 - this->t0);
    }
    return this->path(s);
}

VectorXd Path::evaluate_derivative(double s) const {
    assert(s >= this->t0); 
    assert(s <= this->t1);
    if (!this->d_path) {
        return (this->end_p - this->start_p) / (this->t1 - this->t0); 
    }
    return this->d_path(s);
}
