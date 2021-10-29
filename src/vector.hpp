/**
 * @file vector.hpp
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Header file for Vector class
 * @version 1.0
 * @date 2021-10-28
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef Vector_HPP
#define Vector_HPP

#include <cstdint>
#include <math.h>
#include <cassert>

/**
 * @class Vector
 * @brief A class describing a vector object. 
 * Vectors are array of size n (>0) dynamically constructed.
 * 
 * @warning Indices are 0-based. Math formulae must be adpted consequently.
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
            this->dim   = 0; 
            this-> data = NULL; 
        }

        /**
         * @brief Construct a new Vector object.
         * Return a zeros-vector of dimension n.
         * @param n Dimension of the desired vector (must be greater or equal than 1)
         */
        Vector(uint8_t n) {
            this->dim  = n; 
            this->data = new double[n]; 
            for (int i = 0; i < n; i++) {
                this->data[i] = 0.; 
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

        /* DESTRUCTORS */
        /**
         * @brief Destroy the Vector object.
         */
        ~Vector() {
            delete [] this->data; 
        }

        /* ACCESSORS */

        /* OEPRATORS */
        /**
         * @brief Access the n-th value of the vector.
         * 
         * @param n index of the required value (must be between 0 and n-1)
         * @return double& address of the n-th element of the Vector object.
         * @warning indices are 0-based. 
         */
        double & operator()(uint8_t n) const {
            assert(n >= 0); 
            assert(n < this->dim); 
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

        Vector & operator+=(const Vector & v) {
            assert(this->dim == v.dim); 
            for (int i=0; i < this->dim; i++) {
                this->data[i] += v.data[i];
            }
            return *this;
        }

        Vector & operator-=(const Vector & v) {
            assert(this->dim == v.dim); 
            for (int i=0; i < this->dim; i++) {
                this->data[i] -= v.data[i];
            }
            return *this;
        }

        /**
         * @brief Multiplication of a vector by a scalar
         * v * d = d * v : produces a new vector with the same dimension as v and with components equla to d * v[i]
         * @param d Double value to multiply the vector
         * @return Vector
         */
        Vector operator*(double & d) {
            Vector res(this->dim); 
            for (int i = 0; i < this->dim; i++) {
                res.data[i] = this->data[i] * d; 
            }
            return res; 
        }

        /**
         * @brief Addition of a vector by a scalar
         * 
         * @param d Double value to add to the vector 
         * @return Vector 
         */
        Vector operator+(double & d) {
            Vector res(this->dim); 
            for (int i = 0; i < this->dim; i++) {
                res.data[i] = this->data[i] + d; 
            }
            return res; 
        }

        Vector operator-(double & d) {
            Vector res(this->dim); 
            for (int i = 0; i < this->dim; i++) {
                res.data[i] = this->data[i] - d; 
            }
            return res; 
        }

        Vector operator/(double & d) {
            assert(d != 0.); 
            Vector res(this->dim); 
            for (int i = 0; i < this->dim; i++) {
                res.data[i] = this->data[i] / d; 
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
        double operator*(const Vector & v) {
            assert(this->dim == v.dim); 
            double res = 0.; 
            for (int i=0; i < this->dim; i++) {
                res += this->data[i] * v.data[i];
            }
            return res;
        }

        /* Methods */
        /**
         * @brief Construct vector of the canonical basis of R^n
         * 
         * @param n Dimension of the vector space (must be greater or equal than 1)
         * @param k Number of the basis vector.
         * @return Vector k-th vector of the canonical basis of R^n.
         * @warning Indices are 0-based.
         */
        Vector basis(uint8_t n, uint16_t k) {
            assert(n > 0); 
            assert(k >= 0); 
            assert(k < n); 
            Vector v(n); 
            v(k) = 1; 
            return v; 
        }

        /**
         * @brief Compute the Euclidean norm of a vector. 
         * 
         * @return double Euclidean of the vector. 
         */
        double norm2() {
            double res = 0.; 
            for (int i=0; i < this->dim; i++) {
                res += this->data[i] * this->data[i];
            }
            return sqrt(res);
        }

    private:
        uint8_t dim; 
        double * data;
};

#endif