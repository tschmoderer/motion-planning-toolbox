#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include "vector.hpp"

typedef Vector state_t;
typedef double time_t;

class ControlSystem {
    public: 

    private: 
        state_t x0; 
        time_t  t0; 
        time_t  t1;  

};

#endif