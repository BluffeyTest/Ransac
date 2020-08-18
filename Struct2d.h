/**
 * @file Struct2d.h
 * @author Bluffey (Bluffey@163.com.com)
 * @brief 二维平面结构体
 * @version 0.1
 * @date 2020-08-18
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

/**
 * 二维点
 * */
struct Point2i;
struct Point2f;
struct Point2d;

/**
 * @brief 圆、圆弧、直线、线段结构体
 * 
 */
struct stCircle;
struct stArc;
struct stSegLine;
struct stGenLine;

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

	//Point2i(Point _p2):x(_p2.x),y(p2.y){}
	Point2i(Point2f _p2f) : x((int)(_p2f.x + 0.5)), y((int)(_p2f.y + 0.5)) {}
	Point2i(Point2d _p2d) : x((int)(_p2d.x + 0.5)), y((int)(_p2d.y + 0.5)) {}

	inline Point2i operator+(const Point2i &pt) const;
	inline Point2i operator-(const Point2i &pt) const;
	inline bool operator==(const Point2i &pt) const;
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
	Point2f(Point2d _p2d) : x((float)_p2d.x), y((float)_p2d.y) {}

	inline Point2f operator+(const Point2f &pt) const;
	inline Point2f operator-(const Point2f &pt) const;
	inline bool operator==(const Point2f &pt) const;


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

	inline Point2d operator+(const Point2d &pt) const;
	inline Point2d operator-(const Point2d &pt) const;
	inline bool operator==(const Point2d &pt) const;
}Pointd;

//两点距离
/*inline*/ double Distance(Point &pt1, Point &pt2);

/// <summary>
/// 圆
/// 后期如果有需要最好还要兼容浮点型的点，精度才上得去
/// </summary>
struct stCircle
{
	Point ptCenter;
	double dR;
	stCircle() : ptCenter(Point(0, 0)), dR(0.0) {}
	stCircle(Point &pt, double r) : ptCenter(pt), dR(r) {} ///<直径圆心生成圆
	stCircle(Point &pt1, Point &pt2, Point &pt3);		   ///<三点生成圆

	inline bool operator==(const stCircle &stC) const;
	stCircle Shift(Point &pt) const;
	inline bool Cross(stCircle &stC) const;	 //圆相交
	inline bool Cross(stGenLine &stG) const; //圆与直线相交
	inline bool Cross(stSegLine &stS) const; //圆与线段相交

	inline double FromLine(stGenLine &stG) const; //圆与直线距离
	/*inline*/ double FromPoint(Point &pt) const; //圆与直线距离

	friend std::ostream &operator<<(std::ostream &os, stCircle &stC);
};

/// <summary>
/// 圆弧
/// </summary>
struct stArc
{
	stCircle Circle;
	double dStartAngle; //开始角度，弧度制
	double dEndAngle;	//结束角度弧度制

	stArc() : Circle(stCircle()), dStartAngle(0.0), dEndAngle(0.0) {}
	stArc(stCircle &stC, double ds, double de) : Circle(stC), dStartAngle(ds), dEndAngle(de) {}

	friend std::ostream &operator<<(std::ostream &os, stArc &stArc);
};

/// <summary>
/// 两点线段
/// </summary>
struct stSegLine
{
	Point pt1;
	Point pt2;

	stSegLine() : pt1(Point(0, 0)), pt2(Point(0, 0)) {}
	stSegLine(Point &p1, Point &p2) : pt1(p1), pt2(p2) {}

	inline bool operator==(stSegLine &stS) const;

	inline bool Cross(stSegLine &stS) const;	  ///<线段与线段相交
	inline void GetGenLine(stGenLine &stG) const; ///<从线段获得直线
	inline double Length() const;				  //线段长度
	/*inline*/ double FromPoint(Point pt) const;  //线段到一个点的最短距离

	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);
};

/// <summary>
/// 直线的标准方程
/// </summary>
struct stGenLine
{
	double da;
	double db;
	double dc;

	stGenLine() : da(0.0), db(0.0), dc(0.0) {}
	stGenLine(double a, double b, double c) : da(a), db(b), dc(c) {}
	stGenLine(Point &p1, Point &p2);
	stGenLine(stSegLine &stS);

	inline bool Cross(stGenLine &stG) const;  ///<直线与直线相交
	inline bool Cross(stSegLine &stS) const;  ///<直线与线段相交
	inline double FromPoint(Point &pt) const; ///<直线与点的距离

	/*inline*/ bool operator||(const stGenLine &stG) const; ///<两直线平行

	inline bool operator==(const stGenLine &stG) const; ///<两直线斜率在一定范围内判定为同一条
	friend std::ostream &operator<<(std::ostream &os, stGenLine &stG);
};

#endif // !STRUCT2D_H
