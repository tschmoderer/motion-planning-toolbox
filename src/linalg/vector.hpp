/**
 * @file vector.hpp
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Header file for Vector class
 * @version 2.0
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstdint>
#include <math.h>
#include <cassert>
#include <iostream>
#include <stdlib.h>
#include <time.h>

/**
 * @class Vector
 * @brief A lightweight class describing a Vector object. 
 * Vectors are array with size n (>0) of doubles.
 * 
 * @warning Maximum dimension of a Vector is 65 535
 * @warning Indices are 0-based. Math formulae must be adpted consequently.
 * @todo    Template this class to use different data types (double, float, complex)
 */
class Vector {
    public: 
        /* CONSTRUCTORS */
        /**
         * @brief Construct a new Vector object. 
         * Default constructor. 
         * Return an empty vector of 0 dimension 
         */
        Vector() {
            this->dim  = 0; 
            this->data = NULL; 
        }

        /**
         * @brief Construct a new Vector object.
         * Return a zeros-vector of dimension n.
         * @param n Dimension of the desired vector (must be greater or equal than 1)
         */
        Vector(uint16_t n) {
            assert(n > 0);
            this->dim  = n; 
            this->data = new double[n]; 
            for (int i = 0; i < n; i++) {
                this->data[i] = 0.; 
            }
        }

        /**
         * @brief Construct a new Vector object.
         * Construct a vector object from an array of double. 
         * @param dat Array of double of size n
         * @param n Size of the input array
         */
        Vector(double * dat, uint16_t n) {
            assert(n > 0);
            this->dim  = n; 
            this->data = new double[n]; 
            for (int i = 0; i < n; i++) {
                this->data[i] = dat[i];
            }
        }
        
        /**
         * @brief Construct a new Vector object.
         * Copy constructor. 
         * @param v Vector oject to be copied.
         */
        Vector(const Vector & v) {
           this->dim  = v.dim; 
           this->data = new double[this->dim]; 
           for (int i = 0; i < this->dim; i++) {
               this->data[i] = v.data[i];
           }
       } 

        /* DESTRUCTOR */
        /**
         * @brief Destroy the Vector object.
         */
        ~Vector() {
            delete [] this->data; 
        }

        /* ACCESSORS */
        /**
         * @brief Get the dimension of a Vector object.
         * 
         * @return uint16_t Dimension of the Vector. 
         */
        uint16_t get_dim() const {
            return this->dim; 
        }

        /* OEPRATORS */
        /**
         * @brief Access the n-th value of a Vector object.
         * 
         * @param n index of the required value (must be between 0 and dim-1)
         * @return  double & address of the n-th element of the Vector object.
         * @warning indices are 0-based. 
         */
        double & operator[](uint16_t n) const {
            assert(n >= 0); assert(n < this->dim); 
            return this->data[n]; 
        }

        /**
         * @brief Access the n-th value of a Vector object.
         * Same as operator []
         * 
         * @param n index of the required value (must be between 0 and dim-1)
         * @return  double & address of the n-th element of the Vector object.
         * @warning indices are 0-based. 
         */
        double & operator()(uint16_t n) const {
            assert(n >= 0); assert(n < this->dim); 
            return this->data[n]; 
        }

        /**
         * @brief Overload of the equality operator for Vector objects.
         * Two vectors are said to be equal if and only if they have the same dimension and they have exactly the same values.
         * @param v Vector object to be compare with. 
         * @return true If all values of both vectors coincide.
         * @return false If at least of the value of the two vectors differ.
         */
        bool operator==(const Vector & v) const {
            if (this->dim != v.dim) {
                return false; 
            }
            for (int i = 0; i < this->dim; i++) {
                if (this->data[i] != v.data[i]) {
                    return false; 
                }
            }
            return true; 
        }

        /**
         * @brief Overload the assignement operator. 
         * Acts like a copy constructor. 
         * @param v The vector to be copied. 
         * @return Vector& A copy of vector v. 
         */
        Vector & operator=(const Vector & v) {
            if (v == *this) {
                return *this;
            }
            if (this->dim != v.dim) {
                this->dim = v.dim; 
                delete [] this->data; 
                this->data = new double[this->dim]; 
            }
            for (int i = 0; i < this->dim; i++) {
                this->data[i] = v.data[i];
            }
            return *this;
        }

        /**
         * @brief Overload operator += for vectors objects
         * 
         * @param v RHS
         * @return Vector& Addition of current object with rhs
         * @warning Both vector must be of the same dimension
         */
        Vector & operator+=(const Vector & v) {
            assert(this->dim == v.dim); 
            for (int i=0; i < this->dim; i++) {
                this->data[i] += v.data[i];
            }
            return *this;
        }

        /**
         * @brief Overload operator -= for vectors objects
         * 
         * @param v RHS
         * @return Vector& Difference of current object with rhs
         * @warning Both vector must be of the same dimension
         */
        Vector & operator-=(const Vector & v) {
            assert(this->dim == v.dim); 
            for (int i=0; i < this->dim; i++) {
                this->data[i] -= v.data[i];
            }
            return *this;
        }

        /**
         * @brief Operator to get the opposite vector
         * 
         * @param v a Vector object
         * @return Vector the opposite of v, i.e. -v
         */
        Vector operator-(const Vector & v) {
            Vector res(v.dim); 
            for (int i=0; i < this->dim; i++) {
                res.data[i] = -v.data[i];
            }
            return res;
        }
        
        /**
         * @brief Operator of multiplication of a Vector object by a scalar.
         * 
         * @param d Double value to multiply v with
         * @param v Vector to be multiplied
         * @return Vector whose components are v[i]*d
         */
        friend Vector operator*(const double & d, const Vector & v) {
            Vector res(v.dim); 
            for (int i = 0; i < v.dim; i++) {
                res.data[i] = v.data[i] * d; 
            }
            return res; 
        }

        /**
         * @brief Operator of multiplication of a Vector object by a scalar.
         * 
         * @param v Vector to be multiplied
         * @param d Double value to multiply v with
         * @return Vector whose components are v[i]*d
         */
        friend Vector operator*(const Vector & v, const double & d) {
            // Call previous operator
            return d * v;
        }

        /**
         * @brief Operator of addition of a Vector object with a scalar.
         * 
         * @param d Double value added to v
         * @param v Vector to be additioned
         * @return Vector whose components are v[i] + d
         */
        friend Vector operator+(const double & d, const Vector & v) {
            Vector res(v.dim); 
            for (int i = 0; i < v.dim; i++) {
                res.data[i] = v.data[i] + d; 
            }
            return res; 
        }

        /**
         * @brief Operator of addition of a Vector object with a scalar.
         * 
         * @param v Vector to be additioned
         * @param d Double value added to v
         * @return Vector whose components are v[i] + d
         */
        friend Vector operator+(const Vector & v, const double & d) {
            // Call previous operator
            return d + v;
        }

        /**
         * @brief Operator of remove a scalar to a Vector. 
         * 
         * @param d Double value to remove to v
         * @param v Vector to be dimished
         * @return Vector whose components are d - v[i]
         */
        friend Vector operator-(const double & d, const Vector & v) {
            Vector res(v.dim); 
            for (int i = 0; i < v.dim; i++) {
                res.data[i] = d - v.data[i]; 
            }
            return res; 
        }

        /**
         * @brief Operator of remove a scalar to a Vector.
         * 
         * @param v Vector to be dimished
         * @param d Double value to remove to v
         * @return Vector whose components are v[i] - d
         */
        friend Vector operator-(const Vector & v, const double & d) {
            Vector res(v.dim); 
            for (int i = 0; i < v.dim; i++) {
                res.data[i] = v.data[i] - d; 
            }
            return res; 
        }

        /**
         * @brief Operator to divide a Vector by a scalar.
         * 
         * @param v Vector v
         * @param d Double value to divide v (must be non-zero)
         * @return Vector whose components are v[i] / d
         * @warning d must me non-zero
         */
        friend Vector operator/(const Vector & v, const double & d) {
            assert(d != 0.); 
            Vector res(v.dim); 
            for (int i = 0; i < v.dim; i++) {
                res.data[i] = v.data[i] / (1. * d); 
            }
            return res; 
        }

        /**
         * @brief Dot product between vectors
         * 
         * @param v 
         * @return double Dot product between vetcor object and v
         * @warning Both vectors must be of the same dimension.
         */
        double operator*(const Vector & v) const {
            assert(this->dim == v.dim); 
            double res = 0.; 
            for (int i=0; i < this->dim; i++) {
                res += this->data[i] * v.data[i];
            }
            return res;
        }

        /**
         * @brief Overload output stream operator for Vector object
         * 
         * @param os output stream
         * @param v  Vector object
         * @return std::ostream & updated output stream
         */
        friend std::ostream & operator<< (std::ostream & os, const Vector & v) {
            for (int i = 0; i < v.dim; i++) {
                os << v.data[i] << std::endl; 
            }
            return os;
        }

        /* Methods */
        /**
         * @brief Compute the L^1 norm of a Vector object.
         * 
         * @return double L^1 norm of the Vector.
         */
        double norm1() {
            double res = 0.; 
            for (int i=0; i < this->dim; i++) {
                res += abs(this->data[i]);
            }
            return res; 
        }

        /**
         * @brief Compute the Euclidean norm of a Vector object. 
         * 
         * @return double Euclidean of the Vector. 
         */
        double norm2() {
            double res = 0.; 
            for (int i=0; i < this->dim; i++) {
                res += this->data[i] * this->data[i];
            }
            return sqrt(res);
        }

        /**
         * @brief Compute the L^p norm of a Vector object. 
         * 
         * @param p Order of the norm 
         * @return double L^p norm of the Vector.
         */
        double normp(uint16_t p) {
            double res = 0.;
            for (int i=0; i < this->dim; i++) {
                res += pow(abs(this->data[i]), p);
            }
            return pow(res, 1./p); 
        }

        /**
         * @brief Compute the L^{\infty} norm of a Vector object. 
         * 
         * @return double L^{\infty} norm of the Vector. 
         */
        double normInf() {
            double res = abs(this->data[0]); 
            for (int i=1; i < this->dim; i++) {
                if (res < abs(this->data[i])) {
                    res = abs(this->data[i]);
                }
            }
            return res;
        }

        /**
         * @brief A general method to compute the norm of a Vector object. 
         * 
         * @param type Integer to decide the norm to choose:
         * type = -1 compute the L^{\infty} norm 
         * type >= 1 Compute the L^p norm 
         * @return double L^p norm of the Vector. 
         */
        double norm(int type) {
            assert(type >= -1); assert(type != 0);

            if (type == -1) {
                return this->normInf(); 
            }

            if (type == 1) {
                return this->norm1(); 
            }

            if (type == 2) {
                return this->norm2(); 
            }

            return this->normp(type); 
        }

        /**
        * @brief Construct vector of the canonical basis of R^n
        * 
        * @param n Dimension of the vector space (must be greater or equal than 1)
        * @param k Number of the basis vector (must be between 0 and n-1).
        * @return Vector k-th vector of the canonical basis of R^n.
        * @warning Indices are 0-based.
        */
        static Vector basis(uint16_t n, uint16_t k) {
            assert(n > 0); assert(k >= 0); assert(k < n); 
            Vector v(n); 
            v[k] = 1; 
            return v; 
        }

        /**
        * @brief Construct a Vector object of length n filled with zeros.
        * 
        * @param n Dimension of the vector (must be greater or equal than 1).
        * @return Vector A Vector object of size n filled with zeros
        */
        static Vector zeros(uint16_t n) {
            assert(n > 0); 
            Vector v(n);
            return v;
        }

        /**
        * @brief Construct a Vector object of length n filled with random values sampled from 0. to 1.
        * 
        * @param n Dimension of the vector (must be greater or equal than 1).
        * @return Vector  A Vector object of size n filled with random values
        */
        static Vector rand(uint16_t n) {
            assert(n > 0); 
            srand (time(NULL));

            Vector v(n); 
            for (int i = 0; i < n; i++) {
                v[i] = ((double) std::rand() / (RAND_MAX)); 
            }

            return v;
        }

        /**
        * @brief Construct a Vector object of length n filled with ones
        * 
        * @param n Dimension of the vector (must be greater or equal than 1).
        * @return Vector  A Vector object of size n filled with ones
        */
        static Vector ones(uint16_t n) {
            assert(n > 0); 
            Vector v(n); 
            for (int i = 0; i < n; i++) {
                v[i] = 1.; 
            }

            return v;
        }

        /**
        * @brief Construct a Vector object of length n filled  with equally points spaced between t0 and t1 included. 
        * 
        * @param t0 Starting value
        * @param t1 Final value (must be greater than t0)
        * @param n Number of timestep including t0 and t1 (must be greater or equal than 2)
        * @return Vector of size n of equally spaced timestep between t0 and t1
        */
        static Vector linspace(double t0, double t1, uint16_t n) {
            assert(t1 > t0); 
            assert(n >= 2);
            double dt = (t1-t0) / (1.*n - 1); 
            Vector v(n);
            for (int i = 0; i < n; i++) {
                v[i] = t0 + i * dt;
            }
            return v;
        }

    private:
        uint16_t dim;  /*!< Dimension of Vector object. @warning Must be greater than 1 */
        double * data; /*!< Data of the vector object. */
};
#endif