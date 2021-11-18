#ifndef LOWER_TRIANGULAR_MATRIX_H
#define LOWER_TRIANGULAR_MATRIX_H

#include "matrix.h"

/**
* @class LTMatrix 
* @brief A class describing a Lower Triangular Matrix. 
* Lower triangular matrix are Matrix of dimension $n\times m$ satisfying
* $$
* L_{ij} = \left\{\begin{array}{rl} 0&\textrm{if}\quad j> i \\ 0 &\textrm{otherwise} \end{array}\right.
* $$
* @todo check that calling operator L(i,j) calls the newt implementation of the at function. 
*/
class LTMatrix : public Matrix {
    public: 
        /* CONSTRUCTORS */
        LTMatrix(); 
        // TODO: LTMatrix(uint16_t , uint16_t );
        LTMatrix(uint16_t ); 
        LTMatrix(const LTMatrix & ); 

        /* DESTRUCTORS */
        ~LTMatrix();

        /*ACCESSORS */

        /* METHODS */

        /* OVERLOAD OPERATORS MATRIX*/
        LTMatrix & operator=(const LTMatrix & );

		LTMatrix operator-() const;

        friend LTMatrix operator*(const LTMatrix & , const LTMatrix & ); 
		friend LTMatrix operator*(const double , const LTMatrix & ); 
		friend LTMatrix operator*(const LTMatrix & , const double );

		friend LTMatrix operator+(const LTMatrix & , const LTMatrix & ); 
		friend LTMatrix operator+(const double , const LTMatrix & ); 
		friend LTMatrix operator+(const LTMatrix & , const double );

		friend LTMatrix operator-(const LTMatrix & , const LTMatrix & ); 
		friend LTMatrix operator-(const LTMatrix & , const double );
		friend LTMatrix operator-(const double , const LTMatrix & ); 
		
		friend LTMatrix operator/(const LTMatrix & , const double );

        friend std::ostream & operator<<(std::ostream & , const LTMatrix & );

        /* OVERLOAD METHODS MATRIX */

        /* STATIC METHODS */
	    static double tr(const LTMatrix & );
        static double det(const LTMatrix & );

        /* OVERLOAD STATIC METHODS MATRIX */
        static LTMatrix zeros(uint16_t ); 
		static LTMatrix ones(uint16_t ); 
		static LTMatrix rand(uint16_t );
    
    private:
		/* METHODS */
        double & at(uint16_t , uint16_t ) const;
        void show() const;


};

#endif