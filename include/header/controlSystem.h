/**
* @file controlSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-19
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CNTRLTLBX_CONTROLSYSTEM_H
#define CNTRLTLBX_CONTROLSYSTEM_H

// Macros definitions

// Additional library
#include <cassert>
#include <cstdint>
#include <Eigen/Dense>
#include "controls.h"
#include "odeint/odeint.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

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
        void set_ode_integrator(const ODEInt * ); 
        void set_dynamics(std::function<VectorXd(double , VectorXd , Controls )> );
        
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
        //std::function<MatrixXd(double , VectorXd , Controls )> dFdX;
        //std::function<MatrixXd(double , VectorXd , Controls )> dFdU;
        
        ODEInt * ode_integrator; 

        /* PRIVATE METHODS */
        VectorXd dynamics(double , VectorXd ) const; 

};

#endif
