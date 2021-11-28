#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

/**
* @brief 
* 
* @param n 
* @return uint32_t 
*/
inline uint32_t triangular(uint16_t n) {return n*(n+1)/2;}

void zeros_data(double * , uint32_t );

#endif