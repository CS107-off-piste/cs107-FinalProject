cmake_minimum_required(VERSION 3.17)
project(cs107_FinalProject)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(./src SRC_DIR)

add_executable(cs107_FinalProject main.cpp ${SRC_DIR})