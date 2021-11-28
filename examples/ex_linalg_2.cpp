#include <iostream>
#include "linalg.h"

int main(int argc, char * argv[]) {
    int n = 10;
    LTMatrix L = LTMatrix::rand(n); 
    Vector   x = Vector::rand(n);
    Vector   b = L * x;

    Vector sol = solve(L, b);  

    std::cout << (x-sol).norm2()/(x.norm2()) << std::endl;
}