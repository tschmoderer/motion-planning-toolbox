/**
* @file controlSystem.h
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

class ControlSystem {
    public: 
        
    private: 
        std::function<VectorXd(double,VectorXd,Controls)> F;
        std::function<MatrixXd(double,VectorXd,Controls)> dFdX;
        std::function<MatrixXd(double,VectorXd,Controls)> dFdU;
};

#endif
