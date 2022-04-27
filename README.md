<div id="motion-planning-toolbox-logo" align="center">
    <br />
    <img src="#" alt="Motion Planning ToolBox Logo" width="200"/>
    <h1>Motion Planning Toolbox</h1>
    <h3></h3>
</div>

[![build](https://github.com/tschmoderer/motion-planning-toolbox/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/tschmoderer/motion-planning-toolbox/actions/workflows/cmake.yml) [![docs](https://github.com/tschmoderer/motion-planning-toolbox/actions/workflows/doxygen.yml/badge.svg?branch=main)](https://tschmoderer.github.io/motion-planning-toolbox/html/index.html) [![License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://github.com/tschmoderer/motion-planning-toolbox/blob/master/LICENSE)



A C++ toolbox for the computation of trajectories of control systems.



The library contains a sublibrary of linear algebra developped by myself. 



# Improvements
* In *linalg* library use inheritance of class to avoid unecessary code ;
  * For the moment I do not know how to properly use polymorphism with operators.
* In *linalg* library bind with a BLAS implementation ;

# Install & Building



## Unix 

Require cmake & g++

Optional valgrind for memcheck

```bash
git clone https://github.com/tschmoderer/motion-planning-toolbox.git 
cd motion-planning-toolbox
mkdir build
cd build
cmake ..
make
make test
(Opt) make memcheck
```