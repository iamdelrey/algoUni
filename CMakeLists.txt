cmake_minimum_required(VERSION 3.0.0)
project(algoUni VERSION 0.1.0 LANGUAGES C CXX)
add_definitions(-std=c++20)
include(CTest)
enable_testing()

#add_executable(algoUni pr3/distanceCounter.cpp)
add_executable(algoUni pr3/boyerMooreTurbo.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)