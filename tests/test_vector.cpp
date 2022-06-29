#include "vector.h"
#include "error_code.h"

void test_contructors() {
    Vector v0; 
    Vector v1(5); 
    Vector v2 = v1; 
    Vector* v3 = new Vector(7); 
    delete v3; 
}

void test_accessors() {
    Vector v0; 
    assert(v0.get_dim() == 0); 

    Vector v1(12); 
    assert(v1.get_dim() == 12); 
}

void test_operators() {
    Vector v(5); 
    // Operator ()
    for (int i = 0; i < 5; i++) {
        assert(v[i] == 0.);
    }
    v[2] = 1.2; 

    // Operator 
    uint16_t N = 14;
    v = Vector::rand(N); 
    Vector tmp = v; 
    v = -1+2*v; 
    for (int i = 0; i < N; i++) {
        assert(v[i] == 2*tmp[i] - 1);
    }

    Vector w = Vector::rand(N); 
    double dot = v*w;
}

void test_methods() {

    /* non member methods */
    Vector v1 = Vector::basis(5, 0); 
    assert(v1[0] == 1.); 
    for (int i = 1; i < 5; i++) {
        assert(v1[i] == 0.);
    }

    Vector v2 = Vector::zeros(9); 
    for (int i = 0; i < 9; i++) {
        assert(v2[i] == 0.); 
    }

    Vector v3 = Vector::rand(12); 

    Vector v4 = Vector::ones(100); 
    for (int i = 0; i < 100; i++) {
        assert(v4[i] == 1.); 
    }

    double t0 = 0; double t1 = 1; int N = 257; // use 2^p+1 to get maximum precision of division. 
    Vector v5 = Vector::linspace(t0, t1, N); 
    for (int i = 0; i < N; i++) {
        assert(v5[i] == t0+i*(t1-t0)/(N-1)); 
        if (i < N-2) {
            assert((v5[i+2] - v5[i+1]) == (v5[i+1] - v5[i]) );
        }
    }

    Vector v6 = Vector::rand(N);
    v6.sort(); 
    for (int i = 0; i < N-1; i++) {
        assert(v6(i) <= v6(i+1));
    }
}

void test_friend_methods() {
    Vector v0 = Vector::rand(12); 
    Vector v1 = abs(v0);
    Vector v2 = sqrt(pow2(v0));
    for (int i = 0; i < 12; i++) {
        assert(v1[i] >= 0); 
        assert(v1[i] == v2[i]);
    }
    assert(abs(v1) == v1); 
    assert(pow2(v1) == prod(v1,v1)); 
}


int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 
    test_friend_methods();

    return 0; 
}