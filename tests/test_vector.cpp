#include "vector.hpp"
#include "error_code.h"

void test_contructors() {
    Vector v0; 
    Vector v1(5); 
    Vector v2 = v1; 
    Vector* v3 = new Vector(7); 
    delete v3; 
}

void test_accessors() {

}

void test_operators() {
    Vector v(5); 
    // Operator ()
    for (int i =0; i < 5; i++) {
        assert(v(i) == 0.);
    }
    // Operator 
}

void test_methods() {

}


int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 

    return 0; 
}