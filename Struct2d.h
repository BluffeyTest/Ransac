/**
 * @file Struct2d.h
 * @author Bluffey (Bluffey@163.com.com)
 * @brief 二维平面结构体
 * @version 0.1
 * @date 2020-08-18
 * @note inline 的成员函数的生命和定义需要卸载同一个文件里，不然无法链接
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once
#ifndef STRUCT2D_H
#define STRUCT2D_H
#include <iostream>
//#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <cmath>

/// PI
#define PI	3.1415926535897932384626433832795

/**
 * @brief 二维点
 * */
struct Point2i;
struct Point2f;
struct Point2d;

/**
 * @brief 二维向量
 * 将二维点重定义为二维向量是为了在某些地方不要将两个用混了，
 * 但是在数学上两者又有同样的表现形式，所以就定义在一起了
 * 
 */
typedef Point2i vec2i;
typedef Point2f vec2f;
typedef Point2d vec2d;
typedef vec2d	vec;

/**
 * @brief 圆、圆弧、直线、线段、椭圆、椭圆弧结构体
 * 
 */
struct stCircle;
struct stArc;
struct stSegLine;
struct stGenLine;
struct stEllipse;///<暂时没有具体实现
struct stArcEllipse;///<暂时没有具体实现

/**
 * @brief 整形二维点
 * 
 */
typedef struct Point2i
{
	int x;
	int y;

	Point2i() : x(0), y(0) {}

	Point2i(int _x, int _y) : x(_x), y(_y) {}
	Point2i(float _x, float _y) : x((int)(_x + 0.5)), y((int)(_y + 0.5)) {}
	Point2i(double _x, double _y) : x((int)(_x + 0.5)), y((int)(_y + 0.5)) {}

	double Angle() const;		///<向量与x轴的夹角
	Point2i Rotate(double dAngle,const Point2i &pOri = Point2i(0,0)) const;///<向量或点绕中心点旋转

	///< 备注，内敛函数总是不能如愿运行，故放弃内联
	Point2i operator+(const Point2i &pt) const;	///<两点相加，同时也是两个向量相加
	Point2i operator-(const Point2i &pt) const;	///<两点相减，~~
	bool operator==(const Point2i &pt) const;	///<判断两点是否相等，~~

	bool operator||(const Point2i &pt)const;	///<两个向量是否方向相同

	friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2i &pt);
} Point;

/**
 * @brief 单精度浮点型二维点
 * 
 */
typedef struct Point2f
{
	float x;
	float y;

	Point2f() : x(0.f), y(0.f) {}

	Point2f(int _x, int _y) : x((float)_x), y((float)_y) {}
	Point2f(float _x, float _y) : x(_x), y(_y) {}
	Point2f(double _x, double _y) : x((float)_x), y((float)_y) {}

	Point2f(Point2i _p2i) : x((float)_p2i.x), y((float)_p2i.y) {}
	//Point2f(Point2d _p2d) : x((float)_p2d.x), y((float)_p2d.y) {}

	double Angle() const;		///<向量与x轴的夹角
	Point2f Rotate(double dAngle,const Point2f &pOri = Point2f(0,0)) const;///<向量或点绕中心点旋转

	/*inline*/ Point2f operator+(const Point2f &pt) const;
	/*inline*/ Point2f operator-(const Point2f &pt) const;
	/*inline*/ bool operator==(const Point2f &pt) const;

	friend std::ostream & operator<<(std::ostream &os, /*const*/ Point2f &pt);

}Pointf;

/**
 * @brief 双精度浮点型二维点
 * 
 */
typedef struct Point2d
{
	double x;
	double y;

	Point2d() : x(0.0), y(0.0) {}

	Point2d(int _x, int _y) : x((double)_x), y((double)_y) {}
	Point2d(float _x, float _y) : x(_x), y(_y) {}
	Point2d(double _x, double _y) : x(_x), y(_y) {}

	Point2d(Point2i _p2i) : x((double)_p2i.x), y((double)_p2i.y) {}
	Point2d(Point2f _p2f) : x((double)_p2f.x), y((double)_p2f.y) {}

	double Angle() const;		///<向量与x轴的夹角
	Point2d Rotate(double dAngle,const Point2d &pOri = Point2d(0,0)) const;///<向量或点绕中心点旋转


	/*inline*/ Point2d operator+(const Point2d &pt) const;
	/*inline*/ Point2d operator-(const Point2d &pt) const;
	/*inline*/ bool operator==(const Point2d &pt) const;

	friend std::ostream & operator<<(std::ostream &os, /*const*/ Point2d &pt);
}Pointd;

//两点距离
double Distance(Point &pt1, Point &pt2);
double Distance(Point2d &pt1, Point2d &pt2);

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
	stCircle(Point2d &pt1, Point2d &pt2, Point2d &pt3);		   ///<三点生成圆

	/*inline*/ bool operator==(const stCircle &stC) const;
	stCircle Shift(Point2d &pt) const;		//圆平移
	/*inline*/ bool Cross(stCircle &stC) const;	 //圆相交
	/*inline*/ bool Cross(stGenLine &stG) const; //圆与直线相交
	/*inline*/ bool Cross(stSegLine &stS) const; //圆与线段相交

	/*inline*/ double FromLine(stGenLine &stG) const; //圆与直线距离
	/*inline*/ double FromPoint(Point2d &pt) const; //圆与直线距离

	friend std::ostream &operator<<(std::ostream &os, stCircle &stC);
};

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

	friend std::ostream &operator<<(std::ostream &os, stArc &stArc);
};

/**
 * @brief 两点线段\n
 * 起点和终点是有顺序的
 */
struct stSegLine
{
	Pointd pt1;///<起点
	Pointd pt2;///<终点

	stSegLine() : pt1(Pointd(0, 0)), pt2(Pointd(0, 0)) {}
	stSegLine(Pointd &p1, Pointd &p2) : pt1(p1), pt2(p2) {}

	bool operator==(stSegLine &stS) const;	///<两条线段是否相等

	bool Cross(stSegLine &stS) const;	  ///<线段与线段相交
	void GetGenLine(stGenLine &stG) const; ///<从线段获得直线
	double Length() const;				  ///<线段长度
	double FromPoint(Point pt) const;  ///<线段到一个点的最短距离
	double FromPoint(Point2d pt) const;  ///<线段到一个点的最短距离

	double Angle() const;				///<线段的角度
	double AngleFrom(stSegLine &stS);	///<两条线段的夹角


	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);
};

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
	
	stGenLine(Pointd &p1, Pointd &p2);
	stGenLine(Point &p1, Point &p2);
	stGenLine(stSegLine &stS);

	bool Cross(stGenLine &stG) const;  ///<直线与直线相交
	bool Cross(stSegLine &stS) const;  ///<直线与线段相交
	double FromPoint(Point &pt) const; ///<直线与点的距离
	double FromPoint(Pointd &pt) const;///<直线与点的距离

	double Angle() const;
	double AngleFrom(stGenLine &stG) const;

	bool operator||(const stGenLine &stG) const; ///<两直线平行

	bool operator==(const stGenLine &stG) const; ///<两直线斜率在一定范围内判定为同一条
	friend std::ostream &operator<<(std::ostream &os, stGenLine &stG);
};

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


/**
 * @brief 椭圆的一般方程式ax^2+by^2+cxy+dx+ey = 0;
 * 二次型的表述：
 * 
 */
typedef struct stEllipseNormal
{
	double A;
	double B;
	double C;
	double D;
	double E;

	stEllipseNormal():A(0.0),B(0.0),C(0.0),D(0.0),E(0.0){}
	stEllipseNormal(double _a,double _b,double _c,double _d,double _e):
		A(_a),B(_b),C(_c),D(_d),E(_e){}				///<从已经有的参数复制
	stEllipseNormal(Pointd &pt1,Pointd &pt2,Pointd &pt3, 
		Pointd &pt4,Pointd &pt5,Pointd &pt6);		///<从六个点用线性代数导出
	stEllipseNormal(std::vector<Point2f> &vPts);	///<从点集当中用最小二乘法拟合出来椭圆
	stEllipseNormal(stEllipse &_stE);
	
	


}EllipseStd;


#endif // !STRUCT2D_H
