#ifndef LSQ_H
#define LSQ_H

#include "squareMatrix.h"

class LSQ {
    public: 

        /* CONSTRUCTORS */
        LSQ(); 
        LSQ(const LSQ & ); 
        LSQ(const Matrix * , const Vector * ); 

        /* DESTRUCTOR */
        ~LSQ(); 
        
        /* METHODS */
        void solve();
        void solve(double ); 
        double eval(); 

    private: 
        Matrix * A; 
        Vector * b; 
        Vector * x; 

        double lambda; 

        SquareMatrix * AAt;
        SquareMatrix * AtA;
}; 

#endif