/**
* @file dynamics.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CNTRLTLBX_FUNCTIONS_TYPES_H
#define CNTRLTLBX_FUNCTIONS_TYPES_H

#include "state.h"
#include "time.h"
#include "../controller/controls.h"

// Custom types
typedef std::function<StateVector_t(Time_t , StateVector_t )> dynamic_func_t;
typedef std::function<MatrixXd(Time_t , StateVector_t )> dynamic_func_dx_t;

typedef std::function<StateVector_t(Time_t , StateVector_t , Controls * )> control_func_t;
typedef std::function<MatrixXd(Time_t , StateVector_t , Controls * )> control_func_dx_t;
typedef std::function<MatrixXd(Time_t , StateVector_t , Controls * )> control_func_du_t;

#endif
