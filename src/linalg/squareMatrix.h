#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "matrix.h"

class SquareMatrix : public Matrix {
    public: 
        SquareMatrix(uint16_t ); 

        /* METHODS */

        /* OPERATORS */

        /* STATIC METHODS */
    	static SquareMatrix eye(uint16_t );
	    static SquareMatrix zeros(uint16_t );
        static SquareMatrix diag(const Vector & ); 
        static Vector diag(const SquareMatrix & );
	    static double tr(const SquareMatrix & );

    private:
        
};

#endif