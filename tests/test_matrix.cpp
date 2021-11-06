#include "matrix.h"
#include "error_code.h"

void test_contructors() {
    Matrix M0; 
    Matrix M1(2,3); 
    Matrix * M2 =  new Matrix(12, 4); 
    delete M2;    
}

void test_accessors() {
    Matrix M(2,7); 
    assert(M.get_n_rows() == 2); 
    assert(M.get_n_cols() == 7); 
}

void test_operators() {

}

void test_methods() {
    Matrix M(2,5); 
    Vector v = Vector::rand(5); 

    Vector w = M*v;
}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 

    return 0; 
}