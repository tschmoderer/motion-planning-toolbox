/**
* @file dynamicalSystem.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-21
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief A class describig an integrator of ODE
*/

#ifndef CONTROLTLBX_DYNAMICAL_SYSTEM_H
#define CONTROLTLBX_DYNAMICAL_SYSTEM_H

#include "../types/types.h"

class DynamicalSystem {
    public:
        /* CONSTRUCTORS */
        DynamicalSystem(uint16_t ); 
        DynamicalSystem(uint16_t , double , double , State_t ); 

        /* ACCESSORS */
        void set_x0(State_t ); 
        void set_t0(double ); 
        void set_t1(double );

        void set_dynamics(std::function<VectorXd(double , State_t )> );
        void set_dynamics_derivative_x(std::function<MatrixXd(double , State_t )> );

        /* DESTRUCTOR */
        virtual ~DynamicalSystem(); 

        /* ACCESSORS */

        /* METHODS */
        State_t eval_dynamics(double , State_t ) const; 

        /* OPERATORS */

    protected: 
        /* ATTRIBUTES */
        uint16_t N; /*!< State space dimension */

        State_t x0; /*!< Initial state */
        double  t0; /*!< Initial time */
        double  t1; /*!< Final time */

        std::function<VectorXd(double , State_t )> dynamic_func;
        std::function<MatrixXd(double , State_t )> dynamic_func_derivative;

        /* METHODS */

};

#endif
