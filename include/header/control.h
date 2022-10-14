/**
* @file control.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.1
* @date 2022-10-14
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#include "utils.h"
#include "interpol/interpol.h"
#include "integrator/integrator.h"

using Eigen::VectorXd;

class Control {
    public:
        /* CONSTRUCTORS */
        Control(); 
        Control(double , double , uint16_t , interpolation_method_t , extend_t , extend_t );
        Control(VectorXd , VectorXd , interpolation_method_t , extend_t , extend_t );
        Control(double , double , VectorXd , interpolation_method_t , extend_t , extend_t );
        Control(double , double , uint16_t , std::function<double(double)> * );
        Control(const Control & ); 

        /* DESTRUCTOR */
        ~Control(); 

        /* METHODS */
        double dot_prod_l2(const Control & ) const; 
        double norm2() const;

        /* OPERATORS */
        double & operator()(double ) const;

        Control & operator=(const Control & );
        Control & operator+=(const Control & );
        Control & operator-=(const Control & );

        Control operator-() const;

        friend double operator*(const Control & , const Control & );
        friend Control operator*(const double , const Control & );
        friend Control operator*(const Control & , const double );

        friend Control operator+(const Control & , const Control & );
        friend Control operator+(const double , const Control & );
        friend Control operator+(const Control & , const double );

        friend Control operator-(const Control & , const Control & );
        friend Control operator-(const double , const Control & );
        friend Control operator-(const Control & , const double );

        friend Control operator/(const Control & , const double );

        friend std::ostream & operator<<(std::ostream & , const Control & );

    private: 
        /* ATTRIBUTES */
        double  t0; /*!< Minimum timestep */
        double  t1; /*!< Maximum timestep */ 
        uint16_t N;  /*!< Number of timesteps */

        VectorXd time; /*!< Pointer to array of discrete times */
        VectorXd data; /*!< Pointer to the data of the control at time step */

        std::function<double(double)> * cntrl;

        Interpolator1D * interpolator; /*!< Pointer to interpolation method */
        Integrator1D * integrator;     /*!< Pointer to integration method */

        /* PRIVATE METHODS */
        void construct_discrete_time(); 
        void default_data(); 
        void continue_to_discrete(); 
};
