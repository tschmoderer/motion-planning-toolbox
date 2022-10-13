/**
* @file control.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.1
* @date 2022-10-13
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#include "utils.h"

using Eigen::VectorXd;

class Control {
    public:
        /* CONSTRUCTORS */
        /**
        * @brief Construct a new Control object.
        * Default Constructor
        * By defauly we have the following values : 
        * t0 = 0 ; t1 = 1 ; N = 2
        * data = 0
        * Interpolator linear with constant extension left and right
        */
        Control(); 
        Control(const Control & ); 

        /* DESTRUCTOR */
        ~Control(); 

        /* OPERATORS */
        friend std::ostream & operator<<(std::ostream & , const Control & );


    private: 
        /* ATTRIBUTES */
        double  t0; /*!< Minimum timestep */
        double  t1; /*!< Maximum timestep */ 
        uint16_t N;  /*!< Number of timesteps */

        VectorXd time; /*!< Pointer to array of discrete times */
        VectorXd data; /*!< Pointer to the data of the control at time step */
        //Interpolator1D * interpolator; /*!< Pointer to interpolation method */

        /* PRIVATE METHODS */
        void construct_discrete_time(); 
        void default_data(); 
};
