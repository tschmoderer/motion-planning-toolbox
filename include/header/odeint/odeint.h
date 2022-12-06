/**
* @file odeint.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief A class describig an integrator of ODE
*/

#ifndef ODEINT_H
#define ODEINT_H

// Macros definitions

// Additional library
#include "../systems/dynamicalSystem.h"
#include "../types/types.h"

enum odeint_method_t : uint8_t {
    EULER_EXPLICIT, 
    RK1 = EULER_EXPLICIT,
    RK4
};

/**
 * @brief A class describing an integrator of an ordinary differential equation of the form 
 * \f[
 * \dot{x} = f(t,x)
 * \f]
 * 
 * @todo Implement other methods
 */
class ODEInt {
    public: 
        /* CONSTRUCTORS */
        ODEInt(DynamicalSystem * , odeint_method_t , TimeVector );
        ODEInt(const ODEInt & ); 

        /* DESTRUCTORS */
        virtual ~ODEInt(); 

        /* ACCESSORS */

        /* METHODS */
        Trajectory integrate() const;

    protected: 
        /* ATTRIBUTES */
        DynamicalSystem * sys;     /*!< Pointer to the dynamical system */
        odeint_method_t ode_meth;  /*!< Integration method */
        TimeVector      tspan;     /*!< Number of time steps */
        
        /* METHODS */
        Trajectory rk1() const;
        Trajectory rk4() const;
};

#endif
