/**
* @file matrix.cpp
* @author T. Schmoderer (iathena@mailo.com)
* @brief Implementation of the Matrix class
* @version 2.0
* @date 2021-10-23
* @copyright Copyright (c) 2021
*/

#include "matrix.h"

/* CONSTRUCTORS */

/**
* @brief Construct a Matrix object.
* Default constructor. Set number of rows and number of columns to 0. Set data pointer to NULL.
*/
Matrix::Matrix() {
    this->n_rows     = 0; 
    this->n_cols     = 0; 
    this->n_elements = 0; 
    this->data       = NULL; 
}

/**
* @brief Construct a Matrix object.
* Construct a matrix of size n rows times m columns
* @param m number of rows (must be greater or equal than 1)
* @param n number of colums (must be greater or equal than 1)
*/
Matrix::Matrix(uint16_t m, uint16_t n) {
    assert(m > 0); assert(n > 0);
    this->n_rows     = m; 
    this->n_cols     = n; 
    this->n_elements = n * m; 
    this->data       = new double[n * m]; 
    this->default_data();
}

/**
* @brief Construct a Matrix object.
* Copy contructor
* @param in Matrix to be copied
*/
Matrix::Matrix(const Matrix & in) {
    this->n_rows = in.n_rows; 
    this->n_cols = in.n_cols; 
    this->n_elements = this->n_rows * this->n_cols; 
    this->data = new double[this->n_elements]; 
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = in.data[i]; 
    }
}

/* DESTRUCTORS */

/**
* @brief Destroy the Matrix object
*/
Matrix::~Matrix() {
    delete [] this->data;
}

/* ACCESSORS */

/**
* @brief Accessor to the number of rows.
* @return uint16_t Number of rows of the matrix (is greater or equal than 1)
*/
uint16_t Matrix::get_n_rows() const {
    return this->n_rows;
}

/**
* @brief Accessor to the number of columns.
* @return uint16_t Number of columns of the matrix (is greater or equal than 1)
*/
uint16_t Matrix::get_n_cols() const {
    return this->n_cols;
}

/**
* @brief Accessor to the number of elements
* @return uint32_t Number of elements strored in the matrix
*/
uint32_t Matrix::get_n_elements() const {
    return this->n_elements;
}

/* OPERATORS */

/**
* @brief Overload operator (i,j). 
* @param i Row number (must be greater or equal than 0)
* @param j Column number (must be gretaer or equal than 0)
* @return double & Reference to the (i,j)-th element of the matrix
* @warning Indices are 0-based
*/
double & Matrix::operator()(uint16_t i, uint16_t j) const {
    return this->at(i, j);
}

/**
* @brief Overload operator (i)
* @param n Element number (must be between 0 and n_elements-1)
* @return double& Reference to the n-th stored element of the matrix
*/
double & Matrix::operator()(uint32_t n) const {
    assert(n >= 0); assert(n < this->n_elements); 
    return this->at(n);
}

/**
* @brief Overload assignement operator
* @param B Right Hand Side, Matrix to be copied
* @return Matrix & A Matrix object copy of B.
*/
Matrix & Matrix::operator=(const Matrix & B) {
    if (B == *this) {
        return *this;
    }
    if ((this->n_rows != B.n_rows) || (this->n_cols != B.n_cols)) {
        delete [] this->data;
        this->n_rows = B.n_rows;
        this->n_cols = B.n_cols;
        this->n_elements = this->n_rows * this->n_cols;
        this->data = new double[this->n_elements];
    }
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = B.data[i];
    }
    return *this;
}

/**
* @brief Overload operator +=
* @param B Matrix to add to current Matrix object. 
* @return Matrix & Reference to Matrix object  equal to this->data + B.data
* @warning B must have the same dimensions as the current Matrix object
*/
Matrix & Matrix::operator+=(const Matrix & B) {
    assert(this->n_rows == B.n_rows); 
    assert(this->n_cols == B.n_cols); 
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = this->data[i] + B.data[i];
    }
    return *this;
}

/**
* @brief Overload operator -=
* @param B Matrix to substract to current Matrix object. 
* @return Matrix & Reference to Matrix object  equal to this->data - B.data
* @warning B must have the same dimensions as the current Matrix object
*/
Matrix & Matrix::operator-=(const Matrix & B) {
    assert(this->n_rows == B.n_rows); 
    assert(this->n_cols == B.n_cols); 
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = this->data[i] - B.data[i];
    }
    return *this;
}

/**
* @brief Overload unary operator -
* @return Matrix Object whose coefficients are the opposite of those of the current Matrix object.
*/
Matrix Matrix::operator-() const {
    Matrix A(this->n_rows, this->n_cols); 
    for (int i = 0; i < this->n_elements; i++) {
        A(i) = -this->data[i];
    }
    return A;
}

/**
* @brief Overload of operator ==
* Two matrices are equal if and only they have the same dimensions and the same elements. 
* @param lhs Left Hand Side
* @param rhs Right Hand Side
* @return true if this matrix is equal to B
* @return false if this matrix is different than B
*/
bool operator==(const Matrix & lhs, const Matrix & rhs) {
    if (lhs.n_rows != rhs.n_rows) {
        return false;
    }
    if (lhs.n_cols != rhs.n_cols) {
        return false;
    }
    for (int i = 0; i < lhs.n_elements; i++) {
        if (rhs.data[i] != rhs.data[i]) {
            return false;
        }
    }
    return true;
}

/**
* @brief Overload operator * for multiplication of Matrices
* @param lhs Left Hand Side
* @param rhs Right Hand Side
* @return Matrix Matrix equal to lhs*rhs
* @warning lhs must have the same number of cols as the number of cols of rhs
*/
Matrix operator*(const Matrix & lhs, const Matrix & rhs) {
    assert(lhs.n_cols == rhs.n_rows); 
    Matrix A(lhs.n_rows, rhs.n_cols);
    for (int i = 0; i < lhs.n_rows; i++) {
        for (int j = 0; j < rhs.n_cols; j++) {
            for (int k = 0; k < lhs.n_cols; k++) {
                A(i,j) += lhs(i,k) * rhs(k,j);
            }
        }
    }
    return A;
}

/**
* @brief Overload operator * for left multiplication of covector with Matrix
* @param v A Vector object of dimension n (actually a covector)
* @param A A Matrix object of dimension (n,m)
* @return Vector A Vector object of dimension m (actually a covector)
* @warning Vector v must have the length equal to the number of rows of A
*/
Vector operator*(const Vector & v, const Matrix & A) {
    assert(v.get_dim() == A.n_rows); 
    Vector res(A.n_cols); 
    for (int j = 0; j < A.n_cols; j++) {
        for (int k = 0; k < A.n_rows; k++) {
            res[j] += v[k] * A(k,j); 
        }
    }
    return res;
}

/**
* @brief Overload operator * for right multiplication of Matrix with Vector
* @param v A Vector object of dimension n
* @param A A Matrix object of dimension (m,n)
* @return Vector A Vector object of dimension m 
* @warning Vector v must have the length equla to the number of columns of A
*/
Vector operator*(const Matrix & A, const Vector & v) {
    assert(A.n_cols == v.get_dim()); 
    Vector res(A.n_rows); 
    for (int i = 0; i < A.n_rows; i++) {
        for (int k = 0; k < A.n_cols; k++) {
            res[i] += A(i,k) * v[k]; 
        }
    }
    return res;
}

/**
* @brief Overload operator * for multiplication of a scalar with Matrix
* @param k A scalar.
* @param B A Matrix object.
* @return Matrix Matrix whose coefficients are those of B multiplied by k
*/
Matrix operator*(const double k, const Matrix & B) {
    Matrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] *= k;
        }
    }
    return A;
}

/**
* @brief Overload operator * for multiplication of a Matrix with scalar
* @param B A Matrix object.
* @param k A scalar.
* @return Matrix Matrix whose coefficients are those of B multiplied by k
*/
Matrix operator*(const Matrix & B, const double k) {
    // Use previous operator
    return k * B;
}

/**
* @brief Overload operator + for addition of Matrices
* @param lhs Left Hand Side
* @param rhs Right Hand Side
* @return Matrix Sum of lhs and rhs, i.e. lhs+rhs
* @warning lhs and rhs must have the same dimensions
*/
Matrix operator+(const Matrix & lhs, const Matrix & rhs) {
    assert(lhs.n_rows == rhs.n_rows); 
    assert(lhs.n_cols == rhs.n_cols); 
    Matrix A(lhs.n_rows, lhs.n_cols);
    for (int i = 0; i < lhs.n_elements; i++) {
        A.data[i] = lhs.data[i] + rhs.data[i];
    }
    return A;
}

/**
* @brief Overload operator + for addition of scalar with Matrix
* @param k A scalar.
* @param B A Matrix.
* @return Matrix Matrix whose coefficients are those of B plus k
*/
Matrix operator+(const double k, const Matrix & B) {
    Matrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] += k;
        }
    }
    return A;
}

/**
* @brief Overload operator + for addition of Matrix with scalar
* @param B A Matrix.
* @param k A scalar.
* @return Matrix Matrix whose coefficients are those of B plus k
*/
Matrix operator+(const Matrix & B, const double k) {
   // Use previous operator
   return k + B; 
}

/**
* @brief Overload operator - for soustraction of Matrices
* @param lhs Left Hand Side
* @param rhs Right Hand Side
* @return Matrix Sum of lhs and rhs, i.e. lhs-rhs
* @warning lhs and rhs must have the same dimensions
*/
Matrix operator-(const Matrix & lhs, const Matrix & rhs) {
    assert(lhs.n_rows == rhs.n_rows); 
    assert(lhs.n_cols == rhs.n_cols); 
    Matrix A(lhs.n_rows, lhs.n_cols);
    for (int i = 0; i < lhs.n_elements; i++) {
        A.data[i] = lhs.data[i] - rhs.data[i];
    }
    return A;
}

/**
* @brief Overload operator - for soustraction of Matrix with scalar
* @param B A Matrix.
* @param k A scalar.
* @return Matrix Matrix whose coefficients are those of B minus k
*/
Matrix operator-(const Matrix & B, const double k) {
    Matrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] -= k;
        }
    }
    return A;
}

/**
* @brief Overload operator - for soustraction of scalar with Matrix
* @param k A scalar.
* @param B A Matrix.
* @return Matrix Matrix whose coefficients are k minus B
*/
Matrix operator-(const double k, const Matrix & B) {
    // Use previous operators
    return -(B-k);
}

/**
* @brief Overload operator / for division of Matrix by scalar
* @param B A Matrix.
* @param k A scalar (non-zero).
* @return Matrix Matrix whose coefficients are those of B divided by k
* @warning k must be non-zero.
*/
Matrix operator/(const Matrix & B, const double k) {
    assert(k != 0);
    Matrix A(B); 
    for (int i = 0; i < A.n_elements; i++) {
        A.data[i] /= k;
    }
    return A;
}

/**
* @brief Overload output stream operator for Matrix object
* @param os Output stream.
* @param M Matrix object.
* @return std::ostream & updated output stream 
*/
std::ostream & operator<<(std::ostream & os, const Matrix & M) {
    for (int i = 0; i < M.n_rows; i++) {
        for (int j = 0; j < M.n_cols; j++) {
            os << M(i,j) << "\t"; 
        }
        os << std::endl;
    }
    return os; 
}

/* METHODS */

/**
* @brief Test if a matrix has a square shape. 
* @return true If the Matrix object has teh same number of row and columns. 
* @return false Otherwise. 
*/
bool Matrix::is_square() const {
    return this->n_cols == this->n_rows;
}

/**
* @brief Extract row from Matrix
* @param r Row number must be between 0 and n_rows-1
* @return Vector Vector of length n_cols containing the r-th row of the current Matrix object
*/
Vector Matrix::row(uint16_t r) const {
    assert(r >= 0); assert(r < this->n_rows);
    Vector res(this->n_cols); 
    for (int j = 0; j < this->n_cols; j++) {
        res(j) = this->at(r,j); 
    }
    return res;
}

/**
* @brief Extract column from Matrix
* @param c Column number must be between 0 and n_cols-1
* @return Vector Vector of length n_rows containing the c-th column of the current Matrix object
*/
Vector Matrix::col(uint16_t c) const {
    assert(c >= 0); assert(c < this->n_cols);
    Vector res(this->n_rows); 
    for (int i = 0; i < this->n_rows; i++) {
        res(i) = this->at(i,c); 
    }
    return res;
}

/**
* @brief Compute the norm-1 of a Matrix object. 
* For a Matrix M of dimension $n\times m$, its norm-1 is given by the maximum colum sum (in absolute value)
* \f[
* \|M\|_1 = \max_{1\leq j\leq m} \sum_{i=1}^n |M_{ij}|
* \f]
* @return double Norm-1 of Matrix object 
*/
double Matrix::norm1() const { 
    // Maximum absolute column sum 
    double res = 0.; double s; 
    for (int j = 0; j < this->n_cols; j++) {
        s = 0.; 
        for (int i = 0; i < this->n_rows; i++) {
            s += abs(this->at(i,j)); 
        }
        if (s > res) {
            res = s; 
        }
    }
    return res; 
}

/**
* @brief Compute the norm-Infinity of a Matrix object. 
* For a Matrix M of dimension $n\times m$, its norm-Infinity is given by the maximum row sum (in absolute value)
* $$
* \|M\|_{\infty} = \max_{1\leq i\leq n} \sum_{j=1}^m |M_{ij}|
* $$
* @return double Norm-Infinity of Matrix object 
*/
double Matrix::normInf() const {
    // Maximum line sum 
    double res = 0.; double s; 
    for (int i = 0; i < this->n_rows; i++) {
        s = 0.; 
        for (int j = 0; j < this->n_cols; j++) {
            s += abs(this->at(i,j)); 
        }
        if (s > res) {
            res = s; 
        }
    }
    return res; 
}

/**
* @brief Compute the Frobenius norm of a Matrix object. 
* For a Matrix M of dimension $n\times m$, its Frobenius norm is given by the sum of its coefficient squared
* $$
* \|M\|_{F} = \sum_{i=1}^n \sum_{j=1}^m M_{ij}^2
* $$
* @return double Frobenius norm of Matrix object 
*/
double Matrix::normFrob() const {
    double res = 0.; 
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            res += this->at(i,j) * this->at(i,j); 
        }
    }
    res = sqrt(res); 
    return res; 
}

/**
* @brief Compute the transpose Matrix of a Matrix object. 
* @return Matrix Transpose of current Matrix object.
*/
Matrix Matrix::transpose() const {
    Matrix res(this->n_cols, this->n_rows); 
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            res(j,i) = this->at(i,j); 
        }
    }
    return res; 
}

/* STATIC METHODS */

/**
* @brief Construct a matrix object of dimension n times m filled with zeros
* @param m Number of rows of the Matrix (must be greater or equal than 1).
* @param n Number of cols of the Matrix (must be greater or equal than 1).
* @return Matrix A Matrix object of size nxm filled with zeros
*/
Matrix Matrix::zeros(uint16_t m, uint16_t n) {
    assert(m > 0); assert(n > 0);
    Matrix M(m, n); 
    return M;
}

/**
* @brief Construct a matrix object of dimension n times m filled with ones
* @param m Number of rows of the Matrix (must be greater or equal than 1).
* @param n Number of cols of the Matrix (must be greater or equal than 1).
* @return Matrix A Matrix object of size nxm filled with ones
*/
Matrix Matrix::ones(uint16_t m, uint16_t n) {
    assert(m > 0); assert(n > 0);
    Matrix M(m, n); 
    return M + 1;
}

/**
* @brief Construct a matrix object of dimension n times m filled with random values sampled from 0. to 1.
* @param m Number of rows of the Matrix (must be greater or equal than 1).
* @param n Number of cols of the Matrix (must be greater or equal than 1).
* @return Matrix A Matrix object of size nxm filled with random values
*/
Matrix Matrix::rand(uint16_t m, uint16_t n) {
    assert(m > 0); assert(m > 0); 
    srand (time(NULL));
    Matrix M(m, n); 
    for (int i = 0; i < M.get_n_elements(); i++) {
        M(i) = ((double) std::rand() / (RAND_MAX)); 
    }
    return M; 
}

/**
* @brief Construct an Hilbert matrix.
* @param m Number of rows of the Matrix (must be greater or equal than 1).
* @param n Number of cols of the Matrix (must be greater or equal than 1).
* @return Matrix A Matrix object whose coefficients are $M_{ij} = \frac{1}{i+j-1}$ 
*/
Matrix Matrix::hilbert(uint16_t m, uint16_t n) {
    assert(m > 0); assert(n > 0); 
    Matrix M(m, n); 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            M(i,j) = 1./(i+j+1);
        }
    }
    return M;
}

/**
* @brief Construct a Vandermonde matrix.
* See https://en.wikipedia.org/wiki/Vandermonde_matrix
* @param v Vector of data sampled
* @param n Power order of the vandermonde matrix
* @return Matrix A Matrix object of dimension v.dim x n whose coefficients are $M_{ij}=v_i^{j-1}$ 
*/
Matrix Matrix::vandermonde(const Vector & v, uint16_t n) {
    assert(n > 0); 
    Matrix M(v.get_dim(), n); 
    for (int i = 0; i < v.get_dim(); i++) {
        for (int j = 0; j < n; j++) {
            M(i,j) = pow(v(i), j);
        }
    }
    return M;
}

/**
* @brief Overload operator * between two vectors to compute their outer product
* @param u Vector object of dimension $m$ (>0)
* @param v Vector object of dimension $n$ (>0)
* @return Matrix Matrix object M of dimension $m\times n$ equal to M = u*v^T, i.e. $M_{ij} = u_iv_j$.
*/
Matrix Matrix::outer(const Vector & u, const Vector & v) {
    Matrix A(u.get_dim(), v.get_dim()); 
    for (int i = 0; i < u.get_dim(); i++) {
        for (int j = 0; j < v.get_dim(); j++) {
            A(i,j) = u[i] * v[j]; 
        }
    }
    return A; 
}

/**
* @brief Compute the product of two matrices combined with their transposition 
* @param A Matrix object of dimension $(m_A,n_A)$
* @param TRANSA 
* @param B Matrix object of dimension $(m_B,n_B)$
* @param TRANB 
* @return Matrix 
*/
Matrix Matrix::matmul(const Matrix & A, MATRIX_TRANSPOSE TRANSA, const Matrix & B, MATRIX_TRANSPOSE TRANSB) {
    uint16_t m_A = A.get_n_rows(); 
    uint16_t n_A = A.get_n_cols(); 
    uint16_t m_B = B.get_n_rows(); 
    uint16_t n_B = B.get_n_cols();
    
    // Case 1: A^t * B : (n_A, m_A) * (m_B, n_B)
    if ((TRANSA == TRANSPOSE) && (TRANSB == NO_TRANSPOSE)) {
        assert(m_A == m_B); 
        Matrix M(n_A, n_B); 
        for (int i = 0; i < n_A; i++) {
            for (int j = 0; j < n_B; j++) {
                for (int k = 0; k < m_A; k++) {
                    M(i,j) = A(k,i) * B(k,j); 
                }
            }
        }
        return M; 
    }

    // Case 2: A * B^t : (m_A, n_A) * (n_B, m_B)
    if ((TRANSA == NO_TRANSPOSE) && (TRANSB == TRANSPOSE)) {
        assert(n_A == n_B); 
        Matrix M(m_A, m_B); 
        for (int i = 0; i < m_A; i++) {
            for (int j = 0; j < m_B; j++) {
                for (int k = 0; k < n_A; k++) {
                    M(i,j) = A(i,k) * B(j,k); 
                }
            }
        }
        return M; 
    }

    // Case 3: A^t * B^t : (n_A, m_A) * (n_B, m_B)
    if ((TRANSA == TRANSPOSE) && (TRANSB == TRANSPOSE)) {
        assert(m_A == n_B); 
        Matrix M(n_A, m_B); 
        for (int i = 0; i < n_A; i++) {
            for (int j = 0; j < m_B; j++) {
                for (int k = 0; k < m_A; k++) {
                    M(i,j) = A(k,i) * B(j, k); 
                }
            }
        }
        return M; 
    }

    // Case 4: A * B : (m_A, n_A) * (m_B, n_B)
    return A * B; 
}

/* PRIVATE METHODS */

/**
 * @brief Helper to access the n-th stored value of a Matrix object.
 * @param n Index of the value (must be between 0 and n_elements-1)
 * @return double& Reference to the n-th stored value of Matrix object.
 */
double & Matrix::at(uint32_t n) const {
    assert(n >= 0); assert(n < this->n_elements); 
    return this->data[n]; 
}

/**
* @brief Access given element of a matrix 
* @param i Row number (must be greater or equal than 0)
* @param j Column number (must be greater or equal than 0)
* @return double & Reference to the (i,j)-th element of the matrix
* @warning Indices are 0-based
*/
double & Matrix::at(uint16_t i, uint16_t j) const {
    assert((0 <= i) && (i < this->n_rows));
    assert((0 <= j) && (j < this->n_cols));
    return this->data[(i * this->n_cols) + j];
}

/**
* @brief Helper to display a Matrix object to the standart output stream.
*/
void Matrix::show() const {
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            std::cout << this->at(i,j) << "\t"; 
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Fill the data array with zeros.  
 */
void Matrix::default_data() {
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = 0.;
    }
}