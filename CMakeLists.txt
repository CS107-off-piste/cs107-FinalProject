cmake_minimum_required(VERSION 3.17)
project(cs107_FinalProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(cs107_FinalProject main.cpp src/BinaryOperator.hpp src/UnaryOperator.hpp src/Node.hpp src/Graph.hpp src/ForwardFunctions.hpp src/Graph.cpp src/BackwardFunctions.hpp src/Variable.hpp)