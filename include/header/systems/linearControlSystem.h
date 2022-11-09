/**
* @file linearControlSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for ControlSystem class
*/

#ifndef CNTRLTLBX_LINEARCONTROLSYSTEM_H
#define CNTRLTLBX_LINEARCONTROLSYSTEM_H

// Macros definitions

// Additional library
#include "controlSystem.h"

/**
 * @brief This describes a linear control system of the following form
 *
 * \f[
 *  \dot{x} = A(t)*x+B(t)*u
 * \f]
 * 
 * where \f$A\f$ and \f$B\f$ are matrices of appropriate size
 */
class LinearControlSystem : public ControlSystem {
    public: 
        /* CONSTRUCTORS */
        LinearControlSystem(uint16_t , uint16_t ); 
        LinearControlSystem(uint16_t , uint16_t , Time_t , Time_t , StateVector_t ); 

        /* DESTRUCTORS */
        ~LinearControlSystem(); 

        /* ACCESSORS */
        void set_dynamics_derivative_x(std::function<MatrixXd(Time_t )> );
        void set_dynamics_derivative_u(std::function<MatrixXd(Time_t )> );

        /* METHODS */
        StateVector_t eval_dynamics(Time_t , StateVector_t ) const; 

    private: 
        /* ATTRIBUTES */
        std::function<MatrixXd(Time_t )> A_;
        std::function<MatrixXd(Time_t )> B_; 
};

#endif
