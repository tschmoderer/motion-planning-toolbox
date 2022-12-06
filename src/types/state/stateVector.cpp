#include "../../../include/header/types/state/stateVector.h"

/* CONSTRUCTORS */
/*StateVector::StateVector() : DataVector() {}

StateVector::StateVector(VECTOR_SIZE_TYPE n) : DataVector(n) {}

StateVector::StateVector(VECTOR_SIZE_TYPE n, State_t * d) : DataVector(n,d) {}

StateVector::StateVector(Eigen::Matrix<State_t, Eigen::Dynamic, 1> v) : DataVector(v) {}

StateVector::StateVector(const StateVector & x) {
    this->dim_  = x.dim_;
    this->data_ = x.data_;
}*/

/* DESTRUCTOR */
//StateVector::~StateVector() {}

/* METHODS */
/**
 * @brief Construct the k-th vector of the canonical basis of \f$\mathbb{R}^n\f$
 * 
 * @param n 
 * @param k 
 * @return StateVector 
 * @warning n is a non-negative integer ranging from 1 to 65535
 * @warning k is a non-negative integer ranging from 1 to n
 */
/*StateVector StateVector::basis(VECTOR_SIZE_TYPE n, VECTOR_SIZE_TYPE k) {
    assert(n > 0); 
    assert(k > 0);
    assert(k <= n);

    StateVector res(n);
    res.zeros();  
    res(k-1) = 1; 

    return res;
}*/

/* OPERATORS */
/*StateVector operator*(const SCALAR d, const StateVector & x) {
    return x * d;
}

StateVector operator*(const StateVector & x, const SCALAR d) {
    return StateVector(x.data_ * d);
}

StateVector operator+(const StateVector & lhs, const StateVector & rhs) {
    return StateVector(lhs.data_ + rhs.data_);
}

StateVector operator-(const StateVector & lhs, const StateVector & rhs) {
    return StateVector(lhs.data_ - rhs.data_); 
}
StateVector operator/(const StateVector & x, const SCALAR d) {
    assert(d != 0);
    return StateVector(x.data_ / d);
}*/