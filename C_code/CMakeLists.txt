cmake_minimum_required(VERSION 3.21)
project(C_code)

set(CMAKE_CXX_STANDARD 14)

add_executable(C_code main.cpp Network.cpp Network.h Vector.cpp Vector.h Matrix.cpp Matrix.h ActivationFunction.cpp ActivationFunction.h Source.cpp Source.h)
