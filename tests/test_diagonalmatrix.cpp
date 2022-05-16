#include "diagonalMatrix.h"
#include "error_code.h"

void test_contructors() {
    DiagonalMatrix D1;
    DiagonalMatrix D2(4); 
    assert(D2.get_dim() == 4);
    DiagonalMatrix * D3 = new DiagonalMatrix(52);
    delete D3;
}

void test_accessors() {

}

void test_operators() {

}

void test_methods() {
    DiagonalMatrix D1 = Vector::rand(5); 
    assert(tr(D1) == sum(D1));
    assert(det(D1) == prod(D1));
}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 

    return 0; 
}