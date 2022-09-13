/**
* @file control.cpp
* @author T. Schmoderer (iathena@mailo.com)
* @brief Implementation of control class
* @version 1.0
* @date 2021-10-31
* 
* @copyright Copyright (c) 2021
* 
*/

#include "control.h"

/**
* @brief Construct a new Control object.
* Default Constructor
* By defauly we have the following values : 
* t0 = 0 ; t1 = 1 ; N = 2
* data = 0
* Interpolator linear with constant extension left and right
*/
Control::Control() {
    this->t0 = 0.; 
    this->t1 = 1.; 
    this->N  = 2; 

    this->time = NULL; 
    this->data = NULL;

    this->construct_discrete_time();
    this->default_data(); 

    this->interpolator = new Interpolator1D(INTERP_LINEAR, EXTEND_CONSTANT, EXTEND_CONSTANT);
}

Control::Control(double t0, double t1, uint16_t N, interpolation_method_t imeth = INTERP_LINEAR, extend_t exleft = EXTEND_CONSTANT, extend_t exright = EXTEND_CONSTANT) {
    this->t0 = t0; 
    this->t1 = t1; 
    this->N = N;

    this->time = NULL; 
    this->data = NULL;

    this->construct_discrete_time();
    this->default_data(); 

    this->interpolator = new Interpolator1D(imeth, exleft, exright);
}

Control::Control(Vector * t, Vector * d,  interpolation_method_t imeth = INTERP_LINEAR, extend_t exleft = EXTEND_CONSTANT, extend_t exright = EXTEND_CONSTANT) {
    assert(t->get_dim() == d->get_dim());
    assert(t->get_dim() >= 2);
    this->t0 = (*t)[0]; 
    this->t1 = (*t)[t->get_dim()-1]; 
    this->N = t->get_dim();

    this->time = new Vector(t->get_dim()); 
    this->data = new Vector(t->get_dim()); 

    for (int i = 0; i < t->get_dim(); i++) {
        (*this->time)[i] = (*t)[i];
        (*this->data)[i] = (*d)[i];
    }

    this->interpolator = new Interpolator1D(imeth, exleft, exright);
}

Control::Control(double t0, double t1, Vector * d,  interpolation_method_t imeth = INTERP_LINEAR, extend_t exleft = EXTEND_CONSTANT, extend_t exright = EXTEND_CONSTANT) {
    assert(d->get_dim() >= 2);
    this->t0 = t0; 
    this->t1 = t1; 
    this->N = d->get_dim();

    this->time = NULL; 
    this->data = new Vector(d->get_dim());

    this->construct_discrete_time();

    for (int i = 0; i < d->get_dim(); i++) {
        (*this->data)[i] = (*d)[i];
    }

    this->interpolator = new Interpolator1D(imeth, exleft, exright);
}

Control::Control(const Control & c) {
    this->t0 = c.t0; 
    this->t1 = c.t1; 
    this->N = c.N;

    this->time = new Vector(c.time->get_dim()); 
    this->data = new Vector(c.data->get_dim()); 

    for (int i = 0; i < c.time->get_dim(); i++) {
        (*this->time)[i] = (*c.time)[i];
        (*this->data)[i] = (*c.data)[i];
    }

    this->interpolator = new Interpolator1D(*c.interpolator);
}

Control::~Control() {
    delete this->interpolator;
    delete this->data;
    delete this->time;
}

/* ACCESSORS */
Vector * Control::get_time() const {
    return this->time;
} 

Vector * Control::get_data() const {
    return this->data; 
}


void Control::set_t0(double new_t0) {
    assert(new_t0 < this->t1); 
    this->t0 = new_t0; 
    this->construct_discrete_time(); 
} 

void Control::set_t1(double new_t1) {
    assert(new_t1 > this->t0); 
    this->t1 = new_t1; 
    this->construct_discrete_time(); 
}

void Control::set_N(uint16_t new_N) {
    assert(new_N >= 2); 
    this->N = new_N; 
    this->construct_discrete_time(); 
}

bool Control::set_data(double ti, double d) {
    assert(ti >= (*this->time)[0]);
    assert(ti <= (*this->time)[this->time->get_dim()-1]);

    for (int i = 0; i < this->N; i++) {
        if ((*this->time)[i] == ti) {
            (*this->data)[i] = d; 
            return true; 
        }
    }
    return false;
}

void Control::set_data(const Vector & d) {
    assert(d.get_dim() == this->N); 
    for (int i = 0; i < this->N; i++) {
        (*this->data)[i] = d[i];  
    } 
}

void Control::set_interp_method(interpolation_method_t imeth) {
    this->interpolator->set_method(imeth);
}

void Control::set_interp_method(interpolation_method_t imeth, extend_t exleft, extend_t exright) {
    this->interpolator->set_method(imeth);
    this->interpolator->set_exleft(exleft);
    this->interpolator->set_exright(exright);
}


/* OPERATORS */
double Control::operator()(double t) const {
    assert(this->t0 <= t); 
    assert(t <= this->t1); 

    return this->interpolator->interp1d(this->time, this->data, t); 
}

Vector Control::operator()(const Vector & tmp) const {
    Vector res(tmp.get_dim()); 
    for (int i = 0; i < tmp.get_dim(); i++) {
        res[i] = (*this)(tmp[i]);
    }
    return res;
}

Control operator+(const Control & lhs, const Control & rhs) {
    assert(lhs.t0 == rhs.t0);
    assert(lhs.t1 == rhs.t1);
    assert(lhs.N == rhs.N);
    assert(lhs.interpolator->get_method() == rhs.interpolator->get_method());
    assert(lhs.interpolator->get_exleft() == rhs.interpolator->get_exleft());
    assert(lhs.interpolator->get_exright() == rhs.interpolator->get_exright());

    Control res(lhs.time, lhs.data, lhs.interpolator->get_method(), lhs.interpolator->get_exleft(), lhs.interpolator->get_exright());
    (*res.data) += (*rhs.data);
    return res;
}

Control operator-(const Control & lhs, const Control & rhs) {
    assert(lhs.t0 == rhs.t0);
    assert(lhs.t1 == rhs.t1);
    assert(lhs.N == rhs.N);
    assert(lhs.interpolator->get_method() == rhs.interpolator->get_method());
    assert(lhs.interpolator->get_exleft() == rhs.interpolator->get_exleft());
    assert(lhs.interpolator->get_exright() == rhs.interpolator->get_exright());

    Control res(lhs.time, lhs.data, lhs.interpolator->get_method(), lhs.interpolator->get_exleft(), lhs.interpolator->get_exright());
    (*res.data) -= (*rhs.data);
    return res;
}

Control & Control::operator=(const Control & c) {
    if (c == *this) {
        return *this;
    }

    delete this->time; 
    delete this->data; 
    delete this->interpolator; 

    this->t0 = c.t0; 
    this->t1 = c.t1; 
    this->N = c.N; 

    this->time = new Vector(c.N); 
    this->data = new Vector(c.N); 

    for (int i = 0; i < c.N; i++) {
        (*this->time)[i] = (*c.time)[i];
        (*this->data)[i] = (*c.data)[i];
    }

    this->interpolator = new Interpolator1D(*c.interpolator);

    return *this;
}

Control & Control::operator+=(const Control & rhs) {
    assert(this->t0 == rhs.t0);
    assert(this->t1 == rhs.t1);
    assert(this->N == rhs.N);
    assert(this->interpolator->get_method() == rhs.interpolator->get_method());
    assert(this->interpolator->get_exleft() == rhs.interpolator->get_exleft());
    assert(this->interpolator->get_exright() == rhs.interpolator->get_exright());

    for (int i = 0; i < this->N; i++) {
        assert((*this->time)[i] == (*rhs.time)[i]);
        (*this->data)[i] += (*rhs.data)[i];
    }

    return *this;
}

Control & Control::operator-=(const Control & rhs) {
    assert(this->t0 == rhs.t0);
    assert(this->t1 == rhs.t1);
    assert(this->N == rhs.N);
    assert(this->interpolator->get_method() == rhs.interpolator->get_method());
    assert(this->interpolator->get_exleft() == rhs.interpolator->get_exleft());
    assert(this->interpolator->get_exright() == rhs.interpolator->get_exright());

    for (int i = 0; i < this->N; i++) {
        assert((*this->time)[i] == (*rhs.time)[i]);
        (*this->data)[i] -= (*rhs.data)[i];
    }

    return *this;
}

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

    this->time = new Vector(this->N); 
    (*this->time) = Vector::linspace(this->t0, this->t1, this->N);

    assert(this->time[0] == this->t0); 
    assert(this->time[this->time->get_dim()] == this->t1); 
}

void Control::default_data() {
    this->data = new Vector(this->N); 
}