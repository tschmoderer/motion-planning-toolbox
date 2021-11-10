#include "squareMatrix.h"

SquareMatrix::SquareMatrix(uint16_t n) : Matrix(n,n) {}

SquareMatrix::SquareMatrix(const Matrix & M) : Matrix(M) {
    assert(M.get_n_rows() == M.get_n_cols()); 
}

SquareMatrix & SquareMatrix::operator=(const SquareMatrix & A) {
    Matrix::operator=(A);
    return *this;
}

/**
 * @brief Construct the identity Matrix of size n
 * 
 * @param n Size of the SquareMatrix
 * @return SquareMatrix Identity matrix of dimension n times n 
 */
SquareMatrix SquareMatrix::eye(uint16_t n) {
    SquareMatrix A(n);
    for (int i = 0; i < n; i++ ) {
        A(i,i) = 1.0;
    }
    return A;
}

/**
 * @brief Construct the zeros matrix of size n
 * 
 * @param n Size of the SquareMatrix
 * @return SquareMatrix of dimension n times n composed with only zeros
 */
SquareMatrix SquareMatrix::zeros(uint16_t n) {
    SquareMatrix A(n);
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

SquareMatrix SquareMatrix::vandermonde(const Vector & v) {
    return Matrix::vandermonde(v, v.get_dim()); 
}
