#ifndef LOWER_TRIANGULAR_MATRIX_H
#define LOWER_TRIANGULAR_MATRIX_H

#include "utils.h"
#include "matrix.h"

/**
* @class LTMatrix 
* @brief A class describing a Lower Triangular Matrix. 
* Lower triangular matrix are Matrix of dimension $n\times n$ satisfying
* $$
* L_{ij} = \left\{\begin{array}{rl} 0&\textrm{if}\quad j> i \\ 0 &\textrm{otherwise} \end{array}\right.
* $$
* @todo check that calling operator L(i,j) calls the newt implementation of the at function. 
* @todo Extend the definition to $n\times m$, with $n>m$, matrices.
*/
class LTMatrix : public Matrix {
    public: 
        /* CONSTRUCTORS */
        LTMatrix(); 
        LTMatrix(uint16_t , uint16_t );
        LTMatrix(uint16_t ); 
        LTMatrix(const LTMatrix & ); 

        /* DESTRUCTORS */
        ~LTMatrix();

        /*ACCESSORS */

        /* METHODS */
        uint16_t max_col_from_row(uint16_t ) const; 

        /* OPERATORS */
        double & operator()(uint32_t ) const; 
        double & operator()(uint16_t, uint16_t) const;

        LTMatrix & operator=(const LTMatrix & );

		LTMatrix operator-() const;

        friend LTMatrix operator*(const LTMatrix & , const LTMatrix & ); 
        friend Vector operator*(const LTMatrix & , const Vector & ); 
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
        static LTMatrix rand(uint16_t , uint16_t );
    
    private:
		/* ATTRIBUTES */

		/* METHODS */
		double & at(uint32_t ) const;
		double & at(uint16_t , uint16_t ) const;
		void show() const;
};

#endif