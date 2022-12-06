#include "../../include/header/controller/controls.h"

/* CONSTRUCTORS */
/**
 * @brief Construct a new Controls::Controls object
 * Create a list of nb Control object with domain \f$[t_0,t_1]\f$ and \f$H\f$ step of discretisation
 * 
 * @param nb Number of controls
 * @param t0 
 * @param t1 
 * @param H  Number of discretisation time step of \f$[t_0,t_1]\f$
 * @param im Interpolation method : default INTERP_LINEAR
 * @param el Strategy to extend data when \f$t < t_0\f$ : default EXTEND_ZERO
 * @param er Strategy to extend data when \f$t > t_1\f$ : default EXTEND_ZERO
 * @param int_nb_step Number of time step to integrate controls : default H
 * 
 * @warning H must be at least 2
 * @warning \f$t_0\f$ must be less than \f$t_1\f$
 * @warning nb must be greater than 0
 * @warning Maximum number of control is 255
 */
Controls::Controls(CNTRL_VECTOR_DIM_T nb, Time_t t0, Time_t t1, TIME_VECTOR_DIM_T H, interpolation_method_t im, extend_t el, extend_t er, TIME_VECTOR_DIM_T int_nb_step) {    
    assert(nb > 0);
    assert(nb < 256);
    assert(t1 > t0);  
    assert(H  > 1); 

    this->M  = nb;     
    this->t0 = t0; 
    this->t1 = t1; 
    this->H  = H; 

    this->construct_discrete_time(); 
    this->default_data();
    
    this->interpolator = Interpolator1D(im, el, er); 
   // this->integrator   = new Integrator1D((int_nb_step == 0) ? H : int_nb_step); 
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

    /*if (this->interpolator != NULL) {
        delete this->interpolator; 
    } */

    this->interpolator = cs.interpolator;  

    /*if (this->integrator != NULL) {
        delete this->integrator;
    } 

    this->integrator   = new Integrator1D(*cs.integrator); */
}

/* DESTRUCTOR */
/**
 * @brief Destroy the Controls::Controls object
 */
Controls::~Controls() {
    /*if (this->interpolator != NULL) {
        delete this->interpolator; 
    } */
   /*if (this->integrator != NULL) {
        delete this->integrator;
    }*/ 
}

/* ACCESSORS */
/**
 * @brief 
 * 
 * @return uint8_t 
 */
CNTRL_VECTOR_DIM_T Controls::get_nb_cntrl() const {
    return this->M; 
}

/**
 * @brief 
 * 
 * @param idx 
 * @return VectorXd 
 */
ControlVector Controls::get_control(CNTRL_VECTOR_DIM_T idx) const {
    assert(idx < this->M); 
    ControlVector res(this->H);
    for (int i = 0; i < this->H; i++) {
        res(i) = this->data(i, idx); 
    }
    return res;
}

/**
 * @brief 
 * 
 * @return VectorXd 
 */
TimeVector Controls::get_time() const {
    return this->time;
}

/**
 * @brief 
 * 
 * @return MatrixXd 
 */
ControlMatrix Controls::get_data() const {
    return this->data;
}

/**
 * @brief 
 * 
 * @param t0 
 * @warning t0 should be less than object attribute t1
 * @warning Does not change data, hence the same data are now evaluated at the new interpolation points defined by the discretisation of the interval \f$[t_0,t_1]\$ into H pieces
 */
void Controls::set_t0(Time_t t0) {
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
void Controls::set_t1(Time_t t1) {
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
void Controls::set_H(TIME_VECTOR_DIM_T H) {
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
void Controls::set_discretisation_cntrls(Time_t t0, Time_t t1, TIME_VECTOR_DIM_T H) {
    assert(t1 > t0); 
    assert(H > 1); 

    this->t0 = t0; 
    this->t1 = t1;
    this->H = H;

    this->construct_discrete_time(); 
    this->default_data(); 
}

/**
 * @brief 
 * 
 * @param idx 
 * @param d 
 */
void Controls::set_cntrl(CNTRL_VECTOR_DIM_T idx, Cntrl_t d) {
    assert(idx < this->M);
    for (int i = 0; i < this->H; i++) {
        this->data(i, idx) = d; 
    }
}

/**
 * @brief 
 * 
 * @param idx 
 * @param val 
 */
void Controls::set_cntrl(CNTRL_VECTOR_DIM_T idx, ControlVector val) {
    assert(idx < this->M);
    assert(val.size() == this->H);
    for (int i = 0; i < this->H; i++) {
        this->data(i, idx) = val(i); 
    }
}

/**
 * @brief 
 * 
 * @param interpol 
 */
void Controls::set_interpolation_method(interpolation_method_t im=INTERP_LINEAR, extend_t el=EXTEND_ZERO, extend_t  er=EXTEND_ZERO) {
    /*if (this->interpolator != NULL) {
        delete this->interpolator; 
    }*/  
    this->interpolator.set_method(im);
    this->interpolator.set_exleft(el); 
    this->interpolator.set_exright(er);
} 

/**
 * @brief 
 * 
 * @param integr 
 */
/*void Controls::set_integration_method(TIME_VECTOR_DIM_T new_h) {
    if (this->integrator != NULL) {
        delete this->integrator; 
    }
    this->integrator = new Integrator1D(new_h); 
} */

/* METHODS */
/**
 * @brief Compute the \f$L^2\f$ dot product of two Controls object
 * 
 * @param cs 
 * @return double 
 */
/*SCALAR Controls::dot_prod_l2(const Controls & cs) const {
    assert(this->M == cs.M); 
    assert(this->H == cs.H); 
    assert(this->t0 == cs.t0); 
    assert(this->t1 == cs.t1); 
    assert(this->integrator != NULL);

    double res = 0.;
    ControlData u1(this->H); 
    ControlData u2(this->H); 

    for (int i = 0; i < this->M; i++) {
        u1 = this->get_control(i); 
        u2.array() *= cs.get_control(i).array();
        res += this->integrator->integr<ControlData>(&this->time, &u2);
    }
    return res; 
}

double Controls::norm2() const {
    return sqrt(this->dot_prod_l2(*this));
}*/

/* OPERATORS */
/**
 * @brief 
 * 
 * @param t 
 * @return VectorXd 
 */
ControlVector Controls::operator()(Time_t t) const {
    //assert(this->interpolator != NULL);

    ControlVector res(this->M); 
    ControlData cntrl(this->H);
    for (int i = 0; i < this->M; i++) {
        for (int j = 0; j < this->H; j++) {
            cntrl(j) = this->data(j, i); 
        }
        res(i) = this->interpolator.interp1d<ControlData, Cntrl_t>(&this->time, &cntrl, t); 
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

    /*if (this->interpolator != NULL) {
        delete this->interpolator; 
    }*/

    /*if (this->integrator != NULL) {
        delete this->integrator;
    }*/

    this->interpolator = cs.interpolator;
    //this->integrator   = new Integrator1D(*cs.integrator);

    return *this;
}

Controls & Controls::operator+=(const Controls & cs) {
    assert(this->M  == cs.M);
    assert(this->t0 == cs.t0); 
    assert(this->t1 == cs.t1);
    assert(this->H  == cs.H);

    this->data = this->data + cs.data;
    return *this;
}

Controls & Controls::operator-=(const Controls & cs) {
    assert(this->M  == cs.M);
    assert(this->t0 == cs.t0); 
    assert(this->t1 == cs.t1);
    assert(this->H  == cs.H);

    this->data = this->data - cs.data;
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
/*SCALAR operator*(const Controls & lhs, const Controls & rhs) {
    assert(lhs.M  == rhs.M); 
    assert(lhs.t0 == rhs.t0); 
    assert(lhs.t1 == rhs.t1); 
    assert(lhs.H  == rhs.H); 

    return lhs.dot_prod_l2(rhs); 
}*/

/**
 * @brief Operator, multiplication of a Controls object by a scalar
 * 
 * @param d A scalar
 * @param rhs A Controls object
 * @return Controls object whose data are d*c.data
 */
Controls operator*(const SCALAR d, const Controls & rhs) {
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
    res.data = res.data + rhs.data;
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
    res.data = res.data - rhs.data;
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

/* PRIVATE METHODS */
void Controls::construct_discrete_time() {
    this->time = TimeVector::linspace(this->t0, this->t1, this->H); 
}

void Controls::default_data() {
    this->data = ControlMatrix::Zero(this->H, this->M);
}