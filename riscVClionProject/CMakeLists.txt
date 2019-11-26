cmake_minimum_required(VERSION 3.14)
project(riscVClionProject)

set(CMAKE_CXX_STANDARD 14)


add_executable(riscVClionProject main.cpp Emulator.cpp Instructions.cpp Memory.cpp Memory.h)