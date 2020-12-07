


#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "Point2d.hpp"


/**
 * @brief 椭圆
 * 
 */
struct stEllipse
{
	Point2d center;	///<椭圆中心
	double a;		///<椭圆长半轴长
	double b;		///<椭圆短半轴长
	double angle;	///<旋转角度,角度值

	stEllipse():center(Point2d(0.0,0.0)),a(0.0),b(0.0),angle(0.0){}
	//stEllipse(stEllipseNormal &stEN);
	//stEllipse()
};


#endif //!ELLIPSE_HPP