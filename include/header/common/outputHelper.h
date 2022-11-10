/**
* @file outputHelper.h
* @author T. Schmoderer (iathena@mailo.com)
* @version 0.5.0
* @date 2022-11-10
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

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem> 

using Eigen::VectorXd;
using Eigen::MatrixXd;

/* NAMESPACES */
using namespace std;
namespace fs = std::filesystem;

/* COMMON FORMAT */
const static Eigen::IOFormat CSVFormat(Eigen::FullPrecision, Eigen::DontAlignCols, ",", "\n");

/* CUSTOM TYPE */
enum plot_type_t : uint8_t {
    phase, 
    coordinate
};

enum out_t : uint8_t {
    trajectory, 
    control
};

/**
 * @brief A class to standartize the output format of 
 * - Controls
 * - Trajectories
 * @todo Add more object support
 */
class OutputHelper {
    public: 
        /* CONSTRUCTORS */
        OutputHelper(const Controls & , string = "./control.dat", string = "./time.dat"); 
        OutputHelper(const Trajectory & , string = "./trajectory.dat", string = "./time.dat");

        /* DESTRUCTOR */
        ~OutputHelper();

        /* ACCESSORS */
        OutputHelper format(Eigen::IOFormat ); 

        /* METHODS */
        void save(int ) const;
        
        /* OPERATORS */
        friend std::ostream & operator<<(std::ostream & , const OutputHelper & );

    private:
        /* ATTRIBUTES */
        Eigen::IOFormat fmt = Eigen::IOFormat();
        VectorXd time_;
        MatrixXd data_;

        out_t type_t; 

        // output directory
        string out_dir_;

        // data file info
        string out_file_;
        string filename_;
        string fileext_;

        // timestamps data file info
        string ts_out_file_;
        string ts_filename_;
        string ts_fileext_;

        /* PRIVATE METHOD */
        MatrixXd make_data() const; 
        void set_output_structure(const string );
        void set_output_structure_ts(const string );
        void create_output_dir() const; 
        string exp_filename(int ) const;
        string exp_filename_ts(int ) const;
};

#endif
