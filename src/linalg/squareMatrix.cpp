/**
* @file squareMatrix.cpp
* @author T. Schmoderer (iathena@mailo.com)
* @brief Implementation of the SquareMatrix class
* @version 1.0
* @date 2021-11-17
* @copyright Copyright (c) 2021
*/

#include "squareMatrix.h"

/* CONSTRUCTORS */

SquareMatrix::SquareMatrix() : Matrix() {}
SquareMatrix::SquareMatrix(uint16_t n) : Matrix(n,n) {}
SquareMatrix::SquareMatrix(const SquareMatrix & in) : Matrix(in)  {}

/* DESTRUCTOR */

SquareMatrix::~SquareMatrix() {/* Destructor of matrix is called */}

/* ACCESSORS */

/* OPERATORS */

SquareMatrix & SquareMatrix::operator=(const SquareMatrix & A) {
    Matrix::operator=(A);
    return *this;
}

SquareMatrix SquareMatrix::operator-() const {
    SquareMatrix A(this->n_rows); 
    for (int i = 0; i < this->n_elements; i++) {
        A(i) = -this->data[i];
    }
    return A;
}

SquareMatrix operator*(const SquareMatrix & lhs, const SquareMatrix & rhs)  {
    assert(lhs.n_cols == rhs.n_rows); 
    SquareMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_rows; i++) {
        for (int j = 0; j < rhs.n_cols; j++) {
            for (int k = 0; k < lhs.n_cols; k++) {
                A(i,j) += lhs(i,k) * rhs(k,j);
            }
        }
    }
    return A;
} 

SquareMatrix operator*(const double k, const SquareMatrix & B) {
    SquareMatrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] *= k;
        }
    }
    return A;
}

SquareMatrix operator*(const SquareMatrix & B, const double k) {
    return k * B;
}

SquareMatrix operator+(const SquareMatrix & lhs, const SquareMatrix & rhs) {
    assert(lhs.n_rows == rhs.n_rows); 
    SquareMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_elements; i++) {
        A.data[i] = lhs.data[i] + rhs.data[i];
    }
    return A;
}

SquareMatrix operator+(const double k, const SquareMatrix & B) {
    SquareMatrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] += k;
        }
    }
    return A;
}

SquareMatrix operator+(const SquareMatrix & B, const double k) {
    return k + B;
}

SquareMatrix operator-(const SquareMatrix & lhs, const SquareMatrix & rhs) {
    assert(lhs.n_rows == rhs.n_rows); 
    SquareMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_elements; i++) {
        A.data[i] = lhs.data[i] - rhs.data[i];
    }
    return A;
}

SquareMatrix operator-(const SquareMatrix & B, const double k) {
    SquareMatrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] -= k;
        }
    }
    return A;
}
		
SquareMatrix operator-(const double k, const SquareMatrix & B) {
    return -(B-k);
} 
		
SquareMatrix operator/(const SquareMatrix & B, const double k) {
    assert(k != 0);
    SquareMatrix A(B); 
    for (int i = 0; i < A.get_n_elements(); i++) {
        A.data[i] /= k;
    }
    return A;
}

/* OVERLOAD METHODS MATRIX */

SquareMatrix SquareMatrix::transpose() const {
    SquareMatrix res(this->n_rows); 
    for (int i = 0; i < this->n_cols; i++) {
        for (int j = 0; j < this->n_rows; j++) {
            res(i,j) = this->at(j,i); 
        }
    }
    return res; 
}

/* OVERLOAD STATIC METHODS MATRIX */

SquareMatrix SquareMatrix::zeros(uint16_t n) {
    assert(n > 0); 
    SquareMatrix A(n); 
    return A;
}

SquareMatrix SquareMatrix::ones(uint16_t n) {
    assert(n > 0); 
    SquareMatrix A(n); 
    return A + 1;
}

SquareMatrix SquareMatrix::rand(uint16_t n) {
    assert(n > 0);  
    srand (time(NULL));
    SquareMatrix M(n); 
    for (int i = 0; i < M.get_n_elements(); i++) {
        M(i) = ((double) std::rand() / (RAND_MAX)); 
    }
    return M; 
}

SquareMatrix SquareMatrix::hilbert(uint16_t n) {
    assert(n > 0); 
    SquareMatrix M(n); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M(i,j) = 1./(i+j+1);
        }
    }
    return M;
} 

SquareMatrix SquareMatrix::vandermonde(const Vector & v) {
    SquareMatrix M(v.get_dim()); 
    for (int i = 0; i < v.get_dim(); i++) {
        for (int j = 0; j < v.get_dim(); j++) {
            M(i,j) = pow(v(i), j);
        }
    }
    return M;
}

SquareMatrix SquareMatrix::outer(const Vector & u, const Vector & v) {
    assert(u.get_dim() == v.get_dim());
    SquareMatrix A(u.get_dim()); 
    for (int i = 0; i < u.get_dim(); i++) {
        for (int j = 0; j < v.get_dim(); j++) {
            A(i,j) = u[i] * v[j]; 
        }
    }
    return A; 

}
SquareMatrix SquareMatrix::matmul(const SquareMatrix & A, MATRIX_TRANSPOSE TRANSA, const SquareMatrix & B, MATRIX_TRANSPOSE TRANSB) {
    uint16_t n_A = A.get_n_rows(); 
    uint16_t n_B = B.get_n_rows(); 

    assert(n_A == n_B); 

    // Case 1: A^t * B
    if ((TRANSA == TRANSPOSE) && (TRANSB == NO_TRANSPOSE)) {
        SquareMatrix M(n_A); 
        for (int i = 0; i < n_A; i++) {
            for (int j = 0; j < n_B; j++) {
                for (int k = 0; k < n_A; k++) {
                    M(i,j) = A(k,i) * B(k,j); 
                }
            }
        }
        return M; 
    }

    // Case 2: A * B^t
    if ((TRANSA == NO_TRANSPOSE) && (TRANSB == TRANSPOSE)) {
        SquareMatrix M(n_A); 
        for (int i = 0; i < n_A; i++) {
            for (int j = 0; j < n_B; j++) {
                for (int k = 0; k < n_A; k++) {
                    M(i,j) = A(i,k) * B(j,k); 
                }
            }
        }
        return M; 
    }

    // Case 3: A^t * B^t
    if ((TRANSA == TRANSPOSE) && (TRANSB == TRANSPOSE)) {
        SquareMatrix M(n_A); 
        for (int i = 0; i < n_A; i++) {
            for (int j = 0; j < n_B; j++) {
                for (int k = 0; k < n_A; k++) {
                    M(i,j) = A(k,i) * B(j, k); 
                }
            }
        }
        return M; 
    }

    // Case 4: A * B
    return A * B; 

}

/* STATIC METHODS */

SquareMatrix SquareMatrix::eye(uint16_t n) {
    SquareMatrix A(n);
    for (int i = 0; i < n; i++ ) {
        A(i,i) = 1.0;
    }
    return A;
}

SquareMatrix SquareMatrix::diag(const Vector & v) {
    SquareMatrix A(v.get_dim()); 
    for (int i = 0; i < A.n_rows; i++) {
        A(i,i) = v(i); 
    }
    return A;
}

Vector SquareMatrix::diag(const SquareMatrix & A) {
    Vector res(A.n_rows); 
    for (int i = 0; i < A.n_rows; i++) {
        res(i) = A(i,i); 
    }
    return res;
}

double SquareMatrix::tr(const SquareMatrix & A) {
    double res = 0.; 
    for (int i = 0; i < A.n_rows; i++) {
        res += A(i,i); 
    }
    return res;
}