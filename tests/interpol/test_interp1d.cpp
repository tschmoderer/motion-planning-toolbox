#include "interpol.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

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

void test_with_plots() {
    uint8_t n = 10;
    double t0 = -1; double t1 = 1;
    Vector t = Vector::linspace(t0, t1, n);
    Vector d = Vector::rand(n);

    int n_tst = 225;
    Vector t_tst = Vector::linspace(t0-1, t1+1, n_tst);

    Interpolator1D I1(INTERP_CONSTANT_LEFT, EXTEND_ZERO, EXTEND_ZERO);
    Interpolator1D I2(INTERP_CONSTANT_LEFT, EXTEND_CONSTANT, EXTEND_ZERO);
    Interpolator1D I3(INTERP_CONSTANT_LEFT, EXTEND_ZERO, EXTEND_CONSTANT);
    Interpolator1D I4(INTERP_CONSTANT_LEFT, EXTEND_CONSTANT, EXTEND_CONSTANT);

    // Prepare data.
    std::vector<double> x(n), y(n);
    for(int i=0; i<n; ++i) {
        x.at(i) = t[i];
        y.at(i) = d[i];
    }
    std::vector<double> x_tst(n_tst), y_tst(n_tst);
    
    // Interpolation CONSTANT LEFT
    
    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I1.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I1
    plt::title("I1(INTERP_CONSTANT_LEFT, EXTEND_ZERO, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I2.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I2
    plt::title("I2(INTERP_CONSTANT_LEFT, EXTEND_CONSTANT, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I3.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I3
    plt::title("I3(INTERP_CONSTANT_LEFT, EXTEND_ZERO, EXTEND_CONSTANT)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I4.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I4
    plt::title("I4(INTERP_CONSTANT_LEFT, EXTEND_CONSTANT, EXTEND_CONSTANT)");
    plt::show();

    I1.set_method(INTERP_CONSTANT_RIGHT);
    I2.set_method(INTERP_CONSTANT_RIGHT);
    I3.set_method(INTERP_CONSTANT_RIGHT);
    I4.set_method(INTERP_CONSTANT_RIGHT);
    
    // Interpolation CONSTANT RIGHT
    
    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I1.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I1
    plt::title("I1(INTERP_CONSTANT_RIGHT, EXTEND_ZERO, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I2.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I2
    plt::title("I2(INTERP_CONSTANT_RIGHT, EXTEND_CONSTANT, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I3.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I3
    plt::title("I3(INTERP_CONSTANT_RIGHT, EXTEND_ZERO, EXTEND_CONSTANT)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I4.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I4
    plt::title("I4(INTERP_CONSTANT_RIGHT, EXTEND_CONSTANT, EXTEND_CONSTANT)");
    plt::show();
    
    I1.set_method(INTERP_NEAREST);
    I2.set_method(INTERP_NEAREST);
    I3.set_method(INTERP_NEAREST);
    I4.set_method(INTERP_NEAREST);

    // Interpolation NEAREST
    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I1.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I1
    plt::title("I1(INTERP_NEAREST, EXTEND_ZERO, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I2.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I2
    plt::title("I2(INTERP_NEAREST, EXTEND_CONSTANT, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I3.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I3
    plt::title("I3(INTERP_NEAREST, EXTEND_ZERO, EXTEND_CONSTANT)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I4.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I4
    plt::title("I4(INTERP_NEAREST, EXTEND_CONSTANT, EXTEND_CONSTANT)");
    plt::show();

    I1.set_method(INTERP_LINEAR);
    I2.set_method(INTERP_LINEAR);
    I3.set_method(INTERP_LINEAR);
    I4.set_method(INTERP_LINEAR);

    // Interpolation LINEAR
    
    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I1.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I1
    plt::title("I1(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I2.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I2
    plt::title("I2(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_ZERO)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I3.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I3
    plt::title("I3(INTERP_LINEAR, EXTEND_ZERO, EXTEND_CONSTANT)");
    plt::show();

    for(int i=0; i<n_tst; ++i) {
        x_tst.at(i) = t_tst[i];
        y_tst.at(i) = I4.interp1d(&t, &d, t_tst[i]);
    }
    plt::figure_size(1200, 780);
    plt::plot(x, y, "o"); // DATA
    plt::plot(x_tst, y_tst, ".r"); // I4
    plt::title("I4(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_CONSTANT)");
    plt::show();
    
}

void test_friend_methods() {

}

int main(int argc, char * argv[]) {
    test_contructors(); 
    test_accessors();
    test_operators(); 
    test_methods(); 
    test_friend_methods();
//    test_with_plots();

    return 0; 
}