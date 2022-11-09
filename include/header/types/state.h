/**
* @file state.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief 
*/

#ifndef CNTRLTLBX_STATE_H
#define CNTRLTLBX_STATE_H

// Libraries
#include <Eigen/Dense>

typedef double State_t;
/*
class StateVector_t : public Eigen::VectorXd {
    StateVector_t(uint16_t , double[] );

    StateVector_t & operator=(const Eigen::VectorXd & other) {
        Eigen::VectorXd::operator=(other);
        return *this;
    }
};*/

typedef Eigen::VectorXd StateVector_t;

inline double norm(StateVector_t x) {
    return x.norm();
}

#endif
