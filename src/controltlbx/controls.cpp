#include "controls.h"

Controls::Controls() {
    this->m = 0;
}

Controls::Controls(uint8_t m) {
    this->m = m; 
    for (int i = 0; i < m; i++) {
        this->control_list.push_back(Control());
    }
}

Controls::~Controls() {}

Control Controls::operator[](uint8_t idx) const {
    assert(idx < this->m);
    return this->control_list[idx];
}

Vector Control::get_data(uint8_t ctrl_nb) const {
    assert(ctrl_nb >= 0); assert(ctrl_nb < this->m); 
    Vector res(this->N); 
    for (int i = 0; i < this->N; i++) {
        res[i] = this->data(ctrl_nb, i); 
    }
    return res; 
}