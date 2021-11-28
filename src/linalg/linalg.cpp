#include "linalg.h"

Vector solve(const DiagonalMatrix & D, const Vector & b) {
    assert(D.get_dim() == b.get_dim()); 
    Vector res(b.get_dim()); 
    for (int i = 0; i < b.get_dim(); i++) {
        res(i) = b(i) / D(i); 
    }
    return res; 
}

Vector solve(const LTMatrix & L, const Vector & b) {
    Vector res(b.get_dim()); 
    for (int i = 0; i < b.get_dim(); i++) {
        res(i) = b(i); 
        for (int j = 0; j < i; j++) {
            res(i) -= L(i,j) * res(j);
        }
        res(i) /= L(i,i); 
    }
    return res; 
}