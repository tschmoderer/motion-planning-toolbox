#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem> 
    
#include "../include/header/controltlbx.h"

using namespace std;
namespace fs = std::filesystem;

#define EXP_NB "0"
#define STATE_DIM 3
#define NB_CNTRL 2

VectorXd f_dubin_car(double t, const VectorXd & x, const Controls & u) {
    VectorXd dxdt(STATE_DIM);
    VectorXd cntr(NB_CNTRL);

    cntr = u(t); 

    dxdt[0] = cos(x(2))*cntr(0);
    dxdt[1] = sin(x(2))*cntr(0);
    dxdt[2] = cntr(1);

    return dxdt; 
}

MatrixXd dfdx(double t, const VectorXd & x, const Controls & u) {
    MatrixXd df_dx(STATE_DIM, STATE_DIM);
    VectorXd cntr(NB_CNTRL);

    df_dx = MatrixXd::Zero(STATE_DIM, STATE_DIM);
    cntr = u(t); 

    df_dx(0, 2) = -sin(x(2))*cntr(0);
    df_dx(1, 2) =  cos(x(2))*cntr(0);
    
    return df_dx;
}

MatrixXd dfdu(double t, const VectorXd & x, const Controls & u) {
    MatrixXd df_du(STATE_DIM, NB_CNTRL);
    df_du = MatrixXd::Zero(STATE_DIM, NB_CNTRL);

    df_du(0,0) = sin(x(2));
    df_du(1,0) = cos(x(2));
    df_du(2,2) = 1.;

    return df_du;
}

int main(int argc, char **argv) {
    hello_world_control_tlbx();

    // Put your code here
    // Parameters
    constexpr uint16_t N = STATE_DIM; 
    constexpr uint16_t M = NB_CNTRL; 
    constexpr uint16_t H = 17;
    
    // Caracteristics
    constexpr double t0  = 0; 
    constexpr double t1  = 1;
    constexpr uint16_t T = 129;
    VectorXd x0(N); x0 << 1., 1., M_PI / 4.;

    // Objects
    ControlSystem sys(N, M, t0, t1, x0);
    Controls u(M, t0, t1, H); 
    Interpolator1D   * interpol_cntrl = new Interpolator1D(INTERP_LINEAR, EXTEND_ZERO, EXTEND_ZERO); 
    Integrator1D     * integr_cntrl   = new Integrator1D(H);
    ControlSystemInt * integrator     = new ControlSystemInt(RK4, T);                 

    // Settings
    u.set_interpolation_method(interpol_cntrl);
    u.set_integration_method(integr_cntrl);

    u.set_cntrl(0, 1); 
    //u.set_cntrl(1, 1);

    sys.set_controls(&u); 
    sys.set_cntrl_system_integrator(integrator); 
    sys.set_dynamics(f_dubin_car);
    sys.set_dynamics_derivative_x(dfdx); 
    sys.set_dynamics_derivative_u(dfdu);

    // Control System motion planing part of the program
    constexpr double lambda = 1e-3;
    VectorXd XX1(N); XX1 << 1., 1., 0.;

    VectorXd XX0 = sys.inout();
    cout << "Error norm on first shot: " << (XX1-XX0).norm() << endl;

    // Output
    string dir = argv[0];
    size_t pos = dir.find_last_of('/');
    dir = dir.substr(0, pos);

    string out_dir = dir;

    if (!fs::is_directory(out_dir) || !fs::exists(out_dir)) { 
        fs::create_directory(out_dir); 
    }

    out_dir +=  "/results";
    if (!fs::is_directory(out_dir) || !fs::exists(out_dir)) { 
        fs::create_directory(out_dir); 
    }

    out_dir = out_dir + "/exp_" + EXP_NB;
    if (!fs::is_directory(out_dir) || !fs::exists(out_dir)) { 
        fs::create_directory(out_dir); 
    }

    const static Eigen::IOFormat CSVFormat(Eigen::FullPrecision, Eigen::DontAlignCols, ",", "\n");
    ofstream myfile;
    myfile.open(out_dir + "/trajectory.dat");
    myfile << sys.trajectory().format(CSVFormat);
    myfile.close();

    myfile.open(out_dir + "/control.dat");
   // myfile << (*u).format(CSVFormat);
    myfile.close();

    // Define path 
    Path pi(XX0, XX1); 

    // Clean memory
    delete interpol_cntrl;
    delete integr_cntrl;
    delete integrator;

    // End code
    return 0;
}