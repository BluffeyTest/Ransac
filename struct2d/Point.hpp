/******************************************************************************
 * @file Point.hpp
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

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

/// PI
#define PI	3.1415926535897932384626433832795

struct Point2i;



/**
 * @brief 整形二维点
 * 
 */
typedef
struct Point2i
{
	int x;
	int y;

	Point2i() : x(0), y(0) {}

	Point2i(int _x, int _y) : x(_x), y(_y) {}
	Point2i(float _x, float _y) : x((int)(_x + 0.5)), y((int)(_y + 0.5)) {}
	Point2i(double _x, double _y) : x((int)(_x + 0.5)), y((int)(_y + 0.5)) {}


	bool operator||(const Point2i &pt)const;	///<两个向量是否方向相同

	friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2i &pt);

    /******************************************************************************
     * @brief 向量与x轴的夹角
     * @return double 
     ******************************************************************************/
    inline double Angle() const
    {
        return atan2f((float)this->y,(float)this->x);
    }
    
    /**
     * @brief 向量或点绕中心点旋转
     * 
     * @param dAngle 旋转角度，弧度制
     * @param pOri 原点
     * @return Point2i 
     */
    inline Point2i Rotate(double dAngle,const Point2i &pOri) const
    {
        return Point2i((x-pOri.x)*cos(dAngle) - (y-pOri.y)*sin(dAngle) + 0.5,
                    (x-pOri.x)*sin(dAngle)+(y-pOri.y)*cos(dAngle) + 0.5
        );
    }

    /**
     * @brief Point2i加法
     * 
     * @param pt 相加的点
     * @return Point2i 
     */
    inline Point2i operator+(const Point2i &pt) const
    {
        return Point2i(this->x + pt.x, this->y + pt.y);
    }

    /**
     * @brief Point2i减法
     * 
     * @param pt 
     * @return Point2i 
     */
    inline Point2i operator-(const Point2i &pt) const
    {
        return Point2i(this->x - pt.x, this->y - pt.y);
    }

    /**
     * @brief Point2i判断是否相等
     * 
     * @param pt 
     * @return false 不相等
     * @return true 相等
     */
    inline bool operator==(const Point2i &pt) const
    {
        return (this->x == pt.x && this->y == pt.y);
    }

    /**
     * @brief 重载点的输出运算符
     * 
     */
    friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2i &pt)
    {
        os<<"( "<<pt.x<<", "<<pt.y<<" )";
        return os;
    }
} Point;

typedef Point2i vec2i;




#endif //!POINT_HPP