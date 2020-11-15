/**
 * @file Struct2d.cpp
 * @author Bluffey (Bluffey@163.com)
 * @brief 
 * @version 0.1
 * @date 2020-08-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Struct2d.h"

using namespace std;








stGenLine::stGenLine(Point &p1, Point &p2)
{
    this->a = (double)(p1.y - p2.y);
    this->b = (double)(p2.x - p1.x);
    this->c = (double)(p1.x * p2.y - p2.x * p1.y);
}

stGenLine::stGenLine(Pointd &p1, Pointd &p2)
{
    this->a = (double)(p1.y - p2.y);
    this->b = (double)(p2.x - p1.x);
    this->c = (double)(p1.x * p2.y - p2.x * p1.y);
}

stGenLine::stGenLine(stSegLine &stS)
{
    Pointd &p1 = stS.pt1;
    Pointd &p2 = stS.pt2;
    this->a = (double)(p1.y - p2.y);
    this->b = (double)(p2.x - p1.x);
    this->c = (double)(p1.x * p2.y - p2.x * p1.y);
}

/**
 * @brief ֱ�ߵ���ľ���
 * 
 * @param pt ��
 * @return double 
 */
double stGenLine::FromPoint(Point &pt) const
{
    double dDistance = fabs(this->a * pt.x + this->b * pt.y + this->c) / sqrt(pow(this->a, 2) + pow(this->b, 2));
    return dDistance;
}

/**
 * @brief ֱ�ߵ���ľ���
 * 
 * @param pt ��
 * @return double 
 */
double stGenLine::FromPoint(Pointd &pt) const
{
    double dDistance = fabs(this->a * pt.x + this->b * pt.y + this->c) / sqrt(pow(this->a, 2) + pow(this->b, 2));
    return dDistance;
}

/**
 * @brief ֱ�ߵĽǶ�
 * 
 * @return double 
 */
double stGenLine::Angle() const
{
    return atan2(a,-b);
}

/**
 * @brief ����ֱ��֮��ļн�
 * ������ģ������������ں�һ��ֱ��
 * @param stG 
 * @return double 
 */
double stGenLine::AngleFrom(stGenLine &stG) const
{
    return (atan2(stG.a,-stG.b) - atan2(a,-b));
}

/**
 * @brief ��ֱ��ƽ��
 * 
 * @param stG ��һ��ֱ��
 * @return true 
 * @return false 
 */
bool stGenLine::operator||(const stGenLine &stG) const
{

    double dScale = this->a / stG.a;
    const double eps = 1e-6;
    if (fabs(this->a - stG.a * dScale) < eps && fabs(this->b - stG.b * dScale) < eps)
        return true;
    return false;
}

inline bool stGenLine::operator==(const stGenLine &stG) const
{
    double dScale = this->a / stG.a;
    const double eps = 1e-6;
    if (fabs(this->a - stG.a * dScale) < eps && fabs(this->b - stG.b * dScale) < eps && fabs(this->c - stG.c * dScale) < eps)
        return true;
    return false;
}

inline bool stSegLine::operator==(stSegLine &stS) const
{
    if (this->pt1 == stS.pt1 && this->pt2 == stS.pt2)
        return true;
    return false;
}

//���ſ���ʵ��
inline bool stSegLine::Cross(stSegLine &stS) const
{
    if (!(min(this->pt1.x, this->pt2.x) <= max(stS.pt1.x, stS.pt2.x) 
        && min(stS.pt1.y, stS.pt2.y) <= max(this->pt1.y, this->pt2.y) 
        && min(stS.pt1.x, stS.pt2.x) <= max(this->pt1.x, this->pt2.x) 
        && min(this->pt1.y, this->pt2.y) <= max(stS.pt1.y, stS.pt2.y))
        )
            return false;

    double u, v, w, z;
    u = (stS.pt1.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt1.y - this->pt1.y);
    v = (stS.pt2.x - this->pt1.x) * (this->pt2.y - this->pt1.y) - (this->pt2.x - this->pt1.x) * (stS.pt2.y - this->pt1.y);
    w = (this->pt1.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt1.y - stS.pt1.y);
    z = (this->pt2.x - stS.pt1.x) * (stS.pt2.y - stS.pt1.y) - (stS.pt2.x - stS.pt1.x) * (this->pt2.y - stS.pt1.y);

    return (u * v <= 0.00000001 && w * z <= 0.00000001);
}

inline void stSegLine::GetGenLine(stGenLine &stG) const
{
    stG.a = (double)(this->pt1.y - this->pt2.y);
    stG.b = (double)(this->pt2.x - this->pt1.x);
    stG.c = (double)(this->pt1.x * this->pt2.y - this->pt2.x * this->pt1.y);
}

inline double stSegLine::Length() const
{
    return sqrt(pow(this->pt1.x - this->pt2.x, 2) + pow(this->pt1.y - this->pt2.y, 2));
    ;
}

/**
 * @brief �߶ε���ľ���
 * ��ֱ�ߵ���ľ�����ȣ��߶ε���ľ�������ֵ������ħżһ���˵㵽�õ㶼�ľ���
 * @param pt ��
 * @return double 
 */
double stSegLine::FromPoint(Point pt) const
{
    double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
        + (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
    double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
    double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
    if (r <= 0)
        return sqrt(dAP2); //��һ�����, ����AP�ĳ�
    else if (r >= 1)
        return sqrt(dBP2); //�ڶ������, ����BP�ĳ���
    else                   //���������, ����PC�ĳ���
    {
        double AC = r * this->Length(); //����AC�ĳ���,(AC=r*|AB|)
        return sqrt(dAP2 - AC * AC);    //�ٹ��ɶ�����PC�ĳ���
    }
    return 0.0;
}

/**
 * @brief �߶ε���ľ���
 * ��ֱ�ߵ���ľ�����ȣ��߶ε���ľ�������ֵ������ħżһ���˵㵽�õ㶼�ľ���
 * @param pt ��
 * @return double 
 */
double stSegLine::FromPoint(Point2d pt) const
{
    double r = ((pt.x - this->pt1.x) * (this->pt2.x - this->pt1.x) 
        + (pt.y - this->pt1.y) * (this->pt2.y - this->pt1.y)) / this->Length();
    double dAP2 = pow(this->pt1.x - pt.x, 2) + pow(this->pt1.y - pt.y, 2);
    double dBP2 = pow(pt.x - this->pt2.x, 2) + pow(pt.y - this->pt2.y, 2);
    if (r <= 0)
        return sqrt(dAP2); //��һ�����, ����AP�ĳ�
    else if (r >= 1)
        return sqrt(dBP2); //�ڶ������, ����BP�ĳ���
    else                   //���������, ����PC�ĳ���
    {
        double AC = r * this->Length(); //����AC�ĳ���,(AC=r*|AB|)
        return sqrt(dAP2 - AC * AC);    //�ٹ��ɶ�����PC�ĳ���
    }
    return 0.0;
}

/**
 * @brief �߶ε���б�Ƕ�
 * 
 * @return double �Ƕȣ�������
 */
double stSegLine::Angle() const
{
    return atan2(pt2.y-pt1.y,pt2.x-pt1.x);
}

/**
 * @brief �����߶�֮��ļн�
 * 
 * @param stS ������һ���߶�
 * @return double �Ƕȣ�������
 */
double stSegLine::AngleFrom(stSegLine &stS) 
{
    return (stS.Angle() - this->Angle());
}

double Distance(Point &pt1, Point &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

double Distance(Point2d &pt1, Point2d &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}











ostream &operator<<(ostream &os, stSegLine &stS)
{
    os << "SegLine: "
       << "(" << stS.pt1.x << ", " << stS.pt1.y << ")----( " << stS.pt2.x << ", " << stS.pt2.y << ")";
    return os;
}

ostream &operator<<(ostream &os, stGenLine &stG)
{
    os << "GenLine: " << stG.a << " * x ";
    stG.b < 0 ? os << stG.b : os << "+ " << stG.b;
    os << " * y ";
    stG.c < 0 ? os << stG.c : os << "+ " << stG.c;
    os << " = 0.0";
    return os;
}
