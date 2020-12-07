cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-std=c++11")

project(Ransac VERSION 1.1.0)

#
add_subdirectory(./struct2d)
add_subdirectory(./struct3d)

#
aux_source_directory(./struct2d STRUCT2D_SRC)
aux_source_directory(./struct3d STRUCT3D_SRC)

aux_source_directory(. RANSAC_SRCS)
aux_source_directory(. RANSAC_INCLUDE)
aux_source_directory(. RANSAC_LIB_SRCS)

#设置可执行文件的输出路径
set(EXECUTABLE_OUTPUT_PATH ../bin)

#设置库的输出路径
set(LIBRARY_OUTPUT_PATH ../lib)

#设置包的
#SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
SET(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_library(Ransac ${STRUCT2D_SRC} ${STRUCT3D_SRC} Ransac.cpp)
#add_executable(testRansac testRansac.cpp Ransac.cpp Struct2d.cpp Struct3d.cpp)
add_executable(testRansac testRansac.cpp)
target_link_libraries(testRansac Ransac)

#设置这个库的输出名称为


# 指定 Ransac 库的安装路径
install(TARGETS Ransac DESTINATION bin)
install(FILES Ransac.h Struct2d.h Struct3d.h DESTINATION include)

# 指定安装路径
install(TARGETS Ransac DESTINATION lib)