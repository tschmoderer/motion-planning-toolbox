/**
* @file controlSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
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
        ControlSystem(uint16_t , uint16_t ); 
        ControlSystem(uint16_t , uint16_t , Time_t , Time_t , StateVector_t ); 
        ControlSystem(uint16_t , uint16_t , Time_t , Time_t , StateVector_t , control_func_t , control_func_dx_t , control_func_du_t ); 
        ControlSystem(uint16_t , uint16_t , Time_t , Time_t , StateVector_t , control_func_t , control_func_dx_t , control_func_du_t , uint16_t , interpolation_method_t , extend_t , extend_t , uint16_t ); 

        /* DESTRUCTORS */
        virtual ~ControlSystem(); 

        /* ACCESSORS */
        Controls * ctrls() const;
        void set_controls(const Controls * );

        void set_dynamics(control_func_t );
        void set_dynamics_derivative_x(control_func_dx_t );
        void set_dynamics_derivative_u(control_func_du_t );

        /* METHODS */
        virtual StateVector_t eval_dynamics(Time_t , StateVector_t ) const; 

        /* OPERATORS */

    protected: 
        /*
            from Dynamical System class we get attributes N, x0, t0, t1
        */
        uint16_t M;   /*!< Number of controls */
        Controls * u; 

    private:
        control_func_t    dynamic_func;
        control_func_dx_t dynamic_func_derivative_x;
        control_func_du_t dynamic_func_derivative_u;
        
        /* PRIVATE METHODS */
        
};

#endif
