#include "../include/header/controls.h"

/* CONSTRUCTORS */

/**
 * @brief Construct a new Controls::Controls object
 * Create a list of nb Control object with domain \f$[t_0,t_1]\f$ and \f$H\f$ step of discretisation
 * @param nb Number of controls
 * @param t0 
 * @param t1
 * @param H Number of discretisation time step of \f$[t_0,t_1]\f$
 * @warning nb should takes its values between \f$[0,255]\f$
 * @warning Interpolation method is not set, should be manually added after instanciating a Controls object
 * @warning Integration method is not set, should be manually added after instanciating a Controls object
 */
Controls::Controls(uint8_t nb, double t0, double t1, uint16_t H) {    
    assert(nb < 256);
    assert(t1 > t0);  
    assert(H > 1); 

    this->M  = nb;     
    this->t0 = t0; 
    this->t1 = t1; 
    this->H  = H; 

    this->construct_discrete_time(); 
    this->default_data();
    
    this->interpolator = NULL; 
    this->integrator   = NULL; 
}

/**
 * @brief Construct a new Controls::Controls object
 * Copy constructor
 * @param cs a Controls object to be copied
 */
Controls::Controls(const Controls & cs) {
    this->M  = cs.M; 
    this->t0 = cs.t0;
    this->t1 = cs.t1; 
    this->H  = cs.H; 

    this->time = cs.time; 
    this->data = cs.data;

    this->interpolator = new Interpolator1D(*cs.interpolator);  
    this->integrator   = new Integrator1D(*cs.integrator); 
}

/* DESTRUCTOR */
/**
 * @brief Destroy the Controls::Controls object
 */
Controls::~Controls() {
    if (this->interpolator != NULL) {
        delete this->interpolator; 
    } 
    if (this->integrator != NULL) {
        delete this->integrator;
    } 
}

/* ACCESSORS */
/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t Controls::get_nb_cntrl() const {
    return this->M; 
}

/**
 * @brief 
 * 
 * @param idx 
 * @return VectorXd 
 */
VectorXd Controls::get_control(uint8_t idx) const {
    assert(idx < this->M); 
    return this->data.col(idx);
}

/**
 * @brief 
 * 
 * @param t0 
 * @warning t0 should be less than object attribute t1
 * @warning Does not change data, hence the same data are now evaluated at the new interpolation points defined by the discretisation of the interval \f$[t_0,t_1]\$ into H pieces
 */
void Controls::set_t0(double t0) {
    assert(t0 < this->t1);

    this->t0 = t0;

    this->construct_discrete_time();
} 

/**
 * @brief 
 * 
 * @param t1
 * @warning t1 must be greater than object attribute t0 
 * @warning Does not change data, hence the same data are now evaluated at the new interpolation points defined by the discretisation of the interval \f$[t_0,t_1]\$ into H pieces
 */
void Controls::set_t1(double t1) {
    assert(t1 > this->t0); 

    this->t1 = t1;

    this->construct_discrete_time();
}

/**
 * @brief 
 * 
 * @param H
 * @warning H should be at least 2 
 * @warning Reiniatlise data to zeros
 */
void Controls::set_H(uint16_t H) {
    assert(H > 1);

    this->H = H;

    this->construct_discrete_time();
    this->default_data(); 
}

/**
 * @brief 
 * 
 * @param t0 
 * @param t1 
 * @param H 
 * @warning t0 should be less that t1
 * @warning H should be at least 2
 * @warning Reinitialise data to zeros
 */
void Controls::set_discretisation_cntrls(double t0, double t1, uint16_t H) {
    assert(t1 > t0); 
    assert(H > 1); 

    this->t0 = t0; 
    this->t1 = t1;
    this->H = H;

    this->construct_discrete_time(); 
    this->default_data(); 
}

void Controls::set_cntrl(uint8_t idx, double d) {
    assert(idx < this->M);
    this->data.col(idx) = MatrixXd::Constant(this->H, 1, d);
}

void Controls::set_cntrl(uint8_t idx, VectorXd val) {
    assert(idx < this->M);
    assert(val.size() == this->H);
    this->data.col(idx) = val;
}

/**
 * @brief 
 * 
 * @param interpol 
 */
void Controls::set_interpolation_method(const Interpolator1D * interpol) {
    if (this->interpolator != NULL) {
        delete this->interpolator; 
    }

    this->interpolator = new Interpolator1D(*interpol); 
} 

/**
 * @brief 
 * 
 * @param integr 
 */
void Controls::set_integration_method(const Integrator1D * integr) {
    if (this->integrator != NULL) {
        delete this->integrator; 
    }

    this->integrator = new Integrator1D(*integr); 
} 

/* METHODS */
/**
 * @brief Compute the \f$L^2\f$ dot product of two Controls object
 * 
 * @param cs 
 * @return double 
 * @warning The integrator attibute must be set before using this method
 * @warning The integration method of the first Controls object is used.
 */
double Controls::dot_prod_l2(const Controls & cs) const {
    assert(this->M == cs.M); 
    assert(this->H == cs.H); 
    assert(this->t0 == cs.t0); 
    assert(this->t1 == cs.t1); 
    assert(this->integrator != NULL);

    double res = 0.;
    VectorXd u1(this->H); 
    VectorXd u2(this->H); 

    for (int i = 0; i < this->M; i++) {
        u1 = this->get_control(i); 
        u2 = cs.get_control(i);
        res += this->integrator->integr(this->time, u1.array()*u2.array());
    }
    return res; 
}

double Controls::norm2() const {
    return sqrt(this->dot_prod_l2(*this));
}

/* OPERATORS */
/**
 * @brief 
 * 
 * @param t 
 * @return VectorXd 
 * @warning The interpolator attibute must be set before using this method
 */
VectorXd Controls::operator()(double t) const {
    assert(this->interpolator != NULL);

    VectorXd res(this->M); 
    VectorXd cntrl;
    for (int i = 0; i < this->M; i++) {
        cntrl  = this->get_control(i);
        res(i) = this->interpolator->interp1d(&this->time, &cntrl, t); 
    }
    return res;
}

/**
 * @brief Overload the assignement operator. 
 * Acts like a copy constructor.
 * @param cs The controls to be copied. 
 * @return Controls& A copy of controls cs
 */
Controls & Controls::operator=(const Controls & cs) {
    if (cs == *this) {
        return *this;
    }

    this->M  = cs.M;
    this->t0 = cs.t0;
    this->t1 = cs.t1;
    this->H  = cs.H;

    this->time = cs.time; 
    this->data = cs.data; 

    if (this->interpolator != NULL) {
        delete this->interpolator; 
    }

    if (this->integrator != NULL) {
        delete this->integrator;
    }

    this->interpolator = new Interpolator1D(*cs.interpolator);
    this->integrator   = new Integrator1D(*cs.integrator);

    return *this;
}

Controls & Controls::operator+=(const Controls & cs) {
    assert(this->M  == cs.M);
    assert(this->t0 == cs.t0); 
    assert(this->t1 == cs.t1);
    assert(this->H  == cs.H);

    this->data += cs.data;
    return *this;
}

Controls & Controls::operator-=(const Controls & cs) {
    assert(this->M  == cs.M);
    assert(this->t0 == cs.t0); 
    assert(this->t1 == cs.t1);
    assert(this->H  == cs.H);

    this->data -= cs.data;
    return *this;
}

Controls Controls::operator-() const {
    Controls res(*this); 
    res.data = -res.data;
    return res;
}


bool operator==(const Controls & lhs, const Controls & rhs) {
    if (lhs.M != rhs.M) {
        return false;
    }

    if ((lhs.t0 != rhs.t0) || (lhs.t1 != rhs.t1) || (lhs.H != rhs.H)) {
        return false; 
    }

    if (lhs.time != rhs.time) {
        return false;
    }

    if (lhs.data != rhs.data) {
        return false;
    }

    return true; 
}

/**
 * @brief \f$L^2\f$ dot product between two Controls objects
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return double 
 * @warning Both Controls objects must have the same attributes M, t0, t1, H
 */
double operator*(const Controls & lhs, const Controls & rhs) {
    assert(lhs.M  == rhs.M); 
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.H  == rhs.H); 

    return lhs.dot_prod_l2(rhs); 
}

/**
 * @brief Operator, multiplication of a Controls object by a scalar
 * 
 * @param d A scalar
 * @param rhs A Controls object
 * @return Controls object whose data are d*c.data
 */
Controls operator*(const double d, const Controls & rhs) {
    Controls res(rhs); 
    res.data = d*res.data; 
    return res; 
}

/**
 * @brief Operator, multiplication of a Controls object by a scalar
 * @param lhs A Controls object
 * @param rhs A scalar
 * @return Controls object whose data are d*c.data
 */
Controls operator*(const Controls & lhs, const double d) {
    // call previous operator
    return d*lhs;
}

/**
 * @brief Sum of two Controls object
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return Controls whose data are lhs.data + rhs.data 
 * @warning Both Controls objects must have the same attributes M, t0, t1, H
 */
Controls operator+(const Controls & lhs, const Controls & rhs) {
    assert(lhs.M  == rhs.M); 
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.H  == rhs.H); 

    Controls res(lhs); 
    res.data += rhs.data;
    return res;
}

/**
 * @brief Substraction of two Controls object
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return Controls whose data are lhs.data - rhs.data 
 * @warning Both Controls objects must have the same attributes M, t0, t1, H
 */
Controls operator-(const Controls & lhs, const Controls & rhs) {
    assert(lhs.M  == rhs.M); 
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.H  == rhs.H); 

    Controls res(lhs); 
    res.data -= rhs.data;
    return res;
}


/**
* @brief Operator of division of a Controls object with a scalar.
* 
* @param d Double value dividing lhs
* @param lhs Controls object to be divised
* @return Control whose data are lhs.data[i] / d
* @warning d must be non zero
*/
Controls operator/(const Controls & lhs, const double d) {
    assert(d != 0); 
    // call previous operator
    return (1./d) * lhs;
}


std::ostream & operator<<(std::ostream & os, const Controls & cs) {
    VectorXd cntrl;
    for (int i = 0; i < cs.M; i++) {
        cntrl = cs.get_control(i);

        os << "Control : #" << i+1 << std::endl; 
        for (int i = 0; i < cs.H; i++) {
            os << cs.time(i) << "\t"; 
            os << cntrl(i) << std::endl; 
        }   
        os << std::endl; 
    }
    return os; 
}

/* PRIVATE METHODS */
void Controls::construct_discrete_time() {
    this->time = VectorXd::LinSpaced(this->H, this->t0, this->t1); 
}

void Controls::default_data() {
    this->data = MatrixXd::Zero(this->H, this->M);
}