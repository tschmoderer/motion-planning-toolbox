/**
* @file controls.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-11-09
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CONTROLTLBX_CONTROLS_H
#define CONTROLTLBX_CONTROLS_H

#include "../utils.h"
#include "../interpol/interpol.h"
#include "../integrator/integrator.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

class Controls {
    public: 
        /* CONSTRUCTORS */
        Controls(uint8_t , double , double , uint16_t , interpolation_method_t , extend_t , extend_t , uint16_t );
        Controls(const Controls & ); 

        /* DESTRUCTOR */
        ~Controls(); 

        /* ACCESSORS */
        uint8_t get_nb_cntrl() const;
        VectorXd get_control(uint8_t ) const; 
        VectorXd get_time() const; 
        MatrixXd get_data() const; 

        void set_t0(double ); 
        void set_t1(double ); 
        void set_H(uint16_t ); 
        void set_discretisation_cntrls(double , double , uint16_t ); 

        void set_cntrl(uint8_t , double );
        void set_cntrl(uint8_t , VectorXd );

        void set_interpolation_method(interpolation_method_t , extend_t , extend_t ); 
        void set_integration_method(uint16_t ); 

        /* METHODS */
        double dot_prod_l2(const Controls & ) const;
        double norm2() const;

        /* OPERATORS */
        VectorXd operator()(double ) const;

        Controls & operator=(const Controls & );
        Controls & operator+=(const Controls & );
        Controls & operator-=(const Controls & );

        Controls operator-() const;

        friend bool operator==(const Controls & , const Controls & );
        friend double operator*(const Controls & , const Controls & );
        friend Controls operator*(const double , const Controls & );
        friend Controls operator*(const Controls & , const double );

        friend Controls operator+(const Controls & , const Controls & );

        friend Controls operator-(const Controls & , const Controls & );

        friend Controls operator/(const Controls & , const double );

        friend std::ostream & operator<<(std::ostream & , const Controls & );

        /* STATIC METHODS */
        static Controls random();
        static Controls zeros(); 
        static Controls ones(); 
        static Controls basis(uint8_t , uint16_t ); 

    private: 
        uint8_t  M;  /*!< Number of controls */
        double   t0; /*!< Minimum timestep */
        double   t1; /*!< Maximum timestep */ 
        uint16_t H;  /*!< Number of discretisation timesteps */

        VectorXd time; /*!< Vector of discrete times : dimension H */
        MatrixXd data; /*!< Matrix of the data of the control at each time step : dimension (H , M) */

        Interpolator1D * interpolator; /*!< Pointer to interpolation method */
        Integrator1D   * integrator;   /*!< Pointer to integration method */

        /* PRIVATE METHODS */
        void construct_discrete_time(); 
        void default_data(); 
};

#endif
