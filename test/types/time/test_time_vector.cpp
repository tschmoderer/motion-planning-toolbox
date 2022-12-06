#include "../../../include/header/controltlbx.h"

using namespace std;

void test_constructor() {
    TimeVector t1;
    TimeVector t2(0,1,5);
    TimeVector * t3 = new TimeVector(-1.5,5, 12); 

    assert(t2.check()); 
    assert(t3->check()); 
    
    TimeVector t4 = t2;

    delete t3; 
}

void test_accessors() {

}

void test_methods() {

}

void test_operators() {
    TIME_VECTOR_DIM_T n = 127; 
    Time_t t0 = 0; Time_t t1 = 1.; 
    TimeVector tspan1(t0, t1, n); 

}

int main(int argc, char **argv) {
    test_constructor(); 
    test_accessors();
    test_methods();
    test_operators();

    return 0; 
}