/**
 * @file interpolator.cpp
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Implementation for Interpolator abstract class
 * @version 1.0
 * @date 2022-09-13
 * @copyright Copyright (c) 2022
 */

#include "interpolator.h"

/* CONSTRUCTORS */
/**
* @brief Construct a new Interpolator:: Interpolator object
* Default constructor : interpolation linear in 1D
* @warning Default interpolation method is Linear
* @warning Default dimennsion of data is 1
*/
Interpolator::Interpolator() {
    this->i_method = INTERP_LINEAR;
    this->data_dim = 1;
}

/**
 * @brief Construct a new Interpolator:: Interpolator object
 * Construct interpolator object with user specified parameters
 * @param imeth interpolation method
 * @param data_dim dimension of the data
 */
Interpolator::Interpolator(interpolation_method_t imeth, uint8_t data_dim) {
    this->i_method = imeth;
    this->data_dim = data_dim;
}


/* DESTRUCTOR */
/**
 * @brief Destroy the Interpolator:: Interpolator object
 */
Interpolator::~Interpolator() {}

/**
 * @brief Set interpolation method to interpolator object
 * @param new_method the new interpolation method to be used
 */
void Interpolator::set_method(interpolation_method_t new_method) {
    this->i_method = new_method;
}

/**
 * @brief Get the current interpolation method
 * @return interpolation_method_t 
 */
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
 * @todo check that the documentation says it correctly
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