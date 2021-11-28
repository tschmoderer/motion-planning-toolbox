#include "lowerTriangularMatrix.h"

/* CONSTRUCTORS */

/**
* @brief Construct a new LTMatrix object. 
* Default Constructor, call parent Matrix constructor. 
*/
LTMatrix::LTMatrix() : Matrix() {}

/**
* @brief Construct a new LTMatrix object.  Represent a basic square lower triangular matrix. 
* Data are stored as follows:
* data[0] = l_{11}, data[1,2] = [l_{21}, l_{22}], ...
* @param n Dimension of the matrix (must be greater or equal than $1$). 
*/
LTMatrix::LTMatrix(uint16_t n) {
    assert(n > 0); 
    this->n_rows = n; 
    this->n_cols = n; 
    this->n_elements = triangular(n); 
    this->data = new double[this->n_elements]; 
    this->default_data();
}

/**
* @brief Construct a new LTMatrix object. 
* Represent a general rectangular lower triangular matrix.  
* @param m Number of row of the matrix, must be greater or equal than $n$, 
* @param n Number of colum of the matrix, must be greater or equal than $1$. 
*/
LTMatrix::LTMatrix(uint16_t m, uint16_t n) {
    assert(m > 0); assert(n > 0); 
    assert(m >= n); // otherwise it is a regular dense Matrix. 
    this->n_rows = m; 
    this->n_cols = n; 
    // Matrix is composed of two block on top of each other. 
    // Above block is a square lower triangular matrix of dimension $n\times n$
    // Bellow is a rectangular dense block with dimension $(m-n)\times n$. 
    this->n_elements = triangular(n) + (m-n) * n; 
    this->data = new double[this->n_elements]; 
    this->default_data();
}

/**
* @brief Construct a new LTMatrix object
* Copy constructor. 
* @param in Lower triangular matrix to be copied. 
*/
LTMatrix::LTMatrix(const LTMatrix & in) {
    this->n_rows = in.n_rows; 
    this->n_cols = in.n_cols; 
    this->n_elements = in.n_elements; 
    this->data = new double[this->n_elements];
    for (int i = 0; i < this->n_elements; i++) {
        this->data[i] = in.data[i]; 
    }
} 

/* DESTRUCTORS */

LTMatrix::~LTMatrix() {/*Call Matrix destructor*/}

/*ACCESSORS */

/* METHODS */

/**
 * @brief A method to compute the maximum colum index with non-zero data for a given row $i$.
 * Works for a general rectangular lower triangular matrix $L$ of dimension $(m\times n)$ 
 * with $m\geq n$. With C++ indexing convention, the result is given by 
 * $$
 * j_{\max}(i)=\min(i, n-1),\quad\forall\,0\leq i< m
 * $$
 * @param i Row index, must be between $0$ and $m-1$.
 * @return uint16_t $j_{\max}(i) maximum index of a column with non-zeros data.
 */
uint16_t LTMatrix::max_col_from_row(uint16_t i) const {
    assert(i >=0 ); assert(i < this->n_rows); 
    return std::min((int)i, this->n_cols-1);
}

/* OVERLOAD OPERATORS MATRIX*/

double & LTMatrix::operator()(uint16_t i, uint16_t j) const {
    return this->at(i, j);
}

double & LTMatrix::operator()(uint32_t n) const {
    assert(n >= 0); assert(n < this->n_elements); 
    return this->at(n);
}

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
* @brief Product of Lower Triangular Matrices. For $L_1$ and $L_2$ two lower triangular matrices of dimension $(n,n)$, we have
* $$
* (L_1L_2)_{i,j} = \sum_{k=j}^{i} (L_1)_{ik}(L_2)_{kj} ,\quad \forall\, j \leq i
* $$
* @param lhs Left hand side, a lower triangular matrix of size : $(n, n)$
* @param rhs Right hand side, a lower triangular matrix of size : $(n, n)$
* @return LTMatrix Product lhs and rhs stored as a new lower triangular matrix object
* @warning lhs and rhs must be square (and thus of the same dimensions) lower triangular matrices in order for the product to make sense. 
*/
LTMatrix operator*(const LTMatrix & lhs, const LTMatrix & rhs) {
    assert(lhs.is_square()); assert(rhs.is_square());
    assert(lhs.n_cols == rhs.n_rows); 
    LTMatrix A(lhs.n_rows);
    for (int i = 0; i < lhs.n_rows; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = j; k <= i; k++) {
                A(i,j) += lhs(i,k) * rhs(k,j);
            }
        }
    }
    return A;
} 

Vector operator*(const LTMatrix & lhs, const Vector & rhs) {
    assert(lhs.n_cols == rhs.get_dim()); 
    Vector res(lhs.n_rows); 
    for (int i = 0; i < lhs.n_rows; i++) {
        for (int k = 0; k <= lhs.max_col_from_row(i); k++) {
            res[i] += lhs(i,k) * rhs[k]; 
        }
    }
    return res;
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
            if (j <= L.max_col_from_row(i)) { 
                os << std::setw(6) << L(i,j) << std::setw(4) << "\t"; 
            } else {
                os << std::setw(6) << 0. << std::setw(4) << "\t";
            }
        }
        os << std::endl;
    }
    return os;
}

/* OVERLOAD METHODS MATRIX */

/* STATIC METHODS */

double LTMatrix::tr(const LTMatrix & L) {
    assert(L.is_square()); 
    double res = 0.; 
    for (int i = 0; i < L.n_rows; i++) {
        res += L(i,i); 
    }
    return res;
}

double LTMatrix::det(const LTMatrix & L) {
    assert(L.is_square()); 
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

LTMatrix LTMatrix::rand(uint16_t m, uint16_t n) {
    srand(time(NULL));
    LTMatrix L(m, n); 
    for (int i = 0; i < L.get_n_elements(); i++) {
        L(i) = ((double) std::rand() / (RAND_MAX)); 
    }
    return L; 
}

double & LTMatrix::at(uint32_t n) const {
    assert(n >= 0); assert(n < this->n_elements); 
    return this->data[n]; 
}

/**
* @brief Access given element of a matrix. If $L$ is a lower triangular matrix 
* of dimension $m\times n$ with $m\geq n$, then $i$ can take values between $0$ and $m-1$ 
* and $j$ can take values between $0$ and $j_{\max}(i)=\min(i,n-1)$.
* @param i Row number (must be greater or equal than 0)
* @param j Column number (must be between 0 and $j_{\max}(i)$)
* @return double & Reference to the (i,j)-th element of the matrix
* @warning Indices are 0-based
*/
double & LTMatrix::at(uint16_t i, uint16_t j) const {
    assert((0 <= i) && (i < this->n_rows));
    assert((0 <= j) && (j < this->n_cols));
    assert(j <= i);
    uint32_t idx = 0;
    if (i < this->n_cols) {
        idx = triangular(i) + j;
    } else {
        idx = triangular(this->n_cols) + (i-this->n_cols)*this->n_cols + j;
    }
    return this->data[idx];
}

void LTMatrix::show() const {
    for (int i = 0; i < this->n_rows; i++) {
        for (int j = 0; j < this->n_cols; j++) {
            if (j <= this->max_col_from_row(i)) { 
                std::cout << this->at(i,j) << "\t"; 
            } else {
                std::cout << 0. << "\t";
            }
        }
        std::cout << std::endl;
    }
}