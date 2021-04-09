/******************************************************************************
 * @file Point2f.hpp
 * @brief 换成模板点后已经弃用
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

#ifndef POINT2F_HPP
#define POINT2F_HPP

#include "Point.hpp"


/**
 * @brief 单精度浮点型二维点
 * 
 */
// typedef
// struct Point2f
// {
// 	float x;
// 	float y;

// 	Point2f() : x(0.f), y(0.f) {}

// 	Point2f(int _x, int _y) : x((float)_x), y((float)_y) {}
// 	Point2f(float _x, float _y) : x(_x), y(_y) {}
// 	Point2f(double _x, double _y) : x((float)_x), y((float)_y) {}

// 	Point2f(Point2i _p2i) : x((float)_p2i.x), y((float)_p2i.y) {}

//     /******************************************************************************
//      * @brief 向量与x轴的夹角
//      * @return double 
//      ******************************************************************************/
//     inline double Angle() const
//     {
//         return atan2f(this->y,this->x);
//     }

//     /****************************************************************
//      * @brief 点进行旋转
//      * 
//      * @param dAngle 旋转角度，弧度制
//      * @param pOri 
//      * @return double 
//     *****************************************************************/
//     inline Point2f Rotate(double dAngle,const Point2f &pOri) const
//     {
//         return Point2f((x-pOri.x)*cos(dAngle) - (y-pOri.y)*sin(dAngle),
//                     (x-pOri.x)*sin(dAngle)+(y-pOri.y)*cos(dAngle)
//         );
//     }

//     /**
//      * @brief Point2f加法
//      * 
//      * @param pt 
//      * @return Point2f 
//      */
//     inline Point2f operator+(const Point2f &pt) const
//     {
//         return Point2f(this->x + pt.x, this->y + pt.y);
        
//     }

//     /**
//      * @brief Point2f减法
//      * 
//      * @param pt 
//      * @return Point2f 
//      */
//     inline Point2f operator-(const Point2f &pt) const
//     {
//         return Point2f(this->x - pt.x, this->y - pt.y);
//     }

//     /**
//      * @brief Point2f比较是否相等</br>
//      * 一般不建议使用
//      * 
//      * @param pt 
//      * @return bool 
//      */
//     inline bool operator==(const Point2f &pt) const
//     {
//         const double eps = 1e-3;//float的精度只有六位，算上整数位，一般能有三维小数位是保证精度的就不错了
//         return (fabs(this->x - pt.x)<eps && fabs(this->y - pt.y)<eps );
//     }

//     friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2f &pt)
//     {
//         os<<"( "<<pt.x<<", "<<pt.y<<" )";
//         return os;
//     }
// }Pointf;

// typedef Point2f vec2f;













#endif //!POINT2F_HPP

