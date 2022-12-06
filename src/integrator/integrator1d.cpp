#include "../../include/header/integrator/integrator1d.h"

Integrator1D::Integrator1D() {
    this->nb_points = 256;
}

Integrator1D::Integrator1D(TIME_VECTOR_DIM_T nb) {
    this->nb_points = nb;
}

Integrator1D::Integrator1D(const Integrator1D & integr) {
    this->nb_points = integr.nb_points;
}

Integrator1D::~Integrator1D() {}

SCALAR Integrator1D::integr(Time_t a, Time_t b, std::function<SCALAR(Time_t)> f) const {
    SCALAR sum = 0.;
    SCALAR dx  = 0.;
    TimeVector t = TimeVector::linspace(a, b, this->nb_points);

    for (int i = 0; i < t.size()-1; i++) {
        dx = t(i+1)-t(i);
        sum += dx*(f(t(i+1)) + f(t(i)));
    }

    return sum/2.;
}