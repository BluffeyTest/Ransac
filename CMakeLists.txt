cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "-std=c++11")

project(Ransac)

add_executable(testRansac testRansac.cpp Ransac.cpp Struct2d.cpp Struct3d.cpp)



#add_executable()