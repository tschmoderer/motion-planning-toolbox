/**
* @file integrator1d.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef INTEGRATOR_1D_H
#define INTEGRATOR_1D_H

#include "../utils.h"
#include "../types/time/time.h"
#include "../types/time/timeVector.h"

/**
 * @brief A class to integrate scalar function over time
 * A function can be defined explicitely or via interpolation points
 */
class Integrator1D {
    public:
        /* CONSTRUCTORS */
        Integrator1D(); 
        Integrator1D(TIME_VECTOR_DIM_T ); 
        Integrator1D(const Integrator1D & );

        /* DESTRUCTOR */
        ~Integrator1D();

        /* ACCESSORS */

        /* METHODS */
        SCALAR integr(Time_t , Time_t , std::function<SCALAR(Time_t)> ) const; 
        template<class T>
        SCALAR integr(const TimeVector * t, const T * d) const {
            assert(t->size() == d->size()); 
            SCALAR sum = 0.;
            SCALAR dx  = 0.;

            for (int i = 0; i < t->size()-1; i++) {
                dx = (*t)(i+1)-(*t)(i);
                sum += dx*((*d)(i+1) + (*d)(i));
            }

            return sum/2.;
        }

    private:
        TIME_VECTOR_DIM_T nb_points; /*!< Number of discretisation points */
};

#endif
