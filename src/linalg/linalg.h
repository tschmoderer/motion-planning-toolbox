#ifndef LINALG_H
#define LINALG_H

/* INCLUDE ALL HEADERS */

#include "utils.h"
#include "vector.h"
#include "matrix.h"
#include "squareMatrix.h"
#include "lowerTriangularMatrix.h"
#include "diagonalMatrix.h"

/* ADDITIONNAL TYPES */


/* ADDITIONNAL METHODS */

Vector solve(const DiagonalMatrix & , const Vector & );
Vector solve(const LTMatrix & , const Vector & );

#endif