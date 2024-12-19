cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(ceditor)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 指定头文件目录
include_directories(${PROJECT_SOURCE_DIR}/components)
include_directories(${PROJECT_SOURCE_DIR}/mystl)
include_directories(${PROJECT_SOURCE_DIR}/utils)

# 查找所有源文件
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.cpp")

# 排除测试源文件
list(FILTER SOURCES EXCLUDE REGEX ".*_test.cpp$")

# 创建可执行文件
add_executable(ceditor main.cpp)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)