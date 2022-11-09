/**
* @file dynamicalSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief A class describig an integrator of ODE
*/

#ifndef CONTROLTLBX_DYNAMICAL_SYSTEM_H
#define CONTROLTLBX_DYNAMICAL_SYSTEM_H

#include "../types/types.h"

class DynamicalSystem {
    public:
        /* CONSTRUCTORS */
        DynamicalSystem(uint16_t ); 
        DynamicalSystem(uint16_t , Time_t , Time_t , StateVector_t ); 
        DynamicalSystem(uint16_t , Time_t , Time_t , StateVector_t , dynamic_func_t , dynamic_func_dx_t ); 

        /* ACCESSORS */
        Time_t get_t0() const; 
        Time_t get_t1() const; 
        StateVector_t get_x0() const;
        bool func_derivative_x_is_set() const; 

        void set_t0(Time_t ); 
        void set_t1(Time_t );
        void set_x0(StateVector_t ); 

        virtual void set_dynamics(dynamic_func_t );
        virtual void set_dynamics_derivative_x(dynamic_func_dx_t );

        /* DESTRUCTOR */
        virtual ~DynamicalSystem(); 

        /* ACCESSORS */

        /* METHODS */
        virtual StateVector_t eval_dynamics(Time_t , StateVector_t ) const; 
        virtual StateVector_t eval_dynamics_derivative_x(Time_t , StateVector_t ) const; 

        /* OPERATORS */

    protected: 
        /* ATTRIBUTES */
        uint16_t N; /*!< State space dimension */

        StateVector_t x0; /*!< Initial state */
        Time_t  t0; /*!< Initial time */
        Time_t  t1; /*!< Final time */

    private:
        dynamic_func_t dynamic_func;
        dynamic_func_dx_t dynamic_func_derivative_x;

        /* METHODS */

};

#endif
