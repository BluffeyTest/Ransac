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
#include "Point2f.hpp"
#include "Point2d.hpp"
#include "SegmentLine.hpp"

/**
 * @brief 直线的标准方程
 * $ ax+by+c=0$
 */
struct stGenLine
{
	double a; 
	double b;
	double c;

	stGenLine() : a(0.0), b(0.0), c(0.0) {}
	stGenLine(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
	
    //TODO:
	bool Cross(stGenLine &stG) const;  ///<直线与直线相交
	bool Cross(stSegLine &stS) const;  ///<直线与线段相交
	

    
    stGenLine(Point &p1, Point &p2)
    {
        this->a = (double)(p1.y - p2.y);
        this->b = (double)(p2.x - p1.x);
        this->c = (double)(p1.x * p2.y - p2.x * p1.y);
    }

    stGenLine(Pointd &p1, Pointd &p2)
    {
        this->a = (double)(p1.y - p2.y);
        this->b = (double)(p2.x - p1.x);
        this->c = (double)(p1.x * p2.y - p2.x * p1.y);
    }

    stGenLine(stSegLine &stS)
    {
        Pointd &p1 = stS.pt1;
        Pointd &p2 = stS.pt2;
        this->a = (double)(p1.y - p2.y);
        this->b = (double)(p2.x - p1.x);
        this->c = (double)(p1.x * p2.y - p2.x * p1.y);
    }

    /**
     * @brief 直线到点的距离
     * 
     * @param pt 点
     * @return double 
     */
    inline double FromPoint(Point &pt) const
    {
        double dDistance = fabs(this->a * pt.x + this->b * pt.y + this->c) / sqrt(pow(this->a, 2) + pow(this->b, 2));
        return dDistance;
    }

    /**
     * @brief 直线到点的距离
     * 
     * @param pt 点
     * @return double 
     */
    inline double FromPoint(Pointd &pt) const
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
    inline double AngleFrom(stGenLine &stG) const
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
    inline bool operator||(const stGenLine &stG) const
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
    inline bool operator==(const stGenLine &stG) const
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
    inline bool operator==(stSegLine &stS) const
    {
        std::cout<<"don't suppurt now!"<<std::endl;
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, stGenLine &stG)
    {
        os << "GenLine: " << stG.a << " * x ";
        stG.b < 0 ? os << stG.b : os << "+ " << stG.b;
        os << " * y ";
        stG.c < 0 ? os << stG.c : os << "+ " << stG.c;
        os << " = 0.0";
        return os;
    }

};










#endif //!LINE_HPP