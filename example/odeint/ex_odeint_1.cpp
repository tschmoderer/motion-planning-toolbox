#include "../../include/header/odeint/odeint.h"
#include "matplotlibcpp.h"
#include <iostream>

using namespace std;
namespace plt = matplotlibcpp;

// Example Lorentz system 

const double sigma = 10.0;
const double R = 28.0;
const double b = 8.0 / 3.0;

VectorXd dyn(double t, VectorXd x) {
    VectorXd dxdt(x.size());
    dxdt(0) = sigma * ( x(1) - x(0) );
    dxdt(1) = R * x(0) - x(1) - x(0) * x(2);
    dxdt(2) = -b * x(2) + x(0) * x(1);

    return dxdt;
}

int main(int argc, char * argv[]) {
    VectorXd x0(3); 
    int N = 2500;
    ODEInt odeint(RK4, N); 
    MatrixXd res;
    x0 << 10.0 , 1.0 , 1.0; 
    res = odeint.ode_int(0., 25., x0, dyn);
    
    for (int i = 0; i < N; i++) {
        cout << res(i, 0) << '\t' << res(i, 1) << '\t' << res(i, 2) << '\t' << res(i, 3) << endl;
    }

    std::vector<double> XX, YY, ZZ; 
    for (int i = 0; i < N; i++) {
        XX.push_back(res(i, 1)); 
        YY.push_back(res(i, 2)); 
        ZZ.push_back(res(i, 3)); 
    }
    
    plt::scatter(XX, YY, ZZ);
    plt::title("Integration Lorentz system");
    plt::show();
    
    return 0;
}