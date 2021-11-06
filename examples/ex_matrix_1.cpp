#include <iostream>
#include "matrix.h"
#include "squareMatrix.h"

int main(int argc, char * argv[]) {
    Matrix M1(2,3);
    std::cout << M1 << std::endl; 

    Matrix M2(5,5); 
    std::cout << M2 << std::endl; 

    Matrix M3 = M1; 
    std::cout << M3 << std::endl; 

    SquareMatrix M4 = SquareMatrix::eye(5);
    std::cout << M4 << std::endl; 

    /*SquareMatrix M5 = 2 * M4 * M4 + M4 + 5; 
    std::cout << M5 << std::endl; */

    return 0;
}