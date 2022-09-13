#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include "utils.h"

enum interpolation_method_t : uint8_t {
    INTERP_CONSTANT_LEFT, 
    INTERP_CONSTANT_RIGHT, 
    INTERP_NEAREST,
    INTERP_LINEAR
};

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

        /* STATIC METHODS */
};

#endif