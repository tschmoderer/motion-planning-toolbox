/**
* @file motionPlanner.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for MotionPlanner class
*/

#ifndef CNTRLTLBX_MOTIONPLANNER_H
#define CNTRLTLBX_MOTIONPLANNER_H

#include "../utils.h"
#include "../controller/controls.h"
#include "../odeint/odeint.h"
#include "../path/path.h"
#include "../types/types.h"
#include "../systems/controlSystem.h"


class MotionPlanner {
    public: 
        /* CONSTRUCTORS */
    MotionPlanner(
        uint16_t ,
        uint16_t ,
        Time_t ,
        Time_t ,
        StateVector_t ,
        control_func_t ,
        control_func_dx_t ,
        control_func_du_t ,
        StateVector_t ,
        uint16_t ,
        interpolation_method_t ,
        extend_t ,
        extend_t ,
        uint16_t ,
        odeint_method_t ,
        uint16_t );
    
        MotionPlanner(ControlSystem * , StateVector_t , ODEInt * ); 

        /* DESTRUCTOR */
        ~MotionPlanner(); 

        /* ACCESSORS */
        void init_ctrl(uint8_t , double ); 
        void init_ctrl(uint8_t , VectorXd ); 

        /* METHODS */
        Trajectory trajectory() const; 
        StateVector_t inout() const;

    private:
        /* COPY OF MAIN ATTRIBUTES */
        

        /* ATTRIBUTES */
        ODEInt        * ode_integr;
        ControlSystem * sys_;
        StateVector_t target_; 

};

#endif
