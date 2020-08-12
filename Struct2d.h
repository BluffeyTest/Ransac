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

//�������
/*inline*/ double Distance(Point &pt1, Point &pt2);

/// <summary>
/// Բ
/// �����������Ҫ��û�Ҫ���ݸ����͵ĵ㣬���Ȳ��ϵ�ȥ
/// </summary>
struct stCircle
{
	Point ptCenter;
	double dR;
	stCircle():ptCenter(Point(0,0)),dR(0.0){}
	stCircle(Point &pt,double r):ptCenter(pt),dR(r){}///<ֱ��Բ������Բ
	stCircle(Point& pt1, Point& pt2, Point& pt3);///<��������Բ

	inline bool operator==(const stCircle &stC) const;
	stCircle Shift(Point& pt) const;
	inline bool Cross(stCircle& stC) const;//Բ�ཻ
	inline bool Cross(stGenLine& stG) const;//Բ��ֱ���ཻ
	inline bool Cross(stSegLine& stS) const;//Բ���߶��ཻ

	inline double FromLine(stGenLine& stG) const;//Բ��ֱ�߾���
	/*inline*/ double FromPoint(Point& pt) const;//Բ��ֱ�߾���

	friend ostream& operator <<(ostream& os, stCircle &stC);
	
};

/// <summary>
/// Բ��
/// </summary>
struct stArc
{
	stCircle Circle;
	double dStartAngle;//��ʼ�Ƕȣ�������
	double dEndAngle;	//�����ǶȻ�����

	stArc():Circle(stCircle()), dStartAngle(0.0), dEndAngle(0.0) {}
	stArc(stCircle &stC,double ds,double de):Circle(stC),dStartAngle(ds),dEndAngle(de){}

	friend ostream& operator <<(ostream& os, stArc &stArc);
};

/// <summary>
/// �����߶�
/// </summary>
struct stSegLine
{
	Point pt1;
	Point pt2;

	stSegLine() :pt1(Point(0,0)), pt2(Point(0,0)) {}
	stSegLine(Point &p1, Point &p2) :pt1(p1), pt2(p2) {}

	inline bool operator ==(stSegLine &stS)const;

	inline bool Cross(stSegLine &stS)const;///<�߶����߶��ཻ
	inline void GetGenLine(stGenLine &stG)const;///<���߶λ��ֱ��
	inline double Length()const;//�߶γ���
	/*inline*/ double FromPoint(Point pt)const;//�߶ε�һ�������̾���

	friend ostream& operator <<(ostream& os, stSegLine& stS);
};


/// <summary>
/// ֱ�ߵı�׼����
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

	inline bool Cross(stGenLine &stG) const;///<ֱ����ֱ���ཻ
	inline bool Cross(stSegLine& stS) const;///<ֱ�����߶��ཻ
	inline double FromPoint(Point &pt) const;///<ֱ�����ľ���

	/*inline*/ bool operator||(const stGenLine &stG)const;///<��ֱ��ƽ��

	inline bool operator==(const stGenLine& stG) const;///<��ֱ��б����һ����Χ���ж�Ϊͬһ��
	friend ostream& operator << (ostream& os, stGenLine& stG);
};



#endif // !STRUCT2D_H
