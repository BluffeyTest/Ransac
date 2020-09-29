# Ransac
a ransac algorithm for fitting 2d or 3d geometry，just like line, circle, and ellipse，plane。</br>
用ransac算法拟合2d或3d几何图形，如圆，直线，椭圆，平面等。</br>

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
and then, add the line to your `CMakeLists.txt`:</br>
然后，在`CMakeLists.txt`添加如下行：
```
find_package(Ransac REQUIRED)
include_directories(${Ransac_INCLUDE_DIRS})
target_link_libraries(your_excutable_name  ${Ransac_LIBRARIES})
```
or just copy all files to your path, and you could use these file just like your own file.


### other things
### 别的事
you can use `opencv`'s 2d Point and 3d Point to instead this files 2d Point and 3d Point, it means, you can just use the ``