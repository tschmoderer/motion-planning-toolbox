/**
* @file dynamics.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CNTRLTLBX_FUNCTIONS_TYPES_H
#define CNTRLTLBX_FUNCTIONS_TYPES_H

#include "state/stateVector.h"
#include "state/stateMatrix.h"
#include "time/time.h"

// Custom function types for dynamical systems
typedef std::function<StateVector(Time_t , StateVector)> dynamic_func_t;
typedef std::function<StateMatrix(Time_t , StateVector )> dynamic_func_dx_t;

#endif
