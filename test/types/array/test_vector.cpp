#include "../../../include/header/controltlbx.h"

using namespace std;

void test_constructor() {
    DataVector * v1 = new DataVector(); 
    assert(v1->check()); 
    delete v1;

    DataVector * v2 = new DataVector(125); 
    assert(v2->check()); 
    delete v2; 

    int n = 5; 
    double arr[n] = {1.,-1.5, 5, M_PI, 6}; 
    DataVector * v3 = new DataVector(n, arr);
    assert(v3->check()); 
    delete v3; 

    Eigen::VectorXd tmp(n); 
    tmp <<  1.,-1.5, 5, M_PI, 6;
    DataVector * v4 = new DataVector(tmp); 
    assert(v4->check()); 
    DataVector * v5 = new DataVector(*v4); 
    assert(v5->check());    
    delete v4; 
    delete v5;
}

void test_accessors() {
    DataVector * v1; 
    for (int i = 0; i <= MAXIMUM_SIZE; i++) {
        v1 = new DataVector(i); 
        assert(v1->check()); 
        assert(v1->get_dim() == i);
        assert(v1->size() == i);
        assert(v1->len() == i);
        delete v1;
    }
}

void test_methods() {
    int n = 129; 
    DataVector v1 = DataVector(n); 

    v1.zeros(); 
    for (int i = 0; i < n; i++) {
        assert(v1(i) == 0); 
    }

    v1.ones(); 
    for (int i = 0; i < n; i++) {
        assert(v1(i) == 1); 
    }

    assert(v1.check()); 
}

void test_operators() {
    int n = 129; 
    DataVector v1 = DataVector(n); 
    v1.zeros();
    int m = 1278; 
    DataVector v2 = DataVector(m); 
    v2.ones();
    v1 = v2;
    assert(v1.get_dim() == m); 
    for (int i = 0; i < m; i++) {
        assert(v1(i) == v2(i)); 
    }
}

int main(int argc, char **argv) {
    test_constructor(); 
    test_accessors();
    test_methods();
    test_operators();

    return 0; 
}