/**
* @file matrix.h
* @author T. Schmoderer (iathena@mailo.com)
* @brief Header file for Matrix class
* @version 2.0
* @date 2021-10-21
* @copyright Copyright (c) 2021
*/

#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <iomanip>

/**
* @brief Enumeration of transposition operation for Matrix object, useful for fast multiplication. 
*/
enum MATRIX_TRANSPOSE {TRANSPOSE, NO_TRANSPOSE};

/**
* @class Matrix
* @brief A class describing a Matrix object. 
* Matrices are array of size (n,m) whre n and m are integer greater or equal than 1. 
* Notice that in general a matrix is not square. Non specific structure is assumed. Square, Diagonal, Triangular, etc, have dedicated classes.
* @warning Indices are 0-based (Math Formulae must be adapted consequently)
* @warning Maximum dimension of a Matrix is 65 535 times 65 535
*/
class Matrix {
	public: 
		/* CONSTRUCTORS*/
		Matrix(); 
		Matrix(uint16_t , uint16_t );
		Matrix(const Matrix & );

		/* DESTRUCTOR */
		virtual ~Matrix();

		/* ACCESSORS */
		uint16_t get_n_rows() const; 
		uint16_t get_n_cols() const;
		uint32_t get_n_elements() const; 

		/* METHODS */
		
		bool is_square() const; 
		Vector row(uint16_t ) const;
		Vector col(uint16_t ) const;
		double norm1() const;
		double normInf() const; 
		double normFrob() const; 
		Matrix transpose() const;

		/* OPERATORS */
		double & operator()(uint32_t ) const;
		double & operator()(uint16_t, uint16_t) const;

		Matrix & operator=(const Matrix & );
		Matrix & operator+=(const Matrix & ); 
		Matrix & operator-=(const Matrix & ); 

		Matrix operator-() const; 

		friend bool operator==(const Matrix & , const Matrix & );

		friend Matrix operator*(const Matrix & , const Matrix & ); 
		friend Vector operator*(const Vector & , const Matrix & ); 
		friend Vector operator*(const Matrix & , const Vector & ); 
		friend Matrix operator*(const double , const Matrix & ); 
		friend Matrix operator*(const Matrix & , const double );

		friend Matrix operator+(const Matrix & , const Matrix & ); 
		friend Matrix operator+(const double , const Matrix & ); 
		friend Matrix operator+(const Matrix & , const double );

		friend Matrix operator-(const Matrix & , const Matrix & ); 
		friend Matrix operator-(const Matrix & , const double );
		friend Matrix operator-(const double , const Matrix & ); 
		
		friend Matrix operator/(const Matrix & , const double );

		friend std::ostream & operator<<(std::ostream & , const Matrix & );

		/* STATIC METHODS */
		static Matrix zeros(uint16_t , uint16_t ); 
		static Matrix ones(uint16_t , uint16_t ); 
		static Matrix rand(uint16_t , uint16_t );
		static Matrix hilbert(uint16_t , uint16_t ); 
		static Matrix vandermonde(const Vector & , uint16_t );
		static Matrix outer(const Vector & , const Vector & );
		static Matrix matmul(const Matrix & , MATRIX_TRANSPOSE , const Matrix & , MATRIX_TRANSPOSE );

	protected:
		/* ATTRIBUTES */
		uint16_t n_rows;     /*!< Number of rows. @warning Must be greater than 1 */
		uint16_t n_cols;     /*!< Number of columns. @warning Must be greater than 1 */
		uint32_t n_elements; /*!< Number of elements */
		double * data;       /*!< Matrix data */

		/* METHODS */
		double & at(uint32_t ) const;
		double & at(uint16_t , uint16_t ) const;
		void show() const;
		void default_data(); 
};

#endif