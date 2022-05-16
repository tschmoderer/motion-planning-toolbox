#include "diagonalMatrix.h"

double tr(const DiagonalMatrix & D) {
    return sum(D);
}

double det(const DiagonalMatrix & D) {
    return prod(D);
}