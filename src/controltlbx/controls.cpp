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