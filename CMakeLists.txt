cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-std=c++11")

project(Ransac VERSION 1.1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add local path for finding packages, set the local version first
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

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
#add_library(Ransac SHARED ${STRUCT2D_SRC} ${STRUCT3D_SRC} Ransac.cpp)
#add_executable(testRansac testRansac.cpp Ransac.cpp Struct2d.cpp Struct3d.cpp)
add_executable(testRansac testRansac.cpp)
target_link_libraries(testRansac Ransac)

#设置这个库的输出名称为

set(Ransac_HEADER_FILES
  struct2d/Point.hpp
  #struct2d/Point2f.hpp
  #struct2d/Point2d.hpp
  struct2d/Line.hpp
  struct2d/SegmentLine.hpp
  struct2d/Circle.hpp
  struct2d/Arc.hpp
  struct2d/Ellipse.hpp
  struct2d/EllipseNormal.hpp
  struct2d/Struct2d.hpp
  struct3d/Struct3d.h
  Ransac.h
)

install(
  FILES ${Ransac_HEADER_FILES}
  DESTINATION include/Ransac
)

message("include dir is:${CMAKE_INSTALL_INCLUDEDIR}")

# 指定 Ransac 库的安装路径
#install(TARGETS Ransac DESTINATION bin)
#install(FILES Ransac.h DESTINATION include/Ransac)
#install(FILES S2D DESTINATION include/Ransac/struct2d/)
#install(FILES struct3d/*.hpp DESTINATION include/Ransac/struct3d/)


# 指定安装路径
#install(TARGETS Ransac DESTINATION Racnsac/lib)


# install(TARGETS Ransac 
#         EXPORT RansacTargets
#         LIBRARY DESTINATION lib/Ransac
#         ARCHIVE DESTINATION lib/Ransac
#         RUNTIME DESTINATION bin/Ransac
#         PUBLIC_HEADER DESTINATION include/Ransac
#         )

#install(FILES "struct2d/*.hpp" )