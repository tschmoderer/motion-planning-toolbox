/**
* @file controls.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.2
* @date 2022-10-17
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CONTROLTLBX_CONTROLS_H
#define CONTROLTLBX_CONTROLS_H

#include "utils.h"
#include "control.h"
#include <vector>

class Controls {
    public: 
        /* CONSTRUCTORS */
        Controls(uint8_t );
        Controls(uint8_t , Control );
        Controls(const Controls & ); 

        /* DESTRUCTOR */
        ~Controls(); 

        /* ACCESSORS */
        void set_t0(double ); 
        void set_t1(double ); 
        void set_N(uint16_t ); 
        void set_discretisation(double , double , uint16_t ); 

        /* OPERATORS */
        friend std::ostream & operator<<(std::ostream & , const Controls & );

    private: 
        uint8_t m;                          /*!< Number of controls */
        std::vector<Control> control_list; /*!< List of controls */
};

#endif
