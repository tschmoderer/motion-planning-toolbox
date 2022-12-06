#include "../../../include/header/types/time/timeVector.h"

/* CONSTRUCTORS */
TimeVector::TimeVector() {
    this->t0_ = 0.; 
    this->t1_ = 1.; 
    this->dim_ = 2; 
    this->make_linspace();
}

/**
 * @brief Construct a new Time Vector::TimeVector object
 * Construct a TimeVector object from an array of times 
 * @param dim Dimension of the array 
 * @param t Array of timesteps 
 * @warning The array t is assumed to be sorted in stricly ascending order
 * @warning The dimension should be at least 2
 */
TimeVector::TimeVector(TIME_VECTOR_DIM_T dim, Time_t t[]) {
    assert(dim >= 2); 
    this->dim_ = dim; 
    this->t0_  = t[0];
    this->t0_  = t[dim-1];
    this->data_ = Eigen::Array<Time_t, Eigen::Dynamic, 1>(dim); 
    for (int i = 0; i < dim; i++) {
        this->data_(i) = t[i]; 
    }
    assert(this->check()); 
}

TimeVector::TimeVector(Time_t t0, Time_t t1, TIME_VECTOR_DIM_T n) {
    assert(n >= 2);
    this->t0_ = t0; 
    this->t1_ = t1; 
    this->dim_ = n; 
    this->make_linspace();
}

TimeVector::TimeVector(const TimeVector & tv) {
    this->t0_ = tv.t0_; 
    this->t1_ = tv.t1_; 
    this->dim_ = tv.dim_; 
    this->data_ = tv.data_;
}

/* DESTRUCTOR */
TimeVector::~TimeVector() {}

/* ACCESSORS */
Time_t TimeVector::get_t0() const {
    return this->t0_; 
}

Time_t TimeVector::get_t1() const {
    return this->t1_;
}

TIME_VECTOR_DIM_T TimeVector::size() const {
    return this->dim_;
}

/* METHODS */
#ifndef NDEBUG
    bool TimeVector::check() const {
        if (this->dim_ < 2) {
            return false; 
        }

        if (this->data_(0) != this->t0_) {
            return false; 
        }

        if (this->data_(this->dim_-1) != this->t1_) {
            return false;
        }

        if (this->dim_ != this->data_.size()) {
            return false;
        }

        for (int i = 0; i < this->dim_-1; i++) {
            if (this->data_(i) >= this->data_(i+1)) {
                return false;
            }
        }

        return true;
    }
#endif

/**
 * @brief Return the index of the nearest time step of t. 
 * If t < t0 then 0 is returned
 * If t > t1 then n-1 is returned
 * If \f$t\in[t_0,t_1]\f$ then we return \f$i\f$ such that 
 * \f[
 *  t \in [t_{i}, t_{i+1} [
 * \f]
 * @param t 
 * @return uint16_t 
 */
TIME_VECTOR_DIM_T TimeVector::nearest(Time_t t) const {
    if (t <= this->t0_) {
        return 0; 
    }

    if (t >= this->t1_) {
        return this->size() - 1; 
    }

    for (int i = 0; i < this->size()-1; i++) {
        if ((t >= this->data_(i)) && (t < this->data_(i+1))) {
            return i; 
        }
    }
    
    // never reached
    return this->size() - 1; 
}

/* OPERATORS */
Time_t TimeVector::operator()(TIME_VECTOR_DIM_T idx) const {
    assert(idx < this->dim_); 
    return this->data_(idx); 
}

Time_t TimeVector::operator[](TIME_VECTOR_DIM_T idx) const {
    return this->operator()(idx); 
}

TimeVector & TimeVector::operator=(const TimeVector & tv) {
    if (*this == tv) {
        return *this;
    }
    this->t0_ = tv.t0_; 
    this->t1_ = tv.t1_; 
    this->dim_ = tv.dim_; 
    this->data_ = tv.data_; 
    return *this; 
}

bool operator==(const TimeVector & lhs, const TimeVector & rhs) {
    assert(lhs.check()); 
    assert(rhs.check()); 

    if (lhs.t0_ != rhs.t0_) {
        return false; 
    }

    if (lhs.t1_ != rhs.t1_) {
        return false; 
    }

    if (lhs.dim_ != rhs.dim_) {
        return false; 
    }

    for (int i = 0; i < lhs.dim_; i++) {
        if (lhs.data_(i) == rhs.data_(i)) {
            return false; 
        }
    }

    return true;
}

bool operator!=(const TimeVector & lhs, const TimeVector & rhs) {
    return !(lhs == rhs);
}

std::ostream & operator<<(std::ostream & os, const TimeVector & ts) {
    os << ts.data_;
    return os; 
} 

/* STATIC METHODS */
TimeVector TimeVector::linspace(Time_t t0, Time_t t1, TIME_VECTOR_DIM_T n) {
    return TimeVector(t0, t1, n); 
}

/* PRIVATE METHODS */
void TimeVector::make_linspace() {
    this->data_ = Eigen::Array<Time_t, Eigen::Dynamic, 1>::LinSpaced(this->dim_, this->t0_, this->t1_); 
} 