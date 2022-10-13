/**
 * @file controltlbx.h
 * @author T. Schmoderer (iathena@mailo.com)
 * @brief Main Header file for Control System Library
 * @version 1.0
 * @date 2022-09-13
 * @copyright Copyright (c) 2022
 */

#ifndef CONTROLTLBX_H
#define CONTROLTLBX_H

#include "stdlib.h"
#include "control.h"
#include "controls.h"
#include "controlSystem.h"
#include "linalg.h"

/* VERSION MACROS */
#define VERSION_MPP_TLBX "0.0.0"
#define AUTHOR_MPP_TLBX "T. SCHMODERER/BOHEME"
#define CONTACT_MPP_TLBX "iathena@mailo.com"
#define DOCUMENTATION_MPP_TLBX "https://tschmoderer.github.io/motion-planning-toolbox/html/index.html"

/**
* @brief 
* 
*/
void hello_world_control_tlbx() {
    std::cout << "Welcome to Motion Planning Toolbox" << std::endl;
    std::cout << "Version       : " << VERSION_MPP_TLBX << std::endl;
    std::cout << "Documentation : " << DOCUMENTATION_MPP_TLBX << std::endl; 
    std::cout << "Contact       : " << AUTHOR_MPP_TLBX  << " : " << CONTACT_MPP_TLBX << std::endl; 
    std::cout << "--" << std::endl;
}

#endif