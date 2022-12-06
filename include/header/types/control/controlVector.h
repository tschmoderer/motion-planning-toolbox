/**
* @file controlVector.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief 
*/

#ifndef CNTRLTLBX_CNTRL_VECTOR_H
#define CNTRLTLBX_CNTRL_VECTOR_H

#include "control.h"
#include "../array/dataVector.h"

typedef Vector<Cntrl_t, CNTRL_VECTOR_DIM_T> ControlVector; 
typedef Vector<Cntrl_t, TIME_VECTOR_DIM_T> ControlData; 

#endif
