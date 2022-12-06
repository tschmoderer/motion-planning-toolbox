#include "../../include/header/interpol/interpolator1d.h"

/* CONSTRUCTORS */
/**
 * @brief Construct a new Interpolator1D::Interpolator1D object
 * Default constructor
 * By default extension method to the left and right are CONSTANT
 */
Interpolator1D::Interpolator1D() {
    this->i_method = INTERP_LINEAR;
    this->extend_left_method = EXTEND_CONSTANT; 
    this->extend_right_method = EXTEND_CONSTANT;
}

/**
 * @brief Construct a new Interpolator1D::Interpolator1D object
 * Constrcutor of an Interpolator1D object with user specified parameters
 * @param imethod Interpolation method
 * @param exleft  Method to extend left 
 * @param exright Method to extend right
 */
Interpolator1D::Interpolator1D(interpolation_method_t imethod, extend_t exleft, extend_t exright) {
    this->i_method = imethod;
    this->extend_left_method = exleft; 
    this->extend_right_method = exright;   
}

/**
 * @brief Construct a new Interpolator1D::Interpolator1D object
 * Copy constructor
 * @param interp An Interpolator1D objet to be copied
 */
Interpolator1D::Interpolator1D(const Interpolator1D & interp) {
    this->i_method = interp.i_method; 
    this->extend_left_method = interp.extend_left_method; 
    this->extend_right_method = interp.extend_right_method;   
}

/* DESTRUCTOR */
/**
 * @brief Destroy the Interpolator1D::Interpolator1D object
 */
Interpolator1D::~Interpolator1D() {}

/* ACCESSORS */
void Interpolator1D::set_method(interpolation_method_t im) {
    this->i_method = im;
}

/**
 * @brief Set a mew method for left extension of the interpolation operator
 * @param new_exleft 
 */
void Interpolator1D::set_exleft(extend_t new_exleft) {
    this->extend_left_method = new_exleft;
}

/**
 * @brief Set a mew method for right extension of the interpolation operator
 * @param new_exright 
 */
void Interpolator1D::set_exright(extend_t new_exright) {
    this->extend_right_method = new_exright;
}

/**
 * @brief get current method for left extension of the interpolation operator
 * @return extend_t 
 */
extend_t Interpolator1D::get_exleft() const {
    return this->extend_left_method;
}

/**
 * @brief get current method for right extension of the interpolation operator
 * @return extend_t 
 */
extend_t Interpolator1D::get_exright() const {
    return this->extend_right_method;
}