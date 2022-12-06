/**
* @file controlSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for ControlSystem class
*/

#ifndef CNTRLTLBX_CONTROLSYSTEM_H
#define CNTRLTLBX_CONTROLSYSTEM_H

// Macros definitions

// Additional library
#include "../utils.h"
#include "../types/types.h"
#include "dynamicalSystem.h"


/**
 * @class ControlSystem
 * @brief This describes a general, non-linear dynamic system described by an Ordinary Differential Equation (ODE)
 * of the following form
 *
 * \f[
 *  \dot{x} = f(t,x,u)
 * \f]
 *
 * where \f$ t \f$ the time, \f$ x(t) \f$ is the state, and \f$ u(t) \f$ the control input.
 */
class ControlSystem : public DynamicalSystem {
    public: 
        /* CONSTRUCTORS */
        ControlSystem(STATE_VECTOR_DIM_T , CNTRL_VECTOR_DIM_T ); 
        ControlSystem(STATE_VECTOR_DIM_T , CNTRL_VECTOR_DIM_T , Time_t , Time_t , StateVector ); 

        ControlSystem(STATE_VECTOR_DIM_T , CNTRL_VECTOR_DIM_T , Time_t , Time_t , StateVector , control_func_t ); 
        ControlSystem(STATE_VECTOR_DIM_T , CNTRL_VECTOR_DIM_T , Time_t , Time_t , StateVector , control_func_t , control_func_dx_t ); 
        ControlSystem(STATE_VECTOR_DIM_T , CNTRL_VECTOR_DIM_T , Time_t , Time_t , StateVector , control_func_t , control_func_dx_t , control_func_du_t ); 

/*        ControlSystem(STATE_VECTOR_DIM_T , CNTRL_VECTOR_DIM_T , Time_t , Time_t , StateVector , control_func_t , control_func_dx_t , control_func_du_t , uint16_t , 
                        interpolation_method_t = INTERP_LINEAR, extend_t = EXTEND_ZERO, extend_t = EXTEND_ZERO, uint16_t = 0); 
*/
        /* DESTRUCTORS */
        virtual ~ControlSystem(); 

        /* ACCESSORS */
        Controls * ctrls() const;
        void set_controls(const Controls * );

        void set_dynamics(control_func_t );
        void set_dynamics_derivative_x(control_func_dx_t );
        void set_dynamics_derivative_u(control_func_du_t );

        /* METHODS */
        virtual StateVector eval_dynamics(Time_t , StateVector ) const; 

        /* OPERATORS */

    protected: 
        /*
            from Dynamical System class we get attributes N, x0, t0, t1
        */
        CNTRL_VECTOR_DIM_T M;   /*!< Number of controls */
        Controls * u; 

    private:
        control_func_t    dynamic_func;
        control_func_dx_t dynamic_func_derivative_x;
        control_func_du_t dynamic_func_derivative_u;
        
        /* PRIVATE METHODS */
        
};

#endif
