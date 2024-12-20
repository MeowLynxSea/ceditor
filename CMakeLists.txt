cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER "E:\\mingw64\\bin\\g++.exe")

project(CEditor)

set(CMAKE_CXX_STANDARD 11)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include/")

AUX_SOURCE_DIRECTORY(./src src_files)

add_executable(CEditor ./src/main ${src_files})

add_subdirectory(test)