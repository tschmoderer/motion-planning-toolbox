#include "interpol.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void ex_with_plots_interp_constant_left() {
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
    std::vector<double> x_tst(n_tst), y_tst(n_tst);

    for(int i=0; i<n; ++i) {
        x.at(i) = t[i];
        y.at(i) = d[i];
    }
    
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

}

void ex_with_plots_interp_constant_right() {
    uint8_t n = 10;
    double t0 = -1; double t1 = 1;
    Vector t = Vector::linspace(t0, t1, n);
    Vector d = Vector::rand(n);

    int n_tst = 225;
    Vector t_tst = Vector::linspace(t0-1, t1+1, n_tst);

    Interpolator1D I1(INTERP_CONSTANT_RIGHT, EXTEND_ZERO, EXTEND_ZERO);
    Interpolator1D I2(INTERP_CONSTANT_RIGHT, EXTEND_CONSTANT, EXTEND_ZERO);
    Interpolator1D I3(INTERP_CONSTANT_RIGHT, EXTEND_ZERO, EXTEND_CONSTANT);
    Interpolator1D I4(INTERP_CONSTANT_RIGHT, EXTEND_CONSTANT, EXTEND_CONSTANT);

    // Prepare data.
    std::vector<double> x(n), y(n);
    std::vector<double> x_tst(n_tst), y_tst(n_tst);
    
    for(int i=0; i<n; ++i) {
        x.at(i) = t[i];
        y.at(i) = d[i];
    }
    
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
}

void ex_with_plots_interp_nearest() {
    uint8_t n = 10;
    double t0 = -1; double t1 = 1;
    Vector t = Vector::linspace(t0, t1, n);
    Vector d = Vector::rand(n);

    int n_tst = 225;
    Vector t_tst = Vector::linspace(t0-1, t1+1, n_tst);

    Interpolator1D I1(INTERP_NEAREST, EXTEND_ZERO, EXTEND_ZERO);
    Interpolator1D I2(INTERP_NEAREST, EXTEND_CONSTANT, EXTEND_ZERO);
    Interpolator1D I3(INTERP_NEAREST, EXTEND_ZERO, EXTEND_CONSTANT);
    Interpolator1D I4(INTERP_NEAREST, EXTEND_CONSTANT, EXTEND_CONSTANT);

    // Prepare data.
    std::vector<double> x(n), y(n);
    std::vector<double> x_tst(n_tst), y_tst(n_tst);
    
    for(int i=0; i<n; ++i) {
        x.at(i) = t[i];
        y.at(i) = d[i];
    }

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
}

void ex_with_plots_interp_linear() {
    uint8_t n = 10;
    double t0 = -1; double t1 = 1;
    Vector t = Vector::linspace(t0, t1, n);
    Vector d = Vector::rand(n);

    int n_tst = 225;
    Vector t_tst = Vector::linspace(t0-1, t1+1, n_tst);

    Interpolator1D I1(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO);
    Interpolator1D I2(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_ZERO);
    Interpolator1D I3(INTERP_LINEAR, EXTEND_ZERO, EXTEND_CONSTANT);
    Interpolator1D I4(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_CONSTANT);

    // Prepare data.
    std::vector<double> x(n), y(n);
    std::vector<double> x_tst(n_tst), y_tst(n_tst);
    
    for(int i=0; i<n; ++i) {
        x.at(i) = t[i];
        y.at(i) = d[i];
    }

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


int main(int argc, char * argv[]) {
    ex_with_plots_interp_constant_left();
    ex_with_plots_interp_constant_right(); 
    ex_with_plots_interp_nearest(); 
    ex_with_plots_interp_linear();

    return 0; 
}