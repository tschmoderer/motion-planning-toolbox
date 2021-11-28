#include "vector.h"

int main(int argc, char * argv[]) {
    int n = 5; 
    Vector v0 = Vector::randn(n);
    Vector v1 = Vector::randn(n, 5, 2); 
    Vector v2 = Vector::randn(n, -12, -3); 

    std::cout << v2; 

    return 0;
}