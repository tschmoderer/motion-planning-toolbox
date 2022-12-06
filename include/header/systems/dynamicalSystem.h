/**
* @file dynamicalSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
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
        DynamicalSystem(STATE_VECTOR_DIM_T ); 
        DynamicalSystem(STATE_VECTOR_DIM_T , Time_t , Time_t , StateVector ); 
        DynamicalSystem(STATE_VECTOR_DIM_T , Time_t , Time_t , StateVector , dynamic_func_t ); 
        DynamicalSystem(STATE_VECTOR_DIM_T , Time_t , Time_t , StateVector , dynamic_func_t , dynamic_func_dx_t ); 

        /* DESTRUCTOR */
        virtual ~DynamicalSystem(); 

        /* ACCESSORS */
        Time_t get_t0() const; 
        Time_t get_t1() const; 
        StateVector get_x0() const;
        bool func_derivative_x_is_set() const; 

        void set_t0(Time_t ); 
        void set_t1(Time_t );
        void set_x0(StateVector ); 

        virtual void set_dynamics(dynamic_func_t );
        virtual void set_dynamics_derivative_x(dynamic_func_dx_t );

        /* METHODS */
        virtual StateVector eval_dynamics(Time_t , StateVector ) const; 
        virtual StateMatrix eval_dynamics_derivative_x(Time_t , StateVector ) const; 

        /* OPERATORS */

    protected: 
        /* ATTRIBUTES */
        STATE_VECTOR_DIM_T N_; /*!< State space dimension */
        StateVector x0_;       /*!< Initial state */
        Time_t  t0_;           /*!< Initial time */
        Time_t  t1_;           /*!< Final time */

    private:
        dynamic_func_t dynamic_func;                 /*!< Function \f$F(t,x)\f$ */
        dynamic_func_dx_t dynamic_func_derivative_x; /*!< Jacobian \f$\frac{\partial F}{\partial (t,x)}(t,x)\f$ */

        /* METHODS */
};

#endif
