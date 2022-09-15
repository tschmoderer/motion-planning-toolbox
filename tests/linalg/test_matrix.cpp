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
    Matrix A(2,7); 
    Matrix B(7,4); 

    Matrix C = A * B; 

    A = Matrix(7,2); 
    C = Matrix::matmul(A, TRANSPOSE, B, NO_TRANSPOSE);
}

void test_methods() {
    Matrix M(2,5); 
    Vector v = Vector::rand(5); 

    Vector w = M*v;

    Matrix M2 = Matrix::rand(4,7);
}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 

    return 0; 
}