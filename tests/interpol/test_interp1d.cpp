#include "interpol.h"

void test_contructors() {
    Interpolator1D I1;
    Interpolator1D I2(INTERP_NEAREST, EXTEND_CONSTANT, EXTEND_ZERO);
}

void test_accessors() {

}

void test_operators() {

}

void test_methods() {
    uint8_t n1 = 3;
    double t0 = -1; double t1 = 1;
    double d0 = 2*t0; double d1 = 2*t1;
    Vector t = Vector::linspace(t0, t1, n1);
    Vector d = Vector::linspace(d0, d1, n1);

    std::cout << t << std::endl << std::endl;   
    std::cout << d << std::endl << std::endl;
    
    /* TEST INTERP LINEAR */
    Interpolator1D I1(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO);
    assert(I1.interp1d(&t, &d, t0-1) == 0);
    assert(I1.interp1d(&t, &d, t1+1) == 0);
    assert(I1.interp1d(&t, &d, t0) == d0);
    assert(I1.interp1d(&t, &d, t1) == d1);

    Interpolator1D I2(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_CONSTANT);
    assert(I2.interp1d(&t, &d, t0-1) == d0);
    assert(I2.interp1d(&t, &d, t1+1) == d1);

    Interpolator1D I3(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_CONSTANT);
    assert(I3.interp1d(&t, &d, (t1-t0)/2.) == (d1-d0)/2.);

    uint8_t n2 = 100;
    t = Vector::linspace(t0, t1, n2);
    d = Vector::linspace(d0, d1, n2);

    uint8_t n3 = 225;
    Vector t_tst = Vector::linspace(t0, t1, n3);
    Vector d_tst = Vector::linspace(d0, d1, n3);

    Interpolator1D I4(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_CONSTANT);
    assert(I4.interp1d(&t, &d, (t1-t0)/2.) == (d1-d0)/2.);
    for (int i=0; i < n3; i++) {
        assert(I4.interp1d(&t, &d, t_tst[i]) == d_tst[i]);
    }

    /* TEST INTERP CONSTANT LEFT */
    Interpolator1D I5(INTERP_CONSTANT_LEFT, EXTEND_ZERO, EXTEND_ZERO); 
    assert(I5.interp1d(&t, &d, t0-1) == 0);
    assert(I5.interp1d(&t, &d, t1+1) == 0);
    assert(I5.interp1d(&t, &d, t0) == d0);
    assert(I5.interp1d(&t, &d, t1) == d1);
}


void test_friend_methods() {

}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 
    test_friend_methods();

    return 0; 
}