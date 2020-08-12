#pragma once
#ifndef STRUCT2D_H
#define STRUCT2D_H
#include <iostream>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>

using namespace std;
using namespace cv;

struct stCircle;
struct stArc;
struct stSegLine;
struct stGenLine;

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
	stCircle():ptCenter(Point(0,0)),dR(0.0){}
	stCircle(Point &pt,double r):ptCenter(pt),dR(r){}///<直径圆心生成圆
	stCircle(Point& pt1, Point& pt2, Point& pt3);///<三点生成圆

	inline bool operator==(const stCircle &stC) const;
	stCircle Shift(Point& pt) const;
	inline bool Cross(stCircle& stC) const;//圆相交
	inline bool Cross(stGenLine& stG) const;//圆与直线相交
	inline bool Cross(stSegLine& stS) const;//圆与线段相交

	inline double FromLine(stGenLine& stG) const;//圆与直线距离
	/*inline*/ double FromPoint(Point& pt) const;//圆与直线距离

	friend ostream& operator <<(ostream& os, stCircle &stC);
	
};

/// <summary>
/// 圆弧
/// </summary>
struct stArc
{
	stCircle Circle;
	double dStartAngle;//开始角度，弧度制
	double dEndAngle;	//结束角度弧度制

	stArc():Circle(stCircle()), dStartAngle(0.0), dEndAngle(0.0) {}
	stArc(stCircle &stC,double ds,double de):Circle(stC),dStartAngle(ds),dEndAngle(de){}

	friend ostream& operator <<(ostream& os, stArc &stArc);
};

/// <summary>
/// 两点线段
/// </summary>
struct stSegLine
{
	Point pt1;
	Point pt2;

	stSegLine() :pt1(Point(0,0)), pt2(Point(0,0)) {}
	stSegLine(Point &p1, Point &p2) :pt1(p1), pt2(p2) {}

	inline bool operator ==(stSegLine &stS)const;

	inline bool Cross(stSegLine &stS)const;///<线段与线段相交
	inline void GetGenLine(stGenLine &stG)const;///<从线段获得直线
	inline double Length()const;//线段长度
	/*inline*/ double FromPoint(Point pt)const;//线段到一个点的最短距离

	friend ostream& operator <<(ostream& os, stSegLine& stS);
};


/// <summary>
/// 直线的标准方程
/// </summary>
struct stGenLine
{
	double da;
	double db;
	double dc;

	stGenLine():da(0.0),db(0.0),dc(0.0){}
	stGenLine(double a,double b,double c):da(a),db(b),dc(c){}
	stGenLine(Point &p1, Point &p2);
	stGenLine(stSegLine& stS);

	inline bool Cross(stGenLine &stG) const;///<直线与直线相交
	inline bool Cross(stSegLine& stS) const;///<直线与线段相交
	inline double FromPoint(Point &pt) const;///<直线与点的距离

	/*inline*/ bool operator||(const stGenLine &stG)const;///<两直线平行

	inline bool operator==(const stGenLine& stG) const;///<两直线斜率在一定范围内判定为同一条
	friend ostream& operator << (ostream& os, stGenLine& stG);
};



#endif // !STRUCT2D_H
