#include "../include/header/controls.h"

/* CONSTRUCTORS */

/**
 * @brief Construct a new Controls:: Controls object
 * Create a list of nb default Control object
 * @param nb 
 */
Controls::Controls(uint8_t nb) {    
    this->m = nb; 
    for (int i = 0; i < this->m; i++) {
       this->control_list.push_back(Control()) ; 
    }
}

/**
 * @brief Construct a new Controls:: Controls object
 * Create a list of nb controls object that are copy of the Control c
 * @param nb 
 * @param c 
 */
Controls::Controls(uint8_t nb, Control c) {
    this->m = nb; 
    for (int i = 0; i < this->m; i++) {
       this->control_list.push_back(Control(c)) ; 
    }
}

/* DESTRUCTOR */
Controls::~Controls() {}

/* ACCESSORS */
void Controls::set_t0(double t0) {
    for (int i = 0; i < this->m; i++) {
        this->control_list[i].set_t0(t0); 
    }
} 

void Controls::set_t1(double t1) {
    for (int i = 0; i < this->m; i++) {
        this->control_list[i].set_t1(t1); 
    }
}

void Controls::set_N(uint16_t N) {
    for (int i = 0; i < this->m; i++) {
        this->control_list[i].set_N(N); 
    }
}

void Controls::set_discretisation(double t0, double t1, uint16_t N) {
    for (int i = 0; i < this->m; i++) {
        this->control_list[i].set_discretisation(t0, t1, N); 
    }
}


/* OPERATORS */
std::ostream & operator<<(std::ostream & os, const Controls & cs) {
    for (int i = 0; i < cs.m; i++) {
        os << "Control : #" << i+1 << std::endl; 
        os << cs.control_list[i]; 
        os << std::endl; 
    }
    return os; 
}