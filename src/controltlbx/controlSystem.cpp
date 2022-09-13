#include "controlSystem.h"

ControlSystem::ControlSystem() {
    this->state_dim = 0;
    this->cntrl_dim = 0;

    this->x0 = Vector();
    this->t0 = 0.;
    this->t1 = 0.;

    

    this->f = NULL;
    this->dfdx = NULL;
    this->dfdu = NULL;
}