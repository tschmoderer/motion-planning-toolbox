/**
* @file outputHelper.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.0.3
* @date 2022-10-21
* @copyright Copyright (c) 2022. All rights reserved. This project is released under the GNU GENERAL PUBLIC LICENSE.
*/
/**
 * @brief
*/

#ifndef CONTROLTLBX_OUTPUTHELPER_H
#define CONTROLTLBX_OUTPUTHELPER_H

#include <Eigen/Dense>
#include "../controller/controls.h"
#include "../types/trajectory.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

/**
 * @brief A class to standartize the output format of 
 * - Controls
 * - Trajectories
 * @todo Add more object support
 */
class OutputHelper {
    public: 
        /* CONSTRUCTORS */
        OutputHelper(const Controls & ); 
        OutputHelper(const Trajectory & );

        /* DESTRUCTOR */
        ~OutputHelper();

        /* ACCESSORS */
        void format(Eigen::IOFormat ); 

        /* OPERATORS */
        friend std::ostream & operator<<(std::ostream & , const OutputHelper & );

    private:
        Eigen::IOFormat fmt = Eigen::IOFormat();
        VectorXd time_;
        MatrixXd data_;
};

#endif
