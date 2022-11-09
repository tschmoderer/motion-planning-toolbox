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
    VectorXd x0(3); x0 << 10.0 , 1.0 , 1.0; 
    DynamicalSystem sys(3, 0., 50., x0); 
    sys.set_dynamics(dyn);

    int N = 5000;
    ODEInt odeint(&sys, RK4, N);

    Trajectory T = odeint.integrate();
    cout << T << endl;

    vector<double> XX, YY, ZZ; 
    MatrixXd res = T.get_data();
    for (int i = 0; i < N; i++) {
        XX.push_back(res(i, 0)); 
        YY.push_back(res(i, 1)); 
        ZZ.push_back(res(i, 2)); 
    }
    
    plt::scatter(XX, YY, ZZ);
    plt::title("Integration Lorentz system");
    plt::show();

    return 0;
}