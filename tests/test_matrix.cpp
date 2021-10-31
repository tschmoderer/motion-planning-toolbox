#include "matrix.h"
#include "error_code.h"

void test_contructors() {
    Matrix M0; 
    Matrix M1(2,3); 
    //Matrix M2(0, 5); // should failed
    //Matrix M3(4, 0); //  should failed
    Matrix M4(5); 
    Matrix I3 = eye(3); 

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                assert(I3(i,j) == 1); 
            } else {
                assert(I3(i,j) == 0);
            }
        }
    }

    Matrix Z6 = zeros(6); 
    /*
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            assert(Z6(i,j) == 0);
        }
    }

    Matrix * pM = new Matrix(7); 
    delete pM; 
    */
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
    Vector v(5); 

    Vector w = M*v;
}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 

    return 0; 
}