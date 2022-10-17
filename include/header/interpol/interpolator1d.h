/**
* @file interpolator1d.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.2
* @date 2022-10-17
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef INTERPOLATOR_1D_H
#define INTERPOLATOR_1D_H

#include "interpolator.h"

using Eigen::VectorXd;

/**
 * @brief Enumeration for the different types of extensions possible 
 * When interpolated tume is outside of the prescribed times interval then 
 * either we return 0
 * or we return the same value as the data at the nearest border of the nterval
 */
enum extend_t : uint8_t {
    EXTEND_ZERO,
    EXTEND_CONSTANT 
};

/**
 * @class Interpolator1D
 * @brief Class describing a 1D interpolation operator 
 * etend from the general Interpolator class
 */
class Interpolator1D : public Interpolator {
    public: 
        /* CONSTRUCTORS */
        Interpolator1D(); 
        Interpolator1D(interpolation_method_t , extend_t , extend_t);

        /* DESTRUCTOR */
        ~Interpolator1D();

        /* ACCESSORS */
        void set_exleft(extend_t ); 
        void set_exright(extend_t );

        extend_t get_exleft() const;
        extend_t get_exright() const;

        /* METHODS */
        double interp1d(const VectorXd * , const VectorXd * , double ) const;

    private: 
        /* ATTRIBUTES */
        extend_t extend_left_method;  /*!< Method for interpolating left from the interval of prescribed times. */
        extend_t extend_right_method; /*!< Method for interpolating right from the interval of prescribed times. */

        /* METHODS */
        double interp1d_linear(const VectorXd * , const VectorXd * , double , uint16_t ) const;
        double interp1d_nearest(const VectorXd * , const VectorXd * , double , uint16_t ) const;
        double interp1d_constant_left(const VectorXd * , const VectorXd * , double , uint16_t ) const;
        double interp1d_constant_right(const VectorXd * , const VectorXd * , double , uint16_t ) const;

        double interp1D_extend_left(const VectorXd * , const VectorXd *, double ) const;
        double interp1D_extend_right(const VectorXd * , const VectorXd *, double ) const;
};

#endif
