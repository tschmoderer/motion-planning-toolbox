/**
* @file utils.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CONTROLTLBX_UTILS_H
#define CONTROLTLBX_UTILS_H

// Additional library
#include <cassert>
#include <cstdint>
#include <Eigen/Dense>
#include <iostream>

// Macros definitions
#define MAX_NB_STATE 65535
#define STATE_VECTOR_DIM_T uint16_t

#define MAX_NB_TIME 65535
#define TIME_VECTOR_DIM_T uint16_t

#define MAX_NB_CNTRL 255
#define CNTRL_VECTOR_DIM_T uint8_t

#define SCALAR double

#ifndef M_PI
    /**
     * @brief A macro definig pi constants
     */
    #define M_PI 3.141592653589793238463
#endif

#ifndef M_E
    /**
     * @brief A macro defining Euler's number constant 
     */
    #define M_E  2.718281828459045235360
#endif

#endif
