/**
* @file integrator1d.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-19
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef INTEGRATOR_1D_H
#define INTEGRATOR_1D_H

#include "utils.h"

using Eigen::VectorXd;

class Integrator1D {
    public:
        /* CONSTRUCTORS */
        Integrator1D(); 
        Integrator1D(uint16_t ); 
        Integrator1D(const Integrator1D & );

        /* DESTRUCTOR */
        ~Integrator1D();

        /* ACCESSORS */

        /* METHODS */
        double integr(double , double , std::function<double(double)> ) const; 
        double integr(VectorXd , VectorXd ) const; 

    private:
        uint16_t nb_points; /*!< Number of discretisation points */
};

#endif
