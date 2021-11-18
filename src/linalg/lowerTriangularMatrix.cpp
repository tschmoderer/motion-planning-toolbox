#include "lowerTriangularMatrix.h"

/* CONSTRUCTORS */

LTMatrix::LTMatrix() : Matrix() {}

/**
 * @brief Construct a new Lower Triangular Matrix:: Lower Triangular Matrix object
 * data[0] = l_{11}, data[1,2] = [l_{21}, l_{22}], ...
 * @param n 
 */
LTMatrix::LTMatrix(uint16_t n) {
    assert(n > 0); 
    this->n_rows = n; 
    this->n_cols = n; 
    this->n_elements = n*(n+1) / 2; 
    this->data = new double[this->n_elements]; 
    this->default_data();
}

LTMatrix::LTMatrix(const LTMatrix & in) {
    this->n_rows = in.n_rows; 
    this->n_cols = in.n_cols; 
    this->n_elements = this->n_rows * (this->n_rows + 1) / 2; 
    this->data = new double[this->n_elements];
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = in.data[i]; 
    }
} 

/* DESTRUCTORS */

LTMatrix::~LTMatrix() {}

/*ACCESSORS */

/* METHODS */

/* OVERLOAD OPERATORS MATRIX*/

LTMatrix & LTMatrix::operator=(const LTMatrix & L) {
    if (L == *this) {
        return *this; 
    }
    if ((this->n_rows != L.n_rows) || (this->n_cols != L.n_cols)) {
        delete [] this->data;
        this->n_rows = L.n_rows;
        this->n_cols = L.n_cols;
        this->n_elements = L.n_elements;
        this->data = new double[this->n_elements];
    }
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = L.data[i];
    }
    return *this;
}

LTMatrix LTMatrix::operator-() const {
    LTMatrix L(this->n_rows); 
    for (int i = 0; i < this->n_elements; i++) {
        L(i) = -this->data[i];
    }
    return L;
}

/**
* @brief 
* 
* @param lhs 
* @param rhs 
* @return LTMatrix 
* @todo make this function work
*/
LTMatrix operator*(const LTMatrix & lhs, const LTMatrix & rhs) {
    assert(lhs.n_cols == rhs.n_rows); 
    LTMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_rows; i++) {
        for (int j = 0; j < rhs.n_cols; j++) {
            for (int k = 0; k < lhs.n_cols; k++) {
                A(i,j) += lhs(i,k) * rhs(k,j);
            }
        }
    }
    return A;
} 

LTMatrix operator*(const double k, const LTMatrix & L) {
    LTMatrix A(L); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] *= k;
        }
    }
    return A;
} 

LTMatrix operator*(const LTMatrix & L, const double k) {
    return k * L;
}

LTMatrix operator+(const LTMatrix & lhs, const LTMatrix & rhs) {
    assert(lhs.n_rows == rhs.n_rows); 
    assert(lhs.n_cols == rhs.n_cols);
    LTMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_elements; i++) {
        A.data[i] = lhs.data[i] + rhs.data[i];
    }
    return A;
}

LTMatrix operator+(const double k, const LTMatrix & L) {
    LTMatrix A(L); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] += k;
        }
    }
    return A;
}

LTMatrix operator+(const LTMatrix & L, const double k) {
    return k + L;
}

LTMatrix operator-(const LTMatrix & lhs, const LTMatrix & rhs) {
    assert(lhs.n_rows == rhs.n_rows); 
    assert(lhs.n_cols == rhs.n_cols); 
    LTMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_elements; i++) {
        A.data[i] = lhs.data[i] - rhs.data[i];
    }
    return A;
}

LTMatrix operator-(const LTMatrix & L, const double k) {
    LTMatrix A(L); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] -= k;
        }
    }
    return A;
}

LTMatrix operator-(const double k, const LTMatrix & L) {
    return -(L-k); 
}

LTMatrix operator/(const LTMatrix & L, const double k) {
    assert(k != 0); 
    LTMatrix A(L); 
    for (int i = 0; i < A.get_n_elements(); i++) {
        A.data[i] /= k;
    }
    return A;

}

std::ostream & operator<<(std::ostream & os, const LTMatrix & L) {
    for (int i = 0; i < L.get_n_rows(); i++) {
        for (int j = 0; j < L.get_n_cols(); j++) {
            if (i < j) { 
                os << L(i,j) << "\t"; 
            } else {
                os << 0. << "\t";
            }
        }
        os << std::endl;
    }
    return os;
}

/* OVERLOAD METHODS MATRIX */

/* STATIC METHODS */

double LTMatrix::tr(const LTMatrix & L) {
    double res = 0.; 
    for (int i = 0; i < L.n_rows; i++) {
        res += L(i,i); 
    }
    return res;
}

double LTMatrix::det(const LTMatrix & L) {
    double res = 1.; 
    for (int i = 0; i < L.n_rows; i++) {
        res *= L(i,i); 
    }
    return res;   
}

/* OVERLOAD STATIC METHODS MATRIX */
LTMatrix LTMatrix::zeros(uint16_t n) {
    LTMatrix L(n); 
    return L; 
} 

LTMatrix LTMatrix::ones(uint16_t n) {
    LTMatrix L(n); 
    return L + 1; 
} 

LTMatrix LTMatrix::rand(uint16_t n) {
    srand(time(NULL));
    LTMatrix L(n); 
    for (int i = 0; i < L.get_n_elements(); i++) {
        L(i) = ((double) std::rand() / (RAND_MAX)); 
    }
    return L; 
}

double & LTMatrix::at(uint16_t i, uint16_t j) const {
    assert((0 <= i) && (i < this->n_rows));
    assert((0 <= j) && (j < this->n_cols));
    // TODO CETTE FORMULE EST FAUSSE !!
    return this->data[(i * this->n_cols) + j];
}

void LTMatrix::show() const {
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            if (i < j) { 
                std::cout << this->at(i,j) << "\t"; 
            } else {
                std::cout << 0. << "\t";
            }
        }
        std::cout << std::endl;
    }
}