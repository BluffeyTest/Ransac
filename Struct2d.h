/**
 * @file Struct2d.h
 * @author Bluffey (Bluffey@163.com.com)
 * @brief ��άƽ��ṹ��
 * @version 0.1
 * @date 2020-08-18
 * @note inline �ĳ�Ա�����������Ͷ�����Ҫж��ͬһ���ļ����Ȼ�޷�����
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

/**
 * ��ά��
 * */
struct Point2i;
struct Point2f;
struct Point2d;

/**
 * @brief Բ��Բ����ֱ�ߡ��߶Ρ���Բ����Բ���ṹ��
 * 
 */
struct stCircle;
struct stArc;
struct stSegLine;
struct stGenLine;
struct stEllipse;///<��ʱû�о���ʵ��
struct stArcEllipse;///<��ʱû�о���ʵ��

/**
 * @brief ���ζ�ά��
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
	//Point2i(Point2f _p2f) : x((int)(_p2f.x + 0.5)), y((int)(_p2f.y + 0.5)) {}
	//Point2i(Point2d _p2d) : x((int)(_p2d.x + 0.5)), y((int)(_p2d.y + 0.5)) {}

	///< ��ע�������������ǲ�����Ը���У��ʷ�������
	/*inline*/ Point2i operator+(const Point2i &pt) const;	///<�������
	/*inline*/ Point2i operator-(const Point2i &pt) const;	///<�������
	/*inline*/ bool operator==(const Point2i &pt) const;	///<�ж������Ƿ����

	friend std::ostream &operator<<(std::ostream &os, /*const*/ Point2i &pt);
} Point;

/**
 * @brief �����ȸ����Ͷ�ά��
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

	/*inline*/ Point2f operator+(const Point2f &pt) const;
	/*inline*/ Point2f operator-(const Point2f &pt) const;
	/*inline*/ bool operator==(const Point2f &pt) const;


}Pointf;

/**
 * @brief ˫���ȸ����Ͷ�ά��
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

	/*inline*/ Point2d operator+(const Point2d &pt) const;
	/*inline*/ Point2d operator-(const Point2d &pt) const;
	/*inline*/ bool operator==(const Point2d &pt) const;

	//friend ostream & operator<<(ostream &o, const Point2d &pt);
}Pointd;

//�������
/*inline*/ double Distance(Point &pt1, Point &pt2);
double Distance(Point2d &pt1, Point2d &pt2);

/**
 * @brief Բ
 * �����������Ҫ��û�Ҫ���ݸ����͵ĵ㣬���Ȳ��ϵ�ȥ
 * 
 */
struct stCircle
{
	Point2d ptCenter;
	double dR;
	stCircle() : ptCenter(Point2d(0, 0)), dR(0.0) {}
	stCircle(Point2d &pt, double r) : ptCenter(pt), dR(r) {} ///<ֱ��Բ������Բ
	stCircle(Point2d &pt1, Point2d &pt2, Point2d &pt3);		   ///<��������Բ

	/*inline*/ bool operator==(const stCircle &stC) const;
	stCircle Shift(Point2d &pt) const;		//Բƽ��
	/*inline*/ bool Cross(stCircle &stC) const;	 //Բ�ཻ
	/*inline*/ bool Cross(stGenLine &stG) const; //Բ��ֱ���ཻ
	/*inline*/ bool Cross(stSegLine &stS) const; //Բ���߶��ཻ

	/*inline*/ double FromLine(stGenLine &stG) const; //Բ��ֱ�߾���
	/*inline*/ double FromPoint(Point2d &pt) const; //Բ��ֱ�߾���

	friend std::ostream &operator<<(std::ostream &os, stCircle &stC);
};

/**
 * @brief Բ��
 * 
 */
struct stArc
{
	stCircle Circle;
	double dStartAngle; //��ʼ�Ƕȣ�������
	double dEndAngle;	//�����ǶȻ�����

	stArc() : Circle(stCircle()), dStartAngle(0.0), dEndAngle(0.0) {}
	stArc(stCircle &stC, double ds, double de) : Circle(stC), dStartAngle(ds), dEndAngle(de) {}

	friend std::ostream &operator<<(std::ostream &os, stArc &stArc);
};

/**
 * @brief �����߶�
 * 
 */
struct stSegLine
{
	Point pt1;
	Point pt2;

	stSegLine() : pt1(Point(0, 0)), pt2(Point(0, 0)) {}
	stSegLine(Point &p1, Point &p2) : pt1(p1), pt2(p2) {}

	bool operator==(stSegLine &stS) const;	///<�����߶��Ƿ����

	bool Cross(stSegLine &stS) const;	  ///<�߶����߶��ཻ
	void GetGenLine(stGenLine &stG) const; ///<���߶λ��ֱ��
	double Length() const;				  ///<�߶γ���
	double FromPoint(Point pt) const;  ///<�߶ε�һ�������̾���
	double FromPoint(Point2d pt) const;  ///<�߶ε�һ�������̾���


	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);
};

/**
 * @brief ֱ�ߵı�׼����
 * 
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

	bool Cross(stGenLine &stG) const;  ///<ֱ����ֱ���ཻ
	bool Cross(stSegLine &stS) const;  ///<ֱ�����߶��ཻ
	double FromPoint(Point &pt) const; ///<ֱ�����ľ���
	double FromPoint(Pointd &pt) const;///<ֱ�����ľ���

	bool operator||(const stGenLine &stG) const; ///<��ֱ��ƽ��

	bool operator==(const stGenLine &stG) const; ///<��ֱ��б����һ����Χ���ж�Ϊͬһ��
	friend std::ostream &operator<<(std::ostream &os, stGenLine &stG);
};

/**
 * @brief ��Բ
 * 
 */
struct stEllipse
{
	Point2d center;	///<��Բ����
	double a;		///<��Բ�����᳤
	double b;		///<��Բ�̰��᳤
	double angle;	///<��ת�Ƕ�,�Ƕ�ֵ

	stEllipse():center(Point2d(0.0,0.0)),a(0.0),b(0.0),angle(0.0){}
	//stEllipse(stEllipseNormal &stEN);
	//stEllipse()
};


/**
 * @brief ��Բ��һ�㷽��ʽax^2+by^2+cxy+dx+ey = 0;
 * �����͵ı�����
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
		A(_a),B(_b),C(_c),D(_d),E(_e){}				///<���Ѿ��еĲ�������
	stEllipseNormal(Pointd &pt1,Pointd &pt2,Pointd &pt3, 
		Pointd &pt4,Pointd &pt5,Pointd &pt6);		///<�������������Դ�������
	stEllipseNormal(std::vector<Point2f> &vPts);	///<�ӵ㼯��������С���˷���ϳ�����Բ
	stEllipseNormal(stEllipse &_stE);
	
	


}EllipseStd;


#endif // !STRUCT2D_H
