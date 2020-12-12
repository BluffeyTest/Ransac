/******************************************************************************
 * @file Point2d.hpp
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

#ifndef POINT2D_HPP
#define POINT2D_HPP

#include "Point.hpp"
#include "Point2f.hpp"

/**
 * @brief 双精度浮点型二维点
 * 
 */
typedef
struct Point2d
{
	double x;
	double y;

	Point2d() : x(0.0), y(0.0) {}

	Point2d(int _x, int _y) : x((double)_x), y((double)_y) {}
	Point2d(float _x, float _y) : x(_x), y(_y) {}
	Point2d(double _x, double _y) : x(_x), y(_y) {}

	Point2d(Point2i _p2i) : x((double)_p2i.x), y((double)_p2i.y) {}
	Point2d(Point2f _p2f) : x((double)_p2f.x), y((double)_p2f.y) {}

	friend std::ostream & operator<<(std::ostream &os, /*const*/ Point2d &pt);

    /******************************************************************************
     * @brief 向量与x轴的夹角
     * @return double 
     ******************************************************************************/
    inline double Angle() const
    {
        return atan2(this->y,this->x);
    }

    /****************************************************************
     * @brief 点进行旋转
     * 
     * @param dAngle 旋转角度，弧度制
     * @param pOri 旋转中心
     * @return double 
    *****************************************************************/
    inline Point2d Rotate(double dAngle,const Point2d &pOri = Point2d(0.0,0.0)) const
    {
        return Point2d((x-pOri.x)*cos(dAngle) - (y-pOri.y)*sin(dAngle),
                    (x-pOri.x)*sin(dAngle)+(y-pOri.y)*cos(dAngle)
        );
    }

    /**
     * @brief Point2d加法
     * 
     * @param pt 
     * @return Point2d 
     */
    inline Point2d operator+(const Point2d &pt) const
    {
        return Point2d(this->x + pt.x, this->y + pt.y);
        
    }

    /**
     * @brief Point2d减法
     * 
     * @param pt 
     * @return Point2d 
     */
    inline Point2d operator-(const Point2d &pt) const
    {
        return Point2d(this->x - pt.x, this->y - pt.y);
    }

    /**
     * @brief Point2d比较是否相等</br>
     * 
     * @param pt 
     * @return bool 
     */
    inline bool operator==(const Point2d &pt) const
    {
        const double eps = 1e-6;//double的精度有15位，算上整数位，所以问题小一些
        return (fabs(this->x - pt.x)<eps && fabs(this->y - pt.y)<eps );
    }

    friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2d &pt)
    {
        os<<"( "<<pt.x<<", "<<pt.y<<" )";
        return os;
    }
} Pointd;


typedef Point2d vec2d;
typedef vec2d	vec;




#endif //!POINT2D_HPP







