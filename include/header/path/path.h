/**
* @file path.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-20
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Header file for Pat class
*/

#ifndef PATH_H
#define PATH_H

#include <Eigen/Dense>

using Eigen::VectorXd;

/**
 * @brief Class describing a path between to points. 
 * By default, the path is a straigt line, but an arbirary path can be set via the use of functions. 
 * 
 * @warning Path is defined on \f$[0,1]\f$.
 * @todo generalise for path defined on general intervals
 * @todo Implement finite differences differentiation if derivative is not provided
 */
class Path {
    public: 
        /* CONSTRUCTORS */
        Path(VectorXd , VectorXd ); 

        /* DESTRUCTOR */
        ~Path(); 

        /* ACCESSORS */
        void set_path(std::function<VectorXd(double )> );
        void set_derivative_path(std::function<VectorXd(double )> );

        /* METHODS */
        VectorXd evaluate(double ) const;
        VectorXd evaluate_derivative(double ) const; 

        /* OPERATOR */

    private: 
        /* ATTRIBUTES */
        double t0 = 0.;
        double t1 = 1.;

        VectorXd start_p;
        VectorXd end_p; 
        
        std::function<VectorXd(double )> path;
        std::function<VectorXd(double )> d_path;
};

#endif