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
 * @brief Construct a new Matrix object
 * 
 * @param n number of rows (must be greater or equal than 1)
 * @param m number of colums (must be greater or equal than 1)
 */
Matrix::Matrix(uint8_t n, uint8_t m) {
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
 * @brief Construct a new Matrix object
 * 
 * @param n 
 */
Matrix::Matrix(uint8_t n) {
    assert(n > 0);

    this->n_rows = n; 
    this->n_cols = n; 
    this->n_elements = n * n; 
    this->data = new double[n * n]; 

    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = 0.;
    }
}

/**
 * @brief Construct a new Matrix object
 * 
 * @param in 
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
 * 
 */
Matrix::~Matrix() {
    delete [] this->data;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t Matrix::get_n_rows() const {
    return this->n_rows;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t Matrix::get_n_cols() const {
    return this->n_cols;
}

/**
 * @brief Access given element of a matrix 
 * 
 * @param i Row number (Must be greater or equal than 1)
 * @param j Column number (Must be gretaer or equal than 1)
 * @return double & address of the (i,j)-th element of the matrix
 * 
 * @warning Indices are 1-based
 */
double & Matrix::at(uint8_t i, uint16_t j) const {
    assert((0 < i) && (i <= this->n_rows));
    assert((0 < j) && (j <= this->n_cols));

    return this->data[((i-1) * this->n_cols) + j-1]; // TODO : check this formulae.
}

/**
 * @brief 
 * 
 * @param i 
 * @param j 
 * @return double 
 */
double & Matrix::operator()(uint8_t i, uint8_t j) const {
    return this->at(i, j);
}

bool Matrix::operator==(const Matrix & B) const {
    if (this->n_rows != B.n_rows) {
        return false;
    }

    if (this->n_cols != B.n_cols) {
        return false;
    }

    if (this->data != B.data) {
        return false;
    }

    return true;
}

Matrix & Matrix::operator=(const Matrix & B) {
    if (B == *this) {
        return *this;
    }

    this->n_rows = B.n_rows;
    this->n_cols = B.n_cols;
    this->n_elements = this->n_rows * this->n_cols;
    delete [] this->data;
    this->data = new  double[this->n_elements];

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

void Matrix::show() const {
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            std::cout << this->at(i,j) << "\t"; 
        }
        std::cout << std::endl;
    }
}

/**
 * @brief 
 * 
 * @param n 
 * @return Matrix 
 */
Matrix eye(uint8_t n) {
    Matrix A(n);

    for (int i = 0; i < n; i++ ) {
            A(i,i) = 1.0;
    }

    return A;
}

/**
 * @brief 
 * 
 * @param n 
 * @return Matrix 
 */
Matrix zeros(uint8_t n) {
    Matrix A(n);
    return A;
}