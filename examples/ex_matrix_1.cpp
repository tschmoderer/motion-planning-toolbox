#include <iostream>
#include "matrix.h"

int main(int argc, char * argv[]) {
    Matrix M1(2,3);
    std::cout << M1 << std::endl; 

    Matrix M2(5,5); 
    std::cout << M2 << std::endl; 

    Matrix M3 = M1; 
    std::cout << M3 << std::endl; 

    return 0;
}