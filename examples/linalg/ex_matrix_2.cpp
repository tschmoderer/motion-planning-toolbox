#include <iostream>
#include "squareMatrix.h"

int main(int argc, char * argv[]) {

    SquareMatrix M1 = SquareMatrix::eye(5);
    std::cout << M1 << std::endl; 

    SquareMatrix M2 = M1;
    M2 += M1; M2 -= M1;
    assert(M2 == M1);
    std::cout << M2 << std::endl; 

    return 0;
}