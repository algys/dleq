cmake_minimum_required(VERSION 3.9)
project(dleq)

set(CMAKE_CXX_STANDARD 14)

include_directories(/lib/)
add_executable(dleq main.cpp Proof.hh ecc.hh lib/BigInt.hpp Ecc.hh)