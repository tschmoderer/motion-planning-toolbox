#include "../../include/header/integrator/integrator.h"

# define M_PI           3.14159265358979323846  /* pi */

double f_sin(double x) {
    return sin(x);
}

double f_cos(double x) {
    return cos(x);
}

double f_3(double x) {
    return 1./(x*x*x - 2*x - 5); 
}

int main(int argc, char * argv[]) {
    srand((unsigned int) time(0));

    uint8_t n = 10;
    double t0 = -1; double t1 = 1;
    VectorXd t = VectorXd::LinSpaced(n, t0, t1);
    VectorXd d = VectorXd::Random(n);

    Integrator1D integrator(512); 

    std::cout << integrator.integr(t, d) << std::endl;

    d = VectorXd::Zero(n);
    std::cout << integrator.integr(t, d) << std::endl;

    d = VectorXd::Ones(n); 
    std::cout << integrator.integr(t, d) << std::endl;


    std::cout << integrator.integr(0, 2*M_PI, f_sin) << std::endl;
    std::cout << integrator.integr(0, 2*M_PI, f_cos) << std::endl;
    std::cout << integrator.integr(0, 2, f_3) << std::endl;

    return 0; 
}