#ifndef LINALG_H
#define LINALG_H

/* INCLUDE ALL HEADERS */

#include "utils.h"
#include "vector.h"
#include "matrix.h"
#include "squareMatrix.h"
#include "lowerTriangularMatrix.h"

/* ADDITIONNAL TYPES */

typedef Vector DiagonalMatrix;

/* ADDITIONNAL METHODS */

double tr(const DiagonalMatrix & );
double det(const DiagonalMatrix & );

Vector solve(const DiagonalMatrix & , const Vector & );
Vector solve(const LTMatrix & , const Vector & );

#endif