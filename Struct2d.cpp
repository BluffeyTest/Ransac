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

/**
 * @brief Point2i�ӷ�
 * 
 * @param pt 
 * @return Point2i 
 */
/*inline*/ Point2i Point2i::operator+(const Point2i &pt) const
{
    return Point2i(this->x + pt.x, this->y + pt.y);
}

/**
 * @brief Point2i����
 * 
 * @param pt 
 * @return Point2i 
 */
/*inline*/ Point2i Point2i::operator-(const Point2i &pt) const
{
    return Point2i(this->x - pt.x, this->y - pt.y);
}

/**
 * @brief Point2i�ж��Ƿ����
 * 
 * @param pt 
 * @return Point2i 
 */
/*inline*/ bool Point2i::operator==(const Point2i &pt) const
{
    return (this->x == pt.x && this->y == pt.y);
}

/**
 * @brief ���ص����������
 * 
 */
ostream &operator<<(ostream &os, /*const*/ Point2i &pt)
{
    os<<"( "<<pt.x<<", "<<pt.y<<" )";
    return os;
}

/**
 * @brief Point2f�ӷ�
 * 
 * @param pt 
 * @return Point2f 
 */
/*inline*/ Point2f Point2f::operator+(const Point2f &pt) const
{
    return Point2f(this->x + pt.x, this->y + pt.y);
     
}

/**
 * @brief Point2f����
 * 
 * @param pt 
 * @return Point2f 
 */
/*inline*/ Point2f Point2f::operator-(const Point2f &pt) const
{
    return Point2f(this->x - pt.x, this->y - pt.y);
}

/**
 * @brief Point2f�Ƚ��Ƿ����</br>
 * һ�㲻����ʹ��
 * 
 * @param pt 
 * @return bool 
 */
/*inline*/ bool Point2f::operator==(const Point2f &pt) const
{
    const double eps = 1e-2;//float�ľ���ֻ����λ����������λ��һ��������άС��λ�Ǳ�֤���ȵľͲ�����
    return (fabs(this->x - pt.x)<eps && fabs(this->y - pt.y)<eps );
}

/**
 * @brief Point2d�ӷ�
 * 
 * @param pt 
 * @return Point2d 
 */
/*inline*/ Point2d Point2d::operator+(const Point2d &pt) const
{
    return Point2d(this->x + pt.x, this->y + pt.y);
     
}

/**
 * @brief Point2d����
 * 
 * @param pt 
 * @return Point2d 
 */
/*inline*/ Point2d Point2d::operator-(const Point2d &pt) const
{
    return Point2d(this->x - pt.x, this->y - pt.y);
}

/**
 * @brief Point2d�Ƚ��Ƿ����</br>
 * 
 * @param pt 
 * @return bool 
 */
/*inline*/ bool Point2d::operator==(const Point2d &pt) const
{
    const double eps = 1e-6;//double�ľ�����15λ����������λ����������СһЩ
    return (fabs(this->x - pt.x)<eps && fabs(this->y - pt.y)<eps );
}

/**
 * @brief Construct a new st Circle::st Circle object
 * ʹ����������һ��Բ
 * 
 * @param pt1 
 * @param pt2 
 * @param pt3 
 */
stCircle::stCircle(Point2d &pt1, Point2d &pt2, Point2d &pt3)
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

    //���㹲��
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
 * @brief �Ƚ�����Բ�Ƿ����
 * 
 * @param stC ��һ��Բ
 * @return true ���
 * @return false �����
 */
bool stCircle::operator==(const stCircle &stC) const
{
    if (this->ptCenter.x == stC.ptCenter.x && this->ptCenter.y == stC.ptCenter.y && this->dR == stC.dR)
        return true;
    return false;
}

/**
 * @brief Բ��ƽ��
 * 
 * @param pt ƽ������
 * @return stCircle �µ�Բ
 */
stCircle stCircle::Shift(Point2d &pt) const
{
    Point2d pt1 = this->ptCenter + pt;
    return stCircle(pt1, this->dR);
}

/**
 * @brief ����Բ�Ƿ��ཻ
 * 
 * @param stC ��һ��Բ
 * @return true 
 * @return false 
 */
bool stCircle::Cross(stCircle &stC) const
{
    double dDist = sqrt(pow(this->ptCenter.x - stC.ptCenter.x, 2) + pow(this->ptCenter.y - stC.ptCenter.y, 2));
    if (dDist == (this->dR + stC.dR))
        return true;
    return false;
}

//Բ��ֱ���ཻ
/*inline*/ bool stCircle::Cross(stGenLine &stG) const
{
    double dDistance = this->FromLine(stG); //stG.FromPoint(this->ptCenter);
    if (this->dR < dDistance)
        return true;
    return false;
}

//���Ż�
//���Ӧ���ÿ��������Ŵ���
/*inline*/ bool stCircle::Cross(stSegLine &stS) const
{
    stGenLine stG = stGenLine(stS);
    double d1 = sqrt(pow(stS.pt1.x - this->ptCenter.x, 2) + pow(stS.pt1.y - this->ptCenter.y, 2)); ///<�߶ε�һ���㵽Բ�ĵľ���
    double d2 = sqrt(pow(stS.pt2.x - this->ptCenter.x, 2) + pow(stS.pt2.y - this->ptCenter.y, 2)); ///<�߶εڶ����㵽Բ�ĵľ���
    //double d3 = this->FromLine(stG);///<Բ�ĵ�ֱ�ߵľ���
    double d4 = stS.FromPoint(this->ptCenter);
    if (d1 < this->dR && d2 < this->dR) //����Բ��
        return false;
    if (std::min(d1, d2) < this->dR && max(d1, d2) > this->dR) //һ��Բ��һ��Բ��
        return true;
    if (d4 < this->dR && max(d1, d2) > this->dR) //�����������Բ�ڣ���Զ����Բ��
        return true;
    return false;
}

/*inline*/ double stCircle::FromLine(stGenLine &stG) const
{
    double dDistance = fabs(stG.a * this->ptCenter.x + stG.b * this->ptCenter.y + stG.c) / sqrt(pow(stG.a, 2) + pow(stG.b, 2));
    return dDistance;
}

/*inline*/ double stCircle::FromPoint(Point2d &pt) const
{
    return sqrt(pow(this->ptCenter.x - pt.x, 2) + pow(this->ptCenter.y - pt.y, 2));
}

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
    Point &p1 = stS.pt1;
    Point &p2 = stS.pt2;
    this->a = (double)(p1.y - p2.y);
    this->b = (double)(p2.x - p1.x);
    this->c = (double)(p1.x * p2.y - p2.x * p1.y);
}

double stGenLine::FromPoint(Point &pt) const
{
    double dDistance = fabs(this->a * pt.x + this->b * pt.y + this->c) / sqrt(pow(this->a, 2) + pow(this->b, 2));
    return dDistance;
}

double stGenLine::FromPoint(Pointd &pt) const
{
    double dDistance = fabs(this->a * pt.x + this->b * pt.y + this->c) / sqrt(pow(this->a, 2) + pow(this->b, 2));
    return dDistance;
}

/*inline*/ bool stGenLine::operator||(const stGenLine &stG) const
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

/*inline*/ double stSegLine::FromPoint(Point pt) const
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
 * @brief 
 * 
 * @param pt 
 * @return double 
 */
/*inline*/ double stSegLine::FromPoint(Point2d pt) const
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
 * @return double 
 */
double stSegLine::Angle()
{
    return atan2(pt2.y-pt1.y,pt2.x-pt1.x);
}

/**
 * @brief �����߶�֮��ļн�
 * 
 * @param stS ������һ���߶�
 * @return double 
 */
double AngleFrom(stSegLine &stS)
{

}

/*inline*/ double Distance(Point &pt1, Point &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

double Distance(Point2d &pt1, Point2d &pt2)
{
    return sqrt(pow(pt1.x - pt2.x, 2) + pow(pt1.y - pt2.y, 2));
}

ostream &operator<<(ostream &os, stCircle &stC)
{
    os << "Circle: "
       << "Center = (" << stC.ptCenter.x << ", " << stC.ptCenter.y << "), R = " << stC.dR;
    return os;
}

ostream &operator<<(ostream &os, stArc &stArc)
{
    os << "Arc: " << stArc.Circle << ", startangle = " << stArc.dStartAngle << ", EndAngle = " << stArc.dEndAngle;
    return os;
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
