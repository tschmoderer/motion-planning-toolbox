/**
* @file dataMatrix.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief 
*/

#ifndef CNTRLTLBX_MATRIX_H
#define CNTRLTLBX_MATRIX_H

#include "../../utils.h"

template<typename T = double, typename U = STATE_VECTOR_DIM_T, typename V = U>
class Matrix : public Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> {
   public:
      typedef Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> Base;

      Matrix(void) : Base() {}
      Matrix(U nr, V nc) : Base(nr, nc) {}
      
      // This constructor allows you to construct Matrix from Eigen expressions
      template<typename OtherDerived>
      Matrix(const Eigen::MatrixBase<OtherDerived>& other) : Base(other) {}

      // This method allows you to assign Eigen expressions to Matrix
      template<typename OtherDerived>
      Matrix & operator= (const Eigen::MatrixBase<OtherDerived>& other) {
         this->Base::operator=(other);
         return *this;
      }
};

#endif
