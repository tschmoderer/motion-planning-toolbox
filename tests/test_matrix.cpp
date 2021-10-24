#include "matrix.h"
#include "error_code.h"

void test_contructors() {
    Matrix M0; 
    Matrix M1(2,3); 
    Matrix M2(0, 5); // should failed
    Matrix M3(4, 0); //  should failed
    Matrix M4(5); 
    Matrix I3 = eye(3); 
    Matrix Z6 = zeros(6); 

    Matrix * pM = new Matrix(7); 
    delete pM; 
}

void test_accessors() {

}

void test_operators() {

}

int main(int argc, char * argv[]) {
    test_contructors(); 
    
    return 0; 
}