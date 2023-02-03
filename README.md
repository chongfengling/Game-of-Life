PHAS0100ASSIGNMENT1
------------------

Purpose
-------

This project serves as a starting point for the PHAS0100 2022/23 Assignment 1 Game of Life Simulation coursework. It has a reasonable folder structure for [CMake](https://cmake.org/) based projects that use [CTest](https://cmake.org/) to run unit tests via [Catch](https://github.com/catchorg/Catch2). 

Further information on the specific project is left as an exercise for the student.

Credits
-------

This project is maintained by [Dr. Jamie Quinn](http://jamiejquinn.com/). It is based on [CMakeCatch2](https://github.com/UCL/CMakeCatch2.git) that was originally developed as a teaching aid for UCL's ["Research Computing with C++"](https://github-pages.ucl.ac.uk/research-computing-with-cpp/) course developed by [Dr. James Hetherington](http://www.ucl.ac.uk/research-it-services/people/james) and [Dr. Matt Clarkson](https://iris.ucl.ac.uk/iris/browse/profile?upi=MJCLA42).

Build Instructions
------------------

To run cmake:

```
cmake -B build
```

To compile:

```
cmake --build build
```

To test:

```
cd build
ctest
```

Additional build and running instructions left to the student.
