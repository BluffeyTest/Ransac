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


/**
 * @brief ��ά��
 * */
struct Point2i;
struct Point2f;
struct Point2d;

/**
 * @brief ��ά����
 * ����ά���ض���Ϊ��ά������Ϊ����ĳЩ�ط���Ҫ�������û��ˣ�
 * ��������ѧ����������ͬ���ı�����ʽ�����ԾͶ�����һ����
 * 
 */
typedef Point2i vec2i;
typedef Point2f vec2f;
typedef Point2d vec2d;
typedef vec2d	vec;

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





//�������
double Distance(Point &pt1, Point &pt2);
double Distance(Point2d &pt1, Point2d &pt2);



/**
 * @brief �����߶�\n
 * �����յ�����˳���
 */
struct stSegLine
{
	Pointd pt1;///<���
	Pointd pt2;///<�յ�

	stSegLine() : pt1(Pointd(0, 0)), pt2(Pointd(0, 0)) {}
	stSegLine(Pointd &p1, Pointd &p2) : pt1(p1), pt2(p2) {}

	bool operator==(stSegLine &stS) const;	///<�����߶��Ƿ����

	bool Cross(stSegLine &stS) const;	  ///<�߶����߶��ཻ
	void GetGenLine(stGenLine &stG) const; ///<���߶λ��ֱ��
	double Length() const;				  ///<�߶γ���
	double FromPoint(Point pt) const;  ///<�߶ε�һ�������̾���
	double FromPoint(Point2d pt) const;  ///<�߶ε�һ�������̾���

	double Angle() const;				///<�߶εĽǶ�
	double AngleFrom(stSegLine &stS);	///<�����߶εļн�


	friend std::ostream &operator<<(std::ostream &os, stSegLine &stS);
};

/**
 * @brief ֱ�ߵı�׼����
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

	bool Cross(stGenLine &stG) const;  ///<ֱ����ֱ���ཻ
	bool Cross(stSegLine &stS) const;  ///<ֱ�����߶��ཻ
	double FromPoint(Point &pt) const; ///<ֱ�����ľ���
	double FromPoint(Pointd &pt) const;///<ֱ�����ľ���

	double Angle() const;
	double AngleFrom(stGenLine &stG) const;

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
