#ifndef ODEINT_LIB_INTEGRATOR1D_H
#define ODEINT_LIB_INTEGRATOR1D_H

#include "utils.h"

enum integration_method_t : uint8_t {
    EULER_EXPLICIT,
    EULER_IMPLICIT, 
    RK_4
}

class integrator1d {
    public:

    private: 
        integration_method_t i_meth;
};

#endif