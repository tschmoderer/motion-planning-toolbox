/**
* @file odeint.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.2
* @date 2022-10-17
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef ODEINT_H
#define ODEINT_H

// Macros definitions

// Additional library
#include <cassert>
#include <cstdint>
#include <Eigen/Dense>
#include "../controls.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

enum odeint_method_t : uint8_t {
    EULER_EXPLICIT, 
    RK4,
};

class ODEInt {
    public: 
        /* CONSTRUCTORS */
        ODEInt(odeint_method_t ); 

        /* DESTRUCTORS */
        ~ODEInt(); 

        /* METHODS */
        MatrixXd ode_int(double , double , int , VectorXd , std::function<VectorXd(double,VectorXd)> ); 

    private: 
        /* ATTRIBUTES */
        odeint_method_t ode_meth; 
        
        /* METHODS */
        MatrixXd rk1(VectorXd , VectorXd , std::function<VectorXd(double,VectorXd)> );
        MatrixXd rk4(VectorXd , VectorXd , std::function<VectorXd(double,VectorXd)> );
};

#endif
