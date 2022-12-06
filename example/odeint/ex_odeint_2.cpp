#include "../../include/header/odeint/odeint.h"
#include "matplotlibcpp.h"
#include <iostream>

using namespace std;
namespace plt = matplotlibcpp;

// Example van der Pol equation
const double mu = 1;

StateVector dyn(double t, StateVector x) {
    StateVector dxdt(x.size());
    dxdt(0) = x(1);
    dxdt(1) =mu*(1-x(0)*x(0))*x(1)-x(0);

    return dxdt;
}

int main(int argc, char * argv[]) {
    StateVector x0(2); x0(0) = 2; x0(1) = 0; 
    DynamicalSystem sys(2, 0., 20., x0); 
    sys.set_dynamics(dyn);

    int N = 500;
    ODEInt odeint(&sys, RK4, N);

    Trajectory T = odeint.integrate();
    cout << T << endl;

    vector<double> XX, YY; 
    StateMatrix res = T.get_data();
    for (int i = 0; i < N; i++) {
        XX.push_back(res(i, 0)); 
        YY.push_back(res(i, 1)); 
    }
    
    plt::plot(XX, YY);
    plt::title("Solution of van der Pol Equation (mu = 1) with ODE45");
    plt::show();

    return 0;
}