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
#define PI 3.1415926535897932384626433832795

/*****************************************************************************
 * @brief 二维模板点
 *
 * @tparam _T
 *****************************************************************************/
template <typename _T>
class Point_
{
public:
    //初始化
    Point_() : x((_T)0.0), y((_T)0.0) {}
    Point_(_T _x, _T _y) : x(_x), y(_y) {}

    //类型转换
    template <typename _T2>
    inline
    operator Point_<_T2>() const
    {
        // return Point_<_T2>(saturate_cast<_T2>(x), saturate_cast<_T2>(y));//这儿要留意
        return Point_<_T2>(_T2(x), _T2(y)); //这儿要留意
    }

    /******************************************************************************
     * @brief 向量与x轴的夹角
     * @return double
     ******************************************************************************/
    inline double Angle() const
    {
        return atan2f((float)this->y, (float)this->x);
    }

    /**
     * @brief 计算到另一个点的距离
     * @param pt
     * @return double
     */
    inline double Distance(const Point_<_T> &pt) const
    {
        return sqrt(pow(this->x - pt.x, 2) + pow(this->y - pt.y, 2));
    }

    /*****************************************************************************
     * @brief after unclockwise the vector PI/2, get the angle use as Normal's Angle
     * the new y is the old x, the new x is the old -y
     * @return double
     *****************************************************************************/
    inline double unclockwiseNormalAngle() const
    {
        return atan2(x, -y);
    }

    /*****************************************************************************
     * @brief
     * the new y is the old -x, the new x is the old y
     * @return double
     *****************************************************************************/
    inline double clockwiseNormalAngle() const
    {
        return atan2(-x, y);
    }

    /*****************************************************************************
     * @brief 当以当前向量为起始向量，计算两向量的夹角
     * @param v2
     * @return double
     *****************************************************************************/
    inline double AngleDis(Point_<_T> &v2) const
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
    inline Point_<_T> Rotate(double dAngle, const Point_<_T> &pOri = Point_<_T>((_T)0.0, (_T)0.0)) const
    {
        // return Point_<_T>((x-pOri.x)*cos(dAngle) - (y-pOri.y)*sin(dAngle) + 0.5,
        //             (x-pOri.x)*sin(dAngle)+(y-pOri.y)*cos(dAngle) + 0.5
        // );
        return Point_<_T>(pOri.x + (x - pOri.x) * cos(dAngle) - (y - pOri.y) * sin(dAngle),
                          pOri.y + (x - pOri.x) * sin(dAngle) + (y - pOri.y) * cos(dAngle));
    }

    /**
     * @brief 向量模长
     *
     * @return double
     */
    inline double Length()
    {
        return std::sqrt((double)(x * x + y * y));
    }

    /**
     * @brief 求解单位向量。向量除以模长
     *
     * @return Point_<_T>
     */
    inline Point_<_T> UnitVec()
    {
        return *this / this->Length();
    }

    /*****************************************************************************
     * @brief 向量的点积
     *
     * @param {type} v
     * @return _T
     *****************************************************************************/
    inline _T dot(const Point_<_T> &v) const
    {
        return x * v.x + y * v.y;
    }

    /*****************************************************************************
     * @brief 向量的叉积
     *
     * @param[in] v
     * @return _T
     *****************************************************************************/
    inline _T cross(const Point_<_T> &v) const
    {
        // return x*v.y+y*v.x;
        return x * v.y - y * v.x;
    }

    /**
     * @brief 两个向量是否平行，同向平行和反向平行都包括
     *
     * @param v 另一个向量
     * @return true     平行
     * @return false    不平行
     */
    inline bool operator||(const Point_<_T> &v) const
    {
        return std::abs(cross(v)) < 1e-6;
    }

    /*****************************************************************************
     * @brief 向量同向
     * @details 两向量平行，且点积为正则两向量同向
     * @param v
     * @return true
     * @return false
     *****************************************************************************/
    inline bool SameDirector(const Point_<_T> &v) const
    {
        return std::abs(cross(v)) < 1e-6 && dot(v) > 0;
    }

    /*****************************************************************************
     * @brief 向量反向
     * @details 两向量平行，且点积为反则两向量反向
     * @param v
     * @return true
     * @return false
     *****************************************************************************/
    inline bool OppositeDirector(const Point_<_T> &v) const
    {
        return std::abs(cross(v)) < 1e-6 && dot(v) < 0;
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

    /*****************************************************************************
     * @brief 向量乘法
     *
     * @param {type} d
     * @return Point_<_T>
     *****************************************************************************/
    inline Point_<_T> operator*(const _T d) const
    {
        return Point_<_T>(x * d, y * d);
    }

    /*****************************************************************************
     * @brief 向量乘法
     *
     * @tparam _T2
     * @param {type} d
     * @return Point_<_T>
     *****************************************************************************/
    template <typename _T2>
    inline Point_<_T> operator*(const _T2 d) const
    {
        return Point_<_T>(x * d, y * d);
    }

    /*****************************************************************************
     * @brief 向量除法
     *
     * @param {type} d
     * @return Point_<_T>
     *****************************************************************************/
    inline Point_<_T> operator/(const _T d) const
    {
        return Point_<_T>(x / d, y / d);
    }

    /*****************************************************************************
     * @brief 向量除法
     *
     * @tparam _T2
     * @param {type} d
     * @return Point_<_T>
     *****************************************************************************/
    template <typename _T2>
    inline Point_<_T> operator/(const _T2 d) const
    {
        return Point_<_T>(x / d, y / d);
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
        const std::type_info &nInfo = typeid(_T);

        if (nInfo == typeid(int))
        {
            return (this->x == pt.x && this->y == pt.y);
        }

        if (nInfo == typeid(float))
        {
            const double feps = 1e-3; // float的精度只有六位，算上整数位，一般能有三维小数位是保证精度的就不错了
            return (fabs(this->x - pt.x) < feps && fabs(this->y - pt.y) < feps);
        }

        if (nInfo == typeid(double))
        {
            const double deps = 1e-6; // double的精度有15位，算上整数位，所以问题小一些
            return (fabs(this->x - pt.x) < deps && fabs(this->y - pt.y) < deps);
        }

        return false;
    }

    inline bool operator!=(const Point_<_T> &pt) const
    {
        return !(*this == pt);
    }

    /**
     * @brief 重载点的输出运算符
     *
     */
    friend std::ostream &operator<<(std::ostream &os, /*const*/ Point_<_T> &pt)
    {
        os << "(" << pt.x << "," << pt.y << ")";
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
typedef vec2i vec;
typedef vec2f vecf;
typedef vec2d vecd;

#endif //! POINT_HPP