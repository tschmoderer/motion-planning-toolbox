/**
 * @file controls.h
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Header file for Controls class
 * @version 1.0
 * @date 2022-09-13
 * @copyright Copyright (c) 2022
 */

#ifndef CONTROLTLBX_CONTROLS_H
#define CONTROLTLBX_CONTROLS_H

#include <vector>
#include "utils.h"

/**
 * @class Controls
 * @brief Class to describe a collection of controls
 * @warning Maximum number of controls is 255
 * @warning All controls must have the same prescribed times for interpolation
 */
class Controls {
    public:
      /* CONSTRUCTORS */
      Controls(); 
      Controls(uint8_t );
      Controls(std::vector<Control> );
      Controls(const Controls & ); 

      /* DESTRUCTOR */
      ~Controls(); 

      /* ACCESSORS */
      void add_control(const Control & ); 

      /* METHODS */
      Vector * get_time() const; 
      Vector * get_data(uint8_t ) const; 
      Matrix get_data() const; 

      /* OPERATORS */
      Control operator[](uint8_t ) const; 
      Vector operator()(double ) const; 
      Matrix operator()(const Vector & ) const; 

      Controls & operator=(const Controls & ); 
      Controls & operator+=(const Controls & ); 
      Controls & operator-=(const Controls & ); 

      friend bool operator==(const Controls & , const Controls & );
      friend Controls operator+(const Controls & , const Controls & ); 
      friend Controls operator-(const Control & , const Controls & ); 
      friend std::ostream & operator<<(std::ostream & , const Controls & );

    private: 
      uint8_t m;    /*!< Number of controls */
      std::vector<Control> control_list;
};

#endif