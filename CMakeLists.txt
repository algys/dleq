cmake_minimum_required(VERSION 3.9)
project(dleq)

set(CMAKE_CXX_STANDARD 14)

add_executable(dleq main.cpp Proof.hh Ecc.hh)