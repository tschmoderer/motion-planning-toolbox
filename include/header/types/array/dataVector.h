/**
* @file dataVector.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-12-06
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief 
*/

#ifndef CNTRLTLBX_VECTOR_H
#define CNTRLTLBX_VECTOR_H

#include "../../utils.h"

template<typename T = double, typename U = STATE_VECTOR_DIM_T>
class Vector : public Eigen::Matrix<T, Eigen::Dynamic, 1> {
   public:
      typedef Eigen::Matrix<T, Eigen::Dynamic, 1> Base;

      Vector(void) : Base() {}
      Vector(U n) : Base(n) {}
      
      // This constructor allows you to construct Vector from Eigen expressions
      template<typename OtherDerived>
      Vector(const Eigen::MatrixBase<OtherDerived>& other) : Base(other) {}

      // This method allows you to assign Eigen expressions to Vector
      template<typename OtherDerived>
      Vector & operator= (const Eigen::MatrixBase<OtherDerived>& other) {
         this->Base::operator=(other);
         return *this;
      }
};

#endif
