#include <iostream>
#include "matrix.h"

int main(int argc, char * argv[]) {
    Matrix M1(2,3);
    M1.show();

    Matrix M2(5); 
    M2.show();

    Matrix M3 = M1; 
    M3.show();

    Matrix M4 = eye(5);
    M4.show();

    Matrix M5 = 2 * M4 * M4 + M4 + 5; 
    M5.show();

    return 0;
}