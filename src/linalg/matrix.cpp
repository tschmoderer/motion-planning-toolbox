/**
 * @file matrix.cpp
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Implémentation of the Matrix class
 * @version 1.0
 * @date 2021-10-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "matrix.h"

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
 * 
 * @param n number of rows (must be greater or equal than 1)
 * @param m number of colums (must be greater or equal than 1)
 */
Matrix::Matrix(uint16_t n, uint16_t m) {
    assert(n > 0); assert(m > 0);

    this->n_rows     = n; 
    this->n_cols     = m; 
    this->n_elements = n * m; 
    this->data       = new double[n * m]; 

    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = 0.;
    }
}

/**
 * @brief Construct a Matrix object.
 * Copy contructor
 * 
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

/**
 * @brief Destroy the Matrix object
 */
Matrix::~Matrix() {
    delete [] this->data;
}

/**
 * @brief Accessor to the number of rows.
 * 
 * @return uint16_t Number of rows of the matrix (is greater or equal than 1)
 */
uint16_t Matrix::get_n_rows() const {
    return this->n_rows;
}

/**
 * @brief Accessor to the number of columns.
 * 
 * @return uint16_t Number of columns of the matrix (is greater or equal than 1)
 */
uint16_t Matrix::get_n_cols() const {
    return this->n_cols;
}

Vector Matrix::row(uint16_t r) const {
    assert(r >= 0); assert(r < this->n_rows);
    Vector res(this->n_cols); 
    for (int j = 0; j < this->n_cols; j++) {
        res(j) = this->at(r,j); 
    }
    return res;
}

Vector Matrix::col(uint16_t c) const {
    assert(c >= 0); assert(c < this->n_cols);
    Vector res(this->n_rows); 
    for (int i = 0; i < this->n_rows; i++) {
        res(i) = this->at(i,c); 
    }
    return res;
}

/**
 * @brief Access given element of a matrix 
 * 
 * @param i Row number (must be greater or equal than 0)
 * @param j Column number (must be gretaer or equal than 0)
 * @return double & address of the (i,j)-th element of the matrix
 * 
 * @warning Indices are 0-based
 */
double & Matrix::at(uint16_t i, uint16_t j) const {
    assert((0 <= i) && (i < this->n_rows));
    assert((0 <= j) && (j < this->n_cols));

    return this->data[(i * this->n_cols) + j];
}

/**
 * @brief Overload of operator (i,j). 
 * 
 * @param i Row number (must be greater or equal than 0)
 * @param j Column number (must be gretaer or equal than 0)
 * @return double & address of the (i,j)-th element of the matrix
 * 
 * @warning Indices are 0-based
 */
double & Matrix::operator()(uint16_t i, uint16_t j) const {
    return this->at(i, j);
}

double Matrix::norm1() const { 
    // Maximum column sum 
    double res = 0.; double s; 
    for (int i=0; i < this->n_cols; i++) {
        s = 0.; 
        for (int j=0; j < this->n_rows; j++) {
            s += abs(this->at(i,j)); 
        }
        if (s > res) {
            res = s; 
        }
    }
    return res; 
}

double Matrix::normInf() const {
    // Maximum line sum 
    double res = 0.; double s; 
    for (int j=0; j < this->n_rows; j++) {
        s = 0.; 
        for (int i=0; i < this->n_cols; i++) {
            s += abs(this->at(i,j)); 
        }
        if (s > res) {
            res = s; 
        }
    }
    return res; 
}

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

Matrix Matrix::transpose() const {
    Matrix res(this->n_cols, this->n_rows); 
    for (int i = 0; i < this->n_cols; i++) {
        for (int j = 0; j < this->n_rows; j++) {
            res(i,j) = this->at(j,i); 
        }
    }
    return res; 
}

/**
 * @brief Overload of operator ==
 * Two matrices are equal if and only they have the same dimensions and the same elements. 
 *
 * @param B Matrix to be tested with
 * @return true if this matrix is equal to B
 * @return false if this matrix is different than B
 */
bool Matrix::operator==(const Matrix & B) const {
    if (this->n_rows != B.n_rows) {
        return false;
    }

    if (this->n_cols != B.n_cols) {
        return false;
    }

    for (int i=0; i < this->n_elements; i++) {
        if (this->data[i] != B.data[i]) {
            return false;
        }
    }

    return true;
}

Matrix & Matrix::operator=(const Matrix & B) {
    if (B == *this) {
        return *this;
    }

    if ((this->n_rows != B.n_rows) || (this->n_cols != B.n_cols)) {
        this->n_rows = B.n_rows;
        this->n_cols = B.n_cols;
        this->n_elements = this->n_rows * this->n_cols;
        delete [] this->data;
        this->data = new double[this->n_elements];
    }

    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = B.data[i];
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix & B) const {
    assert(this->n_rows == B.n_rows); 
    assert(this->n_cols == B.n_cols); 

    Matrix A(*this);

    for (int i = 0; i < this->n_elements; i++) {
        A.data[i] = this->data[i] + B.data[i];
    }

    return A;
}

Matrix Matrix::operator*(const Matrix & B) const {
    assert(this->n_cols == B.n_rows); 

    Matrix A(this->n_rows, B.n_cols);

    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < B.n_cols; j++) {
            for (int k = 0; k < this->n_cols; k++) {
                A(i,j) += this->at(i,k) * B(k,j);
            }
        }
    }

    return A;
}

Matrix operator*(const double & k, const Matrix & B) {
    Matrix A(B); 
    for (int i = 0; i < A.n_elements; i++) {
        A.data[i] *= k;
    }
    return A;
}

Matrix operator*(const Matrix & B, const double & k) {
    Matrix A(B); 
    for (int i = 0; i < A.n_elements; i++) {
        A.data[i] *= k;
    }
    return A;
}

Matrix operator+(const double & k, const Matrix & B) {
    Matrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] += k;
        }
    }
    return A;
}

Matrix operator+(const Matrix & B, const double & k) {
    Matrix A(B); 
    if (k != 0) {
        for (int i = 0; i < A.n_elements; i++) {
            A.data[i] += k;
        }
    }
    return A;
}

Matrix operator/(const Matrix & B, const double & k) {
    assert(k != 0);

    Matrix A(B); 
    for (int i = 0; i < A.n_elements; i++) {
        A.data[i] /= k;
    }
    
    return A;
}

Matrix & Matrix::operator+=(const Matrix & B) {
    assert(this->n_rows == B.n_rows); 
    assert(this->n_cols == B.n_cols); 

    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = this->data[i] + B.data[i];
    }

    return *this;
}

Matrix & Matrix::operator-=(const Matrix & B) {
    assert(this->n_rows == B.n_rows); 
    assert(this->n_cols == B.n_cols); 

    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = this->data[i] - B.data[i];
    }

    return *this;
}

Matrix & Matrix::operator+=(const double & k) {
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] += k;
    }

    return *this;
}

Matrix & Matrix::operator-=(const double & k) {
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] -= k;
    }

    return *this;
}

Matrix & Matrix::operator*=(const double & k) {
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] *= k;
    }

    return *this;
}

Matrix & Matrix::operator/=(const double & k) {
    assert(k != 0.);
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] /= (1.*k);
    }

    return *this;
}

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

std::ostream & operator<<(std::ostream & os, const Matrix & M) {
    for (int i = 0; i < M.n_rows; i++) {
        for (int j = 0; j < M.n_cols; j++) {
            os << M(i,j) << "\t"; 
        }
        os << std::endl;
    }
    return os; 
}

/**
 * @brief Helper to display a Matrix object
 * 
 */
void Matrix::show() const {
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            std::cout << this->at(i,j) << "\t"; 
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::ones(uint16_t n, uint16_t m) {
    assert(n > 0); assert(m > 0);
    Matrix M(n,m); 
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < m; j++) {
            M(i,j) = 1.;
        }
    }
    return M;
}

Matrix Matrix::rand(uint16_t n, uint16_t m) {
    assert(n > 0); assert(m > 0); 
    srand (time(NULL));
    Matrix M(n, m); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            M(i,j) = ((double) std::rand() / (RAND_MAX)); 
        }
    }
    return M; 
}

Matrix Matrix::zeros(uint16_t n, uint16_t m) {
    assert(n > 0); assert(m > 0);
    Matrix M(n,m); 
    return M;
}