#include <iostream>
#include <fstream>
#include "control.h"

int main(int argc, char * argv[]) {
    Control c1(1, 0., 1., 10); 
    
    std::ofstream f;
    f.open ("./examples/ex_control_2_output.dat");
    f << c1;
    f.close();

    return 0;
}