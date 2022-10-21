/**
* @file trajectory.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-21
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for Trajectory class
*/

#ifndef CNTRLTLBX_TRAJECTORY_H
#define CNTRLTLBX_TRAJECTORY_H

// Macros definitions

// Additional library
#include <iostream>
#include <Eigen/Dense>
#include "../interpol/interpol.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

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
        Trajectory(VectorXd , MatrixXd ); 
        Trajectory(const Trajectory & ); 

        /* DESTRUCTOR */
        ~Trajectory(); 

        /* ACCESSORS */
        VectorXd get_time() const; 
        MatrixXd get_data() const; 
        void set_interpolation_method(interpolation_method_t , extend_t , extend_t );

        /* METHODS */
        VectorXd evaluate(double ) const; 

        /* OPERATORS */
        friend std::ostream & operator<<(std::ostream & , const Trajectory & );

    private: 
        VectorXd time_;         /*!< Time Vector */
        MatrixXd data_;         /*!< Data Matrix */
        Interpolator1D interp_; /*!< Interpolation strategy */
}; 

#endif
