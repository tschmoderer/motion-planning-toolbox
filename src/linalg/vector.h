/**
* @file vector.h
* @author T. Schmoderer (iathena@mailo.com)
* @brief Header file for Vector class
* @version 2.0
* @date 2021-11-07
* @copyright Copyright (c) 2021
*/

#ifndef VECTOR_H
#define VECTOR_H

#include "utils.h"

/**
* @class Vector
* @brief A lightweight class describing a Vector object. 
* Vectors are array with size n (>0) of doubles.
* @warning Maximum dimension of a Vector is 65 535
* @warning Indices are 0-based. Math formulae must be adapted consequently.
* @todo    Template this class to use different data types (double, float, complex)
*/
class Vector {
    public: 
        /* CONSTRUCTORS */
        Vector();
        Vector(uint16_t );
        Vector(double * , uint16_t );
        Vector(const Vector & ); 

        /* DESTRUCTOR */
        ~Vector();

        /* ACCESSORS */
        uint16_t get_dim() const;

        /* OEPRATORS */
        double & operator[](uint16_t ) const;
        double & operator()(uint16_t ) const;

        Vector & operator=(const Vector & );
        Vector & operator+=(const Vector & );
        Vector & operator-=(const Vector & );

        Vector operator-() const;

        friend bool operator==(const Vector & , const Vector & );
        friend double operator*(const Vector & , const Vector & );
        friend Vector operator*(const double , const Vector & );
        friend Vector operator*(const Vector & , const double );
        friend Vector operator+(const Vector & , const Vector & );
        friend Vector operator+(const double , const Vector & );
        friend Vector operator+(const Vector & , const double );
        friend Vector operator-(const Vector & , const Vector & );
        friend Vector operator-(const double , const Vector & );
        friend Vector operator-(const Vector & , const double );
        friend Vector operator/(const Vector & , const double );
        friend std::ostream & operator<<(std::ostream & , const Vector & );

        /* METHODS */
        double norm(uint8_t );
        double norm1();
        double norm2();
        double normp(uint8_t );
        double normInf();
        void   sort(); 
        std::vector<double> to_std_vector();
        
        /* STATIC METHODS */
        static Vector basis(uint16_t , uint16_t );
        static Vector zeros(uint16_t );
        static Vector ones(uint16_t );
        static Vector rand(uint16_t );
        static Vector randn(uint16_t ); 
        static Vector randn(uint16_t , double , double ); 
        static Vector linspace(double , double , uint16_t );

        /* FRIEND METHODS */
        friend Vector abs(const Vector & ); 
        friend Vector pow2(const Vector & ); 
        friend double prod(const Vector & ); 
        friend Vector prod(const Vector & , const Vector & );
        friend Vector sqrt(const Vector & ); 
        friend double sum(const Vector & ); 
        
    private: 
        uint16_t dim;  /*!< Dimension of Vector object. @warning Must be greater than 1 */
        double * data; /*!< Data of the vector object. */

        /* METHODS */
        uint16_t partition(int , int ); 
        void quicksort(int , int );

        /* STATIC METHODS */
        static void swap(double *, double * ); 
};

#endif