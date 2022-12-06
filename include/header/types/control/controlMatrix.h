/**
* @file controlMatrix.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief 
*/

#ifndef CNTRLTLBX_CNTRL_MATRIX_H
#define CNTRLTLBX_CNTRL_MATRIX_H

#include "control.h"
#include "../array/dataMatrix.h"

typedef Matrix<Cntrl_t, TIME_VECTOR_DIM_T, CNTRL_VECTOR_DIM_T> ControlMatrix; 

#endif
