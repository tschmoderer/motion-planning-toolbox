#include "../include/header/control.h"

/**
* @brief Construct a new Control object.
* Default Constructor
* By defauly we have the following values : 
* t0 = 0 ; t1 = 1 ; N = 2
* data = 0
* Interpolator linear with constant extension left and right
* Integrator is trapezoid on data
*/
Control::Control() {
    this->t0 = 0.; 
    this->t1 = 1.; 
    this->N  = 2; 

    this->time = VectorXd(this->N); 
    this->data = VectorXd(this->N);
    this->cntrl = NULL;

    this->interpolator = new Interpolator1D();
    this->integrator   = new Integrator1D(this->N);

    this->construct_discrete_time();
    this->default_data(); 
}

Control::Control(double a, double b, uint16_t n, interpolation_method_t im, extend_t el, extend_t er) {
    this->t0 = a; 
    this->t1 = b; 
    this->N  = n; 

    this->time = VectorXd(this->N); 
    this->data = VectorXd(this->N);
    this->cntrl = NULL;

    this->interpolator = new Interpolator1D(im, el, er);
    this->integrator   = new Integrator1D(n);

    this->construct_discrete_time();
    this->default_data(); 
}

Control::Control(VectorXd t, VectorXd d, interpolation_method_t im, extend_t el, extend_t er) {
    this->t0 = t(0);
    this->t1 = t(t.size());
    this->N  = t.size();

    this->time = t; 
    this->data = d; 
    this->cntrl = NULL;

    this->interpolator = new Interpolator1D(im, el, er);
    this->integrator   = new Integrator1D(this->N);
}

Control::Control(double a, double b, VectorXd d, interpolation_method_t im, extend_t el, extend_t er) {
    this->t0 = a; 
    this->t1 = b; 
    this->N  = d.size(); 

    this->time = VectorXd(this->N); 
    this->data = d;
    this->cntrl = NULL; 

    this->interpolator = new Interpolator1D(im, el, er);
    this->integrator   = new Integrator1D(this->N);

    this->construct_discrete_time();
}

Control::Control(double a, double b, uint16_t n, std::function<double(double)> * f) {
    this->t0 = a; 
    this->t1 = b; 
    this->N  = n; 

    this->time = VectorXd(this->N); 
    this->data = VectorXd(this->N);
    this->cntrl = f; 

    this->interpolator = new Interpolator1D();
    this->integrator   = new Integrator1D(this->N);

    this->construct_discrete_time();
    this->continue_to_discrete();
}

Control::Control(const Control & c) {
    this->t0 = c.t0; 
    this->t1 = c.t1; 
    this->N  = c.N; 

    this->time  = c.time; 
    this->data  = c.data;
    this->cntrl = c.cntrl; 

    this->interpolator = new Interpolator1D(*c.interpolator);
    this->integrator   = new Integrator1D(*c.integrator);
}

/**
 * @brief Destroy the Control:: Control object
 * 
 */
Control::~Control() {
    delete this->integrator;
    delete this->interpolator;
}

void Control::set_t0(double t0) {
    assert(t0 < this->t1); 
    this->t0 = t0; 
    this->construct_discrete_time(); 
    this->default_data();
}

void Control::set_t1(double t1) {
    assert(t1 > this->t0); 
    this->t1 = t1; 
    this->construct_discrete_time();
    this->default_data();
}

void Control::set_N(uint16_t N) {
    assert(N > 1); 
    this->N = N; 
    this->time = VectorXd(N); 
    this->data = VectorXd(N); 
    this->construct_discrete_time();  
    this->default_data();
}

void Control::set_discretisation(double t0, double t1, uint16_t N) {
    assert(t1 > t0); 
    assert(N > 1); 

    this->t0 = t0; 
    this->t1 = t1; 
    this->N = N; 

    this->time = VectorXd(N); 
    this->data = VectorXd(N); 

    this->construct_discrete_time();  
    this->default_data();
}

/* METHODS */
double Control::dot_prod_l2(const Control & rhs) const {
    return  this->integrator->integr(this->time, this->data * rhs.data); 
}

double Control::norm2() const {
    return this->integrator->integr(this->time, this->data * this->data); ;
}

/* OPERATORS */
double Control::operator()(double t) const {
    return this->interpolator->interp1d(&this->time, &this->data, t);
}

/**
 * @brief Overload the assignement operator. 
 * Acts like a copy constructor.
 * @param c The control to be copied. 
 * @return Control& A copy of vector v. 
 */
Control & Control::operator=(const Control & c) {
    if (c == *this) {
        return *this;
    }

    this->t0 = c.t0;
    this->t1 = c.t1;
    this->N  = c.N;

    this->time = c.time; 
    this->data = c.data; 
    this->cntrl = c.cntrl; 

    delete this->interpolator; 
    delete this->integrator; 

    this->interpolator = new Interpolator1D(*c.interpolator);
    this->integrator   = new Integrator1D(*c.integrator);

    return *this; 
}

Control & Control::operator+=(const Control & c) {
    assert(this->t0 == c.t0); 
    assert(this->t1 == c.t1);
    assert(this->N == c.N);
    for (int i = 0; i < this->N; i++) {
        assert(this->time(i) == c.time(i));
    }

    this->data += c.data;

    return *this; 
}

Control & Control::operator-=(const Control & c) {
    assert(this->t0 == c.t0); 
    assert(this->t1 == c.t1);
    assert(this->N == c.N);
    for (int i = 0; i < this->N; i++) {
        assert(this->time(i) == c.time(i));
    }

    this->data -= c.data;
    return *this; 
}

Control Control::operator-() const {
    Control res(*this);
    res.data = -res.data; 
    return res; 
}

bool operator==(const Control & lhs, const Control & rhs) {
    if ((lhs.t0 != rhs.t0) || (lhs.t1 != rhs.t1) || (lhs.N != rhs.N)) {
        return false; 
    }
    for (int i = 0; i < lhs.N; i++) {
        if ((lhs.time(i) != rhs.time(i)) || (lhs.data(i) != rhs.data(i)) ){
            return false; 
        }
    }
    return true; 
}

/**
 * @brief \f$L^2\f$ dot product between two control functions
 * 
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return double 
 * @warning Both controls must have the same interpolating points
 */
double operator*(const Control & lhs, const Control & rhs) {
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.N == rhs.N); 
    for (int i = 0; i < lhs.N; i++) {
        assert(lhs.time(i) == rhs.time(i));
    }
    return lhs.dot_prod_l2(rhs); 
}

/**
 * @brief Operator, multiplication of a control object by a scalar
 * 
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return double Control whose data are d*c.data(i)
 */
Control operator*(const double d, const Control & rhs) {
    Control res(rhs); 
    res.data = d*res.data; 
    return res; 
}

/**
 * @brief Operator, multiplication of a control object by a scalar
 * 
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return double Control whose data are d*c.data(i)
 */
Control operator*(const Control & lhs, const double d) {
    Control res(lhs); 
    res.data = d*res.data; 
    return res; 
}

/**
 * @brief Addition of two controls
 * 
 * @param lhs  Left hand side
 * @param rhs  Right hand side
 * @return Control 
 */
Control operator+(const Control & lhs, const Control & rhs) {
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.N == rhs.N); 
    for (int i = 0; i < lhs.N; i++) {
        assert(lhs.time(i) == rhs.time(i));
    }
    Control res(lhs); 
    res.data += rhs.data; 
    return res; 
}

/**
* @brief Operator of addition of a Control object with a scalar.
* 
* @param d Double value added to rhs
* @param c Control to be additioned
* @return Control whose data are rhs.data[i] + d
*/
Control operator+(const double d, const Control & rhs) {
    Control res(rhs); 
    for (int i = 0; i < res.N; i++) {
        res.data(i) = d + res.data(i); 
    }
    return res;
}

/**
* @brief Operator of addition of a Control object with a scalar.
* 
* @param d Double value added to lhs
* @param c Control to be additioned
* @return Control whose data are lhs.data[i] + d
*/
Control operator+(const Control & lhs, const double d) {
    Control res(lhs); 
    for (int i = 0; i < res.N; i++) {
        res.data(i) = res.data(i) + d; 
    }   
    return res;
}

/**
 * @brief Substraction of two controls
 * 
 * @param lhs  Left hand side
 * @param rhs  Right hand side
 * @return Control 
 */
Control operator-(const Control & lhs, const Control & rhs) {
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.N == rhs.N); 
    for (int i = 0; i < lhs.N; i++) {
        assert(lhs.time(i) == rhs.time(i));
    }
    Control res(lhs); 
    res.data -= rhs.data; 
    return res; 
}

/**
* @brief Operator of substraction of a Control object with a scalar.
* 
* @param d Double value added to rhs
* @param c Control to be additioned
* @return Control whose data are d - rhs.data[i] 
*/
Control operator-(const double d, const Control & rhs) {
    Control res(rhs); 
    for (int i = 0; i < res.N; i++) {
        res.data(i) = d - res.data(i); 
    } 
    return res;
}

/**
* @brief Operator of substraction of a Control object with a scalar.
* 
* @param d Double value added to lhs
* @param c Control to be additioned
* @return Control whose data are lhs.data[i] - d
*/
Control operator-(const Control & lhs, const double d) {
    Control res(lhs); 
    for (int i = 0; i < res.N; i++) {
        res.data(i) = res.data(i) - d; 
    } 
    return res;
}

/**
* @brief Operator of division of a Control object with a scalar.
* 
* @param d Double value added to lhs
* @param c Control to be additioned
* @return Control whose data are lhs.data[i] - d
*/
Control operator/(const Control & lhs, const double d) {
    assert(d != 0); 
    Control res(lhs); 
    res.data = res.data / (1. * d); 
    return res;
}

/**
* @brief Overload output stream operator for Control object
* @param os Output stream.
* @param c  Control object.
* @return std::ostream & updated output stream
*/
std::ostream & operator<<(std::ostream & os, const Control & c) {
    for (int i = 0; i < c.N; i++) {
        os << c.time[i] << "\t"; 
        os << c.data[i] << std::endl; 
    }
    return os; 
}

void Control::construct_discrete_time() {
    assert(this->t0 < this->t1); 
    assert(this->N >= 2); 

    this->time = VectorXd::LinSpaced(this->N, this->t0, this->t1);
    assert(this->time(0) == this->t0); 
    //assert(this->time[this->time->get_dim()] == this->t1); 
}

void Control::default_data() {
    for (int i = 0; i < this->N; i++) {
        this->data(i) = 0.;
    }
}

void Control::continue_to_discrete() {
    for (int i = 0; i < this->N; i++) {
        this->data(i) = (*this->cntrl)(this->time(i));
    }
}