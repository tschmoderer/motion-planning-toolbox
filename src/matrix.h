#ifndef MATRIX_H
#define MATRIX_H

/**
 * @file matrix.h
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Header file for Matrix class
 * @version 1.0
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 */

#include <iostream>
#include <cstdint>
#include <cassert>
#include "vector.hpp"

/**
 * @class Matrix
 * @brief A class describing a Matrix object. 
 * Matrices are array of size (n,m) whre n and m are integer greater or equal than 1. 
 * Notice that in general a matrix is not square. 
 * @warning Indices are 0-based (Math Formulae must be adapted consequently)
 */
class Matrix {
	public: 
		/* CONSTRUCTORs */
		Matrix(); 
		Matrix(uint8_t , uint8_t );
		Matrix(uint8_t );

		Matrix(const Matrix & );

		/* DESTRUCTOR */
		virtual ~Matrix();

		/* ACCESSORS */
		uint8_t get_n_rows(void) const; 
		uint8_t get_n_cols(void) const;

		/* CLASS METHODS */

		/* OPERATORS */
		double & operator()(uint8_t, uint8_t) const;
		bool operator==(const Matrix & ) const;
		Matrix & operator=(const Matrix & );
		Matrix operator+(const Matrix & ) const; 
		Matrix operator-(const Matrix & ) const; 
		Matrix operator*(const Matrix & ) const; 

		Matrix & operator+=(const Matrix & ); 
		Matrix & operator-=(const Matrix & ); 

		Matrix & operator+=(const double & );
		Matrix & operator-=(const double & );
		Matrix & operator*=(const double & );
		Matrix & operator/=(const double & );

			/* Multiplication scalar with matrix */
		friend Matrix operator*(const double & , const Matrix & ); 
		friend Matrix operator*(const Matrix & , const double & );
			/* Addition scalar with matrix */
		friend Matrix operator+(const double & , const Matrix & ); 
		friend Matrix operator+(const Matrix & , const double & );
			/* Division scalar with matrix */
		friend Matrix operator/(const Matrix & , const double & );
			/* Multiplication Matrix Vector */
		friend Vector operator*(const Matrix & , const Vector & ); 

		/* HELPERS */
		void show() const;

	protected:
		/* ATTRIBUTES */
		uint8_t  n_rows;     /*!< Number of rows. @warning Must be greater than 1 */
		uint8_t  n_cols;     /*!< Number of columns. @warning Must be greater than 1 */
		uint16_t n_elements; /*!< Number of elements */
		double*  data;       /*!< Matrix data */

		/* METHODS */
		double & at(uint8_t , uint16_t ) const;
};

/* Non Members Methods */
Matrix eye(uint8_t );
Matrix zeros(uint8_t );

#endif