/******************************************************************************
 * @file Struct2d.hpp
 * @brief 
 * @author Bluffey (Bluffey@163.com)
 * @version 1.0
 * @date 2020-11-06
 * 
 * @copyright Copyright (c) 2020  成都云裁科技有限公司
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-11-06 <td>1.0     <td>wangh     <td>内容
 * </table>
 ******************************************************************************/

#ifndef STRUCT2D_HPP
#define STRUCT2D_HPP

/// 包含点的文件
#include "Point.hpp"

/// 包含直线和线段的文件
#include "Line.hpp"
#include "SegmentLine.hpp"


/// 包含圆和圆弧的文件
#include "Circle.hpp"
#include "Arc.hpp"

/// 包含椭圆的两个版本的文件
#include "Ellipse.hpp"
#include "EllipseNormal.hpp"


inline double Distance(Point &pt1, Point &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

inline double Distance(Point2d &pt1, Point2d &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}





#endif //!STRUCT2D_HPP