/**
 * @file Struct2d.h
 * @author Bluffey (Bluffey@163.com.com)
 * @brief 二维平面结构体
 * @version 0.1
 * @date 2020-08-18
 * @note inline 的成员函数的生命和定义需要卸载同一个文件里，不然无法链接
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once
#ifndef STRUCT2D_H
#define STRUCT2D_H





//两点距离
double Distance(Point &pt1, Point &pt2);
double Distance(Point2d &pt1, Point2d &pt2);










#endif // !STRUCT2D_H
