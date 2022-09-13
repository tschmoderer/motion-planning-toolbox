/**
 * @file linalg.h
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Main Header file for Linear Algebra Library
 * @version 1.0
 * @date 2022-09-13
 * @copyright Copyright (c) 2022
 */

#ifndef LINALG_H
#define LINALG_H

/* VERSION MACROS */
#define VERSION_LINALG_LIB       "1.0.0"
#define AUTHOR_LINALG_LIB        "T. SCHMODERER/BOHEME"
#define CONTACT_LINALG_LIB       "iathena@mailo.com"
#define DOCUMENTATION_LINALG_LIB "https://tschmoderer.github.io/motion-planning-toolbox/html/index.html"

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