/**
* @file motionPlannerRHCM.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for MotionPlannerRCHM class
*/

#ifndef CNTRLTLBX_MOTIONPLANNERRHCM_H
#define CNTRLTLBX_MOTIONPLANNERRHCM_H

#include "motionPlanner.h"

/**
 * @brief Class to implement the regularised homotopy continuation method
 * 
 */
class MotionPlannerRHCM : MotionPlanner {
    public: 

    private: 
        /* ATTRIBUTES */
        StateVector_t endpoint_first_shot_;
};

#endif
