/**
* @file stateMatrix.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief 
*/

#ifndef CNTRLTLBX_STATE_MATRIX_H
#define CNTRLTLBX_STATE_MATRIX_H

#include "state.h"
#include "../array/dataMatrix.h"

typedef Matrix<State_t, STATE_VECTOR_DIM_T, STATE_VECTOR_DIM_T> StateMatrix; 

#endif
