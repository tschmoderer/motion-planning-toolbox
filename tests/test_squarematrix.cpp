#include "squareMatrix.h"
#include "error_code.h"

void test_contructors() {
    SquareMatrix M0; 
    SquareMatrix M1(2); 
    SquareMatrix * M2 =  new SquareMatrix(12); 
    delete M2;    
}

void test_accessors() {
}

void test_operators() {

}

void test_methods() {
    SquareMatrix M1(2); 
    assert(M1.is_square()); 
}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 

    return 0; 
}