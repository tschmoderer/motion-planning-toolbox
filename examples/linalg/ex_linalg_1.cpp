#include <iostream>
#include "linalg.h"

int main(int argc, char * argv[]) {
    std::cout.precision(5);

    /* Check at formula square LT Matrix*/
    int N = 3; LTMatrix L1 = LTMatrix::rand(N); 
    std::cout << L1.get_n_rows() << " " << L1.get_n_cols() << " " << L1.get_n_elements() << std::endl << std::endl; 

    for (int i = 0; i < L1.get_n_elements(); i++) {
        std::cout << L1(i) << std::endl;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= L1.max_col_from_row(i); j++) {
            std::cout << "(" << i <<  "," << j << ")\t-->\t" << triangular(i) + j << "\t-->\t" << L1(i,j) << std::endl;
        }
    }
    std::cout << std::endl << L1 << std::endl; 

    int M = N + 5; LTMatrix L2 = LTMatrix::rand(M, N); 
    std::cout << L2.get_n_rows() << " " << L2.get_n_cols() << " " << L2.get_n_elements() << std::endl << std::endl; 

    for (int i = 0; i < L2.get_n_elements(); i++) {
        std::cout << L2(i) << std::endl;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j <= L2.max_col_from_row(i); j++) {
            std::cout << "(" << i <<  "," << j << ")\t-->\t";
            if (i < N) {
                std::cout << triangular(i) + j;
            } else {
                std::cout << triangular(N) + (i-N)*N + j;
            }
            std:: cout << "\t-->\t" << L2(i,j) << std::endl;
        }
    }

    std::cout << std::endl << std::fixed << L2 << std::endl; 

    LTMatrix L3 = LTMatrix::rand(M, M); 
    LTMatrix L4 = LTMatrix::rand(M, M); 

    LTMatrix L5 = L3 * L4;

    std::cout << std::endl << std::fixed << L5 << std::endl; 

    return 0;
}