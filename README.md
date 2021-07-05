# Ransac
a ransac algorithm for fitting 2d or 3d geometry，just like line, circle, and ellipse，plane。</br>
用ransac算法拟合2d或3d几何图形，如圆，直线，椭圆，平面等。</br>
now ,add more Geometry computition in it.</br>
现在里面添加了更多的与计算集合相关的运算。</br>

##  install and use 
##  安装与使用

### for Windows

I don't debug it now!</br>
我还没调试确保能用，但问题应该不大。</br>

download the git repository, add the path to your `include` path, and copy the `Ransac.dll` to your project path.</br>
下载git仓库，将其中的文件夹添加到你的`include`文件夹，然后，拷贝`Ransac.dll`文件到你的工作目录即可。 

### for Linux
#### ubuntu

```
git clone https://github.com/BluffeyTest/Ransac.git
```

and then,to make and install it.</br>
然后，生成并安装。</br>
```
cd Ransac
mkdir build
cmake ..
make
sudo make install
```
the default install dir like this,if the first time install ,the `Up-to-date` will show as `Installing`.</br>
默认的安装路径像是这样，如果是第一次安装的话，`Up-to-date` 的地方显示的是 `Installing`</br>
```
-- Install configuration: "Release"
-- Up-to-date: /usr/local/lib/Ransac/libRansac.a
-- Up-to-date: /usr/local/include/Ransac/Point.hpp
-- Up-to-date: /usr/local/include/Ransac/Line.hpp
-- Up-to-date: /usr/local/include/Ransac/SegmentLine.hpp
-- Up-to-date: /usr/local/include/Ransac/Circle.hpp
-- Up-to-date: /usr/local/include/Ransac/Arc.hpp
-- Up-to-date: /usr/local/include/Ransac/Ellipse.hpp
-- Up-to-date: /usr/local/include/Ransac/EllipseNormal.hpp
-- Up-to-date: /usr/local/include/Ransac/Struct2d.hpp
-- Up-to-date: /usr/local/include/Ransac/Struct3d.h
-- Up-to-date: /usr/local/include/Ransac/Ransac.h
-- Up-to-date: /usr/local/lib/cmake/Ransac/ransac-config.cmake
-- Up-to-date: /usr/local/lib/cmake/Ransac/ransac-config-release.cmake
```
and then, add the line to your `CMakeLists.txt`,in your project:</br>
然后，在你的项目中的`CMakeLists.txt`添加如下行：
```
find_package(Ransac REQUIRED)
include_directories(${Ransac_INCLUDE_DIRS})
target_link_libraries(your_excutable_name  ${Ransac_LIBRARIES})
```
or just copy all files to your path, and you could use these file just like your own file.


### other things
### 别的事
