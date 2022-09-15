/**
 * @file controls.cpp
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Implementation of Controls class
 * @version 1.0
 * @date 2022-09-14
 * @copyright Copyright (c) 2022
 */
#include "controls.h"

/* CONSTRUCTORS */
/**
 * @brief Construct a new Controls:: Controls object
 * Default Constructor
 * Set m to 0 and create an empty list of controls
 */
Controls::Controls() {
    this->m = 0;
    this->control_list = std::vector<Control>(0);
}

/**
 * @brief Construct a new Controls:: Controls object
 * Construct a list of m default controls 
 * @param m number of controls
 */
Controls::Controls(uint8_t m) {
    this->m = m; 
    for (int i = 0; i < m; i++) {
        this->control_list.push_back(Control());
    }
}

/**
 * @brief Construct a new Controls:: Controls object
 * Construct a list of m copy of control c
 * @param m number of controls
 * @param c a control to be copied m times
 */
Controls::Controls(uint8_t m, Control c) {
    this->m = m; 
    for (int i = 0; i < m; i++) {
        this->control_list.push_back(c);
    }
}

/**
 * @brief Construct a new Controls:: Controls object
 * Constructor a list of controls from a guven list
 * @param vc a list of controls
 */
Controls::Controls(std::vector<Control> vc) {
    this->m = vc.size();
    for (int i = 0; i < this->m; i++) {
        this->control_list.push_back(vc[i]);
    }
}

/**
 * @brief Construct a new Controls:: Controls object
 * Copy constructor
 * @param cs a control list to be copied
 */
Controls::Controls(const Controls & cs) {
    this->m = cs.m;
    for (int i = 0; i < this->m; i++) {
        this->control_list.push_back(cs.control_list[i]);
    }
}

/* DESTRUCTOR */
/**
 * @brief Destroy the Controls:: Controls object
 * Default destructor
 */
Controls::~Controls() {}

/* ACCESSORS */
/**
 * @brief Add a control to the list
 * @param c a control
 * @warning c must have the same time discretisation as the other controls
 */
void Controls::add_control(const Control & c) {
    this->m = this->m+1;
    this->control_list.push_back(c); 
}

/* METHODS */
/**
 * @brief Return time discretisation of the controls
 * @return Vector* 
 */
Vector * Controls::get_time() const {
    assert(this->m > 0); 
    return this->control_list[0].get_time();
}

/**
 * @brief Return data of a given control
 * @param idx 
 * @return Vector* 
 */
Vector * Controls::get_data(uint8_t idx) const {
    assert(idx < this->m); 
    return this->control_list[idx].get_data(); 
}

/**
 * @brief Return data of all controls as a matrix
 * @return Matrix a matrix of m colum and nb_data lines
 */
Matrix Controls::get_data() const {
    uint16_t n = this->control_list[0].get_time()->get_dim();
    Matrix res(n, this->m); 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < this->m; j++) {
            res(i,j) = (*this->control_list[j].get_time())[i];
        }
    }
    return res;
}

/* OPERATORS */
/**
 * @brief Access a given control of the list
 * @param idx 
 * @return Control 
 */
Control Controls::operator[](uint8_t idx) const {
    assert(idx < this->m);
    return this->control_list[idx];
}

/**
 * @brief Interpolate at a single time t all controls of the list
 * @param t 
 * @return Vector 
 */
Vector Controls::operator()(double t) const {
    Vector res(this->m); 
    for (int i = 0; i < this->m; i++) {
        res[i] = this->control_list[i](t); 
    }
    return res;
}

/**
 * @brief Interpolate all controls at all times
 * @param a vector of all times to interpolate
 * @return Matrix of m colum and size of times lines
 */
Matrix Controls::operator()(const Vector & times) const {
    Matrix res(times.get_dim(), this->m); 
    for (int i = 0; i < times.get_dim(); i++) {
        for (int j = 0; j < this->m; j++) {
            res(i,j) = this->control_list[j](times[i]);
        }
    }
    return res;
}

/**
 * @brief Overload assignation operator 
 * Acts like a copy constructor
 * @param vc 
 * @return Controls& 
 */
Controls & Controls::operator=(const Controls & vc) {
    if (vc == *this) {
        return *this; 
    }

    this->m = vc.m; 
    this->control_list.clear();

    for (int i = 0; i < this->m; i++) {
        this->control_list.push_back(vc.control_list[i]);
    }

    return *this; 
}

/**
 * @brief Overload += operator
 * @param vc 
 * @return Controls& 
 */
Controls & Controls::operator+=(const Controls & vc) {
    assert(this->m == vc.m); 
    for (int i = 0; i < this->m; i++) {
        this->control_list[i] += vc.control_list[i];
    }
    return *this;
}

/**
 * @brief Overload -= operator
 * @param vc 
 * @return Controls& 
 */
Controls & Controls::operator-=(const Controls & vc) {
    assert(this->m == vc.m); 
    for (int i = 0; i < this->m; i++) {
        this->control_list[i] -= vc.control_list[i];
    }
    return *this;
}

/**
 * @brief Equality test operator
 * 
 * @param lhs 
 * @param rhs 
 * @return true 
 * @return false 
 */
bool operator==(const Controls & lhs, const Controls & rhs) {
    if (lhs.m != rhs.m) {
        return false; 
    }
    for (int i = 0; i < lhs.m; i++) {
        if (!(lhs.control_list[i] == rhs.control_list[i])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Overload sum operator
 * Compute the sum of controls 
 * @param lhs 
 * @param rhs 
 * @return Controls 
 */
Controls operator+(const Controls & lhs, const Controls & rhs) {
    assert(lhs.m == rhs.m); 
    Controls res(lhs.m);
    for (int i = 0; i < lhs.m; i++) {
        res.control_list[i] = (lhs.control_list[i] + rhs.control_list[i]);
    }
    return res;
}

/**
 * @brief Overload - operator 
 * Compute the difference of two list of controls
 * @param lhs 
 * @param rhs 
 * @return Controls 
 */
Controls operator-(const Controls & lhs, const Controls & rhs) {
    assert(lhs.m == rhs.m); 
    Controls res(lhs.m);
    for (int i = 0; i < lhs.m; i++) {
        res.control_list[i] = (lhs.control_list[i] - rhs.control_list[i]);
    }
    return res;
}

/**
 * @brief Overload standard output stream operrator
 * @param os 
 * @param vc
 * @return std::ostream& 
 */
std::ostream & operator<<(std::ostream & os, const Controls & vc) {
    os << vc.m << "\t" << vc.control_list[0].get_time()->get_dim() << std::endl << std::endl;
    for (int i = 0; i < vc.m; i++) {
        os << vc.control_list[i]; 
        os << std::endl;
    }
    return os;
}