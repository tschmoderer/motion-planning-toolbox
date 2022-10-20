/**
* @file controlSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-20
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for ControlSystem class
*/

#ifndef CNTRLTLBX_CONTROLSYSTEM_H
#define CNTRLTLBX_CONTROLSYSTEM_H

// Macros definitions

// Additional library
#include "utils.h"
#include "controls.h"
#include "odeint/controlSystemInt.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

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
class ControlSystem {
    public: 
        /* CONSTRUCTORS */
        ControlSystem(uint16_t , uint16_t ); 
        ControlSystem(uint16_t , uint16_t , double , double , VectorXd ); 

        /* DESTRUCTORS */
        ~ControlSystem(); 

        /* ACCESSORS */
        VectorXd get_dynamics(double , VectorXd ) const;

        void set_x0(VectorXd ); 
        void set_t0(double ); 
        void set_t1(double );
        void set_controls(const Controls * );
        void set_cntrl_system_integrator(const ControlSystemInt * ); 
        void set_dynamics(std::function<VectorXd(double , VectorXd , Controls )> );
        void set_dynamics_derivative_x(std::function<MatrixXd(double , VectorXd , Controls )> );
        void set_dynamics_derivative_u(std::function<MatrixXd(double , VectorXd , Controls )> );

        /* METHODS */
        MatrixXd trajectory(); 
        VectorXd inout();

        /* OPERATORS */

    private: 
        uint16_t N; /*!< State space dimension */
        uint16_t M; /*!< Number of controls */

        VectorXd x0; /*!< Initial state */
        double t0;   /*!< Initial time */
        double t1;   /*!< Final time */

        Controls * u; 

        std::function<VectorXd(double , VectorXd , Controls )> F;
        std::function<MatrixXd(double , VectorXd , Controls )> dFdX;
        std::function<MatrixXd(double , VectorXd , Controls )> dFdU;
        
        ControlSystemInt * integrator; 

        /* PRIVATE METHODS */
        VectorXd dynamics(double , VectorXd ) const; 

};

#endif
