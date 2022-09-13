#ifndef INTERPOLATOR_1D_H
#define INTERPOLATOR_1D_H

#include "interpolator.h"

enum extend_t : uint8_t {
    EXTEND_ZERO,
    EXTEND_CONSTANT 
};

class Interpolator1D : public Interpolator {
    public: 
        /* CONSTRUCTORS */
        Interpolator1D(); 
        Interpolator1D(interpolation_method_t , extend_t , extend_t);

        /* DESTRUCTOR */
        ~Interpolator1D();

        /* ACCESSORS */
        void set_exleft(extend_t ); 
        void set_exright(extend_t );

        extend_t get_exleft() const;
        extend_t get_exright() const;

        /* METHODS */
        double interp1d(Vector * , Vector * , double ) const;

    private: 
        /* ATTRIBUTES */
        extend_t extend_left_method;
        extend_t extend_right_method;

        /* METHODS */
        double interp1d_linear(Vector * , Vector * , double , uint16_t ) const;
        double interp1d_nearest(Vector * , Vector * , double , uint16_t ) const;
        double interp1d_constant_left(Vector * , Vector * , double , uint16_t ) const;
        double interp1d_constant_right(Vector * , Vector * , double , uint16_t ) const;

        double interp1D_extend_left(Vector * , Vector *, double ) const;
        double interp1D_extend_right(Vector * , Vector *, double ) const;
};

#endif