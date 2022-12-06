/**
* @file controls.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CONTROLTLBX_CONTROLS_H
#define CONTROLTLBX_CONTROLS_H

#include "../utils.h"
#include "../types/time/timeVector.h"
#include "../types/control/controlVector.h"
#include "../types/control/controlMatrix.h"
#include "../interpol/interpol.h"
#include "../integrator/integrator1d.h"

enum initialisation_method_t : uint8_t {
    INIT_CNTRLS_FUNCTION, 
    INIT_CNTRLS_CONSTANTS, 
    INIT_CNTRLS_DATA,
    INIT_CNTRLS_RANDOM_UNIFORM, 
    INIT_CNTRLS_RANDOM_NORMAL
};

class Controls {
    public: 
        /* CONSTRUCTORS */
        Controls(CNTRL_VECTOR_DIM_T , Time_t , Time_t , TIME_VECTOR_DIM_T , interpolation_method_t = INTERP_LINEAR, extend_t = EXTEND_ZERO, extend_t = EXTEND_ZERO, TIME_VECTOR_DIM_T = 0);
        Controls(const Controls & ); 

        /* DESTRUCTOR */
        ~Controls(); 

        /* ACCESSORS */
        CNTRL_VECTOR_DIM_T get_nb_cntrl() const;
        ControlVector get_control(CNTRL_VECTOR_DIM_T ) const; 
        TimeVector get_time() const; 
        ControlMatrix get_data() const; 

        void set_t0(Time_t ); 
        void set_t1(Time_t ); 
        void set_H(TIME_VECTOR_DIM_T ); 
        void set_discretisation_cntrls(Time_t , Time_t , TIME_VECTOR_DIM_T ); 

        void set_cntrl(CNTRL_VECTOR_DIM_T , Cntrl_t );
        void set_cntrl(CNTRL_VECTOR_DIM_T , ControlVector );

        void set_interpolation_method(interpolation_method_t , extend_t , extend_t ); 
        void set_integration_method(TIME_VECTOR_DIM_T ); 

        /* METHODS */
        void initialise(initialisation_method_t ); 

        //SCALAR dot_prod_l2(const Controls & ) const;
        //SCALAR norm2() const;

        /* OPERATORS */
        ControlVector operator()(Time_t ) const;

        Controls & operator=(const Controls & );
        Controls & operator+=(const Controls & );
        Controls & operator-=(const Controls & );

        Controls operator-() const;

        friend bool operator==(const Controls & , const Controls & );
        //friend SCALAR operator*(const Controls & , const Controls & );
        friend Controls operator*(const Cntrl_t , const Controls & );
        friend Controls operator*(const Controls & , const Cntrl_t );

        friend Controls operator+(const Controls & , const Controls & );

        friend Controls operator-(const Controls & , const Controls & );

        friend Controls operator/(const Controls & , const Cntrl_t );

        /* STATIC METHODS */
        static Controls random();
        static Controls zeros(); 
        static Controls ones(); 
        //static Controls basis(CNTRL_SIZE_TYPE , uint16_t ); 

    private: 
        CNTRL_VECTOR_DIM_T  M; /*!< Number of controls */
        Time_t   t0;           /*!< Minimum timestep */
        Time_t   t1;           /*!< Maximum timestep */ 
        TIME_VECTOR_DIM_T H;   /*!< Number of discretisation timesteps */

        TimeVector time; /*!< Vector of discrete times : dimension H */
        ControlMatrix data; /*!< Matrix of the data of the control at each time step : dimension (H , M) */

        Interpolator1D interpolator; /*!< Interpolation method */
        //Integrator1D   * integrator;   /*!< Pointer to integration method */

        /* PRIVATE METHODS */
        void construct_discrete_time(); 
        void default_data(); 

        void init_with_funct(std::function<ControlVector(Time_t )> ); 
        void init_with_data(const TimeVector * , const ControlMatrix * );
        void init_with_const(const ControlVector * ); 
        void init_with_rand_u(); 
        void init_with_rand_n(); 
};

#endif
