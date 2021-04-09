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



/*****************************************************************************
 * @brief 二维模板点
 * 
 * @tparam _T 
 *****************************************************************************/
template<typename _T>
class Point_
{
public:

    //初始化
    Point_():x((_T)0.0),y((_T)0.0){}
    Point_(_T _x, _T _y):x(_x),y(_y){}

    //类型转换
    template<typename _T2> inline 
    operator Point_<_T2>() const
    {
        //return Point_<_T2>(saturate_cast<_T2>(x), saturate_cast<_T2>(y));//这儿要留意
        return Point_<_T2>(_T2(x), _T2(y));//这儿要留意
    }

   bool operator||(const Point_<_T> &pt)const;	///<两个向量是否方向相同

    /******************************************************************************
     * @brief 向量与x轴的夹角
     * @return double 
     ******************************************************************************/
    inline double Angle() const
    {
        return atan2f((float)this->y,(float)this->x);
    }
    
    /*****************************************************************************
     * @brief 当以当前向量为起始向量，计算两向量的夹角
     * @param v2 
     * @return double 
     *****************************************************************************/
    inline double AngleDis(Point_<_T> &v2)const
    {
        return v2.Angle() - Angle();
    }

    /**
     * @brief 向量或点绕中心点旋转
     * 
     * @param dAngle 旋转角度，弧度制
     * @param pOri 原点
     * @return Point_<_T> 
     */
    inline Point_<_T> Rotate(double dAngle,const Point_<_T> &pOri = Point_<_T>((_T)0.0, (_T)0.0)) const
    {
        return Point_<_T>((x-pOri.x)*cos(dAngle) - (y-pOri.y)*sin(dAngle) + 0.5,
                    (x-pOri.x)*sin(dAngle)+(y-pOri.y)*cos(dAngle) + 0.5
        );
    }

    /**
     * @brief Point_<_T>加法
     * 
     * @param pt 相加的点
     * @return Point_<_T> 
     */
    inline Point_<_T> operator+(const Point_<_T> &pt) const
    {
        return Point_<_T>(this->x + pt.x, this->y + pt.y);
    }

    /**
     * @brief Point_<_T>减法
     * 
     * @param pt 
     * @return Point_<_T> 
     */
    inline Point_<_T> operator-(const Point_<_T> &pt) const
    {
        return Point_<_T>(this->x - pt.x, this->y - pt.y);
    }

    /**
     * @brief Point_<_T>判断是否相等
     * 目前兼容int,float,和double的判断
     * @param pt 
     * @return false 不相等
     * @return true 相等
     */
    inline bool operator==(const Point_<_T> &pt) const
    {
        switch (typeid(_T))
        {
        case typeid(int):
            return (this->x == pt.x && this->y == pt.y);
            break;//break 是多余的，下同
        case typeid(float):
            const double feps = 1e-3;//float的精度只有六位，算上整数位，一般能有三维小数位是保证精度的就不错了
            return (fabs(this->x - pt.x)<feps && fabs(this->y - pt.y)<feps );
            break;
        case typeid(double):
            const double deps = 1e-6;//double的精度有15位，算上整数位，所以问题小一些
            return (fabs(this->x - pt.x)<deps && fabs(this->y - pt.y)<deps );
            break;
        default:
            return false;
            break;
        }
        //return (this->x == pt.x && this->y == pt.y);
    }

    /**
     * @brief 重载点的输出运算符
     * 
     */
    friend std::ostream &operator<<(std::ostream &os, /*const*/ Point_<_T> &pt)
    {
        os<<"( "<<pt.x<<", "<<pt.y<<" )";
        return os;
    }
public:
    _T x;
    _T y;
};

//定义别名
typedef Point_<int> Point2i;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
typedef Point2i Point;
typedef Point2f Pointf;
typedef Point2d Pointd;

//定义向量别名
typedef Point2i vec2i;
typedef Point2f vec2f;
typedef Point2d vec2d;
typedef vec2i   vec;
typedef vec2f   vecf;
typedef vec2d   vecd;

//////////////////////////////////////////////////////////////////////////////////////////////
// 下面的部分不要了
//////////////////////////////////////////////////////////////////////////////////////////////

// struct Point2i;

// /**
//  * @brief 整形二维点
//  * 
//  */
// typedef
// struct Point2i
// {
// 	int x;
// 	int y;

// 	Point2i() : x(0), y(0) {}

// 	Point2i(int _x, int _y) : x(_x), y(_y) {}
// 	Point2i(float _x, float _y) : x((int)(_x + 0.5)), y((int)(_y + 0.5)) {}
// 	Point2i(double _x, double _y) : x((int)(_x + 0.5)), y((int)(_y + 0.5)) {}


// 	bool operator||(const Point2i &pt)const;	///<两个向量是否方向相同

// 	friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2i &pt);

//     /******************************************************************************
//      * @brief 向量与x轴的夹角
//      * @return double 
//      ******************************************************************************/
//     inline double Angle() const
//     {
//         return atan2f((float)this->y,(float)this->x);
//     }
    
//     /**
//      * @brief 向量或点绕中心点旋转
//      * 
//      * @param dAngle 旋转角度，弧度制
//      * @param pOri 原点
//      * @return Point2i 
//      */
//     inline Point2i Rotate(double dAngle,const Point2i &pOri) const
//     {
//         return Point2i((x-pOri.x)*cos(dAngle) - (y-pOri.y)*sin(dAngle) + 0.5,
//                     (x-pOri.x)*sin(dAngle)+(y-pOri.y)*cos(dAngle) + 0.5
//         );
//     }

//     /**
//      * @brief Point2i加法
//      * 
//      * @param pt 相加的点
//      * @return Point2i 
//      */
//     inline Point2i operator+(const Point2i &pt) const
//     {
//         return Point2i(this->x + pt.x, this->y + pt.y);
//     }

//     /**
//      * @brief Point2i减法
//      * 
//      * @param pt 
//      * @return Point2i 
//      */
//     inline Point2i operator-(const Point2i &pt) const
//     {
//         return Point2i(this->x - pt.x, this->y - pt.y);
//     }

//     /**
//      * @brief Point2i判断是否相等
//      * 
//      * @param pt 
//      * @return false 不相等
//      * @return true 相等
//      */
//     inline bool operator==(const Point2i &pt) const
//     {
//         return (this->x == pt.x && this->y == pt.y);
//     }

//     /**
//      * @brief 重载点的输出运算符
//      * 
//      */
//     friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2i &pt)
//     {
//         os<<"( "<<pt.x<<", "<<pt.y<<" )";
//         return os;
//     }
// } Point;

// typedef Point2i vec2i;




#endif //!POINT_HPP