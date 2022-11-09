/**
* @file odeint.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief A class describig an integrator of ODE
*/

#ifndef ODEINT_H
#define ODEINT_H

// Macros definitions

// Additional library
#include <cassert>
#include <cstdint>
#include <Eigen/Dense>

#include "../systems/dynamicalSystem.h"
#include "../types/types.h"

enum odeint_method_t : uint8_t {
    EULER_EXPLICIT, 
    RK4
};

/**
 * @brief A class describing an intergator of an ordinary differential equation of the form 
 * \f[
 * \dot{x} = f(t,x)
 * \f]
 * 
 * @todo Implement other methods
 */
class ODEInt {
    public: 
        /* CONSTRUCTORS */
        ODEInt(DynamicalSystem * , odeint_method_t , uint16_t );
        ODEInt(const ODEInt & ); 

        /* DESTRUCTORS */
        virtual ~ODEInt(); 

        /* ACCESSORS */
        void update_integration_method(odeint_method_t );
        void update_discretisation_length(uint16_t );

        /* METHODS */
        Trajectory integrate() const;

    protected: 
        /* ATTRIBUTES */
        DynamicalSystem * sys;    /*!< Pointer to the dynamical system */
        odeint_method_t ode_meth; /*!< Integration method */
        uint16_t T;               /*!< Number of time steps */
        
        /* METHODS */
        Trajectory rk1() const;
        Trajectory rk4() const;
};

#endif
