/**
* @file motionPlanner.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-20
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for MotionPlanner class
*/

#ifndef CNTRLTLBX_MOTIONPLANNER_H
#define CNTRLTLBX_MOTIONPLANNER_H

#include "../utils.h"
#include "controls.h"
#include "odeint/controlSystemInt.h"
#include "../path/path.h"

using Eigen::VectorXd;

enum mp_method_t : uint8_t {
    R_HCM,
};

class MotionPlanner {
    public: 
        /* CONSTRUCTORS */
        MotionPlanner(ControlSystem * , VectorXd ); 

        /* DESTRUCTOR */
        ~MotionPlanner(); 

    private:
        ControlSystem * sys;
        VectorXd target; 

};

#endif
