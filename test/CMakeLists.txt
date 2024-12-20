cmake_minimum_required(VERSION 3.0) # cmake -G "MinGW Makefiles" ...
project(GTESTWIN_TEST)

SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

#gtest库相关
#如果把gtest放到test目录下,则使用如下包含关系:
add_subdirectory(googletest-1.15.2) # 编译gtest
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest-1.15.2/googletest/include) # 包含gtest等头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest-1.15.2/googlemock/include) # 包含gmock等头文件

# 头文件目录
include_directories("../include")

# 源文件目录
AUX_SOURCE_DIRECTORY("../" SRCs)

# 测试代码目录
AUX_SOURCE_DIRECTORY("." TEST_SRCs)

# 排除gtest代码
list(REMOVE_ITEM TEST_SRCs ${CMAKE_CURRENT_SOURCE_DIR}/googletest-1.15.2/googletest/src/gtest-all.cc)
list(REMOVE_ITEM TEST_SRCs ${CMAKE_CURRENT_SOURCE_DIR}/googletest-1.15.2/googlemock/src/gmock-all.cc)

foreach(TEST_SRC ${TEST_SRCs})
    get_filename_component(TEST_SRC_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_SRC_NAME} ${TEST_SRC})

    # 链接测试库 pthread 库一定要写在${GTEST_BOTH_LIBRARIES}的后面否则编译时会报错,
    # GTEST BOTH LIBRARIES表示链接google test的两个库
    set(GTEST_BOTH_LIBRARIES gtest gtest_main gmock gmock_main)
    target_link_libraries(${TEST_SRC_NAME} PRIVATE ${GTEST_BOTH_LIBRARIES} pthread gcov)
endforeach(TEST_SRC ${TEST_SRCs})