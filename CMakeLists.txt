cmake_minimum_required(VERSION 3.22)
project(voxlang
  LANGUAGES CXX
  VERSION 0.1
  DESCRIPTION "Pre-release")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(spdlog REQUIRED)
find_package(argparse REQUIRED)

set(vox_hds
  src/vm.h
  src/chunk.h
  src/config.h
  src/common.h
  )

set(vox_srcs
  src/vm.cpp
  src/chunk.cpp
  src/main.cpp)

add_executable(voxlang ${vox_srcs} ${vox_hds})

target_link_libraries(voxlang spdlog::spdlog)
target_link_libraries(voxlang argparse::argparse)
