cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "-std=c++11")

#设置总的安装路径
SET(CMAKE_INSTALL_PREFIX /usr/local/Ransac)
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)

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

add_library(Ransac SHARED ${STRUCT2D_SRC} ${STRUCT3D_SRC} Ransac.cpp)
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

#message("include dir is:${CMAKE_INSTALL_INCLUDEDIR}")
message("include dir is:${CMAKE_PREFIX_PATH}")


# 设置被安装的源文件目录和目标目录，但是好像并不需要
target_include_directories(Ransac PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/struct2d>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/struct2d>)

target_include_directories(Ransac PUBLIC
    $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/struct3d>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include/struct3d>)

#设置被安装的公共头文件
# set_target_properties(Ransac PROPERTIES PUBLIC_HEADER 
#     "${Ransac_HEADER_FILES}")

#message("the heders is ${Ransac_HEADER_FILES}")

set_target_properties(Ransac
  PROPERTIES
  POSITION_INDEPENDENT_CODE 1
  SOVERSION ${PROJECT_VERSION_MAJOR}
  OUTPUT_NAME "Ransac"
  DEBUG_POSTFIX "_d"
  Ransac_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include
  PUBLIC_HEADER "Ransac.h"
  MACOSX_RPATH ON
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

#安装头文件、库文件
# install(TARGETS Ransac 
#         EXPORT ransac-targets
#         LIBRARY DESTINATION lib#/Ransac
#         ARCHIVE DESTINATION lib#/Ransac
#         RUNTIME DESTINATION bin#/Ransac
#         PUBLIC_HEADER DESTINATION include/Ransac
#         )


install(TARGETS Ransac 
        EXPORT ransac-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        #PUBLIC_HEADER DESTINATION include/Ransac
        )

#set(STRUCT2D_HEADERS ./struct2d/Point.hpp)


#安装用于寻找头文件和库文件的cmake文件
#注意ransac-config.cmake的包名必须小写
install(EXPORT ransac-targets
    NAMESPACE Ransac::
    FILE ransac-config.cmake
    DESTINATION lib/cmake)

#注意RansacConfig.cmake的包名必须小写
install(EXPORT ransac-targets
    NAMESPACE Ransac::
    FILE RansacConfig.cmake
    DESTINATION lib/cmake)
