cmake_minimum_required(VERSION 3.23)
project(voxlang)

set(CMAKE_CXX_STANDARD 20)


set(vox_hds
  src/vm.h
  src/chunk.h
  src/common.h)

set(vox_srcs
  src/vm.cpp
  src/chunk.cpp
  src/main.cpp)

add_executable(voxlang ${vox_srcs} ${vox_hds})
