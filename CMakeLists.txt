cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11")

project(Ransac)

add_library(Ransac Struct2d.cpp Struct3d.cpp Ransac.cpp)
#add_executable(testRansac testRansac.cpp Ransac.cpp Struct2d.cpp Struct3d.cpp)
add_executable(testRansac testRansac.cpp)
target_link_libraries(testRansac Ransac)


#add_executable()