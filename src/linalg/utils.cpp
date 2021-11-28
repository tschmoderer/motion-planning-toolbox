#include "utils.h"

std::random_device rd;
std::mt19937 gen(rd());

/**
* @brief Generate a random number using the uniform distribution. 
* @param a Lower bound of the interval, default $a=0$
* @param b Upper bound of the interval ($b > a$), default $b=1$.
* @return double A random number picked uniformaly between $[a,b)$, 
*/
double uniform_distribution(double a = 0., double b = 1.) {
    std::uniform_real_distribution<double> d(a,b);
    return d(gen);
}

/**
* @brief Generate a random umber using the Gaussian distribution.
* @param m Mean value of the distribution, default $m=0$. 
* @param s Standart deviation of the distribution, default $s=1$. 
* @return double A random number picked following the Gaussian distribution $\mathcal{N}(m,s)$.
*/
double normal_distribution(double m = 0., double s = 1.) {
    std::normal_distribution<double> d(m, s); 
    return d(gen);
}