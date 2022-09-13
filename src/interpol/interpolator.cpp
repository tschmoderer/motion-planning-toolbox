#include "interpolator.h"

/* CONSTRUCTORS */
Interpolator::Interpolator() {
    this->i_method = INTERP_LINEAR;
    this->data_dim = 1;
}

Interpolator::Interpolator(interpolation_method_t imeth, uint8_t data_dim) {
    this->i_method = imeth;
    this->data_dim = data_dim;
}


/* DESTRUCTOR */
Interpolator::~Interpolator() {}

void Interpolator::set_method(interpolation_method_t new_method) {
    this->i_method = new_method;
}

interpolation_method_t Interpolator::get_method() const {
    return this->i_method;
}

/**
 * @brief Locate the indices where a time t is contained. 
 * FInd the index i such that $$t \in [t_i, t_{i+1}[$$
 * 
 * @param times Vector containing times step
 * @param t Time t (must be contained in [t0,t1] must be differnt than all t_i)
 * @return uint8_t (index of the closest discrete time that is inferior to t)
 * @warning If t <= times[t0] then index of times[t0], i.e. 0, is returned
 * @warning If t > times[t1] then index of times[t1] is returned
 */
uint16_t Interpolator::locate_time(Vector * times, double t) const {
    uint16_t idx = 0; 
    uint16_t N = times->get_dim();

    while (t > (*times)[idx] && idx < N) {
        idx++; 
    }

    if (idx == 0) {
        return 0;
    }

    return (idx-1);
}