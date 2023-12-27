cmake_minimum_required(VERSION 3.27)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(CHIMERA-001-P-A
        VERSION 0.1.0
)

# Target CXX standard for the project
set(CMAKE_CXX_STANDARD 23)

# This project uses Unity Builds for all targets,
# regardless of build type
set(CMAKE_UNITY_BUILD TRUE)