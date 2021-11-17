#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "matrix.h"

class SquareMatrix : public Matrix {
    public: 
        /* CONSTRUCTORS */
        SquareMatrix(); 
        SquareMatrix(uint16_t ); 
        SquareMatrix(const SquareMatrix & ); 

        /* DESTRUCTORS */
        ~SquareMatrix();

        /*ACCESSORS */

        /* METHODS */

        /* OVERLOAD OPERATORS MATRIX*/
        SquareMatrix & operator=(const SquareMatrix & );

		SquareMatrix operator-() const;

        friend SquareMatrix operator*(const SquareMatrix & , const SquareMatrix & ); 
		friend SquareMatrix operator*(const double , const SquareMatrix & ); 
		friend SquareMatrix operator*(const SquareMatrix & , const double );

		friend SquareMatrix operator+(const SquareMatrix & , const SquareMatrix & ); 
		friend SquareMatrix operator+(const double , const SquareMatrix & ); 
		friend SquareMatrix operator+(const SquareMatrix & , const double );

		friend SquareMatrix operator-(const SquareMatrix & , const SquareMatrix & ); 
		friend SquareMatrix operator-(const SquareMatrix & , const double );
		friend SquareMatrix operator-(const double , const SquareMatrix & ); 
		
		friend SquareMatrix operator/(const SquareMatrix & , const double );

        /* OVERLOAD METHODS MATRIX */
        SquareMatrix transpose() const;

        /* STATIC METHODS */
    	static SquareMatrix eye(uint16_t );
        static SquareMatrix diag(const Vector & ); 
        static Vector diag(const SquareMatrix & );
	    static double tr(const SquareMatrix & );

        /* OVERLOAD STATIC METHODS MATRIX */
        static SquareMatrix zeros(uint16_t ); 
		static SquareMatrix ones(uint16_t ); 
		static SquareMatrix rand(uint16_t );
		static SquareMatrix hilbert(uint16_t ); 
		static SquareMatrix vandermonde(const Vector & );
		static SquareMatrix outer(const Vector & , const Vector & );
		static SquareMatrix matmul(const SquareMatrix & , MATRIX_TRANSPOSE , const SquareMatrix & , MATRIX_TRANSPOSE );

    private:
        
};

#endif