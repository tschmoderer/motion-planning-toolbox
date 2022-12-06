/**
* @file trajectory.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for Trajectory class
*/

#ifndef CNTRLTLBX_TRAJECTORY_H
#define CNTRLTLBX_TRAJECTORY_H

#include "../../interpol/interpol.h"
#include "../../types/state/stateVector.h"
#include "../../types/state/stateMatrix.h"

/**
 * @brief This implements a trajectory based on discrete data points which can be evenly or unevenly
 * distributed in time with time stamps associated with each data point. A basic interpolation
 * strategy can evaluate the trajectory also in between data points.
 * 
 * @warning Interpolation method is set by default to : 
 * Interpolation linear, 
 * Extend data outside of interval by Zeros.
 * To change this behaviour consider accesor set_interpolation_method
 */
class Trajectory {
    public:
        /* CONSTRUCTORS */
        Trajectory(); 
        Trajectory(TimeVector , StateMatrix , interpolation_method_t = INTERP_LINEAR, extend_t = EXTEND_ZERO, extend_t = EXTEND_ZERO);
        Trajectory(const Trajectory & ); 

        /* DESTRUCTOR */
        ~Trajectory(); 

        /* ACCESSORS */
        TimeVector get_time() const; 
        StateMatrix get_data() const; 
        void set_interpolation_method(interpolation_method_t , extend_t , extend_t );

        /* METHODS */
        StateVector evaluate(Time_t ) const; 
        StateVector endpoint() const;

    private: 
        TimeVector  time_; /*!< Time Vector */
        StateMatrix data_; /*!< Data Matrix */
        Interpolator1D interp_; /*!< Interpolation strategy */
}; 

#endif
