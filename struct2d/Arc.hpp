/******************************************************************************
 * @file Arc.hpp
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

#ifndef ARC_HPP
#define ARC_HPP

#include "Circle.hpp"


/**
 * @brief 圆弧
 * 
 */
struct stArc
{
	stCircle Circle;
	double dStartAngle; //开始角度，弧度制
	double dEndAngle;	//结束角度弧度制

	stArc() : Circle(stCircle()), dStartAngle(0.0), dEndAngle(0.0) {}
	stArc(stCircle &stC, double ds, double de) : Circle(stC), dStartAngle(ds), dEndAngle(de) {}

	friend std::ostream &operator<<(std::ostream &os, stArc &stArc)
    {
        os << "Arc: " << stArc.Circle << ", startangle = " << stArc.dStartAngle << ", EndAngle = " << stArc.dEndAngle;
        return os;
    }
};





#endif //! ARC_HPP