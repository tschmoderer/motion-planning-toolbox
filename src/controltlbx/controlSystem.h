#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

#include "linalg.h"
#include "utils.h"
#include "controls.h"

class ControlSystem {
    public: 
        ControlSystem(); 
        ControlSystem(state_t , time_t );

        ~ControlSystem(); 

        // 


    private: 
        uint8_t state_dim; 
        uint8_t cntrl_dim;

        state_t x0; 
        temps_t  t0; 
        temps_t  t1;  

        state_t (*f)(temps_t , const state_t & , const Controls & );
        Matrix (*dfdx)(temps_t , const state_t & , const Controls & );
        Matrix (*dfdu)(temps_t , const state_t & , const Controls & );
};

#endif