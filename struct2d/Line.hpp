/******************************************************************************
 * @file Line.hpp
 * @brief 
 * @author Bluffey (Bluffey@163.com)
 * @version 1.0
 * @date 2020-11-13
 * 
 * @copyright Copyright (c) 2020  成都云裁科技有限公司
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2020-11-13 <td>1.0     <td>wangh     <td>内容
 * </table>
 ******************************************************************************/


#ifndef LINE_HPP
#define LINE_HPP

#include "Point.hpp"
#include "SegmentLine.hpp"


//template<class _Tp>
class GenLine_
{
private:
    /* data */
public:
    //初始化和销毁
    GenLine_(): a(0.0), b(0.0), c(0.0) {}
	GenLine_(double _a, double _b, double _c): a(_a), b(_b), c(_c) {}
    ~GenLine_();

    template<class _Tp>
    GenLine_(_Tp &p1, _Tp &p2)
    {
        this->a = (double)(p1.y - p2.y);
        this->b = (double)(p2.x - p1.x);
        this->c = (double)(p1.x * p2.y - p2.x * p1.y);
    }

    template<class _Tp>
    GenLine_(SegmentLine_<_Tp> &stS)
    {
        _Tp &p1 = stS.pt1;
        _Tp &p2 = stS.pt2;
        this->a = (double)(p1.y - p2.y);
        this->b = (double)(p2.x - p1.x);
        this->c = (double)(p1.x * p2.y - p2.x * p1.y);
    }

    //TODO:
	bool Cross(GenLine_ &G) const;  ///<直线与直线相交
    template<class _Tp>
	bool Cross(SegmentLine_<_Tp> &SL) const;  ///<直线与线段相交

    

    /**
     * @brief 直线到点的距离
     * 
     * @param pt 点
     * @return double 
     */
    template<class _Tp>
    inline double FromPoint(_Tp &pt) const
    {
        double dDistance = fabs(this->a * pt.x + this->b * pt.y + this->c) / sqrt(pow(this->a, 2) + pow(this->b, 2));
        return dDistance;
    }

    /**
     * @brief 直线的角度
     * 
     * @return double 
     */
    inline double Angle() const
    {
        return atan2(a,-b);
    }

    /**
     * @brief 两条直线之间的夹角
     * 是有序的，参数里面属于后一条直线
     * @param stG 
     * @return double 
     */
    inline double AngleFrom(GenLine_ &stG) const
    {
        return (atan2(stG.a,-stG.b) - atan2(a,-b));
    }

    /**
     * @brief 两直线平行
     * 
     * @param stG 另一条直线
     * @return true 
     * @return false 
     */
    inline bool operator||(const GenLine_ &stG) const
    {

        double dScale = this->a / stG.a;
        const double eps = 1e-6;
        if (fabs(this->a - stG.a * dScale) < eps && fabs(this->b - stG.b * dScale) < eps)
            return true;
        return false;
    }

    /******************************************************************************
     * @brief 判断两直线是否相等
     * @param[in]  stG              另一条直线
     * @return true     相等
     * @return false    不相等
     ******************************************************************************/
    inline bool operator==(const GenLine_ &stG) const
    {
        double dScale = this->a / stG.a;
        const double eps = 1e-6;
        if (fabs(this->a - stG.a * dScale) < eps && fabs(this->b - stG.b * dScale) < eps 
            && fabs(this->c - stG.c * dScale) < eps)
            return true;
        return false;
    }


    /******************************************************************************
     * @brief 判断直线和线段是否属于同一条直线。
     * @param[in]  stS              线段
     * @return true 
     * @return false 
     ******************************************************************************/
    template<class _Tp>
    inline bool operator==(SegmentLine_<_Tp> &stS) const
    {
        std::cout<<"don't suppurt now!"<<std::endl;
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, GenLine_ &stG)
    {
        os << "GenLine: " << stG.a << " * x ";
        stG.b < 0 ? os << stG.b : os << "+ " << stG.b;
        os << " * y ";
        stG.c < 0 ? os << stG.c : os << "+ " << stG.c;
        os << " = 0.0";
        return os;
    }



public:
    double a;
    double b;
    double c;
};

typedef GenLine_ GenLine;


#endif //!LINE_HPP