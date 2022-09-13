/**
 * @file interpolator.h
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Header file for Interpolator abstract class
 * @version 1.0
 * @date 2022-09-13
 * @copyright Copyright (c) 2022
 */

#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "utils.h"

/**
 * @brief enumeration of the different interpolation methods in 1D
 * 
 */
enum interpolation_method_t : uint8_t {
    INTERP_CONSTANT_LEFT, 
    INTERP_CONSTANT_RIGHT, 
    INTERP_NEAREST,
    INTERP_LINEAR
};

/**
 * @class Interpolator
 * @brief An abstract class to describe an interpolation operator
 */
class Interpolator {
    public:
        /* CONSTRUCTORS */
        Interpolator();
        Interpolator(interpolation_method_t , uint8_t );

        /* DESTRUCTOR */
        ~Interpolator();

        /* ACCESSORS */
        void set_method(interpolation_method_t ); 
        interpolation_method_t get_method() const;

        /* OEPRATORS */

        /* METHODS */
        uint16_t locate_time(Vector * , double ) const;

        /* VIRTUAL METHODS */
        virtual double interp1d(Vector * , Vector * , double ) const = 0;

        /* STATIC METHODS */

        /* FRIEND METHODS */

    protected:
        /* ATTRIBUTES */
        interpolation_method_t i_method;
        uint8_t data_dim;

        /* METHODS */
        
    private: 
        /* ATTRIBUTES */

        /* METHODS */
};

#endif