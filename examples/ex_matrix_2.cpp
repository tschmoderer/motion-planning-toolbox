#include <iostream>
#include <typeinfo>
#include "squareMatrix.h"

int main(int argc, char * argv[]) {


    SquareMatrix M1 = SquareMatrix::eye(5);
    std::cout << M1 << std::endl; 

    SquareMatrix M2 = M1;
    M2 += M1; M2 -= M1;
    assert(M2 == M1);
    M2 *= 2;
    std::cout << M2 << std::endl; 
    std::cout << typeid(M2).name() << std::endl;

    SquareMatrix M3 = Matrix::rand(5,5); 
    std::cout << M3 << std::endl; 

    return 0;
}