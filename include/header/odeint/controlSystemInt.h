/**
* @file controlSystemInt.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-20
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CONTROL_SYSTEM_INT_H
#define CONTROL_SYSTEM_INT_H

// Macros definitions

// Additional library
#include "odeint.h"
#include "../controls.h"

class ControlSystemInt : ODEInt {
    public: 
        /* CONSTRUCTORS */
        ControlSystemInt(odeint_method_t , uint16_t ); 
        ControlSystemInt(const ControlSystemInt & ); 

        /* DESTRUCTORS */
        ~ControlSystemInt(); 

        /* METHODS */
        MatrixXd integrate(double , double , VectorXd , Controls , std::function<VectorXd(double, VectorXd , Controls )> ); 

    private: 
        /* ATTRIBUTES */

        /* PRIVATE METHODS */
        MatrixXd rk1(VectorXd , VectorXd , Controls , std::function<VectorXd(double, VectorXd , Controls )> ); 
        MatrixXd rk4(VectorXd , VectorXd , Controls , std::function<VectorXd(double, VectorXd , Controls )> ); 

};

#endif
