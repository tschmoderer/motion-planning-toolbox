<div id="motion-planning-toolbox-logo" align="center">
    <br />
    <img src="https://raw.githubusercontent.com/tschmoderer/motion-planning-toolbox/main/docs/img/icons/128x128/rocket.png" alt="Motion Planning ToolBox Logo" width="128" id="motion-planning-toolbox-logo-img"/>
    <h1>Motion Planning Toolbox</h1>
    <h3></h3>
</div>


[![language-cpp](https://img.shields.io/badge/language-C%2B%2B-blue)](https://github.com/tschmoderer/motion-planning-toolbox/search?l=c%2B%2B&type=code)  [![build](https://github.com/tschmoderer/motion-planning-toolbox/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/tschmoderer/motion-planning-toolbox/actions/workflows/cmake.yml) [![docs](https://github.com/tschmoderer/motion-planning-toolbox/actions/workflows/doxygen.yml/badge.svg?branch=main)](https://tschmoderer.github.io/motion-planning-toolbox/html/index.html) [![License](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://github.com/tschmoderer/motion-planning-toolbox/blob/master/LICENSE) [![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/tschmoderer/motion-planning-toolbox?label=Version)](https://github.com/tschmoderer/motion-planning-toolbox/releases)


A C++ toolbox for the computation of trajectories of control systems.

# Improvements
* In *linalg* library use inheritance of class to avoid unecessary code ;
  * For the moment I do not know how to properly use polymorphism with operators.
* In *linalg* library bind with a BLAS implementation ;

# Install & Building

## Requierement 
* Eigen 

```bash
sudo apt install libeigen3-dev
```



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

## Credits

Portions of this software are copyright of their respective authors :

- Documentation theme is made by [jothepro](https://github.com/jothepro/doxygen-awesome-css) - MIT License
- Icon is *rocket.svg* distributed by [lucide](https://github.com/lucide-icons/lucide) - ISC License
- Linear Algebra library is [Eigen](https://eigen.tuxfamily.org/) - Apache License