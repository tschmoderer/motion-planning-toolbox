#include "../../include/header/integrator/integrator1d.h"

Integrator1D::Integrator1D() {
    this->nb_points = 256;
}

Integrator1D::Integrator1D(uint16_t nb) {
    this->nb_points = nb;
}

Integrator1D::Integrator1D(const Integrator1D & integr) {
    this->nb_points = integr.nb_points;
}

Integrator1D::~Integrator1D() {}

double Integrator1D::integr(double a, double b, std::function<double(double)> f) const {
    double sum = 0.;
    double dx  = 0.;
    VectorXd t = VectorXd::LinSpaced(this->nb_points, a, b); 

    for (int i = 0; i < t.size()-1; i++) {
        dx = t(i+1)-t(i);
        sum += dx*(f(t(i+1)) + f(t(i)));
    }

    return sum/2.;
}

/**
 * @brief Integrate discrete data with trapezoid method
 * 
 * @param t 
 * @param d 
 * @return double 
 */
double Integrator1D::integr(VectorXd t, VectorXd d) const {
    assert(t.size() == d.size()); 
    double sum = 0.;
    double dx  = 0.;

    for (int i = 0; i < t.size()-1; i++) {
        dx = t(i+1)-t(i);
        sum += dx*(d(i+1) + d(i));
    }

    return sum/2.;
}