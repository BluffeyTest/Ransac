#安装路径
# install_files(include/struct2d 
#     Point.hpp)

# install(
#     FILES 
#     Point.hpp
#     DESTINATION
#     ${CMAKE_INSTALL_INCLUDEDIR})


install(FILES 
        Point.hpp
        Arc.hpp
        Circle.hpp
        Ellipse.hpp
        EllipseNormal.hpp
        Line.hpp
        SegmentLine.hpp
        Struct2d.hpp
        #TYPE INCLUDE 
        DESTINATION ${INSTALL_INCLUDE_DIR}/struct2d
        )