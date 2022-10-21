/**
* @file controltlbx.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-21
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief Main file for the control toolbox library
*/

#ifndef CNTRLTLBX_H
#define CNTRLTLBX_H

#include "utils.h"
#include "controller/controls.h"
#include "systems/controlSystem.h"
#include "path/path.h"
#include "common/outputHelper.h"

/* VERSION MACROS */
#define VERSION_MPP_TLBX "0.0.3"
#define AUTHOR_MPP_TLBX "T. Schmoderer"
#define CONTACT_MPP_TLBX "iathena@mailo.com"
#define DOCUMENTATION_MPP_TLBX "https://tschmoderer.github.io/motion-planning-toolbox/html/index.html"
#define CODE_MPP_TLBX "https://github.com/tschmoderer/motion-planning-toolbox"

/**
* @brief 
* 
*/
void hello_world_control_tlbx() {
    std::cout << "Welcome to Motion Planning Toolbox" << std::endl;
    std::cout << "Version       : " << VERSION_MPP_TLBX << std::endl;
    std::cout << "Code          : " << CODE_MPP_TLBX << std::endl;
    std::cout << "Documentation : " << DOCUMENTATION_MPP_TLBX << std::endl; 
    std::cout << "Contact       : " << AUTHOR_MPP_TLBX  << " - " << CONTACT_MPP_TLBX << std::endl; 
    std::cout << "--" << std::endl;
}

#endif
