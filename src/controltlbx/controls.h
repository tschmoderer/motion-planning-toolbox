#ifndef CONTROLTLBX_CONTROLS_H
#define CONTROLTLBX_CONTROLS_H

#include <vector>
#include "utils.h"

class Controls {
    public:
      /* CONSTRUCTORS */
        Controls(); 
        Controls(uint8_t);
        Controls(const Controls & ); 

        /* DESTRUCTOR */
        ~Controls(); 

        /* ACCESSORS */

        /* METHODS */
        Vector get_time() const; 
        Matrix get_data() const; 
        Vector get_data(uint8_t ) const; 
         /* OPERATORS */
        Vector operator()(double) const; 
        Matrix operator()(const Vector & ) const; 

        Control operator+(const Control & ) const; 
        Control operator-(const Control & ) const; 

        Control & operator=(const Control & ) const; 
        Control & operator+=(const Control & ); 
        Control & operator-=(const Control & ); 

        friend std::ostream & operator<<(std::ostream & , const Control & );
        /* OPERATORS */
        Control operator[](uint8_t) const; 

    private: 
        uint8_t m;    /*!< Number of controls */
        std::vector<Control> control_list;
};

#endif