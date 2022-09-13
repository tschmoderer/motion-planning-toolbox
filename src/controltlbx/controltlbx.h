#ifndef CONTROLTLBX_H
#define CONTROLTLBX_H

#include "stdlib.h"
#include "control.h"
#include "controls.h"
#include "controlSystem.h"
#include "vector.h"

#define VERSION_MPP_TLBX "0.0.0"
#define AUTHOR "T. SCHMODERER/BOHEME"
#define CONTACT "iathena@mailo.com"
#define DOCUMENTATION "https://tschmoderer.github.io/motion-planning-toolbox/html/index.html"

/**
* @brief 
* 
*/
void hello_world_control_tlbx() {
    std::cout << "Welcome to Motion Planning Toolbox" << std::endl;
    std::cout << "Version       : " << VERSION_MPP_TLBX << std::endl;
    std::cout << "Documentation : " << DOCUMENTATION << std::endl; 
    std::cout << "Contact       : " << CONTACT << std::endl; 
    std::cout << "--" << std::endl;
}

#endif