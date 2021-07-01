/******************************************************************************
 * @file Circle.hpp
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

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Point.hpp"


/**
 * @brief 圆
 * 后期如果有需要最好还要兼容浮点型的点，精度才上得去
 * 
 */
struct stCircle
{
	Point2d ptCenter;
	double dR;
	stCircle() : ptCenter(Point2d(0, 0)), dR(0.0) {}
	stCircle(Point2d &pt, double r) : ptCenter(pt), dR(r) {} ///<直径圆心生成圆
    
    /**
     * @brief Construct a new st Circle::st Circle object
     * 使用三点求解出一个圆
     * 
     * @param pt1 
     * @param pt2 
     * @param pt3 
     */
    inline stCircle(Point2d &pt1, Point2d &pt2, Point2d &pt3)
    {
        double x1 = pt1.x, x2 = pt2.x, x3 = pt3.x;
        double y1 = pt1.y, y2 = pt2.y, y3 = pt3.y;
        double a = x1 - x2;
        double b = y1 - y2;
        double c = x1 - x3;
        double d = y1 - y3;
        double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
        double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
        double det = b * c - a * d;

        //三点共线
        if (fabs(det) < 1e-5)
        {
            dR = -1;
            ptCenter = Point2d(0, 0);
        }

        double x0 = -(d * e - b * f) / det;
        double y0 = -(a * f - c * e) / det;
        dR = hypot(x1 - x0, y1 - y0);
        ptCenter = Point2d(x0, y0);
    }

    /**
     * @brief 圆的平移
     * 
     * @param pt 平移向量
     * @return stCircle 新的圆
     */
    inline stCircle Shift(Point2d &pt) const
    {
        Point2d pt1 = this->ptCenter + pt;
        return stCircle(pt1, this->dR);
    }

    /**
     * @brief 两个圆是否相交
     * 
     * @param stC 另一个圆
     * @return true 
     * @return false 
     */
    inline bool Cross(stCircle &stC) const
    {
        double dDist = sqrt(pow(this->ptCenter.x - stC.ptCenter.x, 2) + pow(this->ptCenter.y - stC.ptCenter.y, 2));
        if (dDist == (this->dR + stC.dR))
            return true;
        return false;
    }

    //圆与直线相交
    inline bool Cross(GenLine &stG) const
    {
        double dDistance = this->FromLine(stG); //stG.FromPoint(this->ptCenter);
        if (this->dR < dDistance)
            return true;
        return false;
    }

    //待优化
    //这儿应该用跨立、快排处理
    /******************************************************************************
     * @brief 圆与线段相交
     * @param  stS              线段
     * @return true     相交
     * @return false    不相交
     ******************************************************************************/
    inline bool Cross(SegLine2f &stS) const
    {
        SegLine2f stG = SegLine2f(stS);
        double d1 = sqrt(pow(stS.pt1.x - this->ptCenter.x, 2) + pow(stS.pt1.y - this->ptCenter.y, 2)); ///<线段第一个点到圆心的距离
        double d2 = sqrt(pow(stS.pt2.x - this->ptCenter.x, 2) + pow(stS.pt2.y - this->ptCenter.y, 2)); ///<线段第二个点到圆心的距离
        //double d3 = this->FromLine(stG);///<圆心到直线的距离
        double d4 = stS.FromPoint(this->ptCenter);
        if (d1 < this->dR && d2 < this->dR) //都在圆内
            return false;
        if (std::min(d1, d2) < this->dR && max(d1, d2) > this->dR) //一个圆内一个圆外
            return true;
        if (d4 < this->dR && max(d1, d2) > this->dR) //线上最近点在圆内，最远点在圆外
            return true;
        return false;
    }

    /******************************************************************************
     * @brief 圆心到直线的距离
     * @param  stG              My Param doc
     * @return double 
     ******************************************************************************/
    double FromLine(GenLine &stG) const
    {
        double dDistance = fabs(stG.a * this->ptCenter.x + stG.b * this->ptCenter.y + stG.c) / sqrt(pow(stG.a, 2) + pow(stG.b, 2));
        return dDistance;
    }

    /**
     * @brief 圆心到点的距离
     * 
     * @param pt 
     * @return double 
     */
    inline double FromPoint(Point2d &pt) const
    {
        return sqrt(pow(this->ptCenter.x - pt.x, 2) + pow(this->ptCenter.y - pt.y, 2));
    }

    /**
     * @brief 比较两个圆是否相等
     * 
     * @param stC 另一个圆
     * @return true 相等
     * @return false 不相等
     */
    inline bool operator==(const stCircle &stC) const
    {
        if (this->ptCenter.x == stC.ptCenter.x && this->ptCenter.y == stC.ptCenter.y && this->dR == stC.dR)
            return true;
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, stCircle &stC)
    {
        os << "Circle: "
        << "Center = (" << stC.ptCenter.x << ", " << stC.ptCenter.y << "), R = " << stC.dR;
        return os;
    }

};





#endif //!CIRCLE_HPP

