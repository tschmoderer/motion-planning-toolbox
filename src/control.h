/**
 * @file control.h
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Header file for Control class
 * @version 1.0
 * @date 2021-10-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CONTROL_H
#define CONTROL_H

#include "matrix.h"
#include "vector.hpp"

enum interp_t : uint8_t {
    INTERP_CONSTANT_LEFT, 
    INTERP_CONSTANT_RIGHT, 
    INTERP_NEAREST,
    INTERP_LINEAR
};


/**
 * @class Control
 * @brief A class decribing Control functions. 
 * Controls are described by interpolations points t_i and values u(t_i)
 * Several interpolation methods are implemented to compute u(t) 
 */
class Control {
    public: 
        /* CONSTRUCTORS */
        Control(); 
        Control(uint8_t , double , double , uint8_t );
        Control(const Control & ); 

        /* DESTRUCTOR */
        ~Control(); 

        /* OPERATORS */
        Vector operator()(double) const; 

        Control operator+(const Control & ) const; 
        Control operator-(const Control & ) const; 

        Control & operator=(const Control & ) const; 
        Control & operator+=(const Control & ); 
        Control & operator-=(const Control & ); 

    private: 
        uint8_t m;  /*!< Number of controls */
        double  t0; /*!< Minimum timestep */
        double  t1; /*!< Maximum timestep */ 
        uint8_t N; /*!< Number of timesteps */
        Vector  time; /*!< Array of discrete times */
        Matrix  data; /*!< Value of controls at time step */
        interp_t interp_method = INTERP_LINEAR; /*!< Interpolation methods */

        /* PRIVATE METHODS */
        void construct_discrete_time(); 
        void default_data(); 
        uint8_t locate_time(double ) const; 
        double interp1d(uint8_t , double , uint8_t ) const;
};

#endif