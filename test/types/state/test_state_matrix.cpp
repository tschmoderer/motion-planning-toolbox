#include "../../../include/header/controltlbx.h"

using namespace std;

void test_constructor() {
    StateMatrix t1;
    StateMatrix t2(5, 93);
    StateMatrix t3 = t2; 
}

void test_accessors() {

}

void test_methods() {

}

void test_operators() {
    StateMatrix t2(5, 93); t2 = StateMatrix::Base::Zero(5, 93); 
    StateVector v1(5);     v1 = StateVector::Base::Random(5); 
    StateMatrix t3(5, 93); t3 = StateMatrix::Base::Random(5, 93); 

    t2.col(34) = v1;

    StateVector v2(93);
    v2 = t2.row(4); 

    t2 = 2*t2 + t3/5.1;
}

int main(int argc, char **argv) {
    test_constructor(); 
    test_accessors();
    test_methods();
    test_operators();

    return 0; 
}