cmake_minimum_required(VERSION 3.19)
project(HeatEquation)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        HeatEquation
        main.cpp
        src/KMB/KMB.cpp
        src/KMB/KMB.h
        src/calerf.h
        src/calerf.cpp
        src/Iterative_Methods/Thomas/thomas.cpp
        src/Iterative_Methods/Thomas/thomas.h
        src/Iterative_Methods/Gauss-Seidel/GaussSeidel.cpp
        src/Iterative_Methods/Gauss-Seidel/GaussSeidel.h
        src/Laasonen/laasonen.cpp
        src/Laasonen/laasonen.h
        src/analytic/analytic.cpp
        src/analytic/analytic.h
        src/tools/save.cpp
        src/tools/tools.h
        src/tools/fill.cpp
        src/analytic/analytic.h
        src/tools/max_error.cpp
)

