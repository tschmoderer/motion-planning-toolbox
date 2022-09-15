/**
* @file control.h
* @author T. Schmoderer (iathena@mailo.com)
* @brief Header file for Control class
* @version 1.0
* @date 2021-10-27
* 
* @copyright Copyright (c) 2021
*/

#ifndef CONTROLTLBX_CONTROL_H
#define CONTROLTLBX_CONTROL_H

#include "matrix.h"
#include "vector.h"
#include "interpol.h"

/**
 * @class Control
 * @brief A class decribing a single control function. 
 * A control is described by interpolations points t_i and values u(t_i)
 * Several interpolation methods are implemented to compute u(t) 
 */
class Control {
    public: 
        /* CONSTRUCTORS */
        Control(); 
        Control(double , double , uint16_t , interpolation_method_t , extend_t , extend_t );
        Control(Vector * , Vector * , interpolation_method_t , extend_t , extend_t );
        Control(double , double , Vector * , interpolation_method_t , extend_t , extend_t );
        Control(const Control & ); 

        /* DESTRUCTOR */
        ~Control(); 

        /* ACCESSORS */
        Vector * get_time() const; 
        Vector * get_data() const; 

        void set_t0(double ); 
        void set_t1(double ); 
        void set_N(uint16_t ); 

        bool set_data(double , double ); 
        void set_data(const Vector & ); 

        void set_interp_method(interpolation_method_t );
        void set_interp_method(interpolation_method_t , extend_t , extend_t );

        /* METHODS */

        /* OPERATORS */
        double operator()(double) const; 
        Vector operator()(const Vector & ) const; 

        friend bool operator==(const Control & , const Control & );
        friend Control operator+(const Control & , const Control & ); 
        friend Control operator-(const Control & , const Control & ); 

        Control & operator=(const Control & ); 
        Control & operator+=(const Control & ); 
        Control & operator-=(const Control & ); 

        friend std::ostream & operator<<(std::ostream & , const Control & );

    private: 
        /* ATTRIBUTES */
        double  t0; /*!< Minimum timestep */
        double  t1; /*!< Maximum timestep */ 
        uint16_t N;  /*!< Number of timesteps */

        Vector * time; /*!< Pointer to array of discrete times */
        Vector * data; /*!< Pointer to the data of the control at time step */
        Interpolator1D * interpolator; /*!< Pointer to interpolation method */

        /* PRIVATE METHODS */
        void construct_discrete_time(); 
        void default_data(); 
};

#endif